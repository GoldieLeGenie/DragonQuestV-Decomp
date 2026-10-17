#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "nnsys/fnd.hpp"
#include "nnsys/g3d.hpp"
#include "main/fld/Coll.hpp"
#include "nitro/os.hpp"

struct COLL_HEADER;
struct COLL_POLY;

namespace fld {

// chunk of the field data file
struct UnkFldChunk {
    unsigned int id;                            // 0x00
    unsigned int size;                          // 0x04
};

// table of resources (offsets relocated by FLDObject::Setup)
struct UnkFldResTbl {
    UnkFldChunk header;                           // 0x00
    int num;                                    // 0x08
    void* res[1];                               // 0x0C
};

// keyframe animation, keys follow the header (or are pointed by UnkFldRender::keys)
struct UnkFldAnim {
    short flag;                                 // 0x00  2: hold, 4: per object copy, 8: shape morph keys
    short key_num;                              // 0x02
    short loop;                                 // 0x04
    short wait;                                 // 0x06
    short wait_init;                            // 0x08
    short key_size;                             // 0x0A
    int frame;                                  // 0x0C
    int frame_max;                              // 0x10
    int event_id;                               // 0x14
    int wait_start;                             // 0x18
    int loop_start;                             // 0x1C
    int key[1];                                 // 0x20
};

typedef int (*FLD_ANIM_FUNC)(void* key0, void* key1, fx32 rate, void* work);

struct UnkFldCameraKey {
    int frame;                                  // 0x00
    VecFx32 pos;                                // 0x04
    VecFx32 tag;                                // 0x10
    VecFx32 vec;                                // 0x1C
};

struct UnkFldObjKey {
    int frame;                                  // 0x00
    VecFx32 pos;                                // 0x04
    VecFx32 rot;                                // 0x10
    VecFx32 scale;                              // 0x1C
};

struct UnkFldShapeKey {
    int frame;                                  // 0x00
    int shape;                                  // 0x04
};

struct UnkFldSeqKey {
    int frame;                                  // 0x00
    int shape;                                  // 0x04
    VecFx32 pos;                                // 0x08
    VecFx32 rot;                                // 0x14
    VecFx32 scale;                              // 0x20
};

struct UnkFldLightKey {
    int frame;                                  // 0x00
    unsigned short amb;                         // 0x04
    unsigned short diff;                        // 0x06
    unsigned short spec;                        // 0x08
    unsigned short emi;                         // 0x0A
    int alpha;                                  // 0x0C
};

struct UnkFldMatList {
    unsigned int num;                           // 0x00
    struct {
        NNSG3dResMdl* mdl;                      // 0x00
        int mat;                                // 0x04
    } list[1];                                  // 0x04
};

struct UnkFldLight {
    union {
        char name[0x10];                        // 0x00
        UnkFldMatList* mat_list;                 // 0x00
    };
    UnkFldAnim anim;                              // 0x10
};

// per map object render data (allocated by Setup)
struct UnkFldRender {
    MtxFx33 mtx;                                // 0x00
    VecFx32 trans;                              // 0x24
    VecFx32 scale;                              // 0x30
    VecFx32 rot;                                // 0x3C
    NNSG3dRenderObj* render_obj;                // 0x48
    int flag;                                   // 0x4C
    int alpha;                                  // 0x50
    int index;                                  // 0x54
    UnkFldAnim anim;                              // 0x58
    void* keys;                                 // 0x7C
    void* key0;                                 // 0x80
    void* key1;                                 // 0x84
    fx32 rate;                                  // 0x88
    fx16 box_x;                                 // 0x8C
    fx16 box_y;                                 // 0x8E
    fx16 box_z;                                 // 0x90
    fx16 box_w;                                 // 0x92
    fx16 box_h;                                 // 0x94
    fx16 box_d;                                 // 0x96
    fx32 box_scale;                             // 0x98
    VecFx32 center;                             // 0x9C
    fx32 radius2;                               // 0xA8
    fx32 radius;                                // 0xAC
};

struct UnkFldFade {
    fx32 start;                                 // 0x00
    fx32 end;                                   // 0x04
    fx32 min;                                   // 0x08
};

// 'FMDL' entry
struct UnkFldModel {
    int unk_00;                                 // 0x00
    int unk_04;                                 // 0x04
    NNSG3dResMdl* mdl;                          // 0x08
    int flag;                                   // 0x0C
    UnkFldFade* fade;                             // 0x10
    int unk_14;                                 // 0x14
    void* unk_18;                               // 0x18
    void* unk_1c;                               // 0x1C
    int shape_num;                              // 0x20
    int shape0;                                 // 0x24
    int shape1;                                 // 0x28
    fx32 shape_rate;                            // 0x2C
};

struct UnkFldModelTbl {
    UnkFldChunk header;                           // 0x00
    int num;                                    // 0x08
    int unk_0c;                                 // 0x0C
    UnkFldModel model[1];                         // 0x10
};

struct FLD_MAP_OBJ {
    VecFx32 pos;                                // 0x00
    int unk_0c;                                 // 0x0C
    VecFx32 rot;                                // 0x10
    short model;                                // 0x1C
    short common_id;                            // 0x1E
    VecFx32 scale;                              // 0x20
    int uid;                                    // 0x2C
    int flag;                                   // 0x30
    int priority;                               // 0x34
    UnkFldRender* render;                         // 0x38
    UnkFldModel* model_info;                      // 0x3C
    short seq;                                  // 0x40
    short anim;                                 // 0x42
    short def_model;                            // 0x44
    short def_seq_data;                         // 0x46
    short def_anim;                             // 0x48
    short common_anim;                          // 0x4A
    short common_anim_no;                       // 0x4C
    short unk_4e;                               // 0x4E
};

struct FLD_OBJ_UID {
    short uid;                                  // 0x00
    short obj_id;                               // 0x02
};

// 'FMAP'
struct FLD_MAP {
    UnkFldChunk header;                           // 0x00
    int uid_num;                                // 0x08
    int obj_num;                                // 0x0C
    int unk_10;                                 // 0x10
    short* index;                               // 0x14
    short** order;                              // 0x18
    int extra;                                  // 0x1C
    FLD_MAP_OBJ obj[1];                         // 0x20
};

// 'FETC'
struct UnkFldScene {
    UnkFldChunk header;                           // 0x00
    int backColor;                              // 0x08
    char unk_0c[0x18 - 0xc];                    // 0x0C
    int cameraLimitR;                           // 0x18
    int cameraLimitL;                           // 0x1C
};

struct UnkFldSeq {
    short unk_00;                               // 0x00
    short data;                                 // 0x02
    short anim;                                 // 0x04
    short wait;                                 // 0x06
    short wait_init;                            // 0x08
    short loop;                                 // 0x0A
    short wait_start;                           // 0x0C
    short loop_start;                           // 0x0E
    short frame;                                // 0x10
    short unk_12;                               // 0x12
};

// 'FSEq'
struct UnkFldSeqTbl {
    UnkFldChunk header;                           // 0x00
    int num;                                    // 0x08
    UnkFldSeq seq[1];                             // 0x0C
};

struct UnkFldCommonKey {
    short model;                                // 0x00
    short seq;                                  // 0x02
    short anim;                                 // 0x04
    short unk_06;                               // 0x06
};

// 'FCAN'
struct UnkFldCommonTbl {
    UnkFldChunk header;                           // 0x00
    int num;                                    // 0x08
    struct {
        int num;                                // 0x00
        UnkFldCommonKey* key;                    // 0x04
    } anim[1];                                  // 0x0C
};

// 'FEAN'
struct UnkFldEventTbl {
    UnkFldChunk header;                           // 0x00
    int num;                                    // 0x08
    int unk_0c;                                 // 0x0C
    struct {
        short start;                            // 0x00
        short end;                              // 0x02
    } event[1];                                 // 0x10
};

struct UnkFldPltt16  { short wait; unsigned short col[0x10];  };   // 0x22
struct UnkFldPltt256 { short wait; unsigned short col[0x100]; };   // 0x202

// 'FPAM' entry
struct UnkFldPlttSet {
    short timer;                                // 0x00
    short index;                                // 0x02
    short count;                                // 0x04
    short flag;                                 // 0x06  1: 256 colors, 2: rgb rate applied
    unsigned char data[1];                      // 0x08
};

struct UnkFldPlttEntry {
    char name[0x10];                            // 0x00
    unsigned char anim;                         // 0x10
    unsigned char event;                        // 0x11
    unsigned char unk_12[2];                    // 0x12
    unsigned short* pltt;                       // 0x14
};

// 'FPLP'
struct UnkFldPlttTbl {
    UnkFldChunk header;                           // 0x00
    int num;                                    // 0x08
    UnkFldPlttEntry entry[1];                    // 0x0C
};

struct FLDObject
{
    int m_flag;                                 // 0x000
    UnkFldChunk* m_chunk;                         // 0x004
    void* m_mdl;                                // 0x008
    FLD_MAP* m_map;                             // 0x00C
    UnkFldModelTbl* m_model;                     // 0x010
    UnkFldScene* m_scene;                         // 0x014
    UnkFldSeqTbl* m_seq;                         // 0x018
    int m_seq_num;                              // 0x01C
    UnkFldResTbl* m_seq_data[0x80];              // 0x020
    UnkFldResTbl* m_anim;                        // 0x220
    UnkFldResTbl* m_camera_anim;                 // 0x224
    UnkFldResTbl* m_pltt_anim;                   // 0x228
    UnkFldPlttTbl* m_pltt;                       // 0x22C
    UnkFldResTbl* m_light;                       // 0x230
    UnkFldEventTbl* m_event;                     // 0x234
    NNSFndAllocator m_allocator;                // 0x238
    COLL_HEADER* m_coll;                        // 0x248
    int m_camera_no[2];                         // 0x24C
    VecFx32 m_x32_camera_pos[2];                // 0x254
    VecFx32 m_x32_camera_tag[2];                // 0x26C
    VecFx32 m_x32_camera_vec[2];                // 0x284
    int m_frame_flip_flop;                      // 0x29C
    int m_vanish_flag;                          // 0x2A0
    UnkFldCommonTbl* m_common;                   // 0x2A4
    fx32 m_bbox_far;                            // 0x2A8
    NNSG3dGeBuffer m_ge_buffer;                 // 0x2AC
    VecFx32 m_cross_pos;                        // 0x5B0
    VecFx32 m_cross_dir;                        // 0x5BC
    fx32 m_cross_len;                           // 0x5C8
    int m_simple_bby;                           // 0x5CC
    int m_box_test;                             // 0x5D0
    VecFx32 m_rgb_rate;                         // 0x5D4
    NNSG3dResTex* m_tex;                        // 0x5E0
    unsigned char** m_mat_alpha;                // 0x5E4
    int m_event_anim_id;                        // 0x5E8
    VecFx32 m_scale;                            // 0x5EC
    unsigned char* m_pool;                      // 0x5F8 work memory taken from the FFOg chunk
    int m_pool_rest;                            // 0x5FC
    fx32 m_far_town;                            // 0x600
    VecFx32 m_target;                           // 0x604
    int mainCameraFlag_;                        // 0x610
    int clipping;                               // 0x614

    void SetBBoxFar(fx32 val);
    void setMainCameraFlag(int flag);
    FLDObject();
    ~FLDObject();
    void init();
    int SetCameraNo(int no, int screen);
    int Setup(void* mdl, void* data, void* coll, int heap);
    void unkfunc_0205d3e0();
    void SetCameraPos(fx32 x, fx32 y, fx32 z, int screen);
    void SetCameraCent(fx32 x, fx32 y, fx32 z, int screen);
    void SetCameraUp(fx32 x, fx32 y, fx32 z, int screen);
    void unkfunc_0205db94(int screen);
    void unkfunc_0205e1bc(int obj);
    void unkfunc_0205e294();
    void unkfunc_0205ec7c(FLD_MAP_OBJ* obj);
    void unkfunc_0205ee84(FLD_MAP_OBJ* obj);
    void unkfunc_0205eed0();
    void unkfunc_0205f05c(UnkFldPlttEntry* entry, UnkFldPlttSet* set, int index);
    void unkfunc_0205f0d0();
    void unkfunc_0205f398();
    void unkfunc_0205f404();                                    // calc
    void unkfunc_0205f85c();                                    // draw
    void Final();
    void SetMapObjAlpha(int obj, int alpha, int flag);
    void SetMapObjOnOff(int obj, int flag);
    void SetMapObjPosFX32(int obj, VecFx32* pos);
    void unkfunc_02060384(int obj, VecFx32* rot);
    void AddMapObjRotFX32(int obj, VecFx32* rot);
    void AddMapObjPosFX32(int obj, VecFx32* pos);
    void SetMapUidAlpha(int uid, int alpha, int flag);
    void SetMapUidOnOff(int uid, int flag);
    void SetMapUidPosFX32(int uid, VecFx32* pos);
    void SetMapUidRotFX32(int uid, VecFx32* rot);
    void CollEraseObjId(int obj_id);
    void CollResetObjId(int obj_id);
    int CollGetPolyNoBySurface(int surface_id, int start);
    void unkfunc_0204627c(int uid, VecFx32* rot);
    void AddMapUidPosFX32(int uid, VecFx32* pos);
    int CollGetPolyNoByMapUid(int uid, int start);
    void CollEraseMapUid(int uid);
    void CollResetMapUid(int uid);
    void CollAddPolyPosByMapUid(int uid, VecFx32* pos);
    void CollAddPolyPosByMapObj(int obj, VecFx32* pos);
    int unkfunc_0206092c(int id);                               // event animation
    void unkfunc_02060bf4(short obj, short index);
    int SetCommonAnimation(int obj, int no);
    int GetCommonAnimationNum(int obj);
    int IsCommonAnimationEnd(int obj);
    void unkfunc_0206106c(int obj);
    FLD_MAP_OBJ* GetMapObjPtr(int obj);
    int GetMapObjUid(int obj);
    int CollGetObjId(int poly_no);
    VecFx32* GetMapObjRotFX32(int obj);
    int unkfunc_020611b8(int obj);                              // animation frame
    int unkfunc_02061224(int obj);                              // animation frame max
    int GetCommonAnimationNo(int obj);
    int GetMapObjCommonId(int obj);
    void SetSepia();
    void SetRGBRate(VecFx32* rate, int real_time);
    NNSG3dResTex* unkfunc_02061358();
    void unkfunc_02061520(unsigned short* src, unsigned short* dst, int num);
    void unkfunc_020615c0();
    void unkfunc_020616f4();
    void unkfunc_0206175c(fx32 x, fx32 y, fx32 z);              // scale
    void* unkfunc_0206176c(int size);           // allocate from the work memory
    void unkfunc_02061794(void* p);             // free (nothing to do)
    void unkfunc_02061798(unsigned int color);  // sets the vertex colors of all the shapes
    int unkfunc_02061950(UnkFldRender* render);
    int GetMapObjAlpha(int obj);
    int CollCrossCheck(VecFx32* pos0, VecFx32* pos1, int start, fx32* len);
    int CollGetPoly(int poly_no, COLL_POLY* poly);
    int CollGetSurface(int poly_no);
    int CollGetPolyNoByMapObj(int obj_id, int start);
    COLL_ADD_RESULT_TYPE addExtraPolyColl(int extraNo, int polyNo, COLL_POLY* new_poly, int& allocFlag);
};

}  // namespace fld

extern "C" {
    void func_0208a960(void* head, unsigned int num, unsigned int width, int (*compare)(void*, void*), void* stack);   // MATH_QSort
}
