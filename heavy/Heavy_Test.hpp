/**
 * Copyright (c) 2017 Enzien Audio, Ltd.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, and/or
 * sublicense copies of the Software, strictly on a non-commercial basis,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 * 
 * DO NOT MODIFY. THIS CODE IS MACHINE GENERATED BY THE ENZIEN AUDIO HEAVY COMPILER
 */

#ifndef _HEAVY_CONTEXT_TEST_HPP_
#define _HEAVY_CONTEXT_TEST_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlPrint.h"
#include "HvControlBinop.h"
#include "HvControlDelay.h"
#include "HvControlSystem.h"
#include "HvControlVar.h"
#include "HvControlCast.h"

class Heavy_Test : public HeavyContext {

 public:
  Heavy_Test(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_Test();

  const char *getName() override { return "Test"; }
  int getNumInputChannels() override { return 0; }
  int getNumOutputChannels() override { return 0; }

  int process(float **inputBuffers, float **outputBuffer, int n) override;
  int processInline(float *inputBuffers, float *outputBuffer, int n) override;
  int processInlineInterleaved(float *inputBuffers, float *outputBuffer, int n) override;

  int getParameterInfo(int index, HvParameterInfo *info) override;

  

 private:
  HvTable *getTableForHash(hv_uint32_t tableHash) override;
  void scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) override;

  // static sendMessage functions
  static void cBinop_a0HQ9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_MNnrJ_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cMsg_8fq8Q_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_u5Dzj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_uTMIK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_zrwKo_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_8ouos_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_4lwGp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_j1yZD_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_J2Qew_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_W0OQm_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_8WgZ8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_fhXFX_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_YMM5p_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_PeanV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_csIqt_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_VkiBV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_DhNRV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_73Ifa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_6iq1x_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_Jpz28_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_GQc6I_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  ControlBinop cBinop_a0HQ9;
  ControlVar cVar_uTMIK;
  ControlBinop cBinop_zrwKo;
  ControlBinop cBinop_4lwGp;
  ControlDelay cDelay_J2Qew;
  ControlBinop cBinop_fhXFX;
  ControlBinop cBinop_csIqt;
  ControlBinop cBinop_73Ifa;
};

#endif // _HEAVY_CONTEXT_TEST_HPP_