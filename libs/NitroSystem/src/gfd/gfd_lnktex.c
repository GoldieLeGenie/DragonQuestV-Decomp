#include "gfd_lnkvram.h"

#pragma thumb on

typedef struct {
    UnkLnkVramMan mgr;              /* 0x00 */
    UnkLnkVramMan mgrFor4x4;        /* 0x04 */
    UnkLnkVramBlock* pBlockPool;    /* 0x08 */
    u32 szByte;                     /* 0x0C */
    u32 szByteFor4x4;               /* 0x10 */
    void* pWork;                    /* 0x14 */
    u32 szWork;                     /* 0x18 */
} UnkLnkTexVramManager;

typedef struct {
    u32 szFree;                     /* 0x00 */
    u32 szNrm;                      /* 0x04 */
    u32 sz4x4;                      /* 0x08 */
} UnkLnkTexSlot;

typedef struct {
    UnkLnkTexSlot slot[4];
} UnkLnkTexSlotArray;

typedef u32 (*UnkAllocTexVramFunc)(u32 szByte, BOOL is4x4comp, u32 opt);
typedef int (*UnkFreeTexVramFunc)(u32 key);

UnkLnkTexVramManager data_02127b3c;
extern UnkAllocTexVramFunc data_0209c788;
extern UnkFreeTexVramFunc data_0209c78c;

void func_02086b90(void);
u32 func_02086adc(u32 szByte, BOOL is4x4comp, u32 opt);
int func_02086b40(u32 texKey);


static inline u32 KeyAddr_(u32 key) { return (u32)((key & 0xffff) << 3); }
static inline u32 KeySize_(u32 key) { return (u32)(((key & 0x7fff0000) >> 16) << 4); }
static inline BOOL Key4x4_(u32 key) { return (BOOL)((key & 0x80000000) >> 31); }

u32 func_02086aa0(u32 numMemBlk)
{
    return numMemBlk * sizeof(UnkLnkVramBlock);
}

void func_02086aa4(u32 szByte, u32 szByteFor4x4, void* pManagementWork, u32 szManagementWork, BOOL useAsDefault)
{
    UnkLnkTexVramManager* pMgr = &data_02127b3c;

    pMgr->szByte = szByte;
    pMgr->szByteFor4x4 = szByteFor4x4;
    pMgr->pWork = pManagementWork;
    pMgr->szWork = szManagementWork;
    func_02086b90();

    if (useAsDefault) {
        data_0209c788 = func_02086adc;
        data_0209c78c = func_02086b40;
    }
}

u32 func_02086adc(u32 szByte, BOOL is4x4comp, u32 opt)
{
    u32 addr;
    BOOL result;
    u32 sz = (szByte == 0) ? 16 : ((szByte + 15) & ~15);

    if (sz >= 0x7fff0) {
        return 0;
    }

    if (is4x4comp) {
        result = func_0208691c(&data_02127b3c.mgrFor4x4, &data_02127b3c.pBlockPool, &addr, sz);
    } else {
        result = func_0208691c(&data_02127b3c.mgr, &data_02127b3c.pBlockPool, &addr, sz);
    }
    if (result) {
        return ((sz >> 4) << 16) | ((addr >> 3) & 0xffff) | (is4x4comp << 31);
    }
    return 0;
}

int func_02086b40(u32 texKey)
{
    u32 addr = KeyAddr_(texKey);
    u32 szByte = KeySize_(texKey);
    BOOL is4x4comp = Key4x4_(texKey);
    BOOL result;

    if (szByte != 0) {
        if (is4x4comp) {
            result = func_02086a4c(&data_02127b3c.mgrFor4x4, &data_02127b3c.pBlockPool, addr, szByte);
        } else {
            result = func_02086a4c(&data_02127b3c.mgr, &data_02127b3c.pBlockPool, addr, szByte);
        }
        if (result) {
            return 0;
        } else {
            return 1;
        }
    }
    return 2;
}

void func_02086b90(void)
{
    UnkLnkTexSlotArray slots = {{{0x20000, 0, 0}, {0x20000, 0, 0}, {0x20000, 0, 0}, {0x20000, 0, 0}}};
    u32 szNrm;
    u32 sz4x4;
    u32 szIdx;
    u32 i;
    u32 sz;
    u32 ofs;
    UnkLnkTexSlot* pSlot;
    UnkLnkTexSlot* pSlot2;

    pSlot = slots.slot;
    sz4x4 = data_02127b3c.szByteFor4x4;
    szIdx = sz4x4 / 2;
    szNrm = data_02127b3c.szByte - (sz4x4 + szIdx);

    for (i = 0; i < 4; i++, pSlot++) {
        if (i == 0 || i == 2) {
            if (pSlot->szFree != 0 && sz4x4 != 0) {
                sz = pSlot->szFree;
                if (sz > sz4x4) {
                    sz = sz4x4;
                }
                pSlot->sz4x4 += sz;
                pSlot->szFree -= sz;
                sz4x4 -= sz;
            }
        }
    }
    slots.slot[1].szFree -= szIdx;

    pSlot2 = slots.slot;
    for (i = 0; i < 4; i++, pSlot2++) {
        if (pSlot2->szFree != 0 && szNrm != 0) {
            sz = pSlot2->szFree;
            if (sz > szNrm) {
                sz = szNrm;
            }
            pSlot2->szNrm += sz;
            pSlot2->szFree -= sz;
            szNrm -= sz;
        }
    }

    func_020868b0(&data_02127b3c.mgr);
    func_020868b0(&data_02127b3c.mgrFor4x4);
    data_02127b3c.pBlockPool = func_020868b8(data_02127b3c.pWork, data_02127b3c.szWork / sizeof(UnkLnkVramBlock));

    if (slots.slot[0].sz4x4 != 0) {
        func_020868e4(&data_02127b3c.mgrFor4x4, &data_02127b3c.pBlockPool, 0, slots.slot[0].sz4x4);
    }
    ofs = slots.slot[0].sz4x4;
    if (slots.slot[0].szNrm != 0) {
        func_020868e4(&data_02127b3c.mgr, &data_02127b3c.pBlockPool, ofs, slots.slot[0].szNrm);
    }
    if (slots.slot[2].sz4x4 != 0) {
        func_020868e4(&data_02127b3c.mgrFor4x4, &data_02127b3c.pBlockPool, 0x40000, slots.slot[2].sz4x4);
    }
    ofs = 0x40000 + slots.slot[2].sz4x4;
    if (slots.slot[2].szNrm != 0) {
        func_020868e4(&data_02127b3c.mgr, &data_02127b3c.pBlockPool, ofs, slots.slot[2].szNrm);
    }
    if (slots.slot[3].szNrm != 0) {
        func_020868e4(&data_02127b3c.mgr, &data_02127b3c.pBlockPool, 0x60000, slots.slot[3].szNrm);
    }
    if (slots.slot[1].szNrm != 0) {
        func_020868e4(&data_02127b3c.mgr, &data_02127b3c.pBlockPool, 0x20000 + szIdx, slots.slot[1].szNrm);
    }

    func_02086a08(&data_02127b3c.mgr.pFreeList, &data_02127b3c.pBlockPool);
    func_02086a08(&data_02127b3c.mgrFor4x4.pFreeList, &data_02127b3c.pBlockPool);
}
