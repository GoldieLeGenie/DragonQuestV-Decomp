#include "gfd_lnkvram.h"

#pragma thumb on

typedef struct {
    UnkLnkVramMan mgr;              /* 0x00 */
    UnkLnkVramBlock* pBlockPool;    /* 0x04 */
    u32 szByte;                     /* 0x08 */
    void* pWork;                    /* 0x0C */
    u32 szWork;                     /* 0x10 */
} UnkLnkPlttVramManager;

typedef u32 (*UnkAllocPlttVramFunc)(u32 szByte, BOOL is4pltt, u32 opt);
typedef int (*UnkFreePlttVramFunc)(u32 key);

UnkLnkPlttVramManager data_02127b58;
extern UnkAllocPlttVramFunc data_0209c790;
extern UnkFreePlttVramFunc data_0209c794;

void func_02086db4(void);
u32 func_02086d00(u32 szByte, BOOL is4pltt, u32 opt);
int func_02086d84(u32 plttKey);

u32 func_02086cc4(u32 numMemBlk)
{
    return numMemBlk * sizeof(UnkLnkVramBlock);
}

void func_02086cc8(u32 szByte, void* pManagementWork, u32 szManagementWork, BOOL useAsDefault)
{
    UnkLnkPlttVramManager* pMgr = &data_02127b58;

    pMgr->szByte = szByte;
    pMgr->pWork = pManagementWork;
    pMgr->szWork = szManagementWork;
    func_02086db4();

    if (useAsDefault) {
        data_0209c790 = func_02086d00;
        data_0209c794 = func_02086d84;
    }
}

u32 func_02086d00(u32 szByte, BOOL is4pltt, u32 opt)
{
    u32 addr;
    BOOL result;
    u32 sz = (szByte == 0) ? 8 : ((szByte + 7) & ~7);

    if (sz >= 0x7fff8) {
        return 0;
    }

    if (is4pltt) {
        result = func_0208692c(&data_02127b58.mgr, &data_02127b58.pBlockPool, &addr, sz, 8);
        if (addr + sz > 0x10000) {
            func_02086a4c(&data_02127b58.mgr, &data_02127b58.pBlockPool, addr, sz);
            return 0;
        }
    } else {
        result = func_0208692c(&data_02127b58.mgr, &data_02127b58.pBlockPool, &addr, sz, 16);
    }
    if (result) {
        return ((sz >> 3) << 16) | ((addr >> 3) & 0xffff);
    }
    return 0;
}

int func_02086d84(u32 plttKey)
{
    u32 addr = (plttKey & 0xffff) << 3;
    u32 szByte = ((plttKey & 0xffff0000) >> 16) << 3;
    BOOL result = func_02086a4c(&data_02127b58.mgr, &data_02127b58.pBlockPool, addr, szByte);

    return result ? 0 : 1;
}

void func_02086db4(void)
{
    data_02127b58.pBlockPool = func_020868b8(data_02127b58.pWork, data_02127b58.szWork / sizeof(UnkLnkVramBlock));
    func_020868b0(&data_02127b58.mgr);
    func_020868e4(&data_02127b58.mgr, &data_02127b58.pBlockPool, 0, data_02127b58.szByte);
    func_02086a08(&data_02127b58.mgr.pFreeList, &data_02127b58.pBlockPool);
}
