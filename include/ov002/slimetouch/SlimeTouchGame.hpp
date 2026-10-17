#pragma once
#include <globaldefs.h>
#include "nitro/fx.hpp"
#include "nitro/gx.h"
#include "nitro/tp.hpp"
#include "nitro/types.h"
#include "nnsys/g2d.hpp"
#include "nnsys/g3d.hpp"
#include "ov002/slimetouch/SlimeTouch.hpp"

typedef unsigned short GXRgb;

enum MGX {
    MGX_slimeTouch = 0,
    MGX_slimeRace = 1,
    MGX_null = 2,
};

struct ST_MG_ARG {
    MGX mgx;                                    // 0x00
    int dbSelect;                               // 0x04
    ST_ARG_SL_TOUCH slTouch;                    // 0x08
};

enum MG2_STATE {
    MG2_null = 0,
    MG2_init = 1,
    MG2_init2 = 2,
    MG2_fadeIn = 3,
    MG2_wait_end_fadeIn = 4,
    MG2_gameStart = 5,
    MG2_wait_end_gameStart = 6,
    MG2_gameLoop = 7,
    MG2_gameOver = 8,
    MG2_wait_end_gameOver = 9,
    MG2_fadeOut = 10,
    MG2_wait_end_fadeOut = 11,
    MG2_max = 12,
};

enum BG_MANAGE {
    BG_init = 0,
    BG_draw = 1,
    BG_term = 2,
    BG_on_off = 3,
};

enum KIND {
    KIND_null = 0,
    KIND_slime = 1,
    KIND_slimeBes = 2,
    KIND_metalSlime = 3,
    KIND_chara4 = 4,
    KIND_chara5 = 5,
    KIND_chara6 = 6,
    KIND_chara7 = 7,
    KIND_chara8 = 8,
    KIND_chara9 = 9,
    KIND_chara10 = 10,
    KIND_chara11 = 11,
    KIND_chara12 = 12,
    KIND_chara13 = 13,
    KIND_chara14 = 14,
    KIND_chara15 = 15,
    KIND_chara16 = 16,
    KIND_chara17 = 17,
    KIND_chara18 = 18,
    KIND_chara19 = 19,
    KIND_chara20 = 20,
    SLIME_DATA_MAX = 21,
    KIND_bakudanIwa = 21,
    KIND_player = 22,
    KIND_gameStart = 23,
    KIND_gameOver = 24,
    KIND_ase = 25,
    KIND_board_sl = 26,
    KIND_board_bs = 27,
    KIND_board_mt = 28,
    KIND_odoruHouseki = 29,
    KIND_max = 30,
};

enum SLIME_MOVE {
    MOVE_null = 0,
    MOVE_up = 1,
    MOVE_top = 2,
    MOVE_down = 3,
    MOVE_down_end = 4,
    MOVE_die_dm = 5,
    MOVE_die_dm_wait = 6,
    MOVE_die_wait = 7,
    MOVE_norma2_wait = 8,
    MOVE_norma2_up = 9,
    MOVE_norma2_stand = 10,
    MOVE_norma2_down = 11,
    MOVE_norma2_down2 = 12,
    MOVE_norma2_down3 = 13,
    MOVE_norma2_end = 14,
    MOVE_iwa2 = 15,
    MOVE_player2 = 16,
    MOVE_gameStart = 17,
    MOVE_gameOver = 18,
    MOVE_ase = 19,
    MOVE_max = 20,
};

enum SLIME_ANM_OPT {
    SLIME_ANM_OPT_damage_seizon = 0,
    SLIME_ANM_OPT_damage_die = 1,
    SLIME_ANM_OPT_die = 2,
    SLIME_ANM_OPT_dm_die = 3,
    SLIME_ANM_OPT_force_del = 4,
    SLIME_ANM_OPT_hitBonusTip = 5,
    SLIME_ANM_OPT_MAX = 6,
};

struct SPRITE {
    int x;                                      // 0x00
    int y;                                      // 0x04
    int z;                                      // 0x08
    int alpha;                                  // 0x0C
    int data_id;                                // 0x10
    int dir;                                    // 0x14
    int frame;                                  // 0x18
    GXRgb col;                                  // 0x1C
    u16 rotZ;                                   // 0x1E
    fx32 sclX;                                  // 0x20
    fx32 sclY;                                  // 0x24
    int ssa_id;                                 // 0x28
    int nframe;                                 // 0x2C
};

// loaded sprite texture (NCBR) and palette (NCLR)
struct UnkSpriteTexParam {
    GXTexSizeS sizeS;                           // 0x00
    GXTexSizeT sizeT;                           // 0x04
    GXTexFmt texFmt;                            // 0x08
    int unk_0C;                                 // 0x0C
    GXTexPlttColor0 plttColor0;                 // 0x10
    int unk_14;                                 // 0x14
};

struct SPRITE_DATA {
    int spr_id;                                 // 0x00
    UnkSpriteTexParam tex;                      // 0x04
    unsigned int texKey;                        // 0x1C
    unsigned int plttKey;                       // 0x20
    short width;                                // 0x24
    short height;                               // 0x26
    void* texFile;                              // 0x28
    void* plttFile;                             // 0x2C
};

struct ST_SLIME {
    NNSG3dRenderObj* renderObj;                 // 0x00
    NNSG3dAnmObj* anmObj[4];                    // 0x04
    fx32 anmFrame[4];                           // 0x14
    fx32 anmSeWait;                             // 0x24
    int anmSe;                                  // 0x28
    int anmNum;                                 // 0x2C
    SPRITE* sprite;                             // 0x30
    VecFx32 trans;                              // 0x34
    fx32 frame;                                 // 0x40
    fx32 frameMax;                              // 0x44
    KIND kind;                                  // 0x48
    int tp;                                     // 0x4C
    int alpha;                                  // 0x50
    int dAlpha;                                 // 0x54
    SLIME_MOVE move;                            // 0x58
    int addScore;                               // 0x5C
    int touchX;                                 // 0x60
    int touchY;                                 // 0x64
    int taoshita;                               // 0x68
    int bonusPoint;                             // 0x6C
    int damageAnmOffset;                        // 0x70
    int disp;                                   // 0x74
    GXRgb col;                                  // 0x78
    u16 rotZ;                                   // 0x7A
};

struct ST_SIDE_INFO {
    ST_SLIME slime[17];                         // 0x000
    int stage;                                  // 0x83C
    int clrSlime;                               // 0x840
    int clrNorma;                               // 0x844
    int tokuten;                                // 0x848
    int iwaSpd;                                 // 0x84C
    int iwaSpd2;                                // 0x850
    int iwaPos;                                 // 0x854
    int noMissCnt;                              // 0x858
    int noMissNormaCnt;                         // 0x85C
    int noMissStageCnt;                         // 0x860
    int normaSt;                                // 0x864
    int gameClear;                              // 0x868
    int iwaReturn;                              // 0x86C
    int absoluteCnt;                            // 0x870
    int absoluteBuf[4];                         // 0x874
    int item[17];                               // 0x884
    int bgmChange;                              // 0x8C8
    int kemuri_play_id;                         // 0x8CC
    fx32 appearWait;                            // 0x8D0
    fx32 stageClearWait;                        // 0x8D4
    fx32 bgmChangeWait;                         // 0x8D8
};

struct ST_OBJ_DATA {
    VecFx32 trans;                              // 0x00
    SLIME_MOVE move;                            // 0x0C
};

struct ST_SPRITE_KIND {
    int spr_id;                                 // 0x00
    int data_id;                                // 0x04
    int loadOpt;                                // 0x08
};

struct ST_EFFECT_ANIM {
    int EffectAnim;                             // 0x00
    int slimeAnim;                              // 0x04
    int startFrame;                             // 0x08
    fx32 dZ;                                    // 0x0C
    int times;                                  // 0x10
};

struct BSSA_PARTS {
    short u0;                                   // 0x00
    short v0;                                   // 0x02
    short u1;                                   // 0x04
    short v1;                                   // 0x06
};

struct BSSA_FRAME {
    short n_prim;                               // 0x00
    short prim_ofs;                             // 0x02
};

struct BSSA_PRIM {
    unsigned char parts_id;                     // 0x00
    unsigned char alpha : 5;                    // 0x01
    unsigned char flipH : 1;
    unsigned char flipV : 1;
    fx16 rot_z;                                 // 0x02
    fx16 pos_x;                                 // 0x04
    fx16 pos_y;                                 // 0x06
    fx16 scl_x;                                 // 0x08
    fx16 scl_y;                                 // 0x0A
};

struct BSSA_DATA {
    u8 n_parts;                                 // 0x00
    unsigned char h : 4;                        // 0x01
    unsigned char w : 4;
    short n_frame;                              // 0x02
    short n_prim;                               // 0x04
    short tex_id;                               // 0x06
    BSSA_PARTS* parts;                          // 0x08
    BSSA_FRAME* frame;                          // 0x0C
    BSSA_PRIM* prim;                            // 0x10
};

struct BSSA_EFF_WORK {
    int x;                                      // 0x00
    int y;                                      // 0x04
    int z;                                      // 0x08
    fx32 scale;                                 // 0x0C
    short frame;                                // 0x10
    char eff_id;                                // 0x12
    char flag;                                  // 0x13
};

struct SSA_DATA {
    const char* fname;                          // 0x00
    int spr_id;                                 // 0x04
};

// model file with its animation files
struct UnkSlimeCgModel {
    const char* path;                           // 0x00
    NNSG3dResMdl* mdl;                          // 0x04
    void* file;                                 // 0x08
    struct UnkSlimeCgAnm* anm;                  // 0x0C
};

struct UnkSlimeCgAnm {
    struct {
        const char* path;                       // 0x00
        void* anm;                              // 0x04
    } file[4];
};

// touch panel sample
struct UnkTouchPoint {
    UnkTouchPoint();
    int touch;                                  // 0x00
    short x;                                    // 0x04
    short y;                                    // 0x06
};

// pressed key state
struct UnkPadState {
    u16 trg;                                    // 0x00
    u16 release;                                // 0x02
    u16 cont;                                   // 0x04
};

// VRAM key of a texture/palette loaded from main memory
struct UnkVramCacheEntry {
    unsigned int key;                           // 0x00
    void* data;                                 // 0x04
};

// line of the score messages list
struct UnkScoreMessage {
    const char* str;                            // 0x00
    int slime;                                  // 0x04
    int wait;                                   // 0x08
};

// param
struct ST_SLIME_DATA {
    char* zName;                                // 0x00
    int item;                                   // 0x04
    int tp;                                     // 0x08
    int tokuten;                                // 0x0C
    int timeMin;                                // 0x10
    int timeMax;                                // 0x14
};

// name, model/sprite numbers and parameters of a slime/object kind
struct UnkKindInfo {
    char* name;                                 // 0x00
    int cgNo;                                   // 0x04
    int spriteNo;                               // 0x08
    ST_SLIME_DATA* pSlimeData;                    // 0x0C
};

struct ST_STAGE_DATA {
    int stage;                                  // 0x00
    int norma;                                  // 0x04
    int max;                                    // 0x08
    int oneTime_max;                            // 0x0C
    fx32 timeMin;                               // 0x10
    fx32 timeMax;                               // 0x14
    int absoluteMin;                            // 0x18
    int absoluteMax;                            // 0x1C
    int probability[20];                        // 0x20
    int iwaSpd;                                 // 0x70
    int probabilityNorma[3];                    // 0x74
    int bonus;                                  // 0x80
    int anmNum_slimeUp;                         // 0x84
    fx32 idleTimeHosei;                         // 0x88
};

extern ST_SLIME_DATA slime_data[SLIME_DATA_MAX];

int get_kind_data(KIND kind, int member);
fx32 get_kind_time_rand(KIND kind);
int get_stage_data(int stage, int member);
fx32 get_time_from_stage_data(int stage);
KIND get_kind_from_stage_data(int stage);
KIND get_normaKind_from_stage_data(int stage);
int get_kind_anmNum(KIND kind, SLIME_MOVE move);
int unkfunc_0212e168();

// system
extern void* g_mgWorkAddr;
extern unsigned int g_mgWorkSize;
void** unkfunc_02128060();
void unkfunc_021280a4();
void unkfunc_02128108();
void unkfunc_02128268();
void unkfunc_0212826c(int mode, GXRgb col, fx32 frames);
void unkfunc_0212829c(fx32 passFrame);
BOOL unkfunc_02128314();
void unkfunc_02128334();
void unkfunc_02128394(int upScreen);

// miniGame0
void set_pMGArg(ST_MG_ARG* pMGArg);
ST_MG_ARG* get_pMGArg();
int unkfunc_021284a4();

// miniGame2
void bg_manage(BG_MANAGE bgManage);
void unkfunc_0212873c();
int unkfunc_021287f4();
BOOL chk_touchPad(int* x, int* y);
bool MiniGame2(MG2_STATE* pMG2State);

// miniGameSystem
int unkfunc_02128c04();
void unkfunc_02128c0c();
NNSFndAllocator* unkfunc_02128c4c();
void* unkfunc_02128c5c(u32 size);
void unkfunc_02128c78(void* memBlock);
void* MG_LoadFile(const char* _path, u32* size);
void unkfunc_02128d2c(const char* path, void** pFile, NNSG3dResMdl** pMdl);
u64 unkfunc_02128d7c();
u32 rand32_min_max(u32 min, u32 max);
int randSel_intTable(int* pProbability, int num);
bool MG_IsUpScreen();
void set_drawFin();
void unkfunc_02128f68();
void unkfunc_02128fc4();

// side_info
int get_iwaSpdNormal();
int get_sideUp();
ST_SIDE_INFO* get_pSideInfo(int side);
ST_SLIME* get_pSlime(int side, int id);
KIND get_normaSlimeKind(int side, int offset);
int get_id_pSlime(ST_SLIME* pSlime);
void sideInfo_init();
void sideInfo_update(fx32 passFrame);
void sideInfo_draw(MG2_STATE mg2State);
void unkfunc_021295f4(const char* str, int slime);
int sideInfo_stage_add_ex(int side, int val, int opt);
int sideInfo_taoshita_inc(int side, KIND kind, int* pBonusPoint, int* pAddScore);
int sideInfo_nigashita_inc(int side, KIND kind);
void sideInfo_slime_chk_add(fx32 passFrame);
void sideInfo_slime_chk_touch(int x, int y);
void sideInfo_slime_update_ex(fx32 passFrame, int start, int end);
void sideInfo_slime_draw();
int sideInfo_get_gameST(int side);

// slime
void slime_init(int side, int init);
ST_SLIME* slime_set_obj(int side, int id, KIND kind);
void slime_set_bakudanIwa(int side);
void slime_set_player(int side);
void slime_chk_add(int side, fx32 passFrame);
void get_slime_scr_xy(ST_SLIME* pSlime, int* px, int* py, int opt);
void slime_chk_touch(int side, int x, int y);
void nokori_anaSlime_force_del(int side, ST_SLIME* pSlimeNonForceDel);
void slime_update_ex(int side, fx32 arg_passFrame, int start, int end);
void slime_draw(int side, MtxFx33* rot, int start, int end);
bool bakudanIwa_bakuhatsu(int side, fx32 passFrame);
int get_bonusPointIwa(int side);

// slime_cg
void unkfunc_0212b42c();
void slime_cg_Release(ST_SLIME* pSlime);
void slime_cg_Release_all();
int slime_cg_set(ST_SLIME* pSlime, KIND kind, int anmNum);

// slime_sprite
void slime_sprite_init();
void slime_sprite_draw(ST_SLIME* pSlime);
int slime_sprite_set(ST_SLIME* pSlime, KIND kind, int anmNum);

// sprite
int sprite_data_load_sub(int spr_id, int pal_id, int keep);
int sprite_data_load(int spr_id, int keep);
void unkfunc_0212bd30(int spr_id);
void unkfunc_0212bdb4(int spr_id);
SPRITE* sprite_create(int data_id);
void sprite_term(SPRITE* spr);
void sprite_set_anim(SPRITE* spr, int ssa_id, int frame);
void sprite_draw_start();
void sprite_draw_end();
void sprite_activate(int data_id);
void ssa_sprite_draw(SPRITE* spr);
void sprite_draw_rect(SPRITE* spr, int u1, int v1, int u2, int v2);
void sprite_font_init();
void sprite_draw(SPRITE* spr, int yy);
void draw_touch_num(int x, int y, int num, int alpha);
void draw_stage_num(int stage);
void draw_score_ex(int score, int flag, int x, int y, GXRgb col);
void draw_stage_clear(int x, int y, int stage, int disp_clear, int alpha, int yy, fx32 sclY);
void sprite_all_free();

// ssa_eff
void ssa_eff_init();
BSSA_DATA* ssa_eff_get_bssa(int eff_id);
int ssa_eff_get_nframe(int eff_id);
void ssa_eff_draw(int eff_id, int frame, int x, int y, int z, fx32 scale);
void ssa_eff_draw_3D(int eff_id, int frame, int x, int y, int z, fx32 scale);
int ssa_eff_start(int eff_id, int x, int y, fx32 scale, int flag);
int ssa_eff_update(int upScreen);
BOOL ssa_eff_chk(int play_id, int eff_id);

// bssa_lib
void bssa_draw_prim(BSSA_PRIM* prim, BSSA_PARTS* parts, int poly_id);
void bssa_draw(BSSA_DATA* bssa, int frame, int x, int y, int z, fx32 scale);
void bssa_draw_3D(BSSA_DATA* bssa, int frame, int xpos, int ypos, int zpos, fx32 scale);
BSSA_DATA* bssa_init(void* data);

// VRAM and 3D helpers
void unkfunc_0212d458();
void unkfunc_0212d470();
int unkfunc_0212d4f4(u32 texKey, void* src, int task);
int unkfunc_0212d564(u32 plttKey, void* src, int task);
u32 unkfunc_0212d5d4(u32 size);
int unkfunc_0212d5e8(u32 key);
u32 unkfunc_0212d5f4(u32 size);
int unkfunc_0212d608(u32 key);
u32 unkfunc_0212d614(void* data, u32 size, int load);
u32 unkfunc_0212d6b4(void* data, u32 size, int load);
void unkfunc_0212d754(NNSG3dResTex* tex, int exec);
void unkfunc_0212d790(NNSG3dResTex* tex, int exec);
BOOL unkfunc_0212d83c(void* pResData);
void unkfunc_0212da5c();
int unkfunc_0212dac0(VecFx32* pos, fx32* px, fx32* py, fx32* pz);
void unkfunc_0212dca0(NNSG2dCharacterData* chr);
BOOL unkfunc_0212dcb0(void* file, NNSG2dCharacterData** ppChr);
void unkfunc_0212dcec(NNSG2dPaletteData* pltt);
BOOL unkfunc_0212dcfc(void* file, NNSG2dPaletteData** ppPltt);
