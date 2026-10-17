#include "ov001/town/player/TownActionWalk.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownDamageFloor.hpp"
#include "ov001/town/TownExtraMapObjManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"

#pragma thumb on

inline int FldCollision::getFloorMapUid()
{
    return floorMapUid_;
}

inline int FldCollision::getFloorSurfaceId()
{
    return floorSurfaceId_;
}

inline int FldCollision::getCollID()
{
    return id_;
}

inline int twn::TownStageManager::getSearchObjectId()
{
    return coll_.getSearchObjectId();
}

inline int twn::TownStageManager::getSearchPolyNo()
{
    return coll_.getSearchPolyNo();
}

inline int twn::TownStageManager::getFloorMapUid()
{
    return coll_.getFloorMapUid();
}

inline int twn::TownStageManager::getFloorSurfaceId()
{
    return coll_.getFloorSurfaceId();
}

inline int twn::TownStageManager::getWallCollId()
{
    return coll_.getCollID();
}

inline int twn::TownStageManager::getMapObjUid(int obj_id)
{
    return stage_.m_fld.GetMapObjUid(obj_id);
}

int twn::TownActionWalk::setup()
{
    searchObjectId_ = -1;
    ctrSurfaceId_ = -1;
    sekaijyuSurfaceId_ = -1;
    collId_ = -1;
    floorMapUid_ = 0;
    prevFloorMapUid_ = 0;
    floorSurfaceId_ = -1;
    prevFloorSurfaceId_ = -1;
    cureFloor_ = false;
    moveFlag_ = true;
    collActionFlag_ = -1;
    idoSurfaceid_ = TownStageManager::getSingleton()->getHitSurfaceIdByType(5);
    ctrSurfaceId_ = TownStageManager::getSingleton()->getHitSurfaceIdByType(0xc);
    searchObjectId_ = TownStageManager::getSingleton()->getSearchObjectId();
    searchPolyNo_ = TownStageManager::getSingleton()->getSearchPolyNo();
    floorMapUid_ = TownStageManager::getSingleton()->getFloorMapUid();
    floorSurfaceId_ = TownStageManager::getSingleton()->getFloorSurfaceId();
    collId_ = TownStageManager::getSingleton()->getWallCollId();
    return -1;
}

void twn::TownActionWalk::execute()
{
    prevFloorSurfaceId_ = floorSurfaceId_;
    prevFloorMapUid_ = floorMapUid_;
    prevCollId_ = collId_;
    collActionFlag_ = -1;
    moveFlag_ = false;
    short nowIdx = dirIdx_;
    dss::Fix32Vector3 nowPos = position_;
    TownActionCalculate::normalMove(position_, dirIdx_, TownPlayerAction::walkSpeed);
    dss::Fix32Vector3 nextPos = position_;
    nowPos.vy += TownPlayerAction::collR;
    nextPos.vy += TownPlayerAction::collR;
    if (nowPos.vx.value != nextPos.vx.value || nowPos.vz.value != nextPos.vz.value) {
        moveFlag_ = true;
    }
    TownCharacterManager::getSingleton()->characterColl(nowPos, nextPos, TownPlayerAction::townCharaR);
    collActionFlag_ = TownActionCalculate::townStageColl(nowPos, nextPos, TownPlayerAction::collR, TownPlayerAction::surfaceR, TownPlayerAction::townCharaPreR);
    if (dirIdx_ != nowIdx) {
        ctrSurfaceId_ = -1;
        idoSurfaceid_ = -1;
        searchPolyNo_ = -1;
        searchObjectId_ = -1;
        collId_ = -1;
    }
    if (nowPos != nextPos) {
        ctrSurfaceId_ = -1;
        idoSurfaceid_ = -1;
        searchPolyNo_ = -1;
        searchObjectId_ = -1;
        collId_ = -1;
        floorMapUid_ = 0;
        floorSurfaceId_ = -1;
    }
    if (ctrSurfaceId_ == -1) {
        ctrSurfaceId_ = TownStageManager::getSingleton()->getHitSurfaceIdByType(0xc);
    }
    if (idoSurfaceid_ == -1) {
        idoSurfaceid_ = TownStageManager::getSingleton()->getHitSurfaceIdByType(5);
    }
    if (searchObjectId_ == -1) {
        searchObjectId_ = TownStageManager::getSingleton()->getSearchObjectId();
        searchPolyNo_ = TownStageManager::getSingleton()->getSearchPolyNo();
    }
    if (floorMapUid_ == 0) {
        floorMapUid_ = TownStageManager::getSingleton()->getFloorMapUid();
    }
    if (floorSurfaceId_ == -1) {
        floorSurfaceId_ = TownStageManager::getSingleton()->getFloorSurfaceId();
    }
    if (collId_ == -1) {
        collId_ = TownStageManager::getSingleton()->getWallCollId();
    }
    nextPos.vy -= TownPlayerAction::collR;
    nowPos.vy -= TownPlayerAction::collR;
    TownPlayerManager::getSingleton().player_.townActionKaidan_.setPlayerFixPosition(nowPos, nextPos);
    position_ = nextPos;
    TownDamageFloor::getSingleton().checkDamageFloor(nowPos, nextPos);
}

int twn::TownActionWalk::update()
{
    if (collActionFlag_ != -1) {
        TownPlayerManager::getSingleton().player_.townActionFall_.setCollFall();
        return collActionFlag_;
    }
    int ret = TownPlayerManager::getSingleton().player_.townActionFall_.startCheck();
    if (ret != -1) {
        TownPlayerManager::getSingleton().player_.townActionFall_.setCollFall();
        return ret;
    }
    ret = TownPlayerManager::getSingleton().player_.townActionKaidan_.startCheck();
    if (ret != -1) {
        return ret;
    }
    ret = TownPlayerManager::getSingleton().player_.townActionSube_.startCheck();
    if (ret != -1) {
        return ret;
    }
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(6) != -1) {
        ret = TownPlayerManager::getSingleton().player_.townActionRope_.startCheck();
        if (ret != -1) {
            return ret;
        }
    }
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0xa) != -1) {
        ret = TownPlayerManager::getSingleton().player_.townActionShip_.startCheck();
        if (ret != -1) {
            return ret;
        }
    }
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0xa) != -1) {
        ret = TownPlayerManager::getSingleton().player_.townActionIkada_.startCheck();
        if (ret != -1) {
            return ret;
        }
    }
    if (searchObjectId_ != -1 || TownStageManager::getSingleton()->getHitSurfaceIdByType(1) != -1 || TownStageManager::getSingleton()->getHitSurfaceIdByType(7) != -1) {
        ret = TownPlayerManager::getSingleton().player_.townActionDoor_.startCheck();
        if (ret != -1) {
            return ret;
        }
    } else {
        TownPlayerManager::getSingleton().player_.townActionDoor_.objClear();
    }
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0xe) != -1) {
        ret = TownPlayerManager::getSingleton().player_.townActionIce_.startCheck();
        if (ret != -1) {
            return ret;
        }
    }
    ret = TownPlayerManager::getSingleton().player_.townActionGimmick_.startCheck(0);
    if (ret != -1) {
        return ret;
    }
    if (TownPlayerManager::getSingleton().player_.townActionTruck_.check() == true) {
        TownPlayerManager::getSingleton().player_.townActionTruck_.set();
        return 0x13;
    }
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(4) != -1) {
        if (cureFloor_ == false) {
            TownPlayerManager::getSingleton().player_.townActionKaifuku_.start();
            cureFloor_ = true;
            return 0xf;
        }
    } else {
        cureFloor_ = false;
    }
    return ret;
}

void twn::TownActionWalk::clearActionInfo()
{
    ctrSurfaceId_ = -1;
    idoSurfaceid_ = -1;
    searchPolyNo_ = -1;
    searchObjectId_ = -1;
    collId_ = -1;
}

int twn::TownActionWalk::getMapUid()
{
    int mapUid = TownStageManager::getSingleton()->getMapObjUid(searchObjectId_);
    if (mapUid != 0) {
        TownStageManager::getSingleton()->getObjectPos(searchObjectId_, searchPolyNo_, &searchObjectPos_);
        if (TownActionCalculate::directionCheckByPosition(position_, searchObjectPos_, dirIdx_, 0xc42) == true) {
            return mapUid;
        }
    } else {
        mapUid = TownExtraMapObjManager::getSingleton().checkFloorMapUid(position_);
    }
    return mapUid;
}

bool twn::TownActionWalk::isIdoMonster(int mapUid)
{
    return false;
}
