#pragma once
#include <globaldefs.h>
#include "ov002/slimetouch/SlimeTouch.hpp"
#include "nitro/types.h"
#include "nitro/fx.hpp"

typedef unsigned short GXRgb;

enum NAKAMA_SLIME {
    NAKAMA_SLIME_nonEntry = 0,
    NAKAMA_SLIME_entry_nonBet = 1,
    NAKAMA_SLIME_entry_bet = 2,
    NAKAMA_SLIME_MAX = 3,
};

enum RACE_BG_MAP {
    RACE_BG_MAP_ev1 = 0,
    RACE_BG_MAP_ev2 = 1,
    RACE_BG_MAP_ev3 = 2,
    RACE_BG_MAP_ev4 = 3,
    RACE_BG_MAP_ev5 = 4,
    RACE_BG_MAP_MAX = 5,
};

// Slime race mini game (ov003)
struct ST_ARG_SL_RACE {
    int coin;                                   // 0x00
    NAKAMA_SLIME nakamaSlime;                   // 0x04
    RACE_BG_MAP bgMap;                          // 0x08
    int unk_0c;                                 // 0x0C
    int bedCoin;                                // 0x10
    int gainCoin;                               // 0x14
    int rankNakamaSlime;                        // 0x18
    int rank[6];                                // 0x1C
};

enum MGX {
    MGX_slimeTouch = 0,
    MGX_slimeRace = 1,
    MGX_null = 2,
};

struct ST_MG_ARG {
    MGX mgx;                                    // 0x00
    int dbSelect;                               // 0x04
    union {
        int x[8];
        ST_ARG_SL_TOUCH slTouch;
        ST_ARG_SL_RACE slRace;
    };                                          // 0x08
};

enum MG3_STATE {
    MG3_init = 0,
    MG3_wait_end_fadeIn = 1,
    MG3_gameLoop = 2,
    MG3_wait_end_fadeOut = 3,
    MG3_end = 4,
    MG3_null = 5,
};

// expanded heap made from the work memory given to SlimeRaceInit
struct UnkMiniGameHeap {
    void* handle;                               // 0x00
};

// full screen quad drawn by the fade
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

// pressed key state
struct UnkPadState {
    u16 trg;                                    // 0x00
    u16 release;                                // 0x02
    u16 cont;                                   // 0x04
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

// texture parameters of a loaded sprite (a sub-struct: the copy in sprite_data_load_sub is ldm/stm only for it)
struct UnkSpriteTexParam {
    int sizeS;                                  // 0x00
    int sizeT;                                  // 0x04
    int texFmt;                                 // 0x08
    int unk_10;                                 // 0x0C
    int unk_14;                                 // 0x10 color 0 transparent
    int unk_18;                                 // 0x14 mapping type
};

// loaded sprite texture (NCBR) and palette (NCLR)
struct SPRITE_DATA {
    int spr_id;                                 // 0x00
    UnkSpriteTexParam p;                        // 0x04
    unsigned int texKey;                        // 0x1C
    unsigned int plttKey;                       // 0x20
    short width;                                // 0x24
    short height;                               // 0x26
    void* texFile;                              // 0x28 texture to (re)load in VRAM on activation
    void* plttFile;                             // 0x2C palette to (re)load in VRAM on activation
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

// NNSG2dCharacterData (old NitroSystem layout)
struct UnkG2dCharacterData {
    u16 H;                                      // 0x00
    u16 W;                                      // 0x02
    int pixelFmt;                               // 0x04
    int mapingType;                             // 0x08
    unsigned int characterFmt;                  // 0x0C
    unsigned int szByte;                        // 0x10
    void* pRawData;                             // 0x14
};

// NNSG2dPaletteData
struct UnkG2dPaletteData {
    int fmt;                                    // 0x00
    int bExtendedPlt;                           // 0x04
    unsigned int szByte;                        // 0x08
    void* pRawData;                             // 0x0C
};

// UnkBssaChunk of a .bssa file
struct UnkBssaChunk {
    unsigned int id;                            // 0x00
    int size;                                   // 0x04
};

// texture VRAM key to free
struct UnkVramFreeEntry {
    unsigned int key;                           // 0x00
    void* data;                                 // 0x04
};

enum RUN_TYPE {
    RUN_TYPE_null = 0,
    RUN_TYPE_1 = 1,
    RUN_TYPE_2 = 2,
    RUN_TYPE_3 = 3,
    RUN_TYPE_4 = 4,
    RUN_TYPE_5 = 5,
    RUN_TYPE_6 = 6,
    RUN_TYPE_7 = 7,
    RUN_TYPE_8 = 8,
    RUN_TYPE_MAX = 9,
};

enum STATE {
    STATE_null = 0,
    STATE_stage0 = 1,
    STATE_toGate = 2,
    STATE_inGate = 3,
    STATE_stage1 = 4,
    STATE_stage2 = 5,
    STATE_stage3 = 6,
    STATE_goal = 7,
    STATE_goal2 = 8,
    STATE_MAX = 9,
};

enum ACTION {
    ACTION_null = 0,
    ACTION_idle = 1,
    ACTION_jump1 = 2,
    ACTION_jump2 = 3,
    ACTION_jump3 = 4,
    ACTION_dash = 5,
    ACTION_res0 = 6,
    ACTION_res1 = 7,
    ACTION_iki1 = 8,
    ACTION_iki2 = 9,
    ACTION_sleep = 10,
    ACTION_tentou = 11,
    ACTION_meMawasu = 12,
    ACTION_meSamasu = 13,
    ACTION_yorokobu1 = 14,
    ACTION_yorokobu2 = 15,
    ACTION_yorokobu3 = 16,
    ACTION_back = 17,
    ACTION_moveBack = 18,
    ACTION_MAX = 19,
};

enum GAME_START_ST {
    GAME_START_ST_null = 0,
    GAME_START_ST_disp = 1,
    GAME_START_ST_end = 2,
    GAME_START_ST_end2 = 3,
    GAME_START_ST_end3 = 4,
    GAME_START_ST_MAX = 5,
};

enum RACE_STAGE {
    RACE_STAGE_0 = 0,
    RACE_STAGE_1 = 1,
    RACE_STAGE_2 = 2,
    RACE_STAGE_3 = 3,
    RACE_STAGE_MAX = 4,
    RACE_STAGE_null = 4,
};

enum FATIGUE {
    FATIGUE_null = 0,
    FATIGUE_1 = 1,
    FATIGUE_2 = 2,
    FATIGUE_3 = 3,
    FATIGUE_MAX = 4,
};

enum TIKEI {
    TIKEI_null = 0,
    TIKEI_shiba = 1,
    TIKEI_dirt = 2,
    TIKEI_jari = 3,
    TIKEI_mizu = 4,
    TIKEI_suna = 5,
    TIKEI_ana = 6,
    TIKEI_MAX = 7,
};

struct ST_SPRITE_KIND {
    int spr_id;                                 // 0x00
    int data_id;                                // 0x04
    int loadOpt;                                // 0x08
};

struct ST_SLIME_RACE {
    int sutamina;                               // 0x00
    int decSutamina;                            // 0x04
    RUN_TYPE runType;                           // 0x08
    STATE state;                                // 0x0C
    ACTION action;                              // 0x10
    int repeat;                                 // 0x14
    fx32 frame;                                 // 0x18
    VecFx32 trans;                              // 0x1C
    SPRITE* sprite;                             // 0x28
    SPRITE* sprite2;                            // 0x2C
    int rank;                                   // 0x30
    int dir;                                    // 0x34
    int dirChg;                                 // 0x38
    int effTimes;                               // 0x3C
};

struct ST_GAME_START {
    fx32 frame;                                 // 0x00
    GAME_START_ST st;                           // 0x04
};

struct ST_EFFECT_ANIM {
    int EffectAnim;                             // 0x00
    int slimeAnim;                              // 0x04
    int startFrame;                             // 0x08
    fx32 dZ;                                    // 0x0C
    int times;                                  // 0x10
};

// the DS versions of the mobile parameter tables carry a debug name first
struct ST_RUN_TYPE_DATA {
    const char* name;                           // 0x00
    int probability[RACE_STAGE_MAX][4];         // 0x04 (RUN_TYPE_null: the 4 actions)
};

struct ST_ACTION_DATA {
    const char* name;                           // 0x00
    FATIGUE fatigue;                            // 0x04
    fx32 speed;                                 // 0x08
    fx32 startFrame;                            // 0x0C
    fx32 endFrame;                              // 0x10
    int repeat[2][3];                           // 0x14
};

struct ST_TIKEI_DATA {
    const char* name;                           // 0x00
    int probability[2];                         // 0x04 (TIKEI_null: the actions)
};

struct ST_UNUSUAL_STATE_DATA {
    FATIGUE fatigue;                            // 0x00
    int sutamina;                               // 0x04
    int probability[5];                         // 0x08 (entry 0: the actions)
};

// 8 byte object with an empty inline ctor; the TU's __sinit builds 8 of them (bss 0x02131c30), never used
struct UnkRaceWork {
    int unk_00;                                 // 0x00
    int unk_04;                                 // 0x04

    UnkRaceWork();
};

// slime race game and the minigame library (also linked in the slime touch overlay, hence the namespace)
namespace race {

extern void* g_mgWork;
extern unsigned int g_mgWorkSize;

UnkMiniGameHeap* getMgHeap();
void initTouchPanel();
void startMgFade(int mode, GXRgb col, fx32 frames);
void updateMgFade(fx32 passFrame);
BOOL isMgFadeEnd();
void setMgFadeOrthoProjection();
void drawMgFade(int mode);
void set_pMGArg(ST_MG_ARG* arg);
ST_MG_ARG* get_pMGArg();
int MiniGame3(MG3_STATE* pMG3State);
void initMgAllocator();
void* mgAlloc(unsigned int size);
void mgFree(void* p);
void* MG_LoadFile(const char* name, u32* pSize);
u64 initMgRand();
u32 rand32_min_max(u32 min, u32 max);
int randSel_intTable(int* pProbability, int num);
BOOL MG_IsUpScreen();
void set_drawFin();
void updatePad();
int sprite_data_load_sub(int spr_id, int pal_id, int keep);
int sprite_data_load(int spr_id, int keep);
void sprite_init(SPRITE* spr);
SPRITE* sprite_create(int data_id);
void sprite_set_anim(SPRITE* spr, int ssa_id, int frame);
void sprite_activate(int data_id);
void ssa_sprite_draw_3D(SPRITE* spr);
void sprite_all_free();
void ssa_eff_init();
BSSA_DATA* ssa_eff_get_bssa(int eff_id);
int ssa_eff_get_nframe(int eff_id);
void ssa_eff_draw(int eff_id, int frame, int x, int y, int z, fx32 scale);
void ssa_eff_draw_3D(int eff_id, int frame, int x, int y, int z, fx32 scale);
int ssa_eff_start_3D(int eff_id, int x, int y, int z, fx32 scale, int flag);
int ssa_eff_update(int upScreen);
void bssa_draw_prim(BSSA_PRIM* prim, BSSA_PARTS* parts, int poly_id);
void bssa_draw(BSSA_DATA* bssa, int frame, int x, int y, int z, fx32 scale);
void bssa_draw_3D(BSSA_DATA* bssa, int frame, int xpos, int ypos, int zpos, fx32 scale);
BSSA_DATA* bssa_init(void* data);
void initVramCache();
void releaseVramCache();
int mgLoadTexVram(unsigned int key, void* data, int vblank);
int mgLoadPlttVram(unsigned int key, void* data, int vblank);
unsigned int mgAllocTexVram(unsigned int size);
void mgFreeTexVram(unsigned int key);
unsigned int mgAllocPlttVram(unsigned int size);
void mgFreePlttVram(unsigned int key);
unsigned int allocCachedTexVram(void* data, unsigned int size, int load);
unsigned int allocCachedPlttVram(void* data, unsigned int size, int load);
void setOrthoProjection();
int worldToScreen(const VecFx32* world, fx32* px, fx32* py, fx32* pz);
void unpackCharData(UnkG2dCharacterData* data);
int getUnpackedCharData(void* file, UnkG2dCharacterData** out);
void unpackPaletteData(UnkG2dPaletteData* data);
int unkfunc_02129b64(void* file, UnkG2dPaletteData** out);
void SlimeRace_init_BG(int no);
SPRITE* SlimeRace_init_Chara(int id, int keep);
void setupRaceCamera(fx32 x, int opt);
ST_SLIME_RACE* get_pSlimeRace(int id);
int get_id_pSlimeRace(ST_SLIME_RACE* pSlimeRace);
void gameStart_init();
void gameStart_update(fx32 passFrame);
void gameStart_draw();
void setupCamera();
void slimeRace_init();
ACTION slimeRace_get_action_runType(ST_SLIME_RACE* pSlimeRace, RACE_STAGE raceStage);
TIKEI slimeRace_get_ashimoto_tikei(ST_SLIME_RACE* pSlimeRace);
ACTION slimeRace_get_action_tikei(ST_SLIME_RACE* pSlimeRace);
ACTION slimeRace_get_action_afterAction(ST_SLIME_RACE* pSlimeRace);
int slimeRace_get_action_repeat(ST_SLIME_RACE* pSlimeRace, RACE_STAGE raceStage, ACTION action);
int slimeRace_chk_ashitome(ST_SLIME_RACE* pSlimeRace);
ACTION slimeRace_upDate_action_raceStage(ST_SLIME_RACE* pSlimeRace, RACE_STAGE raceStage, int* pRepeat);
RACE_STAGE getRaceStage(STATE state);
void slimeRace_upDate_sutamina(ST_SLIME_RACE* pSlimeRace, ACTION action);
void slimeRace_upDate_action_change(ST_SLIME_RACE* pSlimeRace);
void slimeRace_upDate_action(ST_SLIME_RACE* pSlimeRace);
int get_slimeRaceOdds_offset(int a, int b);
void get_slimeRaceOdds_offset2(int c, int* a, int* b);
void slimeRace_update_state(ST_SLIME_RACE* pSlimeRace, STATE stateMax);
void slimeRace_upDate_trans_sub(ST_SLIME_RACE* pSlimeRace, fx32 max, fx32 max2, STATE stateMax);
void slimeRace_upDate_trans(ST_SLIME_RACE* pSlimeRace, fx32 passFrame);
void slimeRaceOrder_update();
int slimeRaceOdds_get_sum();
BOOL slimeRace_chk_state_all(STATE state);
void slimeRace_chg_state_all(STATE state);
void slimeRace_upDate_joutai_to_gate();
BOOL slimeRace_upDate_joutai();
bool slimeRace_upDate(fx32* pPassFrame);
void unkfunc_0212b0b8();
void effectAnim_sub(ST_SLIME_RACE* pSlimeRace);
void slimeRace_draw();
void slimeRace_Final();
int get_slimeRaceJoutai();
void set_slimeRaceJoutai(int joutai);
int* get_pSlimeRaceOdds();
int* get_pSlimeRaceBets();
int* get_slimeRace_run_type_data(RUN_TYPE runType, int member);
int get_slimeRace_action_data(ACTION action, int member);
int* get_slimeRace_tikei_data(TIKEI tikei, int member);
int get_slimeRace_unusual_state_data(int id, int member);
int get_UNUSUAL_STATE_MAX();
int unkfunc_0212b594();

}  // namespace race

void SlimeRaceInit(void* work, unsigned int size, ST_ARG_SL_RACE* arg);
void SlimeRaceDraw();
void SlimeRaceExec();
void SlimeRaceTerm();
int SlimeRaceResult(ST_ARG_SL_RACE* arg);
int getRaceJoutai();                         // race state
void setRaceJoutai(int state);
int* getRaceOdds();                        // odds of the pairs
int* getRaceBets();                        // bets of the pairs
