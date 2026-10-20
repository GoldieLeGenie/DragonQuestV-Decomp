#pragma ipa file
#include "main/fld/FldStage.hpp"
#include "main/fld/FldCollision.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/UnkArchive.hpp"
#include "main/dss/UnkMatrix43.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkModelMember.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/data/FileLoader.hpp"
#include "main/object/DSSAObject.hpp"
#include "nitro/fx.hpp"
#include "nitro/g3.hpp"
#include "nitro/fx/fx_trig.h"
#include "nnsys/fnd.hpp"
#include "nnsys/g3d.hpp"

#pragma thumb on

inline UnkFileDataObject::UnkFileDataObject()
{
}

inline UnkFileDataObject::~UnkFileDataObject()
{
}

inline int fld::FLDObject::CollCrossCheck(VecFx32* pos0, VecFx32* pos1, int start, fx32* len)
{
    if (start == 0) {
        m_cross_pos = *pos0;
        func_0208a1dc(pos1, pos0, &m_cross_dir);
        func_0208a330(&m_cross_dir, &m_cross_dir);
        m_cross_len = func_0208a5d0(pos0, pos1);
    }
    return coll_CrossCheck(m_coll, &m_cross_pos, &m_cross_dir, m_cross_len, start, len);
}

inline void fld::FLDObject::CollEraseObjId(int obj_id)
{
    coll_EraseObjId(m_coll, obj_id);
}

inline void fld::FLDObject::CollResetObjId(int obj_id)
{
    coll_ResetObjId(m_coll, obj_id);
}

inline int fld::FLDObject::CollGetPoly(int poly_no, COLL_POLY* poly)
{
    return coll_GetPoly(m_coll, poly_no, poly);
}

inline int fld::FLDObject::CollGetSurface(int poly_no)
{
    return coll_GetSurface(m_coll, poly_no);
}

inline int fld::FLDObject::CollGetObjId(int poly_no)
{
    return coll_GetObjId(m_coll, poly_no);
}

inline int fld::FLDObject::CollGetPolyNoByMapObj(int obj_id, int start)
{
    return coll_GetPolyNoByMapObj(m_coll, obj_id, start);
}

inline COLL_ADD_RESULT_TYPE fld::FLDObject::addExtraPolyColl(int extraNo, int polyNo, COLL_POLY* new_poly, int& allocFlag)
{
    return coll_AddCollPoly2(extraNo, polyNo, m_coll, new_poly, &m_allocator, allocFlag);
}

static void unkfunc_0206a99c();

static int s_drawTick;

FldStage::FldStage() : flag_(0)
{
    collisionFlag_ = 0;
    collisionDrawFlag_ = 0;
    unk_8b4 = 1;
    unk_8b8 = 1;
    unk_8bc = 1;
    extraObjectNum_ = 0;
    scale_.set(1, 1, 1);
    m_render = NULL;
}

FldStage::~FldStage()
{
}

void FldStage::initialize(Render* render)
{
    m_render = render;
}

void FldStage::terminate()
{
}

void FldStage::setup()
{
    setup(true);
}

void FldStage::setup(bool flag)
{
    if (m_render) {
        setRender(m_render);
    }
    m_anim.setModelFile(m_model.getAddr());
    void* model = m_model.getAddr();
    void* texture = m_texture.getAddr();
    void* coll = m_coll.getAddr();
    m_fld.Setup(model, texture, coll, (int)*getHeap0(&data_020fd24c));
    setSepiarExecute();
    if (flag) {
        unkfunc_0206a898();
    }
    dss::Fix32Vector3 scale(1, 1, 1);
    setPaletteRgbRate(0, scale);
    int color = m_fld.m_scene->backColor;
    setBackgroundColor((color & 0xff) >> 3, ((color >> 8) & 0xff) >> 3, ((color >> 16) & 0xff) >> 3);
    if (m_fld.m_coll) {
        extraObjectNum_ = 0;
    }
}

void FldStage::cleanup()
{
    setBackgroundColor(0, 0, 0);
    removeRender();
    m_fld.Final();
    m_model.cleanup();
    m_texture.cleanup();
    m_coll.cleanup();
    m_anim.release();
    m_data.cleanup();
}

void FldStage::setPath(const char* path)
{
    dss::sprintf(path_, "%s", path);
}

bool FldStage::isExist(char* name)
{
    char ss[0x80];
    dss::sprintf(ss, "%s/%s.lz", path_, name);
    return dss::g_File.isExist(ss, dss::File::Switching) != false;
}

void FldStage::load(const char* name)
{
    char ss[0x80];
    dss::sprintf_s(ss, sizeof(ss), "%s/%s.lz", path_, name);
    m_data.setup(ss, 1, 1);
    m_texture.setup(getArchiveFile(m_data.getAddr(), 0));
    if (getArchiveFileSize(m_data.getAddr(), 1)) {
        m_coll.setup(getArchiveFile(m_data.getAddr(), 1));
    }
    m_model.setup(getArchiveFile(m_data.getAddr(), 2));
    if (m_coll.getAddr()) {
        collisionFlag_ = 1;
    }
}

void FldStage::unkfunc_0206a898()
{
    NNSG3dResFileHeader* header = (NNSG3dResFileHeader*)m_model.getAddr();
    NNSG3dResTex* tex = func_02083270(header);
    unsigned int size = tex->header.size;
    func_0207e7f4(*getAppHeap(&data_020fd24c), m_data.getAddr(), m_data.getSize() - size);
    header->dataBlocks = 1;
    header->fileSize = (unsigned char*)tex - (unsigned char*)header;
}

void FldStage::setSepiarEnable(int flag)
{
    if (flag) {
        flag_ |= 1;
    } else {
        flag_ &= ~1;
    }
}

void FldStage::setSepiarExecute()
{
    if (flag_ & 1) {
        applyModelPaletteSepia(getLastModelTexture());
        m_fld.SetSepia();
        m_fld.unkfunc_02061798(0x7fff);
        flag_ &= ~1;
    }
}

void FldStage::draw()
{
    s_drawTick = getTick();
    unkfunc_0206a99c();
    m_fld.unkfunc_0205f404();
    unkfunc_0206a99c();
    if (collisionDrawFlag_ == 0) {
        func_0208032c((VecFx32*)&scale_);
        m_fld.unkfunc_0205f85c();
    }
    unkfunc_0206a99c();
    s_drawTick = getTick() - s_drawTick;
}

void FldStage::resettingTexture()
{
    m_anim.reloadTextures();
}

int FldStage::getDrawTick()
{
    return s_drawTick;
}

static void unkfunc_0206a99c()
{
    VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
    VecFx32 trans = { 0, 0, 0 };
    MtxFx33 rot;
    func_02088970(&rot);
    func_0208032c(&scale);
    func_02070360(&rot, &data_02124bb4.prmBaseRot);
    data_02124bb4.flag &= ~0xa4;
    func_02080308((dss::Fix32Vector3*)&trans);
    func_020802dc();
}

dss::Fix32 FldStage::getCameraLimitR()
{
    return dss::Fix32(m_fld.m_scene->cameraLimitR);
}

dss::Fix32 FldStage::getCameraLimitL()
{
    return dss::Fix32(m_fld.m_scene->cameraLimitL);
}

void FldStage::eraseObject(int id, int flag)
{
    m_fld.CollEraseMapUid(id);
    m_fld.SetMapUidOnOff(id, flag);
}

void FldStage::setMapUidOnOff(int id, int flag)
{
    m_fld.SetMapUidOnOff(id, flag);
}

int FldStage::eventAnim(int event, int objID)
{
    if (objID == 0) {
        m_fld.unkfunc_0206092c(event);
        return 1;
    }
    if (m_fld.getMapObjAnimFrame(objID) == m_fld.getMapObjAnimFrameMax(objID)) {
        m_fld.unkfunc_0206092c(event);
        return 1;
    }
    return 0;
}

void FldStage::repop(int uid)
{
    int* id = GetMapUidObj(uid);
    for (int i = 0; i < pool_counter; i++) {
        m_fld.SetMapObjOnOff(id[i], 0);
        m_fld.SetCommonAnimation(id[i], 0);
        m_fld.CollResetObjId(id[i]);
    }
}

void FldStage::commonAnim(int objectId, int num)
{
    m_fld.SetCommonAnimation(objectId, num);
}

void FldStage::animLocation(int uid, int num, int flag)
{
    if (flag == 1) {
        int* id = GetMapUidObj(uid);
        for (int i = 0; i < pool_counter; i++) {
            setAnimLocation(id[i], num);
        }
    } else {
        setAnimLocation(uid, num);
    }
}

void FldStage::setAnimLocation(int id, int num)
{
    if (m_fld.IsCommonAnimationEnd(id) == 1) {
        m_fld.SetCommonAnimation(id, 0);
        m_fld.CollResetObjId(id);
    }
    if (num == 0) {
        m_fld.CollEraseObjId(id);
        m_fld.SetMapObjOnOff(id, 1);
        return;
    }
    if (m_fld.GetCommonAnimationNum(id) < num) {
        return;
    }
    if (num == m_fld.GetCommonAnimationNo(id)) {
        return;
    }
    m_fld.SetCommonAnimation(id, num);
}

void FldStage::setAlpha(int id, int alpha)
{
    m_fld.SetMapObjAlpha(id, alpha, 0);
}

void FldStage::setFldColl(FldCollision* coll)
{
    coll->collisionFlag_ = &collisionFlag_;
    coll->g_fld = &m_fld;
    coll->coll_ = &m_coll;
}

bool FldStage::collGetPolygonPos(int polygonNo, dss::Fix32Vector3* center)
{
    COLL_POLY collPoly;
    *center *= 0;
    if (!m_fld.CollGetPoly(polygonNo, &collPoly)) {
        return false;
    }
    if (collPoly.type & 1) {
        for (int i = 0; i < 4; i++) {
            center->vx.value += collPoly.vertex[i].x;
            center->vy.value += collPoly.vertex[i].y;
            center->vz.value += collPoly.vertex[i].z;
        }
        *center /= 4;
    } else {
        for (int i = 0; i < 3; i++) {
            center->vx.value += collPoly.vertex[i].x;
            center->vy.value += collPoly.vertex[i].y;
            center->vz.value += collPoly.vertex[i].z;
        }
        *center /= 3;
    }
    return true;
}

void FldStage::addMapGroupPosFX32(int gid, dss::Fix32Vector3& pos)
{
    for (int i = 0; i < m_fld.m_map->obj_num; i++) {
        fld::FLD_MAP_OBJ* obj = m_fld.GetMapObjPtr(i);
        if (obj && (obj->flag & gid)) {
            m_fld.AddMapObjPosFX32(i, (VecFx32*)&pos);
        }
    }
}

void FldStage::addMapGroupRotFX32(int gid, dss::Fix32Vector3& pos)
{
    for (int i = 0; i < m_fld.m_map->obj_num; i++) {
        fld::FLD_MAP_OBJ* obj = m_fld.GetMapObjPtr(i);
        if (obj && (obj->flag & gid)) {
            m_fld.AddMapObjRotFX32(i, (VecFx32*)&pos);
        }
    }
}

int FldStage::collCrossCheckPoly(dss::Fix32Vector3& ar_pos1, dss::Fix32Vector3& ar_pos2, dss::Fix32* ar_retLength, int surfaceFlag)
{
    VecFx32 pos1;
    pos1.x = ar_pos1.vx.value;
    pos1.y = ar_pos1.vy.value;
    pos1.z = ar_pos1.vz.value;
    VecFx32 pos2;
    pos2.x = ar_pos2.vx.value;
    pos2.y = ar_pos2.vy.value;
    pos2.z = ar_pos2.vz.value;
    int No = 0;
    int ret = -1;
    fx32 retLength = 0x7ffffff;
    fx32 tpl;
    while ((No = m_fld.CollCrossCheck(&pos1, &pos2, No, &tpl)) != -1) {
        if (m_fld.CollGetSurface(No) != -1 && !surfaceFlag) {
            No++;
            continue;
        }
        tpl = dss::abs<long>(tpl);
        if (tpl < retLength) {
            ret = No;
            retLength = tpl;
        }
        No++;
    }
    ar_retLength->value = retLength;
    return ret;
}

int FldStage::collGetPoly(int polyNo, COLL_POLY* coll)
{
    return m_fld.CollGetPoly(polyNo, coll);
}

void FldStage::setPosByObjectID(int objID, dss::Fix32Vector3& pos)
{
    m_fld.SetMapObjPosFX32(objID, (VecFx32*)&pos);
}

dss::Fix32Vector3 FldStage::getFx32Vector3(const VecFx32& vec)
{
    dss::Fix32Vector3 ret;
    ret.vx.value = vec.x;
    ret.vy.value = vec.y;
    ret.vz.value = vec.z;
    return ret;
}

VecFx32 FldStage::getVecFx32(const dss::Fix32Vector3& vec)
{
    VecFx32 ret;
    ret.x = vec.vx.value;
    ret.y = vec.vy.value;
    ret.z = vec.vz.value;
    return ret;
}

bool FldStage::getObjectIn(int objectId, dss::Fix32Vector3& pos)
{
    int no;
    bool ret = false;
    VecFx32 tpos = getVecFx32(pos);
    fx32 minX = 0x7fffffff;
    fx32 minZ = 0x7fffffff;
    fx32 maxX = 0x80000000;
    fx32 maxZ = 0x80000000;
    no = m_fld.CollGetPolyNoByMapObj(objectId, 0);
    if (no != -1) do {
        ret = true;
        COLL_POLY coll;
        m_fld.CollGetPoly(no, &coll);
        fx32 x1 = coll.bbox[0].x <= coll.bbox[1].x ? coll.bbox[0].x : coll.bbox[1].x;
        fx32 x2 = coll.bbox[0].x >= coll.bbox[1].x ? coll.bbox[0].x : coll.bbox[1].x;
        fx32 z1 = coll.bbox[0].z <= coll.bbox[1].z ? coll.bbox[0].z : coll.bbox[1].z;
        fx32 z2 = coll.bbox[0].z >= coll.bbox[1].z ? coll.bbox[0].z : coll.bbox[1].z;
        if (x1 < minX) {
            minX = x1;
        }
        if (x2 > maxX) {
            maxX = x2;
        }
        if (z1 < minZ) {
            minZ = z1;
        }
        if (z2 > maxZ) {
            maxZ = z2;
        }
        no = m_fld.CollGetPolyNoByMapObj(objectId, no + 1);
    } while (no != -1);
    if (ret == true) {
        if (tpos.x < minX || tpos.x > maxX || tpos.z < minZ || tpos.z > maxZ) {
            ret = false;
        }
    }
    return ret;
}

int FldStage::getObjWallPolyNo(int objNo, int no)
{
    int tNo = m_fld.CollGetPolyNoByMapObj(objNo, 0);
    if (tNo == -1) {
        return -1;
    }
    int retNo = tNo + no;
    if (objNo != m_fld.CollGetObjId(retNo)) {
        retNo = -1;
    }
    return retNo;
}

short FldStage::getObjectRotIdxY(int objectId)
{
    return m_fld.GetMapObjRotFX32(objectId)->y;
}

VecFx32 FldStage::getUidPos(int obj_uid)
{
    VecFx32 pos;
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    fld::FLD_MAP* m_map = m_fld.m_map;
    int* obj_id = GetMapUidObj(obj_uid);
    for (int i = 0; i < pool_counter; i++) {
        pos.x += m_map->obj[obj_id[i]].pos.x;
        pos.y += m_map->obj[obj_id[i]].pos.y;
        pos.z += m_map->obj[obj_id[i]].pos.z;
    }
    pos.x /= pool_counter;
    pos.y /= pool_counter;
    pos.z /= pool_counter;
    return pos;
}

int* FldStage::GetMapUidObj(int obj_uid)
{
    pool_counter = 0;
    fld::FLD_MAP* map = m_fld.m_map;
    for (int i = 0; i < 128; i++) {
        obj_index[i] = -1;
    }
    if (obj_uid <= 0) {
        return obj_index;
    }
    for (int i = 0; i < map->obj_num; i++) {
        short n = map->index[i];
        if (n >= 0 && obj_uid == map->obj[n].uid) {
            obj_index[pool_counter] = i;
            pool_counter++;
        }
    }
    return obj_index;
}

int FldStage::IsCommonAnimationEnd(int obj_uid)
{
    int* obj_id = GetMapUidObj(obj_uid);
    for (int i = 0; i < pool_counter; i++) {
        if (m_fld.IsCommonAnimationEnd(obj_id[i]) == 0) {
            return false;
        }
    }
    return true;
}

int unkfunc_0206b048(dss::Fix32Vector3* pos, dss::Fix32Vector3* rot, dss::Fix32Vector3* scale, GXBoxTestParam* box, dss::Fix32* rate)
{
    int result;
    G3_PushMtx();
    G3_Translate(pos->vx.value, pos->vy.value, pos->vz.value);
    func_020761a0(FX_SinIdx((unsigned short)rot->vy.value), FX_CosIdx((unsigned short)rot->vy.value));
    func_02076164(FX_SinIdx((unsigned short)rot->vx.value), FX_CosIdx((unsigned short)rot->vx.value));
    func_020761dc(FX_SinIdx((unsigned short)rot->vz.value), FX_CosIdx((unsigned short)rot->vz.value));
    G3_Scale(scale->vx.value, scale->vy.value, scale->vz.value);
    G3_Scale(rate->value, rate->value, rate->value);
    REG_GFX_FIFO_BOX_TEST = ((unsigned int*)box)[0];
    REG_GFX_FIFO_BOX_TEST = ((unsigned int*)box)[1];
    REG_GFX_FIFO_BOX_TEST = ((unsigned int*)box)[2];
    while (func_02075ff4(&result)) {
    }
    G3_PopMtx(1);
    return result;
}

COLL_ADD_RESULT_TYPE FldStage::addBoxCollistion(dss::Fix32Vector3& center, short dir, dss::Fix32Vector3& vec, int& extraId, int& allocFlag)
{
    COLL_ADD_RESULT_TYPE ret;
    COLL_POLY coll;
    if (extraObjectNum_ == 0) {
        extraObjectNum_ = m_fld.m_map->uid_num + 100;
    }
    short objectId;
    if (extraId == -1) {
        objectId = extraObjectNum_;
    } else {
        objectId = extraId;
    }
    dss::UnkMatrix43 matRot;
    matRot.setRotY(dir);
    dss::Fix32Vector3 vertexVec[4];
    dss::Fix32Vector3 normal;
    dss::Fix32Vector3 tempPos;

    coll.obj_id = objectId;
    coll.type |= 0x101;
    coll.id = 0;
    coll.flag = 0;

    vertexVec[0].vy = vertexVec[3].vy = vec.vy * -1;
    vertexVec[2].vy = vertexVec[1].vy = vec.vy;
    for (int i = 0; i < 4; i++) {
        vertexVec[i].vx = vec.vx * -1;
        vertexVec[i].vz = vec.vz;
    }
    vertexVec[3].vz *= -1;
    vertexVec[2].vz *= -1;
    normal.set(-FX32_ONE, 0, 0);
    normal = matRot * normal;
    coll.normal = getVecFx32(normal);
    for (int i = 0; i < 4; i++) {
        tempPos = center + matRot * vertexVec[i];
        coll.vertex[i] = getVecFx32(tempPos);
    }
    ret = m_fld.addExtraPolyColl(extraId, 0, &coll, allocFlag);
    if (ret != RESULT_OK) {
        return ret;
    }

    for (int i = 0; i < 4; i++) {
        vertexVec[i].vx = vec.vx;
        vertexVec[i].vz = vec.vz * -1;
    }
    vertexVec[0].vx *= -1;
    vertexVec[1].vx *= -1;
    normal.set(0, 0, -FX32_ONE);
    normal = matRot * normal;
    coll.normal = getVecFx32(normal);
    for (int i = 0; i < 4; i++) {
        tempPos = center + matRot * vertexVec[i];
        coll.vertex[i] = getVecFx32(tempPos);
    }
    ret = m_fld.addExtraPolyColl(extraId, 1, &coll, allocFlag);
    if (ret != RESULT_OK) {
        return ret;
    }

    for (int i = 0; i < 4; i++) {
        vertexVec[i].vx = vec.vx;
        vertexVec[i].vz = vec.vz;
    }
    vertexVec[0].vz *= -1;
    vertexVec[1].vz *= -1;
    normal.set(FX32_ONE, 0, 0);
    normal = matRot * normal;
    coll.normal = getVecFx32(normal);
    for (int i = 0; i < 4; i++) {
        tempPos = center + matRot * vertexVec[i];
        coll.vertex[i] = getVecFx32(tempPos);
    }
    ret = m_fld.addExtraPolyColl(extraId, 2, &coll, allocFlag);
    if (ret != RESULT_OK) {
        return ret;
    }

    for (int i = 0; i < 4; i++) {
        vertexVec[i].vx = vec.vx;
        vertexVec[i].vz = vec.vz;
    }
    vertexVec[3].vx *= -1;
    vertexVec[2].vx *= -1;
    normal.set(0, 0, FX32_ONE);
    normal = matRot * normal;
    coll.normal = getVecFx32(normal);
    for (int i = 0; i < 4; i++) {
        tempPos = center + matRot * vertexVec[i];
        coll.vertex[i] = getVecFx32(tempPos);
    }
    ret = m_fld.addExtraPolyColl(extraId, 3, &coll, allocFlag);
    if (ret != RESULT_OK) {
        return ret;
    }

    extraObjectNum_++;
    extraId = objectId;
    return RESULT_OK;
}

void FldStage::addMovePosByObjNo(int objNo, dss::Fix32Vector3& vec)
{
    VecFx32 tvec = getVecFx32(vec);
    m_fld.CollAddPolyPosByMapObj(objNo, &tvec);
}

int FldStage::getCrossPolygonOtherSurface(dss::Fix32Vector3& pos0, dss::Fix32Vector3& pos1, int* surface, int count, int& retPolyNo, dss::Fix32* length, int floor)
{
    int num = 0;
    VecFx32 start = getVecFx32(pos0);
    VecFx32 end = getVecFx32(pos1);
    int No = 0;
    int retPoly = -1;
    fx32 retLength = 0x7ffffff;
    fx32 tpl;
    int floorNum = m_fld.m_coll->floor_poly_size;
    while ((No = m_fld.CollCrossCheck(&start, &end, No, &tpl)) != -1) {
        if (!floor && No < floorNum) {
            No++;
            continue;
        }
        int ret = false;
        for (int i = 0; i < count; i++) {
            int surfaceId = m_fld.CollGetSurface(No);
            if ((surfaceId & 0xffff0000) == surface[i]) {
                ret = true;
            }
        }
        if (ret == true) {
            No++;
            continue;
        }
        if (tpl < 0) {
            No++;
            continue;
        }
        tpl = dss::abs<long>(tpl);
        if (tpl < retLength) {
            retPoly = No;
            retLength = tpl;
        }
        num++;
        No++;
    }
    retPolyNo = retPoly;
    if (length) {
        length->value = retLength;
    }
    return num;
}
