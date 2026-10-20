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
        int readOffset_;                             // 0x4C offset of the next unkfunc_0204b21c read
        int readSize_;                             // 0x50 size of the next unkfunc_0204b21c read

        void unkfunc_0204b1cc(int unused);      // init
        void unkfunc_0204b1e8();                // load the FAT/FNT table
        int unkfunc_0204b21c(const char* fname, void* dst, int a);  // load file into buffer
        int unkfunc_0204b250(const char* fname, void* dst, int offset, int size, int a);  // load a part of a file
        int unkfunc_0204b26c(const char* fname, void* dst);
        int unkfunc_0204b284(const char* fname, void* dst);
        void* unkfunc_0204b29c(const char* fname, int a, LoadSwitch sw);           // load file
        void* unkfunc_0204b310(const char* fname, LoadSwitch sw);                  // load an LZ-compressed file
        int unkfunc_0204b32c(const char* fname, LoadSwitch sw);                    // file size
        bool isExist(const char* fname, LoadSwitch sw);
        int unkfunc_0204b370(const char* fname, void* dst);         // read a file
        void* unkfunc_0204b418(const char* fname);                  // read an LZ-compressed file
        int unkfunc_0204b4c8(const char* fname);                    // file size
    };

    extern File g_File;
}
