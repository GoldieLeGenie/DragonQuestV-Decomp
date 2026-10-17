#pragma ipa file
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/shop/TownCurseSpotLight.hpp"
#include "ov001/town/TownExtraCollManager.hpp"
#include "ov001/town/TownExtraMapObjManager.hpp"
#include "ov001/town/TownFukubikiDraw.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "main/cmn/CommonEffectLocation.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/town/MapObjGridMove.hpp"

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline int twn::MapObjectAnimation::getMapUid()
{
    return mapUid_;
}

inline void twn::MapObjectAnimation::setMapUid(int uid)
{
    mapUid_ = uid;
}

inline void twn::MapObjectAnimation::start()
{
    playIndex_ = 0;
}

inline bool twn::MapObjectAnimation::isStop()
{
    return playIndex_ == -1;
}

inline int twn::MapObjectAnimation::getPlayNo()
{
    return animNo_[playIndex_];
}

inline int twn::TownStageManager::getCommonID(int objectID)
{
    if (objectID == -1) {
        return -1;
    }
    return stage_.m_fld.GetMapObjCommonId(objectID);
}

inline int twn::TownStageManager::IsCommonAnimationEnd(int obj_uid)
{
    return stage_.IsCommonAnimationEnd(obj_uid);
}

static float radius = 0.43f;
static dss::Fix32 unk_02165c94(1.5f);
static const char* path = "data/map";

THUMB twn::TownStageManager::TownStageManager()
{
}

THUMB twn::TownStageManager::~TownStageManager()
{
}

THUMB twn::TownStageManager* twn::TownStageManager::getSingleton()
{
    static TownStageManager m_singleton;
    return &m_singleton;
}

THUMB void twn::TownStageManager::initialize()
{
    stage_.setSepiarEnable(status::g_StageInfo.sepiaFlag_);
    coll_.animObjectCheck_ = &animObjectCheck_;
    coll_.resetEraseSurface();
    if (g_Global.getMapNameId() == 0x163) {
        renderDraw_ = 1;
        stage_.initialize(&TownSystem::getSingleton().townSystemRender_);
    } else {
        renderDraw_ = 0;
    }
    stage_.setPath(path);
    stage_.load(g_Global.getMapName());
    allocFlag_ = 1;
    stopScript_ = 0;
    TownExtraCollManager::getSingleton().setup();
    status::g_StageAttribute.setup(g_Global.getMapName(), g_Global.getMapNameId(), g_Global.getNowAreaNo());
    switch (g_Global.getMapNameId()) {
    case 0xa:
    case 0x2e:
    case 0x157:
    case 0x1df:
    case 0x1f9:
    case 0x274:
        stage_.setup(false);
        break;
    default:
        stage_.setup();
        break;
    }
    stage_.setFldColl(&coll_);
    TownCamera::getSingleton()->setLimitL(stage_.getCameraLimitL());
    TownCamera::getSingleton()->setLimitR(stage_.getCameraLimitR());
    if (!status::g_StageAttribute.isCameraIcon()) {
        TownCamera::getSingleton()->resetAngle();
    }
    for (int i = 0; i < 4; i++) {
        softEraseObjId_[i] = -1;
    }
    softEraseNum_ = 0;
    stage_.m_fld.clipping = 1;
    cmn::CommonEffectLocation::getSingleton().initialize();
    if (status::g_StageInfo.encount_ == 0) {
        for (int i = 0; i < 2; i++) {
            g_GridMove[i].initialize();
        }
    }
}

THUMB void twn::TownStageManager::terminate()
{
    cmn::CommonEffectLocation::getSingleton().terminate();
    stage_.cleanup();
    status::g_StageAttribute.cleanup();
}

THUMB void twn::TownStageManager::execute()
{
    cmn::CommonEffectLocation::getSingleton().execute();
    execSoftErase();
    execObjectAnimPlay();
    TownCurseSpotLight::getSingleton().execute();
}

THUMB void twn::TownStageManager::draw()
{
    TownFukubikiDraw::getSingleton().execute();
    if (renderDraw_ == 0) {
        stage_.draw();
    }
}

THUMB void twn::TownStageManager::pause(int flag)
{
    if (flag) {
        stage_.m_fld.m_flag |= 4;
    } else {
        stage_.m_fld.m_flag &= ~4;
    }
    cmn::CommonParticleEmitter::getSingleton()->stop_ = flag;
}

THUMB bool twn::TownStageManager::isStageExist(char* name)
{
    char fileName[128];
    dss::sprintf_s(fileName, sizeof(fileName), "%s/%s.lz", path, name);
    if (dss::g_File.isExist(fileName, dss::File::Switching) != 0) {
        return true;
    }
    return false;
}

THUMB dss::Fix32Vector3 twn::TownStageManager::compute(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 r, dss::Fix32 searchSurface, dss::Fix32 preR, dss::Fix32& height)
{
    coll_.playerIdx_ = TownPlayerManager::getSingleton().getDirection();
    return coll_.compute(oldPos, newPos, r, searchSurface, preR, height);
}

THUMB int twn::TownStageManager::getLinkMapNameId()
{
    if (getExitIndex() != -1) {
        int nameId = util::StageLink::getNameId(g_Global.getMapNameId(), getExitIndex());
        if (nameId != 0) {
            return nameId;
        }
    }
    return 0;
}

THUMB bool twn::TownStageManager::setExitPosition(dss::Fix32Vector3* pos, int index)
{
    return coll_.setExitPosition(pos, index);
}

THUMB float twn::TownStageManager::getRadius()
{
    return radius;
}

THUMB void twn::TownStageManager::setRadius(float r)
{
    radius = r;
}

THUMB dss::Fix32Vector3 twn::TownStageManager::getMapUidPos(int uid)
{
    dss::Fix32Vector3 ret;
    VecFx32 vec = stage_.getUidPos(uid);
    ret.vx.value = vec.x;
    ret.vy.value = vec.y;
    ret.vz.value = vec.z;
    return ret;
}

THUMB dss::Fix32Vector3 twn::TownStageManager::getMapUidRot(int uid)
{
    int* obj_id = stage_.GetMapUidObj(uid);
    return *(dss::Fix32Vector3*)stage_.m_fld.GetMapObjRotFX32(*obj_id);
}

THUMB void twn::TownStageManager::addMapUidPosFX32(int uid, dss::Fix32Vector3& pos)
{
    stage_.m_fld.CollAddPolyPosByMapUid(uid, (VecFx32*)&pos);
    stage_.m_fld.AddMapUidPosFX32(uid, (VecFx32*)&pos);
}

THUMB void twn::TownStageManager::setMapUidPosFX32(int uid, dss::Fix32Vector3& pos)
{
    stage_.m_fld.SetMapUidPosFX32(uid, (VecFx32*)&pos);
}

THUMB dss::Fix32Vector3 twn::TownStageManager::getRiseupPos(int uid, int type)
{
    dss::Fix32Vector3 pos;
    int* index = stage_.GetMapUidObj(uid);
    switch (type) {
    case 0x44:
        for (int i = 0; i < stage_.pool_counter; i++) {
            if (getCommonID(index[i]) == 0x13ec) {
                getObjectPos(index[i], 0, &pos);
                return pos;
            }
        }
        break;
    case 0x20:
        for (int i = 0; i < stage_.pool_counter; i++) {
            if (getCommonID(index[i]) == 0x76c) {
                getObjectPos(index[i], 0, &pos);
                return pos;
            }
        }
        break;
    case 0x11:
        for (int i = 0; i < stage_.pool_counter; i++) {
            if (getCommonID(index[i]) == 0x4b0) {
                getObjectPos(index[i], 0, &pos);
                return pos;
            }
        }
        break;
    case 0x4a:
        TownExtraMapObjManager::getSingleton().getPosition(uid, pos);
        break;
    default:
        pos = TownStageManager::getSingleton()->getMapUidPos(uid);
        break;
    }
    return pos;
}

THUMB void twn::TownStageManager::setObjectDraw(int id, int num, int flag)
{
    if (num == 1) {
        stage_.repop(id);
    }
    stage_.animLocation(id, num, flag);
}

THUMB int twn::TownStageManager::getObjectIDfromMapUid(int uid)
{
    int* id = stage_.GetMapUidObj(uid);
    return *id;
}

THUMB void twn::TownStageManager::rotObjectUid(int uid, short angle)
{
    dss::Fix32Vector3 rot;
    rot *= 0;
    rot.vy.value = angle;
    stage_.m_fld.SetMapUidRotFX32(uid, (VecFx32*)&rot);
}

THUMB void twn::TownStageManager::eraseSurface(int id)
{
    coll_EraseSurface(stage_.m_fld.m_coll, id);
}

THUMB void twn::TownStageManager::resetSurface(int id)
{
    coll_ResetSurface(stage_.m_fld.m_coll, id);
}

THUMB bool twn::TownStageManager::addBoxCollision(dss::Fix32Vector3& center, short dir, dss::Fix32Vector3& vec, int& extraId)
{
    COLL_ADD_RESULT_TYPE ret = stage_.addBoxCollistion(center, dir, vec, extraId, allocFlag_);
    switch (ret) {
    case MEMORY_ALLOC_ERROR:
    case ALLOC_MAX_OVER_ERROR:
    case NUM_MAX_OVER_ERROR:
        return false;
    }
    return true;
}

THUMB dss::Fix32 twn::TownStageManager::getDiagonalLength(int polyNo)
{
    dss::Fix32 ret(0.0f);
    COLL_POLY coll;
    dss::Fix32Vector3 vec, pos1, pos2;
    if (stage_.collGetPoly(polyNo, &coll) != -1) {
        pos1 = FldStage::getFx32Vector3(coll.bbox[0]);
        pos2 = FldStage::getFx32Vector3(coll.bbox[1]);
        vec = pos2 - pos1;
        ret = vec.length();
    }
    return ret;
}

THUMB dss::Fix32Vector3 twn::TownStageManager::getSurfaceDir(int surfaceId)
{
    dss::Fix32Vector3 retVec;
    COLL_POLY coll;
    int polyNo = coll_GetPolyNoBySurface(stage_.m_fld.m_coll, surfaceId, 0);
    stage_.collGetPoly(polyNo, &coll);
    retVec = FldStage::getFx32Vector3(coll.normal);
    return retVec;
}

THUMB bool twn::TownStageManager::checkCrossPolygon(dss::Fix32Vector3 pos0, dss::Fix32Vector3 pos1, int polyNo)
{
    VecFx32 tpos0, tpos1;
    tpos0 = FldStage::getVecFx32(pos0);
    tpos1 = FldStage::getVecFx32(pos1);
    return coll_.checkCrossPolygon(tpos0, tpos1, polyNo);
}

THUMB int twn::TownStageManager::checkCrossNumCheckUnder(dss::Fix32Vector3& start, dss::Fix32Vector3& end, bool flag)
{
    VecFx32 tpos0, tpos1;
    tpos0 = FldStage::getVecFx32(start);
    tpos1 = FldStage::getVecFx32(end);
    return coll_.checkCrossNumCheckUnder(tpos0, tpos1, flag);
}

THUMB int twn::TownStageManager::checkCrossNum(dss::Fix32Vector3& start, dss::Fix32Vector3& end, bool flag)
{
    VecFx32 tpos0, tpos1;
    tpos0 = FldStage::getVecFx32(start);
    tpos1 = FldStage::getVecFx32(end);
    return coll_.checkCrossNum(tpos0, tpos1, flag);
}

THUMB int twn::TownStageManager::checkCrossNumEraseSurface(dss::Fix32Vector3& start, dss::Fix32Vector3& end, int mask, int flag, int& polyNo)
{
    VecFx32 tpos0, tpos1;
    tpos0 = FldStage::getVecFx32(start);
    tpos1 = FldStage::getVecFx32(end);
    return coll_.checkCrossNumEraseSurface(tpos0, tpos1, mask, flag, polyNo);
}

THUMB bool twn::TownStageManager::getSearchPolyDirection(dss::Fix32Vector3& dir)
{
    return getPolyDirection(dir, coll_.getSearchPolyNo());
}

THUMB bool twn::TownStageManager::getPolyDirection(dss::Fix32Vector3& dir, int polyNo)
{
    COLL_POLY coll;
    if (TownStageManager::getSingleton()->stage_.collGetPoly(polyNo, &coll) == -1) {
        return false;
    }
    dir.vx.value = coll.normal.x;
    dir.vy.value = coll.normal.y;
    dir.vz.value = coll.normal.z;
    return true;
}

THUMB int twn::TownStageManager::getHitSurfaceIdByType(int type)
{
    return coll_.getSurfaceByType(type);
}

THUMB dss::Fix32Vector3 twn::TownStageManager::getHitSurfaceDirByType(int type)
{
    dss::Fix32Vector3 retVec;
    retVec.set(0, 0, 0);
    int polyNo = coll_.surfacePolyNo_[type];
    getPolyDirection(retVec, polyNo);
    return retVec;
}

THUMB void twn::TownStageManager::setSoftErase(int objectId)
{
    if (softEraseNum_ < 4) {
        softEraseObjId_[softEraseNum_] = objectId;
        softEraseNum_++;
    }
}

THUMB void twn::TownStageManager::execSoftErase()
{
    for (int i = 0; i < 4; i++) {
        if (softEraseObjId_[i] != -1) {
            int alpha = stage_.m_fld.GetMapObjAlpha(softEraseObjId_[i]) - 2;
            if (alpha <= 0) {
                int uid = stage_.m_fld.GetMapObjUid(softEraseObjId_[i]);
                stage_.eraseObject(uid, 1);
                softEraseObjId_[i] = -1;
                softEraseNum_--;
            } else {
                stage_.setAlpha(softEraseObjId_[i], alpha);
            }
        }
    }
}

THUMB bool twn::TownStageManager::isEndSoftErase(int objectId)
{
    bool ret = true;
    for (int i = 0; i < 4; i++) {
        if (objectId == softEraseObjId_[i]) {
            ret = false;
        }
    }
    return ret;
}

THUMB dss::Fix32Vector3 twn::TownStageManager::getHitSurfacePosByType(int type)
{
    dss::Fix32Vector3 retVec;
    retVec.set(0, 0, 0);
    int polyNo = coll_.surfacePolyNo_[type];
    stage_.collGetPolygonPos(polyNo, &retVec);
    return retVec;
}

THUMB int twn::TownStageManager::getExitIndex()
{
    int polyNo;
    int exitId = -1;
    polyNo = coll_.getSurfaceByType(5);
    if (polyNo != exitId) {
        return polyNo;
    }
    polyNo = coll_.getSurfaceByType(1);
    if (polyNo != -1) {
        exitId = coll_.surfacePolyNo_[1];
    } else {
        polyNo = coll_.getSurfaceByType(7);
        if (polyNo != -1) {
            exitId = coll_.surfacePolyNo_[7];
        } else {
            polyNo = coll_.getSurfaceByType(0x10);
            if (polyNo != exitId) {
                return polyNo;
            }
        }
    }
    if (polyNo == -1) {
        return -1;
    }
    dss::Fix32Vector3 playerPos(TownPlayerManager::getSingleton().getPosition());
    if (isPolyFacePosition(exitId, playerPos) != 1) {
        polyNo = -1;
    }
    return polyNo;
}

THUMB bool twn::TownStageManager::isPolyFacePosition(int polyNo, dss::Fix32Vector3& playerPos)
{
    dss::Fix32Vector3 tPlayerPos(playerPos);
    COLL_POLY coll;
    if (stage_.collGetPoly(polyNo, &coll) == 1) {
        if (coll.normal.y != 0) {
            return true;
        }
        dss::Fix32Vector3 p1 = FldStage::getFx32Vector3(coll.bbox[0]);
        dss::Fix32Vector3 p2 = FldStage::getFx32Vector3(coll.bbox[1]);
        p1.vy = p2.vy = 0L;
        dss::Fix32Vector3 vec = p1 - p2;
        if (vec.lengthsq().value > 0x1000) {
            return true;
        }
        tPlayerPos.vy = 0L;
        if ((tPlayerPos - p1) * (p1 - p2) > 0L) {
            return false;
        }
        if ((tPlayerPos - p2) * (p2 - p1) > 0L) {
            return false;
        }
    }
    return true;
}

THUMB bool twn::TownStageManager::isPolyFacePosition(int polyNo, dss::Fix32Vector3& playerPos, dss::Fix32 len)
{
    dss::Fix32Vector3 tPlayerPos(playerPos);
    COLL_POLY coll;
    if (stage_.collGetPoly(polyNo, &coll) == 1) {
        dss::Fix32Vector3 p1 = FldStage::getFx32Vector3(coll.bbox[0]);
        dss::Fix32Vector3 p2 = FldStage::getFx32Vector3(coll.bbox[1]);
        p1.vy = p2.vy = 0L;
        dss::Fix32Vector3 vec = p1 - p2;
        tPlayerPos.vy = 0L;
        if ((tPlayerPos - p1) * (p1 - p2) > 0L) {
            return false;
        }
        if ((tPlayerPos - p2) * (p2 - p1) > 0L) {
            return false;
        }
        dss::Fix32Vector3 normal = FldStage::getFx32Vector3(coll.normal);
        if ((tPlayerPos - p1) * normal > len) {
            return false;
        }
        if ((tPlayerPos - p1) * normal < 0L) {
            return false;
        }
        return true;
    }
    return false;
}

THUMB bool twn::TownStageManager::getObjectPos(int objectID, int polyNo, dss::Fix32Vector3* pos)
{
    return coll_.getObjectPos(objectID, polyNo, pos);
}

THUMB void twn::TownStageManager::addMovePosByObjNo(int objNo, dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos)
{
    dss::Fix32Vector3 move = newPos - oldPos;
    stage_.addMovePosByObjNo(objNo, move);
}

THUMB int twn::TownStageManager::getCrossPolygonOtherSurface(dss::Fix32Vector3& start, dss::Fix32Vector3& end, int* surface, int count, int& polyNo, dss::Fix32* dist, int all)
{
    return stage_.getCrossPolygonOtherSurface(start, end, surface, count, polyNo, dist, all);
}

THUMB void twn::TownStageManager::collEraseMapUid(int id)
{
    TownPlayerManager::getSingleton().searchMapUid_ = 0;
    TownPlayerManager::getSingleton().player_.townActionWalk_.searchObjectId_ = -1;
    stage_.m_fld.CollEraseMapUid(id);
}

THUMB void twn::TownStageManager::startMapObjAnimRegist(int uid)
{
    for (int i = 0; i < ANIM_OBJ_COUNT; i++) {
        if (uid == mapObjectAnim_[i].getMapUid()) {
            mapObjectAnim_[i].start();
            setObjectDraw(uid, mapObjectAnim_[i].getPlayNo(), 1);
        }
    }
}

THUMB bool twn::TownStageManager::setMapObjAnimRegist(int uid, int no)
{
    bool check = false;
    int index = 0;
    for (int i = 0; i < ANIM_OBJ_COUNT; i++) {
        if (uid == mapObjectAnim_[i].getMapUid()) {
            return mapObjectAnim_[i].registAnimation(no);
        }
        if (mapObjectAnim_[i].getMapUid() == 0 && check == false) {
            check = true;
            index = i;
        }
    }
    if (check == true) {
        mapObjectAnim_[index].clear();
        mapObjectAnim_[index].setMapUid(uid);
        mapObjectAnim_[index].registAnimation(no);
        return true;
    }
    return false;
}

THUMB void twn::TownStageManager::execObjectAnimPlay()
{
    for (int i = 0; i < ANIM_OBJ_COUNT; i++) {
        if (mapObjectAnim_[i].getMapUid() != 0 && !mapObjectAnim_[i].isStop()) {
            int objId = getObjectIDfromMapUid(mapObjectAnim_[i].getMapUid());
            if (objId == -1) {
                mapObjectAnim_[i].clear();
            } else if (IsCommonAnimationEnd(mapObjectAnim_[i].getMapUid())) {
                if (mapObjectAnim_[i].isNext() == true) {
                    setObjectDraw(objId, mapObjectAnim_[i].getNextPlayNo(), 0);
                } else {
                    mapObjectAnim_[i].clear();
                }
            }
        }
    }
}

THUMB bool twn::UnkTownAnimObjectCheck::isAnimObject(fld::FLDObject* fld, int objectId)
{
    switch (fld->GetMapObjCommonId(objectId)) {
    case 0x1130:
    case 0x1131:
    case 0x1132:
    case 0x1133:
    case 0x1134:
    case 0x1135:
    case 0x1136:
    case 0x1137:
    case 0x1138:
    case 0x1139:
    case 0x113a:
    case 0x113b:
    case 0x113c:
        return true;
    }
    return false;
}
