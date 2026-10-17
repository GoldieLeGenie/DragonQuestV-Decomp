#include "ov005/fld/FieldAction.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/status/StageInfo.hpp"
#include "main/window/NormalControl.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"

inline void status::StageInfo::setFirmamentPosition(dss::Fix32Vector3& pos)
{
    firmamentPosition_ = pos;
}

inline bool fld::FieldActionCastle::search()
{
    return false;
}

THUMB int fld::FieldActionCastle::setup()
{
    state_ = CROUD_DRAW;
    counter_ = 0;
    counter2_ = 0;
    castleSpeed_.value = 0x1000;
    return -1;
}

THUMB void fld::FieldActionCastle::execute()
{
    FieldCarrirerDraw* carrier = FieldPlayerManager::getSingleton().getCarrierDraw(3);
    switch (state_) {
    case CROUD_DRAW:
        carrier->setDepth(6);
        carrier->setShadowFlag(1);
        carrier->setShadowAlpha(counter2_ * 0x1f / 8);
        if (counter2_ >= 8) {
            counter2_ = 0;
            state_ = READY_UP;
        }
        counter2_++;
        break;
    case READY_UP:
        counter2_ = dss::clamp(0, counter2_, 0x28);
        FieldStage::getSingleton()->setOffset(counter2_ / 2);
        carrier->setHeight(counter2_ / 2);
        if (counter2_ >= 0x28) {
            counter2_ = 0;
            state_ = READY_UP_END;
        }
        counter2_++;
        break;
    case MOVE:
        window::gNormalControl.execute();
        castleMove();
        break;
    case GET_DOWN:
        counter2_ = dss::clamp(0, counter2_, 0x28);
        FieldStage::getSingleton()->setOffset((0x28 - counter2_) / 2);
        FieldPlayerManager::getSingleton().firmamentDraw_.setHeight((0x28 - counter2_) / 2);
        if (counter2_ >= 0x28) {
            state_ = CROWD_ERASE;
            counter2_ = 0;
        }
        counter2_++;
        break;
    case CROWD_ERASE:
        carrier->setShadowAlpha(0x1f - counter2_ * 0x1f / 8);
        if (counter2_ >= 8) {
            counter2_ = 0;
            state_ = CASTLE_END;
        }
        counter2_++;
        break;
    }
    FieldPlayerManager::getSingleton().firmamentDraw_.setPosition(position_);
    FieldPlayerManager::getSingleton().firmamentDraw_.setRotate((unsigned short)dirIdx_);
}

THUMB int fld::FieldActionCastle::update()
{
    switch (state_) {
    case CROUD_DRAW:
    case READY_UP:
        break;
    case READY_UP_END:
        state_ = MOVE;
        FieldPlayerManager::getSingleton().setRemote(false);
        break;
    case MOVE:
        if (checkGetOut() == true) {
            state_ = GET_DOWN;
            counter_ = 0;
            FieldPlayerManager::getSingleton().setRemote(true);
        }
        break;
    case GET_DOWN:
    case CROWD_ERASE:
        break;
    case CASTLE_END: {
        dss::Fix32Vector3 pos(0.0f, 0.0f, 7.5f);
        cmn::g_extraMapLink.setExtraLinkTown(0x58, pos, 0);
        FieldStage::getSingleton()->setOffset(0);
        status::g_StageInfo.setFirmamentPosition(position_);
        break;
    }
    }
    counter_++;
    return -1;
}

THUMB void fld::FieldActionCastle::setStart()
{
    position_ = FieldPlayerManager::getSingleton().firmamentDraw_.getPosition();
    counter_ = 0;
    state_ = CROUD_DRAW;
    speed_.set(0, 0, 0);
    FieldPlayerManager::getSingleton().setDrawPartyNone();
    FieldPlayerManager::getSingleton().player_.setMoveType(5);
    FieldPlayerManager::getSingleton().setRemote(true);
}

THUMB bool fld::FieldActionCastle::isGetOffAttr()
{
    int blkX = position_.vx.value / 0x10000;
    int blkY = position_.vy.value / 0x10000;
    blockType_[8] = FieldStage::getSingleton()->getBlockAttr2(blkX, blkY);
    FieldStage::getSingleton()->setChipAttr(blkX, blkY, blockType_);
    if (FieldActionBase::isGetOffAttr() == false || blockType_[8] == 7) {
        return false;
    }
    dss::Fix32Vector3 temp = position_;
    position_.vx.value += 0x10000;
    FieldStage::getSingleton()->setChipAttr(position_.vx.value / 0x10000, position_.vy.value / 0x10000, blockType_);
    if (FieldActionBase::isGetOffAttr() == false) {
        position_ = temp;
        return false;
    }
    position_.vx.value -= 0x20000;
    FieldStage::getSingleton()->setChipAttr(position_.vx.value / 0x10000, position_.vy.value / 0x10000, blockType_);
    if (FieldActionBase::isGetOffAttr() == false) {
        position_ = temp;
        return false;
    }
    position_.vy.value -= 0x10000;
    FieldStage::getSingleton()->setChipAttr(position_.vx.value / 0x10000, position_.vy.value / 0x10000, blockType_);
    if (FieldActionBase::isGetOffAttr() == false) {
        position_ = temp;
        return false;
    }
    position_.vy.value += 0x10000;
    FieldStage::getSingleton()->setChipAttr(position_.vx.value / 0x10000, position_.vy.value / 0x10000, blockType_);
    if (FieldActionBase::isGetOffAttr() == false) {
        position_ = temp;
        return false;
    }
    position_ = temp;
    if (FieldStage::getSingleton()->getFieldData().isSymbolNearArea(position_, 0x20, 0x20) != -1) {
        return false;
    }
    position_ = temp;
    return true;
}

THUMB void fld::FieldActionCastle::castleMove()
{
    endlessMove(castleSpeed_, castleSpeed_, -1);
    if (FieldStage::getSingleton()->getFieldData().isSymbolNearArea(positionN_, 0x38, 0x38) == 0x27) {
        positionN_ = position_;
    }
    position_ = positionN_;
}
