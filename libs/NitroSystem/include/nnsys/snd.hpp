#pragma once

// NitroSystem sound functions without a name in the libs headers
extern "C" {
    void func_0207b384(void);                                       // NNS_SndMain
    void func_0207b480(int playerNo, int count);
    void func_0207b494(int playerNo, int size);
    void func_0207b504(void* handle, int fadeFrame);                // NNS_SndPlayerStopSeq
    void func_0207b510(void* handle, int flag);                     // NNS_SndPlayerPause
    void func_0207b51c(void* handle);                               // NNS_SndHandleInit
    int func_0207b534(int playerNo);                                // NNS_SndPlayerCountPlayingSeqByPlayerNo
    void func_0207b568(void* handle, int volume);                   // NNS_SndPlayerSetVolume
    void func_0207b578(void* handle, int priority);
    void func_0207b59c(void* handle, unsigned short trackBitMask, int value);
    int func_0207b5e0(void* handle);
    void func_0207be8c(int level);
    void func_0207c0c8(void* arc, void* file, void* heap, int flag);    // NNS_SndArcInit
    void* func_0207c5fc(void* memory, unsigned int size);           // NNS_SndHeapCreate
    void func_0207c658(void* heap);                                 // NNS_SndHeapClear
    int func_0207c70c(void* heap);                                  // NNS_SndHeapSaveState
    void func_0207c740(void* heap, int level);                      // NNS_SndHeapLoadState
    int func_0207c844(int no, void* heap);
    int func_0207c860(int no, void* heap);
    int func_0207c87c(int seqNo, unsigned int loadFlag, void* heap);
    void func_0207ce50(int playerHeap);
    int func_0207ceac(void* handle, int seqNo);                     // NNS_SndArcPlayerStartSeq
    int func_0207ced8(void* handle, int seqArcNo, int index);       // NNS_SndArcPlayerStartSeqArc
    int func_0207cf2c(void* handle, int playerNo, int bankNo, int playerPrio, int seqArcNo, int index);  // NNS_SndArcPlayerStartSeqArcEx
    void func_0207d0a0(unsigned long threadPrio, void* heap);       // stream player init
    void func_0207d244(void* handle, int no, int flag);
    void func_0207d260(void* handle, int value);
    void func_0207d270(void* handle, int volume);
    void func_0207d280(void* handle);
    int func_0207d29c(void* handle);
}
