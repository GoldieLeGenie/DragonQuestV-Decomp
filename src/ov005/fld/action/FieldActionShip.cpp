#include "ov005/fld/FieldAction.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/StageInfo.hpp"
#include "ov005/fld/FieldPlayerDoku.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"

inline int cmn::CommonPartyInfo::getShipNo()
{
    return shipNo_;
}

inline void cmn::CommonPartyInfo::setShipNo(int shipNo)
{
    shipNo_ = shipNo;
}

inline cmn::PARTY_RIDE_ON_TYPE cmn::CommonPartyInfo::getRideOn()
{
    return rideOnType_;
}

inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type)
{
    rideOnType_ = type;
}

inline void status::StageInfo::setShipPosition(int index, dss::Fix32Vector3& pos)
{
    shipPosition_[index] = pos;
}

inline void fld::FieldShipDraw::setNamiAnim(int ride)
{
    ride_ = ride;
}

inline void fld::FieldPlayerManager::setShipPos(int index, dss::Fix32Vector3& pos)
{
    shipDraw_[index].setPosition(pos);
}

inline dss::Fix32Vector3& fld::FieldPlayerManager::getShipPos(int index)
{
    return shipDraw_[index].getPosition();
}

inline fld::FieldShipDraw& fld::FieldPlayerManager::getShipDraw(int index)
{
    return shipDraw_[index];
}

inline void fld::FieldPlayerManager::setShipDir(int index, short dir)
{
    shipDraw_[index].setRotate(dir);
}

inline void fld::FieldPlayerManager::setNamiAnim(int index, bool flag)
{
    shipDraw_[index].setNamiAnim(flag);
}

inline void fld::FieldPlayerManager::setDrawNone()
{
    partyDraw_.setDrawNone();
}

inline void fld::FieldPlayerManager::setLink(bool flag)
{
    flagMapLink_ = flag;
}

inline void fld::FieldPlayerManager::setMapLink(bool flag)
{
    flagMapLink_ = flag;
}

inline void fld::FieldPlayerManager::setMoveType(int type)
{
    player_.setMoveType(type);
}

inline void fld::FieldData::pause(int flag)
{
    pause_ = flag;
}

inline void cmn::CommonParticleEmitter::pause(bool flag)
{
    stop_ = flag;
}

inline void fld::FieldStage::pause(int flag)
{
    fieldData.pause(flag);
    cmn::CommonParticleEmitter::getSingleton()->pause(flag);
}

inline void fld::FieldStage::setScriptShip(bool flag)
{
    scriptShip_ = flag;
}

THUMB int fld::FieldActionShip::setup()
{
    shipAction_ = FIELD_SHIP_ACTION_NONE;
    if (cmn::g_cmnPartyInfo.getRideOn() == cmn::RIDE_ON_SHIP_IKADA) {
        FieldPlayerManager::getSingleton().shipDraw_[cmn::g_cmnPartyInfo.getShipNo()].ride_ = 1;
        FieldPlayerManager::getSingleton().partyDraw_.setDrawNone();
        FieldPlayerManager::getSingleton().setShipPos(cmn::g_cmnPartyInfo.getShipNo(), position_);
        shipAction_ = 3;
        return 1;
    }
    return -1;
}

THUMB void fld::FieldActionShip::execute()
{
    switch (shipAction_) {
    case FIELD_SHIP_ACTION_GET_ON:
    case FIELD_SHIP_ACTION_GET_OFF:
        cmn::gMoveToTarget.execute();
        break;
    case 3:
        shipMove();
        break;
    }
}

THUMB void fld::FieldActionShip::startAction()
{
    int shipNo = cmn::g_cmnPartyInfo.getShipNo();
    dss::Fix32Vector3 target = FieldPlayerManager::getSingleton().getShipPos(shipNo);
    FieldPlayerManager::getSingleton().party_.LRreset_ = true;
    FieldPlayerManager::getSingleton().setRemote(true);
    cmn::gMoveToTarget.setAction(position_, target, Speed, 1, 0, 3);
    dss::Fix32Vector3 vec = target - position_;
    dirIdx_ = FieldActionCalculate::getDir8ByVector3(vec);
    downCounter_ = 0;
    SoundManager::stopBgm(0x14);
    shipAction_ = FIELD_SHIP_ACTION_GET_ON;
}

THUMB void fld::FieldActionShip::scriptStart()
{
    shipAction_ = 3;
    dss::Fix32Vector3 pos = FieldPlayerManager::getSingleton().getPosition();
    FieldPlayerManager::getSingleton().setMoveType(FieldPlayer::MOVE_SHIP);
    FieldPlayerManager::getSingleton().setShipPos(1, pos);
    FieldPlayerManager::getSingleton().setDrawNone();
    FieldPlayerManager::getSingleton().setNamiAnim(1, true);
    FieldStage::getSingleton()->setScriptShip(true);
    cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_SHIP_IKADA);
    cmn::g_cmnPartyInfo.setShipNo(1);
}

THUMB void fld::FieldActionShip::shipMove()
{
    int shipNo = cmn::g_cmnPartyInfo.getShipNo();
    moveNormal(Speed, xSpeed, ySpeed);
    int blkX = position_.vx.value / 0x10000;
    int blkY = position_.vy.value / 0x10000;
    blockType_[8] = FieldStage::getSingleton()->getBlockAttr2(blkX, blkY);
    FieldStage::getSingleton()->setShipColl(blkX, blkY, fieldCollInfo_);
    FieldStage::getSingleton()->setChipAttr(blkX, blkY, blockType_);
    setColl(blkX, blkY, 1, 1);
    dss::Fix32Vector3 pos = positionN_;
    dss::Fix32Vector3 vec(0, 0, 0);
    switch (dirIdx_) {
    case 3:
    case 4:
    case 5:
        vec.vy.value = 0x1000;
        pos += vec * 0x18;
        break;
    case 0:
    case 1:
    case 7:
        vec.vy.value = -0x1000;
        pos += vec * 4;
        break;
    }
    if (FieldStage::getSingleton()->getFieldData().isNearSymbol(pos, 0) != -1) {
        positionN_ = position_;
    }
    FieldPlayerInfo fldPlayerInfo = { position_, positionN_, dirIdx_ };
    FieldActionCalculate::playerFixMove(&fldPlayerInfo, &fieldCollInfo_, blkX, blkY, Speed);
    positionN_ = fldPlayerInfo.nextPos;
    FieldPlayerDoku::getSingleton().setBlockAttr(blockType_[8]);
    move_ = false;
    if (position_ != positionN_) {
        move_ = true;
    }
    FieldPlayerDoku::getSingleton().checkDokuDamage(position_, positionN_);
    position_ = positionN_;
    FieldPlayerManager::getSingleton().getShipDraw(shipNo).setPosition(position_);
    FieldPlayerManager::getSingleton().getShipDraw(shipNo).setRotate(dirIdx_);
    status::g_StageInfo.setShipPosition(shipNo, position_);
}

THUMB int fld::FieldActionShip::update()
{
    int shipNo = cmn::g_cmnPartyInfo.getShipNo();
    int ret = -1;
    switch (shipAction_) {
    case FIELD_SHIP_ACTION_GET_ON:
        FieldPlayerManager::getSingleton().setMapLink(true);
        if (cmn::gMoveToTarget.update() == 3) {
            FieldPlayerManager::getSingleton().setRemote(false);
            FieldPlayerManager::getSingleton().partyDraw_.setDrawNone();
            cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_SHIP_IKADA);
            shipAction_ = 3;
            FieldPlayerManager::getSingleton().shipDraw_[shipNo].ride_ = 1;
            FieldStage::getSingleton()->pause(0);
            SoundManager::play(9, 5);
            move_ = false;
        }
        break;
    case FIELD_SHIP_ACTION_GET_OFF:
        if (cmn::gMoveToTarget.update() == 0) {
            cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_NONE);
            FieldPlayerManager::getSingleton().party_.setBashaArray(true);
            FieldPlayerManager::getSingleton().setRemote(false);
            FieldStage::getSingleton()->pause(0);
            SoundManager::fieldPlay(7);
            ret = 0;
        }
        break;
    case 3: {
        int BlkX = position_.vx.value / 0x10000;
        int BlkY = position_.vy.value / 0x10000;
        if (checkGetDownShip(BlkX, BlkY, dirIdx_) == true) {
            FieldPlayerManager::getSingleton().setRemote(true);
            shipAction_ = FIELD_SHIP_ACTION_GET_OFF;
            FieldPlayerManager::getSingleton().partyDraw_.resetDrawCount();
            FieldPlayerManager::getSingleton().party_.setAllPlayerAtFirst();
            FieldPlayerManager::getSingleton().setShipPos(shipNo, position_);
            FieldStage::getSingleton()->pause(1);
            FieldPlayerManager::getSingleton().shipDraw_[shipNo].ride_ = 0;
            FieldPlayerManager::getSingleton().party_.setBashaArray(false);
            SoundManager::stopBgm(0x14);
        }
        break;
    }
    }
    return ret;
}

THUMB bool fld::FieldActionShip::search()
{
    return false;
}

THUMB bool fld::FieldActionShip::checkGetDownShip(int blkX, int blkY, short dirIdx)
{
    int shipNo = cmn::g_cmnPartyInfo.getShipNo();
    FieldStage::getSingleton()->setWalkColl(blkX, blkY, fieldCollInfo_);
    dss::Fix32Vector3 dir = FieldActionCalculate::getVector3ByDir8(dirIdx);
    int targetBlkX = (positionN_.vx.value + dir.vx.value * 10) / 0x10000;
    int targetBlkY;
    if (dir.vy <= dss::Fix32(0L)) {
        targetBlkY = (positionN_.vy.value + dir.vy.value * 10) / 0x10000;
    } else {
        targetBlkY = (positionN_.vy.value + dir.vy.value * 7) / 0x10000;
    }
    if (blockType_[dirIdx] != 7) {
        downCounter_ = 0;
        return false;
    }
    if (dirIdx % 2 != 0) {
        downCounter_ = 0;
        return false;
    }
    if (fieldCollInfo_.blockColl[dirIdx] == true) {
        dss::Fix32Vector3 target = positionN_;
        if (dir.vx < dss::Fix32(0L)) {
            target.vx.value = (targetBlkX << 16) - dir.vx.value * 9;
        } else if (dir.vx > dss::Fix32(0L)) {
            target.vx.value = dir.vx.value * 9 + targetBlkX * 0x10000;
        }
        if (dir.vy < dss::Fix32(0L)) {
            target.vy.value = (targetBlkY << 16) - dir.vy.value * 9;
        } else if (dir.vy > dss::Fix32(0L)) {
            target.vy.value = dir.vy.value * 9 + targetBlkY * 0x10000;
        }
        int tX = target.vx.value / 0x10000;
        int tY = target.vy.value / 0x10000;
        if (FieldStage::getSingleton()->getBlockAttr2(tX + 1, tY) == 8) {
            if (tX + 2 != blkX) {
                target.vx = (long)(((tX + 1) << 4) - 9);
            }
        } else if (FieldStage::getSingleton()->getBlockAttr2(tX - 1, tY) == 8) {
            if (tX - 2 != blkX) {
                target.vx = (long)((tX << 4) + 9);
            }
        }
        if (FieldStage::getSingleton()->getBlockAttr2(tX, tY + 1) == 8) {
            if (tY + 2 != blkY) {
                target.vy = (long)(((tY + 1) << 4) - 9);
            }
        } else if (FieldStage::getSingleton()->getBlockAttr2(tX, tY - 1) == 8) {
            if (tY - 2 != blkY) {
                target.vy = (long)((tY << 4) + 9);
            }
        }
        bool hitAttr = FieldActionCalculate::isEnableGetOff(target);
        dss::Fix32Vector3 vec = target - position_;
        vec.vz = 0L;
        if ((target - position_).lengthsq() > shipGetDownR * shipGetDownR) {
            downCounter_ = 0;
            return false;
        }
        if (hitAttr == true) {
            cmn::gMoveToTarget.setAction(position_, target, Speed, 1, 0, 0);
            dirIdx_ = FieldActionCalculate::getDir8ByVector3(vec);
            FieldPlayerManager::getSingleton().setShipDir(shipNo, dirIdx_);
            if (inputDir_ == -1 || inputDir_ != prevInputDir_) {
                downCounter_ = 0;
            } else {
                downCounter_++;
            }
            if (downCounter_ <= 0xf) {
                return false;
            }
            return true;
        }
    }
    downCounter_ = 0;
    return false;
}

THUMB dss::Fix32Vector3& fld::FieldActionShip::getShipDrawPos(int index)
{
    switch (shipAction_) {
    case FIELD_SHIP_ACTION_GET_ON:
    case FIELD_SHIP_ACTION_GET_OFF:
        return FieldPlayerManager::getSingleton().getShipPos(index);
    case 3:
        if (index == cmn::g_cmnPartyInfo.getShipNo()) {
            return position_;
        }
        FieldPlayerManager::getSingleton().getShipPos(index);
        break;
    }
    return FieldPlayerManager::getSingleton().getShipPos(index);
}
