#include "../nns_internal.h"

#pragma thumb on

typedef struct {
    u32 type;           /* 0x00 */
    const void* pSrc;   /* 0x04 */
    u32 dstAddr;        /* 0x08 */
    u32 szByte;         /* 0x0C */
} UnkVramTransferTask;

typedef struct {
    UnkVramTransferTask* pTaskArray; /* 0x00 */
    u32 lengthOfArray;               /* 0x04 */
    u16 idxFront;                    /* 0x08 */
    u16 idxRear;                     /* 0x0A */
    u16 numTasks;                    /* 0x0C */
    u32 totalSize;                   /* 0x10 */
} UnkVramTransferManager;

typedef void (*UnkVramLoadFunc)(const void* pSrc, u32 dstAddr, u32 szByte);

UnkVramTransferManager data_02127b28;

void func_02076e98(void);
void func_02076ef4(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02077034(void);
void func_02077080(void);
void func_020770b4(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02077120(void);
void func_02077164(void);
void func_020771f4(const void* pSrc, u32 szByte);
void func_0207725c(const void* pSrc, u32 szByte);
void func_020772c8(void);
void func_020767d0(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076890(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076950(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076a10(const void* pSrc, u32 dstAddr, u32 szByte);
void func_020764d0(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076590(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076650(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076710(const void* pSrc, u32 dstAddr, u32 szByte);
void GX_LoadOBJPltt(const void* pSrc, u32 dstAddr, u32 szByte);
void GX_LoadBGPltt(const void* pSrc, u32 dstAddr, u32 szByte);
void GX_BeginLoadOBJExtPltt(void);
void GX_LoadOBJExtPltt(const void* pSrc, u32 dstAddr, u32 szByte);
void GX_EndLoadOBJExtPltt(void);
void GX_BeginLoadBGExtPltt(void);
void GX_LoadBGExtPltt(const void* pSrc, u32 dstAddr, u32 szByte);
void GX_EndLoadBGExtPltt(void);
void GX_LoadOAM(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076420(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076830(const void* pSrc, u32 dstAddr, u32 szByte);
void func_020768f0(const void* pSrc, u32 dstAddr, u32 szByte);
void func_020769b0(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076a70(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076530(const void* pSrc, u32 dstAddr, u32 szByte);
void func_020765f0(const void* pSrc, u32 dstAddr, u32 szByte);
void func_020766b0(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076770(const void* pSrc, u32 dstAddr, u32 szByte);
void GXS_LoadOBJPltt(const void* pSrc, u32 dstAddr, u32 szByte);
void GXS_LoadBGPltt(const void* pSrc, u32 dstAddr, u32 szByte);
void GXS_BeginLoadOBJExtPltt(void);
void GXS_LoadOBJExtPltt(const void* pSrc, u32 dstAddr, u32 szByte);
void GXS_EndLoadOBJExtPltt(void);
void GXS_BeginLoadBGExtPltt(void);
void GXS_LoadBGExtPltt(const void* pSrc, u32 dstAddr, u32 szByte);
void GXS_EndLoadBGExtPltt(void);
void GXS_LoadOAM(const void* pSrc, u32 dstAddr, u32 szByte);
void func_02076478(const void* pSrc, u32 dstAddr, u32 szByte);

u16 func_020864f8(UnkVramTransferManager* mgr, u16 idx)
{
    return (u16)((idx + 1) % mgr->lengthOfArray);
}

BOOL func_0208650c(UnkVramTransferManager* mgr)
{
    return mgr->numTasks == mgr->lengthOfArray;
}

BOOL func_0208651c(UnkVramTransferManager* mgr)
{
    return mgr->numTasks == 0;
}

void func_0208652c(const void* pSrc, u32 dstAddr, u32 szByte)
{
    func_02076e98();
    func_02076ef4(pSrc, dstAddr, szByte);
    func_02077034();
}

void func_02086548(const void* pSrc, u32 dstAddr, u32 szByte)
{
    func_02077080();
    func_020770b4(pSrc, dstAddr, szByte);
    func_02077120();
}

void func_02086564(const void* pSrc, u32 dstAddr, u32 szByte)
{
    func_02077164();
    func_020771f4(pSrc, szByte);
    func_020772c8();
}

void func_0208657c(const void* pSrc, u32 dstAddr, u32 szByte)
{
    func_02077164();
    func_0207725c(pSrc, szByte);
    func_020772c8();
}

void func_02086594(const void* pSrc, u32 dstAddr, u32 szByte) { func_020767d0(pSrc, dstAddr, szByte); }
void func_0208659c(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076890(pSrc, dstAddr, szByte); }
void func_020865a4(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076950(pSrc, dstAddr, szByte); }
void func_020865ac(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076a10(pSrc, dstAddr, szByte); }
void func_020865b4(const void* pSrc, u32 dstAddr, u32 szByte) { func_020764d0(pSrc, dstAddr, szByte); }
void func_020865bc(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076590(pSrc, dstAddr, szByte); }
void func_020865c4(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076650(pSrc, dstAddr, szByte); }
void func_020865cc(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076710(pSrc, dstAddr, szByte); }
void func_020865d4(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076650(pSrc, dstAddr, szByte); }
void func_020865dc(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076710(pSrc, dstAddr, szByte); }
void func_020865e4(const void* pSrc, u32 dstAddr, u32 szByte) { GX_LoadOBJPltt(pSrc, dstAddr, szByte); }
void func_020865ec(const void* pSrc, u32 dstAddr, u32 szByte) { GX_LoadBGPltt(pSrc, dstAddr, szByte); }

void func_020865f4(const void* pSrc, u32 dstAddr, u32 szByte)
{
    GX_BeginLoadOBJExtPltt();
    GX_LoadOBJExtPltt(pSrc, dstAddr, szByte);
    GX_EndLoadOBJExtPltt();
}

void func_02086610(const void* pSrc, u32 dstAddr, u32 szByte)
{
    GX_BeginLoadBGExtPltt();
    GX_LoadBGExtPltt(pSrc, dstAddr, szByte);
    GX_EndLoadBGExtPltt();
}

void func_0208662c(const void* pSrc, u32 dstAddr, u32 szByte) { GX_LoadOAM(pSrc, dstAddr, szByte); }
void func_02086634(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076420(pSrc, dstAddr, szByte); }
void func_0208663c(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076830(pSrc, dstAddr, szByte); }
void func_02086644(const void* pSrc, u32 dstAddr, u32 szByte) { func_020768f0(pSrc, dstAddr, szByte); }
void func_0208664c(const void* pSrc, u32 dstAddr, u32 szByte) { func_020769b0(pSrc, dstAddr, szByte); }
void func_02086654(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076a70(pSrc, dstAddr, szByte); }
void func_0208665c(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076530(pSrc, dstAddr, szByte); }
void func_02086664(const void* pSrc, u32 dstAddr, u32 szByte) { func_020765f0(pSrc, dstAddr, szByte); }
void func_0208666c(const void* pSrc, u32 dstAddr, u32 szByte) { func_020766b0(pSrc, dstAddr, szByte); }
void func_02086674(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076770(pSrc, dstAddr, szByte); }
void func_0208667c(const void* pSrc, u32 dstAddr, u32 szByte) { func_020766b0(pSrc, dstAddr, szByte); }
void func_02086684(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076770(pSrc, dstAddr, szByte); }
void func_0208668c(const void* pSrc, u32 dstAddr, u32 szByte) { GXS_LoadOBJPltt(pSrc, dstAddr, szByte); }
void func_02086694(const void* pSrc, u32 dstAddr, u32 szByte) { GXS_LoadBGPltt(pSrc, dstAddr, szByte); }

void func_0208669c(const void* pSrc, u32 dstAddr, u32 szByte)
{
    GXS_BeginLoadOBJExtPltt();
    GXS_LoadOBJExtPltt(pSrc, dstAddr, szByte);
    GXS_EndLoadOBJExtPltt();
}

void func_020866b8(const void* pSrc, u32 dstAddr, u32 szByte)
{
    GXS_BeginLoadBGExtPltt();
    GXS_LoadBGExtPltt(pSrc, dstAddr, szByte);
    GXS_EndLoadBGExtPltt();
}

void func_020866d4(const void* pSrc, u32 dstAddr, u32 szByte) { GXS_LoadOAM(pSrc, dstAddr, szByte); }
void func_020866dc(const void* pSrc, u32 dstAddr, u32 szByte) { func_02076478(pSrc, dstAddr, szByte); }

/* run one transfer task */
/* VRAM load function per transfer type */
const UnkVramLoadFunc data_0208ec60[36] = {
    func_0208652c, func_02086548, func_02086564, func_0208657c,
    func_02086594, func_0208659c, func_020865a4, func_020865ac,
    func_020865b4, func_020865bc, func_020865c4, func_020865cc,
    func_020865d4, func_020865dc, func_020865e4, func_020865ec,
    func_020865f4, func_02086610, func_0208662c, func_02086634,
    func_0208663c, func_02086644, func_0208664c, func_02086654,
    func_0208665c, func_02086664, func_0208666c, func_02086674,
    func_0208667c, func_02086684, func_0208668c, func_02086694,
    func_0208669c, func_020866b8, func_020866d4, func_020866dc,
};

void func_020866e4(UnkVramTransferTask* task)
{
    UnkVramLoadFunc func = data_0208ec60[task->type];
    DC_PurgeRange(task->pSrc, task->szByte);
    func(task->pSrc, task->dstAddr, task->szByte);
}

void func_02086708(UnkVramTransferManager* mgr)
{
    mgr->idxFront = mgr->idxRear = 0;
    mgr->numTasks = 0;
    mgr->totalSize = 0;
}

BOOL func_02086718(UnkVramTransferManager* mgr)
{
    if (!func_0208650c(mgr)) {
        mgr->idxRear = func_020864f8(mgr, mgr->idxRear);
        mgr->numTasks++;
        return TRUE;
    }
    return FALSE;
}

UnkVramTransferTask* func_0208673c(UnkVramTransferManager* mgr)
{
    return &mgr->pTaskArray[mgr->idxFront];
}

UnkVramTransferTask* func_02086748(UnkVramTransferManager* mgr)
{
    return &mgr->pTaskArray[mgr->idxRear];
}

BOOL func_02086754(UnkVramTransferManager* mgr)
{
    if (!func_0208651c(mgr)) {
        mgr->idxFront = func_020864f8(mgr, mgr->idxFront);
        mgr->numTasks--;
        return TRUE;
    }
    return FALSE;
}

void func_02086778(UnkVramTransferTask* pTaskArray, u32 lengthOfArray)
{
    data_02127b28.pTaskArray = pTaskArray;
    data_02127b28.lengthOfArray = lengthOfArray;
    func_02086708(&data_02127b28);
}

void func_02086790(void)
{
    UnkVramTransferManager* mgr = &data_02127b28;
    UnkVramTransferTask* task = func_0208673c(mgr);

    while (func_02086754(mgr)) {
        func_020866e4(task);
        mgr->totalSize -= task->szByte;
        task = func_0208673c(mgr);
    }
}

BOOL func_020867d0(u32 type, u32 dstAddr, const void* pSrc, u32 szByte)
{
    UnkVramTransferManager* mgr = &data_02127b28;
    UnkVramTransferTask* task;

    if (!func_0208650c(mgr)) {
        task = func_02086748(mgr);
        task->type = type;
        task->pSrc = pSrc;
        task->dstAddr = dstAddr;
        task->szByte = szByte;
        func_02086718(mgr);
        mgr->totalSize += task->szByte;
        return TRUE;
    }
    return FALSE;
}

u32 func_02086814(void)
{
    return data_02127b28.totalSize;
}
