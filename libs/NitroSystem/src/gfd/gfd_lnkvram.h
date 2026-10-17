#ifndef GFD_LNKVRAM_H
#define GFD_LNKVRAM_H

#include "../nns_internal.h"

typedef struct UnkLnkVramBlock {
    u32 addr;                       /* 0x00 */
    u32 szByte;                     /* 0x04 */
    struct UnkLnkVramBlock* pPrev;  /* 0x08 */
    struct UnkLnkVramBlock* pNext;  /* 0x0C */
} UnkLnkVramBlock;

typedef struct {
    UnkLnkVramBlock* pFreeList;     /* 0x00 */
} UnkLnkVramMan;

void func_020868b0(UnkLnkVramMan* pMgr);
UnkLnkVramBlock* func_020868b8(UnkLnkVramBlock* pArray, u32 num);
BOOL func_020868e4(UnkLnkVramMan* pMgr, UnkLnkVramBlock** ppBlockPool, u32 baseAddr, u32 szByte);
BOOL func_0208691c(UnkLnkVramMan* pMgr, UnkLnkVramBlock** ppBlockPool, u32* pRetAddr, u32 szByte);
BOOL func_0208692c(UnkLnkVramMan* pMgr, UnkLnkVramBlock** ppBlockPool, u32* pRetAddr, u32 szByte, u32 alignment);
void func_02086a08(UnkLnkVramBlock** ppList, UnkLnkVramBlock** ppBlockPool);
BOOL func_02086a4c(UnkLnkVramMan* pMgr, UnkLnkVramBlock** ppBlockPool, u32 baseAddr, u32 szByte);

#endif
