#pragma ipa file
#include "ov001/town/player/TownActionShip.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownDamageFloor.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/global/Global.hpp"
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

inline int FldCollision::getSurfacePolyNoByType(int type)
{
    return surfacePolyNo_[type];
}

inline int twn::TownStageManager::getHitPolyNoByType(int type)
{
    return coll_.getSurfacePolyNoByType(type);
}

inline void twn::TownStageManager::setAlpha(int id, int alpha)
{
    stage_.setAlpha(id, alpha);
}

inline void twn::TownStageManager::eraseObject(int uid, int flag)
{
    stage_.eraseObject(uid, flag);
}

inline void twn::TownStageManager::setPosByObjectID(int objID, dss::Fix32Vector3& pos)
{
    stage_.setPosByObjectID(objID, pos);
}

inline int twn::TownStageManager::getCrossPolyNo(dss::Fix32Vector3& pos0, dss::Fix32Vector3& pos1, dss::Fix32* length, bool flag)
{
    return stage_.collCrossCheckPoly(pos0, pos1, length, flag);
}

namespace twn {
    const dss::Fix32 unk_02151390(0.4f);
}

int twn::TownActionShip::setup()
{
    int ret = -1;
    ctrSurfacePoly_ = -1;
    ctrSurfaceId_ = -1;
    shipObjectId_ = -1;
    namiAlpha_ = 0;
    shipObjectId_ = TownStageManager::getSingleton()->getObjectIDfromMapUid(0x1f4);
    shipNamiObjectId_ = TownStageManager::getSingleton()->getObjectIDfromMapUid(0x1f3);
    prevShipDirection_ = 0;
    shipDirection_ = prevShipDirection_;
    moveMode_ = GET_ON_SHIP;
    if (shipObjectId_ != -1) {
        if (cmn::g_cmnPartyInfo.getRideOn() == cmn::RIDE_ON_SHIP_IKADA) {
            if (status::g_StageInfo.getEncountFlag() == false && cmn::g_cmnPartyInfo.isPrevLocation() == false) {
                dss::Fix32 fix((fx32)0x1800);
                dss::Fix32Vector3 vec;
                TownActionCalculate::getDirByIdx(dirIdx_, vec);
                vec *= fix;
                position_ += vec;
            }
            position_.vy = shipPosition_.vy;
            prevShipDirection_ = dirIdx_;
            setShipPosition(position_);
            shipDirection_ = dirIdx_;
            TownStageManager::getSingleton()->setAlpha(shipNamiObjectId_, 0x1f);
            moveMode_ = SHIP_MOVE;
            ret = 8;
        } else {
            if (cmn::g_cmnPartyInfo.getShipMapName() == 0) {
                shipPosition_ = TownStageManager::getSingleton()->getMapUidPos(0x1f4);
                shipNamiPosition_ = TownStageManager::getSingleton()->getMapUidPos(0x1f3);
                cmn::g_cmnPartyInfo.setShipInfo(g_Global.getMapNameId(), shipPosition_, shipDirection_);
            }
            int id = cmn::g_cmnPartyInfo.getShipMapName();
            if (id == g_Global.getMapNameId()) {
                cmn::g_cmnPartyInfo.getShipInfo(shipPosition_, shipDirection_);
                TownStageManager::getSingleton()->rotObjectUid(0x1f4, shipDirection_);
                setShipPosition(shipPosition_);
            } else {
                TownStageManager::getSingleton()->eraseObject(0x1f4, true);
                TownStageManager::getSingleton()->eraseObject(0x1f3, true);
                shipObjectId_ = -1;
            }
            TownStageManager::getSingleton()->setAlpha(shipNamiObjectId_, 0);
        }
        prevShipPosition_ = shipPosition_;
        prevShipDirection_ = shipDirection_;
    }
    return ret;
}

void twn::TownActionShip::execute()
{
    switch (moveMode_) {
    case SHIP_MOVE:
        shipMove();
        break;
    case SHIP_MOVE_TO:
        cmn::gMoveToTarget.execute();
        setShipPosition(position_);
        setDirection(dirIdx_);
        break;
    case SHIP_DOCKED_AT:
        cmn::gMoveToTarget.execute();
        setShipPosition(position_);
        setDirection(dockedDirIdx_);
        break;
    case GET_ON_SHIP:
    case GET_OFF_SHIP:
        cmn::gMoveToTarget.execute();
        setShipNamiAlpha();
        break;
    }
}

/* not original: at -O4 the idx2 arithmetic is sunk past the first abs() call */
#pragma push
#pragma optimization_level 3
int twn::TownActionShip::update()
{
    int ret = -1;
    static dss::Fix32 fixOne;
    fixOne.value = 0x1000;
    switch (moveMode_) {
    case SHIP_MOVE: {
        if (ctrSurfaceId_ == -1) {
            ctrSurfaceId_ = TownStageManager::getSingleton()->getHitSurfaceIdByType(0xc);
            ctrSurfacePoly_ = TownStageManager::getSingleton()->getHitPolyNoByType(0xc);
        }
        if (ctrSurfaceId_ != -1) {
            dss::Fix32Vector3 pos;
            dss::Fix32Vector3 vec;
            TownActionCalculate::getDirByIdx(dirIdx_, vec);
            pos = position_ + vec;
            if (TownActionCalculate::checkIkadaTalk(pos, dirIdx_, ctrSurfaceId_, ctrSurfacePoly_, false) == true) {
                break;
            }
        }
        shipVec_ = shipPosition_ - prevShipPosition_;
        dss::Fix32Vector3 surfaceDir;
        dss::Fix32Vector3 surfacePos;
        if (TownActionCalculate::checkGetDownShipAndIkada(position_, dirIdx_, targetPos_, surfaceDir, surfacePos, TownPlayerAction::getDownL) == true) {
            dss::Fix32Vector3 vec = shipPosition_ - surfacePos;
            vec.vy = 0L;
            dockedLen_ = surfaceDir * vec - fixOne;
            dockedatPos_ = position_ - surfaceDir * dockedLen_;
            short idx = 0;
            TownActionCalculate::getIdxByVec(idx, surfaceDir);
            short idx1 = idx + 0x4000 - shipDirection_;
            short idx2 = idx - 0x4000 - shipDirection_;
            short tIdx;
            if (dss::abs<short>(idx1) < dss::abs<short>(idx2)) {
                tIdx = idx + 0x4000;
            } else {
                tIdx = idx - 0x4000;
            }
            dockedDirIdx_ = tIdx;
            cmn::gMoveToTarget.setAction(shipPosition_, dockedatPos_, TownPlayerAction::getOnOffSpeed / 3, 0, 2, 8);
            TownPlayerManager::getSingleton().setRemote(true);
            moveMode_ = SHIP_DOCKED_AT;
        }
        ret = TownPlayerManager::getSingleton().player_.townActionDoor_.startCheck();
        break;
    }
    case SHIP_DOCKED_AT:
        if (cmn::gMoveToTarget.update() != -1 && dss::abs<short>(dockedDirIdx_ - shipDirection_) <= 200) {
            shipDirection_ = dockedDirIdx_;
            prevShipPosition_ = shipPosition_;
            prevShipDirection_ = shipDirection_;
            cmn::gMoveToTarget.setAction(position_, targetPos_, TownPlayerAction::getOnOffSpeed, 1, 0, 8);
            TownPlayerManager::getSingleton().setPartyToFirst(position_);
            TownPlayerManager::getSingleton().resetDrawPartyCount();
            moveMode_ = GET_OFF_SHIP;
        }
        break;
    case GET_ON_SHIP:
        if (cmn::gMoveToTarget.update() != -1) {
            moveMode_ = SHIP_MOVE_TO;
            cmn::gMoveToTarget.setAction(position_, dockedatPos_, TownPlayerAction::getOnOffSpeed, 0, 2, 8);
        }
        break;
    case SHIP_MOVE_TO:
        if (cmn::gMoveToTarget.update() != -1) {
            TownPlayerManager::getSingleton().setRemote(false);
            cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_SHIP_IKADA);
            prevShipPosition_ = shipPosition_;
            shipVec_ = shipPosition_ - prevShipPosition_;
            moveMode_ = SHIP_MOVE;
        }
        break;
    case GET_OFF_SHIP:
        if (cmn::gMoveToTarget.update() != -1) {
            TownPlayerManager::getSingleton().setRemote(false);
            cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_NONE);
            cmn::g_cmnPartyInfo.setShipInfo(g_Global.getMapNameId(), shipPosition_, shipDirection_);
            ret = 0;
        }
        break;
    }
    return ret;
}

#pragma pop

int twn::TownActionShip::startCheck()
{
    int ret = -1;
    static const dss::Fix32 len((fx32)0x333);
    static const dss::Fix32 searchL((fx32)0x159a);
    dss::Fix32Vector3 target;
    dss::Fix32 length;
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0xa) != -1 && shipObjectId_ != -1) {
        length = TownPlayerAction::shipR + TownPlayerAction::getDownL * 2;
        if (TownActionCalculate::checkGetOnShipAndIkada(position_, shipPosition_, dirIdx_, length)) {
            target = shipPosition_;
            cmn::gMoveToTarget.setAction(position_, target, TownPlayerAction::getOnOffSpeed, 1, 2, 8);
            moveMode_ = GET_ON_SHIP;
            TownPlayerManager::getSingleton().setRemote(true);
            dockedatPos_ = shipPosition_;
            dss::Fix32Vector3 vec;
            TownActionCalculate::getDirByIdx(shipDirection_ + 0x4000, vec);
            dss::Fix32Vector3 pos = shipPosition_ + vec * searchL;
            dss::Fix32 retLen;
            if (TownStageManager::getSingleton()->getCrossPolyNo(shipPosition_, pos, &retLen, true) > 0) {
                dockedLen_ = retLen;
                dockedatPos_ = shipPosition_ - vec * dockedLen_;
            }
            pos = shipPosition_ - vec * searchL;
            if (TownStageManager::getSingleton()->getCrossPolyNo(shipPosition_, pos, &retLen, true) > 0) {
                dockedLen_ = retLen;
                dockedatPos_ = shipPosition_ + vec * dockedLen_;
            }
            ret = 8;
        }
    }
    return ret;
}

void twn::TownActionShip::setDirection(short playerDir)
{
    prevShipDirection_ = shipDirection_;
    if (((playerDir < 0 ? -playerDir : playerDir) <= 0x3fff || (prevShipDirection_ < 0 ? -prevShipDirection_ : prevShipDirection_) <= 0x3fff)
        && ((playerDir - prevShipDirection_ < 0) ? -(playerDir - prevShipDirection_) : (playerDir - prevShipDirection_)) < 0x7fff) {
        short tempDir = playerDir / 12 + prevShipDirection_ / 12 * 11;
        shipDirection_ = tempDir;
        TownStageManager::getSingleton()->rotObjectUid(0x1f4, shipDirection_);
        TownStageManager::getSingleton()->rotObjectUid(0x1f3, shipDirection_);
    } else {
        unsigned short tempDir = (unsigned short)playerDir / 12 + (unsigned short)prevShipDirection_ / 12 * 11;
        shipDirection_ = tempDir;
        TownStageManager::getSingleton()->rotObjectUid(0x1f4, shipDirection_);
        TownStageManager::getSingleton()->rotObjectUid(0x1f3, shipDirection_);
    }
}

void twn::TownActionShip::setShipNamiAlpha()
{
    dss::Fix32Vector3 vec;
    vec = shipPosition_ - prevShipPosition_;
    short idx = shipDirection_ - prevShipDirection_;
    int addAlpha;
    if (dss::abs<long>(vec.lengthsq().value) > 10 || dss::abs<short>(idx) > 200) {
        addAlpha = 2;
    } else {
        addAlpha = -2;
    }
    namiAlpha_ += addAlpha;
    namiAlpha_ = dss::min<int>(namiAlpha_, 0x1f);
    namiAlpha_ = dss::max<int>(namiAlpha_, 0);
    TownStageManager::getSingleton()->setAlpha(shipNamiObjectId_, namiAlpha_);
}

void twn::TownActionShip::setShipPosition(dss::Fix32Vector3& pos)
{
    TownStageManager::getSingleton()->setPosByObjectID(shipObjectId_, pos);
    TownStageManager::getSingleton()->setPosByObjectID(shipNamiObjectId_, pos);
    shipPosition_ = pos;
    shipNamiPosition_ = pos;
}

void twn::TownActionShip::shipMove()
{
    dss::Fix32Vector3 tempPos;
    dss::Fix32Vector3 nowPos;
    dss::Fix32Vector3 nextPos;
    prevShipPosition_ = shipPosition_;
    nowPos = shipPosition_;
    TownActionCalculate::normalMove(shipPosition_, dirIdx_, TownPlayerAction::shipSpeed);
    nextPos = shipPosition_;
    TownActionCalculate::townCharaColl(nowPos, nextPos, TownPlayerAction::shipR);
    tempPos = nextPos;
    TownActionCalculate::townShipStageColl(nowPos, nextPos, TownPlayerAction::shipCollR, TownPlayerAction::shipR, TownPlayerAction::shipR);
    nextPos.vy = nowPos.vy;
    setShipPosition(nextPos);
    setDirection(dirIdx_);
    setShipNamiAlpha();
    if (nowPos.vx != nextPos.vx || nowPos.vz != nextPos.vz) {
        ctrSurfacePoly_ = -1;
        ctrSurfaceId_ = -1;
    }
    position_ = nextPos;
    TownDamageFloor::getSingleton().checkDamageFloor(nowPos, nextPos);
}

void twn::TownActionShip::setShipDataByScript(int nameId, dss::Fix32Vector3& pos, short idx)
{
    cmn::g_cmnPartyInfo.setShipInfo(nameId, pos, idx);
    if (nameId == g_Global.getMapNameId()) {
        shipPosition_ = pos;
        shipNamiPosition_ = pos;
        prevShipPosition_ = pos;
        shipDirection_ = idx;
        prevShipDirection_ = idx;
        shipObjectId_ = TownStageManager::getSingleton()->getObjectIDfromMapUid(0x1f4);
        TownStageManager::getSingleton()->setPosByObjectID(shipObjectId_, shipPosition_);
    } else {
        TownStageManager::getSingleton()->eraseObject(0x1f4, true);
        shipObjectId_ = -1;
    }
}
