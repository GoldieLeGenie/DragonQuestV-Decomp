#pragma once
#include <globaldefs.h>

// Overlay loaded on demand (one at a time)
struct UnkOverlaySlot {
    int loaded_;                                // 0x00
    int id_;                                    // 0x04

    UnkOverlaySlot();
    ~UnkOverlaySlot();
    void unkfunc_0204b580(int id);              // load (unloads the previous one)
    void unkfunc_0204b5a8();                    // unload
};

extern UnkOverlaySlot data_020a29ec;            // window overlay of the game parts (18-20)
extern UnkOverlaySlot data_020a29f4;

void unkfunc_02018e6c(int type);                // load the window overlay: 1 = 19, 2 = 18, 3 = 20
void unkfunc_02018eac();                        // unload the window overlay
void unkfunc_0204b5d4(int id);                  // FS_LoadOverlay
void unkfunc_0204b5e8(int id);                  // FS_UnloadOverlay
void unkfunc_0204b5fc(int flag);                // flag != 0: set bit 15 of data_0209a238
int unkfunc_0204b61c();                         // data_0209a238 has bit 15 set

extern unsigned int data_0209a238;
