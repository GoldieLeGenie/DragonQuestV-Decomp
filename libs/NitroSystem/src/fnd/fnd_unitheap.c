#include "fnd_types.h"

#pragma thumb on

/* Unit heap: fixed-size blocks kept in a singly linked free list. */

typedef struct UnkUnitMBlock {
    struct UnkUnitMBlock* unk_00;   // 0x00 next free block
} UnkUnitMBlock;

typedef struct UnkUnitMBlockList {
    UnkUnitMBlock* unk_00;          // 0x00 first free block
} UnkUnitMBlockList;

typedef struct UnkUnitHeapHead {
    UnkUnitMBlockList unk_00;       // 0x00 free list
    u32 unk_04;                     // 0x04 block size
} UnkUnitHeapHead;

typedef struct UnkUnitHeap {
    UnkFndHeapHead unk_00;          // 0x00
    UnkUnitHeapHead unk_24;         // 0x24
} UnkUnitHeap;

static inline void FillAllocMemory(UnkFndHeapHead* heap, void* address, u32 size) {
    if ((u16)(heap->unk_20 & 0xff) & 1) {
        func_02070224(0, address, size);
    }
}

/* Pops the first free block. */
UnkUnitMBlock* func_0207eb14(UnkUnitMBlockList* list) {
    UnkUnitMBlock* block = list->unk_00;

    if (block != NULL) {
        list->unk_00 = block->unk_00;
    }
    return block;
}

void* func_0207eb24(UnkUnitHeap* heap) {
    UnkUnitMBlock* block;
    UnkUnitHeapHead* unit = &heap->unk_24;

    block = func_0207eb14(&unit->unk_00);

    if (block != NULL) {
        FillAllocMemory(&heap->unk_00, block, unit->unk_04);
    }
    return block;
}

void func_0207eb54(UnkUnitHeap* heap, void* memBlock) {
    UnkUnitMBlock* block = (UnkUnitMBlock*)memBlock;

    block->unk_00 = heap->unk_24.unk_00.unk_00;
    heap->unk_24.unk_00.unk_00 = block;
}
