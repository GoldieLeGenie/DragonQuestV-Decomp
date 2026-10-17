#ifndef G3D_INTERNAL_H
#define G3D_INTERNAL_H

#include <nitro/types.h>
#include <nitro/reg.h>

typedef s32 fx32;
typedef s16 fx16;
typedef s64 fx64;

#define FX32_ONE 0x1000

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22; } MtxFx33;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22, _30, _31, _32; } MtxFx43;
typedef struct { fx32 _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33; } MtxFx44;

/* resource structures */
typedef struct NNSG3dResDict {
    u8 revision;     // 0x00
    u8 numEntry;     // 0x01
    u16 sizeDictBlk; // 0x02
    u16 unk_04;      // 0x04
    u16 ofsEntry;    // 0x06
} NNSG3dResDict;

typedef struct UnkResDictTreeNode {
    u8 refBit;   // 0x00
    u8 idx[2];   // 0x01 (left, right)
    u8 idxEntry; // 0x03
} UnkResDictTreeNode;

typedef struct UnkResDictEntryHeader {
    u16 sizeUnit; // 0x00
    u16 ofsName;  // 0x02
    u8 data[4];   // 0x04
} UnkResDictEntryHeader;

typedef struct NNSG3dResName {
    u32 val[4];
} NNSG3dResName;

static inline void* GetResDataByIdx(const NNSG3dResDict* dict, u32 idx) {
    if (dict != NULL && idx < dict->numEntry) {
        UnkResDictEntryHeader* p = (UnkResDictEntryHeader*)((u8*)dict + dict->ofsEntry);
        return (void*)((u8*)&p->data[0] + p->sizeUnit * idx);
    }
    return NULL;
}

typedef struct UnkBinFileHeader {
    u32 signature;   // 0x00
    u16 byteOrder;   // 0x04
    u16 version;     // 0x06
    u32 fileSize;    // 0x08
    u16 headerSize;  // 0x0C
    u16 dataBlocks;  // 0x0E
} UnkBinFileHeader;

typedef struct NNSG3dResTexInfo {
    u32 vramKey;    // 0x00
    u16 sizeTex;    // 0x04 data size / 8
    u16 ofsDict;    // 0x06
    u16 flag;       // 0x08 (bit 0: loaded)
    u16 unk_0a;     // 0x0A
    u32 ofsTex;     // 0x0C
} NNSG3dResTexInfo;

typedef struct NNSG3dResTex4x4Info {
    u32 vramKey;    // 0x00
    u16 sizeTex;    // 0x04 data size / 8
    u16 ofsDict;    // 0x06
    u16 flag;       // 0x08 (bit 0: loaded)
    u16 unk_0a;     // 0x0A
    u32 ofsTex;     // 0x0C
    u32 ofsTexPlttIdx; // 0x10
} NNSG3dResTex4x4Info;

typedef struct NNSG3dResPlttInfo {
    u32 vramKey;    // 0x00
    u16 sizePltt;   // 0x04 data size / 8
    u16 flag;       // 0x06 (bit 0: loaded)
    u16 ofsDict;    // 0x08
    u16 unk_0a;     // 0x0A
    u32 ofsPlttData; // 0x0C
} NNSG3dResPlttInfo;

typedef struct NNSG3dResTex {
    u32 kind;                       // 0x00
    u32 size;                       // 0x04
    NNSG3dResTexInfo texInfo;       // 0x08
    NNSG3dResTex4x4Info tex4x4Info; // 0x18
    NNSG3dResPlttInfo plttInfo;     // 0x2C
    NNSG3dResDict dict;             // 0x3C
} NNSG3dResTex;

typedef struct NNSG3dResMdlSet NNSG3dResMdlSet;

typedef struct NNSG3dResMdlInfo {
    u8 sbcType;      // 0x00
    u8 scalingRule;  // 0x01
    u8 texMtxMode;   // 0x02
    u8 numNode;      // 0x03
    u8 numMat;       // 0x04
    u8 numShp;       // 0x05
    u8 unk_06;       // 0x06
    u8 unk_07;       // 0x07
    fx32 posScale;   // 0x08
    fx32 invPosScale; // 0x0C
    u8 unk_10[0x2c - 0x10];
} NNSG3dResMdlInfo;

typedef struct NNSG3dResMdl {
    u32 size;           // 0x00
    u32 ofsSbc;         // 0x04
    u32 ofsMat;         // 0x08
    u32 ofsShp;         // 0x0C
    u32 ofsEvpMtx;      // 0x10
    NNSG3dResMdlInfo info; // 0x14
    NNSG3dResDict nodeInfo; // 0x40
} NNSG3dResMdl;

typedef struct NNSG3dResMat {
    u16 unk_00;         // 0x00
    u16 unk_02;         // 0x02
    NNSG3dResDict dict; // 0x04
} NNSG3dResMat;

typedef struct NNSG3dResMatData {
    u16 itemTag;      // 0x00
    u16 size;         // 0x02
    u32 diffAmb;      // 0x04
    u32 specEmi;      // 0x08
    u32 polyAttr;     // 0x0C
    u32 polyAttrMask; // 0x10
    u32 texImageParam; // 0x14
    u32 unk_18;       // 0x18
    u16 texPlttBase;  // 0x1C
    u16 flag;         // 0x1E
    u16 origWidth;    // 0x20
    u16 origHeight;   // 0x22
    fx32 magW;        // 0x24
    fx32 magH;        // 0x28
    u8 texMtx[4];     // 0x2C
} NNSG3dResMatData;

typedef struct NNSG3dResShp {
    NNSG3dResDict dict; // 0x00
} NNSG3dResShp;

typedef struct NNSG3dResShpData {
    u16 itemTag; // 0x00
    u16 size;    // 0x02
    u32 flag;    // 0x04
    u32 ofsDL;   // 0x08
    u32 sizeDL;  // 0x0C
} NNSG3dResShpData;

typedef struct UnkResNodeData {
    u16 flag; // 0x00
    s16 _00;  // 0x02
} UnkResNodeData;

/* animation results */
typedef struct NNSG3dMatAnmResult {
    u32 flag;          // 0x00
    u32 prmMatColor0;  // 0x04
    u32 prmMatColor1;  // 0x08
    u32 prmPolygonAttr; // 0x0C
    u32 prmTexImage;   // 0x10
    u32 prmTexPltt;    // 0x14
    fx32 scaleS;       // 0x18
    fx32 scaleT;       // 0x1C
    fx16 rotSin;       // 0x20
    fx16 rotCos;       // 0x22
    fx32 transS;       // 0x24
    fx32 transT;       // 0x28
    u16 origWidth;     // 0x2C
    u16 origHeight;    // 0x2E
    fx32 magW;         // 0x30
    fx32 magH;         // 0x34
} NNSG3dMatAnmResult;

typedef struct NNSG3dJntAnmResult {
    u32 flag;        // 0x00
    VecFx32 scale;   // 0x04
    VecFx32 scaleEx0; // 0x10
    VecFx32 scaleEx1; // 0x1C
    MtxFx33 rot;     // 0x28
    VecFx32 trans;   // 0x4C
} NNSG3dJntAnmResult;

typedef struct NNSG3dVisAnmResult {
    BOOL isVisible;
} NNSG3dVisAnmResult;

typedef struct NNSG3dAnmObj NNSG3dAnmObj;
typedef void (*UnkAnmFunc)(void* result, NNSG3dAnmObj* obj, u32 idx);
typedef BOOL (*UnkBlendFunc)(void* result, NNSG3dAnmObj* obj, u32 idx);

struct NNSG3dAnmObj {
    fx32 frame;            // 0x00
    fx32 ratio;            // 0x04
    void* resAnm;          // 0x08
    void* funcAnm;         // 0x0C
    NNSG3dAnmObj* next;    // 0x10
    void* resTex;          // 0x14
    u8 priority;           // 0x18
    u8 numMapData;         // 0x19
    u16 mapData[1];        // 0x1A
};

typedef struct NNSG3dRS NNSG3dRS;
typedef void (*UnkSbcCallback)(NNSG3dRS* rs);

typedef struct NNSG3dRenderObj {
    u32 flag;                    // 0x00
    NNSG3dResMdl* resMdl;        // 0x04
    NNSG3dAnmObj* anmMat;        // 0x08
    UnkBlendFunc funcBlendMat;   // 0x0C
    NNSG3dAnmObj* anmJnt;        // 0x10
    UnkBlendFunc funcBlendJnt;   // 0x14
    NNSG3dAnmObj* anmVis;        // 0x18
    UnkBlendFunc funcBlendVis;   // 0x1C
    UnkSbcCallback cbFunc;       // 0x20
    u8 cbCmd;                    // 0x24
    u8 cbTiming;                 // 0x25
    u16 unk_26;                  // 0x26
    UnkSbcCallback cbInitFunc;   // 0x28
    void* unk_2c;                // 0x2C
    u8* ptrUserSbc;              // 0x30
    NNSG3dJntAnmResult* recJntAnm; // 0x34
    NNSG3dMatAnmResult* recMatAnm; // 0x38
    u32 hintMatAnmExist[2];      // 0x3C
    u32 hintJntAnmExist[2];      // 0x44
    u32 hintVisAnmExist[2];      // 0x4C
} NNSG3dRenderObj;

typedef void (*UnkJntScaleFunc)(NNSG3dJntAnmResult* r, const void* p, const u8* cmd, u32 flag);
typedef void (*UnkJntMtxFunc)(const NNSG3dJntAnmResult* r);
typedef void (*UnkTexMtxFunc)(NNSG3dMatAnmResult* r);

struct NNSG3dRS {
    u8* c;                            // 0x000
    NNSG3dRenderObj* pRenderObj;      // 0x004
    u32 flag;                         // 0x008
    UnkSbcCallback cbVecFunc[32];     // 0x00C
    u8 cbVecTiming[32];               // 0x08C
    u8 currentNode;                   // 0x0AC
    u8 currentMat;                    // 0x0AD
    u8 currentNodeDesc;               // 0x0AE
    u8 unk_af;                        // 0x0AF
    NNSG3dMatAnmResult* pMatAnmResult; // 0x0B0
    NNSG3dJntAnmResult* pJntAnmResult; // 0x0B4
    NNSG3dVisAnmResult* pVisAnmResult; // 0x0B8
    u32 isMatCached[4];               // 0x0BC
    u32 isScaleCacheOne[2];           // 0x0CC
    NNSG3dResDict* pResNodeInfo;      // 0x0D4
    NNSG3dResMat* pResMat;            // 0x0D8
    NNSG3dResShp* pResShp;            // 0x0DC
    fx32 posScale;                    // 0x0E0
    fx32 invPosScale;                 // 0x0E4
    UnkJntScaleFunc funcJntScale;     // 0x0E8
    UnkJntMtxFunc funcJntMtx;         // 0x0EC
    UnkTexMtxFunc funcTexMtx;         // 0x0F0
    NNSG3dMatAnmResult tmpMatAnmResult; // 0x0F4
    NNSG3dJntAnmResult tmpJntAnmResult; // 0x12C
    NNSG3dVisAnmResult tmpVisAnmResult; // 0x184
};

typedef void (*UnkSbcFunc)(NNSG3dRS* rs, u32 opt);
typedef void (*UnkMatFunc)(NNSG3dRS* rs, u32 opt, const NNSG3dResMatData* mat, u32 idx);
typedef void (*UnkShpFunc)(NNSG3dRS* rs, u32 opt, const NNSG3dResShpData* shp, u32 idx);

typedef struct NNSG3dGlb {
    u32 unk_000[2];          // 0x000 packed command + matrix mode (sent with func_020826d0)
    MtxFx44 projMtx;         // 0x008
    u32 unk_048;             // 0x048 matrix mode
    MtxFx43 cameraMtx;       // 0x04C
    u32 unk_07c;             // 0x07C packed commands
    u32 unk_080[4];          // 0x080 light vectors
    u32 unk_090;             // 0x090 packed commands
    u32 prmMatColor0;        // 0x094
    u32 prmMatColor1;        // 0x098
    u32 prmPolygonAttr;      // 0x09C
    u32 unk_0a0;             // 0x0A0 viewport
    u32 unk_0a4;             // 0x0A4 packed commands
    u32 unk_0a8[4];          // 0x0A8 light colors
    u32 unk_0b8;             // 0x0B8 packed commands
    MtxFx33 prmBaseRot;      // 0x0BC
    VecFx32 unk_0e0;         // 0x0E0 base translation
    VecFx32 unk_0ec;         // 0x0EC base scale
    u32 unk_0f8;             // 0x0F8
    u32 flag;                // 0x0FC (bits set = cached matrix valid)
    MtxFx43 unk_100;         // 0x100 inverse camera matrix
    MtxFx43 unk_130;         // 0x130 base rot/scale * camera
    MtxFx43 unk_160;         // 0x160 inverse of unk_130
    u8 unk_190[0x30];        // 0x190
    MtxFx44 unk_1c0;         // 0x1C0 inverse projection matrix
    MtxFx44 unk_200;         // 0x200 inverse (projection * camera) matrix
    VecFx32 camPos;          // 0x240
    VecFx32 camUp;           // 0x24C
    VecFx32 camTarget;       // 0x258
} NNSG3dGlb;

typedef struct NNSG3dGeBuffer {
    u32 idx;        // 0x000
    u32 data[0xc0]; // 0x004
} NNSG3dGeBuffer;

/* per-node scale cache entry */
typedef struct UnkScaleCache {
    VecFx32 s;   // 0x00
    VecFx32 inv; // 0x0C
} UnkScaleCache;

/* per-joint envelope matrix cache entry */
typedef struct UnkEvpCache {
    MtxFx44 m; // 0x00
    MtxFx33 n; // 0x40
} UnkEvpCache;

/* render state buffers (data_02124e1c) */
typedef struct UnkG3dRSOnGlb {
    NNSG3dMatAnmResult matCache[64];   // 0x0000
    UnkScaleCache      scaleCache[64]; // 0x0E00
    UnkEvpCache        evpCache[64];   // 0x1400
} UnkG3dRSOnGlb;

typedef struct UnkGeState {
    NNSG3dGeBuffer* buf; // 0x00
    volatile u32 busy;   // 0x04
    u32 useDmaAsync;     // 0x08
} UnkGeState;

static inline NNSG3dResMatData* GetMatDataByIdx(const NNSG3dResMat* mat, u32 idx) {
    if (mat != NULL) {
        const u32* p = (const u32*)GetResDataByIdx(&mat->dict, idx);
        if (p != NULL) {
            return (NNSG3dResMatData*)((u8*)mat + *p);
        }
    }
    return NULL;
}

static inline NNSG3dResShpData* GetShpDataByIdx(const NNSG3dResShp* shp, u32 idx) {
    if (shp != NULL) {
        const u32* p = (const u32*)GetResDataByIdx(&shp->dict, idx);
        if (p != NULL) {
            return (NNSG3dResShpData*)((u8*)shp + *p);
        }
    }
    return NULL;
}

static inline UnkResNodeData* GetNodeDataByIdx(const NNSG3dResDict* info, u32 idx) {
    if (info != NULL) {
        const u32* p = (const u32*)GetResDataByIdx(info, idx);
        if (p != NULL) {
            return (UnkResNodeData*)((u8*)info + *p);
        }
    }
    return NULL;
}

/* callback helpers (inlined) */
static inline u32 CheckCallBack(NNSG3dRS* rs, u32 cmd) {
    return rs->cbVecFunc[cmd] ? rs->cbVecTiming[cmd] : 0;
}

static inline BOOL CallBackCheck_A(NNSG3dRS* rs, u32 cmd, u32* pTiming) {
    *pTiming = CheckCallBack(rs, cmd);
    if (*pTiming == 1) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[cmd](rs);
        *pTiming = CheckCallBack(rs, cmd);
        return rs->flag & 0x40;
    }
    return FALSE;
}

static inline BOOL CallBackCheck_B(NNSG3dRS* rs, u32 cmd, u32* pTiming) {
    if (*pTiming == 2) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[cmd](rs);
        *pTiming = CheckCallBack(rs, cmd);
        return rs->flag & 0x40;
    }
    return FALSE;
}

static inline BOOL CallBackCheck_C(NNSG3dRS* rs, u32 cmd, u32 timing) {
    if (timing == 3) {
        rs->flag &= ~0x40;
        rs->cbVecFunc[cmd](rs);
        return rs->flag & 0x40;
    }
    return FALSE;
}

/* external functions */
void MI_CpuFill(u32 value, void* dest, u32 size);
void MI_CpuFillU16(u16 value, void* dest, u32 size);
void MI_CpuFillFromSrc(const void* src, volatile void* dest, u32 size);
void MI_CpuCopy(const void* src, void* dest, u32 size);
void MI_CpuClear24(void* dest);
void func_02070224(u32 value, void* dest, u32 size);
void func_0206ffd0(u32 dmaNo, const void* src, u32 size, void (*cb)(void*), void* arg);
void func_0207013c(u32 dmaNo, const void* src, u32 size, void (*cb)(void*), void* arg);
void MI_CpuCopy64(const u32* src, u32* dest);
s64 FX_Divide64(s32 denom);
void func_02088970(MtxFx33* m);
void func_02088d40(MtxFx43* m);
void func_02089630(MtxFx44* m);
void func_02088e28(const MtxFx43* src, MtxFx43* dst);
void func_020891b4(const MtxFx43* a, const MtxFx43* b, MtxFx43* ab);
void func_02088d9c(const MtxFx43* src, MtxFx43* dst, fx32 x, fx32 y, fx32 z);
void func_02088d68(const MtxFx43* src, MtxFx44* dst);
void func_02089690(const MtxFx44* a, const MtxFx44* b, MtxFx44* ab);
fx32 func_0208a2d0(const VecFx32* v);
void func_0208a330(const VecFx32* src, VecFx32* dst);
void func_02089488(const VecFx32* v, const MtxFx43* m, VecFx32* dst);
void func_0208965c(const MtxFx44* src, MtxFx43* dst);
fx32 FX_Divide(fx32 a, fx32 b);
void FX_InvAsync(fx32 d);
fx64 FX_GetDivResultFx64c(void);
void func_02075ae4(const MtxFx43* m);
void func_02075b00(const MtxFx43* m);
void func_02075b1c(const MtxFx33* m);
void func_02075b38(void);
BOOL func_02075e58(MtxFx44* m);
BOOL func_02075e88(MtxFx33* m);
void func_020801e8(void);
const MtxFx43* func_020803f8(void);
const MtxFx43* func_02080608(void);
const MtxFx43* func_02080630(void);
const MtxFx44* func_02080658(void);
void func_0208069c(int* x1, int* y1, int* x2, int* y2);
u32 func_0207f9dc(const void* anm, const NNSG3dResMdl* mdl);
fx32 func_0208a8b4(fx32 v32, fx64 v64c);
void* func_02083268(const UnkBinFileHeader* file);
NNSG3dResTex* func_02083270(const UnkBinFileHeader* file);
u32 func_0207fc2c(NNSG3dResTex* tex);
u32 func_0207fc3c(NNSG3dResTex* tex);
void func_0207fc4c(NNSG3dResTex* tex, u32 texKey, u32 tex4x4Key);
void func_0207fc5c(NNSG3dResTex* tex, BOOL execBeginEnd);
void func_0207fcd8(NNSG3dResTex* tex, u32* texKey, u32* tex4x4Key);
u32 func_0207fd08(NNSG3dResTex* tex);
void func_0207fd18(NNSG3dResTex* tex, u32 plttKey);
void func_0207fd1c(NNSG3dResTex* tex, BOOL execBeginEnd);
u32 func_0207fd4c(NNSG3dResTex* tex);
BOOL func_0208012c(NNSG3dResMdlSet* mdlSet, NNSG3dResTex* tex);
void func_02080194(NNSG3dResMdlSet* mdlSet);
/* current VRAM manager functions (gfd) */
extern u32 (*data_0209c788)(u32 size, BOOL is4x4comp, u32 opt);
extern int (*data_0209c78c)(u32 key);
extern u32 (*data_0209c790)(u32 size, BOOL is4pltt, u32 opt);
extern int (*data_0209c794)(u32 key);
void* func_0207ebcc(void* allocator, u32 size);
void func_0207ebd8(void* allocator, void* p);

/* functions of this range */
void G3d_RenderSBCCommands(NNSG3dRS* rs);
void func_02080c04(NNSG3dRS* rs, NNSG3dRenderObj* obj);
void func_02080d48(u32* hint, const NNSG3dAnmObj* anm);
void G3d_Render(NNSG3dRenderObj* obj);
void func_02082604(void);
void func_0208263c(void);
void func_0208264c(void* arg);
void func_02082660(const u32* dl, u32 size);
void func_020826d0(u32 op, const void* args, u32 num);
void func_02082758(MtxFx43* m, MtxFx33* n);

/* data */
extern UnkSbcFunc data_0209c6a8[];   // SBC command table
extern NNSG3dRS* data_02124e18;      // current render state
extern UnkG3dRSOnGlb data_02124e1c;  // render state buffers
extern NNSG3dGlb data_02124bb4;
extern UnkGeState data_02127b1c;
extern u32 data_0209c504;

#endif
