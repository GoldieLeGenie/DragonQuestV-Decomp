#pragma once
#include <globaldefs.h>

// heap block of the allocation log
struct UnkHeapLogEntry {
    int state_;                                 // 0x00 0: free, 1: allocated, 2: allocated before the mark
    void* addr_;                                // 0x04
    int size_;                                  // 0x08
    void* caller_;                              // 0x0C return address of the allocation
};

// allocation log of the dss heaps
struct UnkHeapLog {
    UnkHeapLogEntry entries_[256];              // 0x0000
    int enabled_;                               // 0x1000
    int unk_1004;                               // 0x1004

    void initialize();                    // init
    void recordAlloc(const char* name, void* addr, int size, void* caller, void** heap);   // add a block
    void recordFree(const char* name, void* addr, void* caller, void** heap);             // remove a block
    char* getLogText();                   // text of the allocated blocks
    void markLoggedEntries();                    // mark the allocated blocks
};

extern char data_020fd2a4[0x400];
extern UnkHeapLog data_020fd6a4;
