#include "gfd_lnkvram.h"

#pragma thumb on

typedef struct {
    u32 start;
    u32 end;
} UnkLnkVramRegion;

static inline UnkLnkVramBlock* GetNewBlock_(UnkLnkVramBlock** ppBlockPool)
{
    UnkLnkVramBlock* pBlk = *ppBlockPool;
    if (pBlk != NULL) {
        *ppBlockPool = pBlk->pNext;
    }
    return pBlk;
}

static inline void InitBlock_(UnkLnkVramBlock* pBlk, u32 addr, u32 szByte)
{
    pBlk->addr = addr;
    pBlk->szByte = szByte;
    pBlk->pPrev = NULL;
    pBlk->pNext = NULL;
}

static inline void InitBlockFromRegion_(UnkLnkVramBlock* pBlk, const UnkLnkVramRegion* pRegion)
{
    pBlk->addr = pRegion->start;
    pBlk->szByte = pRegion->end - pRegion->start;
    pBlk->pPrev = NULL;
    pBlk->pNext = NULL;
}

static inline void InsertBlock_(UnkLnkVramBlock** ppList, UnkLnkVramBlock* pBlk)
{
    if (*ppList != NULL) {
        (*ppList)->pPrev = pBlk;
    }
    pBlk->pNext = *ppList;
    pBlk->pPrev = NULL;
    *ppList = pBlk;
}

static inline void RemoveBlock_(UnkLnkVramBlock** ppList, UnkLnkVramBlock* pBlk)
{
    UnkLnkVramBlock* pPrev = pBlk->pPrev;
    UnkLnkVramBlock* pNext = pBlk->pNext;

    if (pPrev != NULL) {
        pPrev->pNext = pNext;
    } else {
        *ppList = pNext;
    }
    if (pNext != NULL) {
        pNext->pPrev = pPrev;
    }
}

/* merges the free blocks adjacent to a region into it, returns whether any block was merged */
static BOOL func_02086820(UnkLnkVramBlock** ppList, UnkLnkVramBlock** ppBlockPool, UnkLnkVramRegion* pRegion)
{
    UnkLnkVramBlock* pBlk = *ppList;
    UnkLnkVramBlock* pNext;
    BOOL bMerged = FALSE;

    while (pBlk != NULL) {
        pNext = pBlk->pNext;
        if (pBlk->addr == pRegion->end) {
            pRegion->end = pBlk->addr + pBlk->szByte;
            RemoveBlock_(ppList, pBlk);
            InsertBlock_(ppBlockPool, pBlk);
            bMerged |= TRUE;
        }
        if (pBlk->addr + pBlk->szByte == pRegion->start) {
            pRegion->start = pBlk->addr;
            RemoveBlock_(ppList, pBlk);
            InsertBlock_(ppBlockPool, pBlk);
            bMerged |= TRUE;
        }
        pBlk = pNext;
    }
    return bMerged;
}

void func_020868b0(UnkLnkVramMan* pMgr)
{
    pMgr->pFreeList = NULL;
}

/* links an array of blocks into a pool list */
UnkLnkVramBlock* func_020868b8(UnkLnkVramBlock* pArray, u32 num)
{
    u32 i;

    for (i = 0; i < num - 1; i++) {
        pArray[i].pNext = &pArray[i + 1];
        pArray[i + 1].pPrev = &pArray[i];
    }
    pArray[0].pPrev = NULL;
    (pArray + num - 1)->pNext = NULL;
    return pArray;
}

/* adds a free region to the manager */
BOOL func_020868e4(UnkLnkVramMan* pMgr, UnkLnkVramBlock** ppBlockPool, u32 baseAddr, u32 szByte)
{
    UnkLnkVramBlock* pBlk = GetNewBlock_(ppBlockPool);

    if (pBlk != NULL) {
        InitBlock_(pBlk, baseAddr, szByte);
        InsertBlock_(&pMgr->pFreeList, pBlk);
        return TRUE;
    }
    return FALSE;
}

BOOL func_0208691c(UnkLnkVramMan* pMgr, UnkLnkVramBlock** ppBlockPool, u32* pRetAddr, u32 szByte)
{
    return func_0208692c(pMgr, ppBlockPool, pRetAddr, szByte, 0);
}

/* allocates szByte from the free list (first fit) */
BOOL func_0208692c(UnkLnkVramMan* pMgr, UnkLnkVramBlock** ppBlockPool, u32* pRetAddr, u32 szByte, u32 alignment)
{
    u32 alignedAddr;
    u32 needSize;
    u32 alignOfs;
    UnkLnkVramBlock* pFound = NULL;
    UnkLnkVramBlock* pBlk = pMgr->pFreeList;

    while (pBlk != NULL) {
        if (alignment > 1) {
            alignedAddr = (pBlk->addr + (alignment - 1)) & ~(alignment - 1);
            alignOfs = alignedAddr - pBlk->addr;
            needSize = szByte + alignOfs;
        } else {
            alignedAddr = pBlk->addr;
            alignOfs = 0;
            needSize = szByte;
        }
        if (pBlk->szByte >= needSize) {
            pFound = pBlk;
            break;
        }
        pBlk = pBlk->pNext;
    }

    if (pFound != NULL) {
        if (alignOfs != 0) {
            UnkLnkVramBlock* pNew = GetNewBlock_(ppBlockPool);
            if (pNew == NULL) {
                goto fail;
            }
            InitBlock_(pNew, pFound->addr, alignOfs);
            InsertBlock_(&pMgr->pFreeList, pNew);
        }
        pFound->szByte -= needSize;
        pFound->addr += needSize;
        if (pFound->szByte == 0) {
            RemoveBlock_(&pMgr->pFreeList, pFound);
            InsertBlock_(ppBlockPool, pFound);
        }
        *pRetAddr = alignedAddr;
        return TRUE;
    }
fail:
    *pRetAddr = 0;
    return FALSE;
}

/* merges all the adjacent free blocks of a list */
void func_02086a08(UnkLnkVramBlock** ppList, UnkLnkVramBlock** ppBlockPool)
{
    UnkLnkVramBlock* pBlk = *ppList;

    while (pBlk != NULL) {
        UnkLnkVramRegion region;

        region.start = pBlk->addr;
        region.end = pBlk->addr + pBlk->szByte;
        if (func_02086820(ppList, ppBlockPool, &region)) {
            pBlk->addr = region.start;
            pBlk->szByte = region.end - region.start;
            pBlk = *ppList;
        } else {
            pBlk = pBlk->pNext;
        }
    }
}

/* returns a region to the free list, merging it with adjacent free blocks */
BOOL func_02086a4c(UnkLnkVramMan* pMgr, UnkLnkVramBlock** ppBlockPool, u32 baseAddr, u32 szByte)
{
    UnkLnkVramRegion region;
    UnkLnkVramBlock* pBlk;

    region.start = baseAddr;
    region.end = baseAddr + szByte;
    func_02086820(&pMgr->pFreeList, ppBlockPool, &region);

    pBlk = GetNewBlock_(ppBlockPool);
    if (pBlk == NULL) {
        return FALSE;
    }
    InitBlockFromRegion_(pBlk, &region);
    InsertBlock_(&pMgr->pFreeList, pBlk);
    return TRUE;
}
