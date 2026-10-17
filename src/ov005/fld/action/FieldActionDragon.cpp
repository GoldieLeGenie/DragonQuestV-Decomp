#pragma ipa file
#include "ov005/fld/FieldAction.hpp"
#include <nitro/fx/fx_trig.h>
#include "main/sound/SoundManager.hpp"
#include "main/window/NormalControl.hpp"
#include "ov005/fld/FieldPlayerDoku.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"
#include "ov005/fld/FieldSystem.hpp"

inline short fld::FieldPlayerManager::getDirIdx()
{
    return dirIdx_;
}

inline fld::FieldSystemScript& fld::FieldSystem::getScriptSystem()
{
    return fieldSystemScript_;
}

const dss::Fix32 fld::FieldActionDragon::sq2 = 0.7071067f;

THUMB int fld::FieldActionDragon::setup()
{
    state_ = READY_ROLLUP;
    counter_ = 0;
    dragonSpeed_.value = 0x1000;
    return -1;
}

THUMB void fld::FieldActionDragon::execute()
{
    FieldCarrirerDraw* carrier = FieldPlayerManager::getSingleton().getCarrierDraw(4);
    switch (state_) {
    case READY_ROLLUP:
        if (!FieldPlayerManager::getSingleton().getMoveToFirstFlag()) {
            carrier->setShadowFlag(0);
            carrier->setPosition(position_);
            if ((unsigned short)FieldPlayerManager::getSingleton().getDirIdx() < 4) {
                carrier->setRotate(2);
            } else {
                carrier->setRotate(6);
            }
            counter_ = 0;
            SoundManager::stopBgm(0x14);
            state_ = DRAGON_READY_DOWN;
        }
        break;
    case DRAGON_READY_DOWN:
        carrier->setDisplayEnable(1);
        if (FieldPlayerManager::getSingleton().getDirIdx() < 4) {
            carrier->setOffsetXY(counter_ * 0xc0 / 0x78 - 0xc0, 0);
        } else {
            carrier->setOffsetXY(0xc0 - counter_ * 0xc0 / 0x78, 0);
        }
        carrier->setHigh(0x30 - counter_ * 0x30 / 0x78);
        counter_++;
        if (counter_ > 0x78) {
            FieldPlayerManager::getSingleton().setDrawPartyNone();
            state_ = DRAGON_UP_END;
            counter_ = 0;
        }
        break;
    case DRAGON_RIDE_ON:
        state_ = DRAGON_UP;
    case DRAGON_UP:
        state_ = DRAGON_UP_END;
    case DRAGON_MOVE:
        if (counter_ * 2 / 3 < 0x5a) {
            FieldStage::getSingleton()->setOffset(counter_ / 3);
            carrier->setHigh(counter_ / 3);
            counter_++;
            doragonMove(dirIdx_);
        } else {
            window::gNormalControl.execute();
            doragonMove(-1);
        }
        carrier->setPosition(position_);
        carrier->setRotate((unsigned short)dirIdx_);
        break;
    case DRAGON_DOWN:
        switch (FieldPlayerManager::getSingleton().getDirIdx()) {
        case 0:
            cx_ = position_.vx.value - (radius_ << 12);
            cy_ = position_.vy.value;
            rad_ = 0;
            break;
        case 1:
            cx_ = position_.vx.value - sq2.value * radius_;
            cy_ = position_.vy.value - sq2.value * radius_;
            rad_ = 0x2000;
            break;
        case 2:
            cx_ = position_.vx.value;
            cy_ = position_.vy.value - (radius_ << 12);
            rad_ = 0x4000;
            break;
        case 3:
            cx_ = position_.vx.value + sq2.value * radius_;
            cy_ = position_.vy.value - sq2.value * radius_;
            rad_ = 0x6000;
            break;
        case 4:
            cx_ = position_.vx.value + (radius_ << 12);
            cy_ = position_.vy.value;
            rad_ = 0x8000;
            break;
        case 5:
            cx_ = position_.vx.value + sq2.value * radius_;
            cy_ = position_.vy.value + sq2.value * radius_;
            rad_ = 0xa000;
            break;
        case 6:
            cx_ = position_.vx.value;
            cy_ = position_.vy.value + (radius_ << 12);
            rad_ = 0xc000;
            break;
        default:
            cx_ = position_.vx.value - sq2.value * radius_;
            cy_ = position_.vy.value + sq2.value * radius_;
            rad_ = 0xe000;
            break;
        }
        state_ = DRAGON_GET_OFF;
        break;
    case DRAGON_GET_OFF: {
        FieldStage::getSingleton()->setOffset((0x5a - (counter_ << 12) / 0x1800) / 2);
        FieldPlayerManager::getSingleton().fieldDragonDraw_.setHigh((0x5a - (counter_ << 12) / 0x1800) / 2);
        unsigned short angle = rad_ + ((-counter_ << 12) / 0x1800 << 16) / 0x5a;
        int x = cx_ + FX_CosIdx(angle) * radius_;
        int y = cy_ + FX_SinIdx(angle) * radius_;
        position_.vx.value = x;
        position_.vy.value = y;
        carrier->setPosition(position_);
        carrier->setRotate((unsigned int)(angle << 3) >> 16);
        counter_++;
        if ((counter_ << 12) / 0x1800 > 0x5a) {
            state_ = DRAGON_GET_OFF2;
            counter_ = 0;
            offsetx_ = 0;
            offsety_ = 0;
        }
        break;
    }
    case DRAGON_GET_OFF2:
        FieldPlayerManager::getSingleton().party_.setAllPlayerAtFirst();
        FieldPlayerManager::getSingleton().party_.LRreset_ = false;
        FieldPlayerManager::getSingleton().resetDrawPartyCount();
        carrier->setDisplayEnable(1);
        switch (FieldPlayerManager::getSingleton().getDirIdx()) {
        case 0:
            offsetx_ = 0;
            offsety_ = -(counter_ * balSpeed.value) / 0x1000;
            break;
        case 1:
            offsetx_ = counter_ * balXSpeed.value / 0x1000;
            offsety_ = -(counter_ * balYSpeed.value) / 0x1000;
            break;
        case 2:
            offsetx_ = counter_ * balSpeed.value / 0x1000;
            offsety_ = 0;
            break;
        case 3:
            offsetx_ = counter_ * balXSpeed.value / 0x1000;
            offsety_ = counter_ * balYSpeed.value / 0x1000;
            break;
        case 4:
            offsetx_ = 0;
            offsety_ = counter_ * balYSpeed.value / 0x1000;
            break;
        case 5:
            offsetx_ = -(counter_ * balXSpeed.value) / 0x1000;
            offsety_ = counter_ * balYSpeed.value / 0x1000;
            break;
        case 6:
            offsetx_ = -(counter_ * balSpeed.value) / 0x1000;
            offsety_ = 0;
            break;
        default:
            offsetx_ = -(counter_ * balXSpeed.value) / 0x1000;
            offsety_ = -(counter_ * balYSpeed.value) / 0x1000;
            break;
        }
        carrier->setRotate(FieldPlayerManager::getSingleton().getDirIdx());
        carrier->setOffsetXY(offsetx_, offsety_);
        carrier->setHigh(counter_ * 0x30 / 0x50);
        counter_++;
        if (counter_ > 0x50) {
            state_ = DRAGON_GET_OFF_END;
            counter_ = 0;
        } else if (counter_ == 0x32) {
            SoundManager::stopBgm(0x14);
        }
        break;
    }
}

THUMB int fld::FieldActionDragon::update()
{
    switch (state_) {
    case READY_ROLLUP:
    case DRAGON_READY_DOWN:
    case DRAGON_RIDE_ON:
    case DRAGON_UP:
        break;
    case DRAGON_UP_END:
        FieldPlayerManager::getSingleton().setRemote(false);
        SoundManager::play(0x11, 5);
        state_ = DRAGON_MOVE;
        break;
    case DRAGON_MOVE:
        if (FieldSystem::getSingleton()->getScriptSystem().isEventLock() == true) {
            return -1;
        }
        if (FieldStage::getSingleton()->getSearchSymbolAttach(position_, NULL) == 0x27) {
            break;
        }
        if (checkGetOut() == true) {
            state_ = DRAGON_DOWN;
            counter_ = 0;
            FieldPlayerManager::getSingleton().setRemote(true);
        }
        break;
    case DRAGON_DOWN:
    case DRAGON_GET_OFF:
    case DRAGON_GET_OFF2:
        break;
    case DRAGON_GET_OFF_END:
        FieldPlayerManager::getSingleton().fieldDragonDraw_.setDisplayEnable(0);
        FieldPlayerManager::getSingleton().setRemote(false);
        FieldStage::getSingleton()->setOffset(0);
        SoundManager::fieldPlay(7);
        return 0;
    }
    counter_++;
    return -1;
}

THUMB void fld::FieldActionDragon::setStart()
{
    counter_ = 0;
    state_ = READY_ROLLUP;
    speed_.set(0, 0, 0);
    FieldPlayerManager::getSingleton().party_.LRreset_ = true;
    FieldPlayerManager::getSingleton().setMoveToFirstFlag();
    FieldPlayerManager::getSingleton().setRemote(true);
    SoundManager::playSe(0x16b, 0);
    FieldPlayerDoku::getSingleton().clear();
}

THUMB void fld::FieldActionDragon::directStart()
{
    counter_ = 0x5a;
    FieldStage::getSingleton()->setOffset(counter_ / 2);
    FieldPlayerManager::getSingleton().fieldDragonDraw_.setHigh(counter_ / 2);
    FieldPlayerManager::getSingleton().fieldDragonDraw_.setDisplayEnable(1);
    FieldPlayerManager::getSingleton().fieldDragonDraw_.setShadowFlag(0);
    FieldPlayerManager::getSingleton().setDrawPartyNone();
    state_ = DRAGON_MOVE;
}

THUMB void fld::FieldActionDragon::doragonMove(short idx)
{
    if (FieldSystem::getSingleton()->getScriptSystem().isEventLock() == true) {
        return;
    }
    dss::Fix32 speed1 = 0x1800;
    dss::Fix32 speed2 = 0x14cd;
    endlessMove(speed1, speed2, idx);
    position_ = positionN_;
}

THUMB bool fld::FieldActionDragon::isGetOffAttr()
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

THUMB bool fld::FieldActionDragon::search()
{
    return false;
}

