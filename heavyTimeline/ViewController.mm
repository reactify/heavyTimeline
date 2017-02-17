//
//  ViewController.mm
//  HeavyTimeline
//
//  Created by Ragnar Hrafnkelsson on 17/02/2017.
//  Copyright (c) 2017 Reactify. All rights reserved.
//

#include <memory>
#include "portaudio.h"
#include "Heavy_Test.hpp"
#import  "ViewController.h"

using ContextRef = std::unique_ptr<Heavy_Test>;

// Constants
const double SampleRate = 44100.0;
const unsigned long BlockSize = 256;

typedef struct
{
  ContextRef context;
  int64_t processedFrames;
} UserData;


int check_pa_error( PaError error );

static int paCallback( const void *input,
                       void *output,
                       unsigned long frameCount,
                       const PaStreamCallbackTimeInfo* timeInfo,
                       PaStreamCallbackFlags statusFlags,
                       void *userData )
{
  UserData *data = (UserData *)userData;
  // short * out = (short *)output;
  // memset( out, 0, frameCount * sizeof(short) );
  
  data->processedFrames += data->context->processInline( nullptr, nullptr, (int)frameCount );
  
  return paContinue;
}

void printHook( HeavyContextInterface *c, const char *printName, const char *str, const HvMessage *m ) {
  double timestampMs = 1000.0 * ((double) hv_msg_getTimestamp(m)) / hv_getSampleRate(c);
  printf("[@ %.3fms] %s: %s\n", timestampMs, printName, str);
}


@interface ViewController()
{
  PaStream *stream;
  UserData data;
}
@property (weak) IBOutlet NSSlider *slider;
@property (strong) NSTimer *timer;
@end


@implementation ViewController

- (void)dealloc {
  _timer = nil;
}

- (void)viewDidLoad {
  [super viewDidLoad];
  [self start];
}

- (void)viewDidAppear {
  [super viewDidAppear];
}

- (void)viewWillDisappear {
  [super viewWillDisappear];
  [self stop];
}

- (int)setup {
  
  data.context = ContextRef( new Heavy_Test( SampleRate ) );
  data.context->setPrintHook( &printHook );
  
  // Setup PortAudio
  if ( check_pa_error( Pa_Initialize() ) ) return 1;
  
  // Opening stream
  if ( check_pa_error(
                      Pa_OpenDefaultStream(&stream, 0, 2,
                                           paInt16, SampleRate, BlockSize, paCallback, &data)) ) {
                      return 1;
                     }
  return 0;
}

- (int)start {
  if ( Pa_IsStreamActive(stream) < 0 ) {
    [self setup];
  }
  
  NSLog(@"Starting audio");
  
  // Start Processing
  if (check_pa_error(Pa_StartStream(stream))) return 1;
  
  self.timer = [NSTimer scheduledTimerWithTimeInterval:1.0
                                                target:self
                                              selector:@selector(updatePlayhead)
                                              userInfo:nil
                                               repeats:YES];
  return 0;
}

- (int)pause {
  check_pa_error( Pa_StopStream(stream) );
  
  [self.timer invalidate];
  self.timer = nil;
  
  return 0;
}

- (int)stop {
  if ( check_pa_error(Pa_CloseStream(stream)) ) return 1;
  
  if ( check_pa_error(Pa_Terminate()) ) return 1;
  
  printf("Shut down\n");
  return 0;
}

- (void)updatePlayhead {
  int64_t processedFrames = data.processedFrames;
  double seconds = (double)processedFrames / SampleRate;
  self.slider.doubleValue = seconds;
}

- (IBAction)onSliderEvent:(id)sender {
  NSEvent *event = [[NSApplication sharedApplication] currentEvent];
  BOOL startingDrag = event.type == NSLeftMouseDown;
  BOOL endingDrag   = event.type == NSLeftMouseUp;
  BOOL dragging     = event.type == NSLeftMouseDragged;
  
  NSAssert( startingDrag || endingDrag || dragging, @"unexpected event type caused slider change: %@", event );
  
  if ( startingDrag ) {
    NSLog(@"Slider value started changing, pausing audio" );
    [self pause];
  }

  if (endingDrag) {
    NSLog(@"Slider value stopped changing, seek to target position");
    
    int64_t targetFrames = (int64_t)([sender doubleValue] * SampleRate);
    
    // If target is lower than already processed
    // we need to rewind and create new context
    // and process frames up until the target
    if ( targetFrames < data.processedFrames ) {
      dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        data.context = ContextRef( new Heavy_Test( SampleRate ) );
        data.context->setPrintHook( &printHook );
        data.processedFrames = data.context->process( nullptr, nullptr, (int)targetFrames );
        dispatch_async(dispatch_get_main_queue(), ^{
          [self start];
        });
      });
      return;
    }
    
    // Else, we calculate frames needed to seek forward and process
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
      int64_t framesToProcess = targetFrames - data.processedFrames;
      data.processedFrames += data.context->process( nullptr, nullptr, (int)framesToProcess );
      dispatch_async(dispatch_get_main_queue(), ^{
        [self start];
      });
    });
  }
}

int check_pa_error( PaError error ) {
  if (error != paNoError) {
    printf("(portaudio error) %s\n", Pa_GetErrorText(error));
    return 1;
  }
  return 0;
}

@end
