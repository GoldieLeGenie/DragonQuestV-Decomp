#pragma once

// C++ subset of nitro/fs.h
struct FSFile {
    char unk_00[0x24];
    unsigned int startRomOffset;                // 0x24
    unsigned int endRomOffset;                  // 0x28
    char unk_2c[0x1c];
};

extern "C" {
    int FS_LoadOverlay(void* overlay, unsigned int overlayID);
    int FS_UnloadOverlay(void* overlay, unsigned int overlayID);
    unsigned int FS_TryLoadTable(void* buf, unsigned int size);
    void func_02073868(FSFile* file);           // FS_InitFile
    int func_02073a3c(FSFile* file, const char* path);  // FS_OpenFile
    int func_02073a68(FSFile* file);            // FS_CloseFile
    int func_02073b58(FSFile* file, void* buf, int size);  // FS_ReadFile
    int func_02073b64(FSFile* file, int pos, int mode);     // FS_SeekFile
}
