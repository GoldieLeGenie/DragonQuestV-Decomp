#pragma once
#include <globaldefs.h>

// VRAM transfer task (NitroSystem)
struct UnkVramTransferTask {
    int type_;                                  // 0x00
    void* src_;                                 // 0x04
    int address_;                               // 0x08
    int size_;                                  // 0x0C
};

// texture/palette VRAM managers and the VRAM transfer queue of the dss engine
struct VramTransferManager {
    int unk_00;                                 // 0x00
    int plttUsed_;                                 // 0x04 palette VRAM in use
    unsigned int texVramFree_;                        // 0x08 texture VRAM size
    int texSize_;                               // 0x0C
    UnkVramTransferTask tasks_[0x80];           // 0x10
    int unk_810;                                // 0x810
    int vblankTransfer_;                                // 0x814 transfer in the V-blank

    VramTransferManager();
    ~VramTransferManager();
    void initTransferQueue();                        // init the transfer queue
    void initVramManagers(int texSize, int plttSize); // init the texture/palette VRAM managers
    void onPartTerminate();
    int allocTexVram(int size);                 // allocates a texture block, returns its handle
    void freeTexVram(unsigned int handle);     // frees a texture block
    int getTexVramAddr(unsigned int handle);      // address of a texture block
    int getTexVramSize(unsigned int handle);      // size of a texture block
    int allocPlttVram(int size);                 // allocates a palette block, returns its handle
    void freePlttVram(unsigned int handle);     // frees a palette block
    int getPlttVramAddr(unsigned int handle);      // address of a palette block
    int getPlttVramSize(unsigned int handle);      // size of a palette block
    void transferToVram(int type, void* src, int address, unsigned int size, int flag);
    void doTransfers();                        // do the queued transfers
};

extern VramTransferManager data_020f4f74;
extern unsigned char data_020f578c[0x800];      // palette VRAM manager work
extern unsigned char data_020f5f8c[0x800];      // texture VRAM manager work

extern "C" {
    void func_02086778(UnkVramTransferTask* tasks, int count);             // NNS_GfdInitVramTransferManager
    void func_02086790(void);                                               // NNS_GfdDoVramTransfer
    int func_020867d0(int type, int address, void* src, unsigned int size); // NNS_GfdRegisterNewVramTransferTask
    int func_02086814(void);
    unsigned int func_02086aa0(int count);                                  // NNS_GfdGetLnkTexVramManagerWorkSize
    void func_02086aa4(int size, int size4x4, void* work, unsigned int workSize, int useAsDefault);    // NNS_GfdInitLnkTexVramManager
    unsigned int func_02086cc4(int count);                                  // NNS_GfdGetLnkPlttVramManagerWorkSize
    void func_02086cc8(int size, void* work, unsigned int workSize, int useAsDefault);                  // NNS_GfdInitLnkPlttVramManager
    unsigned int func_02086adc(unsigned int size, int is4x4, unsigned int opt);  // NNS_GfdAllocLnkTexVram
    int func_02086b40(unsigned int key);                                    // NNS_GfdFreeLnkTexVram
    unsigned int func_02086d00(unsigned int size, int is4Pltt, unsigned int opt);  // NNS_GfdAllocLnkPlttVram
    int func_02086d84(unsigned int key);                                    // NNS_GfdFreeLnkPlttVram
}

extern int (*data_0209c788)(int size, int is4x4, int opt);     // NNS_GfdDefaultFuncAllocTexVram
extern int (*data_0209c78c)(int key);                          // NNS_GfdDefaultFuncFreeTexVram
extern int (*data_0209c790)(int size, int is4Pltt, int opt);   // NNS_GfdDefaultFuncAllocPlttVram
extern int (*data_0209c794)(int key);                          // NNS_GfdDefaultFuncFreePlttVram
