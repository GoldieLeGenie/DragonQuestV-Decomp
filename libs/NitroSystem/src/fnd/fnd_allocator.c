#include "fnd_types.h"

#pragma thumb on

/* Generic allocator interface over the expanded / frame / unit / OS heaps. */

struct UnkFndAllocator;

typedef void* (*UnkFndAllocFunc)(struct UnkFndAllocator* allocator, u32 size);
typedef void (*UnkFndFreeFunc)(struct UnkFndAllocator* allocator, void* memBlock);

typedef struct UnkFndAllocatorFunc {
    UnkFndAllocFunc unk_00;         // 0x00 alloc
    UnkFndFreeFunc unk_04;          // 0x04 free
} UnkFndAllocatorFunc;

typedef struct UnkFndAllocator {
    const UnkFndAllocatorFunc* unk_00; // 0x00 function table
    void* unk_04;                   // 0x04 heap
    u32 unk_08;                     // 0x08 heap parameter 1 (alignment / OS arena id)
    u32 unk_0c;                     // 0x0C heap parameter 2
} UnkFndAllocator;

extern void* func_0207e7d4(void* heap, u32 size, int alignment);
extern void func_0207e8dc(void* heap, void* memBlock);
extern void* func_0207ea70(void* heap, u32 size, int alignment);
extern void* func_0207eb24(void* heap);
extern void func_0207eb54(void* heap, void* memBlock);
extern void* OS_AllocFromHeap(int arena, int heap, u32 size);
extern void OS_FreeFromHeap(int arena, int heap, void* ptr);

typedef struct UnkUnitHeapView {
    UnkFndHeapHead unk_00;          // 0x00
    void* unk_24;                   // 0x24 free list
    u32 unk_28;                     // 0x28 block size
} UnkUnitHeapView;

void* func_0207eb5c(UnkFndAllocator* allocator, u32 size) {
    return func_0207e7d4(allocator->unk_04, size, (int)allocator->unk_08);
}

void func_0207eb6c(UnkFndAllocator* allocator, void* memBlock) {
    func_0207e8dc(allocator->unk_04, memBlock);
}

void* func_0207eb78(UnkFndAllocator* allocator, u32 size) {
    return func_0207ea70(allocator->unk_04, size, (int)allocator->unk_08);
}

void func_0207eb88(UnkFndAllocator* allocator, void* memBlock) {
}

void* func_0207eb8c(UnkFndAllocator* allocator, u32 size) {
    UnkUnitHeapView* heap = (UnkUnitHeapView*)allocator->unk_04;

    if (size > heap->unk_28) {
        return NULL;
    }
    return func_0207eb24(heap);
}

void func_0207eba0(UnkFndAllocator* allocator, void* memBlock) {
    func_0207eb54(allocator->unk_04, memBlock);
}

void* func_0207ebac(UnkFndAllocator* allocator, u32 size) {
    return OS_AllocFromHeap((int)allocator->unk_08, (int)allocator->unk_04, size);
}

void func_0207ebbc(UnkFndAllocator* allocator, void* memBlock) {
    OS_FreeFromHeap((int)allocator->unk_08, (int)allocator->unk_04, memBlock);
}

/* allocator function tables: expanded heap, frame heap, unit heap, OS heap */
static const UnkFndAllocatorFunc data_0208eb48 = {func_0207eb5c, func_0207eb6c};
static const UnkFndAllocatorFunc data_0208eb40 = {func_0207eb78, func_0207eb88};
static const UnkFndAllocatorFunc data_0208eb38 = {func_0207eb8c, func_0207eba0};
static const UnkFndAllocatorFunc data_0208eb50 = {func_0207ebac, func_0207ebbc};

void* func_0207ebcc(UnkFndAllocator* allocator, u32 size) {
    return allocator->unk_00->unk_00(allocator, size);
}

void func_0207ebd8(UnkFndAllocator* allocator, void* memBlock) {
    allocator->unk_00->unk_04(allocator, memBlock);
}

void func_0207ebe4(UnkFndAllocator* allocator, void* heap, int alignment) {
    allocator->unk_00 = &data_0208eb48;
    allocator->unk_04 = heap;
    allocator->unk_08 = (u32)alignment;
    allocator->unk_0c = 0;
}

/* The frame heap, unit heap and OS heap initializers are not linked in the ROM (no caller);
   their function tables stay in this unit's .rodata. */
void unkfunc_unused_18(UnkFndAllocator* allocator, void* heap, int alignment) {
    allocator->unk_00 = &data_0208eb40;
    allocator->unk_04 = heap;
    allocator->unk_08 = (u32)alignment;
    allocator->unk_0c = 0;
}

void unkfunc_unused_17(UnkFndAllocator* allocator, void* heap) {
    allocator->unk_00 = &data_0208eb38;
    allocator->unk_04 = heap;
    allocator->unk_08 = 0;
    allocator->unk_0c = 0;
}

void unkfunc_unused_19(UnkFndAllocator* allocator, int arena, int heap) {
    allocator->unk_00 = &data_0208eb50;
    allocator->unk_04 = (void*)heap;
    allocator->unk_08 = (u32)arena;
    allocator->unk_0c = 0;
}
