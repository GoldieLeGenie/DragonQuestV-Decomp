#pragma once
#include <globaldefs.h>

// Overlay loaded on demand (one at a time)
struct UnkOverlaySlot {
    int loaded_;                                // 0x00
    int id_;                                    // 0x04

    UnkOverlaySlot();
    ~UnkOverlaySlot();
    void load(int id);              // load (unloads the previous one)
    void unload();                    // unload
};

extern UnkOverlaySlot data_020a29ec;            // window overlay of the game parts (18-20)
extern UnkOverlaySlot data_020a29f4;

void loadWindowOverlay(int type);                // load the window overlay: 1 = 19, 2 = 18, 3 = 20
void unloadWindowOverlay();                        // unload the window overlay
void loadOverlay(int id);                  // FS_LoadOverlay
void unloadOverlay(int id);                  // FS_UnloadOverlay
void setPadLock(int flag);                // flag != 0: set bit 15 of data_0209a238
int isPadInputBlocked();                         // data_0209a238 has bit 15 set

extern unsigned int data_0209a238;
