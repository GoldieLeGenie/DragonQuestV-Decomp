#pragma once
#include <globaldefs.h>
#include "nitro/gx.h"

// OAM shadow buffer of one screen
struct UnkOamBuffer {
    GXOamAttr oam_[128];                        // 0x000
    int count_;                                 // 0x400
    int prevCount_;                             // 0x404
    int unk_408;                                // 0x408

    void init();                    // init
    void clear();                    // clear
    void requestTransfer(int type);            // queue the transfer
    GXOamAttr* allocEntry();              // next free entry
};

// palette shadow buffer (16 palettes of 16 colors)
struct UnkPaletteBuffer {
    unsigned short color_[0x100];               // 0x000

    void requestTransfer(int type);            // queue the transfer
    void setColor(int index, int color, unsigned short rgb);
    void loadColors(int index, int color, const void* src, int count);
};

// queued copy to the VRAM, OAM or palettes
struct UnkVramRequest {
    int active_;                                // 0x00
    int type_;                                  // 0x04
    int offset_;                                // 0x08
    void* base_;                                // 0x0C
    const void* src_;                           // 0x10
    int size_;                                  // 0x14
    void* buffer_;                              // 0x18 freed after the copy
};

struct UnkVramRequestQueue {
    UnkVramRequest request_[128];               // 0x000
    int size_;                                  // 0xE00 bytes copied by the last update
    int lines_;                                 // 0xE04 lines spent by the last update

    UnkVramRequestQueue();
    void* getDestination(int type);           // destination of a type
    int executeRequest(UnkVramRequest* request);  // copy
};

extern UnkVramRequestQueue data_021003e8;

void flushVramRequests();                        // copy all the queued requests
UnkVramRequest* requestCompressedVramCopy(int type, int offset, void* data, int size);   // queue compressed data
UnkVramRequest* requestVramCopy(int type, int offset, const void* src, int size);  // queue
int getBgCharVramType(int bg);                   // BG character type (0-3 main, 4-7 sub)
int getBgScreenVramType(int bg);                   // BG screen type (0-3 main, 4-7 sub)

extern "C" {
    void func_02070224(unsigned int value, void* dest, unsigned int size);  // fill
    void* func_020757fc(void);                  // BG0 character
    void* func_02075850(void);                  // BG1 character
    void* func_020758a4(void);                  // BG2 character
    void* func_02075934(void);                  // BG3 character
    void* func_02075830(void);                  // sub BG0 character
    void* func_02075884(void);                  // sub BG1 character
    void* func_020758f4(void);                  // sub BG2 character
    void* func_0207598c(void);                  // sub BG3 character
    void* func_02075564(void);                  // BG0 screen
    void* func_020755b8(void);                  // BG1 screen
    void* func_0207560c(void);                  // BG2 screen
    void* func_02075704(void);                  // BG3 screen
    void* func_02075598(void);                  // sub BG0 screen
    void* func_020755ec(void);                  // sub BG1 screen
    void* func_02075690(void);                  // sub BG2 screen
    void* func_02075788(void);                  // sub BG3 screen
}
