#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"

// Menu icon file: either loaded whole, or read entry by entry into a small LRU cache
struct UnkIconFile {
    const char* file_;                          // 0x00  file loaded whole
    DataObject data_;                           // 0x04
    const char* streamFile_;                    // 0x14  file read entry by entry
    int entrySize_;                             // 0x18
    int cacheNum_;                              // 0x1C
    int* keys_;                                 // 0x20
    int* ages_;                                 // 0x24
    char* cache_;                               // 0x28
    void* header_;                              // 0x2C

    void unkfunc_0206dc2c(const char* file);
    void unkfunc_0206dc3c(const char* file, const char* streamFile, int entrySize, int cacheNum);
    void* unkfunc_0206dc68(int index);         // icon data, index 9999: palette
    void unkfunc_0206dd28();                    // clear the cache
    void unkfunc_0206dd54(int entrySize, int cacheNum);   // allocate the cache, load the header
    char* unkfunc_0206dde4(int index);         // cached entry (NULL: not cached)
};
