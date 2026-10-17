// Sound archive: header/table loading and info/file access for the current archive.
#include "snd_internal.h"

#pragma thumb on

typedef struct UnkSndArcTable {
    /* 0x00 */ u32 count;
    /* 0x04 */ u32 offsets[1];
} UnkSndArcTable;

typedef struct UnkSndArcInfo {
    /* 0x00 */ u8 magic[4];
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 seqOffset;
    /* 0x0C */ u32 seqArcOffset;
    /* 0x10 */ u32 bankOffset;
    /* 0x14 */ u32 waveArcOffset;
    /* 0x18 */ u32 playerOffset;
    /* 0x1C */ u32 groupOffset;
    /* 0x20 */ u32 strmPlayerOffset;
    /* 0x24 */ u32 strmOffset;
} UnkSndArcInfo;

typedef struct UnkSndArcFatEntry {
    /* 0x00 */ u32 offset;
    /* 0x04 */ u32 size;
    /* 0x08 */ void* mem;
    /* 0x0C */ u32 unk_0c;
} UnkSndArcFatEntry;

typedef struct UnkSndArcFat {
    /* 0x00 */ u8 magic[4];
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 count;
    /* 0x0C */ UnkSndArcFatEntry entries[1];
} UnkSndArcFat;

typedef struct UnkSndArcHeader {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ u32 symbOffset;
    /* 0x14 */ u32 symbSize;
    /* 0x18 */ u32 infoOffset;
    /* 0x1C */ u32 infoSize;
    /* 0x20 */ u32 fatOffset;
    /* 0x24 */ u32 fatSize;
    /* 0x28 */ u32 fileOffset;
    /* 0x2C */ u32 fileSize;
} UnkSndArcHeader;

typedef struct UnkSndArc {
    /* 0x00 */ UnkSndArcHeader header;
    /* 0x30 */ BOOL fileOpened;
    /* 0x34 */ FS_File file;
    /* 0x7C */ FS_FileIdentifier fileId;
    /* 0x84 */ UnkSndArcFat* fat;
    /* 0x88 */ void* symb;
    /* 0x8C */ UnkSndArcInfo* info;
    /* 0x90 */ void* unk_90;
} UnkSndArc;

static inline void* UnkSndArc_OffsetToPtr(const void* base, u32 offset) {
    if (offset == 0) {
        return NULL;
    }
    return (u8*)base + offset;
}
#define OFFSET_TO_PTR(base, ofs) UnkSndArc_OffsetToPtr(base, ofs)

UnkSndArc* data_02123cb0; // current archive

void* func_0207c6c8(void* heap, u32 size, void (*callback)(void*, u32, void*, u32), void* data1, u32 data2);

BOOL func_0207c12c(UnkSndArc* arc, void* heap, BOOL loadSymb);
void func_0207c5e4(void* mem, u32 size, void* data1, u32 data2);
void func_0207c5ec(void* mem, u32 size, void* data1, u32 data2);
void func_0207c5f4(void* mem, u32 size, void* data1, u32 data2);

void func_0207c0c8(UnkSndArc* arc, const char* path, void* heap, BOOL loadSymb) {
    arc->info = NULL;
    arc->fat = NULL;
    arc->symb = NULL;
    arc->unk_90 = NULL;

    if (!func_0207399c(&arc->fileId, path)) {
        return;
    }

    func_02073868(&arc->file);
    if (!func_020739f4(&arc->file, arc->fileId)) {
        return;
    }

    arc->fileOpened = TRUE;

    if (func_0207c12c(arc, heap, loadSymb)) {
        data_02123cb0 = arc;
    }
}

BOOL func_0207c12c(UnkSndArc* arc, void* heap, BOOL loadSymb) {
    s32 readSize;
    if (!func_02073b64(&arc->file, 0, 0)) {
        return FALSE;
    }
    if (func_02073b58(&arc->file, arc, sizeof(UnkSndArcHeader)) != sizeof(UnkSndArcHeader)) {
        return FALSE;
    }

    if (heap != NULL) {
        arc->info = func_0207c6c8(heap, arc->header.infoSize, func_0207c5e4, arc, 0);
        if (arc->info == NULL) {
            return FALSE;
        }
        if (!func_02073b64(&arc->file, arc->header.infoOffset, 0)) {
            return FALSE;
        }
        readSize = func_02073b58(&arc->file, arc->info, arc->header.infoSize);
        if (readSize != arc->header.infoSize) {
            return FALSE;
        }

        arc->fat = func_0207c6c8(heap, arc->header.fatSize, func_0207c5ec, arc, 0);
        if (arc->fat == NULL) {
            return FALSE;
        }
        if (!func_02073b64(&arc->file, arc->header.fatOffset, 0)) {
            return FALSE;
        }
        readSize = func_02073b58(&arc->file, arc->fat, arc->header.fatSize);
        if (readSize != arc->header.fatSize) {
            return FALSE;
        }

        if (loadSymb && arc->header.symbSize != 0) {
            arc->symb = func_0207c6c8(heap, arc->header.symbSize, func_0207c5f4, arc, 0);
            if (arc->symb == NULL) {
                return FALSE;
            }
            if (!func_02073b64(&arc->file, arc->header.symbOffset, 0)) {
                return FALSE;
            }
            readSize = func_02073b58(&arc->file, arc->symb, arc->header.symbSize);
        if (readSize != arc->header.symbSize) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

UnkSndArc* func_0207c288(UnkSndArc* arc) {
    UnkSndArc* prev = data_02123cb0;
    data_02123cb0 = arc;
    return prev;
}

UnkSndArc* func_0207c298(void) {
    return data_02123cb0;
}

void* func_0207c2a4(int index) {
    UnkSndArc* arc = data_02123cb0;
    UnkSndArcTable* table = OFFSET_TO_PTR(arc->info, arc->info->seqOffset);

    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index >= table->count) {
        return NULL;
    }
    return OFFSET_TO_PTR(arc->info, table->offsets[index]);
}

void* func_0207c2f0(int index) {
    UnkSndArc* arc = data_02123cb0;
    UnkSndArcTable* table = OFFSET_TO_PTR(arc->info, arc->info->seqArcOffset);

    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index >= table->count) {
        return NULL;
    }
    return OFFSET_TO_PTR(arc->info, table->offsets[index]);
}

void* func_0207c33c(int index) {
    UnkSndArc* arc = data_02123cb0;
    UnkSndArcTable* table = OFFSET_TO_PTR(arc->info, arc->info->bankOffset);

    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index >= table->count) {
        return NULL;
    }
    return OFFSET_TO_PTR(arc->info, table->offsets[index]);
}

void* func_0207c388(int index) {
    UnkSndArc* arc = data_02123cb0;
    UnkSndArcTable* table = OFFSET_TO_PTR(arc->info, arc->info->waveArcOffset);

    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index >= table->count) {
        return NULL;
    }
    return OFFSET_TO_PTR(arc->info, table->offsets[index]);
}

void* func_0207c3d4(int index) {
    UnkSndArc* arc = data_02123cb0;
    UnkSndArcTable* table = OFFSET_TO_PTR(arc->info, arc->info->strmOffset);

    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index >= table->count) {
        return NULL;
    }
    return OFFSET_TO_PTR(arc->info, table->offsets[index]);
}

void* func_0207c420(int index) {
    UnkSndArc* arc = data_02123cb0;
    UnkSndArcTable* table = OFFSET_TO_PTR(arc->info, arc->info->playerOffset);

    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index >= table->count) {
        return NULL;
    }
    return OFFSET_TO_PTR(arc->info, table->offsets[index]);
}

void* func_0207c46c(int index) {
    UnkSndArc* arc = data_02123cb0;
    UnkSndArcTable* table = OFFSET_TO_PTR(arc->info, arc->info->strmPlayerOffset);

    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index >= table->count) {
        return NULL;
    }
    return OFFSET_TO_PTR(arc->info, table->offsets[index]);
}

u32 func_0207c4b8(u32 fileId) {
    UnkSndArcFat* fat = data_02123cb0->fat;

    if (fileId >= fat->count) {
        return 0;
    }
    return fat->entries[fileId].offset;
}

u32 func_0207c4d8(u32 fileId) {
    UnkSndArcFat* fat = data_02123cb0->fat;

    if (fileId >= fat->count) {
        return 0;
    }
    return fat->entries[fileId].size;
}

s32 func_0207c4f8(u32 fileId, void* dst, s32 size, u32 offset) {
    UnkSndArc* arc = data_02123cb0;
    UnkSndArcFat* fat = arc->fat;
    UnkSndArcFatEntry* entry;
    s32 blockSize;
    s32 total;

    if (fileId >= fat->count) {
        return -1;
    }

    entry = &fat->entries[fileId];
    blockSize = (s32)arc->unk_90;
    if (blockSize == 0) {
        blockSize = size;
    }

    for (total = 0; total < size;) {
        s32 len = size - total;
        s32 result;

        if (len > blockSize) {
            len = blockSize;
        }
        if (len > entry->size - offset) {
            len = entry->size - offset;
        }
        if (len == 0) {
            break;
        }
        if (!func_02073b64(&arc->file, entry->offset + offset, 0)) {
            return -1;
        }
        result = func_02073b58(&arc->file, dst, len);
        if (result < 0) {
            return result;
        }
        total += result;
        offset += result;
        dst = (u8*)dst + result;
    }
    return total;
}

void func_0207c59c(FS_FileIdentifier* fileId) {
    *fileId = data_02123cb0->fileId;
}

void* func_0207c5b0(u32 fileId) {
    UnkSndArcFat* fat = data_02123cb0->fat;

    if (fileId >= fat->count) {
        return NULL;
    }
    return fat->entries[fileId].mem;
}

void func_0207c5d0(u32 fileId, void* mem) {
    data_02123cb0->fat->entries[fileId].mem = mem;
}

void func_0207c5e4(void* mem, u32 size, void* data1, u32 data2) {
    ((UnkSndArc*)data1)->info = NULL;
}

void func_0207c5ec(void* mem, u32 size, void* data1, u32 data2) {
    ((UnkSndArc*)data1)->fat = NULL;
}

void func_0207c5f4(void* mem, u32 size, void* data1, u32 data2) {
    ((UnkSndArc*)data1)->symb = NULL;
}
