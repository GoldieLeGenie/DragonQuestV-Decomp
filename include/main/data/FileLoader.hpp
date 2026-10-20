#pragma once
#include <globaldefs.h>
#include "nitro/fs.hpp"

namespace dss {
    struct File {
        enum LoadSwitch {
            None = 0,
            Switching = 1,
        };

        FSFile file_;                           // 0x00
        int size_;                              // 0x48 size of the last loaded file
        int readOffset_;                             // 0x4C offset of the next loadToBuffer read
        int readSize_;                             // 0x50 size of the next loadToBuffer read

        void init(int unused);      // init
        void loadFsTable();                // load the FAT/FNT table
        int loadToBuffer(const char* fname, void* dst, int a);  // load file into buffer
        int loadPartToBuffer(const char* fname, void* dst, int offset, int size, int a);  // load a part of a file
        int unkfunc_0204b26c(const char* fname, void* dst);
        int unkfunc_0204b284(const char* fname, void* dst);
        void* allocAndLoad(const char* fname, int a, LoadSwitch sw);           // load file
        void* loadCompressed(const char* fname, LoadSwitch sw);                  // load an LZ-compressed file
        int getFileSize(const char* fname, LoadSwitch sw);                    // file size
        bool isExist(const char* fname, LoadSwitch sw);
        int readRomFile(const char* fname, void* dst);         // read a file
        void* readCompressedFile(const char* fname);                  // read an LZ-compressed file
        int getRomFileSize(const char* fname);                    // file size
    };

    extern File g_File;
}
