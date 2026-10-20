#pragma once
#include <globaldefs.h>
#include "main/fld/FLDObject.hpp"
#include "ov003/fld/SlimeRaceColl.hpp"

// older copy of fld::FLDObject linked in the slime race overlay
namespace race {

struct FLDObject
{
    int m_flag;                                 // 0x000
    fld::UnkFldChunk* m_chunk;                  // 0x004
    void* m_mdl;                                // 0x008
    fld::FLD_MAP* m_map;                        // 0x00C
    fld::UnkFldModelTbl* m_model;               // 0x010
    fld::UnkFldScene* m_scene;                  // 0x014
    fld::UnkFldSeqTbl* m_seq;                   // 0x018
    int m_seq_num;                              // 0x01C
    fld::UnkFldResTbl* m_seq_data[0x80];        // 0x020
    fld::UnkFldResTbl* m_anim;                  // 0x220
    fld::UnkFldResTbl* m_camera_anim;           // 0x224
    fld::UnkFldResTbl* m_pltt_anim;             // 0x228
    fld::UnkFldPlttTbl* m_pltt;                 // 0x22C
    fld::UnkFldResTbl* m_light;                 // 0x230
    fld::UnkFldEventTbl* m_event;               // 0x234
    NNSFndAllocator m_allocator;                // 0x238
    COLL_HEADER* m_coll;                        // 0x248
    int m_camera_no[2];                         // 0x24C
    VecFx32 m_x32_camera_pos[2];                // 0x254
    VecFx32 m_x32_camera_tag[2];                // 0x26C
    VecFx32 m_x32_camera_vec[2];                // 0x284
    int m_frame_flip_flop;                      // 0x29C
    int m_vanish_flag;                          // 0x2A0
    fld::UnkFldCommonTbl* m_common;             // 0x2A4
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

    FLDObject();
    ~FLDObject();
    void init();
    int Setup(void* mdl, void* data, void* coll, int heap);
    void unkfunc_0212c54c();
    void SetCameraPos(fx32 x, fx32 y, fx32 z, int screen);
    void SetCameraCent(fx32 x, fx32 y, fx32 z, int screen);
    void SetCameraUp(fx32 x, fx32 y, fx32 z, int screen);
    void unkfunc_0212cd00(int screen);
    void unkfunc_0212d328(int obj);
    void unkfunc_0212d400();
    void unkfunc_0212dd2c(fld::FLD_MAP_OBJ* obj);
    void unkfunc_0212df34(fld::FLD_MAP_OBJ* obj);
    void unkfunc_0212df80();
    void unkfunc_0212e10c(fld::UnkFldPlttEntry* entry, fld::UnkFldPlttSet* set, int index);
    void unkfunc_0212e304();
    void unkfunc_0212e354();                                    // calc
    void unkfunc_0212e7ac();                                    // draw
    void Final();
    int unkfunc_0212f050(int id);                               // event animation
    void unkfunc_0212f318(short obj, short index);
    void unkfunc_0212f354(int obj);
    NNSG3dResTex* unkfunc_0212f428();
    void unkfunc_0212f5dc(unsigned short* src, unsigned short* dst, int num);
    void unkfunc_0212f67c();
    void unkfunc_0212f738();
    void* allocWork(int size);           // allocate from the work memory
    void freeWork(void* p);             // free (nothing to do)
};

}  // namespace race
