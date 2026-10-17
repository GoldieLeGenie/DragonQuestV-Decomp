#pragma ipa file
#include "ov002/slimetouch/SlimeTouchGame.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/UnkVramTransfer.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/sound/SoundManager.hpp"
#include "nitro/dc.h"
#include "nitro/fs.hpp"
#include "nitro/fx/fx_division.h"
#include "nitro/fx/fx_trig.h"
#include "nitro/g3.hpp"
#include "nitro/gx.hpp"
#include "nitro/math.hpp"
#include "nnsys/fnd.hpp"
#include "nnsys/g2d.hpp"
#include <mem.h>
#include <stdio.h>

// ---------------------------------------------------------------------------
// inline helpers

inline u16 PAD_Read()
{
    return (u16)(((REG_KEYINPUT | *(vu16*)0x027fffa8) ^ 0x2fff) & 0x2fff);
}

inline void MATH_InitRand32(MATHRandContext32* context, u64 seed)
{
    context->x = seed;
    context->mul = (1566083941LL << 32) + 1812433253LL;
    context->add = 2531011;
}

inline u32 MATH_Rand32(MATHRandContext32* context, u32 max)
{
    context->x = context->mul * context->x + context->add;
    if (max == 0) {
        return (u32)(context->x >> 32);
    } else {
        return (u32)(((context->x >> 32) * max) >> 32);
    }
}

inline void MATH_InitRand16(MATHRandContext16* context, u32 seed)
{
    context->x = seed;
    context->mul = 1566083941LL;
    context->add = 2531011;
}

inline u16 MATH_Rand16(MATHRandContext16* context, u16 max)
{
    context->x = context->mul * context->x + context->add;
    if (max == 0) {
        return (u16)(context->x >> 16);
    } else {
        return (u16)(((context->x >> 16) * max) >> 16);
    }
}

inline void NNS_G3dGlbSetBaseRot(const MtxFx33* m)
{
    func_02070360(m, &data_02124bb4.prmBaseRot);
    data_02124bb4.flag &= ~0xa4;
}

inline NNSG3dResMdl* unkGetMdl(NNSG3dResMdlSet* mdlSet)
{
    NNSG3dResDictEntryHeader* entry = (NNSG3dResDictEntryHeader*)((u8*)&mdlSet->dict + mdlSet->dict.ofsEntry);
    return (NNSG3dResMdl*)((u8*)mdlSet + ((NNSG3dResDictMdlSetData*)entry->data)->offset);
}

inline void unkSetTexParam(UnkSpriteTexParam* param, NNSG2dCharacterData* chr)
{
    if (chr->mapingType == 0) {
        int sizeS_;
        switch (chr->W) {
        case 1:
            sizeS_ = 0;
            break;
        case 2:
            sizeS_ = 1;
            break;
        case 4:
            sizeS_ = 2;
            break;
        case 8:
            sizeS_ = 3;
            break;
        case 16:
            sizeS_ = 4;
            break;
        case 32:
            sizeS_ = 5;
            break;
        default:
            sizeS_ = 0;
            break;
        }
        param->sizeS = (GXTexSizeS)sizeS_;
        int sizeT_;
        switch (chr->H) {
        case 1:
            sizeT_ = 0;
            break;
        case 2:
            sizeT_ = 1;
            break;
        case 4:
            sizeT_ = 2;
            break;
        case 8:
            sizeT_ = 3;
            break;
        case 16:
            sizeT_ = 4;
            break;
        case 32:
            sizeT_ = 5;
            break;
        default:
            sizeT_ = 0;
            break;
        }
        param->sizeT = (GXTexSizeT)sizeT_;
    } else {
        param->sizeS = (GXTexSizeS)chr->W;
        param->sizeT = (GXTexSizeT)chr->H;
    }
    param->texFmt = (GXTexFmt)chr->pixelFmt;
    param->unk_0C = 0;
    param->plttColor0 = GX_TEXPLTTCOLOR0_TRNS;
    param->unk_14 = chr->mapingType;
}

inline fx32 FX_Mul32x64c(fx32 v32, fx64 v64c)
{
    return (fx32)((v64c * v32 + 0x80000000LL) >> 32);
}

inline UnkTouchPoint::UnkTouchPoint()
{
}

// ---------------------------------------------------------------------------
// data

struct UnkScreenPos {
    short x;
    short y;
};

struct UnkFadeQuad {
    short x;                                    // 0x00
    short y;                                    // 0x02
    short w;                                    // 0x04
    short h;                                    // 0x06
    short unk_08;                               // 0x08
    u8 z;                                       // 0x0A
    u8 alpha;                                   // 0x0B
    int unk_0c;                                 // 0x0C
    int unk_10;                                 // 0x10
    int unk_14;                                 // 0x14
    u16 unk_18;                                 // 0x18
    GXRgb col;                                  // 0x1A
};

struct UnkBgRect {
    short x;                                    // 0x00
    short y;                                    // 0x02
    short w;                                    // 0x04
    short h;                                    // 0x06
    short z;                                    // 0x08
    short ofsY;                                 // 0x0A
};

static ST_SPRITE_KIND sprite_kind_data[24] = {
    { 0, -1, 1 },
    { 101, -1, 0 },
    { 102, -1, 0 },
    { 103, -1, 0 },
    { 2, -1, 1 },
    { 0, -1, 1 },
    { 104, -1, 1 },
    { 105, -1, 1 },
    { 106, -1, 1 },
    { 107, -1, 1 },
    { 108, -1, 1 },
    { 109, -1, 1 },
    { 110, -1, 1 },
    { 111, -1, 1 },
    { 112, -1, 1 },
    { 113, -1, 1 },
    { 114, -1, 1 },
    { 115, -1, 1 },
    { 116, -1, 1 },
    { 117, -1, 1 },
    { 118, -1, 1 },
    { 119, -1, 1 },
    { 120, -1, 1 },
    { 100, -1, 1 },
};
static int s_housekiAmp = 4;
static const char* data_ov002_0212e364[14] = {
    "",
    "nextStage",
    "bonusStage",
    "skipNormaChk",
    "nextKindItem",
    "sound",
    "soundSe",
    "spDraw",
    "slimeScale",
    "BgDisp",
    "PositionTest",
    "playerChara",
    "playerDir",
    "lightVec",
};
static int s_touchTrg;
static UnkScreenPos s_touchPos;
static int s_tpMoveDiv = 4;
static fx32 slimeScale = 0x3333;
static fx32 s_fadeCount;
static short s_texCacheCount;
static int data_ov002_02133a88;
static fx32 s_fadeFrames = 0x3c000;
static ST_MG_ARG* pMiniGameArg;
static UnkScoreMessage s_scoreMessage[8];
static int s_ssaEffInit;
static BSSA_EFF_WORK g_eff_work[32];
static NNSFndAllocator s_allocator;
static u16 s_tpSampleCount;
static int s_rotxAngle = 0xc800;
static int data_ov002_02133b68[21];
static int s_firstFrame;
static MATHRandContext32 s_rand32;
static int s_drawFin;
static int s_effDz = 16;
static int s_touchValid;
static TPData s_tpAutoBuf[16];
static int data_ov002_02133a60;
static int s_bgDisp = 1;
static ST_OBJ_DATA obj_data[17] = {
    { { 0x3c000, 0x53000, 0 }, MOVE_up },
    { { 0x82000, 0x53000, 0 }, MOVE_up },
    { { 0xc8000, 0x53000, 0 }, MOVE_up },
    { { 0x64000, 0x7b000, 0xa000 }, MOVE_up },
    { { 0xa0000, 0x7b000, 0xa000 }, MOVE_up },
    { { 0x3c000, 0xa3000, 0x14000 }, MOVE_up },
    { { 0x82000, 0xa3000, 0x14000 }, MOVE_up },
    { { 0xc8000, 0xa3000, 0x14000 }, MOVE_up },
    { { -0x40000, 0x28000, 0x2a000 }, MOVE_norma2_up },
    { { -0x16000, 0x28000, 0x2a000 }, MOVE_norma2_wait },
    { { 0x14000, 0x28000, 0x2a000 }, MOVE_norma2_wait },
    { { 0x3e000, 0x28000, 0x2a000 }, MOVE_norma2_wait },
    { { 0x22000, 0x8e000, 0x2000 }, MOVE_iwa2 },
    { { 0xc8000, 0x9a000, 0x1000 }, MOVE_player2 },
    { { 0, 0, 0xc000 }, MOVE_gameStart },
    { { 0, 0, 0 }, MOVE_gameOver },
    { { 0x55000, 0xa000, -0xf000 }, MOVE_ase },
};
static int data_ov002_02133a6c;
static int font_sprite_data[9];
static int s_tpAlphaMul = 31;
static short slime_r = 22;
static SPRITE_DATA g_sprite_data[48];
#pragma explicit_zero_data on
static short s_touch2InitX = 0;
#pragma explicit_zero_data off
static fx32 normaSlimeScale = 0x1e380;
static void* s_expHeap;
static int s_clearStageX = 76;
static int s_clearStageY = 88;
static int intTrans0[3];
static fx32 s_playTime;
static int s_clearStageRestart;
static UnkFadeQuad s_fadeQuad = { 0, 0, 256, 192, 0, 255, 31 };
static short bakudanIwa_r = 16;
static u16 s_cameraAngle = 0x3e00;
static int updateCnt_downScr;
static BSSA_DATA* g_bssa[28];
static UnkVramCacheEntry s_plttCache[16];
#pragma explicit_zero_data on
static short s_touchInitY = 0;
#pragma explicit_zero_data off
static MATHRandContext16 s_rand16;
static int data_ov002_02133ac4[3];
static int data_ov002_02133ad0[3];
static int s_slimeSpriteInit;
void* g_mgWorkAddr;
static int s_tpMoveMul = 3;
static fx32 s_passFrame = 0x1000;
static int s_touchOld;
static SPRITE* s_bgSprite[2];
static int s_tpAutoSampling;
static short s_charaDrawOffset;
static ST_SIDE_INFO sideInfo[1];
static int s_expHeapCreated;
static UnkPadState s_pad;
static float data_ov002_0212e2fc = 2.5f;
static UnkSlimeCgAnm s_slimeCgAnm[9] = {
    { { { "SlimeTouch/START.nsbca", NULL }, { "SlimeTouch/START.nsbma", NULL }, { "SlimeTouch/START.nsbva", NULL }, { NULL, NULL } } },
    { { { "SlimeTouch/gameover.nsbca", NULL }, { "SlimeTouch/gameover.nsbma", NULL }, { "SlimeTouch/gameover.nsbva", NULL }, { NULL, NULL } } },
    { { { "SlimeTouch/ase.nsbca", NULL }, { "SlimeTouch/ase.nsbma", NULL }, { "SlimeTouch/ase.nsbva", NULL }, { NULL, NULL } } },
    { { { "SlimeTouch/board_1.nsbca", NULL } } },
    { { { "SlimeTouch/board_2.nsbca", NULL } } },
    { { { "SlimeTouch/board_3.nsbca", NULL } } },
    { { { "SlimeTouch/board_4.nsbca", NULL } } },
    { { { "SlimeTouch/board_5.nsbca", NULL } } },
    { { { "SlimeTouch/board_6.nsbca", NULL } } },
};
static int s_playerSprite[17] = {
    5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69,
};
static int data_ov002_02133a90;
static UnkTouchPoint s_tpSample[8];
static UnkScreenPos s_touchPos2;
static UnkBgRect s_bgRect[15] = {
    { 40, 150, 42, 32, 5, 1 },
    { 111, 150, 42, 32, 5, 1 },
    { 181, 150, 42, 32, 5, 1 },
    { 40, 182, 42, 16, 5, 0 },
    { 111, 182, 42, 16, 5, 0 },
    { 181, 182, 42, 16, 5, 0 },
    { 79, 186, 42, 14, 15, 0 },
    { 139, 186, 42, 14, 15, 0 },
    { 79, 198, 42, 32, 15, 1 },
    { 139, 198, 42, 32, 15, 1 },
    { 79, 230, 42, 4, 15, 0 },
    { 139, 230, 42, 4, 15, 0 },
    { 40, 224, 42, 32, 25, 0 },
    { 111, 224, 42, 32, 25, 0 },
    { 181, 224, 42, 32, 25, 0 },
};
static int s_clearStageX2 = 34;
static UnkSlimeCgModel s_slimeCgModel[7] = {
    { NULL, NULL, NULL, NULL },
    { "SlimeTouch/START.nsbmd", NULL, NULL, &s_slimeCgAnm[0] },
    { "SlimeTouch/gameover.nsbmd", NULL, NULL, &s_slimeCgAnm[1] },
    { "SlimeTouch/ase.nsbmd", NULL, NULL, &s_slimeCgAnm[2] },
    { "SlimeTouch/board_sl.nsbmd", NULL, NULL, &s_slimeCgAnm[3] },
    { "SlimeTouch/board_bs.nsbmd", NULL, NULL, &s_slimeCgAnm[3] },
    { "SlimeTouch/board_mt.nsbmd", NULL, NULL, &s_slimeCgAnm[3] },
};
static int s_pause;
static int s_nrotxAngle = 0xc000;
static short chara_r = 32;
#pragma explicit_zero_data on
static short s_touch2InitY = 0;
#pragma explicit_zero_data off
static int s_fadeMode = -1;
static int data_ov002_0212e334 = 300;
static UnkVramCacheEntry s_texCache[16];
static int s_tpFrameOfs = 8;
static int s_bgDataId[2];
unsigned int g_mgWorkSize;
static int s_tpAlphaDiv = 31;
static int data_ov002_0212e300 = 4;
static NNSFndAllocator* s_pAllocator;
static short s_plttCacheCount;
static int s_fadeState;
static int data_ov002_0212e2dc = 1;
static int s_clearStageDx = -10;
static SSA_DATA ssa_data_touch[28] = {
    { "SlimeTouch/bsaa/bakuhatu.bssa", 200 },
    { "SlimeTouch/bsaa/touch_fx_001.bssa", 201 },
    { "SlimeTouch/bsaa/m_kemu_siro.bssa", 202 },
    { "SlimeTouch/bsaa/touch_fx_002.bssa", 203 },
    { "SlimeTouch/bsaa/coin.bssa", 204 },
    { "SlimeTouch/bsaa/touch_001.bssa", 0 },
    { "SlimeTouch/bsaa/touch_001_6fl.bssa", 0 },
    { "SlimeTouch/bsaa/touch_001_9fl.bssa", 0 },
    { "SlimeTouch/bsaa/touch_002.bssa", 0 },
    { "SlimeTouch/bsaa/touch_002a.bssa", 0 },
    { "SlimeTouch/bsaa/touch_002b.bssa", 0 },
    { "SlimeTouch/bsaa/touch_003.bssa", 0 },
    { "SlimeTouch/bsaa/touch_004.bssa", 0 },
    { "SlimeTouch/bsaa/touch_005.bssa", 0 },
    { "SlimeTouch/bsaa/touch_006.bssa", 0 },
    { "SlimeTouch/bsaa/touch_007.bssa", 0 },
    { "SlimeTouch/bsaa/bonus001a.bssa", 0 },
    { "SlimeTouch/bsaa/bonus001b.bssa", 0 },
    { "SlimeTouch/bsaa/bonus001c.bssa", 0 },
    { "SlimeTouch/bsaa/bonus001d.bssa", 108 },
    { "SlimeTouch/bsaa/bonus002a.bssa", 0 },
    { "SlimeTouch/bsaa/bonus002b.bssa", 0 },
    { "SlimeTouch/bsaa/bonus002c.bssa", 0 },
    { "SlimeTouch/bsaa/bonus002d.bssa", 108 },
    { "SlimeTouch/bsaa/item_null1.bssa", 0 },
    { "SlimeTouch/bsaa/item_null2.bssa", 0 },
    { "SlimeTouch/bsaa/item_null3.bssa", 0 },
    { "SlimeTouch/bsaa/item_null4.bssa", 0 },
};
#pragma explicit_zero_data on
static short s_touchInitX = 0;
#pragma explicit_zero_data off
static int s_tpY = -2;

inline u32 rand32(u32 max)
{
    return MATH_Rand32(&s_rand32, max);
}

inline u16 rand16(u16 max)
{
    return MATH_Rand16(&s_rand16, max);
}

// ---------------------------------------------------------------------------
// system

void** unkfunc_02128060()
{
    if (s_expHeapCreated == 0) {
        s_expHeapCreated = 1;
        s_expHeap = func_0207e7ac(g_mgWorkAddr, g_mgWorkSize, 0);
    }
    return &s_expHeap;
}

void unkfunc_021280a4()
{
    TPCalibrateParam calibrate;
    func_020786d4();
    func_0207871c(&calibrate);
    func_02078794(&calibrate);
    s_touchValid = 0;
    s_touchTrg = 0;
    s_touchOld = 0;
    s_touchPos.x = s_touchInitX;
    s_touchPos.y = s_touchInitY;
    s_touchPos2.x = s_touch2InitX;
    s_touchPos2.y = s_touch2InitY;
}

void unkfunc_02128108()
{
    int touch = 0;
    s_touchValid = 0;
    if (s_tpAutoSampling) {
        u16 count = 0;
        u16 last = func_020788e8();
        u16 i = (last - 4) & 0xf;
        if (i != last) {
            do {
                TPData tp;
                func_02078a70(&tp, &s_tpAutoBuf[i]);
                if (tp.touch != 0 && tp.validity == 0) {
                    s_touchValid = 1;
                    s_tpSample[count].touch = 1;
                    s_touchPos.x = tp.x;
                    s_tpSample[count].x = s_touchPos.x;
                    s_touchPos.y = tp.y;
                    s_tpSample[count].y = s_touchPos.y;
                    count++;
                    touch = 1;
                }
                i = (i + 1) & 0xf;
            } while (i != last);
        }
        s_tpSampleCount = count;
    } else {
        TPData tp;
        do {
            func_02078844();
        } while (func_020788d4(&tp) != 0);
        s_touchValid = tp.validity == 0;
        if (tp.touch == 1 && tp.validity == 0) {
            touch = 1;
            s_touchPos.x = tp.x;
            s_touchPos.y = tp.y;
        }
    }
    s_touchPos2.x = s_touchPos.x;
    s_touchPos2.y = s_touchPos.y + 192;
    s_touchTrg = touch & (touch ^ s_touchOld);
    s_touchOld = touch;
}

void unkfunc_02128268()
{
}

void unkfunc_0212826c(int mode, GXRgb col, fx32 frames)
{
    s_fadeQuad.col = col;
    s_fadeMode = mode;
    s_fadeState = 1;
    s_fadeCount = 0;
    s_fadeFrames = frames;
}

void unkfunc_0212829c(fx32 passFrame)
{
    if (s_fadeFrames <= s_fadeCount) {
        s_fadeCount = s_fadeFrames;
        if (s_fadeState == 1) {
            s_fadeState = 2;
        }
    }
    int alpha = s_fadeCount * 31 / s_fadeFrames;
    if (s_fadeMode == 0) {
        alpha = 31 - alpha;
    }
    s_fadeQuad.alpha = alpha;
    s_fadeCount += passFrame;
}

BOOL unkfunc_02128314()
{
    BOOL end = FALSE;
    if (s_fadeState == 0 || s_fadeState == 3) {
        end = TRUE;
    }
    return end;
}

void unkfunc_02128334()
{
    func_020760b4(0, 0xc0000, 0, 0x100000, -0x100000, 0x100000, FX32_ONE, 1, NULL);
    G3_StoreMtx(0);
    G3_MtxMode(1);
}

void unkfunc_02128394(int upScreen)
{
    if (s_fadeState == 0) {
        return;
    }
    u8 alpha = s_fadeQuad.alpha;
    if (alpha != 0) {
        func_0207ec9c(5);
        if (upScreen == 0) {
            unkfunc_0212da5c();
        } else {
            unkfunc_02128334();
        }
        REG_GFX_FIFO_TEXTURE_PARAM = 0;
        REG_GFX_FIFO_MATRIX_IDENTITY = 0;
        REG_GFX_FIFO_VERTEX_COLOR = s_fadeQuad.col;
        REG_GFX_FIFO_POLYGON_ATTR = 0x3f0000c0 | (alpha << 16);
        int w = s_fadeQuad.w;
        int h = s_fadeQuad.h;
        func_0207eca8(s_fadeQuad.x, s_fadeQuad.y, s_fadeQuad.z, w, h, 0, 0, w, h);
    }
    if (s_fadeState == 2) {
        if (s_fadeMode == 0) {
            s_fadeState = 0;
        } else if (s_fadeMode == 1) {
            s_fadeState = 3;
        }
    }
}

// ---------------------------------------------------------------------------
// miniGame0

void set_pMGArg(ST_MG_ARG* pMGArg)
{
    pMiniGameArg = pMGArg;
}

ST_MG_ARG* get_pMGArg()
{
    return pMiniGameArg;
}

int unkfunc_021284a4()
{
    return s_playerSprite[get_pMGArg()->slTouch.player];
}

// ---------------------------------------------------------------------------
// miniGame2

void bg_manage(BG_MANAGE bgManage)
{
    if (bgManage == BG_init) {
        return;
    }
    if (bgManage == BG_draw) {
        if (s_bgDisp == 0) {
            return;
        }
        if (s_bgDataId[0] == 0) {
            s_bgDataId[0] = sprite_data_load(900, 0);
            s_bgDataId[1] = sprite_data_load(901, 0);
            s_bgSprite[0] = sprite_create(s_bgDataId[0]);
            s_bgSprite[1] = sprite_create(s_bgDataId[1]);
        }
        if (MG_IsUpScreen()) {
            SPRITE* spr = s_bgSprite[0];
            spr->z = 0;
            spr->y = 0;
            sprite_draw(spr, -1);
            spr = s_bgSprite[1];
            spr->x = 0;
            spr->z = 0;
            spr->y = 128;
            sprite_draw(spr, -1);
        } else {
            SPRITE* spr = s_bgSprite[1];
            spr->x = 0;
            spr->z = 0;
            spr->y = -65;
            sprite_draw(spr, -1);
            for (int i = 0; i < 15; i++) {
                UnkBgRect* rect = &s_bgRect[i];
                int x = rect->x;
                int y = rect->y;
                spr = s_bgSprite[1];
                spr->x = x;
                spr->y = y - 65 + rect->ofsY;
                spr->z = rect->z;
                sprite_draw_rect(spr, x, y, x + rect->w, y + rect->h);
            }
        }
    } else if (bgManage == BG_term) {
        s_bgDisp ^= 1;
    }
}

static void MiniGame2_init()
{
    unkfunc_02128c0c();
    unkfunc_021280a4();
    unkfunc_0212d458();
    unkfunc_02128d7c();
    unkfunc_0212e168();
    s_pause = 0;
    s_passFrame = FX32_ONE;
    s_playTime = 0;
    bg_manage(BG_init);
    sideInfo_init();
    unkfunc_02128268();
    if (s_ssaEffInit == 0) {
        s_ssaEffInit = 1;
        ssa_eff_init();
    }
    unkfunc_02128fc4();
    *(vu16*)0x05000000 = 0;
    *(vu16*)0x05000400 = 0;
    func_02080350(0, 0, -FX32_ONE, 0);
    func_02080380(0, 0x7fff);
    func_02075ecc(0, 31, 0x7fff, 0, 0);
    unkfunc_02128f68();
    int bgm = 31;
    if (get_pMGArg()->slTouch.dbStage > 99) {
        bgm = 28;
    }
    SoundManager::play(bgm, 15);
}

void unkfunc_0212873c()
{
    func_02089e40(0x60000, -0x60000, -0x80000, 0x80000, -0x400000, 0x400000, FX32_ONE, &data_02124bb4.projMtx);
    data_02124bb4.flag &= ~0x50;
    func_02088dd0(&data_02124bb4.cameraMtx, FX_SinIdx(s_cameraAngle), FX_CosIdx(s_cameraAngle));
    if (MG_IsUpScreen()) {
        data_02124bb4.cameraMtx.m[3][1] = -0x60000;
    } else {
        data_02124bb4.cameraMtx.m[3][1] = 0x60000;
    }
}

int unkfunc_021287f4()
{
    unkfunc_02128c04();
    return 0;
}

BOOL chk_touchPad(int* x, int* y)
{
    if (!MG_IsUpScreen()) {
        unkfunc_02128108();
        if (s_touchTrg) {
            *x = s_touchPos.x;
            *y = s_touchPos.y;
            return TRUE;
        }
    }
    return FALSE;
}

bool MiniGame2(MG2_STATE* pMG2State)
{
    func_020885e0();
    if (*pMG2State == MG2_init) {
        MiniGame2_init();
        *pMG2State = MG2_fadeIn;
        func_020885e0();
        return false;
    }
    if (*pMG2State == MG2_init2) {
        MiniGame2_init();
        *pMG2State = MG2_gameStart;
        func_020885e0();
    }
    unkfunc_02128f68();
    if (unkfunc_021287f4()) {
        return true;
    }
    unkfunc_0212873c();
    if (s_pause == 0) {
        int side = get_sideUp();
        MG2_STATE state = *pMG2State;
        if (state == MG2_fadeIn) {
            unkfunc_0212826c(0, 0, 0x3c000);
            *pMG2State = MG2_wait_end_fadeIn;
        } else if (state == MG2_wait_end_fadeIn) {
            unkfunc_0212829c(s_passFrame);
            if (unkfunc_02128314()) {
                *pMG2State = MG2_gameStart;
            }
        } else if (state == MG2_gameStart) {
            slime_set_obj(side, 14, KIND_gameStart)->disp = 1;
            *pMG2State = MG2_wait_end_gameStart;
        } else if (state == MG2_wait_end_gameStart) {
            sideInfo_slime_update_ex(s_passFrame, 14, 15);
            ST_SLIME* pSlime = get_pSlime(side, 14);
            if (pSlime->disp == 0) {
                *pMG2State = MG2_gameLoop;
                slime_cg_Release(pSlime);
                SoundManager::playSe(300, 0);
            }
        } else if (state == MG2_gameLoop) {
            sideInfo_slime_chk_add(s_passFrame);
            int x;
            int y;
            if (chk_touchPad(&x, &y)) {
                sideInfo_slime_chk_touch(x, y);
            }
            sideInfo_slime_update_ex(s_passFrame, 0, 17);
            sideInfo_update(s_passFrame);
            s_playTime += s_passFrame;
            switch (sideInfo_get_gameST(side)) {
            case 3:
                *pMG2State = MG2_fadeOut;
                SoundManager::stop(15);
                break;
            case 2:
                *pMG2State = MG2_gameOver;
                SoundManager::stop(15);
                break;
            }
        } else if (state == MG2_gameOver) {
            if (bakudanIwa_bakuhatsu(side, s_passFrame)) {
                slime_set_obj(side, 15, KIND_gameOver)->disp = 1;
                *pMG2State = MG2_wait_end_gameOver;
            }
        } else if (state == MG2_wait_end_gameOver) {
            sideInfo_slime_update_ex(s_passFrame, 15, 16);
            ST_SLIME* pSlime = get_pSlime(side, 15);
            if (pSlime->disp == 0) {
                *pMG2State = MG2_fadeOut;
                slime_cg_Release(pSlime);
            }
        } else if (state == MG2_fadeOut) {
            unkfunc_0212826c(1, 0, 0x3c000);
            *pMG2State = MG2_wait_end_fadeOut;
        } else if (state == MG2_wait_end_fadeOut) {
            unkfunc_0212829c(s_passFrame);
            if (unkfunc_02128314()) {
                int side = get_sideUp();
                ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
                get_pMGArg()->slTouch.score = pSideInfo->tokuten;
                get_pMGArg()->slTouch.stage = pSideInfo->stage;
                int gameClear = 0;
                if (sideInfo_get_gameST(side) == 3) {
                    gameClear = 1;
                }
                get_pMGArg()->slTouch.gameClear = gameClear;
                for (int i = 0; i < 17; i++) {
                    get_pMGArg()->slTouch.item[i] = pSideInfo->item[i];
                }
                return true;
            }
        }
    }
    if (*pMG2State > MG2_init) {
        if (s_firstFrame == 0) {
            s_firstFrame = 1;
        } else {
            bg_manage(BG_draw);
            sideInfo_draw(*pMG2State);
            sideInfo_slime_draw();
            ssa_eff_update(MG_IsUpScreen());
            unkfunc_02128394(0);
            set_drawFin();
        }
    }
    if (!MG_IsUpScreen()) {
        updateCnt_downScr--;
    }
    return false;
}

// ---------------------------------------------------------------------------
// miniGameSystem

int unkfunc_02128c04()
{
    return 0;
}

void unkfunc_02128c0c()
{
    void* heap = *unkfunc_02128060();
    func_0207ebe4(&s_allocator, (int)heap, 32);
    s_pAllocator = &s_allocator;
    func_0207e968(heap, 1);
}

NNSFndAllocator* unkfunc_02128c4c()
{
    return s_pAllocator;
}

void* unkfunc_02128c5c(u32 size)
{
    return func_0207ebcc(s_pAllocator, size);
}

void unkfunc_02128c78(void* memBlock)
{
    func_0207ebd8(s_pAllocator, memBlock);
}

void* MG_LoadFile(const char* _path, u32* size)
{
    FSFile file;
    char path[128];
    void* data;
    sprintf(path, "/data/%s", _path);
    func_02073868(&file);
    if (func_02073a3c(&file, path)) {
        u32 len = file.endRomOffset - file.startRomOffset;
        data = unkfunc_02128c5c(len);
        if (data) {
            if (len != func_02073b58(&file, data, len)) {
                unkfunc_02128c78(data);
                data = NULL;
            }
        }
        func_02073a68(&file);
        if (size) {
            *size = len;
        }
    }
    return data;
}

void unkfunc_02128d2c(const char* path, void** pFile, NNSG3dResMdl** pMdl)
{
    void* file = MG_LoadFile(path, NULL);
    if (pFile) {
        *pFile = file;
    }
    if (pMdl) {
        func_020827d0(file);
        *pMdl = unkGetMdl(func_02083268(file));
    }
}

u64 unkfunc_02128d7c()
{
    unsigned int buffer[8];
    u64 digest[2];
    OS_GetLowEntropyData(buffer);
    func_0208a920(digest, buffer, sizeof(buffer));
    u64 seed = digest[0] ^ digest[1];
    seed ^= (seed << 32) | (seed >> 32);
    MATH_InitRand32(&s_rand32, seed);
    MATH_InitRand16(&s_rand16, MATH_Rand32(&s_rand32, 0));
    return seed;
}

u32 rand32_min_max(u32 min, u32 max)
{
    u32 range = max - min;
    if (range == 0) {
        return min;
    }
    return min + rand32(range + 1);
}

int randSel_intTable(int* pProbability, int num)
{
    int bunbo = 0;
    int i;
    for (i = 0; i < num; i++) {
        bunbo += pProbability[i];
    }
    if (bunbo > 0) {
        int rand = rand32(bunbo);
        for (i = 0; i < num; i++) {
            rand -= pProbability[i];
            if (rand < 0) {
                return i;
            }
        }
    }
    return 0;
}

bool MG_IsUpScreen()
{
    return ((REG_POWER_CNT & 0x8000) >> 15) == 0;
}

void set_drawFin()
{
    s_drawFin = 1;
}

void unkfunc_02128f68()
{
    u16 cont = PAD_Read();
    s_pad.trg = cont & (cont ^ s_pad.cont);
    s_pad.release = s_pad.cont & (cont ^ s_pad.cont);
    s_pad.cont = cont;
}

void unkfunc_02128fc4()
{
}

// ---------------------------------------------------------------------------
// side_info

int get_iwaSpdNormal()
{
    static int iwaSpdNormal = 1;
    return iwaSpdNormal;
}

int get_sideUp()
{
    return 0;
}

ST_SIDE_INFO* get_pSideInfo(int side)
{
    switch (side) {
    case 0:
        return &sideInfo[0];
    default:
        return &sideInfo[0];
    }
}

ST_SLIME* get_pSlime(int side, int id)
{
    if (id >= 0 && id < 17) {
        ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
        if (pSideInfo) {
            return &pSideInfo->slime[id];
        }
    }
    return sideInfo[0].slime;
}

KIND get_normaSlimeKind(int side, int offset)
{
    KIND normaSlimeKind = KIND_null;
    if (offset < 0) {
        offset = get_pSideInfo(side)->clrSlime;
    }
    if (offset >= 0 && offset < 4) {
        ST_SLIME* pSlime = get_pSlime(side, offset + 8);
        switch (pSlime->kind) {
        case KIND_board_sl:
            normaSlimeKind = KIND_slime;
            break;
        case KIND_board_bs:
            normaSlimeKind = KIND_slimeBes;
            break;
        case KIND_board_mt:
            normaSlimeKind = KIND_metalSlime;
            break;
        default:
            normaSlimeKind = KIND_null;
            break;
        }
    }
    if (normaSlimeKind == KIND_null) {
        get_pSideInfo(side);
    }
    return normaSlimeKind;
}

int get_id_pSlime(ST_SLIME* pSlime)
{
    return pSlime - sideInfo[0].slime;
}

void sideInfo_init()
{
    static int s_sideInfoInit;
    if (s_sideInfoInit == 0) {
        s_sideInfoInit = 1;
        unkfunc_0212b42c();
        slime_sprite_init();
    }
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(0);
    pSideInfo->stage = 1;
    pSideInfo->clrSlime = 4;
    pSideInfo->clrNorma = 0;
    pSideInfo->tokuten = 0;
    pSideInfo->iwaSpd = get_iwaSpdNormal();
    pSideInfo->iwaSpd2 = get_iwaSpdNormal();
    pSideInfo->iwaPos = 0;
    pSideInfo->noMissCnt = 0;
    pSideInfo->noMissNormaCnt = 0;
    pSideInfo->noMissStageCnt = 0;
    pSideInfo->normaSt = 0;
    pSideInfo->gameClear = 0;
    pSideInfo->iwaReturn = 0;
    pSideInfo->absoluteCnt = 0;
    int i;
    for (i = 0; i < 4; i++) {
        pSideInfo->absoluteBuf[i] = 0;
    }
    for (i = 0; i < 17; i++) {
        pSideInfo->item[i] = 0;
    }
    pSideInfo->bgmChange = 0;
    pSideInfo->appearWait = 0;
    pSideInfo->stageClearWait = 0;
    pSideInfo->bgmChangeWait = 0;
    slime_init(0, s_sideInfoInit);
    slime_set_bakudanIwa(0);
    slime_set_player(0);
    slime_set_obj(0, 16, KIND_ase)->disp = 0;
}

void sideInfo_update(fx32 passFrame)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(0);
    pSideInfo->appearWait -= passFrame;
}

/* not original: without it wait * 255 and the quotient's high word swap ip and lr */
#pragma push
#pragma opt_common_subs off
static int get_stageClear_alpha(fx32 wait, int disp_clear, int* px)
{
    int alpha;
    wait *= 255;
    wait /= 240 * FX32_ONE;
    wait *= 255;
    fx16 cos = FX_CosIdx((u16)wait);
    fx16 sin = FX_SinIdx((u16)wait);
    sin = sin < 0 ? -sin : sin;
    alpha = sin * 63 >> FX32_SHIFT;
    if (alpha < 1) {
        alpha = 1;
    } else if (alpha > 31) {
        alpha = 31;
    }
    int x = (31 - alpha) * 4;
    if (cos < 0) {
        x *= -1;
    }
    if (disp_clear == 0) {
        x *= -1;
    }
    *px = x;
    return alpha;
}
#pragma pop

static void bakudanIwa_return(int side)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    if (pSideInfo->iwaReturn == 0) {
        pSideInfo->iwaReturn = 1;
        pSideInfo->iwaSpd = -64;
    }
}

static void sideInfo_draw_downScr_clearStage_sub(fx32 stageClearWait, int disp_clear, int x, int y, int stage)
{
    int xx;
    int alpha = get_stageClear_alpha(stageClearWait, disp_clear, &xx);
    int yy = -1;
    fx32 sclY = FX32_ONE;
    if (disp_clear == 0) {
        xx = 0;
        if (stageClearWait < 0x10000) {
            fx32 t = FX_Divide(stageClearWait, 0x10000);
            alpha = t * 31 >> FX32_SHIFT;
            yy = (FX32_ONE - t) * 80 >> FX32_SHIFT;
        } else if (stageClearWait > 0x72000) {
            fx32 t = FX_Divide(stageClearWait - 0x72000, 0x6000);
            sclY = FX32_ONE - t;
            alpha = sclY * 31 >> FX32_SHIFT;
        } else {
            alpha = 31;
        }
    }
    if (alpha > 0 && sclY > 0) {
        draw_stage_clear(x + xx, y, stage, disp_clear, alpha, yy, sclY);
    }
}

static BOOL chk_kemuri(ST_SIDE_INFO* pSideInfo)
{
    return ssa_eff_chk(pSideInfo->kemuri_play_id, 2);
}

static void sideInfo_draw_downScr_clearStage(int side)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    int stage = pSideInfo->stage;
    int disp_clear = 1;
    int bgm = 0;
    if (pSideInfo->stageClearWait > 0x78000) {
        s_clearStageRestart = 1;
        pSideInfo->stageClearWait = 0x78000;
    } else {
        if (pSideInfo->noMissStageCnt >= 5) {
            stage = stage * 1000;
            bgm = 28;
        } else {
            if (stage >= 1000) {
                pSideInfo->stage = stage / 1000;
                stage = pSideInfo->stage;
                bgm = 31;
            }
            stage = stage + 1;
        }
        if (s_clearStageRestart == 1) {
            pSideInfo->stageClearWait = 0x78000;
            s_clearStageRestart = 0;
            pSideInfo->bgmChange = bgm;
        }
        disp_clear = 0;
    }
    if (stage > 99 && stage < 1000) {
        return;
    }
    int x = s_clearStageX2;
    int y = s_clearStageY;
    ST_SLIME* pSlime = get_pSlime(side, 12);
    if (disp_clear == 0) {
        x = s_clearStageX;
        if (pSlime->kind == KIND_bakudanIwa) {
            bakudanIwa_return(side);
        }
    }
    if (pSideInfo->iwaReturn == 1) {
        pSideInfo->stageClearWait = 0x78000;
        return;
    }
    if (chk_kemuri(pSideInfo)) {
        return;
    }
    if (pSideInfo->bgmChange) {
        SoundManager::play(pSideInfo->bgmChange, 15);
        pSideInfo->bgmChange = 0;
        pSideInfo->bgmChangeWait = 0xc000;
        pSideInfo->stageClearWait = 0x78000;
    }
    if (stage >= 1000) {
        x -= 6;
    } else if (stage >= 10) {
        x += s_clearStageDx;
    }
    sideInfo_draw_downScr_clearStage_sub(pSideInfo->stageClearWait, disp_clear, x, y, stage);
}

static void sideInfo_draw_downScr(MG2_STATE mg2State)
{
    int side = 0;
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    if (mg2State == MG2_gameLoop && pSideInfo->normaSt == 0) {
        if (pSideInfo->stageClearWait == 0) {
            bakudanIwa_return(side);
        } else {
            sideInfo_draw_downScr_clearStage(side);
        }
    }
}

void sideInfo_draw(MG2_STATE mg2State)
{
    if (MG_IsUpScreen()) {
        ST_SIDE_INFO* pSideInfo = get_pSideInfo(0);
        int stage = pSideInfo->stage;
        int tokuten = pSideInfo->tokuten;
        if (stage > 99) {
            stage = stage / 1000;
        }
        draw_stage_num(stage);
        draw_score_ex(tokuten, 0, 0, 0, 0);
    } else {
        sideInfo_draw_downScr(mg2State);
    }
}

void unkfunc_021295f4(const char* str, int slime)
{
    int i;
    for (i = 7; i >= 1; i--) {
        s_scoreMessage[i] = s_scoreMessage[i - 1];
    }
    s_scoreMessage[i].str = str;
    s_scoreMessage[i].slime = slime;
    s_scoreMessage[i].wait = 120;
}

int sideInfo_stage_add_ex(int side, int val, int opt)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    int stage = pSideInfo->stage + val;
    if (stage < 1000) {
        if (stage < 1) {
            if (opt == 0) {
                stage = 1;
            } else {
                stage = 99;
            }
        } else if (stage > 99) {
            if (opt != 0) {
                stage = 1;
            } else {
                pSideInfo->gameClear = 1;
                pSideInfo->iwaSpd = 0;
                pSideInfo->iwaSpd2 = 0;
                stage = 99;
            }
        }
        pSideInfo->stage = stage;
    }
    return stage;
}

int sideInfo_taoshita_inc(int side, KIND kind, int* pBonusPoint, int* pAddScore)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    int stage = pSideInfo->stage;
    int taoshita = 0;
    int addScore = get_kind_data(kind, 3);
    int bonusPoint = -1;
    int bonusPointIwa = -1;
    if (kind >= 4) {
        int offset = kind - 4;
        if (offset >= 0 && offset < 17) {
            pSideInfo->item[offset]++;
            if (pSideInfo->item[offset] > 99) {
                pSideInfo->item[offset] = 99;
            }
        }
    } else {
        int normaSlimeKind = get_normaSlimeKind(side, -1);
        if (normaSlimeKind) {
            if (kind == normaSlimeKind) {
                taoshita = 2;
                pSideInfo->clrSlime++;
                pSideInfo->noMissCnt++;
                if (pSideInfo->clrSlime >= 4) {
                    pSideInfo->clrNorma++;
                    taoshita = 3;
                    bonusPointIwa = get_bonusPointIwa(side);
                    pSideInfo->iwaSpd2 = pSideInfo->iwaSpd;
                    pSideInfo->iwaSpd = 0;
                    if (pSideInfo->clrSlime <= pSideInfo->noMissCnt) {
                        pSideInfo->noMissCnt = 0;
                        bonusPoint = get_stage_data(stage, 9);
                        pSideInfo->noMissNormaCnt++;
                    }
                    int clrNorma = pSideInfo->clrNorma;
                    if (get_stage_data(stage, 1) <= clrNorma) {
                        taoshita = 4;
                        if (clrNorma <= pSideInfo->noMissNormaCnt) {
                            pSideInfo->noMissNormaCnt = 0;
                            pSideInfo->noMissStageCnt++;
                        }
                        pSideInfo->stageClearWait = 0xf0000;
                    }
                }
            } else {
                pSideInfo->noMissCnt = 0;
                pSideInfo->noMissNormaCnt = 0;
                pSideInfo->noMissStageCnt = 0;
                addScore *= taoshita - 1;
                taoshita = 1;
            }
        }
    }
    int tokuten = pSideInfo->tokuten + addScore;
    if (bonusPoint > 0) {
        tokuten += bonusPoint;
    }
    if (bonusPointIwa > 0) {
        tokuten += bonusPointIwa;
    }
    if (tokuten < -999999) {
        tokuten = -999999;
    } else if (tokuten > 999999) {
        tokuten = 999999;
    }
    pSideInfo->tokuten = tokuten;
    if (pAddScore) {
        *pAddScore = addScore;
    }
    if (pBonusPoint) {
        *pBonusPoint = bonusPoint;
    }
    return taoshita;
}

int sideInfo_nigashita_inc(int side, KIND kind)
{
    int nigashita = 0;
    if (kind < 4) {
        int normaSlimeKind = get_normaSlimeKind(side, -1);
        if (normaSlimeKind) {
            if (kind != normaSlimeKind) {
                nigashita = 2;
            } else {
                nigashita = 1;
                get_pSideInfo(side);
            }
        }
    }
    return nigashita;
}

void sideInfo_slime_chk_add(fx32 passFrame)
{
    slime_chk_add(0, passFrame);
}

void sideInfo_slime_chk_touch(int x, int y)
{
    slime_chk_touch(0, x, y);
}

void sideInfo_slime_update_ex(fx32 passFrame, int start, int end)
{
    slime_update_ex(0, passFrame, start, end);
}

void sideInfo_slime_draw()
{
    MtxFx33 rot;
    MtxFx33 rotx;
    MtxFx33 nrotx;
    MtxFx33 Irot;
    func_02088970(&rot);
    if (MG_IsUpScreen()) {
        func_02088a70(&rot, FX_SinIdx(0x8000), FX_CosIdx(0x8000));
    }
    func_02088970(&rotx);
    func_02088a54(&rotx, FX_SinIdx((u16)s_rotxAngle), FX_CosIdx((u16)s_rotxAngle));
    MTX_Concat33(&rotx, &rotx, &rot);
    func_02088970(&nrotx);
    func_02088a54(&nrotx, FX_SinIdx((u16)s_nrotxAngle), FX_CosIdx((u16)s_nrotxAngle));
    MTX_Concat33(&nrotx, &nrotx, &rot);
    func_02088970(&Irot);
    if (MG_IsUpScreen()) {
        slime_draw(0, &Irot, 12, 13);
        slime_draw(0, &Irot, 13, 14);
        slime_draw(0, &Irot, 16, 17);
    } else {
        slime_draw(0, &rotx, 0, 8);
        slime_draw(0, &nrotx, 8, 12);
        slime_draw(0, &Irot, 14, 15);
        slime_draw(0, &Irot, 15, 16);
    }
}

int sideInfo_get_gameST(int side)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    if (pSideInfo->iwaPos == 2) {
        return 2;
    }
    if (pSideInfo->gameClear) {
        return 3;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// slime

void slime_init(int side, int init)
{
    for (int i = 0; i < 17; i++) {
        ST_SLIME* pSlime = get_pSlime(side, i);
        pSlime->kind = KIND_null;
        if (init == 0) {
            pSlime->renderObj = NULL;
            for (int j = 0; j < 4; j++) {
                pSlime->anmObj[j] = NULL;
                pSlime->anmFrame[j] = 0;
            }
            pSlime->anmSeWait = -1;
            pSlime->anmSe = 0;
            pSlime->anmNum = 0;
            pSlime->sprite = NULL;
        }
    }
}

static int slime_get_cnt(int side, u32* use_map)
{
    u32 mask = 0xff;
    if (use_map && *use_map) {
        mask = *use_map;
    }
    int cnt = 0;
    u32 map = 0;
    for (int i = 0; i < 17; i++) {
        if (mask & (1 << i)) {
            ST_SLIME* pSlime = get_pSlime(side, i);
            if (pSlime->kind) {
                map |= 1 << i;
                cnt++;
            }
        }
    }
    if (use_map) {
        *use_map = map;
    }
    return cnt;
}

static int _rand_sel32(u32 bit_map, int banme)
{
    if (bit_map) {
        if (banme < 0) {
            int cnt = 0;
            for (int i = 0; i < 32; i++) {
                if (bit_map & (1 << i)) {
                    cnt++;
                }
            }
            banme = rand16(cnt);
        }
        int cnt = 0;
        for (int i = 0; i < 32; i++) {
            if (bit_map & (1 << i)) {
                if (banme == cnt) {
                    return i;
                }
                cnt++;
            }
        }
    }
    return 0;
}

static int get_anmNum(KIND kind, SLIME_MOVE move)
{
    int anmNum = 0;
    switch (move) {
    case MOVE_up:
        anmNum = get_kind_anmNum(kind, MOVE_up);
        break;
    case MOVE_norma2_wait:
        break;
    case MOVE_norma2_up:
        anmNum = 1;
        break;
    }
    return anmNum;
}

static void slime_set(ST_SLIME* pSlime, KIND kind, VecFx32* trans, SLIME_MOVE move)
{
    int anmNum = get_anmNum(kind, move);
    slime_cg_set(pSlime, kind, anmNum);
    pSlime->trans.x = trans->x;
    pSlime->trans.y = trans->y;
    pSlime->trans.z = trans->z;
    pSlime->frame = 0;
    pSlime->frameMax = 0x7fffffff;
    pSlime->kind = kind;
    pSlime->tp = get_kind_data(kind, 2);
    pSlime->alpha = 31;
    pSlime->dAlpha = 0;
    pSlime->move = move;
    pSlime->addScore = 0;
    pSlime->touchX = 0;
    pSlime->touchY = 0;
    pSlime->taoshita = 0;
    pSlime->bonusPoint = -1;
    pSlime->damageAnmOffset = 0;
    pSlime->disp = 1;
    pSlime->col = 0x7fff;
    pSlime->rotZ = 0;
}

static void slime_set_norma(int side, int stage)
{
    for (int i = 8; i < 12; i++) {
        ST_SLIME* pSlime = get_pSlime(side, i);
        if (stage > 99) {
            pSlime->kind = KIND_null;
            pSlime->disp = 0;
        } else {
            KIND kind = get_normaKind_from_stage_data(stage);
            if (kind) {
                slime_set(pSlime, kind, &obj_data[i].trans, obj_data[i].move);
                pSlime->frameMax = (i - 8) << 14;
                pSlime->rotZ = 0x4000;
            }
        }
    }
}

ST_SLIME* slime_set_obj(int side, int id, KIND kind)
{
    ST_SLIME* pSlime = get_pSlime(side, id);
    slime_set(pSlime, kind, &obj_data[id].trans, obj_data[id].move);
    return pSlime;
}

void slime_set_bakudanIwa(int side)
{
    int id = 12;
    KIND kind = KIND_bakudanIwa;
    slime_set_obj(side, id, kind);
}

void slime_set_player(int side)
{
    int id = 13;
    KIND kind = KIND_player;
    slime_set_obj(side, id, kind);
}

static void set_absoluteCnt_Buf(ST_SIDE_INFO* pSideInfo)
{
    pSideInfo->absoluteCnt = 0;
    for (int i = 0; i < 4; i++) {
        pSideInfo->absoluteBuf[i] = 0;
    }
    int stage = pSideInfo->stage;
    int absoluteMin = get_stage_data(stage, 12);
    int absoluteMax = get_stage_data(stage, 13);
    if (absoluteMin * absoluteMax != 0) {
        int dAbsolute = absoluteMax - absoluteMin;
        if (dAbsolute >= 3) {
            for (int i = 0; i < 4; i++) {
                pSideInfo->absoluteBuf[i] = absoluteMin + rand32(dAbsolute + 1);
            }
            for (int i = 0; i < 3; i++) {
                for (int j = i + 1; j < 4; j++) {
                    if (pSideInfo->absoluteBuf[i] > pSideInfo->absoluteBuf[j]) {
                        int sw = pSideInfo->absoluteBuf[i];
                        pSideInfo->absoluteBuf[i] = pSideInfo->absoluteBuf[j];
                        pSideInfo->absoluteBuf[j] = sw;
                    } else if (pSideInfo->absoluteBuf[i] == pSideInfo->absoluteBuf[j]) {
                        pSideInfo->absoluteBuf[j]++;
                        if (absoluteMax < pSideInfo->absoluteBuf[j]) {
                            pSideInfo->absoluteBuf[j] = pSideInfo->absoluteBuf[i];
                            if (i == 0) {
                                pSideInfo->absoluteBuf[i] = absoluteMin;
                            } else {
                                pSideInfo->absoluteBuf[i] = pSideInfo->absoluteBuf[i - 1] + 1;
                                if (pSideInfo->absoluteBuf[i] == pSideInfo->absoluteBuf[j]) {
                                    pSideInfo->absoluteBuf[i] = absoluteMin;
                                    i = -1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

static int bakudanIwa_kemuri_on(fx32 iwaTransX)
{
    int x = (iwaTransX >> FX32_SHIFT) + 22;
    int y = 176;
    int play_id = ssa_eff_start(2, x, y, FX32_ONE, 32);
    SoundManager::playSe(0x217, 0);
    return play_id;
}

static int add_normaSlime(int side, fx32 passFrame)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    if (pSideInfo->stageClearWait) {
        if (pSideInfo->bgmChangeWait > 0) {
            pSideInfo->bgmChangeWait -= passFrame;
        } else if (pSideInfo->iwaReturn != 1) {
            pSideInfo->stageClearWait -= passFrame;
        }
        if (pSideInfo->stageClearWait > 0) {
            return 0;
        }
        if (pSideInfo->noMissStageCnt >= 5) {
            pSideInfo->noMissStageCnt = 0;
            pSideInfo->stage = pSideInfo->stage * 1000;
        } else {
            sideInfo_stage_add_ex(side, 1, 0);
        }
        pSideInfo->appearWait = 0;
        pSideInfo->stageClearWait = 0;
        pSideInfo->clrNorma = 0;
    }
    if (sideInfo_get_gameST(side) == 3) {
        pSideInfo->clrSlime = 4;
        return 0;
    }
    if (pSideInfo->iwaReturn == 1) {
        return 0;
    }
    slime_set_norma(side, pSideInfo->stage);
    pSideInfo->clrSlime = 0;
    pSideInfo->appearWait = 0x1e000;
    pSideInfo->iwaSpd = pSideInfo->iwaSpd2;
    pSideInfo->iwaReturn = 3;
    set_absoluteCnt_Buf(pSideInfo);
    return 1;
}

static BOOL chk_normaSlime_move(int side, SLIME_MOVE move)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    if (pSideInfo->clrSlime < 4) {
        return FALSE;
    }
    for (int i = 8; i < 12; i++) {
        ST_SLIME* pSlime = get_pSlime(side, i);
        if (pSlime->kind == KIND_null) {
            return FALSE;
        }
        if (move != pSlime->move) {
            return FALSE;
        }
    }
    return TRUE;
}

static void slime_chk_add_norma(int side, fx32 passFrame)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    if (pSideInfo->normaSt == 0) {
        if (add_normaSlime(side, passFrame)) {
            pSideInfo->normaSt = 1;
        }
    } else if (pSideInfo->normaSt == 1) {
        if (chk_normaSlime_move(side, MOVE_norma2_down2)) {
            for (int i = 8; i < 12; i++) {
                ST_SLIME* pSlime = get_pSlime(side, i);
                pSlime->move = MOVE_norma2_down3;
                slime_cg_set(pSlime, pSlime->kind, 5);
            }
            pSideInfo->normaSt = 2;
        }
    } else {
        if (chk_normaSlime_move(side, MOVE_norma2_end)) {
            pSideInfo->normaSt = 0;
        }
    }
}

void slime_chk_add(int side, fx32 passFrame)
{
    slime_chk_add_norma(side, passFrame);
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    int stage = pSideInfo->stage;
    if (pSideInfo->iwaReturn == 3 && pSideInfo->appearWait <= 0) {
        pSideInfo->iwaReturn = 0;
        ST_SLIME* pSlime = get_pSlime(side, 12);
        KIND oldKind;
        KIND newKind = KIND_bakudanIwa;
        if (stage > 99) {
            newKind = KIND_odoruHouseki;
        }
        oldKind = pSlime->kind;
        slime_set_obj(side, 12, newKind);
        int alpha = 31;
        int dAlpha = 0;
        if (oldKind != newKind) {
            fx32 iwaTransX = pSlime->trans.x;
            bakudanIwa_kemuri_on(iwaTransX);
            alpha = 1;
            dAlpha = 1;
        }
        pSlime->alpha = alpha;
        pSlime->dAlpha = dAlpha;
    }
    if (pSideInfo->clrSlime >= 4) {
        return;
    }
    if (pSideInfo->stageClearWait) {
        return;
    }
    if (pSideInfo->appearWait > 0) {
        return;
    }
    pSideInfo->appearWait = get_time_from_stage_data(stage);
    int addMax = get_stage_data(stage, 3);
    int allMax = get_stage_data(stage, 2);
    for (int i = 0; i < addMax; i++) {
        u32 use_map = 0;
        int cnt = slime_get_cnt(side, &use_map);
        if (allMax <= cnt) {
            return;
        }
        KIND kind = KIND_null;
        if (kind == KIND_null) {
            pSideInfo->absoluteCnt++;
            for (int j = 0; j < 4; j++) {
                if (pSideInfo->absoluteCnt == pSideInfo->absoluteBuf[j]) {
                    kind = get_normaSlimeKind(side, j);
                    break;
                }
            }
            if (kind == KIND_null) {
                kind = get_kind_from_stage_data(stage);
            }
        }
        if (kind) {
            int id = _rand_sel32(use_map ^ 0xff, -1);
            if (id >= 0) {
                ST_SLIME* pSlime = get_pSlime(side, id);
                slime_set(pSlime, kind, &obj_data[id].trans, obj_data[id].move);
                pSlime->frameMax = 0x7fffffff;
            }
        }
    }
}

void get_slime_scr_xy(ST_SLIME* pSlime, int* px, int* py, int opt)
{
    *px = pSlime->trans.x >> FX32_SHIFT;
    *py = pSlime->trans.y >> FX32_SHIFT;
}

static int chk_hit(int x, int y, ST_SLIME* pSlime)
{
    int hit = 0;
    int px;
    int py;
    get_slime_scr_xy(pSlime, &px, &py, 0);
    px = px - x;
    px = px < 0 ? -px : px;
    py = py - y;
    if (px < 12 && py < 17 && py >= -3) {
        hit = 1;
    }
    return hit;
}

static void slime_anm_sub(ST_SLIME* pSlime, int anmNum, int effId, int effSe, int anmSe, fx32 anmSeWait)
{
    slime_cg_set(pSlime, pSlime->kind, anmNum);
    int px = pSlime->touchX;
    int py = pSlime->touchY;
    if (effId >= 0) {
        ssa_eff_start(effId, px, py, FX32_ONE, 16);
    }
    if (effSe) {
        SoundManager::playSe(effSe, 0);
    }
    if (anmSe) {
        pSlime->anmSeWait = anmSeWait;
        pSlime->anmSe = anmSe;
    }
}

static void slime_anm(ST_SLIME* pSlime, SLIME_ANM_OPT opt)
{
    struct ST_SLIME_ANM_PARM_DATA {
        int effId;
        int effSe;
        int anmNum[2];
        int anmSe;
    };
    enum SLIME_ANM_PARAM {
        SLIME_ANM_PARAM_nonNorma = 0,
        SLIME_ANM_PARAM_Norma = 1,
        SLIME_ANM_PARAM_tassei = 2,
        SLIME_ANM_PARAM_bonus = 3,
        SLIME_ANM_PARAM_MAX = 4,
    };
    static ST_SLIME_ANM_PARM_DATA slime_anm_param_data[6][4] = {
        {
            { 1, 0, { 9, 10 }, 402 },
            { 1, 0, { 9, 10 }, 402 },
            { 0, 0, { 0, 0 }, 0 },
            { 0, 0, { 0, 0 }, 0 },
        },
        {
            { 1, 0, { 9, 10 }, 402 },
            { 1, 0, { 9, 10 }, 402 },
            { 1, 0, { 9, 10 }, 402 },
            { 1, 0, { 9, 10 }, 402 },
        },
        {
            { -1, 0, { 14, 15 }, 405 },
            { -1, 0, { 14, 15 }, 0 },
            { -1, 0, { 14, 15 }, 501 },
            { -1, 0, { 14, 15 }, 501 },
        },
        {
            { 1, 0, { 14, 15 }, 405 },
            { 1, 0, { 14, 15 }, 402 },
            { 1, 0, { 14, 15 }, 402 },
            { 1, 0, { 14, 15 }, 402 },
        },
        {
            { -1, 0, { 13, 13 }, 0 },
            { 0, 0, { 0, 0 }, 0 },
            { 0, 0, { 0, 0 }, 0 },
            { 0, 0, { 0, 0 }, 0 },
        },
        {
            { 3, 0, { 0, 0 }, 324 },
            { 0, 0, { 0, 0 }, 0 },
            { 0, 0, { 0, 0 }, 0 },
            { 0, 0, { 0, 0 }, 0 },
        },
    };
    SLIME_ANM_PARAM param;
    if (opt == SLIME_ANM_OPT_force_del) {
        param = SLIME_ANM_PARAM_nonNorma;
    } else if (pSlime->kind >= KIND_chara4 && pSlime->kind <= KIND_chara20) {
        opt = SLIME_ANM_OPT_hitBonusTip;
        param = SLIME_ANM_PARAM_nonNorma;
    } else if (opt == SLIME_ANM_OPT_damage_seizon) {
        int side = get_sideUp();
        KIND normaKind = get_normaSlimeKind(side, -1);
        param = SLIME_ANM_PARAM_nonNorma;
        if (normaKind == pSlime->kind) {
            param = SLIME_ANM_PARAM_Norma;
        }
    } else if (pSlime->bonusPoint >= 0) {
        param = SLIME_ANM_PARAM_bonus;
    } else {
        param = SLIME_ANM_PARAM_Norma;
        switch (pSlime->taoshita) {
        case 1:
            param = SLIME_ANM_PARAM_nonNorma;
            break;
        case 3:
        case 4:
            param = SLIME_ANM_PARAM_tassei;
            break;
        }
    }
    ST_SLIME_ANM_PARM_DATA* pParam = &slime_anm_param_data[opt][param];
    int anmNum;
    if (pSlime->kind >= KIND_chara4) {
        SLIME_MOVE move = MOVE_die_dm;
        if (opt == SLIME_ANM_OPT_force_del) {
            move = MOVE_down;
        }
        anmNum = get_kind_anmNum(pSlime->kind, move);
    } else {
        int offset = pSlime->damageAnmOffset & 1;
        pSlime->damageAnmOffset++;
        anmNum = pParam->anmNum[offset];
    }
    fx32 anmSeWait = 0;
    int effId = pParam->effId;
    int effSe = pParam->effSe;
    if (opt != SLIME_ANM_OPT_die) {
        anmSeWait = s_effDz << FX32_SHIFT;
    }
    int anmSe = pParam->anmSe;
    slime_anm_sub(pSlime, anmNum, effId, effSe, anmSe, anmSeWait);
}

void slime_chk_touch(int side, int x, int y)
{
    for (int i = 0; i < 17; i++) {
        ST_SLIME* pSlime = get_pSlime(side, i);
        if (pSlime->kind == KIND_null) {
            continue;
        }
        if (pSlime->tp <= 0) {
            continue;
        }
        if (!(pSlime->move == MOVE_up || pSlime->move == MOVE_top || pSlime->move == MOVE_down)) {
            continue;
        }
        if (!chk_hit(x, y, pSlime)) {
            continue;
        }
        pSlime->touchX = x;
        pSlime->touchY = y;
        int damage = --pSlime->tp;
        if (damage > 0) {
            if (pSlime->move == MOVE_top) {
                fx32 max = pSlime->frameMax + get_kind_data(pSlime->kind, 6);
                if (max < pSlime->frameMax) {
                    max = 0x7fffffff;
                }
                pSlime->frameMax = max;
            }
            get_pSideInfo(side);
            slime_anm(pSlime, SLIME_ANM_OPT_damage_seizon);
        } else {
            pSlime->tp = 0;
            pSlime->move = MOVE_die_dm;
        }
    }
}

static fx32 get_bakudanIwa_spd(int side)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    int iwaSpd = pSideInfo->iwaSpd;
    fx32 stageSpd;
    if (iwaSpd < 0) {
        stageSpd = 0x199;
    } else {
        stageSpd = get_stage_data(pSideInfo->stage, 7);
    }
    return stageSpd * iwaSpd;
}

static void set_ase0_disp(int side, int disp)
{
    ST_SLIME* pAse0 = get_pSlime(side, 16);
    if (disp == pAse0->disp) {
        return;
    }
    pAse0->disp ^= 1;
    pAse0->frame = 0;
    for (int i = 0; i < 4; i++) {
        pAse0->anmFrame[i] = 0;
    }
}

void nokori_anaSlime_force_del(int side, ST_SLIME* pSlimeNonForceDel)
{
    u32 bit_map = 0xff;
    if (pSlimeNonForceDel) {
        int id = get_id_pSlime(pSlimeNonForceDel);
        bit_map = (1 << id) ^ 0xff;
    }
    for (int i = 0; i < 8; i++) {
        if (bit_map & (1 << i)) {
            ST_SLIME* pSlime = get_pSlime(side, i);
            if (pSlime->kind) {
                slime_anm(pSlime, SLIME_ANM_OPT_force_del);
                pSlime->move = MOVE_die_wait;
                pSlime->frame = 0;
                pSlime->frameMax = 0x7fffffff;
                pSlime->addScore = 0;
            }
        }
    }
}

static void slime_update_rot_bakudanIwa(ST_SLIME* pSlime, fx32 passFrame, fx32 spd)
{
    if (pSlime->kind == KIND_odoruHouseki) {
        u16 idx = pSlime->frame >> 2;
        pSlime->trans.y = 0x8a000 - (FX32_ONE - FX_CosIdx(idx)) * s_housekiAmp;
        return;
    }
    int dx = FX_Mul(spd, passFrame);
    s16 idx = dx;
    pSlime->rotZ += (s16)(idx / 4);
}

static void slime_update_trans_bakudanIwa(ST_SLIME* pSlime, fx32 passFrame, int side)
{
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    if (pSideInfo->iwaReturn == 3) {
        return;
    }
    if (pSlime->dAlpha) {
        int alpha = pSlime->alpha + pSlime->dAlpha;
        if (alpha > 31) {
            alpha = 31;
        } else if (alpha < 1) {
            alpha = 1;
        }
        if (alpha == pSlime->alpha) {
            pSlime->dAlpha = 0;
        } else {
            pSlime->alpha = alpha;
        }
    }
    fx32* pZ = &pSlime->trans.z;
    if (pSlime->move == MOVE_iwa2) {
        pZ = &pSlime->trans.x;
    }
    fx32 z = *pZ;
    fx32 spd = get_bakudanIwa_spd(side);
    z += FX_Mul(spd, passFrame);
    if (z >= 0xb2000) {
        pSlime->col = 31;
        z = 0xb2000;
        if (pSideInfo->iwaPos != 3 && pSideInfo->stage > 99) {
            pSideInfo->normaSt = 0;
            pSideInfo->stageClearWait = 0xf0000;
            pSideInfo->kemuri_play_id = bakudanIwa_kemuri_on(pSlime->trans.x);
            pSlime->alpha = 30;
            pSlime->dAlpha = -1;
            pSideInfo->iwaPos = 3;
            nokori_anaSlime_force_del(side, NULL);
        } else if (pSideInfo->iwaPos != 3) {
            pSideInfo->iwaPos = 2;
        }
        slime_update_rot_bakudanIwa(pSlime, passFrame, spd);
    } else if (z > 0x6a000) {
        pSlime->col = 0x7fff;
        if (pSideInfo->iwaSpd > 0 && (pSlime->frame & 0x8000)) {
            pSlime->col = 31;
        }
        pSideInfo->iwaPos = 1;
        set_ase0_disp(side, 1);
        slime_update_rot_bakudanIwa(pSlime, passFrame, spd);
    } else {
        if (z < 0x22000) {
            pSlime->rotZ = 0;
            pSideInfo->iwaSpd = 0;
            pSideInfo->iwaReturn = 2;
            z = 0x22000;
        } else {
            slime_update_rot_bakudanIwa(pSlime, passFrame, spd);
        }
        pSlime->col = 0x7fff;
        pSideInfo->iwaPos = 0;
        set_ase0_disp(side, 0);
    }
    *pZ = z;
    if (pSlime->kind == KIND_odoruHouseki) {
        pSlime->col = 0x7fff;
    }
}

static void slime_update_trans(ST_SLIME* pSlime, fx32 passFrame, int side)
{
    if (pSlime->move == MOVE_iwa2) {
        slime_update_trans_bakudanIwa(pSlime, passFrame, side);
    }
}

static void slime_update_frame(ST_SLIME* pSlime, fx32 passFrame)
{
    pSlime->frame += passFrame;
    if (pSlime->frame < 0) {
        pSlime->frame = 0x7fffffff;
    }
    fx32 frameMax = pSlime->frameMax;
    if (pSlime->move == MOVE_up) {
        frameMax /= 2;
    }
    if (frameMax <= 0) {
        frameMax = 0x7fffffff;
    }
    if (frameMax > pSlime->frame) {
        return;
    }
    SLIME_MOVE move = pSlime->move;
    KIND kind = pSlime->kind;
    switch (move) {
    case MOVE_up:
    case MOVE_down:
        pSlime->frame = frameMax;
        break;
    case MOVE_top:
        pSlime->frame = 0x3fffffff;
        pSlime->frameMax = 0x7fffffff;
        pSlime->move = MOVE_down;
        slime_cg_set(pSlime, kind, get_kind_anmNum(pSlime->kind, MOVE_down));
        break;
    case MOVE_norma2_wait:
        pSlime->frame = 0;
        pSlime->move = MOVE_norma2_up;
        slime_cg_set(pSlime, kind, 1);
        break;
    default:
        pSlime->frame = 0;
        break;
    }
}

static void slime_del_norma_update(int side, int taoshita)
{
    switch (taoshita) {
    case 0:
    case 1:
        return;
    }
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    int clrSlime = pSideInfo->clrSlime;
    ST_SLIME* pSlime = get_pSlime(side, clrSlime + 7);
    pSlime->move = MOVE_norma2_down;
    slime_cg_set(pSlime, pSlime->kind, 3);
}

static void slime_del(int side, ST_SLIME* pSlime)
{
    const char* str = NULL;
    int bonusPoint = -1;
    if (pSlime->tp > 0) {
        int nigashita = sideInfo_nigashita_inc(side, pSlime->kind);
        switch (nigashita) {
        case 0:
            break;
        case 1:
            str = "lost";
            break;
        case 2:
            break;
        }
    } else {
        int taoshita = sideInfo_taoshita_inc(side, pSlime->kind, &bonusPoint, &pSlime->addScore);
        pSlime->taoshita = taoshita;
        pSlime->bonusPoint = bonusPoint;
        slime_anm(pSlime, SLIME_ANM_OPT_dm_die);
        pSlime->move = MOVE_die_wait;
        pSlime->frame = 0;
        pSlime->frameMax = 0x7fffffff;
        switch (taoshita) {
        case 3:
        case 4:
            nokori_anaSlime_force_del(side, pSlime);
            break;
        }
        switch (taoshita) {
        case 4:
            str = "stUp";
            if (sideInfo_get_gameST(side) == 3) {
                str = "gameClear";
            }
            break;
        case 3:
            str = "Clear";
            break;
        case 1:
            str = "Miss";
            break;
        case 0:
        case 2:
            break;
        }
        slime_del_norma_update(side, taoshita);
    }
    if (str == NULL) {
        return;
    }
    if (bonusPoint >= 0) {
        static char bonusStr[32];
        int id = get_id_pSlime(pSlime);
        sprintf(bonusStr, "bounus %d", bonusPoint);
        unkfunc_021295f4(bonusStr, -(id + 1));
    }
    unkfunc_021295f4(str, get_id_pSlime(pSlime));
}

static fx32 hosei_passFrame(fx32 passFrame, ST_SLIME* pSlime, int side)
{
    switch (pSlime->move) {
    case MOVE_player2:
        if (get_pSideInfo(side)->iwaPos == 0) {
            passFrame /= 2;
        } else {
            passFrame *= 2;
        }
        break;
    case MOVE_gameStart:
    case MOVE_gameOver:
    case MOVE_ase:
        passFrame /= 2;
        break;
    }
    return passFrame;
}

static void slime_update_anmSe(ST_SLIME* pSlime, fx32 passFrame)
{
    if (pSlime->anmSeWait < 0) {
        return;
    }
    pSlime->anmSeWait -= passFrame;
    if (pSlime->anmSeWait > 0) {
        return;
    }
    pSlime->anmSeWait = -1;
    if (pSlime->anmSe) {
        SoundManager::playSe(pSlime->anmSe, 0);
    }
    fx32 anmSeWait;
    int anmSe = 0;
    anmSeWait = -1;
    switch (pSlime->taoshita) {
    case 4:
        anmSeWait = 0xe000;
        anmSe = 0x199;
        break;
    case 3:
        anmSeWait = 0x14000;
        anmSe = 501;
        if (pSlime->bonusPoint < 0) {
            anmSeWait = 0x14000;
        }
        break;
    }
    if (anmSe != 0 && anmSe != pSlime->anmSe) {
        pSlime->anmSe = anmSe;
        pSlime->anmSeWait = anmSeWait;
    }
}

static void slime_update_anmFrame(ST_SLIME* pSlime, fx32 passFrame)
{
    if (pSlime->disp != 1) {
        return;
    }
    int anmFin = 0;
    if (pSlime->sprite) {
        if (pSlime->sprite->ssa_id) {
            int nFrame = pSlime->sprite->nframe;
            fx32 frame = pSlime->anmFrame[0] + passFrame / 2;
            if (nFrame <= frame >> FX32_SHIFT) {
                frame = (nFrame - 1) << FX32_SHIFT;
                anmFin = 1;
            }
            pSlime->anmFrame[0] = frame;
        }
    } else {
        for (int i = 0; i < 4; i++) {
            if (pSlime->anmObj[i]) {
                pSlime->anmFrame[i] += passFrame;
                fx32 max = ((NNSG3dResAnmCommon*)pSlime->anmObj[i]->resAnm)->numFrame << FX32_SHIFT;
                if (pSlime->move == MOVE_ase) {
                    max = 0x2d000;
                }
                if (max <= pSlime->anmFrame[i]) {
                    pSlime->anmFrame[i] = 0;
                    anmFin = 1;
                }
            }
        }
    }
    if (anmFin != 1) {
        return;
    }
    SLIME_MOVE move = pSlime->move;
    KIND kind = pSlime->kind;
    switch (move) {
    case MOVE_gameStart:
    case MOVE_gameOver:
        pSlime->disp = 0;
        break;
    case MOVE_up:
        pSlime->frame = 0;
        pSlime->frameMax = get_kind_time_rand(pSlime->kind);
        pSlime->move = MOVE_top;
    case MOVE_top: {
        int anmNum = get_kind_anmNum(pSlime->kind, MOVE_top);
        if (anmNum != pSlime->anmNum) {
            slime_cg_set(pSlime, kind, anmNum);
        }
        break;
    }
    case MOVE_down:
        pSlime->frame = 0;
        pSlime->move = MOVE_down_end;
        break;
    case MOVE_die_dm_wait:
        slime_anm(pSlime, SLIME_ANM_OPT_die);
        pSlime->move = MOVE_die_wait;
        pSlime->frame = 0;
        pSlime->frameMax = 0x7fffffff;
        break;
    case MOVE_die_wait:
        if (pSlime->anmSeWait <= 0) {
            pSlime->kind = KIND_null;
            pSlime->disp = 0;
        }
        break;
    case MOVE_norma2_up:
        pSlime->move = MOVE_norma2_stand;
        slime_cg_set(pSlime, kind, 2);
        break;
    case MOVE_norma2_down:
        pSlime->move = MOVE_norma2_down2;
        slime_cg_set(pSlime, kind, 4);
        break;
    case MOVE_norma2_down3:
        pSlime->move = MOVE_norma2_end;
        slime_cg_set(pSlime, kind, 0);
        break;
    }
}

void slime_update_ex(int side, fx32 arg_passFrame, int start, int end)
{
    for (int i = start; i < end; i++) {
        ST_SLIME* pSlime = get_pSlime(side, i);
        if (pSlime->kind == KIND_null) {
            continue;
        }
        fx32 passFrame = hosei_passFrame(arg_passFrame, pSlime, side);
        if (pSlime->move == MOVE_die_dm) {
            slime_del(side, pSlime);
        }
        slime_update_anmSe(pSlime, passFrame);
        slime_update_anmFrame(pSlime, passFrame);
        slime_update_trans(pSlime, passFrame, side);
        slime_update_frame(pSlime, passFrame);
        if (pSlime->move == MOVE_down_end) {
            slime_del(side, pSlime);
            pSlime->kind = KIND_null;
            pSlime->disp = 0;
        }
    }
}

static void unkfunc_0212b0fc(ST_SLIME* pSlime, MtxFx33* rot, VecFx32* scale)
{
    func_0208032c(scale);
    NNS_G3dGlbSetBaseRot(rot);
    VecFx32 trans = pSlime->trans;
    func_02080308((dss::Fix32Vector3*)&trans);
    func_020802dc();
    G3d_Render(pSlime->renderObj);
    for (int i = 0; i < 4; i++) {
        NNSG3dAnmObj* anmObj = pSlime->anmObj[i];
        if (anmObj) {
            anmObj->frame = pSlime->anmFrame[i];
        }
    }
}

static fx32 unkfunc_0212b188(int id)
{
    fx32 scale = FX32_ONE;
    if (id >= 0 && id < 8) {
        scale = slimeScale;
    } else if (id >= 8 && id < 12) {
        scale = normaSlimeScale;
    }
    return scale;
}

static void slime_tp_draw(ST_SLIME* pSlime)
{
    int xx;
    int score = pSlime->addScore;
    if (pSlime->move == MOVE_die_wait && score != 0) {
        xx = pSlime->trans.x >> FX32_SHIFT;
        const int yy = pSlime->trans.y >> FX32_SHIFT;
        int y = yy + -32;
        int f = (pSlime->frame >> FX32_SHIFT) - s_tpFrameOfs;
        if (f < 0) {
            f = 0;
        }
        int dy = s_tpY + f * s_tpMoveMul / s_tpMoveDiv;
        int alpha = 31 - f * s_tpAlphaMul / s_tpAlphaDiv;
        if (alpha < 1) {
            alpha = 1;
        }
        draw_touch_num(xx + 8, y - dy, score, alpha);
    }
}

void slime_draw(int side, MtxFx33* rot, int start, int end)
{
    VecFx32 scale;
    for (int i = start; i < end; i++) {
        ST_SLIME* pSlime = get_pSlime(side, i);
        if (pSlime->kind == KIND_null) {
            continue;
        }
        if (pSlime->disp != 1) {
            continue;
        }
        if (pSlime->sprite) {
            slime_sprite_draw(pSlime);
        } else {
            fx32 s = unkfunc_0212b188(i);
            scale.x = s;
            scale.y = s;
            scale.z = s;
            unkfunc_0212b0fc(pSlime, rot, &scale);
        }
        slime_tp_draw(pSlime);
    }
}

bool bakudanIwa_bakuhatsu(int side, fx32 passFrame)
{
    static fx32 bakuFrame = 0x1e000;
    if (sideInfo_get_gameST(side) == 3) {
        return true;
    }
    if (bakuFrame < 0) {
        bakuFrame = 0x1e000;
        return true;
    }
    if (passFrame && bakuFrame == 0x1e000) {
        ssa_eff_start(0, 200, 164, FX32_ONE, 32);
        SoundManager::playSe(0x205, 0);
        get_pSlime(side, 12)->disp = 0;
        get_pSlime(side, 16)->disp = 0;
        ST_SLIME* pSlime = get_pSlime(side, 13);
        pSlime->trans.x = 0xe4000;
        pSlime->trans.y = 0xa6000;
        pSlime->trans.z = FX32_ONE;
        pSlime->rotZ = 0x4000;
    }
    bakuFrame -= passFrame;
    return false;
}

int get_bonusPointIwa(int side)
{
    ST_SLIME* pSlime = get_pSlime(side, 12);
    int distance = (0xb2000 - pSlime->trans.x) >> FX32_SHIFT;
    ST_SIDE_INFO* pSideInfo = get_pSideInfo(side);
    return distance / 10 * pSideInfo->stage;
}

// ---------------------------------------------------------------------------
// slime_cg

void unkfunc_0212b42c()
{
    int i;
    for (i = 0; i < 9; i++) {
        for (int j = 0; j < 4; j++) {
            if (s_slimeCgAnm[i].file[j].path && s_slimeCgAnm[i].file[j].anm == NULL) {
                s_slimeCgAnm[i].file[j].anm = func_02083298(MG_LoadFile(s_slimeCgAnm[i].file[j].path, NULL), 0);
            }
        }
    }
    for (u32 n = 0; n < sizeof(s_slimeCgModel) / sizeof(s_slimeCgModel[0]); n++) {
        if (s_slimeCgModel[n].path && s_slimeCgModel[n].mdl == NULL) {
            switch (n) {
            case 1:
            case 2:
                unkfunc_02128d2c(s_slimeCgModel[n].path, &s_slimeCgModel[n].file, NULL);
                break;
            default:
                unkfunc_02128d2c(s_slimeCgModel[n].path, &s_slimeCgModel[n].file, &s_slimeCgModel[n].mdl);
                break;
            }
        }
    }
}

void slime_cg_Release(ST_SLIME* pSlime)
{
    int slime_cg = get_kind_data(pSlime->kind, 7);
    if (s_slimeCgModel[slime_cg].file) {
        func_0208294c(s_slimeCgModel[slime_cg].file);
    }
    s_slimeCgModel[slime_cg].mdl = NULL;
    pSlime->kind = KIND_null;
}

void slime_cg_Release_all()
{
    for (u32 i = 0; i < sizeof(s_slimeCgModel) / sizeof(s_slimeCgModel[0]); i++) {
        if (s_slimeCgModel[i].file) {
            func_0208294c(s_slimeCgModel[i].file);
            s_slimeCgModel[i].mdl = NULL;
        }
    }
}

static int slime_cg_set_sub(ST_SLIME* pSlime, KIND kind, int anmNum)
{
    int ret = 0;
    NNSFndAllocator* allocator = unkfunc_02128c4c();
    if (allocator) {
        int slime_cg = get_kind_data(kind, 7);
        NNSG3dResMdl* mdl = s_slimeCgModel[slime_cg].mdl;
        if (mdl == NULL) {
            void* file = s_slimeCgModel[slime_cg].file;
            if (file) {
                unkfunc_0212d83c(file);
                mdl = unkGetMdl(func_02083268(file));
                s_slimeCgModel[slime_cg].mdl = mdl;
            }
        }
        if (mdl) {
            if (pSlime->renderObj == NULL) {
                pSlime->renderObj = func_02082d7c(allocator);
            }
            func_0207fa78(pSlime->renderObj, mdl);
            UnkSlimeCgAnm* anm = &s_slimeCgModel[slime_cg].anm[anmNum];
            for (int i = 0; i < 4; i++) {
                if (pSlime->anmObj[i]) {
                    func_02082da8(allocator, pSlime->anmObj[i]);
                    pSlime->anmObj[i] = NULL;
                    pSlime->anmFrame[i] = 0;
                }
                void* res = anm->file[i].anm;
                if (res) {
                    NNSG3dAnmObj* anmObj = func_02082d90(allocator, res, mdl);
                    func_0207fa14(anmObj, res, mdl, NULL);
                    func_0207fb5c(pSlime->renderObj, anmObj);
                    pSlime->anmObj[i] = anmObj;
                    ret = 1;
                }
            }
        }
    }
    return ret;
}

int slime_cg_set(ST_SLIME* pSlime, KIND kind, int anmNum)
{
    int ret = 0;
    if (get_kind_data(kind, 7) == 0) {
        if (get_kind_data(kind, 8)) {
            ret = slime_sprite_set(pSlime, kind, anmNum);
        }
    } else {
        ret = slime_cg_set_sub(pSlime, kind, anmNum);
    }
    if (ret) {
        for (int i = 0; i < 4; i++) {
            pSlime->anmFrame[i] = 0;
        }
        pSlime->anmSeWait = -1;
        pSlime->anmNum = anmNum;
    }
    return ret;
}

// ---------------------------------------------------------------------------
// slime_sprite

void slime_sprite_init()
{
    if (s_slimeSpriteInit == 0) {
        s_slimeSpriteInit = 1;
        sprite_font_init();
    }
    int spr_id = sprite_kind_data[5].spr_id;
    int data_id = sprite_kind_data[5].data_id;
    if (data_id != -1) {
        if (spr_id) {
            unkfunc_0212bdb4(spr_id);
        }
        sprite_kind_data[5].data_id = -1;
    }
    sprite_kind_data[5].spr_id = unkfunc_021284a4();
    for (u32 i = 0; i < sizeof(sprite_kind_data) / sizeof(sprite_kind_data[0]); i++) {
        spr_id = sprite_kind_data[i].spr_id;
        data_id = sprite_kind_data[i].data_id;
        if (data_id == -1 && spr_id) {
            int loadOpt = sprite_kind_data[i].loadOpt;
            sprite_kind_data[i].data_id = sprite_data_load(spr_id, loadOpt);
        }
    }
}

void slime_sprite_draw(ST_SLIME* pSlime)
{
    SPRITE* spr = pSlime->sprite;
    if (spr == NULL) {
        return;
    }
    int x = pSlime->trans.x >> FX32_SHIFT;
    intTrans0[0] = x;
    int y = pSlime->trans.y >> FX32_SHIFT;
    intTrans0[1] = y;
    int z = pSlime->trans.z >> FX32_SHIFT;
    intTrans0[2] = z;
    spr->x = x;
    pSlime->sprite->y = y;
    pSlime->sprite->z = z;
    pSlime->sprite->alpha = pSlime->alpha;
    fx32 frame = pSlime->frame;
    if (pSlime->sprite->ssa_id) {
        frame = pSlime->anmFrame[0];
    }
    pSlime->sprite->frame = frame >> FX32_SHIFT;
    get_id_pSlime(pSlime);
    pSlime->sprite->col = pSlime->col;
    pSlime->sprite->rotZ = pSlime->rotZ;
    sprite_draw(pSlime->sprite, -1);
}

int slime_sprite_set(ST_SLIME* pSlime, KIND kind, int anmNum)
{
    int ret = 0;
    if (pSlime->sprite) {
        sprite_term(pSlime->sprite);
        pSlime->sprite = NULL;
    }
    int sprite_kind = get_kind_data(kind, 8);
    if (sprite_kind_data[sprite_kind].data_id != -1) {
        pSlime->sprite = sprite_create(sprite_kind_data[sprite_kind].data_id);
        if (pSlime->sprite) {
            switch (sprite_kind_data[sprite_kind].spr_id) {
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 112:
            case 113:
            case 114:
            case 115:
            case 116:
            case 117:
            case 118:
            case 119:
            case 120:
                sprite_set_anim(pSlime->sprite, anmNum, 0);
                break;
            default:
                pSlime->sprite->dir = 2;
                pSlime->sprite->frame = 0;
                break;
            }
            ret = 1;
        }
    }
    return ret;
}

// ---------------------------------------------------------------------------
// sprite

int sprite_data_load_sub(int spr_id, int pal_id, int keep)
{
    void* file;
    SPRITE_DATA* data = NULL;
    int ret = -1;
    SPRITE_DATA* found = NULL;
    for (int i = 0; i < 48; i++) {
        int id = g_sprite_data[i].spr_id;
        if (pal_id == id) {
            return i;
        }
        if (spr_id == id) {
            found = &g_sprite_data[i];
        }
        if (id == 0) {
            ret = i;
            g_sprite_data[i].spr_id = spr_id;
            data = &g_sprite_data[i];
            break;
        }
    }
    char path[64];
    u32 size;
    if (found == NULL) {
        sprintf(path, "SlimeTouch/sprite/%03d.NCBR", spr_id);
        file = MG_LoadFile(path, &size);
        if (file) {
            NNSG2dCharacterData* chr;
            unkfunc_0212dcb0(file, &chr);
            unkSetTexParam(&data->tex, chr);
            data->width = 8 << data->tex.sizeS;
            data->height = 8 << data->tex.sizeT;
            data->texKey = unkfunc_0212d5d4(chr->szByte);
            data->texFile = NULL;
            unkfunc_0212d4f4(data->texKey, chr->pRawData, 0);
            unkfunc_02128c78(file);
        }
    } else {
        *data = *found;
    }
    sprintf(path, "SlimeTouch/sprite/%03d.NCLR", pal_id);
    file = MG_LoadFile(path, &size);
    if (file) {
        NNSG2dPaletteData* pltt;
        unkfunc_0212dcfc(file, &pltt);
        data->plttKey = unkfunc_0212d5f4(pltt->szByte);
        data->texFile = NULL;
        unkfunc_0212d564(data->plttKey, pltt->pRawData, 0);
        unkfunc_02128c78(file);
    }
    return ret;
}

int sprite_data_load(int spr_id, int keep)
{
    int ret = sprite_data_load_sub(spr_id, spr_id, keep);
    if (spr_id >= 5 && spr_id < 73) {
        sprite_data_load_sub(spr_id + 1, spr_id + 1, keep);
        sprite_data_load_sub(spr_id + 2, spr_id + 2, keep);
        sprite_data_load_sub(spr_id + 3, spr_id + 3, keep);
    }
    return ret;
}

void unkfunc_0212bd30(int spr_id)
{
    for (int i = 0; i < 48; i++) {
        SPRITE_DATA* data = &g_sprite_data[i];
        if (data->spr_id && (data->spr_id == spr_id || spr_id == -1)) {
            if (data->texFile) {
                unkfunc_02128c78(data->texFile);
            } else {
                func_02086b40(data->texKey);
            }
            if (data->plttFile) {
                unkfunc_02128c78(data->plttFile);
            } else {
                func_02086d84(data->plttKey);
            }
            data->spr_id = 0;
        }
    }
}

void unkfunc_0212bdb4(int spr_id)
{
    unkfunc_0212bd30(spr_id);
    if (spr_id >= 5 && spr_id < 73) {
        unkfunc_0212bd30(spr_id + 1);
        unkfunc_0212bd30(spr_id + 2);
        unkfunc_0212bd30(spr_id + 3);
    }
}

static void sprite_init(SPRITE* spr)
{
    spr->x = 0;
    spr->y = 0;
    spr->z = 1;
    spr->alpha = 31;
    spr->dir = 0;
    spr->frame = 0;
    spr->col = 0x7fff;
    spr->rotZ = 0;
    spr->sclX = FX32_ONE;
    spr->sclY = FX32_ONE;
    spr->ssa_id = 0;
    spr->nframe = 0;
}

SPRITE* sprite_create(int data_id)
{
    SPRITE* spr = (SPRITE*)unkfunc_02128c5c(sizeof(SPRITE));
    sprite_init(spr);
    spr->data_id = data_id;
    return spr;
}

void sprite_term(SPRITE* spr)
{
    unkfunc_02128c78(spr);
}

void sprite_set_anim(SPRITE* spr, int ssa_id, int frame)
{
    spr->ssa_id = ssa_id;
    spr->frame = frame;
    spr->nframe = ssa_eff_get_nframe(ssa_id);
}

void sprite_draw_start()
{
    REG_GFX_FIFO_MATERIAL_DIFFUSE_AMBIENT = 0xffff;
    REG_GFX_FIFO_MATERIAL_SPECULAR_EMISSION = 0;
    REG_GFX_FIFO_POLYGON_ATTR = 0x1f00c0;
    unkfunc_0212da5c();
    func_0207ec9c(10);
    REG_GFX_FIFO_MATRIX_PUSH = 0;
    REG_GFX_FIFO_MATRIX_IDENTITY = 0;
}

void sprite_draw_end()
{
    REG_GFX_FIFO_MATRIX_POP = 1;
}

void sprite_activate(int data_id)
{
    SPRITE_DATA* data = &g_sprite_data[data_id];
    u32 texAddr = (data->texKey & 0xffff) << 3;
    u32 plttAddr = (data->plttKey & 0xffff) << 3;
    if (data->texFile) {
        texAddr = (u16)unkfunc_0212d614(data->texFile, ((data->texKey & 0x7fff0000) >> 16) << 4, 1) << 3;
    }
    if (data->plttFile) {
        plttAddr = (u16)unkfunc_0212d6b4(data->plttFile, ((data->plttKey & 0xffff0000) >> 16) << 3, 1) << 3;
    }
    G3_TexImageParam(data->tex.texFmt, GX_TEXGEN_TEXCOORD, data->tex.sizeS, data->tex.sizeT, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, data->tex.plttColor0, texAddr);
    REG_GFX_FIFO_TEXTURE_PALETTE = plttAddr >> (4 - (data->tex.texFmt == 2));
}

static void split_G2dDrawSpriteFast(short x, short y, int z, int sizeX, int sizeY, int u1, int v1, int u2, int v2, int yy)
{
    int hh = sizeY / 2;
    int vv = v1 + (v2 - v1) / 2;
    func_0207eca8(x, (short)(y - yy), z, sizeX, hh, u1, v1, u2, vv);
    REG_GFX_FIFO_MATRIX_IDENTITY = 0;
    func_0207eca8(x, (short)(y + hh + yy), z, sizeX, hh, u1, vv, u2, v2);
}

static void font_draw(SPRITE* spr, int yy)
{
    static char tbl_w[6] = { 11, 22, 8, 24, 25, 32 };
    static char tbl_h[6] = { 16, 22, 8, 32, 32, 32 };
    sprite_draw_start();
    sprite_activate(spr->data_id);
    int w = tbl_w[spr->dir];
    int h = tbl_h[spr->dir];
    int u = w * spr->frame;
    int sizeX = w * spr->sclX >> FX32_SHIFT;
    int sizeY = h * spr->sclY >> FX32_SHIFT;
    REG_GFX_FIFO_MATERIAL_DIFFUSE_AMBIENT = spr->col | 0x8000;
    REG_GFX_FIFO_POLYGON_ATTR = (spr->alpha << 16) | 0xc0;
    if (yy < 0) {
        func_0207eca8((short)spr->x, (short)(spr->y + h / 2 - sizeY / 2), spr->z, sizeX, sizeY, u, 0, u + w, h);
    } else {
        split_G2dDrawSpriteFast(spr->x, spr->y, spr->z, sizeX, sizeY, u, 0, u + w, h, yy);
    }
    sprite_draw_end();
}

static void chara_draw(SPRITE* spr)
{
    sprite_draw_start();
    sprite_activate(spr->data_id + spr->dir);
    int u = spr->frame / 8 % 4;
    if (u == 3) {
        u = 1;
    }
    short ofs = s_charaDrawOffset;
    G3_Translate((spr->x + ofs) << FX32_SHIFT, (spr->y + ofs) << FX32_SHIFT, 0);
    u *= 24;
    func_020761dc(FX_SinIdx(spr->rotZ), FX_CosIdx(spr->rotZ));
    func_0207eca8((short)-ofs, (short)-ofs, spr->z, 24, 32, u, 0, u + 24, 32);
    sprite_draw_end();
}

void ssa_sprite_draw(SPRITE* spr)
{
    BSSA_DATA* bssa = ssa_eff_get_bssa(spr->ssa_id);
    unkfunc_0212da5c();
    sprite_activate(spr->data_id);
    bssa_draw(bssa, spr->frame, spr->x, spr->y, spr->z, spr->sclX);
}

void sprite_draw_rect(SPRITE* spr, int u1, int v1, int u2, int v2)
{
    sprite_draw_start();
    sprite_activate(spr->data_id);
    func_0207eca8((short)spr->x, (short)spr->y, spr->z, u2 - u1, v2 - v1, u1, v1, u2, v2);
    sprite_draw_end();
}

void sprite_font_init()
{
    font_sprite_data[0] = sprite_data_load(998, 1);
    font_sprite_data[1] = sprite_data_load(999, 0);
    font_sprite_data[2] = sprite_data_load(997, 0);
    font_sprite_data[3] = sprite_data_load(996, 0);
    font_sprite_data[4] = sprite_data_load(995, 0);
    font_sprite_data[5] = sprite_data_load(211, 0);
    font_sprite_data[6] = sprite_data_load(212, 0);
    font_sprite_data[7] = sprite_data_load(213, 0);
    font_sprite_data[8] = sprite_data_load(204, 0);
}

void sprite_draw(SPRITE* spr, int yy)
{
    SPRITE_DATA* data = &g_sprite_data[spr->data_id];
    if (spr->ssa_id) {
        ssa_sprite_draw(spr);
        return;
    }
    if (data->spr_id >= 5 && data->spr_id < 73) {
        chara_draw(spr);
        return;
    }
    sprite_draw_start();
    sprite_activate(spr->data_id);
    short w = data->width;
    short h = data->height;
    REG_GFX_FIFO_MATERIAL_DIFFUSE_AMBIENT = spr->col | 0x8000;
    REG_GFX_FIFO_POLYGON_ATTR = (spr->alpha << 16) | 0xc0;
    short rx = chara_r;
    short ry = rx;
    if (data->spr_id == 2) {
        rx = slime_r;
        ry = rx;
    } else if (data->spr_id == 100) {
        rx = 0;
        ry = rx;
    }
    G3_Translate((spr->x + rx) << FX32_SHIFT, (spr->y + ry) << FX32_SHIFT, 0);
    u16 idx = spr->rotZ;
    fx16 sin = FX_SinIdx(idx);
    fx16 cos = FX_CosIdx(idx);
    if (data->spr_id == 2) {
        func_020761dc(sin, cos);
    } else if (data->spr_id == 100) {
        rx = bakudanIwa_r;
    } else {
        func_02076164(sin, cos);
    }
    G3_Translate(-((spr->x + rx) << FX32_SHIFT), -((spr->y + ry) << FX32_SHIFT), 0);
    if (spr->data_id == font_sprite_data[6]) {
        h = 38;
    }
    if (yy < 0) {
        int sizeY = h * spr->sclY >> FX32_SHIFT;
        func_0207eca8((short)spr->x, (short)(spr->y + h / 2 - sizeY / 2), spr->z, w, sizeY, 0, 0, w, h);
    } else {
        split_G2dDrawSpriteFast(spr->x, spr->y, spr->z, w, h, 0, 0, w, h, yy);
    }
    sprite_draw_end();
}

void draw_touch_num(int x, int y, int num, int alpha)
{
    SPRITE spr;
    int mi = 0;
    spr.x = x;
    spr.y = y;
    spr.z = 30;
    spr.dir = 2;
    spr.data_id = font_sprite_data[num < 0 ? 3 : 2];
    spr.alpha = alpha;
    spr.col = 0x7fff;
    spr.sclX = FX32_ONE;
    spr.sclY = FX32_ONE;
    if (num < 0) {
        num = -num;
        mi = 1;
    }
    do {
        spr.frame = num % 10;
        num /= 10;
        font_draw(&spr, -1);
        spr.x -= 8;
    } while (num != 0);
    if (mi) {
        spr.frame = 10;
        font_draw(&spr, -1);
    }
}

void draw_stage_num(int stage)
{
    SPRITE spr;
    spr.x = 112;
    spr.y = 84;
    spr.z = 1;
    spr.dir = 1;
    spr.data_id = font_sprite_data[0];
    spr.alpha = 31;
    spr.col = 0x233f;
    spr.sclX = FX32_ONE;
    spr.sclY = FX32_ONE;
    if (stage < 10) {
        spr.x = 117;
    } else {
        spr.frame = stage / 10;
        spr.x = 107;
        font_draw(&spr, -1);
        spr.x = 124;
    }
    spr.frame = stage % 10;
    font_draw(&spr, -1);
}

void draw_score_ex(int score, int flag, int x, int y, GXRgb col)
{
    static int dwscr_score_x = 168;
    static int dwscr_score_y = 96;
    static int dwscr_score_y_rankin = 128;
    SPRITE spr;
    int minus = score < 0 ? 1 : 0;
    spr.y = 119;
    spr.z = 30;
    spr.dir = 0;
    spr.data_id = font_sprite_data[1];
    spr.alpha = 31;
    spr.sclX = FX32_ONE;
    spr.sclY = FX32_ONE;
    int w = 8;
    if (flag == 0) {
        spr.x = 192;
        if (score >= 0) {
            spr.col = 0x7fe0;
        } else {
            score *= -1;
            spr.col = 31;
        }
        w = 12;
    } else if (flag == 1 || flag == 2) {
        spr.col = 0x7fff;
        if (score < 0) {
            score *= -1;
            spr.col = 31;
        }
        spr.dir = 3;
        spr.data_id = font_sprite_data[4];
        spr.x = dwscr_score_x;
        spr.y = dwscr_score_y;
        if (flag == 2) {
            spr.y = dwscr_score_y_rankin;
        }
        w = 20;
    } else {
        spr.sclX = FX32_ONE;
        spr.sclY = FX32_ONE;
        spr.col = col;
        spr.x = x;
        spr.y = y;
    }
    do {
        spr.frame = score % 10;
        score /= 10;
        font_draw(&spr, -1);
        spr.x -= w * spr.sclX >> FX32_SHIFT;
    } while (score != 0);
    if (minus) {
        spr.frame = 10;
        font_draw(&spr, -1);
    }
}

void draw_stage_clear(int x, int y, int stage, int disp_clear, int alpha, int yy, fx32 sclY)
{
    if (disp_clear) {
        return;
    }
    SPRITE spr;
    sprite_init(&spr);
    spr.z = 30;
    spr.x = x;
    spr.y = y;
    spr.data_id = font_sprite_data[6];
    spr.alpha = alpha;
    spr.sclY = sclY;
    sprite_draw(&spr, yy);
    spr.x += 82;
    if (stage >= 1000) {
        spr.data_id = font_sprite_data[8];
        spr.dir = 5;
        spr.x += 2;
        spr.y += 2;
        spr.sclX = FX32_ONE;
        font_draw(&spr, yy);
        spr.x += 32;
        spr.y -= 2;
    } else {
        spr.data_id = font_sprite_data[5];
        spr.dir = 4;
        if (stage >= 10) {
            spr.frame = stage / 10;
            font_draw(&spr, yy);
            spr.x += 25;
        }
        spr.frame = stage % 10;
        font_draw(&spr, yy);
        spr.x += 26;
    }
    if (disp_clear) {
        spr.data_id = font_sprite_data[7];
        sprite_draw(&spr, -1);
    }
}

void sprite_all_free()
{
    for (int i = 0; i < 48; i++) {
        SPRITE_DATA* data = &g_sprite_data[i];
        if (data->texFile) {
            unkfunc_02128c78(data->texFile);
        } else if (data->texKey) {
            func_02086b40(data->texKey);
        }
        if (data->plttFile) {
            unkfunc_02128c78(data->plttFile);
        } else if (data->plttKey) {
            func_02086d84(data->plttKey);
        }
        memset(data, 0, sizeof(SPRITE_DATA));
    }
}

// ---------------------------------------------------------------------------
// ssa_eff

void ssa_eff_init()
{
    __builtin__clear(g_eff_work, sizeof(g_eff_work));
    for (u32 i = 0; i < sizeof(ssa_data_touch) / sizeof(ssa_data_touch[0]); i++) {
        g_bssa[i] = bssa_init(MG_LoadFile(ssa_data_touch[i].fname, NULL));
        if (ssa_data_touch[i].spr_id) {
            g_bssa[i]->tex_id = sprite_data_load(ssa_data_touch[i].spr_id, 1);
        } else {
            g_bssa[i]->tex_id = 0;
        }
    }
}

BSSA_DATA* ssa_eff_get_bssa(int eff_id)
{
    return g_bssa[eff_id];
}

int ssa_eff_get_nframe(int eff_id)
{
    return g_bssa[eff_id]->n_frame;
}

void ssa_eff_draw(int eff_id, int frame, int x, int y, int z, fx32 scale)
{
    unkfunc_0212da5c();
    sprite_activate(g_bssa[eff_id]->tex_id);
    bssa_draw(g_bssa[eff_id], frame, x, y, z, scale);
}

void ssa_eff_draw_3D(int eff_id, int frame, int x, int y, int z, fx32 scale)
{
    sprite_activate(g_bssa[eff_id]->tex_id);
    bssa_draw_3D(g_bssa[eff_id], frame, x, y, z, scale);
}

int ssa_eff_start(int eff_id, int x, int y, fx32 scale, int flag)
{
    int ret = -1;
    for (u32 i = 0; i < sizeof(g_eff_work) / sizeof(g_eff_work[0]); i++) {
        if (g_eff_work[i].flag == 0) {
            ret = i;
            break;
        }
    }
    if (ret != -1) {
        BSSA_EFF_WORK* wk = &g_eff_work[ret];
        wk->flag |= (char)flag | 2;
        wk->eff_id = eff_id;
        g_eff_work[ret].x = x;
        wk->y = y;
        wk->z = 100;
        wk->scale = scale;
        wk->frame = 0;
    }
    return ret;
}

int ssa_eff_update(int upScreen)
{
    u32 i;
    int ret = 0;
    int mask = upScreen ? 0x20 : 0x10;
    for (i = 0; i < sizeof(g_eff_work) / sizeof(g_eff_work[0]); i++) {
        BSSA_EFF_WORK* wk = &g_eff_work[i];
        int flag = wk->flag;
        if (flag & mask) {
            if (!(flag & 8)) {
                if (flag & 0x80) {
                    ssa_eff_draw_3D(wk->eff_id, wk->frame, wk->x, wk->y, wk->z, wk->scale);
                } else {
                    ssa_eff_draw(wk->eff_id, wk->frame, wk->x, wk->y, wk->z, wk->scale);
                }
            }
            if (!(flag & 4)) {
                wk->frame++;
            }
            if (wk->frame == g_bssa[wk->eff_id]->n_frame) {
                if (flag & 1) {
                    wk->frame = 0;
                } else if (flag & 0x40) {
                    wk->frame = g_bssa[wk->eff_id]->n_frame;
                } else {
                    wk->flag = 0;
                }
            }
            ret++;
        }
    }
    return ret;
}

BOOL ssa_eff_chk(int play_id, int eff_id)
{
    BSSA_EFF_WORK* wk = &g_eff_work[play_id];
    BOOL ret = FALSE;
    if (wk->eff_id != (char)eff_id) {
        return ret;
    }
    if (wk->flag) {
        ret = TRUE;
    }
    return ret;
}

// ---------------------------------------------------------------------------
// bssa_lib

#define FX64C_TWOPI_INV ((fx64)0x000028BE60DB9391LL)
#define FX_RAD_TO_IDX(rad) ((u16)(((fx64)(rad) * FX64C_TWOPI_INV + 0x80000000000LL) >> 44))

void bssa_draw_prim(BSSA_PRIM* prim, BSSA_PARTS* parts, int poly_id)
{
    G3_PolygonAttr(0, 0, 0xc0, poly_id, prim->alpha, 0);
    int u0 = prim->flipH ? parts->u1 : parts->u0;
    int u1 = prim->flipH ? parts->u0 : parts->u1;
    int v0 = prim->flipV ? parts->v1 : parts->v0;
    int v1 = prim->flipV ? parts->v0 : parts->v1;
    G3_Begin(1);
    G3_TexCoord(u0 << FX32_SHIFT, v0 << FX32_SHIFT);
    G3_Vtx(-0x800, -0x800, 0);
    G3_TexCoord(u0 << FX32_SHIFT, v1 << FX32_SHIFT);
    G3_Vtx(-0x800, 0x800, 0);
    G3_TexCoord(u1 << FX32_SHIFT, v1 << FX32_SHIFT);
    G3_Vtx(0x800, 0x800, 0);
    G3_TexCoord(u1 << FX32_SHIFT, v0 << FX32_SHIFT);
    G3_Vtx(0x800, -0x800, 0);
    G3_End();
}

void bssa_draw(BSSA_DATA* bssa, int frame, int x, int y, int z, fx32 scale)
{
    if (frame < 0) {
        frame = 0;
    } else if (frame >= bssa->n_frame) {
        frame = bssa->n_frame - 1;
    }
    BSSA_FRAME* fr = &bssa->frame[frame];
    BSSA_PRIM* prim = &bssa->prim[fr->prim_ofs];
    G3_PushMtx();
    G3_Color(0x7fff);
    for (int i = 0; i < fr->n_prim; i++) {
        BSSA_PARTS* parts = &bssa->parts[prim->parts_id];
        G3_Identity();
        G3_Translate(x << FX32_SHIFT, y << FX32_SHIFT, (i + 1) << FX32_SHIFT);
        G3_Scale(scale, scale, FX32_ONE);
        G3_Translate(prim->pos_x << 8, prim->pos_y << 8, z << FX32_SHIFT);
        if (prim->rot_z) {
            u16 rz = FX_RAD_TO_IDX(prim->rot_z);
            func_020761dc(FX_SinIdx(rz), FX_CosIdx(rz));
        }
        G3_Scale((parts->u1 - parts->u0) * prim->scl_x, (parts->v1 - parts->v0) * prim->scl_y, FX32_ONE);
        bssa_draw_prim(prim, parts, i & 0x3f);
        prim++;
    }
    G3_PopMtx(1);
}

void bssa_draw_3D(BSSA_DATA* bssa, int frame, int xpos, int ypos, int zpos, fx32 scale)
{
    if (frame < 0) {
        frame = 0;
    } else if (frame >= bssa->n_frame) {
        frame = bssa->n_frame - 1;
    }
    BSSA_FRAME* fr = &bssa->frame[frame];
    BSSA_PRIM* prim = &bssa->prim[fr->prim_ofs];
    VecFx32 pos;
    pos.x = xpos;
    pos.y = ypos;
    pos.z = zpos;
    fx32 x;
    fx32 y;
    fx32 z;
    unkfunc_0212dac0(&pos, &x, &y, &z);
    MtxFx44 trans;
    func_02089e40(0, 0xc0000, 0, 0x100000, 0, 0x1100, FX32_ONE, &trans);
    G3_MtxMode(0);
    func_02075ac8(&trans);
    G3_MtxMode(1);
    G3_PushMtx();
    G3_Color(0x7fff);
    for (int i = 0; i < fr->n_prim; i++) {
        BSSA_PARTS* parts = &bssa->parts[prim->parts_id];
        G3_Identity();
        G3_Translate(x, y, z + i);
        G3_Scale(scale, scale, FX32_ONE);
        G3_Translate(prim->pos_x << 8, prim->pos_y << 8, 0);
        if (prim->rot_z) {
            u16 rz = FX_RAD_TO_IDX(prim->rot_z);
            func_020761dc(FX_SinIdx(rz), FX_CosIdx(rz));
        }
        G3_Scale((parts->u1 - parts->u0) * prim->scl_x, (parts->v1 - parts->v0) * prim->scl_y, FX32_ONE);
        bssa_draw_prim(prim, parts, i & 0x3f);
        prim++;
    }
    G3_PopMtx(1);
}

BSSA_DATA* bssa_init(void* data)
{
    struct chunk {
        u32 id;
        u32 size;
    };
    chunk* cnk = (chunk*)data;
    BSSA_DATA* bssa = NULL;
    while (cnk->id) {
        switch (cnk->id) {
        case 0x30444853:
            bssa = (BSSA_DATA*)(cnk + 1);
            break;
        case 0x30545053:
            bssa->parts = (BSSA_PARTS*)(cnk + 1);
            break;
        case 0x30525053:
            bssa->prim = (BSSA_PRIM*)(cnk + 1);
            break;
        case 0x30524653:
            bssa->frame = (BSSA_FRAME*)(cnk + 1);
            break;
        }
        cnk = (chunk*)((u8*)cnk + cnk->size + sizeof(chunk));
    }
    return bssa;
}

// ---------------------------------------------------------------------------
// VRAM

void unkfunc_0212d458()
{
    s_texCacheCount = 0;
    s_plttCacheCount = 0;
}

void unkfunc_0212d470()
{
    int i;
    for (i = 0; i < s_texCacheCount; i++) {
        unkfunc_0212d5e8(s_texCache[i].key);
    }
    s_texCacheCount = 0;
    for (i = 0; i < s_plttCacheCount; i++) {
        unkfunc_0212d608(s_plttCache[i].key);
    }
    s_plttCacheCount = 0;
}

int unkfunc_0212d4f4(u32 texKey, void* src, int task)
{
    u32 addr = (texKey & 0xffff) << 3;
    u32 size = ((texKey & 0x7fff0000) >> 16) << 4;
    if (task) {
        return func_020867d0(0, addr, src, size);
    }
    DC_PurgeRange(src, size);
    func_02076e98();
    func_02076ef4(src, addr, size);
    func_02077034();
    return 1;
}

int unkfunc_0212d564(u32 plttKey, void* src, int task)
{
    u32 addr = (plttKey & 0xffff) << 3;
    u32 size = ((plttKey & 0xffff0000) >> 16) << 3;
    if (task) {
        return func_020867d0(1, addr, src, size);
    }
    DC_PurgeRange(src, size);
    func_02077080();
    func_020770b4(src, addr, size);
    func_02077120();
    return 1;
}

u32 unkfunc_0212d5d4(u32 size)
{
    return func_02086adc(size, 0, 1);
}

int unkfunc_0212d5e8(u32 key)
{
    return func_02086b40(key);
}

u32 unkfunc_0212d5f4(u32 size)
{
    return func_02086d00(size, 0, 1);
}

int unkfunc_0212d608(u32 key)
{
    return func_02086d84(key);
}

u32 unkfunc_0212d614(void* data, u32 size, int load)
{
    for (int i = 0; i < s_texCacheCount; i++) {
        if (s_texCache[i].data == data) {
            return s_texCache[i].key;
        }
    }
    u32 key = func_02086adc(size, 0, 1);
    s_texCache[s_texCacheCount].data = data;
    s_texCache[s_texCacheCount].key = key;
    s_texCacheCount++;
    if (load) {
        unkfunc_0212d4f4(key, data, 1);
    }
    return key;
}

u32 unkfunc_0212d6b4(void* data, u32 size, int load)
{
    for (int i = 0; i < s_plttCacheCount; i++) {
        if (s_plttCache[i].data == data) {
            return s_plttCache[i].key;
        }
    }
    u32 key = func_02086d00(size, 0, 1);
    s_plttCache[s_plttCacheCount].data = data;
    s_plttCache[s_plttCacheCount].key = key;
    s_plttCacheCount++;
    if (load) {
        unkfunc_0212d564(key, data, 1);
    }
    return key;
}

// ---------------------------------------------------------------------------
// model resources

void unkfunc_0212d754(NNSG3dResTex* tex, int exec)
{
    func_020867d0(1, (tex->plttInfo.vramKey & 0xffff) << 3, (u8*)tex + tex->plttInfo.ofsPlttData, tex->plttInfo.sizePltt << 3);
    tex->plttInfo.flag |= 1;
}

void unkfunc_0212d790(NNSG3dResTex* tex, int exec)
{
    u32 size = tex->texInfo.sizeTex << 3;
    if (size) {
        func_020867d0(0, (tex->texInfo.vramKey & 0xffff) << 3, (u8*)tex + tex->texInfo.ofsTex, size);
        tex->texInfo.flag |= 1;
    }
    u32 size4x4 = tex->tex4x4Info.sizeTex << 3;
    if (size4x4) {
        u32 addr4x4 = (tex->tex4x4Info.vramKey & 0xffff) << 3;
        u8* pIdx = (u8*)tex + tex->tex4x4Info.ofsTexPlttIdx;
        func_020867d0(0, addr4x4, (u8*)tex + tex->tex4x4Info.ofsTex, size4x4);
        func_020867d0(0, 0x20000 + ((addr4x4 & 0x1ffff) >> 1) + ((addr4x4 & 0x40000) >> 2), pIdx, size4x4 >> 1);
        tex->tex4x4Info.flag |= 1;
    }
}

BOOL unkfunc_0212d83c(void* pResData)
{
    switch (*(u32*)pResData) {
    case 0x30444d42:
    case 0x30585442: {
        NNSG3dResTex* tex;
        u32 szTex;
        u32 szTex4x4;
        u32 szPltt;
        BOOL sucTex = TRUE;
        BOOL sucTex4x4 = TRUE;
        BOOL sucPltt = TRUE;
        u32 keyTex;
        u32 keyTex4x4;
        u32 keyPltt;

        tex = func_02083270(pResData);
        if (tex) {
            szTex = func_0207fc2c(tex);
            szTex4x4 = func_0207fc3c(tex);
            szPltt = func_0207fd08(tex);

            if (szTex) {
                keyTex = data_0209c788(szTex, FALSE, 0);
                if (keyTex == 0) {
                    sucTex = FALSE;
                }
            } else {
                keyTex = 0;
            }

            if (szTex4x4) {
                keyTex4x4 = data_0209c788(szTex4x4, TRUE, 0);
                if (keyTex4x4 == 0) {
                    sucTex4x4 = FALSE;
                }
            } else {
                keyTex4x4 = 0;
            }

            if (szPltt) {
                keyPltt = data_0209c790(szPltt, tex->tex4x4Info.flag & 0x8000, 0);
                if (keyPltt == 0) {
                    sucPltt = FALSE;
                }
            } else {
                keyPltt = 0;
            }

            if (!sucTex || !sucTex4x4 || !sucPltt) {
                data_0209c794(keyPltt);
                data_0209c78c(keyTex4x4);
                data_0209c78c(keyTex);
                return FALSE;
            }

            func_0207fc4c(tex, keyTex, keyTex4x4);
            func_0207fd18(tex, keyPltt);
            unkfunc_0212d790(tex, TRUE);
            unkfunc_0212d754(tex, TRUE);
        }

        if (*(u32*)pResData == 0x30444d42) {
            NNSG3dResMdlSet* mdlSet = func_02083268(pResData);
            if (tex) {
                func_0208012c(mdlSet, tex);
            }
        }
        return TRUE;
    }
    case 0x30414342:
    case 0x30415642:
    case 0x30414d42:
    case 0x30505442:
    case 0x30415442:
        return TRUE;
    default:
        return FALSE;
    }
}

void unkfunc_0212da5c()
{
    func_020760b4(0, 0xc0000, 0, 0x100000, -0x400000, 0x400000, FX32_ONE, 1, NULL);
    G3_StoreMtx(0);
    G3_MtxMode(1);
}

/* not original: at -O4 the three roundings are not interleaved */
#pragma push
#pragma optimization_level 3
int unkfunc_0212dac0(VecFx32* world, fx32* px, fx32* py, fx32* pz)
{
    int ret;
    int x1;
    int dx;
    int y1;
    fx32 w;
    const MtxFx44* proj;
    fx32 x;
    VecFx32 vec;
    int dy;
    int x2;
    fx64 inv;
    int y2;
    fx32 y;
    fx32 z;

    proj = &data_02124bb4.projMtx;
    func_02089488(world, &data_02124bb4.cameraMtx, &vec);
    {
        fx64 tw = (fx64)vec.x * proj->m[0][3] + (fx64)vec.y * proj->m[1][3] + (fx64)vec.z * proj->m[2][3];
        w = (fx32)(tw >> 12) + proj->m[3][3];
    }
    FX_InvAsync(w);
    {
        fx64 tx = (fx64)vec.x * proj->m[0][0] + (fx64)vec.y * proj->m[1][0] + (fx64)vec.z * proj->m[2][0];
        fx64 ty = (fx64)vec.x * proj->m[0][1] + (fx64)vec.y * proj->m[1][1] + (fx64)vec.z * proj->m[2][1];
        fx64 tz = (fx64)vec.x * proj->m[0][2] + (fx64)vec.y * proj->m[1][2] + (fx64)vec.z * proj->m[2][2];
        x = (fx32)(tx >> 12) + proj->m[3][0];
        y = (fx32)(ty >> 12) + proj->m[3][1];
        z = (fx32)(tz >> 12) + proj->m[3][2];
    }
    inv = FX_GetDivResultFx64c();
    x = (FX_Mul32x64c(x, inv) + FX32_ONE) / 2;
    y = (FX_Mul32x64c(y, inv) + FX32_ONE) / 2;
    z = (FX_Mul32x64c(z, inv) + FX32_ONE) / 2;

    ret = 0;
    if (x < 0 || y < 0 || x > FX32_ONE || y > FX32_ONE) {
        ret = -1;
    }

    func_0208069c(&x1, &y1, &x2, &y2);
    dx = x2 - x1;
    dy = y2 - y1;
    *px = x * dx + 0x800 + (x1 << FX32_SHIFT);
    *py = ((191 - y1) << FX32_SHIFT) - (y * dy + 0x800);
    *pz = -z;
    return ret;
}
#pragma pop

// ---------------------------------------------------------------------------
// NNS G2D resources

void unkfunc_0212dca0(NNSG2dCharacterData* chr)
{
    chr->pRawData = (u8*)chr->pRawData + (u32)chr;
}

BOOL unkfunc_0212dcb0(void* file, NNSG2dCharacterData** ppChr)
{
    NNSG2dBinaryBlockHeader* block = func_0207ebf8(file, 0x43484152);
    if (block) {
        unkfunc_0212dca0((NNSG2dCharacterData*)(block + 1));
        *ppChr = (NNSG2dCharacterData*)(block + 1);
        return TRUE;
    }
    *ppChr = NULL;
    return FALSE;
}

void unkfunc_0212dcec(NNSG2dPaletteData* pltt)
{
    pltt->pRawData = (u8*)pltt->pRawData + (u32)pltt;
}

BOOL unkfunc_0212dcfc(void* file, NNSG2dPaletteData** ppPltt)
{
    NNSG2dBinaryBlockHeader* block = func_0207ebf8(file, 0x504c5454);
    if (block) {
        unkfunc_0212dcec((NNSG2dPaletteData*)(block + 1));
        *ppPltt = (NNSG2dPaletteData*)(block + 1);
        return TRUE;
    }
    *ppPltt = NULL;
    return FALSE;
}

// ---------------------------------------------------------------------------
// unused: dead-stripped by the linker, keeps the hidden data items referenced (pooled)

void* unkfunc_unused_SlimeTouchGame(int id)
{
    switch (id) {
    case 0:
        return &data_ov002_0212e2dc;
    case 1:
        return &data_ov002_0212e2fc;
    case 2:
        return &data_ov002_0212e300;
    case 3:
        return &data_ov002_0212e334;
    case 4:
        return &data_ov002_02133a60;
    case 5:
        return &data_ov002_02133a6c;
    case 6:
        return &data_ov002_02133a88;
    case 7:
        return &data_ov002_02133a90;
    case 8:
        return data_ov002_02133ac4;
    case 9:
        return data_ov002_02133ad0;
    case 10:
        return data_ov002_02133b68;
    case 11:
        return data_ov002_0212e364;
    }
    return NULL;
}
