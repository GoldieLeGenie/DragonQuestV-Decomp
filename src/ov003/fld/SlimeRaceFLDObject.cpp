#include "ov003/fld/SlimeRaceFLDObject.hpp"
#include "ov003/fld/SlimeRaceColl.hpp"
#include "main/fld/FldStage.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "nitro/g3.hpp"
#include "nitro/gx.hpp"
#include "nitro/fx/fx_trig.h"
#include <mem.h>
#include <string.h>
#include <nitro/std.h>
#include <nitro/fx/fx_atan.h>

#define FLD_ID(a, b, c, d) (((d) << 24) | ((c) << 16) | ((b) << 8) | (a))
#define FLD_LERP(a, b, t) ((a) + FX_Mul((b) - (a), (t)))
#define FLD_LERP_NR(a, b, t) ((a) + (fx32)(((fx64)(t) * ((b) - (a))) >> FX32_SHIFT))


// NNS_G3dGetResDataByIdx and the other resource accessors, without NULL checks
static inline void* FLD_GetResDataByIdx(const NNSG3dResDict* dict, unsigned int idx)
{
    NNSG3dResDictEntryHeader* p = (NNSG3dResDictEntryHeader*)((unsigned char*)dict + dict->ofsEntry);
    return &p->data[0] + p->sizeUnit * idx;
}

static inline void* FLD_GetPlttDataByName(const NNSG3dResTex* tex, const void* name)
{
    return func_02083064((NNSG3dResDict*)((unsigned char*)tex + tex->plttInfo.ofsDict), name);
}

static inline NNSG3dResShp* FLD_GetShp(NNSG3dResMdl* mdl)
{
    return (NNSG3dResShp*)((unsigned char*)mdl + mdl->ofsShp);
}

static inline NNSG3dResShpData* FLD_GetShpDataByIdx(const NNSG3dResShp* shp, unsigned int idx)
{
    const NNSG3dResDictShpData* data = (const NNSG3dResDictShpData*)FLD_GetResDataByIdx(&shp->dict, idx);
    return (NNSG3dResShpData*)((unsigned char*)shp + data->offset);
}

namespace race {

using namespace fld;

static int s_frameStep;
static int s_cameraNo;
static VecFx32 s_cameraPos;
static VecFx32 s_plane0;
static VecFx32 s_plane1;

static int compareRaceObjPriority(void* a, void* b);

// NNS_G3dResDefaultSetup with one VRAM block per texture
ARM static int setupRaceFldRes(void* file)
{
    unsigned int szTex;
    unsigned int szPltt;
    int result;
    int texKey;
    int keys[0x100];
    switch (*(unsigned int*)file) {
    case FLD_ID('B', 'M', 'D', '0'):
    case FLD_ID('B', 'T', 'X', '0'): {
        result = 1;
        texKey = 0;
        NNSG3dResTex* tex = func_02083270(file);
        if (tex != NULL) {
            unsigned int i;
            int plttKey;
            szTex = func_0207fc2c(tex);
            szPltt = func_0207fd08(tex);
            func_02076e98();
            for (i = 0; i < tex->dict.numEntry; i++) {
                NNSG3dResDictEntryHeader* p = (NNSG3dResDictEntryHeader*)((unsigned char*)&tex->dict + tex->dict.ofsEntry);
                unsigned int* param = (unsigned int*)(p->data + p->sizeUnit * i);
                unsigned int start;
                unsigned int end;
                if (i == tex->dict.numEntry - 1) {
                    start = (*param & 0xffff) << 3;
                    end = szTex;
                } else {
                    start = (*param & 0xffff) << 3;
                    end = (*(unsigned int*)(p->data + p->sizeUnit * (i + 1)) & 0xffff) << 3;
                }
                unsigned int size = end - start;
                texKey = (*data_0209c788)(size, 0, 0);
                keys[i] = texKey;
                func_02076ef4((unsigned char*)tex + tex->texInfo.ofsTex + start, (texKey & 0xffff) << 3, size);
                *param = (*param & 0xffff0000) | (texKey & 0xffff);
            }
            func_02077034();
            if (szPltt != 0) {
                plttKey = (*data_0209c790)(szPltt, tex->tex4x4Info.flag & 0x8000, 0);
                if (plttKey == 0) {
                    result = 0;
                }
            } else {
                plttKey = 0;
            }
            if (!result) {
                (*data_0209c794)(plttKey);
                (*data_0209c78c)(0);
                (*data_0209c78c)(texKey);
                return 0;
            }
            tex->texInfo.flag |= 1;
            tex->texInfo.vramKey = 0;
            func_0207fd18(tex, plttKey);
            func_0207fd1c(tex, 1);
        }
        if (*(unsigned int*)file == FLD_ID('B', 'M', 'D', '0')) {
            NNSG3dResMdlSet* mdlSet = func_02083268(file);
            if (tex != NULL) {
                func_0208012c(mdlSet, tex);
                for (unsigned int i = 0; i < tex->dict.numEntry; i++) {
                    NNSG3dResDictEntryHeader* p = (NNSG3dResDictEntryHeader*)((unsigned char*)&tex->dict + tex->dict.ofsEntry);
                    *(int*)(p->data + p->sizeUnit * i) = keys[i];
                }
            }
        }
        return 1;
    }
    case FLD_ID('B', 'C', 'A', '0'):
    case FLD_ID('B', 'V', 'A', '0'):
    case FLD_ID('B', 'M', 'A', '0'):
    case FLD_ID('B', 'T', 'P', '0'):
    case FLD_ID('B', 'T', 'A', '0'):
        return 1;
    default:
        return 0;
    }
}

// NNS_G3dResDefaultRelease for the textures set up by setupRaceFldRes
ARM static void releaseRaceFldRes(void* file, NNSG3dResTex* tex)
{
    int texKey;
    int tex4x4Key;
    switch (*(unsigned int*)file) {
    case FLD_ID('B', 'M', 'D', '0'): {
        NNSG3dResMdlSet* mdlSet = func_02083268(file);
        if (func_02083270(file) != NULL) {
            func_02080194(mdlSet);
        }
        break;
    }
    case FLD_ID('B', 'T', 'X', '0'):
    case FLD_ID('B', 'C', 'A', '0'):
    case FLD_ID('B', 'V', 'A', '0'):
    case FLD_ID('B', 'M', 'A', '0'):
    case FLD_ID('B', 'T', 'P', '0'):
    case FLD_ID('B', 'T', 'A', '0'):
        break;
    }
    if (tex == NULL) {
        return;
    }
    int plttKey = func_0207fd4c(tex);
    func_0207fcd8(tex, &texKey, &tex4x4Key);
    if (plttKey != 0) {
        (*data_0209c794)(plttKey);
    }
    if (tex4x4Key != 0) {
        (*data_0209c78c)(tex4x4Key);
    }
    for (unsigned int i = 0; i < tex->dict.numEntry; i++) {
        NNSG3dResDictEntryHeader* p = (NNSG3dResDictEntryHeader*)((unsigned char*)&tex->dict + tex->dict.ofsEntry);
        (*data_0209c78c)(*(int*)(p->data + p->sizeUnit * i));
    }
}

// blends two 15-bit colors
ARM static unsigned int blendRgb15(unsigned int c0, unsigned int c1, fx32 rate)
{
    short x0;
    short x1;
    unsigned int col;
    x0 = c0 & 0x1f;
    x1 = c1 & 0x1f;
    if (x0 != x1) {
        x0 = x0 + ((x1 - x0) * rate >> FX32_SHIFT);
    }
    col = x0 & 0x1f;
    x0 = (c0 >> 5) & 0x1f;
    x1 = (c1 >> 5) & 0x1f;
    if (x0 != x1) {
        x0 = x0 + ((x1 - x0) * rate >> FX32_SHIFT);
    }
    col |= (x0 & 0x1f) << 5;
    x0 = (c0 >> 10) & 0x1f;
    x1 = (c1 >> 10) & 0x1f;
    if (x0 != x1) {
        x0 = x0 + ((x1 - x0) * rate >> FX32_SHIFT);
    }
    col |= (x0 & 0x1f) << 10;
    return col;
}
static void calcRaceMapObjRender(FLD_MAP_OBJ* obj, VecFx32* ofs);
static int updateRaceFldAnim(UnkFldAnim* anim, FLD_ANIM_FUNC func, void* work);
static int applyRaceCameraKey(void* key0, void* key1, fx32 rate, void* work);
static int applyRaceObjKey(void* key0, void* key1, fx32 rate, void* work);
static int applyRaceObjKeyRotOffset(void* key0, void* key1, fx32 rate, void* work);
static int storeRaceSeqKeys(void* key0, void* key1, fx32 rate, void* work);
static int applyRaceSeqKey(void* key0, void* key1, fx32 rate, void* work);
static int applyRaceShapeMorph(void* key0, void* key1, fx32 rate, void* work);
static void morphDlTexCoords(fx32 rate, unsigned int size, unsigned int* dld, unsigned int* dl0, unsigned int* dl1);
static void morphDlVertices(fx32 rate, unsigned int size, unsigned int* dld, unsigned int* dl0, unsigned int* dl1);
static void morphDlTexCoordsVertices(fx32 rate, unsigned int size, unsigned int* dld, unsigned int* dl0, unsigned int* dl1);
static void morphDlAll(fx32 rate, unsigned int size, unsigned int* dld, unsigned int* dl0, unsigned int* dl1);
static int applyRaceLightKey(void* key0, void* key1, fx32 rate, void* work);
static int isRaceMapObjInView(UnkFldRender* render, fx32 far);
static int boxTestRaceMapObj(VecFx32* pos, VecFx32* rot, VecFx32* scale, VecFx32* box, fx32 rate);
static void skipRaceSbcBillboard(NNSG3dRS* rs, unsigned int opt);
static int unkfunc_0212e6b0(FLD_MAP_OBJ* obj, UnkFldModel* model);
static void setRaceMdlMatAlpha(NNSG3dResMdl* mdl, int alpha, unsigned char* base);

ARM FLDObject::FLDObject()
{
    m_flag = 0;
    init();
}

ARM FLDObject::~FLDObject()
{
    Final();
}

ARM void FLDObject::init()
{
    m_chunk = NULL;
    m_mdl = NULL;
    m_map = NULL;
    m_model = NULL;
    m_scene = NULL;
    m_seq = NULL;
    m_seq_num = 0;
    m_anim = NULL;
    m_camera_anim = NULL;
    m_pltt_anim = NULL;
    m_pltt = NULL;
    m_light = NULL;
    m_event = NULL;
    m_coll = NULL;
    m_tex = NULL;
    for (int i = 0; i < 2; i++) {
        m_camera_no[i] = 0;
        SetCameraPos(0, 0, 0, i);
        SetCameraCent(0, 0, FX32_ONE, i);
        SetCameraUp(0, FX32_ONE, 0, i);
    }
    m_frame_flip_flop = 0;
    m_vanish_flag = 0;
    m_common = NULL;
    m_bbox_far = FX32_ONE * 60;
    m_simple_bby = 1;
    m_box_test = 0;
    m_mat_alpha = NULL;
    m_event_anim_id = 0;
    m_scale.x = m_scale.y = m_scale.z = FX32_ONE;
}

ARM int FLDObject::Setup(void* mdl, void* data, void* coll, int heap)
{
    int i;
    if (coll != NULL) {
        coll = (unsigned char*)coll + 0x10;
    }
    if (m_flag & 1) {
        Final();
    }
    setupRaceFldRes(mdl);
    func_0207ebe4(&m_allocator, heap, 4);
    m_chunk = (UnkFldChunk*)((unsigned char*)data + 0x10);
    m_mdl = mdl;
    UnkFldChunk* chunk = m_chunk;
    while (chunk->id != 0) {
        switch (chunk->id) {
        case FLD_ID('F', 'M', 'A', 'P'):
            m_map = (FLD_MAP*)chunk;
            ((FLD_MAP*)chunk)->order = (short**)&((FLD_MAP*)chunk)->obj[((FLD_MAP*)chunk)->obj_num];
            m_map->index = (short*)&m_map->order[m_map->obj_num];
            break;
        case FLD_ID('F', 'M', 'D', 'L'):
            m_model = (UnkFldModelTbl*)chunk;
            break;
        case FLD_ID('F', 'S', 'Q', 'd'):
            if (m_seq_num < 0x80) {
                m_seq_data[m_seq_num] = (UnkFldResTbl*)chunk;
                m_seq_num++;
                for (i = 0; i < ((UnkFldResTbl*)chunk)->num; i++) {
                    ((UnkFldResTbl*)chunk)->res[i] = (unsigned char*)data + (int)((UnkFldResTbl*)chunk)->res[i];
                }
            }
            break;
        case FLD_ID('F', 'P', 'M', 'v'):
            m_anim = (UnkFldResTbl*)chunk;
            for (i = 0; i < ((UnkFldResTbl*)chunk)->num; i++) {
                ((UnkFldResTbl*)chunk)->res[i] = (unsigned char*)data + (int)((UnkFldResTbl*)chunk)->res[i];
            }
            break;
        case FLD_ID('F', 'E', 'M', 'v'):
            m_camera_anim = (UnkFldResTbl*)chunk;
            for (i = 0; i < ((UnkFldResTbl*)chunk)->num; i++) {
                ((UnkFldResTbl*)chunk)->res[i] = (unsigned char*)data + (int)((UnkFldResTbl*)chunk)->res[i];
            }
            break;
        case FLD_ID('F', 'P', 'A', 'M'):
            m_pltt_anim = (UnkFldResTbl*)chunk;
            for (i = 0; i < ((UnkFldResTbl*)chunk)->num; i++) {
                ((UnkFldResTbl*)chunk)->res[i] = (unsigned char*)data + (int)((UnkFldResTbl*)chunk)->res[i];
            }
            break;
        case FLD_ID('F', 'P', 'L', 'P'):
            m_pltt = (UnkFldPlttTbl*)chunk;
            break;
        case FLD_ID('F', 'C', 'A', 'N'): {
            UnkFldCommonKey* key;
            m_common = (UnkFldCommonTbl*)chunk;
            key = (UnkFldCommonKey*)&m_common->anim[m_common->num];
            for (i = 0; i < m_common->num; i++) {
                m_common->anim[i].key = key;
                key += m_common->anim[i].num;
            }
            break;
        }
        case FLD_ID('F', 'S', 'R', 'A'):
            m_light = (UnkFldResTbl*)chunk;
            for (i = 0; i < ((UnkFldResTbl*)chunk)->num; i++) {
                ((UnkFldResTbl*)chunk)->res[i] = (unsigned char*)data + (int)((UnkFldResTbl*)chunk)->res[i];
            }
            break;
        case FLD_ID('F', 'E', 'A', 'N'):
            m_event = (UnkFldEventTbl*)chunk;
            break;
        case FLD_ID('F', 'E', 'T', 'C'):
            m_scene = (UnkFldScene*)chunk;
            break;
        case FLD_ID('F', 'S', 'E', 'q'):
            m_seq = (UnkFldSeqTbl*)chunk;
            break;
        case FLD_ID('F', 'W', 'R', 'K'):
            m_pool = (unsigned char*)chunk;
            m_pool_rest = chunk->size;
            break;
        case FLD_ID('F', 'A', 'T', 'B'):
        case FLD_ID('F', 'T', 'T', 'B'):
        case FLD_ID('F', 'N', 'A', 'M'):
        case FLD_ID('F', 'H', 'D', 'R'):
        case FLD_ID('F', 'C', 'R', 'S'):
        case FLD_ID('F', 'C', 'R', 'T'):
        case FLD_ID('F', 'T', 'E', 'X'):
        case FLD_ID('F', 'P', 'T', 'X'):
        case FLD_ID('F', 'L', 'G', 't'):
        case FLD_ID('F', 'F', 'O', 'g'):
            break;
        }
        chunk = (UnkFldChunk*)((unsigned char*)chunk + chunk->size + sizeof(UnkFldChunk));
    }

    UnkFldModelTbl* model = m_model;
    FLD_MAP* map = m_map;
    m_mat_alpha = (unsigned char**)allocWork(model->num * sizeof(unsigned char*));
    memset(m_mat_alpha, 0, model->num * sizeof(unsigned char*));
    for (int i = 0; i < model->num; i++) {
        UnkFldModel* info = &model->model[i];
        NNSG3dResMdlSet* mdlSet = func_02083268(mdl);
        NNSG3dResDictEntryHeader* p = (NNSG3dResDictEntryHeader*)((unsigned char*)&mdlSet->dict + mdlSet->dict.ofsEntry);
        info->mdl = (NNSG3dResMdl*)((unsigned char*)mdlSet + ((NNSG3dResDictMdlSetData*)(p->data + p->sizeUnit * i))->offset);
        info->unk_18 = (unsigned char*)data + (int)info->unk_18;
        info->unk_14 = 0;
        if (info->fade != NULL) {
            info->fade = (UnkFldFade*)((unsigned char*)data + (int)info->fade);
        }
        if (info->unk_1c != NULL) {
            info->unk_1c = (unsigned char*)data + (int)info->unk_1c;
        }
        if (info->mdl->info.numMat != 0) {
            m_mat_alpha[i] = (unsigned char*)allocWork(info->mdl->info.numMat);
            for (unsigned int j = 0; j < info->mdl->info.numMat; j++) {
                m_mat_alpha[i][j] = func_02083018(info->mdl, j);
            }
        }
    }

    for (i = 0; i < map->obj_num; i++) {
        FLD_MAP_OBJ* obj = &map->obj[i];
        UnkFldModel* info = &model->model[obj->model];
        obj->model_info = info;
        obj->render = (UnkFldRender*)allocWork(sizeof(UnkFldRender));
        if (obj->render == NULL) {
            Final();
            return 0;
        }
        obj->render->render_obj = func_02082d7c(&m_allocator);
        func_0207fa78(obj->render->render_obj, info->mdl);
        obj->render->alpha = func_02083018(obj->render->render_obj->resMdl, 0);
        if (info->flag & 0x200) {
            obj->flag |= 0x100000;
        }
        if (info->flag & 0x400) {
            obj->flag |= 0x200000;
        }
        NNSG3dResMdlInfo* mdlInfo = &info->mdl->info;
        obj->render->box_x = mdlInfo->boxX;
        obj->render->box_y = mdlInfo->boxY;
        obj->render->box_w = mdlInfo->boxW;
        obj->render->box_h = mdlInfo->boxH;
        obj->render->box_d = mdlInfo->boxD;
        obj->render->box_scale = mdlInfo->boxPosScale;
        int z = mdlInfo->boxZ - mdlInfo->boxD;
        if (z <= -0x8000 || z >= 0x8000) {
            obj->render->box_z = z >> 1;
            obj->render->box_x >>= 1;
            obj->render->box_y >>= 1;
            obj->render->box_w >>= 1;
            obj->render->box_h >>= 1;
            obj->render->box_d >>= 1;
            obj->render->box_scale <<= 1;
        } else {
            obj->render->box_z = z;
        }
        obj->priority <<= 4;
        obj->render->flag = 7;
        calcRaceMapObjRender(obj, NULL);
    }

    sortMapObjOrder();
    m_tex = createPlttTexCopy();

    UnkFldLight* l;
    unsigned int mdlNum;
    UnkFldResTbl* light = m_light;
    if (light != NULL) {
        NNSG3dResMdlSet* mdlSet = func_02083268(m_mdl);
        mdlNum = mdlSet->dict.numEntry;
        UnkFldMatList* list = (UnkFldMatList*)allocWork(mdlNum * 8 + 4);
        if (list == NULL) {
            for (i = 0; i < light->num; i++) {
                ((UnkFldLight*)light->res[i])->mat_list = NULL;
            }
            Final();
            return 0;
        }
        for (i = 0; i < light->num; i++) {
            l = (UnkFldLight*)light->res[i];
            list->num = 0;
            for (unsigned int j = 0; j < mdlNum; j++) {
                char name[0x10];
                NNSG3dResDictEntryHeader* p = (NNSG3dResDictEntryHeader*)((unsigned char*)&mdlSet->dict + mdlSet->dict.ofsEntry);
                NNSG3dResMdl* resMdl = (NNSG3dResMdl*)((unsigned char*)mdlSet + ((NNSG3dResDictMdlSetData*)(p->data + p->sizeUnit * j))->offset);
                NNSG3dResMat* mat = (NNSG3dResMat*)((unsigned char*)resMdl + resMdl->ofsMat);
                MI_CpuSet(name, 0, sizeof(name));
                MI_CpuCopyU8(l->name, name, sizeof(name));
                int idx = func_02083180(&mat->dict, name);
                if (idx != -1) {
                    list->list[list->num].mat = idx;
                    list->list[list->num].mdl = resMdl;
                    list->num++;
                }
            }
            if (list->num != 0) {
                l->mat_list = (UnkFldMatList*)allocWork(list->num * 8 + 4);
                if (l->mat_list == NULL) {
                    Final();
                    break;
                }
                MI_CpuCopyU8(list, l->mat_list, list->num * 8 + 4);
            }
        }
        if (i < light->num) {
            for (; i < light->num; i++) {
                ((UnkFldLight*)light->res[i])->mat_list = NULL;
            }
            freeWork(list);
            return 0;
        }
        freeWork(list);
    }

    m_coll = (COLL_HEADER*)coll;
    if (!race::coll_init((COLL_HEADER*)coll, &m_allocator)) {
        Final();
        return 0;
    }
    func_020825dc(&m_ge_buffer);
    m_flag |= 1;
    return 1;
}

ARM static int compareRaceObjPriority(void* a, void* b)
{
    return ((FLD_OBJ_UID*)a)->uid - ((FLD_OBJ_UID*)b)->uid;
}

ARM void FLDObject::sortMapObjOrder()
{
    int i;
    unsigned char stack[0x100];
    FLD_OBJ_UID* uid = (FLD_OBJ_UID*)m_map->order;
    for (i = 0; i < m_map->obj_num; i++) {
        uid[i].uid = m_map->obj[i].priority;
        uid[i].obj_id = i;
    }
    func_0208a960(uid, m_map->obj_num, sizeof(FLD_OBJ_UID), compareRaceObjPriority, stack);
    for (i = 0; i < m_map->obj_num; i++) {
        m_map->order[i] = &m_map->index[uid[i].obj_id];
    }
}

ARM static void calcRaceMapObjRender(FLD_MAP_OBJ* obj, VecFx32* ofs)
{
    UnkFldRender* render = obj->render;
    if (render->flag & 8) {
        obj->pos.x = render->trans.x;
        obj->pos.y = render->trans.y;
        obj->pos.z = render->trans.z;
    } else if (render->flag & 1) {
        render->trans.x = obj->pos.x;
        render->trans.y = obj->pos.y;
        render->trans.z = obj->pos.z;
    }
    if (render->flag & 0x10) {
        obj->scale.x = render->scale.x;
        obj->scale.y = render->scale.y;
        obj->scale.z = render->scale.z;
    } else if (render->flag & 2) {
        render->scale.x = obj->scale.x;
        render->scale.y = obj->scale.y;
        render->scale.z = obj->scale.z;
    }
    if (render->flag & 0x20) {
        obj->rot.x = render->rot.x;
        obj->rot.y = render->rot.y;
        obj->rot.z = render->rot.z;
    } else if (render->flag & 4) {
        render->rot.x = obj->rot.x;
        render->rot.y = obj->rot.y;
        render->rot.z = obj->rot.z;
    }
    MtxFx33 mtx;
    if (render->rot.y != 0) {
        func_02088a70(&render->mtx, FX_SinIdx((unsigned short)render->rot.y), FX_CosIdx((unsigned short)render->rot.y));
    } else {
        func_02088970(&render->mtx);
    }
    if (render->rot.x != 0) {
        func_02088a54(&mtx, FX_SinIdx((unsigned short)render->rot.x), FX_CosIdx((unsigned short)render->rot.x));
        MTX_Concat33(&mtx, &render->mtx, &render->mtx);
    }
    if (render->rot.z != 0) {
        func_02088a8c(&mtx, FX_SinIdx((unsigned short)render->rot.z), FX_CosIdx((unsigned short)render->rot.z));
        MTX_Concat33(&mtx, &render->mtx, &render->mtx);
    }
    if (ofs != NULL) {
        VecFx32 v;
        func_02088cc4(ofs, &render->mtx, &v);
        func_0208a1a8(&v, &render->trans, &render->trans);
    }
    fx32 s = render->box_scale;
    func_02088994(&render->mtx, &mtx, FX_Mul(render->scale.x, s), FX_Mul(render->scale.y, s), FX_Mul(render->scale.z, s));
    VecFx32 box;
    VecFx32 min;
    box.x = render->box_x;
    box.y = render->box_y;
    box.z = render->box_z;
    func_02088cc4(&box, &mtx, &min);
    box.x += render->box_w >> 1;
    box.y += render->box_h >> 1;
    box.z += render->box_d >> 1;
    func_02088cc4(&box, &mtx, &render->center);
    render->radius2 = FX_Mul(render->center.x - min.x, render->center.x - min.x) + FX_Mul(render->center.y - min.y, render->center.y - min.y) + FX_Mul(render->center.z - min.z, render->center.z - min.z);
    render->radius = FX_Sqrt(render->radius2);
    func_0208a1a8(&render->center, &render->trans, &render->center);
    render->flag = 0;
}

ARM static int updateRaceFldAnim(UnkFldAnim* anim, FLD_ANIM_FUNC func, void* work)
{
    unsigned char* keys = (unsigned char*)anim->key;
    if (anim->flag & 4) {
        keys = (unsigned char*)((FLD_MAP_OBJ*)work)->render->keys;
    }
    int ret = -1;
    int num = anim->key_num;
    if (num != 0 && anim->loop_start != 0) {
        if (anim->wait > 0) {
            ret = func(keys, keys, 0, work);
            anim->wait -= s_frameStep;
        } else {
            unsigned char* key0;
            unsigned char* key1;
            fx32 rate;
            if (anim->frame == anim->frame_max) {
                key1 = keys + (num - 1) * anim->key_size;
                key0 = key1;
            } else {
                int size = anim->key_size;
                int lo = 0;
                while (lo < num) {
                    int mid = (lo + num) >> 1;
                    if (*(int*)(keys + mid * size) < anim->frame) {
                        lo = mid + 1;
                    } else {
                        num = mid;
                    }
                }
                key1 = keys + lo * size;
                key0 = key1;
                if (*(int*)key1 > anim->frame) {
                    key0 = key1 + -1 * size;
                } else if (*(int*)key1 < anim->frame) {
                    key1 += size;
                }
            }
            if (key0 == key1) {
                rate = 0;
            } else {
                rate = FX_Divide((anim->frame - *(int*)key0) << FX32_SHIFT, (*(int*)key1 - *(int*)key0) << FX32_SHIFT);
                if (rate == FX32_ONE) {
                    key0 = key1;
                    rate = 0;
                } else if (rate == 0) {
                    key1 = key0;
                }
            }
            ret = func(key0, key1, rate, work);
            if (!(anim->flag & 2)) {
                anim->frame += s_frameStep;
            }
            if (anim->frame > anim->frame_max) {
                if (anim->loop > 0) {
                    anim->loop--;
                }
                if (anim->loop == 0) {
                    anim->frame = anim->frame_max;
                } else {
                    anim->frame -= anim->frame_max;
                }
                anim->wait = anim->wait_init;
            }
        }
    }
    return ret;
}

ARM static int applyRaceCameraKey(void* key0, void* key1, fx32 rate, void* work)
{
    UnkFldCameraKey* k0 = (UnkFldCameraKey*)key0;
    UnkFldCameraKey* k1 = (UnkFldCameraKey*)key1;
    FLDObject* fld = (FLDObject*)work;
    int no = s_cameraNo;
    fld->SetCameraPos(FLD_LERP(k0->pos.x, k1->pos.x, rate), FLD_LERP(k0->pos.y, k1->pos.y, rate), FLD_LERP(k0->pos.z, k1->pos.z, rate), no);
    fld->SetCameraCent(FLD_LERP(k0->tag.x, k1->tag.x, rate), FLD_LERP(k0->tag.y, k1->tag.y, rate), FLD_LERP(k0->tag.z, k1->tag.z, rate), no);
    fld->SetCameraUp(FLD_LERP(k0->vec.x, k1->vec.x, rate), FLD_LERP(k0->vec.y, k1->vec.y, rate), FLD_LERP(k0->vec.z, k1->vec.z, rate), no);
    return 0;
}

ARM void FLDObject::SetCameraPos(fx32 x, fx32 y, fx32 z, int screen)
{
    m_x32_camera_pos[screen].x = x;
    m_x32_camera_pos[screen].y = y;
    m_x32_camera_pos[screen].z = z;
}

ARM void FLDObject::SetCameraCent(fx32 x, fx32 y, fx32 z, int screen)
{
    m_x32_camera_tag[screen].x = x;
    m_x32_camera_tag[screen].y = y;
    m_x32_camera_tag[screen].z = z;
}

ARM void FLDObject::SetCameraUp(fx32 x, fx32 y, fx32 z, int screen)
{
    m_x32_camera_vec[screen].x = x;
    m_x32_camera_vec[screen].y = y;
    m_x32_camera_vec[screen].z = z;
}

ARM void FLDObject::updateCameraAnim(int screen)
{
    UnkFldResTbl* camera = m_camera_anim;
    int no = m_camera_no[screen];
    if (camera == NULL || no == 0) {
        return;
    }
    if (no > camera->num) {
        return;
    }
    UnkFldAnim* anim = (UnkFldAnim*)camera->res[no - 1];
    s_cameraNo = screen;
    updateRaceFldAnim(anim, applyRaceCameraKey, this);
}

ARM static int applyRaceObjKey(void* key0, void* key1, fx32 rate, void* work)
{
    UnkFldObjKey* k0 = (UnkFldObjKey*)key0;
    UnkFldObjKey* k1 = (UnkFldObjKey*)key1;
    FLD_MAP_OBJ* obj = (FLD_MAP_OBJ*)work;
    if (rate == 0) {
        obj->render->trans.x = obj->pos.x + k0->pos.x;
        obj->render->trans.y = obj->pos.y + k0->pos.y;
        obj->render->trans.z = obj->pos.z + k0->pos.z;
        obj->render->rot.x = obj->rot.x + k0->rot.x;
        obj->render->rot.y = obj->rot.y + k0->rot.y;
        obj->render->rot.z = obj->rot.z + k0->rot.z;
        obj->render->scale.x = FX_Mul(obj->scale.x, k0->scale.x);
        obj->render->scale.y = FX_Mul(obj->scale.y, k0->scale.y);
        obj->render->scale.z = FX_Mul(obj->scale.z, k0->scale.z);
    } else {
        obj->render->trans.x = obj->pos.x + FLD_LERP_NR(k0->pos.x, k1->pos.x, rate);
        obj->render->trans.y = obj->pos.y + FLD_LERP_NR(k0->pos.y, k1->pos.y, rate);
        obj->render->trans.z = obj->pos.z + FLD_LERP_NR(k0->pos.z, k1->pos.z, rate);
        obj->render->rot.x = obj->rot.x + FLD_LERP_NR(k0->rot.x, k1->rot.x, rate);
        obj->render->rot.y = obj->rot.y + FLD_LERP_NR(k0->rot.y, k1->rot.y, rate);
        obj->render->rot.z = obj->rot.z + FLD_LERP_NR(k0->rot.z, k1->rot.z, rate);
        obj->render->scale.x = FX_Mul(obj->scale.x, FLD_LERP_NR(k0->scale.x, k1->scale.x, rate));
        obj->render->scale.y = FX_Mul(obj->scale.y, FLD_LERP_NR(k0->scale.y, k1->scale.y, rate));
        obj->render->scale.z = FX_Mul(obj->scale.z, FLD_LERP_NR(k0->scale.z, k1->scale.z, rate));
    }
    obj->render->flag = 0;
    calcRaceMapObjRender(obj, NULL);
    return 0;
}

ARM static int applyRaceObjKeyRotOffset(void* key0, void* key1, fx32 rate, void* work)
{
    UnkFldObjKey* k0 = (UnkFldObjKey*)key0;
    UnkFldObjKey* k1 = (UnkFldObjKey*)key1;
    FLD_MAP_OBJ* obj = (FLD_MAP_OBJ*)work;
    VecFx32 ofs;
    if (rate == 0) {
        ofs.x = k0->pos.x;
        ofs.y = k0->pos.y;
        ofs.z = k0->pos.z;
        obj->render->trans.x = obj->pos.x;
        obj->render->trans.y = obj->pos.y;
        obj->render->trans.z = obj->pos.z;
        obj->render->rot.x = obj->rot.x + k0->rot.x;
        obj->render->rot.y = obj->rot.y + k0->rot.y;
        obj->render->rot.z = obj->rot.z + k0->rot.z;
        obj->render->scale.x = FX_Mul(obj->scale.x, k0->scale.x);
        obj->render->scale.y = FX_Mul(obj->scale.y, k0->scale.y);
        obj->render->scale.z = FX_Mul(obj->scale.z, k0->scale.z);
    } else {
        ofs.x = FLD_LERP_NR(k0->pos.x, k1->pos.x, rate);
        ofs.y = FLD_LERP_NR(k0->pos.y, k1->pos.y, rate);
        ofs.z = FLD_LERP_NR(k0->pos.z, k1->pos.z, rate);
        obj->render->trans.x = obj->pos.x;
        obj->render->trans.y = obj->pos.y;
        obj->render->trans.z = obj->pos.z;
        obj->render->rot.x = obj->rot.x + FLD_LERP_NR(k0->rot.x, k1->rot.x, rate);
        obj->render->rot.y = obj->rot.y + FLD_LERP_NR(k0->rot.y, k1->rot.y, rate);
        obj->render->rot.z = obj->rot.z + FLD_LERP_NR(k0->rot.z, k1->rot.z, rate);
        obj->render->scale.x = FX_Mul(obj->scale.x, FLD_LERP_NR(k0->scale.x, k1->scale.x, rate));
        obj->render->scale.y = FX_Mul(obj->scale.y, FLD_LERP_NR(k0->scale.y, k1->scale.y, rate));
        obj->render->scale.z = FX_Mul(obj->scale.z, FLD_LERP_NR(k0->scale.z, k1->scale.z, rate));
    }
    obj->render->flag = 0;
    calcRaceMapObjRender(obj, &ofs);
    return 0;
}

ARM void FLDObject::updateMapObjAnim(int no)
{
    short index = m_map->index[no];
    FLD_MAP_OBJ* obj = &m_map->obj[index];
    if (index == -1) {
        return;
    }
    if (obj->flag & 0x1000000) {
        return;
    }
    if (obj->anim < 0) {
        return;
    }
    UnkFldAnim* anim = (UnkFldAnim*)m_anim->res[obj->anim];
    if (anim->flag & 4) {
        anim = &obj->render->anim;
    }
    if (obj->flag & 0x400000) {
        anim->flag |= 2;
        if (anim->flag & 4) {
            updateRaceFldAnim(anim, applyRaceObjKeyRotOffset, obj);
        } else {
            updateRaceFldAnim(anim, applyRaceObjKey, obj);
        }
        anim->flag &= ~2;
    } else if (anim->flag & 4) {
        updateRaceFldAnim(anim, applyRaceObjKeyRotOffset, obj);
    } else {
        updateRaceFldAnim(anim, applyRaceObjKey, obj);
    }
}

ARM void FLDObject::updateMapObjAnims()
{
    FLD_MAP* map = m_map;
    if (m_anim == NULL) {
        return;
    }
    for (int i = 0; i < map->obj_num; i++) {
        updateMapObjAnim(i);
    }
}

ARM static int storeRaceSeqKeys(void* key0, void* key1, fx32 rate, void* work)
{
    FLD_MAP_OBJ* obj = (FLD_MAP_OBJ*)work;
    obj->render->key0 = key0;
    obj->render->key1 = key1;
    obj->render->rate = rate;
    return 0;
}

ARM static int applyRaceSeqKey(void* key0, void* key1, fx32 rate, void* work)
{
    UnkFldSeqKey* k0 = (UnkFldSeqKey*)key0;
    UnkFldSeqKey* k1 = (UnkFldSeqKey*)key1;
    FLD_MAP_OBJ* obj = (FLD_MAP_OBJ*)work;
    obj->render->key0 = key0;
    obj->render->key1 = key1;
    obj->render->rate = rate;
    if (rate == 0) {
        obj->render->trans.x = obj->pos.x + k0->pos.x;
        obj->render->trans.y = obj->pos.y + k0->pos.y;
        obj->render->trans.z = obj->pos.z + k0->pos.z;
        obj->render->rot.x = obj->rot.x + k0->rot.x;
        obj->render->rot.y = obj->rot.y + k0->rot.y;
        obj->render->rot.z = obj->rot.z + k0->rot.z;
        obj->render->scale.x = FX_Mul(obj->scale.x, k0->scale.x);
        obj->render->scale.y = FX_Mul(obj->scale.y, k0->scale.y);
        obj->render->scale.z = FX_Mul(obj->scale.z, k0->scale.z);
    } else {
        obj->render->trans.x = obj->pos.x + FLD_LERP_NR(k0->pos.x, k1->pos.x, rate);
        obj->render->trans.y = obj->pos.y + FLD_LERP_NR(k0->pos.y, k1->pos.y, rate);
        obj->render->trans.z = obj->pos.z + FLD_LERP_NR(k0->pos.z, k1->pos.z, rate);
        obj->render->rot.x = obj->rot.x + FLD_LERP_NR(k0->rot.x, k1->rot.x, rate);
        obj->render->rot.y = obj->rot.y + FLD_LERP_NR(k0->rot.y, k1->rot.y, rate);
        obj->render->rot.z = obj->rot.z + FLD_LERP_NR(k0->rot.z, k1->rot.z, rate);
        obj->render->scale.x = FX_Mul(obj->scale.x, FLD_LERP_NR(k0->scale.x, k1->scale.x, rate));
        obj->render->scale.y = FX_Mul(obj->scale.y, FLD_LERP_NR(k0->scale.y, k1->scale.y, rate));
        obj->render->scale.z = FX_Mul(obj->scale.z, FLD_LERP_NR(k0->scale.z, k1->scale.z, rate));
    }
    obj->render->flag = 0;
    calcRaceMapObjRender(obj, NULL);
    return 0;
}

ARM static int applyRaceShapeMorph(void* key0, void* key1, fx32 rate, void* work)
{
    UnkFldSeqKey* k0;
    UnkFldSeqKey* k1;
    FLD_MAP_OBJ* obj;
    int num;
    NNSG3dResShp* shp;
    int i;
    NNSG3dResShpData* s0;
    NNSG3dResShpData* s1;
    NNSG3dResShpData* sd;
    unsigned int* dl0;
    unsigned int* dld;
    unsigned int* dl1;
    unsigned int size;
    k0 = (UnkFldSeqKey*)key0;
    k1 = (UnkFldSeqKey*)key1;
    obj = (FLD_MAP_OBJ*)work;
    num = obj->model_info->shape_num;
    if (obj->model_info->shape0 == k0->shape && obj->model_info->shape1 == k1->shape && obj->model_info->shape_rate == rate) {
        return 0;
    }
    obj->model_info->shape0 = k0->shape;
    obj->model_info->shape1 = k1->shape;
    obj->model_info->shape_rate = rate;
    shp = FLD_GetShp(obj->render->render_obj->resMdl);
    for (i = 0; i < num; i++) {
        sd = FLD_GetShpDataByIdx(shp, i);
        s0 = FLD_GetShpDataByIdx(shp, num * (k0->shape + 2) + i);
        s1 = FLD_GetShpDataByIdx(shp, num * (k1->shape + 2) + i);
        dld = (unsigned int*)((unsigned char*)sd + sd->ofsDL);
        dl0 = (unsigned int*)((unsigned char*)s0 + s0->ofsDL);
        dl1 = (unsigned int*)((unsigned char*)s1 + s1->ofsDL);
        size = sd->sizeDL / 4;
        switch (obj->flag & 0x70000000) {
        case 0x20000000:
            morphDlVertices(rate, size, dld, dl0, dl1);
            break;
        case 0x40000000:
            morphDlTexCoords(rate, size, dld, dl0, dl1);
            break;
        case 0x60000000:
            morphDlTexCoordsVertices(rate, size, dld, dl0, dl1);
            break;
        default:
            morphDlAll(rate, size, dld, dl0, dl1);
            break;
        }
    }
    return 0;
}

#define FLD_LERP_S16(dst, src0, src1, rate)             \
    x1 = (src1);                                        \
    x0 = (src0);                                        \
    if (x0 == x1) {                                     \
        (dst) = x0;                                     \
    } else {                                            \
        (dst) = x0 + ((x1 - x0) * (rate) >> FX32_SHIFT);\
    }

// texture coordinates only
ARM static void morphDlTexCoords(fx32 rate, unsigned int size, unsigned int* dld, unsigned int* dl0, unsigned int* dl1)
{
    unsigned int pos;
    unsigned int cmd;
    int j;
    short* a;
    short* b;
    short* d;
    unsigned int op;
    short x0;
    short x1;
    for (pos = 0; pos < size;) {
        cmd = dld[pos];
        pos++;
        for (j = 4; j > 0; j--) {
            op = cmd & 0xff;
            cmd >>= 8;
            if (op == 0x22) {
                d = (short*)&dld[pos];
                a = (short*)&dl0[pos];
                b = (short*)&dl1[pos];
                FLD_LERP_S16(d[0], a[0], b[0], rate);
                FLD_LERP_S16(d[1], a[1], b[1], rate);
                pos++;
            } else if (op == 0x23) {
                pos += 2;
            } else if (op != 0 && op != 0x41) {
                pos++;
            }
        }
    }
}

// vertex positions only
ARM static void morphDlVertices(fx32 rate, unsigned int size, unsigned int* dld, unsigned int* dl0, unsigned int* dl1)
{
    unsigned int pos;
    unsigned int cmd;
    int j;
    short* a;
    short* b;
    short* d;
    unsigned int op;
    short x0;
    short x1;
    for (pos = 0; pos < size;) {
        cmd = dld[pos];
        pos++;
        for (j = 4; j > 0; j--) {
            op = cmd & 0xff;
            cmd >>= 8;
            if (op == 0x23) {
                d = (short*)&dld[pos];
                a = (short*)&dl0[pos];
                b = (short*)&dl1[pos];
                FLD_LERP_S16(d[0], a[0], b[0], rate);
                FLD_LERP_S16(d[1], a[1], b[1], rate);
                FLD_LERP_S16(d[2], a[2], b[2], rate);
                pos += 2;
            } else if (op != 0 && op != 0x41) {
                pos++;
            }
        }
    }
}

// texture coordinates and vertex positions
ARM static void morphDlTexCoordsVertices(fx32 rate, unsigned int size, unsigned int* dld, unsigned int* dl0, unsigned int* dl1)
{
    unsigned int pos;
    unsigned int cmd;
    int j;
    short* a;
    short* b;
    short* d;
    short* a2;
    short* b2;
    short* d2;
    unsigned int op;
    short x0;
    short x1;
    for (pos = 0; pos < size;) {
        cmd = dld[pos];
        pos++;
        for (j = 4; j > 0; j--) {
            op = cmd & 0xff;
            cmd >>= 8;
            if (op == 0x22) {
                d = (short*)&dld[pos];
                a = (short*)&dl0[pos];
                b = (short*)&dl1[pos];
                FLD_LERP_S16(d[0], a[0], b[0], rate);
                FLD_LERP_S16(d[1], a[1], b[1], rate);
                pos++;
            } else if (op == 0x23) {
                d2 = (short*)&dld[pos];
                a2 = (short*)&dl0[pos];
                b2 = (short*)&dl1[pos];
                FLD_LERP_S16(d2[0], a2[0], b2[0], rate);
                FLD_LERP_S16(d2[1], a2[1], b2[1], rate);
                FLD_LERP_S16(d2[2], a2[2], b2[2], rate);
                pos += 2;
            } else if (op != 0 && op != 0x41) {
                pos++;
            }
        }
    }
}

// colors, texture coordinates and vertex positions
ARM static void morphDlAll(fx32 rate, unsigned int size, unsigned int* dld, unsigned int* dl0, unsigned int* dl1)
{
    unsigned int pos;
    unsigned int cmd;
    int j;
    short* a;
    short* b;
    short* d;
    short* a2;
    short* b2;
    short* d2;
    unsigned int c0;
    short x0;
    short x1;
    for (pos = 0; pos < size;) {
        cmd = dld[pos];
        pos++;
        for (j = 4; j > 0; j--) {
            switch (cmd & 0xff) {
            case 0x20:
                c0 = dl0[pos];
                if (c0 == dl1[pos]) {
                    dld[pos] = c0;
                } else {
                    dld[pos] = blendRgb15(c0, dl1[pos], rate);
                }
                pos++;
                break;
            case 0x22:
                d = (short*)&dld[pos];
                a = (short*)&dl0[pos];
                b = (short*)&dl1[pos];
                FLD_LERP_S16(d[0], a[0], b[0], rate);
                FLD_LERP_S16(d[1], a[1], b[1], rate);
                pos++;
                break;
            case 0x23:
                d2 = (short*)&dld[pos];
                a2 = (short*)&dl0[pos];
                b2 = (short*)&dl1[pos];
                FLD_LERP_S16(d2[0], a2[0], b2[0], rate);
                FLD_LERP_S16(d2[1], a2[1], b2[1], rate);
                FLD_LERP_S16(d2[2], a2[2], b2[2], rate);
                pos += 2;
                break;
            case 0x40:
                pos++;
                break;
            case 0:
            case 0x41:
                break;
            }
            cmd >>= 8;
        }
    }
}

ARM void FLDObject::updateMapObjSeq(FLD_MAP_OBJ* obj)
{
    UnkFldSeq* seq;
    UnkFldAnim* anim;
    UnkFldSeqKey* keys;
    UnkFldSeqKey* last;
    int frame;
    int num;
    if (m_seq == NULL) {
        return;
    }
    if (obj->seq < 0) {
        return;
    }
    seq = &m_seq->seq[obj->seq];
    if (seq->data < 0) {
        return;
    }
    anim = (UnkFldAnim*)m_seq_data[seq->data]->res[seq->anim];
    anim->wait = seq->wait;
    anim->wait_init = seq->wait_init;
    anim->loop = seq->loop;
    anim->frame = seq->frame;
    anim->loop_start = seq->loop_start;
    num = anim->key_num;
    if (anim->flag & 1) {
        if (anim->flag & 8) {
            keys = (UnkFldSeqKey*)anim->key;
            last = &keys[num - 1];
            frame = last->frame;
            if (obj->flag & 2) {
                *last = keys[0];
            } else {
                *last = keys[num - 2];
            }
            keys[anim->key_num - 1].frame = frame;
        } else {
            UnkFldShapeKey* keys = (UnkFldShapeKey*)anim->key;
            int shape;
            if (obj->flag & 2) {
                shape = keys[0].shape;
            } else {
                shape = keys[num - 2].shape;
            }
            keys[num - 1].shape = shape;
        }
    } else {
        anim->key_num = num - 1;
    }
    FLD_ANIM_FUNC func = (anim->flag & 8) ? applyRaceSeqKey : storeRaceSeqKeys;
    if (obj->flag & 0x400000) {
        anim->flag |= 2;
        updateRaceFldAnim(anim, func, obj);
        anim->flag &= ~2;
    } else {
        updateRaceFldAnim(anim, func, obj);
    }
    seq->wait = anim->wait;
    seq->wait_init = anim->wait_init;
    seq->loop = anim->loop;
    seq->frame = anim->frame;
    seq->loop_start = anim->loop_start;
    anim->key_num = num;
}

ARM void FLDObject::applyMapObjShapeMorph(FLD_MAP_OBJ* obj)
{
    if (m_seq == NULL) {
        return;
    }
    if (obj->seq < 0) {
        return;
    }
    if (m_seq->seq[obj->seq].data < 0) {
        return;
    }
    applyRaceShapeMorph(obj->render->key0, obj->render->key1, obj->render->rate, obj);
}

ARM void FLDObject::updatePlttAnims()
{
    int i;
    UnkFldPlttTbl* pltt = m_pltt;
    UnkFldResTbl* anim = m_pltt_anim;
    UnkFldPlttEntry* entry;
    UnkFldPlttSet* set;
    int index;
    int wait;
    if (pltt == NULL || anim == NULL) {
        return;
    }
    for (i = 0; i < pltt->num; i++) {
        entry = &pltt->entry[i];
        set = (UnkFldPlttSet*)anim->res[entry->anim];
        index = set->index;
        if (entry->event != 0) {
            if (entry->event == m_event_anim_id) {
                continue;
            }
            index = 0;
        }
        copyPlttAnimFrame(entry, set, index);
    }
    if (m_event_anim_id > 0) {
        for (i = 0; i < pltt->num; i++) {
            entry = &pltt->entry[i];
            if (entry->event == m_event_anim_id) {
                set = (UnkFldPlttSet*)anim->res[entry->anim];
                copyPlttAnimFrame(entry, set, set->index);
            }
        }
    }
    for (i = 0; i < anim->num; i++) {
        UnkFldPlttSet* set = (UnkFldPlttSet*)anim->res[i];
        if (set->flag & 1) {
            wait = ((UnkFldPltt256*)set->data)[set->index].wait;
        } else {
            wait = ((UnkFldPltt16*)set->data)[set->index].wait;
        }
        set->timer += s_frameStep;
        if (set->timer >= wait) {
            set->timer -= wait;
            set->index++;
            if (set->index >= set->count) {
                set->index = 0;
            }
        }
    }
    m_flag |= 0x80;
}

ARM void FLDObject::copyPlttAnimFrame(UnkFldPlttEntry* entry, UnkFldPlttSet* set, int index)
{
    int ofs = m_tex->plttInfo.sizePltt;
    unsigned short* src;
    int size;
    if (set->flag & 1) {
        size = sizeof(((UnkFldPltt256*)set->data)[index].col);
        src = ((UnkFldPltt256*)set->data)[index].col;
    } else {
        size = sizeof(((UnkFldPltt16*)set->data)[index].col);
        src = ((UnkFldPltt16*)set->data)[index].col;
    }
    if (m_flag & 0x40) {
        MI_CpuCopyU8(src, entry->pltt + ofs * 4, size);
    } else {
        MI_CpuCopyU8(src, entry->pltt, size);
    }
}

ARM static int applyRaceLightKey(void* key0, void* key1, fx32 rate, void* work)
{
    UnkFldLightKey* k0 = (UnkFldLightKey*)key0;
    UnkFldLightKey* k1 = (UnkFldLightKey*)key1;
    UnkFldLight* light = (UnkFldLight*)work;
    unsigned short diff;
    unsigned short amb;
    unsigned short spec;
    unsigned short emi;
    int alpha;
    unsigned int i;
    NNSG3dResMdl* mdl;
    if (k0 == k1) {
        amb = k0->amb;
        diff = k0->diff;
        spec = k0->spec;
        emi = k0->emi;
        alpha = k0->alpha;
    } else {
        unsigned int c0, c1, x0, x1;
        c0 = k0->amb;
        if (c0 != k1->amb) {
            c0 = blendRgb15(c0, k1->amb, rate);
        }
        amb = c0;
        c0 = k0->spec;
        if (c0 != k1->spec) {
            c0 = blendRgb15(c0, k1->spec, rate);
        }
        spec = c0;
        c0 = k0->emi;
        if (c0 != k1->emi) {
            c0 = blendRgb15(c0, k1->emi, rate);
        }
        emi = c0;
        c0 = k0->diff;
        if (c0 != k1->diff) {
            c0 = blendRgb15(c0, k1->diff, rate);
        }
        diff = c0;
        c0 = k0->alpha;
        c1 = k1->alpha;
        if (c0 != c1) {
            x0 = c0 & 0x1f;
            x1 = c1 & 0x1f;
            if (x0 != x1) {
                x0 = x0 + FX_Mul(x1 - x0, rate);
            }
            c0 = x0 & 0x1f;
        }
        alpha = c0;
    }
    if (light->mat_list != NULL) {
        UnkFldMatList* list = light->mat_list;
        for (i = 0; i < list->num; i++) {
            mdl = list->list[i].mdl;
            int mat = list->list[i].mat;
            func_02082ed8(mdl, mat, amb);
            func_02082f28(mdl, mat, spec);
            func_02082f78(mdl, mat, emi);
            func_02082e88(mdl, mat, diff);
            func_02082fc8(mdl, mat, alpha);
        }
    }
    return 0;
}

ARM void FLDObject::updateLightAnims()
{
    UnkFldResTbl* light = m_light;
    if (light == NULL) {
        return;
    }
    for (int i = 0; i < light->num; i++) {
        UnkFldLight* l = (UnkFldLight*)light->res[i];
        updateRaceFldAnim(&l->anim, applyRaceLightKey, l);
    }
}

ARM void FLDObject::calc()
{
    if (!(m_flag & 1)) {
        return;
    }
    if (m_flag & 4) {
        return;
    }
    m_frame_flip_flop ^= 1;
    if (m_frame_flip_flop == 0) {
        s_frameStep = 2;
    } else {
        s_frameStep = 0;
    }
    updateCameraAnim(0);
    if (m_camera_no[0] != m_camera_no[1]) {
        updateCameraAnim(1);
    } else {
        m_x32_camera_pos[1].x = m_x32_camera_pos[0].x;
        m_x32_camera_pos[1].y = m_x32_camera_pos[0].y;
        m_x32_camera_pos[1].z = m_x32_camera_pos[0].z;
        m_x32_camera_tag[1].x = m_x32_camera_tag[0].x;
        m_x32_camera_tag[1].y = m_x32_camera_tag[0].y;
        m_x32_camera_tag[1].z = m_x32_camera_tag[0].z;
        m_x32_camera_vec[1].x = m_x32_camera_vec[0].x;
        m_x32_camera_vec[1].y = m_x32_camera_vec[0].y;
        m_x32_camera_vec[1].z = m_x32_camera_vec[0].z;
    }
    updateMapObjAnims();
    updatePlttAnims();
    updateLightAnims();
    if (m_flag & 0x100) {
        return;
    }
    if (m_flag & 0x40) {
        applyRgbRateToPltt();
    }
    if (m_flag & 0xc0) {
        transferPltt();
    }
}

ARM static int isRaceMapObjInView(UnkFldRender* render, fx32 far)
{
    fx32 dx = render->center.x - s_cameraPos.x;
    fx32 dz = render->center.z - s_cameraPos.z;
    if (FX_Mul(dx, dx) + FX_Mul(dz, dz) - render->radius2 >= far) {
        return 0;
    }
    VecFx32 pos;
    VecFx32 dir;
    func_0208a574(render->radius, &s_plane0, &render->center, &pos);
    func_0208a1dc(&pos, &s_cameraPos, &dir);
    if (func_0208a210(&dir, &s_plane0) < 0) {
        return 0;
    }
    func_0208a574(render->radius, &s_plane1, &render->center, &pos);
    func_0208a1dc(&pos, &s_cameraPos, &dir);
    return func_0208a210(&dir, &s_plane1) >= 0;
}

ARM static int boxTestRaceMapObj(VecFx32* pos, VecFx32* rot, VecFx32* scale, VecFx32* box, fx32 rate)
{
    int result;
    G3_PushMtx();
    G3_Translate(pos->x, pos->y, pos->z);
    func_020761a0(FX_SinIdx((unsigned short)rot->y), FX_CosIdx((unsigned short)rot->y));
    func_02076164(FX_SinIdx((unsigned short)rot->x), FX_CosIdx((unsigned short)rot->x));
    func_020761dc(FX_SinIdx((unsigned short)rot->z), FX_CosIdx((unsigned short)rot->z));
    G3_Scale(scale->x, scale->y, scale->z);
    G3_Scale(rate, rate, rate);
    REG_GFX_FIFO_BOX_TEST = box->x;
    REG_GFX_FIFO_BOX_TEST = box->y;
    REG_GFX_FIFO_BOX_TEST = box->z;
    while (func_02075ff4(&result)) {
    }
    G3_PopMtx(1);
    return result;
}

ARM static void skipRaceSbcBillboard(NNSG3dRS* rs, unsigned int opt)
{
    int len = 2;
    if (opt & 0x40) {
        len++;
    }
    if (opt & 0x20) {
        len++;
    }
    rs->c += len;
}

ARM static int unkfunc_0212e6b0(FLD_MAP_OBJ* obj, UnkFldModel* model)
{
    UnkFldFade* fade = model->fade;
    int alpha = 0x1f;
    fx32 dist = func_0208a5d0(&obj->render->trans, &data_02124bb4.camPos);
    if (dist < fade->end) {
        fx32 rate = 0;
        if (fade->end - fade->start > 0) {
            rate = FX_Divide(dist - fade->start, fade->end - fade->start);
            if (rate < 0) {
                rate = 0;
            } else if (rate >= FX32_ONE) {
                rate = FX32_ONE;
            }
        }
        alpha = (fade->min + FX_Mul(rate, FX32_ONE - fade->min)) >> 7;
        if (alpha < 0) {
            alpha = 0;
        } else if (alpha >= 0x1f) {
            alpha = 0x1f;
        }
    }
    return alpha;
}

ARM static void setRaceMdlMatAlpha(NNSG3dResMdl* mdl, int alpha, unsigned char* base)
{
    for (unsigned int i = 0; i < mdl->info.numMat; i++) {
        func_02082fc8(mdl, i, alpha * base[i] / 31);
    }
}

#define FLD_DRAW_OBJ(obj)                                                                               \
    if ((model->flag & 0x1f) != obj->render->alpha) {                                                   \
        model->flag = (model->flag & ~0x1f) | obj->render->alpha;                                       \
        setRaceMdlMatAlpha(obj->render->render_obj->resMdl, obj->render->alpha, m_mat_alpha[obj->model]); \
    }                                                                                                   \
    func_020826d0(0x17, &data_02124bb4.cameraMtx, 12);                                                  \
    func_020826d0(0x1c, &obj->render->trans, 3);                                                        \
    if (obj->flag & 0x24) {                                                                             \
        func_020826d0(0x1a, (obj->flag & 4) ? &rot : func_020803f8(), 9);                               \
    } else {                                                                                            \
        func_020826d0(0x1a, &obj->render->mtx, 9);                                                      \
    }                                                                                                   \
    func_020826d0(0x1b, &obj->render->scale, 3);                                                        \
    G3d_Render(obj->render->render_obj);

inline void* OS_GetITCMArenaLo()
{
    return OS_GetArenaLo(3);
}

ARM void FLDObject::draw()
{
    MtxFx43 saved;
    MtxFx33 rot;
    FLD_MAP_OBJ** work;
    int i;
    FLD_MAP_OBJ* robj;
    FLD_MAP* map;
    UnkFldModel* model;
    short** p;
    short** end;
    int flag;
    int count = 0;
    int deferred;
    MtxFx43* cam;
    fx32 far2;
    map = m_map;
    if (!(m_flag & 1)) {
        return;
    }
    work = (FLD_MAP_OBJ**)(((unsigned int)OS_GetITCMArenaLo() + 3) & ~3);
    cam = &data_02124bb4.cameraMtx;
    end = map->order + map->obj_num;
    data_0209c6a8[7] = skipRaceSbcBillboard;
    data_0209c6a8[8] = skipRaceSbcBillboard;
    saved = *cam;
    func_02088d9c(&saved, cam, m_scale.x, m_scale.y, m_scale.z);
    {
        const VecFx32* pos = &data_02124bb4.camPos;
        const VecFx32* tgt = &data_02124bb4.camTarget;
        unsigned short rotY = FX_Atan2Idx(tgt->z - pos->z, tgt->x - pos->x) + 0x8000;
        func_02088a70(&rot, FX_CosIdx(rotY), FX_SinIdx(rotY));
    }
    {
        VecFx32 scale = {FX32_ONE, FX32_ONE, FX32_ONE};
        VecFx32 trans = {0, 0, 0};
        MtxFx33 baseRot;
        func_02088970(&baseRot);
        func_0208032c(&scale);
        func_02070360(&baseRot, &data_02124bb4.prmBaseRot);
        data_02124bb4.flag &= ~0xa4;
        func_02080308((dss::Fix32Vector3*)&trans);
        func_020802dc();
    }
    {
        VecFx32 far[4];
        VecFx32 near;
        VecFx32 v0;
        VecFx32 v1;
        int x1;
        int y1;
        int x2;
        int y2;
        fx32 z;
        func_0208069c(&x1, &y1, &x2, &y2);
        x1--;
        y1--;
        x2++;
        y2++;
        func_02082b90(x1, y1, &near, &far[0]);
        func_02082b90(x1, y2, &near, &far[1]);
        func_02082b90(x2, y1, &near, &far[2]);
        func_02082b90(x2, y2, &near, &far[3]);
        near.x = data_02124bb4.camPos.x;
        near.y = data_02124bb4.camPos.y;
        z = data_02124bb4.camPos.z;
        s_cameraPos.x = near.x;
        s_cameraPos.y = near.y;
        s_cameraPos.z = z;
        near.z = z;
        func_0208a1dc(&far[1], &near, &v0);
        func_0208a1dc(&far[0], &near, &v1);
        func_0208a24c(&v0, &v1, &s_plane0);
        func_0208a330(&s_plane0, &s_plane0);
        func_0208a1dc(&far[2], &near, &v0);
        func_0208a1dc(&far[3], &near, &v1);
        func_0208a24c(&v0, &v1, &s_plane1);
        func_0208a330(&s_plane1, &s_plane1);
    }
    if (m_box_test == 0) {
        far2 = FX_Mul(m_bbox_far, m_bbox_far);
        for (p = map->order; p != end; p++) {
            if (**p == -1) {
                continue;
            }
            FLD_MAP_OBJ* obj = &map->obj[**p];
            flag = obj->flag;
            if (flag & 0x1000000) {
                continue;
            }
            if (obj->render->flag != 0) {
                calcRaceMapObjRender(obj, NULL);
            }
            if (!(m_flag & 4)) {
                updateMapObjSeq(obj);
            }
            if (flag & 0x2000000) {
                continue;
            }
            if (isRaceMapObjInView(obj->render, far2)) {
                if (!(m_flag & 4)) {
                    applyMapObjShapeMorph(obj);
                }
                work[count++] = obj;
            }
        }
    } else if (m_box_test == 1) {
        G3_MtxMode(3);
        G3_Identity();
        G3_MtxMode(2);
        G3_PolygonAttr(1, 0, 0xc0, 0, 0, 0x3000);
        G3_Begin(0);
        G3_End();
        for (p = map->order; p != end; p++) {
            if (**p == -1) {
                continue;
            }
            FLD_MAP_OBJ* obj = &map->obj[**p];
            flag = obj->flag;
            if (flag & 0x1000000) {
                continue;
            }
            if (obj->render->flag != 0) {
                calcRaceMapObjRender(obj, NULL);
            }
            if (!(m_flag & 4)) {
                updateMapObjSeq(obj);
            }
            if (flag & 0x2000000) {
                continue;
            }
            if (boxTestRaceMapObj(&obj->render->trans, &obj->render->rot, &obj->render->scale, (VecFx32*)&obj->render->box_x, obj->render->box_scale)) {
                if (!(m_flag & 4)) {
                    applyMapObjShapeMorph(obj);
                }
                work[count++] = obj;
            }
        }
    }
    DC_CleanAll();
    deferred = count;
    for (i = 0; i < count; i++) {
        robj = work[i];
        model = robj->model_info;
        if (robj->flag & 0x300000) {
            if (m_vanish_flag == 0) {
                robj->render->alpha = 0x1f;
            } else {
                robj->render->alpha = unkfunc_0212e6b0(robj, model);
            }
        }
        if (robj->render->alpha != 0x1f && !(flag & 0x4000000)) {
            work[deferred++] = robj;
            continue;
        }
        FLD_DRAW_OBJ(robj);
    }
    for (; count < deferred; count++) {
        robj = work[count];
        model = robj->model_info;
        FLD_DRAW_OBJ(robj);
    }
    func_02082604();
    data_0209c6a8[7] = G3d_SBCRender_007;
    data_0209c6a8[8] = G3d_SBCRender_008;
    *cam = saved;
}

ARM void FLDObject::Final()
{
    FLD_MAP* map;
    int i;
    UnkFldResTbl* light;
    UnkFldLight* l;
    map = m_map;
    if (!(m_flag & 1)) {
        return;
    }
    for (i = 0; i < map->obj_num; i++) {
        if (map->obj[i].render != NULL) {
            func_02082d88(&m_allocator, map->obj[i].render->render_obj);
            freeWork(map->obj[i].render);
            map->obj[i].render = NULL;
        }
    }
    light = m_light;
    if (light != NULL) {
        for (i = 0; i < light->num; i++) {
            l = (UnkFldLight*)light->res[i];
            if (l->mat_list != NULL) {
                freeWork(l->mat_list);
            }
        }
    }
    func_020825f0();
    releaseRaceFldRes(m_mdl, m_tex);
    if (m_coll != NULL && m_coll->ext_data != NULL) {
        func_0207ebd8(&m_allocator, m_coll->ext_data);
    }
    freeWork(m_tex);
    if (m_mat_alpha != NULL) {
        for (i = 0; i < m_model->num; i++) {
            if (*(unsigned char**)((unsigned char*)m_mat_alpha + i * (int)sizeof(unsigned char*)) != NULL) {
                freeWork(*(unsigned char**)((unsigned char*)m_mat_alpha + i * (int)sizeof(unsigned char*)));
            }
        }
        freeWork(m_mat_alpha);
    }
    m_flag &= ~1;
    init();
}

ARM int FLDObject::setEventAnimation(int id)
{
    int i;
    int j;
    int start;
    int end;
    int num;
    UnkFldPlttEntry* entry;
    UnkFldResTbl* light;
    UnkFldPlttSet* set;
    UnkFldPlttTbl* pltt;
    UnkFldLight* l;
    UnkFldResTbl* pltt_anim;
    if (m_event == NULL || id < 0 || id > m_event->num) {
        return 0;
    }
    m_event_anim_id = id;
    if (id == 0) {
        end = m_map->uid_num;
        for (i = 0; i < end; i++) {
            setMapObjIndex(i, i);
        }
        if (m_map->extra != 0) {
            setMapObjIndex(i - 1, -1);
        }
        for (; i < m_map->obj_num; i++) {
            setMapObjIndex(i, -1);
        }
        if (m_map->extra != 0) {
            setMapObjIndex(i - 1, m_map->obj_num - 1);
        }
    } else {
        start = m_event->event[id - 1].start;
        end = m_event->event[id - 1].end;
        num = m_map->uid_num;
        if (m_map->extra != 0) {
            num--;
        }
        for (i = start; i < end; i++) {
            setMapObjIndex(i, i);
            resetMapObjAnim(i);
            if (m_anim != NULL) {
                updateMapObjAnim(i);
            }
            for (j = 0; j < num; j++) {
                if (m_map->obj[i].uid != 0 && m_map->obj[i].uid == m_map->obj[j].uid) {
                    setMapObjIndex(j, -1);
                }
            }
        }
        light = m_light;
        if (light != NULL) {
            for (i = 0; i < light->num; i++) {
                l = (UnkFldLight*)light->res[i];
                if (l->anim.event_id > 0 && l->anim.event_id == m_event_anim_id) {
                    l->anim.loop = l->anim.loop_start;
                    l->anim.wait = l->anim.wait_start;
                    l->anim.frame = 0;
                    updateRaceFldAnim(&l->anim, applyRaceLightKey, l);
                }
            }
        }
        pltt = m_pltt;
        if (pltt != NULL && (pltt_anim = m_pltt_anim) != NULL) {
            i = 0;
            if (pltt->num > 0) {
                entry = pltt->entry;
                do {
                    set = (UnkFldPlttSet*)pltt_anim->res[entry->anim];
                    if (entry->event != 0 && entry->event == m_event_anim_id) {
                        set->index = 0;
                        set->timer = 0;
                    }
                    i++;
                    entry++;
                } while (i < pltt->num);
            }
        }
    }
    return 1;
}

ARM void FLDObject::setMapObjIndex(short obj, short index)
{
    if (obj < 0) {
        return;
    }
    if (obj >= m_map->obj_num) {
        return;
    }
    m_map->obj[obj].render->index = index;
    m_map->index[obj] = index;
}

ARM void FLDObject::resetMapObjAnim(int obj)
{
    if (obj <= -1) {
        return;
    }
    FLD_MAP* map = m_map;
    if (obj >= map->obj_num) {
        return;
    }
    int index = map->index[obj];
    if (index <= -1) {
        return;
    }
    if (index >= map->obj_num) {
        return;
    }
    FLD_MAP_OBJ* o = &map->obj[index];
    if (m_seq != NULL && o->seq != -1) {
        UnkFldSeq* seq = &m_seq->seq[o->seq];
        if (seq->data != -1) {
            seq->loop = seq->loop_start;
            seq->wait = seq->wait_start;
            seq->frame = 0;
        }
    }
    if (m_anim != NULL && o->anim != -1) {
        UnkFldAnim* anim = (UnkFldAnim*)m_anim->res[o->anim];
        if (anim->flag & 4) {
            return;
        }
        anim->loop = anim->loop_start;
        anim->wait = anim->wait_start;
        anim->frame = 0;
    }
}

ARM NNSG3dResTex* FLDObject::createPlttTexCopy()
{
    NNSG3dResTex* tex;
    int plttNum;
    int plttSize;
    NNSG3dResTex* buf;
    unsigned char* src;
    unsigned char* dst;
    unsigned short* data;
    unsigned char* pltt;
    int i;
    UnkFldPlttEntry* entry;
    UnkFldPlttTbl* tbl;
    tex = func_02083270(m_mdl);
    if (tex == NULL) {
        return NULL;
    }
    plttNum = tex->plttInfo.sizePltt;
    plttSize = plttNum * 8;
    buf = (NNSG3dResTex*)allocWork(tex->header.size - tex->texInfo.sizeTex * 8 - tex->tex4x4Info.sizeTex * 8 + plttNum * 8);
    buf->header.kind = tex->header.kind;
    buf->header.size = tex->header.size;
    buf->texInfo.vramKey = tex->texInfo.vramKey;
    buf->texInfo.sizeTex = tex->texInfo.sizeTex;
    buf->texInfo.ofsDict = tex->texInfo.ofsDict;
    buf->texInfo.flag = tex->texInfo.flag;
    buf->texInfo.dummy_ = tex->texInfo.dummy_;
    buf->texInfo.ofsTex = tex->texInfo.ofsTex;
    buf->tex4x4Info.vramKey = tex->tex4x4Info.vramKey;
    buf->tex4x4Info.sizeTex = tex->tex4x4Info.sizeTex;
    buf->tex4x4Info.ofsDict = tex->tex4x4Info.ofsDict;
    buf->tex4x4Info.flag = tex->tex4x4Info.flag;
    buf->tex4x4Info.dummy_ = tex->tex4x4Info.dummy_;
    buf->tex4x4Info.ofsTex = tex->tex4x4Info.ofsTex;
    buf->tex4x4Info.ofsTexPlttIdx = tex->tex4x4Info.ofsTexPlttIdx;
    buf->plttInfo.vramKey = tex->plttInfo.vramKey;
    buf->plttInfo.sizePltt = tex->plttInfo.sizePltt;
    buf->plttInfo.flag = tex->plttInfo.flag;
    buf->plttInfo.ofsDict = tex->plttInfo.ofsDict;
    buf->plttInfo.dummy_ = tex->plttInfo.dummy_;
    buf->plttInfo.ofsPlttData = tex->plttInfo.ofsPlttData;
    src = (unsigned char*)&tex->dict;
    dst = (unsigned char*)&buf->dict;
    MI_CpuCopyU8(src, dst, tex->dict.sizeDictBlk);
    MI_CpuCopyU8(src + tex->dict.sizeDictBlk, dst + tex->dict.sizeDictBlk, ((NNSG3dResDict*)(src + tex->dict.sizeDictBlk))->sizeDictBlk);
    src = (unsigned char*)tex + tex->plttInfo.ofsPlttData;
    pltt = (unsigned char*)buf + buf->texInfo.ofsTex;
    MI_CpuCopyU8(src, pltt, plttSize);
    MI_CpuCopyU8(src, pltt + plttNum * 8, plttSize);
    buf->plttInfo.ofsPlttData = pltt - (unsigned char*)buf;
    m_tex = buf;
    tbl = m_pltt;
    if (tbl != NULL) {
        i = 0;
        if (tbl->num > 0) {
            entry = tbl->entry;
            do {
                data = (unsigned short*)FLD_GetPlttDataByName(buf, entry);
                entry->pltt = (unsigned short*)((unsigned char*)buf + buf->plttInfo.ofsPlttData + *data * 8);
                i++;
                entry++;
            } while (i < tbl->num);
        }
    }
    return buf;
}

ARM void FLDObject::applyRgbRate(unsigned short* src, unsigned short* dst, int num)
{
    fx32 rateR;
    fx32 rateG;
    fx32 rateB;
    int i;
    unsigned short col;
    fx32 r;
    fx32 g;
    fx32 b;
    rateR = m_rgb_rate.x;
    rateG = m_rgb_rate.y;
    rateB = m_rgb_rate.z;
    for (i = 0; i < num; i++) {
        col = src[i];
        r = (col & 0x1f) * rateR;
        g = ((col & 0x3e0) >> 5) * rateG;
        b = ((col & 0x7c00) >> 10) * rateB;
        r = MATH_MIN(r, 0x1f000);
        g = MATH_MIN(g, 0x1f000);
        b = MATH_MIN(b, 0x1f000);
        dst[i] = (unsigned char)(r >> FX32_SHIFT) | ((unsigned char)(g >> FX32_SHIFT) << 5) | ((unsigned char)(b >> FX32_SHIFT) << 10);
    }
}

ARM void FLDObject::applyRgbRateToPltt()
{
    unsigned char* pltt;
    int size;
    unsigned char* src;
    NNSG3dResDict* dict;
    unsigned int num;
    NNSG3dResTex* tex;
    int i;
    int ofs;
    int len;
    tex = m_tex;
    pltt = (unsigned char*)tex + tex->plttInfo.ofsPlttData;
    dict = (NNSG3dResDict*)((unsigned char*)tex + tex->plttInfo.ofsDict);
    num = dict->numEntry;
    size = tex->plttInfo.sizePltt;
    src = pltt + size * 8;
    for (i = 0; i < num; i++) {
        NNSG3dResDictEntryHeader* hdr = (NNSG3dResDictEntryHeader*)((unsigned char*)dict + dict->ofsEntry);
        if (strncmp((char*)((unsigned char*)hdr + hdr->ofsName + i * sizeof(NNSG3dResName)), "tz_", 3) == 0) {
            continue;
        }
        ofs = ((NNSG3dResDictPlttData*)(hdr->data + hdr->sizeUnit * i))->offset * 8;
        if (i + 1 != num) {
            len = ((NNSG3dResDictPlttData*)(hdr->data + hdr->sizeUnit * (i + 1)))->offset * 8 - ofs;
        } else {
            len = size * 8 - ofs;
        }
        if ((unsigned int)len <= 0x200) {
            applyRgbRate((unsigned short*)(src + ofs), (unsigned short*)(pltt + ofs), len / 2);
        }
    }
}

ARM void FLDObject::transferPltt()
{
    NNSG3dResTex* tex = m_tex;
    DC_CleanRange((unsigned char*)tex + tex->plttInfo.ofsPlttData, tex->plttInfo.sizePltt * 8);
    tex->plttInfo.flag &= ~1;
    func_0207fd1c(tex, 1);
    m_flag &= ~0x80;
}

ARM void* FLDObject::allocWork(int size)
{
    void* p = m_pool;
    size = (size + 3) & ~3;
    m_pool += size;
    m_pool_rest -= size;
    return p;
}

ARM void FLDObject::freeWork(void* p)
{
}

}  // namespace race
