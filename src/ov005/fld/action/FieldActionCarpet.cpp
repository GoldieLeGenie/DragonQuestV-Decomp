#include "ov005/fld/FieldAction.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/window/NormalControl.hpp"
#include "ov005/fld/FieldPlayerDoku.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"

inline cmn::PartyMoveAction::PARTY_ACTION_STATE cmn::PartyMoveAction::getPartyState()
{
    return state_;
}

inline void fld::FieldPartyDraw::setShadowFlag(int index, int flag)
{
    partyCharacter_[index].setShadowFlag(flag);
}

inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type)
{
    rideOnType_ = type;
}

inline void fld::FieldPlayerManager::setHeight(int high)
{
    height_ = high;
}

THUMB int fld::FieldActionCarpet::setup()
{
    state_ = READY;
    counter_ = 0;
    carpetSpeed_.value = 0x1000;
    return -1;
}

THUMB void fld::FieldActionCarpet::execute()
{
    switch (state_) {
    case MOVE: {
        window::gNormalControl.execute();
        carpetMove();
        dss::Fix32Vector3 pos2 = position_;
        FieldPlayerManager::getSingleton().getCarrierDraw(2)->setPosition(pos2);
        FieldPlayerManager::getSingleton().getCarrierDraw(2)->setRotate(dirIdx_);
        break;
    }
    case READY:
        FieldPlayerManager::getSingleton().getCarrierDraw(2)->setPosition(position_);
        FieldPlayerManager::getSingleton().getCarrierDraw(2)->setRotate(dirIdx_);
        if (FieldPlayerManager::getSingleton().party_.getPartyState() != cmn::PartyMoveAction::MOVE_TO_FIRST) {
            FieldPlayerManager::getSingleton().setPartyDrawOne();
            counter_ = 0;
            FieldPlayerManager::getSingleton().partyDraw_.setShadowFlag(0, false);
            dss::Fix32Vector3 pos = position_;
            FieldPlayerManager::getSingleton().getCarrierDraw(2)->setPosition(pos);
            FieldPlayerManager::getSingleton().getCarrierDraw(2)->setRotate(dirIdx_);
            cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_CARPET);
            counter2_ = 0;
            SoundManager::play(0x11, 5);
            state_ = RISE_UP;
        }
        break;
    case RISE_UP:
        FieldPlayerManager::getSingleton().getCarrierDraw(2)->setPosition(position_);
        FieldPlayerManager::getSingleton().getCarrierDraw(2)->setRotate(dirIdx_);
        FieldPlayerManager::getSingleton().getCarrierDraw(2)->setHeight(counter2_ * 6 / 8);
        FieldPlayerManager::getSingleton().setHeight(counter2_ * 12 / 8);
        counter2_++;
        if (counter2_ >= 8) {
            state_ = RISE_UP_END;
            counter2_ = 0;
        }
        break;
    case GET_DOWN:
        FieldPlayerManager::getSingleton().getCarrierDraw(2)->setHeight(6 - counter2_ * 6 / 8);
        FieldPlayerManager::getSingleton().setHeight(12 - counter2_ * 12 / 8);
        counter2_++;
        if (counter2_ >= 8) {
            state_ = GET_DOWN_END;
            counter2_ = 0;
        }
        break;
    case GET_DOWN_END:
        FieldPlayerManager::getSingleton().partyDraw_.setShadowFlag(0, true);
        state_ = GET_OUT_WAIT;
        counter_ = 0;
        break;
    }
}

THUMB int fld::FieldActionCarpet::update()
{
    switch (state_) {
    case RISE_UP_END:
        FieldPlayerDoku::getSingleton().clear();
        FieldPlayerManager::getSingleton().setRemote(false);
        state_ = MOVE;
        break;
    case MOVE:
        if (checkGetOut() == true) {
            FieldPlayerManager::getSingleton().setRemote(true);
            state_ = GET_DOWN;
            counter_ = 0;
            SoundManager::stopBgm(0x14);
        }
        break;
    case GET_OUT_WAIT:
        if (counter_ > 10) {
            FieldPlayerManager::getSingleton().setRemote(false);
            FieldPlayerManager::getSingleton().party_.setAllPlayerAtFirst();
            FieldPlayerManager::getSingleton().party_.LRreset_ = false;
            FieldPlayerManager::getSingleton().resetDrawPartyCount();
            SoundManager::fieldPlay(7);
            return 0;
        }
        break;
    }
    counter_++;
    return -1;
}

THUMB bool fld::FieldActionCarpet::isCarpetGetOnOffAttr()
{
    if (FieldPlayerManager::getSingleton().isTenkuNearAreaGetOn() == true) {
        return false;
    }
    int blkX = position_.vx.value / 0x10000;
    int blkY = position_.vy.value / 0x10000;
    blockType_[8] = FieldStage::getSingleton()->getBlockAttr2(blkX, blkY);
    FieldStage::getSingleton()->setChipAttr(blkX, blkY, blockType_);
    if (isGetOffAttr() == true) {
        FieldStage::getSingleton()->setCarpetColl(blkX, blkY, fieldCollInfo_);
        setColl(blkX, blkY, 1, 1);
        if ((getOn_[0] == 0 && fieldCollInfo_.collLine[0] > position_.vy) || (getOn_[1] == 0 && fieldCollInfo_.collLine[1] < position_.vx) ||
            (getOn_[2] == 0 && fieldCollInfo_.collLine[2] < position_.vy) || (getOn_[3] == 0 && fieldCollInfo_.collLine[3] > position_.vx)) {
            return false;
        }
        return true;
    }
    return false;
}

THUMB void fld::FieldActionCarpet::setStart()
{
    counter_ = 0;
    state_ = READY;
    SoundManager::stopBgm(0x14);
    FieldPlayerManager::getSingleton().player_.setMoveType(6);
    FieldPlayerManager::getSingleton().party_.LRreset_ = true;
    FieldPlayerManager::getSingleton().setRemote(true);
    FieldPlayerManager::getSingleton().party_.moveAllPlayerToFirst();
    FieldPlayerManager::getSingleton().getCarrierDraw(2)->setPosition(position_);
    FieldPlayerManager::getSingleton().getCarrierDraw(2)->setRotate(dirIdx_);
}

THUMB void fld::FieldActionCarpet::carpetMove()
{
    move_ = false;
    dss::Fix32Vector3 oldPos = position_;
    dss::Fix32 speed = Speed2 * carpetSpeed_;
    dss::Fix32 xspeed = xSpeed2 * carpetSpeed_;
    dss::Fix32 yspeed = ySpeed2 * carpetSpeed_;
    moveNormal(speed, xspeed, yspeed);
    int blkX = position_.vx.value / 0x10000;
    int blkY = position_.vy.value / 0x10000;
    blockType_[8] = FieldStage::getSingleton()->getBlockAttr2(blkX, blkY);
    FieldStage::getSingleton()->setCarpetColl(blkX, blkY, fieldCollInfo_);
    FieldStage::getSingleton()->setChipAttr(blkX, blkY, blockType_);
    dss::Fix32Vector3 vec = positionN_ - oldPos;
    coll(blkX, blkY);
    if (oldPos != positionN_) {
        dirIdx_ = FieldActionCalculate::getDir8ByVector3(vec);
        collSE_ = true;
    } else if (move_ == true && collSE_ == true) {
        collSE_ = false;
    }
    int id;
    int index = FieldStage::getSingleton()->getSearchSymbolAttach(positionN_, &id);
    if (index >= 0) {
        // attach ids 0 and 0x1f-0x21 never block the carpet
        switch (id + 0xe) {
        case 0xe:
        case 0x2d:
        case 0x2e:
        case 0x2f:
            break;
        default: {
            dss::Fix32Vector3 smPos = FieldStage::getSingleton()->getSymbolPosition(index);
            if ((smPos - positionN_) * (positionN_ - position_) > dss::Fix32(0L)) {
                positionN_ = position_;
            }
            break;
        }
        }
    }
    position_ = positionN_;
}

THUMB bool fld::FieldActionCarpet::isGetOffAttr()
{
    if (FieldPlayerManager::getSingleton().isTenkuNearAreaGetOn() == true) {
        return false;
    }
    int blkX = position_.vx.value / 0x10000;
    int blkY = position_.vy.value / 0x10000;
    blockType_[8] = FieldStage::getSingleton()->getBlockAttr2(blkX, blkY);
    FieldStage::getSingleton()->setChipAttr(blkX, blkY, blockType_);
    return FieldActionBase::isGetOffAttr();
}

THUMB bool fld::FieldActionCarpet::search()
{
    return false;
}
