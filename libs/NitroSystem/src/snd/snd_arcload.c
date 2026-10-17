// Sound archive loader: loads sequences, banks and wave archives into a sound heap.
#include "snd_internal.h"
#include <nitro/snd/wavearc.h>

#pragma thumb on

typedef void (*UnkSndHeapCallback)(void* mem, u32 size, void* data1, u32 data2);

typedef struct UnkSndSeqInfo {
    /* 0x00 */ u32 fileId;
    /* 0x04 */ u16 bankNo;
} UnkSndSeqInfo;

typedef struct UnkSndSeqArcInfo {
    /* 0x00 */ u32 fileId;
} UnkSndSeqArcInfo;

typedef struct UnkSndBankInfo {
    /* 0x00 */ u32 fileId;
    /* 0x04 */ u16 waveArcNo[4];
} UnkSndBankInfo;

typedef struct UnkSndWaveArcInfo {
    /* 0x00 */ u32 fileId : 24;
    /* 0x00 */ u32 flags : 8;
} UnkSndWaveArcInfo;

typedef struct UnkSndInstPos {
    /* 0x00 */ u32 prgNo;
    /* 0x04 */ u32 index;
} UnkSndInstPos;

typedef struct UnkSndInstData {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u16 waveNo;
    /* 0x04 */ u16 waveArcNo;
    /* 0x06 */ u8 unk_06[6];
} UnkSndInstData;


void* func_0207c288(void* arc);
void* func_0207c298(void);
void* func_0207c2a4(int index);
void* func_0207c2f0(int index);
void* func_0207c33c(int index);
void* func_0207c388(int index);
u32   func_0207c4d8(u32 fileId);
s32   func_0207c4f8(u32 fileId, void* dst, u32 size, u32 offset);
void* func_0207c5b0(u32 fileId);
void  func_0207c5d0(u32 fileId, void* mem);
void* func_0207c6c8(void* heap, u32 size, UnkSndHeapCallback callback, void* data1, u32 data2);
UnkSndInstPos func_0207840c(void);
BOOL  func_0207841c(void* bank, UnkSndInstData* inst, UnkSndInstPos* pos);

int   func_0207c894(int seqNo, u32 flags, void* heap, BOOL addToArc, void** pData);
int   func_0207c8e4(int seqArcNo, u32 flags, void* heap, BOOL addToArc, void** pData);
int   func_0207c920(int bankNo, u32 flags, void* heap, BOOL addToArc, void** pData);
int   func_0207c9e8(int waveArcNo, u32 flags, void* heap, BOOL addToArc, void** pData);
void* func_0207ca44(u32 fileId, UnkSndHeapCallback callback, void* data1, u32 data2, void* heap);
void* func_0207caa8(u32 fileId, void* heap, BOOL addToArc);
void* func_0207caec(u32 fileId, void* heap, BOOL addToArc);
void* func_0207cb30(u32 fileId, void* heap, BOOL addToArc);
void* func_0207cb74(u32 fileId, void* heap, BOOL addToArc);
void* func_0207cbb8(u32 fileId, void* heap, BOOL addToArc);
void  func_0207cc80(void* mem, void* arc, u32 fileId);
void  func_0207ccbc(void* mem, u32 size, void* data1, u32 data2);
void  func_0207ccd4(void* mem, u32 size, void* data1, u32 data2);
void  func_0207ccf4(void* mem, u32 size, void* data1, u32 data2);
void  func_0207cd14(void* mem, u32 size, void* data1, u32 data2);
void  func_0207cd28(void* mem, u32 size, void* data1, u32 data2);
BOOL  func_0207cd54(UnkSndWaveArc* waveArc, u32 index, u32 fileId, void* heap);
BOOL  func_0207cde4(UnkSndWaveArc* waveArc, void* bank, int index, u32 fileId, void* heap);

BOOL func_0207c844(int seqArcNo, void* heap) {
    return func_0207c8e4(seqArcNo, 0xFF, heap, TRUE, NULL) == 0;
}

BOOL func_0207c860(int bankNo, void* heap) {
    return func_0207c920(bankNo, 0xFF, heap, TRUE, NULL) == 0;
}

BOOL func_0207c87c(int seqNo, u32 flags, void* heap) {
    return func_0207c894(seqNo, flags, heap, TRUE, NULL) == 0;
}

int func_0207c894(int seqNo, u32 flags, void* heap, BOOL addToArc, void** pData) {
    UnkSndSeqInfo* info = func_0207c2a4(seqNo);
    void* data;
    int result;

    if (info == NULL) {
        return 2;
    }

    result = func_0207c920(info->bankNo, flags, heap, addToArc, NULL);
    if (result != 0) {
        return result;
    }

    if (flags & 1) {
        data = func_0207caa8(info->fileId, heap, addToArc);
        if (data == NULL) {
            return 6;
        }
    } else {
        data = func_0207c5b0(info->fileId);
    }

    if (pData != NULL) {
        *pData = data;
    }
    return 0;
}

int func_0207c8e4(int seqArcNo, u32 flags, void* heap, BOOL addToArc, void** pData) {
    UnkSndSeqArcInfo* info = func_0207c2f0(seqArcNo);
    void* data;

    if (info == NULL) {
        return 3;
    }

    if (flags & 8) {
        data = func_0207caec(info->fileId, heap, addToArc);
        if (data == NULL) {
            return 7;
        }
    } else {
        data = func_0207c5b0(info->fileId);
    }

    if (pData != NULL) {
        *pData = data;
    }
    return 0;
}

int func_0207c920(int bankNo, u32 flags, void* heap, BOOL addToArc, void** pData) {
    UnkSndBankInfo* info = func_0207c33c(bankNo);
    void* bank;
    int i;

    if (info == NULL) {
        return 4;
    }

    if (flags & 2) {
        bank = func_0207cb30(info->fileId, heap, addToArc);
        if (bank == NULL) {
            return 8;
        }
    } else {
        bank = func_0207c5b0(info->fileId);
    }

    for (i = 0; i < 4; i++) {
        UnkSndWaveArcInfo* waveArcInfo;
        void* waveArc;
        int result;

        if (info->waveArcNo[i] == 0xFFFF) {
            continue;
        }

        waveArcInfo = func_0207c388(info->waveArcNo[i]);
        if (waveArcInfo == NULL) {
            return 5;
        }

        result = func_0207c9e8(info->waveArcNo[i], flags, heap, addToArc, &waveArc);
        if (result != 0) {
            return result;
        }

        if ((waveArcInfo->flags & 1) && (flags & 4)) {
            if (!func_0207cde4(waveArc, bank, i, waveArcInfo->fileId, heap)) {
                return 9;
            }
        }

        if (bank != NULL && waveArc != NULL) {
            func_0207830c(bank, i, waveArc);
        }
    }

    if (pData != NULL) {
        *pData = bank;
    }
    return 0;
}

int func_0207c9e8(int waveArcNo, u32 flags, void* heap, BOOL addToArc, void** pData) {
    UnkSndWaveArcInfo* info = func_0207c388(waveArcNo);
    void* data;

    if (info == NULL) {
        return 5;
    }

    if (flags & 4) {
        if (info->flags & 1) {
            data = func_0207cbb8(info->fileId, heap, addToArc);
        } else {
            data = func_0207cb74(info->fileId, heap, addToArc);
        }
        if (data == NULL) {
            return 9;
        }
    } else {
        data = func_0207c5b0(info->fileId);
    }

    if (pData != NULL) {
        *pData = data;
    }
    return 0;
}

void* func_0207ca44(u32 fileId, UnkSndHeapCallback callback, void* data1, u32 data2, void* heap) {
    u32 size = func_0207c4d8(fileId);
    void* mem;

    if (size == 0) {
        return NULL;
    }
    if (heap == NULL) {
        return NULL;
    }

    mem = func_0207c6c8(heap, size + 0x20, callback, data1, data2);
    if (mem == NULL) {
        return NULL;
    }

    if (size != func_0207c4f8(fileId, mem, size, 0)) {
        return NULL;
    }

    DC_CleanRange(mem, size);
    return mem;
}

void* func_0207caa8(u32 fileId, void* heap, BOOL addToArc) {
    void* data = func_0207c5b0(fileId);

    if (data == NULL) {
        data = func_0207ca44(fileId, func_0207ccbc, addToArc ? func_0207c298() : NULL, fileId, heap);
        if (addToArc && data != NULL) {
            func_0207c5d0(fileId, data);
        }
    }
    return data;
}

void* func_0207caec(u32 fileId, void* heap, BOOL addToArc) {
    void* data = func_0207c5b0(fileId);

    if (data == NULL) {
        data = func_0207ca44(fileId, func_0207ccbc, addToArc ? func_0207c298() : NULL, fileId, heap);
        if (addToArc && data != NULL) {
            func_0207c5d0(fileId, data);
        }
    }
    return data;
}

void* func_0207cb30(u32 fileId, void* heap, BOOL addToArc) {
    void* data = func_0207c5b0(fileId);

    if (data == NULL) {
        data = func_0207ca44(fileId, func_0207ccd4, addToArc ? func_0207c298() : NULL, fileId, heap);
        if (addToArc && data != NULL) {
            func_0207c5d0(fileId, data);
        }
    }
    return data;
}

void* func_0207cb74(u32 fileId, void* heap, BOOL addToArc) {
    void* data = func_0207c5b0(fileId);

    if (data == NULL) {
        data = func_0207ca44(fileId, func_0207ccf4, addToArc ? func_0207c298() : NULL, fileId, heap);
        if (addToArc && data != NULL) {
            func_0207c5d0(fileId, data);
        }
    }
    return data;
}

void* func_0207cbb8(u32 fileId, void* heap, BOOL addToArc) {
    static UnkSndWaveArc data_02123cb4;
    u32 size;
    UnkSndWaveArc* waveArc = func_0207c5b0(fileId);
    u32 tableSize;
    s32 readSize;

    if (waveArc == NULL) {

        if (func_0207c4f8(fileId, &data_02123cb4, 0x3C, 0) != 0x3C) {
            return NULL;
        }

        tableSize = data_02123cb4.waveCount * 4;
        size = tableSize * 2 + 0x3C;

        if (heap == NULL) {
            return NULL;
        }

        waveArc = func_0207c6c8(heap, size + 0x20, func_0207cd14, addToArc ? func_0207c298() : NULL, fileId);
        if (waveArc == NULL) {
            return NULL;
        }

        readSize = func_0207c4f8(fileId, waveArc, tableSize + 0x3C, 0);
        if (readSize != tableSize + 0x3C) {
            return NULL;
        }

        MI_CpuCopyU8(waveArc->waveOffset, &waveArc->waveOffset[waveArc->waveCount], tableSize);
        MI_CpuSet(waveArc->waveOffset, 0, tableSize);
        DC_CleanRange(waveArc, size);

        if (addToArc) {
            func_0207c5d0(fileId, waveArc);
        }
    }
    return waveArc;
}

void func_0207cc80(void* mem, void* arc, u32 fileId) {
    void* prev;
    int irq;

    if (arc == NULL) {
        return;
    }

    irq = OS_DisableIRQ();
    prev = func_0207c288(arc);
    if (mem == func_0207c5b0(fileId)) {
        func_0207c5d0(fileId, NULL);
    }
    func_0207c288(prev);
    OS_RestoreIRQ(irq);
}

void func_0207ccbc(void* mem, u32 size, void* data1, u32 data2) {
    func_0207cc80(mem, data1, data2);
    func_02077c14(mem, (u8*)mem + size);
}

void func_0207ccd4(void* mem, u32 size, void* data1, u32 data2) {
    func_0207cc80(mem, data1, data2);
    func_02077c2c(mem, (u8*)mem + size);
    func_0207838c(mem);
}

void func_0207ccf4(void* mem, u32 size, void* data1, u32 data2) {
    func_0207cc80(mem, data1, data2);
    func_02077c44(mem, (u8*)mem + size);
    func_020783e0(mem);
}

void func_0207cd14(void* mem, u32 size, void* data1, u32 data2) {
    func_0207cc80(mem, data1, data2);
    func_020783e0(mem);
}

void func_0207cd28(void* mem, u32 size, void* data1, u32 data2) {
    if (mem == func_02078538(data1, data2)) {
        func_02078518(data1, data2, NULL);
    }
    func_02077c44(mem, (u8*)mem + size);
}

BOOL func_0207cd54(UnkSndWaveArc* waveArc, u32 index, u32 fileId, void* heap) {
    u32 size;
    u32 offset;
    u32 end;

    if (func_02078538(waveArc, index) != NULL) {
        return TRUE;
    }

    {
        u32 count = func_02078514(waveArc);
        u32 i = waveArc->waveCount + index;
        offset = waveArc->waveOffset[i];
        end = index < count - 1 ? *(waveArc->waveOffset + i + 1) : waveArc->fileSize;
    }
    size = end - offset;

    if (heap == NULL) {
        return FALSE;
    }

    heap = func_0207c6c8(heap, size + 0x20, func_0207cd28, waveArc, index);
    if (heap == NULL) {
        return FALSE;
    }

    if (size != func_0207c4f8(fileId, heap, size, offset)) {
        return FALSE;
    }

    DC_CleanRange(heap, size);
    func_02078518(waveArc, index, heap);
    return TRUE;
}

BOOL func_0207cde4(UnkSndWaveArc* waveArc, void* bank, int index, u32 fileId, void* heap) {
    UnkSndInstPos pos = func_0207840c();
    UnkSndInstData inst;

    if (bank == NULL) {
        return FALSE;
    }

    while (func_0207841c(bank, &inst, &pos)) {
        if (inst.type == 1 && index == inst.waveArcNo) {
            if (!func_0207cd54(waveArc, inst.waveNo, fileId, heap)) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
