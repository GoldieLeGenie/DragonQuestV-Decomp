#include "fnd_types.h"

#pragma thumb on

/* Frame heap: stack-like allocator growing from both ends. */

typedef struct UnkFrmHeapState {
    u32 unk_00;                     // 0x00 tag
    void* unk_04;                   // 0x04 saved head
    void* unk_08;                   // 0x08 saved tail
    struct UnkFrmHeapState* unk_0c; // 0x0C previous state
} UnkFrmHeapState;

typedef struct UnkFrmHeapHead {
    void* unk_00;                   // 0x00 head allocation pointer
    void* unk_04;                   // 0x04 tail allocation pointer
    UnkFrmHeapState* unk_08;        // 0x08 saved states
} UnkFrmHeapHead;

typedef struct UnkFrmHeap {
    UnkFndHeapHead unk_00;          // 0x00
    UnkFrmHeapHead unk_24;          // 0x24
} UnkFrmHeap;                       // 0x30

#define SIG_FRMH 0x46524d48

#define HEAD_FROM_FRM(frm) ((UnkFndHeapHead*)((u32)(frm) - sizeof(UnkFndHeapHead)))
#define ROUND_UP(v, a)     ((((a) - 1) + (u32)(v)) & ~((a) - 1))
#define ROUND_DOWN(v, a)   ((u32)(v) & ~((a) - 1))

static inline void FillAllocMemory(UnkFndHeapHead* heap, void* address, u32 size) {
    if ((u16)(heap->unk_20 & 0xff) & 1) {
        func_02070224(0, address, size);
    }
}

UnkFrmHeap* func_0207e974(void* start, void* end, u16 option) {
    UnkFrmHeap* heap = (UnkFrmHeap*)start;
    UnkFrmHeapHead* frm = &heap->unk_24;

    func_0207e400(&heap->unk_00, SIG_FRMH, (void*)((u32)frm + sizeof(UnkFrmHeapHead)), end, option);
    frm->unk_00 = heap->unk_00.unk_18;
    frm->unk_04 = heap->unk_00.unk_1c;
    frm->unk_08 = NULL;
    return heap;
}

/* Allocates from the head pointer. */
void* func_0207e9a0(UnkFrmHeapHead* frm, u32 size, u32 alignment) {
    void* newBlock = (void*)ROUND_UP(frm->unk_00, alignment);
    void* endAddress = (void*)(size + (u32)newBlock);

    if ((u32)endAddress > (u32)frm->unk_04) {
        return NULL;
    }
    FillAllocMemory(HEAD_FROM_FRM(frm), frm->unk_00, (u32)endAddress - (u32)frm->unk_00);
    frm->unk_00 = endAddress;
    return newBlock;
}

/* Allocates from the tail pointer. */
void* func_0207e9e0(UnkFrmHeapHead* frm, u32 size, u32 alignment) {
    void* newBlock = (void*)ROUND_DOWN((u32)frm->unk_04 - size, alignment);

    if ((u32)newBlock < (u32)frm->unk_00) {
        return NULL;
    }
    FillAllocMemory(HEAD_FROM_FRM(frm), newBlock, (u32)frm->unk_04 - (u32)newBlock);
    frm->unk_04 = newBlock;
    return newBlock;
}

/* Frees everything allocated from the head. */
void func_0207ea1c(UnkFrmHeap* heap) {
    UnkFrmHeapHead* frm = &heap->unk_24;

    frm->unk_00 = heap->unk_00.unk_18;
    frm->unk_08 = NULL;
}

/* Frees everything allocated from the tail. */
void func_0207ea2c(UnkFrmHeap* heap) {
    UnkFrmHeapState* state;
    UnkFrmHeapHead* frm = &heap->unk_24;

    for (state = frm->unk_08; state != NULL; state = state->unk_0c) {
        state->unk_08 = heap->unk_00.unk_1c;
    }
    frm->unk_04 = heap->unk_00.unk_1c;
}

UnkFrmHeap* func_0207ea48(void* start, u32 size, u16 option) {
    void* end = (void*)ROUND_DOWN(size + (u32)start, 4);

    start = (void*)ROUND_UP(start, 4);
    if ((u32)start > (u32)end || (u32)end - (u32)start < sizeof(UnkFrmHeap)) {
        return NULL;
    }
    return func_0207e974(start, end, option);
}

void func_0207ea68(UnkFrmHeap* heap) {
    func_0207e45c(&heap->unk_00);
}

void* func_0207ea70(UnkFrmHeap* heap, u32 size, int alignment) {
    UnkFrmHeapHead* frm = &heap->unk_24;

    if (size == 0) {
        size = 1;
    }
    size = ROUND_UP(size, 4);
    if (alignment >= 0) {
        return func_0207e9a0(frm, size, alignment);
    } else {
        return func_0207e9e0(frm, size, -alignment);
    }
}

void func_0207ea94(UnkFrmHeap* heap, int mode) {
    if (mode & 1) {
        func_0207ea1c(heap);
    }
    if (mode & 2) {
        func_0207ea2c(heap);
    }
}

BOOL func_0207eab4(UnkFrmHeap* heap, u32 tagName) {
    void* oldHead;
    UnkFrmHeapHead* frm = &heap->unk_24;
    UnkFrmHeapState* state;

    oldHead = frm->unk_00;
    state = func_0207e9a0(frm, sizeof(UnkFrmHeapState), 4);

    if (state == NULL) {
        return FALSE;
    }
    state->unk_00 = tagName;
    state->unk_04 = oldHead;
    state->unk_08 = frm->unk_04;
    state->unk_0c = frm->unk_08;
    frm->unk_08 = state;
    return TRUE;
}

BOOL func_0207eae4(UnkFrmHeap* heap, u32 tagName) {
    UnkFrmHeapHead* frm = &heap->unk_24;
    UnkFrmHeapState* state = frm->unk_08;

    if (tagName != 0) {
        for (; state != NULL; state = state->unk_0c) {
            if (state->unk_00 == tagName) {
                break;
            }
        }
    }
    if (state == NULL) {
        return FALSE;
    }
    frm->unk_00 = state->unk_04;
    frm->unk_04 = state->unk_08;
    frm->unk_08 = state->unk_0c;
    return TRUE;
}
