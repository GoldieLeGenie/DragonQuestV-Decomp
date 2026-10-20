#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkHeapLog.hpp"
#include "main/object/DSSAObject.hpp"
#include "nitro/os.hpp"

ARM void setCompressedData(void* src)
{
    data_020fd244[0] = src;
}

ARM void uncompressData(void* dst)
{
    data_020fd244[1] = dst;
    switch (*(unsigned int*)data_020fd244[0] & 0xf0) {
    case 0x10:
        func_02070620(data_020fd244[0], dst);
        break;
    case 0x20:
        func_02070720(data_020fd244[0], dst);
        break;
    case 0x30:
        func_02070818(data_020fd244[0], dst);
        break;
    }
    DC_CleanAll();
}

ARM unsigned int getUncompressedSize(void* src)
{
    if (src == NULL) {
        src = data_020fd244[0];
    }
    return *(unsigned int*)src >> 8;
}

ARM int isCompressed(void* data)
{
    switch (*(int*)data & 0xf0) {
    case 0x10:
    case 0x20:
    case 0x30:
    case 0x80:
        return 1;
    }
    return 0;
}

ARM void* uncompressAlloc(void* data)
{
    setCompressedData(data);
    void* dst = dssAlloc(&data_020fd24c, getUncompressedSize(data), 4);
    uncompressData(dst);
    return dst;
}

ARM void initHeap(UnkHeap* heap, unsigned int size0, unsigned int size1, unsigned int size2, int mode)
{
    void* memory0;
    void* memory1;
    void* memory2 = 0;
    unsigned int size;
    memory0 = OS_AllocFromArenaLo(0, size0, 0x20);
    memory1 = OS_AllocFromArenaLo(0, size1, 0x20);
    int lo = roundUp((int)OS_GetArenaLo(0), 0x20);
    size = roundDown((unsigned int)OS_GetArenaHi(0), 0x20) - lo;
    switch (mode) {
    case 0:
        memory2 = OS_AllocFromArenaLo(0, size, 0x20);
        break;
    case 1:
        memory0 = OS_AllocFromArenaLo(2, size0, 0x20);
        memory1 = OS_AllocFromArenaLo(2, size1, 0x20);
        size = size2;
        memory2 = OS_AllocFromArenaLo(2, size2, 0x20);
        break;
    case 2:
        memory0 = OS_AllocFromArenaLo(2, size0, 0x20);
        memory1 = OS_AllocFromArenaLo(2, size1, 0x20);
        size += 0x19000;
        memory2 = OS_AllocFromArenaLo(2, size, 0x20);
        break;
    }
    heap->heap0_ = func_0207e7ac(memory0, size0, 2);
    heap->heap1_ = func_0207e7ac(memory1, size1, 2);
    heap->heap2_ = func_0207e7ac(memory2, size, 1);
    func_0207ebe4(&heap->allocator0_, (int)heap->heap0_, 0x20);
    func_0207ebe4(&heap->allocator1_, (int)heap->heap1_, 0x20);
    func_0207ebe4(&heap->allocator2_, (int)heap->heap2_, 0x20);
    heap->size0_ = size0;
    heap->size1_ = size1;
    heap->size2_ = size;
    heap->free0_ = getHeap0FreeSize(heap);
    heap->free1_ = getSystemHeapFreeSize(heap);
    heap->free2_ = getAppHeapFreeSize(heap);
    if ((unsigned int)memory0 - 0x02000000 > 0x100000) {
        debugPrintfStub("Program Memory Over!!!! : 0x%08x\n", (unsigned int)memory0 - 0x02000000);
    }
    heap->unk_54 = (int)memory0 - 0x02000000;
    data_020fd6a4.initialize();
}

ARM int roundUp(int value, int alignment)
{
    return (value + (alignment - 1)) & ~(alignment - 1);
}

ARM void freeSystemHeap(UnkHeap* heap, void* p)
{
    register void* caller = 0;
    asm { mov caller, lr }
    func_0207e8dc(heap->heap1_, p);
    data_020fd6a4.recordFree("SYS", p, caller, &heap->heap1_);
}

ARM void* allocAppHeap(UnkHeap* heap, int size, int align)
{
    register void* caller = 0;
    asm { mov caller, lr }
    register void* p = 0;
    p = func_0207e7d4(heap->heap2_, size, align);
    data_020fd6a4.recordAlloc("APP", p, size, caller, &heap->heap2_);
    return p;
}

ARM void freeAppHeap(UnkHeap* heap, void* p)
{
    register void* caller = 0;
    asm { mov caller, lr }
    func_0207e8dc(heap->heap2_, p);
    data_020fd6a4.recordFree("APP", p, caller, &heap->heap2_);
}

ARM void* dssAlloc(UnkHeap* heap, int size, int align)
{
    return allocAppHeap(heap, size, align);
}

ARM void dssFree(UnkHeap* heap, void* p)
{
    freeAppHeap(heap, p);
}

ARM unsigned int getHeap0FreeSize(UnkHeap* heap)
{
    return func_0207e908(heap->heap0_);
}

ARM unsigned int getSystemHeapFreeSize(UnkHeap* heap)
{
    return func_0207e908(heap->heap1_);
}

ARM unsigned int getAppHeapFreeSize(UnkHeap* heap)
{
    return func_0207e908(heap->heap2_);
}

ARM unsigned int getAppHeapTotalFreeSize(UnkHeap* heap)
{
    return func_0207e908(heap->heap2_);
}

ARM void** getHeap0(UnkHeap* heap)
{
    return &heap->heap0_;
}

ARM void** getSystemHeap(UnkHeap* heap)
{
    return &heap->heap1_;
}

ARM void** getAppHeap(UnkHeap* heap)
{
    return &heap->heap2_;
}

ARM void markHeapBlocks(UnkHeap* heap)
{
    data_020fd6a4.markLoggedEntries();
}

ARM void freeSystemMemory(void* p)
{
    freeSystemHeap(&data_020fd24c, p);
}

void* data_020fd244[2];
UnkHeap data_020fd24c;
