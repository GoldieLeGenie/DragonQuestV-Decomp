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

    void setup(const char* file);
    void setupStream(const char* file, const char* streamFile, int entrySize, int cacheNum);
    void* getData(int index);         // icon data, index 9999: palette
    void clearCache();                    // clear the cache
    void setupCache(int entrySize, int cacheNum);   // allocate the cache, load the header
    char* findCachedEntry(int index);         // cached entry (NULL: not cached)
};
