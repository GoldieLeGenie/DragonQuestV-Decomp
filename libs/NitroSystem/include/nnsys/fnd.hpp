#pragma once

struct NNSFndAllocator {
    void* pFunc;                                // 0x00
    void* pHeap;                                // 0x04
    unsigned int heapParam1;                    // 0x08
    unsigned int heapParam2;                    // 0x0C
};

extern "C" {
    void  func_0207ebe4(NNSFndAllocator* allocator, int heap, int alignment);       // NNS_FndInitAllocatorForExpHeap
    void* func_0207ebcc(NNSFndAllocator* allocator, unsigned int size);             // NNS_FndAllocFromAllocator
    void  func_0207ebd8(NNSFndAllocator* allocator, void* memBlock);                // NNS_FndFreeToAllocator
    void* func_0207e7ac(void* memory, unsigned int size, int option);               // NNS_FndCreateExpHeapEx
    void  func_0207e7cc(void* heap);                                                 // NNS_FndDestroyExpHeap
    void  func_0207e968(void* heap, unsigned short groupID);                        // NNS_FndSetGroupIDForExpHeap
    void* func_0207e7d4(void* heap, int size, int align);                           // NNS_FndAllocFromExpHeapEx
    unsigned int func_0207e7f4(void* heap, void* memBlock, unsigned int size);      // NNS_FndResizeForMBlockExpHeap
    void  func_0207e8dc(void* heap, void* memBlock);                                // NNS_FndFreeToExpHeap
    unsigned int func_0207e908(void* heap);                                         // NNS_FndGetTotalFreeSizeForExpHeap
    unsigned int func_0207e920(void* heap, int alignment);                          // NNS_FndGetAllocatableSizeForExpHeapEx
}
