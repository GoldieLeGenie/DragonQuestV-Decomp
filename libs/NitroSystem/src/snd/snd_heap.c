// Sound heap: frame heap with sections of blocks that carry a free callback.
#include "snd_internal.h"

#pragma thumb on

typedef void (*UnkSndHeapCallback)(void* mem, u32 size, void* data1, u32 data2);

typedef struct UnkSndHeap {
    /* 0x00 */ void* frmHeap;
    /* 0x04 */ UnkList sectionList;
} UnkSndHeap; // size 0x10

typedef struct UnkSndHeapSection {
    /* 0x00 */ UnkList blockList;
    /* 0x0C */ UnkLink link;
} UnkSndHeapSection; // size 0x14

typedef struct UnkSndHeapBlock {
    /* 0x00 */ UnkLink link;
    /* 0x08 */ u32 size;
    /* 0x0C */ UnkSndHeapCallback callback;
    /* 0x10 */ void* data1;
    /* 0x14 */ u32 data2;
    /* 0x18 */ u8 unk_18[8];
    /* 0x20 */ u8 buffer[0];
} UnkSndHeapBlock; // size 0x20

void func_0207c658(UnkSndHeap* heap);
void func_0207c7d4(UnkList* list);
BOOL func_0207c7e0(UnkSndHeap* heap, void* frmHeap);
BOOL func_0207c804(UnkSndHeap* heap);
void func_0207c82c(void);

UnkSndHeap* func_0207c5fc(void* startAddress, u32 size) {
    u32 endAddress = (u32)startAddress + size;
    UnkSndHeap* heap = (UnkSndHeap*)(((u32)startAddress + 3) & ~3);
    void* frmHeap;

    if ((u32)heap > endAddress) {
        return NULL;
    }
    if (endAddress - (u32)heap < sizeof(UnkSndHeap)) {
        return NULL;
    }

    frmHeap = func_0207ea48(heap + 1, endAddress - (u32)heap - sizeof(UnkSndHeap), 0);
    if (frmHeap == NULL) {
        return NULL;
    }

    if (!func_0207c7e0(heap, frmHeap)) {
        func_0207ea68(frmHeap);
        return NULL;
    }

    return heap;
}

void func_0207c648(UnkSndHeap* heap) {
    func_0207c658(heap);
    func_0207ea68(heap->frmHeap);
}

void func_0207c658(UnkSndHeap* heap) {
    UnkSndHeapSection* section;
    BOOL doCallback = FALSE;
    UnkSndHeapBlock* block;

    while ((section = func_0207e394(&heap->sectionList, NULL)) != NULL) {
        for (block = func_0207e394(&section->blockList, NULL); block != NULL; block = func_0207e394(&section->blockList, block)) {
            if (block->callback != NULL) {
                block->callback(block->buffer, block->size, block->data1, block->data2);
                doCallback = TRUE;
            }
        }
        func_0207e348(&heap->sectionList, section);
    }

    func_0207ea94(heap->frmHeap, 3);

    if (doCallback) {
        func_0207c82c();
    }

    func_0207c804(heap);
}

void* func_0207c6c8(UnkSndHeap* heap, u32 size, UnkSndHeapCallback callback, void* data1, u32 data2) {
    UnkSndHeapSection* section;
    UnkSndHeapBlock* block = func_0207ea70(heap->frmHeap, ((size + 0x1F) & ~0x1F) + sizeof(UnkSndHeapBlock), 32);

    if (block == NULL) {
        return NULL;
    }

    section = func_0207e394(&heap->sectionList, NULL);
    block->size = size;
    block->callback = callback;
    block->data1 = data1;
    block->data2 = data2;
    func_0207e2b8(&section->blockList, block);
    return block->buffer;
}

s32 func_0207c70c(UnkSndHeap* heap) {
    if (!func_0207eab4(heap->frmHeap, heap->sectionList.numObjects)) {
        return -1;
    }
    if (!func_0207c804(heap)) {
        func_0207eae4(heap->frmHeap, 0);
        return -1;
    }
    return heap->sectionList.numObjects - 1;
}

void func_0207c740(UnkSndHeap* heap, int level) {
    UnkSndHeapSection* section;
    UnkSndHeapBlock* block = NULL;
    BOOL doCallback = FALSE;

    if (level == 0) {
        func_0207c658(heap);
        return;
    }

    while (level < heap->sectionList.numObjects) {
        section = func_0207e394(&heap->sectionList, NULL);

        for (block = func_0207e394(&section->blockList, block); block != NULL; block = func_0207e394(&section->blockList, block)) {
            if (block->callback != NULL) {
                block->callback(block->buffer, block->size, block->data1, block->data2);
                doCallback = TRUE;
            }
        }
        func_0207e348(&heap->sectionList, section);
    }

    func_0207eae4(heap->frmHeap, level);

    if (doCallback) {
        func_0207c82c();
    }

    func_0207eab4(heap->frmHeap, heap->sectionList.numObjects);
    func_0207c804(heap);
}

void func_0207c7d4(UnkList* list) {
    func_0207e290(list, 0);
}

BOOL func_0207c7e0(UnkSndHeap* heap, void* frmHeap) {
    func_0207e290(&heap->sectionList, 0xC);
    heap->frmHeap = frmHeap;

    if (!func_0207c804(heap)) {
        return FALSE;
    }
    return TRUE;
}

BOOL func_0207c804(UnkSndHeap* heap) {
    UnkSndHeapSection* section = func_0207ea70(heap->frmHeap, sizeof(UnkSndHeapSection), 4);

    if (section == NULL) {
        return FALSE;
    }

    func_0207c7d4(&section->blockList);
    func_0207e2b8(&heap->sectionList, section);
    return TRUE;
}

void func_0207c82c(void) {
    u32 tag = func_02078010();
    func_02077eb8(1);
    func_02077fcc(tag);
}
