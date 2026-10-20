#pragma ipa file
#include "ov003/slimerace/SlimeRace.hpp"
#include "ov003/fld/SlimeRaceFLDObject.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/sound/SoundManager.hpp"
#include "nitro/dc.h"
#include "nitro/fs.hpp"
#include "nitro/fx.hpp"
#include "nitro/fx/fx_division.h"
#include "nitro/fx/fx_trig.h"
#include "nitro/g3.hpp"
#include "nitro/gx.h"
#include "nitro/gx.hpp"
#include "nitro/math.hpp"
#include "nitro/pad.h"
#include "nnsys/fnd.hpp"
#include "nnsys/g2d.hpp"
#include "nnsys/g3d.hpp"
#include <mem.h>
#include <printf.h>

#define NNS_GFD_GET_TEX_KEY_ADDR(key) (((key) & 0xffff) << 3)
#define NNS_GFD_GET_TEX_KEY_SIZE(key) ((((key) & 0x7fff0000) >> 16) << 4)
#define NNS_GFD_GET_PLTT_KEY_ADDR(key) (((key) & 0xffff) << 3)
#define NNS_GFD_GET_PLTT_KEY_SIZE(key) ((((key) & 0xffff0000) >> 16) << 3)
#define FX_RAD_TO_IDX(rad) ((u16)(((fx64)(rad) * 0x28be60db9391LL + 0x80000000000LL) >> 44))

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

inline int GX_GetDispSelect()
{
    return (REG_POWER_CNT & 0x8000) >> 15;
}

inline void G3_TexPlttBase(unsigned int addr, int texFmt)
{
    REG_GFX_FIFO_TEXTURE_PALETTE = addr >> (4 - (texFmt == 2));
}

inline fx32 FX_Mul32x64c(fx32 v32, fx64 v64c)
{
    return (fx32)((v64c * v32 + 0x80000000LL) >> 32);
}

inline void NNS_G3dGlbPerspectiveW(fx32 fovySin, fx32 fovyCos, fx32 aspect, fx32 n, fx32 f, fx32 scaleW)
{
    func_02089cf4(fovySin, fovyCos, aspect, n, f, scaleW, &data_02124bb4.projMtx);
    data_02124bb4.flag &= ~0x50;
}

inline UnkRaceWork::UnkRaceWork()
{
}

namespace race {

static int unk_02131aa4;
static ST_SLIME_RACE slimeRace[6];
static int unk_02131a70;
static fx32 s_fovySin;
static short unk_02131a42;
static ST_TIKEI_DATA tikei_data[TIKEI_MAX] = {
    { "TIKEI_null", { 0, 11 } },   // TIKEI_null: TIKEI_null
    { "\x8e\xc5\x81i\x8a\xee\x96{\x81j", { 100, 0 } },   // TIKEI_shiba: 芝（基本）
    { "\x83_\x81[\x83g\x81i\x8a\xee\x96{\x81j", { 95, 5 } },   // TIKEI_dirt: ダート（基本）
    { "\x8d\xbb\x97\x98", { 90, 10 } },   // TIKEI_jari: 砂利
    { "\x90\x85\x97\xad\x82\xe8", { 85, 15 } },   // TIKEI_mizu: 水溜り
    { "\x8d\xbb\x8eR", { 75, 25 } },   // TIKEI_suna: 砂山
    { "\x8c\x8a", { 50, 50 } },   // TIKEI_ana: 穴
};
static void* s_collFile;
static int unk_02131a7c;
static fx32 s_cameraOfsX = 0xb3d7;
static int unk_02131a50;
#pragma explicit_zero_data on
static short unk_02130924 = 0;
#pragma explicit_zero_data reset
static MATHRandContext32 s_rand32;
static int unk_02130938 = 31;
static void* s_mapFile;
static ST_EFFECT_ANIM effectAnimData[11] = {
    { 0, 10, 0, 0, 0 },
    { 2, 11, 12, 0x200, 0 },
    { 3, 12, 3, 0x200, 0 },
    { 1, 16, 3, 0, 0 },
    { 5, 10, -1, 0, 0 },
    { 5, 7, 9, 0, 0 },
    { 5, 8, 16, 0, 0 },
    { 5, 9, 25, 0, 0 },
    { 5, 15, 48, 0, 0 },
    { 5, 16, 4, 0, 0 },
    { 5, 16, 42, 0, 1 },
};
static ST_GAME_START gameStart;
static UnkVramFreeEntry s_plttFreeList[16];
static int st_rank;
#pragma explicit_zero_data on
static short unk_0213092a = 0;
#pragma explicit_zero_data reset
static fx32 slimeRaceFrame;
static BSSA_EFF_WORK g_eff_work[32];
static fx32 s_cameraOfsZ = 0x15b0a;
static short s_texFreeCount;
static int unk_02131ab0;
static short unk_0213092e = 32;
static int unk_02131aa0;
static int unk_02131a78;
static int unk_02131afc[3];
static int decSutamina_data[2][4] = {
    { 0, 1, 2, 3 },
    { 0, 2, 4, 6 },
};
static int unk_02130958 = 0x40200000;
static int s_drawFin;
static int s_drawStarted;
static int unk_02130960 = 1;
static int s_pause;
static int s_bgDisp = 1;
#pragma explicit_zero_data on
static short unk_02130926 = 0;
#pragma explicit_zero_data reset
static ST_UNUSUAL_STATE_DATA unusual_state_data[16] = {
    { FATIGUE_null, 0, { 0, 9, 8, 10, 11 } },
    { FATIGUE_3, 80, { 82, 6, 2, 0, 10 } },
    { FATIGUE_3, 60, { 72, 9, 4, 0, 15 } },
    { FATIGUE_3, 40, { 62, 12, 6, 0, 20 } },
    { FATIGUE_3, 20, { 52, 15, 8, 0, 25 } },
    { FATIGUE_3, 0, { 40, 20, 10, 0, 30 } },
    { FATIGUE_2, 80, { 89, 3, 3, 0, 5 } },
    { FATIGUE_2, 60, { 80, 6, 6, 1, 7 } },
    { FATIGUE_2, 40, { 74, 8, 8, 2, 8 } },
    { FATIGUE_2, 20, { 68, 10, 10, 3, 9 } },
    { FATIGUE_2, 0, { 62, 12, 12, 4, 10 } },
    { FATIGUE_1, 80, { 100, 0, 0, 0, 0 } },
    { FATIGUE_1, 60, { 96, 0, 2, 2, 0 } },
    { FATIGUE_1, 40, { 92, 0, 4, 4, 0 } },
    { FATIGUE_1, 20, { 86, 0, 8, 6, 0 } },
    { FATIGUE_1, 0, { 80, 0, 12, 8, 0 } },
};
static int unk_02131a84;
static short unk_02131a40;
static fx32 s_fovyCos;
static SSA_DATA ssa_data_race[23] = {
    { "SlimeRace/bssa/dash_kemuri.bssa", 410 },
    { "SlimeRace/bssa/tubure_kemuri.bssa", 412 },
    { "SlimeRace/bssa/iki1.bssa", 411 },
    { "SlimeRace/bssa/iki2.bssa", 411 },
    { "SlimeRace/bssa/race_start.bssa", 413 },
    { "SlimeRace/bssa/mizusibuki.bssa", 414 },
    { "SlimeRace/bssa/slm_001.bssa", 0 },
    { "SlimeRace/bssa/slm_002.bssa", 0 },
    { "SlimeRace/bssa/slm_003.bssa", 0 },
    { "SlimeRace/bssa/slm_004.bssa", 0 },
    { "SlimeRace/bssa/slm_005.bssa", 0 },
    { "SlimeRace/bssa/slm_006.bssa", 0 },
    { "SlimeRace/bssa/slm_007.bssa", 0 },
    { "SlimeRace/bssa/slm_008.bssa", 0 },
    { "SlimeRace/bssa/slm_009.bssa", 0 },
    { "SlimeRace/bssa/slm_010.bssa", 0 },
    { "SlimeRace/bssa/slm_011.bssa", 0 },
    { "SlimeRace/bssa/slm_012.bssa", 0 },
    { "SlimeRace/bssa/slm_013.bssa", 0 },
    { "SlimeRace/bssa/slm_014.bssa", 0 },
    { "SlimeRace/bssa/slm_015.bssa", 0 },
    { "SlimeRace/bssa/slm_016.bssa", 0 },
    { "SlimeRace/bssa/star_001.bssa", 0 },
};
static int slimeRaceOrderPos[6];
static int slimeRaceOrder[6];
static SPRITE_DATA g_sprite_data[48];
static int unk_02131bb4[9];
static void* s_gateMapFile;
static int unk_02130930 = 16;
static UnkVramFreeEntry s_texFreeList[32];
static fx32 s_cameraY = 0x1d800;
static int s_raceStart = 1;
static MATHRandContext16 s_rand16;
static ST_RUN_TYPE_DATA run_type_data[RUN_TYPE_MAX] = {
    { "RUN_TYPE_null", { { 2, 3, 4, 5 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } },   // RUN_TYPE_null: RUN_TYPE_null
    { "\x88\xc0\x92\xe8\x92\x86\x83W\x83\x83\x83\x93\x83v\x8c^", { { 20, 80, 0, 0 }, { 20, 80, 0, 0 }, { 20, 60, 20, 0 }, { 0, 60, 20, 20 } } },   // RUN_TYPE_1: 安定中ジャンプ型
    { "\x96`\x8c\xaf\x91\xe5\x83W\x83\x83\x83\x93\x83v\x8c^", { { 10, 25, 65, 0 }, { 10, 30, 60, 0 }, { 40, 40, 0, 20 }, { 40, 0, 60, 0 } } },   // RUN_TYPE_2: 冒険大ジャンプ型
    { "\x98" "A\x91\xb1\x8f\xac\x83W\x83\x83\x83\x93\x83v\x8c^", { { 100, 0, 0, 0 }, { 80, 0, 0, 20 }, { 40, 20, 40, 0 }, { 80, 0, 0, 20 } } },   // RUN_TYPE_3: 連続小ジャンプ型
    { "\x8e\x9e\x81X\x83_\x83" "b\x83V\x83\x85\x8c^", { { 60, 40, 0, 0 }, { 15, 55, 0, 30 }, { 50, 10, 0, 40 }, { 0, 20, 60, 20 } } },   // RUN_TYPE_4: 時々ダッシュ型
    { "\x88\xea\x82\xa9\x94\xaa\x82\xa9\x8c^", { { 10, 10, 80, 0 }, { 10, 90, 0, 0 }, { 70, 15, 15, 0 }, { 0, 0, 100, 0 } } },   // RUN_TYPE_5: 一か八か型
    { "\x8b\xcf\x93\x99\x8c^", { { 34, 33, 33, 0 }, { 25, 25, 25, 25 }, { 25, 25, 25, 25 }, { 25, 25, 25, 25 } } },   // RUN_TYPE_6: 均等型
    { "\x90\xe6\x8ds\x93\xa6\x82\xb0\x90\xd8\x82\xe8\x8c^", { { 0, 0, 100, 0 }, { 0, 0, 80, 20 }, { 70, 30, 0, 0 }, { 100, 0, 0, 0 } } },   // RUN_TYPE_7: 先行逃げ切り型
    { "\x92\xc7\x82\xa2\x8d\x9e\x82\xdd\x8c^", { { 100, 0, 0, 0 }, { 100, 0, 0, 0 }, { 30, 30, 40, 0 }, { 0, 0, 80, 20 } } },   // RUN_TYPE_8: 追い込み型
};
UnkRaceWork s_raceWork[8];
static UnkFadeQuad s_fadeQuad = { 0, 0, 256, 192, 0, 255, 31 };
static fx32 s_fadeFrames = 0x3c000;
static int s_runTypeWork[2][5];
static UnkMiniGameHeap s_heap;
static short unk_0213092c = 22;
static void* s_gateMdlFile;
static VecFx32 s_cameraTarget;
static ST_MG_ARG* pMiniGameArg;
static int unk_02130948 = 168;
static VecFx32 s_cameraUp = { 0, FX32_ONE, 0 };
static int s_heapCreated;
static short s_plttFreeCount;
static int s_fadeState;
static int unk_02131a48;
static int slimeRaceJoutai = 8;
static NNSFndAllocator s_allocator;
static ST_ACTION_DATA action_data[ACTION_MAX] = {
    { "ACTION_null", FATIGUE_null, 0x0, 0x0, 0x0, { { 0, 0, 0 }, { 0, 0, 0 } } },   // ACTION_null: ACTION_null
    { "\x83" "A\x83" "C\x83h\x83\x8a\x83\x93\x83O", FATIGUE_null, 0x0, 0x0, 0xd000, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_idle: アイドリング
    { "\x83W\x83\x83\x83\x93\x83v\x81i\x8f\xac\x81j", FATIGUE_1, 0xa4, 0x0, 0x9000, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_jump1: ジャンプ（小）
    { "\x83W\x83\x83\x83\x93\x83v\x81i\x92\x86\x81j", FATIGUE_2, 0x11f, 0x6000, 0x10000, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_jump2: ジャンプ（中）
    { "\x83W\x83\x83\x83\x93\x83v\x81i\x91\xe5\x81j", FATIGUE_3, 0x19a, 0xa000, 0x19000, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_jump3: ジャンプ（大）
    { "\x83_\x83" "b\x83V\x83\x85", FATIGUE_3, 0x148, 0x0, 0x6000, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_dash: ダッシュ
    { "-", FATIGUE_null, 0x0, 0x0, 0x0, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_res0: -
    { "-", FATIGUE_null, 0x0, 0x0, 0x0, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_res1: -
    { "\x91\xa7\x82\xf0\x82\xc2\x82\xad\x81i\x91\xe5\x81j", FATIGUE_null, 0x0, 0x0, 0x0, { { 0, 1, 3 }, { 0, 2, 5 } } },   // ACTION_iki1: 息をつく（大）
    { "\x91\xa7\x82\xf0\x82\xc2\x82\xad\x81i\x8f\xac\x81j", FATIGUE_null, 0x0, 0x0, 0x0, { { 1, 1, 2 }, { 2, 2, 3 } } },   // ACTION_iki2: 息をつく（小）
    { "\x90Q\x82\xe9", FATIGUE_null, 0x0, 0x0, 0x0, { { 2, 2, 2 }, { 2, 2, 2 } } },   // ACTION_sleep: 寝る
    { "\x93]\x93|", FATIGUE_null, 0x0, 0x0, 0x0, { { 0, 1, 1 }, { 0, 1, 1 } } },   // ACTION_tentou: 転倒
    { "\x96\xda\x82\xf0\x89\xf1\x82\xb7", FATIGUE_null, 0x0, 0x0, 0x0, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_meMawasu: 目を回す
    { "\x96\xda\x82\xf0\x8ao\x82\xdc\x82\xb7", FATIGUE_null, 0x0, 0x0, 0x0, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_meSamasu: 目を覚ます
    { "\x8a\xec\x82\xd4\x81i\x83W\x83\x83\x83\x93\x83v\x81j", FATIGUE_null, 0x0, 0x0, 0x0, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_yorokobu1: 喜ぶ（ジャンプ）
    { "\x8a\xec\x82\xd4\x81i\x97h\x82\xea\x82\xe9\x81" "A\x83j\x83R\x83j\x83R\x8a\xe1\x81j", FATIGUE_null, 0x0, 0x0, 0x0, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_yorokobu2: 喜ぶ（揺れる、ニコニコ眼）
    { "\x8a\xec\x82\xd4\x81i\x93|\x82\xea\x82\xe9\x81" "A\x8d\x95\x96\xda\x81j", FATIGUE_null, 0x0, 0x0, 0x0, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_yorokobu3: 喜ぶ（倒れる、黒目）
    { "\x8c\xe3\x82\xeb\x82\xf0\x8c\xfc\x82\xad", FATIGUE_null, 0x0, 0x0, 0x0, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_back: 後ろを向く
    { "\x88\xda\x93\xae\x81i\x8c\xe3\x82\xeb\x8c\xfc\x82\xab\x81j", FATIGUE_null, 0xa4, 0x1000, 0xa000, { { 1, 1, 1 }, { 1, 1, 1 } } },   // ACTION_moveBack: 移動（後ろ向き）
};
static u16 s_camRotX = 0x3e00;
static int unk_02131b08[3];
static fx32 s_fovy = 0x5400;
static int slimeRaceCnt;
race::FLDObject s_fld;
static int _slimeRaceOdds[2][15];
unsigned int g_mgWorkSize;
static int unk_02130954 = 96;
static int s_actionCount[2][6];
static UnkPadState s_pad;
static int unk_02131ac4;
static int unk_02131a8c;
static NNSFndAllocator* s_pAllocator;
static int action_data_anim[ACTION_MAX] = {
    0, 6, 7, 8, 9, 10, 0, 0, 11, 12, 14, 16, 13, 15, 17, 18, 19, 20, 21,
};
static fx32 s_fadeCount;
static int s_fadeMode = -1;
static void* s_mdlFile;
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
static fx32 s_goalFrame[6];
race::FLDObject s_fldGate;
static VecFx32 s_cameraPos;
static fx32 s_passFrame = FX32_ONE;
static int unk_0213094c = 128;
static BSSA_DATA* g_bssa[23];
void* g_mgWork;

inline u32 rand32(u32 max)
{
    return MATH_Rand32(&s_rand32, max);
}

UnkMiniGameHeap* getMgHeap()
{
    if (s_heapCreated == 0) {
        s_heapCreated = 1;
        s_heap.handle = func_0207e7ac(g_mgWork, g_mgWorkSize, 0);
    }
    return &s_heap;
}

void initTouchPanel()
{
}

void startMgFade(int mode, GXRgb col, fx32 frames)
{
    s_fadeQuad.col = col;
    s_fadeMode = mode;
    s_fadeState = 1;
    s_fadeCount = 0;
    s_fadeFrames = frames;
}

void updateMgFade(fx32 passFrame)
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

BOOL isMgFadeEnd()
{
    BOOL ret = FALSE;
    if (s_fadeState == 0 || s_fadeState == 3) {
        ret = TRUE;
    }
    return ret;
}

void setMgFadeOrthoProjection()
{
    func_020760b4(0, FX32_ONE * 192, 0, FX32_ONE * 256, -FX32_ONE * 256, FX32_ONE * 256, FX32_ONE, TRUE, NULL);
    G3_StoreMtx(0);
    G3_MtxMode(1);
}

void drawMgFade(int mode)
{
    if (s_fadeState == 0) {
        return;
    }
    u8 alpha = s_fadeQuad.alpha;
    if (alpha != 0) {
        func_0207ec9c(5);
        if (mode == 0) {
            setOrthoProjection();
        } else {
            setMgFadeOrthoProjection();
        }
        G3_TexImageParam(GX_TEXFMT_NONE, GX_TEXGEN_NONE, GX_TEXSIZE_S8, GX_TEXSIZE_T8, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_USE, 0);
        G3_Identity();
        G3_Color(s_fadeQuad.col);
        G3_PolygonAttr(0, 0, 0xc0, 63, alpha, 0);
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

void set_pMGArg(ST_MG_ARG* arg)
{
    pMiniGameArg = arg;
}

ST_MG_ARG* get_pMGArg()
{
    return pMiniGameArg;
}

static void MiniGame3_init()
{
    initMgAllocator();
    initVramCache();
    initMgRand();
    slimeRace_init();
    updatePad();
    initTouchPanel();
    startMgFade(0, 0, 0x3c000);
}

static MG3_STATE MiniGame3_update(MG3_STATE MG3State, fx32* passFrame)
{
    if (MG3State == MG3_wait_end_fadeIn) {
        updateMgFade(*passFrame);
        if (isMgFadeEnd()) {
            MG3State = MG3_gameLoop;
        }
    } else if (MG3State == MG3_gameLoop) {
        updatePad();
        if (slimeRace_upDate(passFrame)) {
            SoundManager::stop(15);
            startMgFade(1, 0, 0x3c000);
            MG3State = MG3_wait_end_fadeOut;
        }
    } else if (MG3State == MG3_wait_end_fadeOut) {
        updateMgFade(*passFrame);
        if (isMgFadeEnd()) {
            slimeRace_Final();
            MG3State = MG3_end;
        }
    }
    return MG3State;
}

static void MiniGame3_draw(fx32 passFrame)
{
    if (s_drawStarted == 0) {
        s_drawStarted = 1;
        return;
    }
    slimeRace_draw();
    drawMgFade(1);
    set_drawFin();
}

int MiniGame3(MG3_STATE* pMG3State)
{
    G3_Viewport(0, 0, 255, 191);
    int ret = 0;
    func_020885e0();
    if (*pMG3State == MG3_init) {
        MiniGame3_init();
        *pMG3State = MG3_wait_end_fadeIn;
        return ret;
    }
    *pMG3State = MiniGame3_update(*pMG3State, &s_passFrame);
    if (*pMG3State == MG3_end) {
        ret = 1;
    }
    MiniGame3_draw(s_passFrame);
    return ret;
}

void initMgAllocator()
{
    void* heap = getMgHeap()->handle;
    func_0207ebe4(&s_allocator, (int)heap, 0x20);
    s_pAllocator = &s_allocator;
    func_0207e968(heap, 1);
}

void* mgAlloc(unsigned int size)
{
    return func_0207ebcc(s_pAllocator, size);
}

void mgFree(void* p)
{
    func_0207ebd8(s_pAllocator, p);
}

void* MG_LoadFile(const char* name, u32* pSize)
{
    FSFile file;
    char path[0x80];
    void* buf;
    u32 size;
    sprintf(path, "/data/%s", name);
    func_02073868(&file);
    if (func_02073a3c(&file, path)) {
        size = file.endRomOffset - file.startRomOffset;
        buf = mgAlloc(size);
        if (buf != NULL) {
            if (func_02073b58(&file, buf, size) != size) {
                mgFree(buf);
                buf = NULL;
            }
        }
        func_02073a68(&file);
        if (pSize != NULL) {
            *pSize = size;
        }
    }
    return buf;
}

u64 initMgRand()
{
    u32 data[8];
    u64 digest[2];
    OS_GetLowEntropyData(data);
    func_0208a920(digest, data, sizeof(data));
    u64 seed = digest[0] ^ digest[1];
    seed ^= (seed << 32) | (seed >> 32);
    MATH_InitRand32(&s_rand32, seed);
    MATH_InitRand16(&s_rand16, MATH_Rand32(&s_rand32, 0));
    return seed;
}

u32 rand32_min_max(u32 min, u32 max)
{
    u32 rand;
    if (max - min == 0) {
        return min;
    }
    rand = rand32(max - min + 1);
    return min + rand;
}

int randSel_intTable(int* pProbability, int num)
{
    int bunbo = 0;
    for (int i = 0; i < num; i++) {
        bunbo += pProbability[i];
    }
    if (bunbo > 0) {
        int rand = rand32(bunbo);
        for (int i = 0; i < num; i++) {
            rand -= pProbability[i];
            if (rand < 0) {
                return i;
            }
        }
    }
    return 0;
}

BOOL MG_IsUpScreen()
{
    return GX_GetDispSelect() == 0;
}

void set_drawFin()
{
    s_drawFin = 1;
}

void updatePad()
{
    u16 cont = PAD_Read();
    s_pad.trg = cont & (cont ^ s_pad.cont);
    s_pad.release = s_pad.cont & (cont ^ s_pad.cont);
    s_pad.cont = cont;
}

// sprite.cpp

int sprite_data_load_sub(int spr_id, int pal_id, int keep)
{
    void* file;
    SPRITE_DATA* data = NULL;
    SPRITE_DATA* found = NULL;
    int ret = -1;
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
        sprintf(path, "SlimeRace/sprite/%03d.NCBR", spr_id);
        file = MG_LoadFile(path, &size);
        if (file) {
            UnkG2dCharacterData* chr;
            getUnpackedCharData(file, &chr);
            UnkG2dCharacterData* c = chr;
            if (c->mapingType == 0) {
                int n;
                switch (c->W) {
                case 1:
                    n = 0;
                    break;
                case 2:
                    n = 1;
                    break;
                case 4:
                    n = 2;
                    break;
                case 8:
                    n = 3;
                    break;
                case 16:
                    n = 4;
                    break;
                case 32:
                    n = 5;
                    break;
                default:
                    n = 0;
                    break;
                }
                data->p.sizeS = n;
                switch (c->H) {
                case 1:
                    n = 0;
                    break;
                case 2:
                    n = 1;
                    break;
                case 4:
                    n = 2;
                    break;
                case 8:
                    n = 3;
                    break;
                case 16:
                    n = 4;
                    break;
                case 32:
                    n = 5;
                    break;
                default:
                    n = 0;
                    break;
                }
                data->p.sizeT = n;
            } else {
                data->p.sizeS = c->W;
                data->p.sizeT = c->H;
            }
            data->p.texFmt = c->pixelFmt;
            data->p.unk_10 = 0;
            data->p.unk_14 = 1;
            data->p.unk_18 = c->mapingType;
            data->width = 8 << data->p.sizeS;
            data->height = 8 << data->p.sizeT;
            data->texKey = mgAllocTexVram(chr->szByte);
            data->texFile = NULL;
            mgLoadTexVram(data->texKey, chr->pRawData, 0);
            mgFree(file);
        }
    } else {
        *data = *found;
    }
    sprintf(path, "SlimeRace/sprite/%03d.NCLR", pal_id);
    file = MG_LoadFile(path, &size);
    if (file) {
        UnkG2dPaletteData* pltt;
        unkfunc_02129b64(file, &pltt);
        data->plttKey = mgAllocPlttVram(pltt->szByte);
        data->texFile = NULL;
        mgLoadPlttVram(data->plttKey, pltt->pRawData, 0);
        mgFree(file);
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

void sprite_init(SPRITE* spr)
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
    SPRITE* spr = (SPRITE*)mgAlloc(sizeof(SPRITE));
    sprite_init(spr);
    spr->data_id = data_id;
    return spr;
}

void sprite_set_anim(SPRITE* spr, int ssa_id, int frame)
{
    spr->ssa_id = ssa_id;
    spr->frame = frame;
    spr->nframe = ssa_eff_get_nframe(ssa_id);
}

void sprite_activate(int data_id)
{
    SPRITE_DATA* data = &g_sprite_data[data_id];
    unsigned int texAddr = NNS_GFD_GET_TEX_KEY_ADDR(data->texKey);
    unsigned int plttAddr = NNS_GFD_GET_PLTT_KEY_ADDR(data->plttKey);

    if (data->texFile != NULL) {
        texAddr = NNS_GFD_GET_TEX_KEY_ADDR(allocCachedTexVram(data->texFile, NNS_GFD_GET_TEX_KEY_SIZE(data->texKey), 1));
    }
    if (data->plttFile != NULL) {
        plttAddr = NNS_GFD_GET_PLTT_KEY_ADDR(allocCachedPlttVram(data->plttFile, NNS_GFD_GET_PLTT_KEY_SIZE(data->plttKey), 1));
    }
    G3_TexImageParam((GXTexFmt)data->p.texFmt, GX_TEXGEN_TEXCOORD, (GXTexSizeS)data->p.sizeS, (GXTexSizeT)data->p.sizeT, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, (GXTexPlttColor0)data->p.unk_14, texAddr);
    G3_TexPlttBase(plttAddr, data->p.texFmt);
}

void ssa_sprite_draw_3D(SPRITE* spr)
{
    BSSA_DATA* bssa = ssa_eff_get_bssa(spr->ssa_id);
    sprite_activate(spr->data_id);
    bssa_draw_3D(bssa, spr->frame, spr->x, spr->y, spr->z, spr->sclX);
}

void sprite_all_free()
{
    int i;
    SPRITE_DATA* data = g_sprite_data;

    for (i = 0; i < 48; i++, data++) {
        if (data->texFile != NULL) {
            mgFree(data->texFile);
        } else if (data->texKey != 0) {
            func_02086b40(data->texKey);
        }
        if (data->plttFile != NULL) {
            mgFree(data->plttFile);
        } else if (data->plttKey != 0) {
            func_02086d84(data->plttKey);
        }
        memset(data, 0, sizeof(SPRITE_DATA));
    }
}

// ---------------------------------------------------------------------------
// ssa_eff.cpp

// DIFF: the ROM clears g_eff_work with an inlined stm zero-fill loop (mov r0-r3,#0; 0x14 x 2 stm) instead of
// a memset call, and the constants 0/1 of the loop are then in sb/r4 instead of r4/sb. Neither memset (MSL or
// dss::memset), nor struct assignment from a zero temporary/compound literal/static const, nor a word loop
// reproduce it (the temporaries are filled on the stack and copied). Same code in ov002 (0x0212cb9c).
void ssa_eff_init()
{
    unsigned int i;

    __builtin__clear(g_eff_work, sizeof(g_eff_work));
    for (i = 0; i < 23; i++) {
        g_bssa[i] = bssa_init(MG_LoadFile(ssa_data_race[i].fname, NULL));
        if (ssa_data_race[i].spr_id != 0) {
            g_bssa[i]->tex_id = sprite_data_load(ssa_data_race[i].spr_id, 1);
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
    setOrthoProjection();
    sprite_activate(g_bssa[eff_id]->tex_id);
    bssa_draw(g_bssa[eff_id], frame, x, y, z, scale);
}

void ssa_eff_draw_3D(int eff_id, int frame, int x, int y, int z, fx32 scale)
{
    sprite_activate(g_bssa[eff_id]->tex_id);
    bssa_draw_3D(g_bssa[eff_id], frame, x, y, z, scale);
}

int ssa_eff_start_3D(int eff_id, int x, int y, int z, fx32 scale, int flag)
{
    unsigned int i;
    int ret = -1;

    for (i = 0; i < 32; i++) {
        if (g_eff_work[i].flag == 0) {
            ret = i;
            break;
        }
    }
    if (ret != -1) {
        BSSA_EFF_WORK* wk = &g_eff_work[ret];
        wk->flag |= (char)flag | 0x82;
        wk->eff_id = eff_id;
        wk->x = x;
        wk->y = y;
        wk->z = z;
        wk->scale = scale;
        wk->frame = 0;
    }
    return ret;
}

int ssa_eff_update(int upScreen)
{
    unsigned int i;
    int ret = 0;
    int mask = upScreen ? 0x20 : 0x10;

    for (i = 0; i < 32; i++) {
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

// ---------------------------------------------------------------------------
// bssa_lib.cpp

void bssa_draw_prim(BSSA_PRIM* prim, BSSA_PARTS* parts, int poly_id)
{
    int u0;
    int u1;
    int v0;
    int v1;

    G3_PolygonAttr(0, 0, 0xc0, poly_id, prim->alpha, 0);
    u0 = prim->flipH ? parts->u1 : parts->u0;
    u1 = prim->flipH ? parts->u0 : parts->u1;
    v0 = prim->flipV ? parts->v1 : parts->v0;
    v1 = prim->flipV ? parts->v0 : parts->v1;
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
    BSSA_FRAME* fr;
    BSSA_PRIM* prim;
    int i;

    if (frame < 0) {
        frame = 0;
    } else if (frame >= bssa->n_frame) {
        frame = bssa->n_frame - 1;
    }
    fr = &bssa->frame[frame];
    prim = &bssa->prim[fr->prim_ofs];
    G3_PushMtx();
    G3_Color(0x7fff);
    for (i = 0; i < fr->n_prim; i++) {
        BSSA_PARTS* parts = &bssa->parts[prim->parts_id];
        G3_Identity();
        G3_Translate(x << FX32_SHIFT, y << FX32_SHIFT, (i + 1) << FX32_SHIFT);
        G3_Scale(scale, scale, FX32_ONE);
        G3_Translate(prim->pos_x << 8, prim->pos_y << 8, z << FX32_SHIFT);
        if (prim->rot_z != 0) {
            u16 rz = FX_RAD_TO_IDX(prim->rot_z);
            func_020761dc(FX_SinIdx(rz), FX_CosIdx(rz));
        }
        G3_Scale(prim->scl_x * (parts->u1 - parts->u0), prim->scl_y * (parts->v1 - parts->v0), FX32_ONE);
        bssa_draw_prim(prim, parts, i & 0x3f);
        prim++;
    }
    G3_PopMtx(1);
}

void bssa_draw_3D(BSSA_DATA* bssa, int frame, int xpos, int ypos, int zpos, fx32 scale)
{
    BSSA_FRAME* fr;
    BSSA_PRIM* prim;
    VecFx32 pos;
    MtxFx44 trans;
    fx32 x;
    fx32 y;
    fx32 z;
    int i;

    if (frame < 0) {
        frame = 0;
    } else if (frame >= bssa->n_frame) {
        frame = bssa->n_frame - 1;
    }
    fr = &bssa->frame[frame];
    prim = &bssa->prim[fr->prim_ofs];
    pos.x = xpos;
    pos.y = ypos;
    pos.z = zpos;
    worldToScreen(&pos, &x, &y, &z);
    func_02089e40(0, 192 << FX32_SHIFT, 0, 256 << FX32_SHIFT, 0, 0x1100, FX32_ONE, &trans);
    G3_MtxMode(0);
    func_02075ac8(&trans);
    G3_MtxMode(1);
    G3_PushMtx();
    G3_Color(0x7fff);
    for (i = 0; i < fr->n_prim; i++) {
        BSSA_PARTS* parts = &bssa->parts[prim->parts_id];
        G3_Identity();
        G3_Translate(x, y, z + i);
        G3_Scale(scale, scale, FX32_ONE);
        G3_Translate(prim->pos_x << 8, prim->pos_y << 8, 0);
        if (prim->rot_z != 0) {
            u16 rz = FX_RAD_TO_IDX(prim->rot_z);
            func_020761dc(FX_SinIdx(rz), FX_CosIdx(rz));
        }
        G3_Scale(prim->scl_x * (parts->u1 - parts->u0), prim->scl_y * (parts->v1 - parts->v0), FX32_ONE);
        bssa_draw_prim(prim, parts, i & 0x3f);
        prim++;
    }
    G3_PopMtx(1);
}

BSSA_DATA* bssa_init(void* data)
{
    BSSA_DATA* bssa = NULL;
    UnkBssaChunk* cnk = (UnkBssaChunk*)data;
    while (cnk->id != 0) {
        switch (cnk->id) {
        case 0x30444853:                        // SHD0
            bssa = (BSSA_DATA*)(cnk + 1);
            break;
        case 0x30524653:                        // SFR0
            bssa->frame = (BSSA_FRAME*)(cnk + 1);
            break;
        case 0x30545053:                        // SPT0
            bssa->parts = (BSSA_PARTS*)(cnk + 1);
            break;
        case 0x30525053:                        // SPR0
            bssa->prim = (BSSA_PRIM*)(cnk + 1);
            break;
        }
        cnk = (UnkBssaChunk*)((u8*)cnk + cnk->size + sizeof(UnkBssaChunk));
    }
    return bssa;
}

void initVramCache()
{
    s_texFreeCount = 0;
    s_plttFreeCount = 0;
}


void releaseVramCache()
{
    int i;
    for (i = 0; i < s_texFreeCount; i++) {
        mgFreeTexVram(s_texFreeList[i].key);
    }
    s_texFreeCount = 0;
    for (i = 0; i < s_plttFreeCount; i++) {
        mgFreePlttVram(s_plttFreeList[i].key);
    }
    s_plttFreeCount = 0;
}

int mgLoadTexVram(unsigned int key, void* data, int vblank)
{
    unsigned int addr = (key & 0xffff) << 3;
    unsigned int size = ((key & 0x7fff0000) >> 16) << 4;
    if (vblank) {
        return func_020867d0(0, addr, data, size);
    }
    DC_PurgeRange(data, size);
    func_02076e98();
    func_02076ef4(data, addr, size);
    func_02077034();
    return 1;
}

int mgLoadPlttVram(unsigned int key, void* data, int vblank)
{
    unsigned int addr = (key & 0xffff) << 3;
    unsigned int size = ((key & 0xffff0000) >> 16) << 3;
    if (vblank) {
        return func_020867d0(1, addr, data, size);
    }
    DC_PurgeRange(data, size);
    func_02077080();
    func_020770b4(data, addr, size);
    func_02077120();
    return 1;
}

unsigned int mgAllocTexVram(unsigned int size)
{
    return func_02086adc(size, 0, 1);
}

void mgFreeTexVram(unsigned int key)
{
    func_02086b40(key);
}

unsigned int mgAllocPlttVram(unsigned int size)
{
    return func_02086d00(size, 0, 1);
}

void mgFreePlttVram(unsigned int key)
{
    func_02086d84(key);
}

unsigned int allocCachedTexVram(void* data, unsigned int size, int load)
{
    unsigned int key;
    int i;
    for (i = 0; i < s_texFreeCount; i++) {
        if (s_texFreeList[i].data == data) {
            return s_texFreeList[i].key;
        }
    }
    key = func_02086adc(size, 0, 1);
    s_texFreeList[s_texFreeCount].data = data;
    s_texFreeList[s_texFreeCount].key = key;
    s_texFreeCount++;
    if (load) {
        mgLoadTexVram(key, data, 1);
    }
    return key;
}

unsigned int allocCachedPlttVram(void* data, unsigned int size, int load)
{
    unsigned int key;
    int i;
    for (i = 0; i < s_plttFreeCount; i++) {
        if (s_plttFreeList[i].data == data) {
            return s_plttFreeList[i].key;
        }
    }
    key = func_02086d00(size, 0, 1);
    s_plttFreeList[s_plttFreeCount].data = data;
    s_plttFreeList[s_plttFreeCount].key = key;
    s_plttFreeCount++;
    if (load) {
        mgLoadPlttVram(key, data, 1);
    }
    return key;
}

void setOrthoProjection()
{
    func_020760b4(0, 192 * FX32_ONE, 0, 256 * FX32_ONE, -1024 * FX32_ONE, 1024 * FX32_ONE, FX32_ONE, 1, NULL);
    G3_StoreMtx(0);
    G3_MtxMode(1);
}

// world position to screen position (fx32), returns -1 outside of the view volume
// DIFF: only the scheduling of the three FX_Mul32x64c roundings: the ROM interleaves the x/y/z 64-bit products and
// uses `adds rX, rX, #0x80000000` immediates each time, ours computes x first then keeps 0x80000000/0 in lr/r5 for y
// and z (function is 4 bytes longer). Everything before (projection) and after (viewport, *px/*py/*pz) matches.
int worldToScreen(const VecFx32* world, fx32* px, fx32* py, fx32* pz)
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
    w = (fx32)(((fx64)vec.x * proj->m[0][3] + (fx64)vec.y * proj->m[1][3] + (fx64)vec.z * proj->m[2][3]) >> FX32_SHIFT);
    w += proj->m[3][3];
    FX_InvAsync(w);
    x = (fx32)(((fx64)vec.x * proj->m[0][0] + (fx64)vec.y * proj->m[1][0] + (fx64)vec.z * proj->m[2][0]) >> FX32_SHIFT);
    x += proj->m[3][0];
    y = (fx32)(((fx64)vec.x * proj->m[0][1] + (fx64)vec.y * proj->m[1][1] + (fx64)vec.z * proj->m[2][1]) >> FX32_SHIFT);
    y += proj->m[3][1];
    z = (fx32)(((fx64)vec.x * proj->m[0][2] + (fx64)vec.y * proj->m[1][2] + (fx64)vec.z * proj->m[2][2]) >> FX32_SHIFT);
    z += proj->m[3][2];
    inv = FX_GetDivResultFx64c();
    x = FX_Mul32x64c(x, inv);
    y = FX_Mul32x64c(y, inv);
    z = FX_Mul32x64c(z, inv);
    x = (x + FX32_ONE) / 2;
    y = (y + FX32_ONE) / 2;
    z = (z + FX32_ONE) / 2;

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

// NNS_G2dUnpackNCG
void unpackCharData(UnkG2dCharacterData* data)
{
    data->pRawData = (void*)((unsigned int)data->pRawData + (unsigned int)data);
}

// NNS_G2dGetUnpackedCharacterData
int getUnpackedCharData(void* file, UnkG2dCharacterData** out)
{
    NNSG2dBinaryBlockHeader* block = func_0207ebf8(file, 0x43484152);   // CHAR
    if (block == NULL) {
        *out = NULL;
        return 0;
    }
    unpackCharData((UnkG2dCharacterData*)(block + 1));
    *out = (UnkG2dCharacterData*)(block + 1);
    return 1;
}

// NNS_G2dUnpackNCL
void unpackPaletteData(UnkG2dPaletteData* data)
{
    data->pRawData = (void*)((unsigned int)data->pRawData + (unsigned int)data);
}

// NNS_G2dGetUnpackedPaletteData
int unkfunc_02129b64(void* file, UnkG2dPaletteData** out)
{
    NNSG2dBinaryBlockHeader* block = func_0207ebf8(file, 0x504c5454);   // PLTT
    if (block == NULL) {
        *out = NULL;
        return 0;
    }
    unpackPaletteData((UnkG2dPaletteData*)(block + 1));
    *out = (UnkG2dPaletteData*)(block + 1);
    return 1;
}

// with --loose only differs by the pool layout: in the ROM s_fldGate.m_box_test is more than 4095 bytes from
// the pool base so the last store goes through an extra literal (0x02132a40 = pool+0x1000)
void SlimeRace_init_BG(int no)
{
    unsigned int size;
    char fname[128];

    sprintf(fname, "SlimeRace/map/ev%02d.map", no);
    s_mapFile = MG_LoadFile(fname, &size);
    sprintf(fname, "SlimeRace/map/ev%02d.nsbmd", no);
    s_mdlFile = MG_LoadFile(fname, &size);
    sprintf(fname, "SlimeRace/map/ev%02d.col", no);
    s_collFile = MG_LoadFile(fname, &size);
    s_fld.Setup(s_mdlFile, s_mapFile, s_collFile, (int)getMgHeap()->handle);
    s_fld.m_box_test = 1;
    no = (no & 1) ? 1 : 2;
    sprintf(fname, "SlimeRace/map/gate%02d.map", no);
    s_gateMapFile = MG_LoadFile(fname, &size);
    sprintf(fname, "SlimeRace/map/gate%02d.nsbmd", no);
    s_gateMdlFile = MG_LoadFile(fname, &size);
    s_fldGate.Setup(s_gateMdlFile, s_gateMapFile, NULL, (int)getMgHeap()->handle);
    s_fldGate.m_box_test = 1;
}

SPRITE* SlimeRace_init_Chara(int id, int keep)
{
    return sprite_create(sprite_data_load_sub(0x191, id + 0x191, keep));
}

void setupRaceCamera(fx32 x, int opt)
{
    fx32 camZ;
    fx32 tgtZ;
    fx32 min;
    u16 idx = (u16)((s_fovy * 0xB60B60B60BLL + 0x80000000000LL) >> 44);
    s_fovySin = FX_SinIdx(idx);
    s_fovyCos = FX_CosIdx(idx);
    func_02089cf4(s_fovySin, s_fovyCos, 0x1555, 0xa000, 0xc8000, FX32_ONE, &data_02124bb4.projMtx);
    data_02124bb4.flag &= ~0x50;
    tgtZ = x;
    min = -0x3199;
    if (MG_IsUpScreen()) {
        min = (fx32)0x80000000;
        tgtZ = x - s_cameraOfsX;
    }
    tgtZ = (tgtZ > 0x40000) ? 0x40000 : ((tgtZ < min) ? min : tgtZ);
    camZ = (x > 0x40000) ? 0x40000 : ((x < min) ? min : x);
    s_cameraTarget.z = tgtZ;
    s_cameraPos.y = s_cameraY;
    s_cameraPos.z = camZ + s_cameraOfsZ;
    data_02124bb4.camPos = s_cameraPos;
    data_02124bb4.camUp = s_cameraUp;
    data_02124bb4.camTarget = s_cameraTarget;
    func_02089528(&s_cameraPos, &s_cameraUp, &s_cameraTarget, &data_02124bb4.cameraMtx);
    data_02124bb4.flag &= ~0xe8;
}

ST_SLIME_RACE* get_pSlimeRace(int id)
{
    if (id < 0 || id >= 6) {
        id = 0;
    }
    return &slimeRace[id];
}

int get_id_pSlimeRace(ST_SLIME_RACE* pSlimeRace)
{
    return pSlimeRace - slimeRace;
}

void gameStart_init()
{
    gameStart.frame = 0;
    gameStart.st = GAME_START_ST_null;
}

void gameStart_update(fx32 passFrame)
{
    if (gameStart.st != GAME_START_ST_disp) {
        return;
    }
    if (!MG_IsUpScreen()) {
        return;
    }
    gameStart.frame += passFrame;
    if (gameStart.frame >= ssa_eff_get_nframe(4) << FX32_SHIFT) {
        gameStart.st = GAME_START_ST_end;
    }
}

void gameStart_draw()
{
}

void setupCamera()
{
    func_02089e40(FX32_ONE * 96, -FX32_ONE * 96, -FX32_ONE * 128, FX32_ONE * 128, -FX32_ONE * 1024, FX32_ONE * 1024,
                  FX32_ONE, &data_02124bb4.projMtx);
    data_02124bb4.flag &= ~0x50;
    u16 idx = s_camRotX;
    func_02088dd0(&data_02124bb4.cameraMtx, FX_SinIdx(idx), FX_CosIdx(idx));
    if (MG_IsUpScreen()) {
        data_02124bb4.cameraMtx.m[3][1] = -FX32_ONE * 96;
    } else {
        data_02124bb4.cameraMtx.m[3][1] = FX32_ONE * 96;
    }
}

// DIFF: register allocation only (same instructions/shape, same size 0x2f8). ROM: first loop keeps
// slimeRaceOrder/-1/vote/s_goalFrame in r6/r5/r7/fp (ours r7/r6/fp/r5); second loop voteSum=r4,
// sutamina=r5, pSlimeRace=r6 (ours r6/r4/r5); odds loop i=fp j=sb vote=r8 voteSum*200=r7 (ours fp/r8/r7/sb).
// Declaration order of the locals does not change it (all permutations tried). In the full TU the
// pool layout also makes st_rank/slimeRaceCnt non adjacent (avoid an stm: keep them apart in the pool).
void slimeRace_init()
{
    static int vote[6];
    fx32 posX0;
    fx32 posXW;
    int voteSum;
    int* pRank;
    int* pBets;
    int* pOdds;

    unkfunc_0212b594();
    get_pMGArg()->slRace.bedCoin = 0;
    get_pMGArg()->slRace.gainCoin = 0;
    get_pMGArg()->slRace.rankNakamaSlime = 0;
    pRank = get_pMGArg()->slRace.rank;
    for (int i = 0; i < 6; i++) {
        vote[i] = 0;
        slimeRaceOrder[i] = 0;
        pRank[i] = -1;
        s_goalFrame[i] = 0;
        ST_SLIME_RACE* pSlimeRace = get_pSlimeRace(i);
        pSlimeRace->sutamina = 0;
        pSlimeRace->decSutamina = 0;
        pSlimeRace->runType = RUN_TYPE_null;
        pSlimeRace->state = STATE_null;
        pSlimeRace->action = ACTION_null;
        pSlimeRace->repeat = 0;
        pSlimeRace->frame = 0;
        pSlimeRace->trans.x = 0;
        pSlimeRace->trans.y = 0;
        pSlimeRace->trans.z = 0;
        pSlimeRace->sprite = NULL;
        pSlimeRace->sprite2 = NULL;
        pSlimeRace->rank = 0;
        pSlimeRace->dir = 1;
        pSlimeRace->dirChg = 0;
        pSlimeRace->effTimes = 0;
    }
    pOdds = get_pSlimeRaceOdds();
    pBets = get_pSlimeRaceBets();
    for (int i = 0; i < 15; i++) {
        *pOdds++ = 0;
        *pBets++ = 0;
    }
    slimeRaceFrame = 0;
    slimeRaceCnt = 6;
    if (get_pMGArg()->slRace.nakamaSlime == NAKAMA_SLIME_nonEntry) {
        slimeRaceCnt = 5;
    }
    posX0 = -0x3333;
    posXW = 0x18f5;
    if (get_pMGArg()->slRace.bgMap == RACE_BG_MAP_ev2 || get_pMGArg()->slRace.bgMap == RACE_BG_MAP_ev4) {
        posX0 = -0x34cc;
        posXW = 0x14cc;
    }
    voteSum = 0;
    for (int i = 0; i < slimeRaceCnt; i++) {
        ST_SLIME_RACE* pSlimeRace = get_pSlimeRace(i);
        int sutamina = rand32_min_max(60, 100);
        RUN_TYPE runType = (RUN_TYPE)rand32_min_max(1, 8);
        pSlimeRace->sutamina = sutamina;
        pSlimeRace->runType = runType;
        sutamina -= 58;
        sutamina *= sutamina;
        voteSum += sutamina;
        vote[i] = sutamina;
        pSlimeRace->sprite = SlimeRace_init_Chara(i, 1);
        pSlimeRace->sprite2 = SlimeRace_init_Chara(i, 1);
        pSlimeRace->trans.x = posX0 + posXW * i;
        pSlimeRace->trans.y = 0;
        pSlimeRace->trans.z = -0xc000;
        pSlimeRace->state = STATE_stage0;
    }
    pOdds = get_pSlimeRaceOdds();
    voteSum *= 200;
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 6; j++) {
            if (vote[j] > 0) {
                int v = voteSum / (vote[i] + vote[j]);
                *pOdds = v / 10;
                if (v % 10 >= 5) {
                    (*pOdds)++;
                }
                if (*pOdds < 11) {
                    *pOdds = 11;
                } else if (*pOdds > 9999) {
                    *pOdds = 9999;
                }
            }
            pOdds++;
        }
    }
    ssa_eff_init();
    SlimeRace_init_BG(get_pMGArg()->slRace.bgMap + 1);
    gameStart_init();
    set_slimeRaceJoutai(8);
}

ACTION slimeRace_get_action_runType(ST_SLIME_RACE* pSlimeRace, RACE_STAGE raceStage)
{
    ACTION action = ACTION_null;
    if (raceStage >= RACE_STAGE_0 && raceStage < RACE_STAGE_MAX) {
        int* pProbability = get_slimeRace_run_type_data(pSlimeRace->runType, 1) + raceStage * 4;
        int* pAction = get_slimeRace_run_type_data(RUN_TYPE_null, 1);
        int num = 4;
        if (raceStage == RACE_STAGE_0) {
            int i;
            for (i = 0; i < 3; i++) {
                s_runTypeWork[0][i] = pProbability[i];
                s_runTypeWork[1][i] = pAction[i];
            }
            s_runTypeWork[0][i] = (100 - pSlimeRace->sutamina) / 2;
            s_runTypeWork[1][i] = ACTION_sleep;
            i++;
            s_runTypeWork[0][i] = 20 - s_runTypeWork[0][i];
            s_runTypeWork[1][i] = ACTION_idle;
            pProbability = s_runTypeWork[0];
            pAction = s_runTypeWork[1];
            num = 5;
        }
        action = (ACTION)pAction[randSel_intTable(pProbability, num)];
    }
    return action;
}

TIKEI slimeRace_get_ashimoto_tikei(ST_SLIME_RACE* pSlimeRace)
{
    VecFx32 new_pos;
    new_pos.x = pSlimeRace->trans.x;
    new_pos.y = pSlimeRace->trans.y;
    new_pos.z = pSlimeRace->trans.z;
    return (TIKEI)(u16)race::coll_CheckWallId(s_fld.m_coll, &new_pos, 0x733);
}

ACTION slimeRace_get_action_tikei(ST_SLIME_RACE* pSlimeRace)
{
    ACTION action = ACTION_null;
    TIKEI tikei = slimeRace_get_ashimoto_tikei(pSlimeRace);
    if (tikei != TIKEI_null) {
        int* pProbability = get_slimeRace_tikei_data(tikei, 1);
        int* pAction = get_slimeRace_tikei_data(TIKEI_null, 1);
        action = (ACTION)pAction[randSel_intTable(pProbability, 2)];
    }
    return action;
}

ACTION slimeRace_get_action_afterAction(ST_SLIME_RACE* pSlimeRace)
{
    ACTION action = ACTION_null;
    FATIGUE fatigue = (FATIGUE)get_slimeRace_action_data(pSlimeRace->action, 1);
    int sutamina = pSlimeRace->sutamina;
    for (int i = 1; i < get_UNUSUAL_STATE_MAX(); i++) {
        if (fatigue == get_slimeRace_unusual_state_data(i, 0) && sutamina >= get_slimeRace_unusual_state_data(i, 1)) {
            int* pProbability = (int*)get_slimeRace_unusual_state_data(i, 2);
            int* pAction = (int*)get_slimeRace_unusual_state_data(0, 2);
            action = (ACTION)pAction[randSel_intTable(pProbability, 5)];
            break;
        }
    }
    return action;
}

int slimeRace_get_action_repeat(ST_SLIME_RACE* pSlimeRace, RACE_STAGE raceStage, ACTION action)
{
    int repeat = 1;
    switch (raceStage) {
    case RACE_STAGE_0:
        if (action == ACTION_sleep) {
            repeat = 3;
        }
        break;
    case RACE_STAGE_1:
    case RACE_STAGE_2:
    case RACE_STAGE_3: {
        FATIGUE fatigue = (FATIGUE)get_slimeRace_action_data(pSlimeRace->action, 1);
        int fatigueOffset = fatigue - 1;
        if (fatigueOffset < 0) {
            repeat = 1;
        } else {
            int (*repeatData)[3] = (int (*)[3])get_slimeRace_action_data(action, 7);
            int min = repeatData[0][fatigueOffset];
            int max = repeatData[1][fatigueOffset];
            repeat = rand32_min_max(min, max);
        }
        break;
    }
    }
    return repeat;
}

int slimeRace_chk_ashitome(ST_SLIME_RACE* pSlimeRace)
{
    return 0;
}

ACTION slimeRace_upDate_action_raceStage(ST_SLIME_RACE* pSlimeRace, RACE_STAGE raceStage, int* pRepeat)
{
    ACTION action = ACTION_null;
    int repeat = 0;
    int id = get_id_pSlimeRace(pSlimeRace);
    if (slimeRace_chk_ashitome(pSlimeRace)) {
        action = ACTION_meMawasu;
        repeat = 1;
    } else {
        if (raceStage != RACE_STAGE_0 && get_slimeRace_action_data(pSlimeRace->action, 1) != FATIGUE_null) {
            s_actionCount[0][id]++;
            action = slimeRace_get_action_tikei(pSlimeRace);
            if (action == ACTION_null) {
                action = slimeRace_get_action_afterAction(pSlimeRace);
            }
            if (action != ACTION_null) {
                repeat = slimeRace_get_action_repeat(pSlimeRace, raceStage, action);
            }
        }
        if (action != ACTION_null && repeat > 0) {
            s_actionCount[1][id]++;
        } else {
            action = slimeRace_get_action_runType(pSlimeRace, raceStage);
            repeat = slimeRace_get_action_repeat(pSlimeRace, raceStage, action);
        }
    }
    if (pRepeat != NULL) {
        *pRepeat = repeat;
    }
    return action;
}

RACE_STAGE getRaceStage(STATE state)
{
    switch (state) {
    case STATE_stage0:
        return RACE_STAGE_0;
    case STATE_stage1:
        return RACE_STAGE_1;
    case STATE_stage2:
        return RACE_STAGE_2;
    case STATE_stage3:
        return RACE_STAGE_3;
    }
    return RACE_STAGE_null;
}

void slimeRace_upDate_sutamina(ST_SLIME_RACE* pSlimeRace, ACTION action)
{
    int sutamina = pSlimeRace->sutamina - pSlimeRace->decSutamina;
    if (sutamina < 0) {
        sutamina = 0;
    }
    pSlimeRace->sutamina = sutamina;
    int offset = 0;
    if (action == pSlimeRace->action) {
        offset = 1;
    }
    FATIGUE fatigue = (FATIGUE)get_slimeRace_action_data(action, 1);
    pSlimeRace->decSutamina = decSutamina_data[offset][fatigue];
}

void slimeRace_upDate_action_change(ST_SLIME_RACE* pSlimeRace)
{
    int repeat = 1;
    ACTION action = ACTION_null;
    switch (pSlimeRace->action) {
    case ACTION_tentou: {
        int rand = rand32(100);
        if (rand < 25) {
            action = ACTION_meMawasu;
        }
        break;
    }
    case ACTION_sleep:
        action = ACTION_meSamasu;
        break;
    default:
        switch (pSlimeRace->state) {
        case STATE_toGate:
            action = ACTION_jump1;
            break;
        case STATE_inGate:
            action = ACTION_idle;
            break;
        case STATE_goal:
            pSlimeRace->action = ACTION_null;
            action = slimeRace_upDate_action_raceStage(pSlimeRace, RACE_STAGE_3, NULL);
            break;
        case STATE_goal2:
            switch (pSlimeRace->rank) {
            case 1:
                action = ACTION_yorokobu1;
                break;
            case 2:
                action = ACTION_yorokobu2;
                break;
            case 3:
                action = ACTION_yorokobu3;
                break;
            default:
                action = ACTION_idle;
                break;
            }
            break;
        default: {
            RACE_STAGE raceStage = getRaceStage(pSlimeRace->state);
            if (raceStage != RACE_STAGE_null) {
                action = slimeRace_upDate_action_raceStage(pSlimeRace, raceStage, &repeat);
                if (raceStage != RACE_STAGE_0) {
                    slimeRace_upDate_sutamina(pSlimeRace, action);
                }
            }
            break;
        }
        }
        break;
    }
    pSlimeRace->action = action;
    pSlimeRace->repeat = repeat;
}

void slimeRace_upDate_action(ST_SLIME_RACE* pSlimeRace)
{
    int actFin = 0;
    if (pSlimeRace->action == ACTION_null) {
        pSlimeRace->repeat = 0;
        actFin = 1;
    } else {
        int anim = get_slimeRace_action_data(pSlimeRace->action, 8);
        if (pSlimeRace->frame > ssa_eff_get_nframe(anim) << FX32_SHIFT) {
            actFin = 1;
        }
    }
    if (actFin == 0) {
        return;
    }
    pSlimeRace->frame = 0;
    pSlimeRace->repeat--;
    pSlimeRace->effTimes = 0;
    if (pSlimeRace->repeat > 0) {
        return;
    }
    if (pSlimeRace->dirChg != 0) {
        pSlimeRace->dirChg = 0;
        pSlimeRace->dir *= -1;
        pSlimeRace->action = ACTION_back;
        pSlimeRace->repeat = 1;
        return;
    }
    if (pSlimeRace->dir < 0) {
        pSlimeRace->action = ACTION_moveBack;
        pSlimeRace->repeat = 1;
        return;
    }
    slimeRace_upDate_action_change(pSlimeRace);
}

int get_slimeRaceOdds_offset(int a, int b)
{
    if (a > b) {
        int t = a;
        a = b;
        b = t;
    }
    int j, i;
    int c = 0;
    for (i = 0, j = 5; i < a; i++, j--) {
        c += j;
    }
    return c + (b - a - 1);
}

void get_slimeRaceOdds_offset2(int c, int* a, int* b)
{
    static int _data[15][2] = {
        { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 },
        { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 },
        { 2, 3 }, { 2, 4 }, { 2, 5 },
        { 3, 4 }, { 3, 5 },
        { 4, 5 },
    };
    *a = _data[c][0];
    *b = _data[c][1];
}


void slimeRace_update_state(ST_SLIME_RACE* pSlimeRace, STATE stateMax)
{
    if (stateMax > pSlimeRace->state) {
        pSlimeRace->state = (STATE)(pSlimeRace->state + 1);
        if (pSlimeRace->state == STATE_goal && pSlimeRace->rank == 0) {
            int id = get_id_pSlimeRace(pSlimeRace);
            int* pRank = get_pMGArg()->slRace.rank;
            int rank = st_rank;
            pRank[rank] = id;
            s_goalFrame[rank] = slimeRaceFrame;
            rank++;
            st_rank = rank;
            pSlimeRace->rank = rank;
            if (rank == 2) {
                set_slimeRaceJoutai(4);
                slimeRaceFrame = 0;
                int* pOdds = get_pSlimeRaceOdds();
                int* pBets = get_pSlimeRaceBets();
                int c = get_slimeRaceOdds_offset(pRank[0], pRank[1]);
                int x10_coin = pOdds[c] * pBets[c];
                get_pMGArg()->slRace.gainCoin = x10_coin / 10;
                if (x10_coin % 10 >= 5) {
                    get_pMGArg()->slRace.gainCoin++;
                }
            }
            if (id == 5) {
                get_pMGArg()->slRace.rankNakamaSlime = get_pSlimeRace(5)->rank;
            }
        }
    }
    if (pSlimeRace->state != STATE_stage0) {
        pSlimeRace->dir = 1;
        pSlimeRace->dirChg = 0;
    } else {
        pSlimeRace->dirChg = 1;
    }
}

void slimeRace_upDate_trans_sub(ST_SLIME_RACE* pSlimeRace, fx32 max, fx32 max2, STATE stateMax)
{
    if (pSlimeRace->dir >= 0) {
        if (max <= pSlimeRace->trans.z) {
            if (max2 < pSlimeRace->trans.z) {
                pSlimeRace->trans.z = max2;
            }
            slimeRace_update_state(pSlimeRace, stateMax);
        }
    } else {
        if (max >= pSlimeRace->trans.z) {
            if (max2 > pSlimeRace->trans.z) {
                pSlimeRace->trans.z = max2;
            }
            slimeRace_update_state(pSlimeRace, stateMax);
        }
    }
}

// DIFF: instruction scheduling only around FX_Mul / the trans.z update (ROM: adc before lsr, dir loaded
// before trans.z, `mov r2, #0x36000` hoisted above the mla; registers r3/r2 swapped for dMove/max2).
// Tried: decl orders of max/max2/stateMax, dir * dMove, z = z + ..., explicit fx64 forms, inline +=, default case.
void slimeRace_upDate_trans(ST_SLIME_RACE* pSlimeRace, fx32 passFrame)
{
    fx32 startFrame = get_slimeRace_action_data(pSlimeRace->action, 3);
    fx32 endFrame = get_slimeRace_action_data(pSlimeRace->action, 4);
    fx32 frame = pSlimeRace->frame;
    if (frame != 0 && startFrame < frame && endFrame >= frame) {
        fx32 speed = get_slimeRace_action_data(pSlimeRace->action, 2);
        fx32 dMove = FX_Mul(speed, passFrame);
        dMove *= pSlimeRace->dir;
        pSlimeRace->trans.z += dMove;
        fx32 max = 0x7fffffff;
        fx32 max2 = 0x36000;
        STATE stateMax = STATE_null;
        switch (pSlimeRace->state) {
        case STATE_stage0:
            stateMax = STATE_stage0;
            if (pSlimeRace->dir >= 0) {
                max = 0x36000 - 0x3f800;
            } else {
                max = 0x36000 - 0x42000;
            }
            max2 = max;
            break;
        case STATE_toGate:
        case STATE_inGate:
            max = -0x3199;
            stateMax = STATE_inGate;
            max2 = max;
            break;
        case STATE_stage1:
            max = 0xa000;
            stateMax = STATE_stage2;
            break;
        case STATE_stage2:
            max = 0x28000;
            stateMax = STATE_stage3;
            break;
        case STATE_stage3:
            max = 0x31000;
            stateMax = STATE_goal;
            break;
        case STATE_goal:
        case STATE_goal2:
            max = 0x34000;
            stateMax = STATE_goal2;
            break;
        }
        slimeRace_upDate_trans_sub(pSlimeRace, max, max2, stateMax);
    }
}

void slimeRaceOrder_update()
{
    int* pOrder = slimeRaceOrder;
    for (int i = 0; i < slimeRaceCnt; i++) {
        int z = get_pSlimeRace(i)->trans.z;
        slimeRaceOrderPos[i] = z;
        pOrder[i] = i;
        for (int j = 0; j < i; j++) {
            if (z > slimeRaceOrderPos[j]) {
                for (int k = i; k >= j + 1; k--) {
                    slimeRaceOrderPos[k] = slimeRaceOrderPos[k - 1];
                    pOrder[k] = pOrder[k - 1];
                }
                slimeRaceOrderPos[j] = z;
                pOrder[j] = i;
                break;
            }
        }
    }
}

int slimeRaceOdds_get_sum()
{
    int* pBets = get_pSlimeRaceBets();
    int sum = 0;
    for (int i = 0; i < 15; i++) {
        sum += pBets[i];
    }
    return sum;
}

BOOL slimeRace_chk_state_all(STATE state)
{
    for (int i = 0; i < slimeRaceCnt; i++) {
        if (state != get_pSlimeRace(i)->state) {
            return FALSE;
        }
    }
    return TRUE;
}

void slimeRace_chg_state_all(STATE state)
{
    for (int i = 0; i < slimeRaceCnt; i++) {
        ST_SLIME_RACE* pSlimeRace = get_pSlimeRace(i);
        pSlimeRace->state = state;
        switch (state) {
        case STATE_toGate:
        case STATE_inGate:
        case STATE_stage1:
            pSlimeRace->action = ACTION_null;
            pSlimeRace->dir = 1;
            pSlimeRace->dirChg = 0;
            break;
        }
    }
}

void slimeRace_upDate_joutai_to_gate()
{
    if (gameStart.st == GAME_START_ST_null) {
        if (slimeRace_chk_state_all(STATE_inGate)) {
            gameStart.st = GAME_START_ST_end;
        }
    } else if (gameStart.st == GAME_START_ST_end) {
        gameStart.st = GAME_START_ST_end2;
        SoundManager::play(0x35, 15);
        slimeRaceFrame = 0;
    } else if (gameStart.st == GAME_START_ST_end2) {
        if (slimeRaceFrame > 0x104000) {
            s_fldGate.setEventAnimation(1);
            gameStart.st = GAME_START_ST_end3;
            slimeRaceFrame = 0;
        }
    } else if (gameStart.st == GAME_START_ST_end3) {
        if (slimeRaceFrame > 0x1e000) {
            slimeRace_chg_state_all(STATE_stage1);
            slimeRaceFrame = 0;
            set_slimeRaceJoutai(3);
            SoundManager::play(0x1d, 15);
        }
    }
}

BOOL slimeRace_upDate_joutai()
{
    switch (get_slimeRaceJoutai()) {
    case 8:
        if (get_pMGArg()->slRace.nakamaSlime == NAKAMA_SLIME_entry_nonBet) {
            set_slimeRaceJoutai(1);
        } else {
            set_slimeRaceJoutai(0);
            SoundManager::play(8, 15);
        }
        break;
    case 1:
        get_pMGArg()->slRace.bedCoin = slimeRaceOdds_get_sum();
        s_raceStart = 1;
        slimeRace_chg_state_all(STATE_toGate);
        set_slimeRaceJoutai(2);
        SoundManager::stop(0x3c);
        break;
    case 2:
        slimeRace_upDate_joutai_to_gate();
        break;
    case 4:
        if (slimeRaceFrame > 0x5a000) {
            set_slimeRaceJoutai(5);
            SoundManager::play(0x36, 15);
        }
        break;
    case 5:
        if (slimeRace_chk_state_all(STATE_goal2)) {
            set_slimeRaceJoutai(6);
        }
        break;
    case 7:
        return TRUE;
    }
    return FALSE;
}

bool slimeRace_upDate(fx32* pPassFrame)
{
    if (s_pause == 0) {
        gameStart_update(*pPassFrame);
        if (slimeRace_upDate_joutai()) {
            return true;
        }
        for (int i = 0; i < slimeRaceCnt; i++) {
            ST_SLIME_RACE* pSlimeRace = get_pSlimeRace(i);
            if (pSlimeRace->state != STATE_null) {
                slimeRace_upDate_action(pSlimeRace);
                slimeRace_upDate_trans(pSlimeRace, *pPassFrame);
                slimeRaceOrder_update();
                if (MG_IsUpScreen()) {
                    pSlimeRace->frame += *pPassFrame;
                }
            }
        }
        slimeRaceFrame += *pPassFrame;
    }
    s_fld.calc();
    s_fldGate.calc();
    return false;
}

void unkfunc_0212b0b8()
{
}

void effectAnim_sub(ST_SLIME_RACE* pSlimeRace)
{
    int anim = get_slimeRace_action_data(pSlimeRace->action, 8);
    int frame = pSlimeRace->frame >> 12;
    SPRITE* sprite = pSlimeRace->sprite;
    int start = 0;
    int max = 4;
    if (slimeRace_get_ashimoto_tikei(pSlimeRace) == TIKEI_mizu) {
        start = 5;
        max = 11;
    }
    for (int i = start; i < max; i++) {
        ST_EFFECT_ANIM* eff = &effectAnimData[i];
        if (anim == eff->slimeAnim && frame >= eff->startFrame - 2 && pSlimeRace->effTimes == eff->times) {
            ssa_eff_start_3D(eff->EffectAnim, sprite->x, sprite->y, sprite->z + eff->dZ, FX32_ONE, 0x30);
            if (eff->startFrame >= 0) {
                pSlimeRace->effTimes++;
            }
            return;
        }
    }
}

void slimeRace_draw()
{
    fx32 z0;
    int anim;
    ST_SLIME_RACE* pSlimeRace0 = get_pSlimeRace(0);
    z0 = -0x3199;
    if (pSlimeRace0->state >= STATE_stage1) {
        int* pRank = get_pMGArg()->slRace.rank;
        if (pRank[0] >= 0) {
            pSlimeRace0 = get_pSlimeRace(pRank[0]);
        } else {
            pSlimeRace0 = get_pSlimeRace(slimeRaceOrder[0]);
        }
        z0 = pSlimeRace0->trans.z;
    }
    setupRaceCamera(z0, 0);
    if (s_bgDisp) {
        NNS_G3dGlbPerspectiveW(s_fovySin, s_fovyCos, 0x1555, 0x14000, 0xc8000, FX32_ONE);
        s_fldGate.draw();
        NNS_G3dGlbPerspectiveW(s_fovySin, s_fovyCos, 0x1555, 0xa000, 0xc8000, FX32_ONE);
        s_fld.draw();
    }
    for (int i = 0; i < slimeRaceCnt; i++) {
        ST_SLIME_RACE* pSlimeRace = get_pSlimeRace(i);
        SPRITE* sprite = pSlimeRace->sprite;
        sprite->x = pSlimeRace->trans.x;
        sprite->z = pSlimeRace->trans.z;
        anim = get_slimeRace_action_data(pSlimeRace->action, 8);
        if (anim == 0) {
            anim = 6;
        }
        int t = pSlimeRace->frame >> 12;
        if (anim == 20 && pSlimeRace->dir > 0) {
            t = ssa_eff_get_nframe(anim) - t;
        }
        sprite_set_anim(sprite, anim, t);
        ssa_sprite_draw_3D(sprite);
        if (anim == 13) {
            sprite = pSlimeRace->sprite2;
            sprite->x = pSlimeRace->trans.x;
            sprite->z = pSlimeRace->trans.z;
            sprite_set_anim(sprite, 22, t);
            ssa_sprite_draw_3D(sprite);
        }
        effectAnim_sub(pSlimeRace);
    }
    ssa_eff_update(MG_IsUpScreen());
    unkfunc_0212b0b8();
    setupCamera();
    gameStart_draw();
}

void slimeRace_Final()
{
    s_fld.Final();
    s_fldGate.Final();
}

int get_slimeRaceJoutai()
{
    return slimeRaceJoutai;
}

void set_slimeRaceJoutai(int joutai)
{
    slimeRaceJoutai = joutai;
}

int* get_pSlimeRaceOdds()
{
    return _slimeRaceOdds[0];
}

int* get_pSlimeRaceBets()
{
    return _slimeRaceOdds[1];
}

int* get_slimeRace_run_type_data(RUN_TYPE runType, int member)
{
    if (runType >= RUN_TYPE_null && runType < RUN_TYPE_MAX) {
        ST_RUN_TYPE_DATA* pRunType = &run_type_data[runType];
        switch (member) {
        case 0:
            return (int*)pRunType->name;
        case 1:
            return pRunType->probability[0];
        }
    }
    return (int*)-1;
}

int get_slimeRace_action_data(ACTION action, int member)
{
    if (action >= ACTION_null && action < ACTION_MAX) {
        ST_ACTION_DATA* pAction = &action_data[action];
        switch (member) {
        case 0:
            return (int)pAction->name;
        case 1:
            return pAction->fatigue;
        case 2:
            return pAction->speed;
        case 3:
            return pAction->startFrame;
        case 4:
            return pAction->endFrame;
        case 7:
            return (int)pAction->repeat;
        case 8:
            return action_data_anim[action];
        }
    }
    return -1;
}

int* get_slimeRace_tikei_data(TIKEI tikei, int member)
{
    if (tikei >= TIKEI_null && tikei < TIKEI_MAX) {
        ST_TIKEI_DATA* pTikei = &tikei_data[tikei];
        switch (member) {
        case 0:
            return (int*)pTikei->name;
        case 1:
            return pTikei->probability;
        }
    }
    return (int*)-1;
}

int get_slimeRace_unusual_state_data(int id, int member)
{
    if (id >= 0 && id < sizeof(unusual_state_data) / sizeof(unusual_state_data[0])) {
        ST_UNUSUAL_STATE_DATA* pUnusual_State = &unusual_state_data[id];
        switch (member) {
        case 0:
            return pUnusual_State->fatigue;
        case 1:
            return pUnusual_State->sutamina;
        case 2:
            return (int)pUnusual_State->probability;
        }
    }
    return -1;
}

int get_UNUSUAL_STATE_MAX()
{
    return sizeof(unusual_state_data) / sizeof(unusual_state_data[0]);
}

int unkfunc_0212b594()
{
    return 0;
}

// The minigame library functions using this data are not linked in the race overlay;
// this function stands for them (it is dead-stripped at link).
void unkfunc_unused_0(void** p)
{
    p[0] = &unk_02131a48;
    p[1] = &unk_02131ac4;
    p[2] = &unk_0213092a;
    p[3] = &unk_02130926;
    p[4] = &unk_02131a70;
    p[5] = &unk_02131a7c;
    p[6] = &unk_0213092e;
    p[7] = &unk_0213092c;
    p[8] = &unk_02130930;
    p[9] = &unk_02131aa4;
    p[10] = &unk_02130938;
    p[11] = &sprite_kind_data;
    p[12] = &unk_02131a78;
    p[13] = &unk_02130954;
    p[14] = &unk_02131aa0;
    p[15] = &unk_02131a84;
    p[16] = &unk_02130924;
    p[17] = &unk_02131afc;
    p[18] = &unk_02131ab0;
    p[19] = &unk_0213094c;
    p[20] = &unk_02131a50;
    p[21] = &unk_02131a40;
    p[22] = &unk_02131a8c;
    p[23] = &unk_02131b08;
    p[24] = &unk_02130948;
    p[25] = &unk_02130958;
    p[26] = &unk_02131a42;
    p[27] = &unk_02131bb4;
    p[28] = &unk_02130960;
}

}  // namespace race
