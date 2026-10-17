#include "ov001/town/player/gimmick/MapGimmickBase.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"

#pragma thumb on

inline void fld::FLDObject::CollEraseObjId(int obj_id)
{
    coll_EraseObjId(m_coll, obj_id);
}

inline void fld::FLDObject::CollResetObjId(int obj_id)
{
    coll_ResetObjId(m_coll, obj_id);
}

inline void FldStage::eraseCollision(int objectID)
{
    m_fld.CollEraseObjId(objectID);
}

inline void FldStage::resetCollision(int objectID)
{
    m_fld.CollResetObjId(objectID);
}

inline void twn::TownStageManager::eraseCollision(int objectID)
{
    stage_.eraseCollision(objectID);
}

inline void twn::TownStageManager::resetCollision(int objectID)
{
    stage_.resetCollision(objectID);
}

inline int FldCollision::getCollID()
{
    return id_;
}

inline int FldCollision::getFloorMapUid()
{
    return floorMapUid_;
}

inline int twn::TownStageManager::getWallCollId()
{
    return coll_.getCollID();
}

inline int twn::TownStageManager::getFloorMapUid()
{
    return coll_.getFloorMapUid();
}

inline int twn::TownStageManager::getCollPolyByPolyNo(int polyNo, COLL_POLY* coll)
{
    return stage_.collGetPoly(polyNo, coll);
}

twn::MapGimmickBase::MapGimmickBase()
{
    startUid_ = 0;
    endUid_ = 0;
    surfaceType_ = 0;
    state_.clear();
    flag_.clear();
}

void twn::MapGimmickBase::setup()
{
    if (state_.check(0x400) == true) {
        for (int i = startUid_; i <= endUid_; i++) {
            TownStageManager::getSingleton()->setObjectDraw(i, 0, 1);
            int objNo = TownStageManager::getSingleton()->getObjectIDfromMapUid(i);
            TownStageManager::getSingleton()->resetCollision(objNo);
        }
    }
    if (state_.check(8) == true) {
        for (int i = USE_GLOBAL_FLAG_START; i < USE_GLOBAL_FLAG_END; i++) {
            if (g_AreaFlag.check(i) == true) {
                int uid = startUid_ + (i - USE_GLOBAL_FLAG_START);
                useGlobalSetup(uid);
                int objNo = TownStageManager::getSingleton()->getObjectIDfromMapUid(uid);
                if (state_.check(0x400) == true) {
                    TownStageManager::getSingleton()->setObjectDraw(uid, 1, 1);
                }
                if (state_.check(1) && objNo != -1) {
                    TownStageManager::getSingleton()->eraseCollision(objNo);
                }
                if (state_.check(2)) {
                    TownStageManager::getSingleton()->resetCollision(objNo);
                }
            }
        }
    }
}

void twn::MapGimmickBase::useGlobalSetup(int uid)
{
}

int twn::MapGimmickBase::isStart()
{
    if (state_.check(0x10) == true) {
        int surfaceId = TownStageManager::getSingleton()->getHitSurfaceIdByType(surfaceType_);
        if (surfaceId != -1) {
            return set(startUid_ + (surfaceId & 0xfff), surfaceId);
        }
    } else {
        int polyNo = TownStageManager::getSingleton()->getWallCollId();
        int uid = 0;
        COLL_POLY poly;
        if (TownStageManager::getSingleton()->getCollPolyByPolyNo(polyNo, &poly) == true) {
            uid = poly.uid;
        }
        if (uid == 0) {
            uid = TownStageManager::getSingleton()->getFloorMapUid();
        }
        if (startUid_ <= uid && uid <= endUid_) {
            return set(uid, -1);
        }
    }
    return -1;
}

int twn::MapGimmickBase::set(int uid, int surface)
{
    if (state_.check(0x80) == true && state_.check(0x100) == true) {
        return -1;
    }
    if (state_.check(0x200) == true) {
        if (flag_.check(uid % 100) == true) {
            return -1;
        }
    }
    if (state_.check(8) == true) {
        int flagNo = uid % 100 + USE_GLOBAL_FLAG_START;
        if (flagNo >= USE_GLOBAL_FLAG_START && flagNo <= USE_GLOBAL_FLAG_END) {
            if (!g_AreaFlag.check(flagNo)) {
                g_AreaFlag.set(flagNo);
            } else {
                return -1;
            }
        }
    }
    int objNo = TownStageManager::getSingleton()->getObjectIDfromMapUid(uid);
    if (state_.check(1) && objNo != -1) {
        TownStageManager::getSingleton()->eraseCollision(objNo);
    }
    if (state_.check(2)) {
        TownStageManager::getSingleton()->resetCollision(objNo);
    }
    if (state_.check(0x20) == true) {
        TownStageManager::getSingleton()->eraseSurface(surface);
    }
    if (state_.check(4) == true) {
        setAnimation(uid);
    }
    state_.set(0x100);
    flag_.set(uid % 100);
    if (state_.check(0x40) == true) {
        return 0x14;
    }
    if (state_.check(0x800) == true) {
        TownPlayerManager::getSingleton().player_.townActionFall_.setCollFall();
        return 3;
    }
    return -1;
}

void twn::MapGimmickBase::setData(int startUid, int endUid, int surfaceType, unsigned int state)
{
    startUid_ = startUid;
    endUid_ = endUid;
    surfaceType_ = surfaceType;
    state_.set(state);
}
