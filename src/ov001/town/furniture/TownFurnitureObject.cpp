#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov001/leveldata/FurnitureParam.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/menu/UiMsg.hpp"

inline unsigned long dq5::level::FurnitureParam::getNormalMsg()
{
    return normalMsg;
}

inline unsigned long dq5::level::FurnitureParam::getCheckMsg()
{
    return checkMsg;
}

inline unsigned short dq5::level::FurnitureParam::getSound()
{
    return sound;
}

inline unsigned char dq5::level::FurnitureParam::getType()
{
    return type;
}

inline char dq5::level::FurnitureParam::getBroken()
{
    return byte_1 & 1;
}

inline char dq5::level::FurnitureParam::getAnimation()
{
    return (byte_1 & 2) >> 1;
}

inline int twn::TownStageManager::IsCommonAnimationEnd(int obj_uid)
{
    return stage_.IsCommonAnimationEnd(obj_uid);
}

THUMB twn::TownFurnitureObject::TownFurnitureObject()
{
}

THUMB twn::TownFurnitureObject::~TownFurnitureObject()
{
}

THUMB void twn::TownFurnitureObject::setup(int uid, int data, dq5::level::FurnitureParam* pCommon, int search)
{
    uid_ = uid;
    data_ = data;
    common_ = pCommon;
    phase_ = PHASE_FIRST_MESSAGE;
    index_ = -1;
    furniture_.clear();
    furniture_.set(DEFAULT_SETTING);
    if (common_->getBroken()) {
        if (search) {
            furniture_.remove(OPEN_ANIM_ENABLE);
        } else {
            furniture_.remove(CHECK_MESSAGE_FLAG);
        }
    }
}

THUMB void twn::TownFurnitureObject::setupExtend(int data)
{
}

THUMB void twn::TownFurnitureObject::cleanup()
{
}

THUMB void twn::TownFurnitureObject::execute()
{
    switch (phase_) {
    case PHASE_FIRST_MESSAGE:
        if (checkMsg() != 0 || common_->getNormalMsg() != 0) {
            phase_ = PHASE_WAIT_OPEN;
            setMessage();
        } else {
            phase_ = PHASE_OPEN;
        }
        break;
    case PHASE_WAIT_OPEN:
        if (TownWindowSystem::getSingleton().isWait()) {
            phase_ = PHASE_OPEN;
        }
        if (!TownWindowSystem::getSingleton().isMessageOpen()) {
            cleanup();
            phase_ = PHASE_NONE;
        }
        break;
    case PHASE_OPEN:
        openObject();
        startRiseup();
        phase_ = PHASE_WAIT_CLOSE;
        break;
    case PHASE_WAIT_CLOSE:
        if (isRiseupEnd()) {
            endRiseup();
            phase_ = PHASE_CLOSE;
        }
        break;
    case PHASE_CLOSE:
        if (TownWindowSystem::getSingleton().isWait()) {
            phase_ = PHASE_EXTEND_CLOSE;
        }
        if (!TownWindowSystem::getSingleton().isMessageOpen() && TownStageManager::getSingleton()->IsCommonAnimationEnd(uid_)) {
            closeObject();
            cleanup();
            phase_ = PHASE_NONE;
        }
        break;
    case PHASE_EXTEND_CLOSE:
        if (soundStart()) {
            phase_ = PHASE_CLOSE;
        }
        break;
    }
    if (furniture_.check(CHECK_ANIM_FLAG)) {
        if (TownStageManager::getSingleton()->IsCommonAnimationEnd(uid_)) {
            TownStageManager::getSingleton()->setObjectDraw(uid_, ANIM_NONE, 1);
            furniture_.remove(CHECK_ANIM_FLAG);
        }
    }
}

THUMB void twn::TownFurnitureObject::setFirstMessage()
{
    if (checkMsg() != 0 || common_->getNormalMsg() != 0) {
        if (common_->getCheckMsg() != 0) {
            addMessage(common_->getCheckMsg(), false);
        }
        if (common_->getNormalMsg() != 0) {
            addMessage(common_->getNormalMsg(), false);
        }
        if (data_ != 0) {
            TownWindowSystem::getSingleton().waitCommonMessage();
        }
    }
}

THUMB void twn::TownFurnitureObject::setMessage()
{
    openWindow_ = 1;
    setFirstMessage();
    setSecondMessage();
}

THUMB void twn::TownFurnitureObject::openObject()
{
    if (furniture_.check(OPEN_ANIM_ENABLE)) {
        if (common_->getAnimation()) {
            TownStageManager::getSingleton()->setObjectDraw(uid_, ANIM_OPEN, 1);
            SoundManager::playSe(common_->getSound(), 0);
        }
        if (common_->getBroken()) {
            furniture_.set(CHECK_ANIM_FLAG);
        }
    }
}

THUMB void twn::TownFurnitureObject::closeObject()
{
    if (furniture_.check(CLOSE_ANIM_ENABLE) && common_->getAnimation() && !common_->getBroken()) {
        TownStageManager::getSingleton()->setObjectDraw(uid_, ANIM_CLOSE, 1);
        SoundManager::playSe(common_->getSound(), 0);
    }
}

THUMB void twn::TownFurnitureObject::startRiseup()
{
    index_ = -1;
}

THUMB bool twn::TownFurnitureObject::endRiseup()
{
    if (checkMsg() == 0 && common_->getNormalMsg() == 0) {
        setMessage();
    }
    TownWindowSystem::getSingleton().clearCommonMessage();
    return false;
}

THUMB bool twn::TownFurnitureObject::isRiseupEnd()
{
    return true;
}

THUMB dss::Fix32Vector3 twn::TownFurnitureObject::getFurnPosition()
{
    return TownStageManager::getSingleton()->getRiseupPos(uid_, common_->getType());
}

THUMB unsigned long twn::TownFurnitureObject::checkMsg()
{
    if (furniture_.check(CHECK_MESSAGE_FLAG)) {
        return common_->getCheckMsg();
    }
    if (common_->getBroken()) {
        return 0;
    }
    return common_->getCheckMsg();
}

THUMB void twn::TownFurnitureObject::addMessage(int mesID, bool flag)
{
    if (openWindow_ != 0) {
        openWindow_ = 0;
        ui_MsgSndSet(0x30);
        TownWindowSystem::getSingleton().openSystemMessage();
    }
    if (flag) {
        TownWindowSystem::getSingleton().serialCommonMessage(mesID);
    } else {
        TownWindowSystem::getSingleton().addCommonMessage(mesID);
    }
}

THUMB bool twn::TownFurnitureObject::isFinish()
{
    return phase_ == PHASE_NONE;
}

THUMB bool twn::TownFurnitureObject::soundStart()
{
    return true;
}
