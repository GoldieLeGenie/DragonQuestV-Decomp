#include "fnd_types.h"

#pragma thumb on

BOOL       data_02124b60; // root heap list initialized
UnkFndList data_02124b64; // root heap list

/* Recursively finds the heap (in list or its children) whose memory range contains memBlock. */
UnkFndHeapHead* func_0207e3a4(UnkFndList* list, const void* memBlock) {
    UnkFndHeapHead* heap = NULL;

    while ((heap = func_0207e384(list, heap)) != NULL) {
        if (heap->unk_18 <= memBlock && memBlock < heap->unk_1c) {
            UnkFndHeapHead* child = func_0207e3a4(&heap->unk_0c, memBlock);

            if (child != NULL) {
                return child;
            }
            return heap;
        }
    }
    return NULL;
}

/* Returns the list a heap at this address must be registered in. */
UnkFndList* func_0207e3e4(void* heap) {
    UnkFndList* list = &data_02124b64;
    UnkFndHeapHead* containHeap = func_0207e3a4(list, heap);

    if (containHeap != NULL) {
        list = &containHeap->unk_0c;
    }
    return list;
}

void func_0207e400(UnkFndHeapHead* heap, u32 signature, void* start, void* end, u16 option) {
    heap->unk_00 = signature;
    heap->unk_18 = start;
    heap->unk_1c = end;
    heap->unk_20 = 0;
    heap->unk_20 &= ~0xff;
    heap->unk_20 |= option & 0xff;
    func_0207e290(&heap->unk_0c, 4);
    if (!data_02124b60) {
        func_0207e290(&data_02124b64, 4);
        data_02124b60 = TRUE;
    }
    func_0207e2b8(func_0207e3e4(heap), heap);
}

void func_0207e45c(UnkFndHeapHead* heap) {
    func_0207e348(func_0207e3e4(heap), heap);
}
