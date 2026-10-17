#include "ov001/town/player/TownActionIkada.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownDamageFloor.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/global/Global.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/status/StageInfo.hpp"

#pragma thumb on

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline cmn::PARTY_RIDE_ON_TYPE cmn::CommonPartyInfo::getRideOn()
{
    return rideOnType_;
}

inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type)
{
    rideOnType_ = type;
}

inline int cmn::CommonPartyInfo::isPrevLocation()
{
    return prevLocation_;
}

inline int status::StageInfo::getEncountFlag()
{
    return encount_;
}

inline void twn::TownStageManager::eraseObject(int uid, int flag)
{
    stage_.eraseObject(uid, flag);
}

inline void twn::TownStageManager::setPosByObjectID(int objID, dss::Fix32Vector3& pos)
{
    stage_.setPosByObjectID(objID, pos);
}

inline int twn::TownStageManager::getHitPolyNoByType(int type)
{
    return coll_.getSurfacePolyNoByType(type);
}

inline int FldCollision::getSurfacePolyNoByType(int type)
{
    return surfacePolyNo_[type];
}

inline int twn::TownStageManager::boxCollCompute(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 rad, dss::Fix32Vector3* retVec)
{
    return coll_.boxCompute(nowPos, nextPos, rad, retVec);
}

inline void twn::TownPlayerManager::setScriptPlayer(int flag)
{
    scriptPlayer_ = flag;
}

inline void cmn::CommonWalkDamage::setDamageFlag(bool flag)
{
    damageFlag_ = flag;
}

inline void cmn::CommonWalkDamage::setEffectFlag(bool flag)
{
    effectFlag_ = flag;
}

inline void cmn::CommonWalkDamage::setCounter(int count)
{
    walkCount_ = count;
}

int twn::TownActionIkada::setup()
{
    int ret = -1;
    ctrSurfacePoly_ = -1;
    ctrSurfaceId_ = -1;
    counter_ = 0;
    ikadaObjectId_ = TownStageManager::getSingleton()->getObjectIDfromMapUid(0x1ea);
    if (ikadaObjectId_ != -1) {
        if (cmn::g_cmnPartyInfo.getRideOn() == cmn::RIDE_ON_SHIP_IKADA) {
            if (status::g_StageInfo.getEncountFlag() == false && cmn::g_cmnPartyInfo.isPrevLocation() == false) {
                dss::Fix32Vector3 vec;
                dss::Fix32 fix((fx32)0x4cd);
                TownActionCalculate::getDirByIdx(dirIdx_, vec);
                vec *= fix;
                position_ += vec;
            }
            ikadaPosition_ = TownStageManager::getSingleton()->getMapUidPos(0x1ea);
            position_.vy = ikadaPosition_.vy;
            if (status::g_StageInfo.getEncountFlag() == false) {
                position_.vy = ikadaPosition_.vy;
            }
            setIkadaPosition(position_);
            moveMode_ = 0;
            ret = 9;
        } else {
            if (cmn::g_cmnPartyInfo.getIkadaMapNameId() == 0) {
                ikadaPosition_ = TownStageManager::getSingleton()->getMapUidPos(0x1ea);
                cmn::g_cmnPartyInfo.setIkadaInfo(g_Global.getMapNameId(), ikadaPosition_);
            }
            int nameId = cmn::g_cmnPartyInfo.getIkadaMapNameId();
            if (nameId == g_Global.getMapNameId()) {
                ikadaPosition_ = cmn::g_cmnPartyInfo.getIkadaPos();
                setIkadaPosition(ikadaPosition_);
            } else {
                TownStageManager::getSingleton()->eraseObject(0x1ea, 1);
                ikadaObjectId_ = -1;
            }
        }
    }
    return ret;
}

void twn::TownActionIkada::execute()
{
    switch (moveMode_) {
    case 0:
        ikadaMove();
        break;
    case 1:
    case 2:
        cmn::gMoveToTarget.execute();
        break;
    }
}

int twn::TownActionIkada::update()
{
    dss::Fix32Vector3 targetPos;
    int ret = -1;
    switch (moveMode_) {
    case 0:
        if (ctrSurfaceId_ == -1) {
            ctrSurfaceId_ = TownStageManager::getSingleton()->getHitSurfaceIdByType(12);
            ctrSurfacePoly_ = TownStageManager::getSingleton()->getHitPolyNoByType(12);
        }
        if (TownActionCalculate::checkIkadaTalk(position_, dirIdx_, ctrSurfaceId_, ctrSurfacePoly_, false) == true) {
            break;
        }
        {
            dss::Fix32Vector3 surfaceDir;
            dss::Fix32Vector3 surfacePos;
            if (TownActionCalculate::checkGetDownIkada(position_, dirIdx_, targetPos) == true || script_ == SCRIPT_GET_OFF) {
                if (script_ == SCRIPT_GET_OFF) {
                    targetPos = scriptTarget_;
                }
                TownPlayerManager::getSingleton().setPartyToFirst(position_);
                TownPlayerManager::getSingleton().resetDrawPartyCount();
                cmn::gMoveToTarget.setAction(position_, targetPos, TownPlayerAction::getOnOffSpeed, 1, 0, 9);
                moveMode_ = 2;
                TownPlayerManager::getSingleton().setRemote(true);
                counter_ = 0;
            }
            ret = TownPlayerManager::getSingleton().player_.townActionDoor_.startCheck();
        }
        break;
    case 1:
        if (cmn::gMoveToTarget.update() != -1) {
            moveMode_ = 0;
            cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_SHIP_IKADA);
            TownPlayerManager::getSingleton().setRemote(false);
            TownDamageFloor::getSingleton().clear();
            if (script_ == SCRIPT_GET_ON) {
                TownPlayerManager::getSingleton().setScriptPlayer(false);
                script_ = SCRIPT_NONE;
            }
        }
        break;
    case 2:
        if (counter_ == 10) {
            TownDamageFloor::getSingleton().setDamageFlag(true);
            TownDamageFloor::getSingleton().setEffectFlag(true);
            TownDamageFloor::getSingleton().setCounter(0);
        }
        counter_++;
        if (cmn::gMoveToTarget.update() != -1) {
            ret = 0;
            cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_NONE);
            TownPlayerManager::getSingleton().setRemote(false);
            cmn::g_cmnPartyInfo.setIkadaInfo(g_Global.getMapNameId(), ikadaPosition_);
            if (script_ == SCRIPT_GET_OFF) {
                script_ = SCRIPT_NONE;
                TownPlayerManager::getSingleton().setScriptPlayer(false);
            }
        }
        break;
    }
    return ret;
}

int twn::TownActionIkada::startCheck()
{
    int ret = -1;
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(10) != -1 || script_ == SCRIPT_GET_ON) {
        dss::Fix32Vector3 target;
        dss::Fix32 length;
        if (ikadaObjectId_ != -1) {
            length = TownPlayerAction::ikadaR + TownPlayerAction::getDownL * 2;
            if (TownActionCalculate::checkGetOnShipAndIkada(position_, ikadaPosition_, dirIdx_, length) || script_ == SCRIPT_GET_ON) {
                target = ikadaPosition_;
                cmn::gMoveToTarget.setAction(position_, target, TownPlayerAction::getOnOffSpeed, 1, 1, 9);
                moveMode_ = 1;
                TownPlayerManager::getSingleton().setRemote(true);
                TownDamageFloor::getSingleton().clear();
                ret = 9;
            }
        }
    }
    return ret;
}

void twn::TownActionIkada::ikadaMove()
{
    dss::Fix32Vector3 retVec;
    dss::Fix32Vector3 nowPos;
    dss::Fix32Vector3 nextPos;
    ikadaPosition_ = position_;
    nowPos = ikadaPosition_;
    TownActionCalculate::normalMove(ikadaPosition_, dirIdx_, TownPlayerAction::shipSpeed);
    nextPos = ikadaPosition_;
    nowPos.vy += TownPlayerAction::collR;
    nextPos.vy += TownPlayerAction::collR;
    TownStageManager::getSingleton()->boxCollCompute(nowPos, nextPos, TownPlayerAction::ikadaR, &retVec);
    nextPos = retVec;
    nextPos.vy = nowPos.vy - TownPlayerAction::collR;
    nowPos.vy = nowPos.vy - TownPlayerAction::collR;
    ikadaPosition_ = nextPos;
    position_ = nextPos;
    if (nowPos.vx != nextPos.vx || nowPos.vz != nextPos.vz) {
        ctrSurfacePoly_ = -1;
        ctrSurfaceId_ = -1;
    }
    TownStageManager::getSingleton()->setPosByObjectID(ikadaObjectId_, ikadaPosition_);
    TownDamageFloor::getSingleton().checkDamageFloor(nowPos, nextPos);
}

void twn::TownActionIkada::setIkadaDataByScript(int nameId, dss::Fix32Vector3& pos)
{
    cmn::g_cmnPartyInfo.setIkadaInfo(nameId, pos);
    if (nameId == g_Global.getMapNameId()) {
        ikadaPosition_ = pos;
        ikadaObjectId_ = TownStageManager::getSingleton()->getObjectIDfromMapUid(0x1ea);
        TownStageManager::getSingleton()->setPosByObjectID(ikadaObjectId_, ikadaPosition_);
    } else {
        TownStageManager::getSingleton()->eraseObject(0x1ea, 1);
        ikadaObjectId_ = -1;
    }
}

void twn::TownActionIkada::setIkadaPosition(dss::Fix32Vector3& pos)
{
    TownStageManager::getSingleton()->setPosByObjectID(ikadaObjectId_, pos);
    ikadaPosition_ = pos;
}
