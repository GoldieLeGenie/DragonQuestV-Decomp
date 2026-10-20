#pragma ipa file
#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "ov001/leveldata/FurnitureData.hpp"
#include "ov001/leveldata/FurnitureParam.hpp"
#include "ov001/leveldata/MirrorMessage.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/CharacterInitData.hpp"
#include "main/leveldata/EncountData.hpp"
#include "main/leveldata/EncountSpecial.hpp"
#include "main/menu/MaterielMenu_SlotEnter.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/window/ShopMenuControl.hpp"

inline dq5::level::CharacterInitData* dq5::level::CharacterInitData::getRecord(int index)
{
    return (CharacterInitData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::EncountData* dq5::level::EncountData::getRecord(int index)
{
    return (EncountData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::EncountSpecial* dq5::level::EncountSpecial::getRecord(int index)
{
    return (EncountSpecial*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::FurnitureData* dq5::level::FurnitureData::getRecord(int index)
{
    return (FurnitureData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline char dq5::level::FurnitureData::getScript()
{
    return byte_1 & 1;
}

inline char dq5::level::FurnitureData::getSlot()
{
    return (byte_1 & 0x1e) >> 1;
}

inline dq5::level::FurnitureParam* dq5::level::FurnitureParam::getRecord(int index)
{
    return (FurnitureParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline char dq5::level::FurnitureParam::getBroken()
{
    return byte_1 & 1;
}

inline dq5::level::MirrorMessage* dq5::level::MirrorMessage::getRecord(int index)
{
    return (MirrorMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::MirrorMessage::getArraySize()
{
    return binary_.record_;
}

inline char dq5::level::MirrorMessage::getYounenki()
{
    return byte_1 & 1;
}

inline char dq5::level::MirrorMessage::getSeinenki()
{
    return (byte_1 & 2) >> 1;
}

inline char dq5::level::MirrorMessage::getSounenki()
{
    return (byte_1 & 4) >> 2;
}

inline char dq5::level::MirrorMessage::getCount()
{
    return (byte_1 & 0x18) >> 3;
}

inline char dq5::level::MirrorMessage::getVoice1()
{
    return (byte_1 & 0x60) >> 5;
}

inline char dq5::level::MirrorMessage::getVoice2()
{
    return byte_2 & 3;
}

inline char dq5::level::MirrorMessage::getVoice3()
{
    return (byte_2 & 0xc) >> 2;
}

inline int status::PlayerStatus::getPlayerKindIndex()
{
    return haveStatusInfo_.haveStatus_.playerKindIndex_;
}

inline void twn::TownStageManager::eraseObject(int uid, int flag)
{
    stage_.eraseObject(uid, flag);
}

inline void window::ShopMenuControl::startMenu(int type)
{
    menuType_ = type;
    state_ = 7;
}

static dss::Fix32Vector3 s_twinkleRot;
static dss::Fix32Vector3 s_twinkleScale(0.96f, 0.96f, 0.96f);
static GXBoxTestParam s_twinkleBox;
static dss::Fix32 s_twinkleRate((fx32)0x1000);

THUMB twn::TownFurnitureManager::TownFurnitureManager()
{
}

THUMB twn::TownFurnitureManager::~TownFurnitureManager()
{
}

THUMB twn::TownFurnitureManager* twn::TownFurnitureManager::getSingleton()
{
    static TownFurnitureManager m_singleton;
    return &m_singleton;
}


THUMB void twn::TownFurnitureManager::initialize()
{
    list_ = status::g_StageAttribute.furnitureIndex_;
    if (status::g_StageAttribute.furnitureIndex_ >= 0) {
        size_ = dq5::level::FurnitureData::getRecord(list_)->ListSize;
    } else {
        size_ = 0;
    }
    returnFurnitureEncount();
    for (int i = 0; i < size_; i++) {
        if (status::g_StageInfo.getFurnFlag(dq5::level::FurnitureData::getRecord(list_ + i)->flagIndex)
            && dq5::level::FurnitureData::getRecord(list_ + i)->type == 0x44) {
            TownStageManager::getSingleton()->setObjectDraw(dq5::level::FurnitureData::getRecord(list_ + i)->uid, 3, 1);
        }
        if (status::g_StageInfo.getDoorOpenFlag(dq5::level::FurnitureData::getRecord(list_ + i)->openIndex)) {
            TownStageManager::getSingleton()->eraseObject(dq5::level::FurnitureData::getRecord(list_ + i)->uid, 1);
        }
        if (status::g_StageInfo.getFurnBreakFlag(dq5::level::FurnitureData::getRecord(list_ + i)->furnIndex)) {
            TownStageManager::getSingleton()->eraseObject(dq5::level::FurnitureData::getRecord(list_ + i)->uid, 1);
        }
    }
    object_ = NULL;
    TownFurnitureControlManager::getSingleton().initialize();
    s_twinkleBox.x = 0;
    s_twinkleBox.y = 0;
    s_twinkleBox.z = 0;
    s_twinkleBox.width = 0x1000;
    s_twinkleBox.height = 0x1000;
    s_twinkleBox.depth = 0x1000;
    force_ = false;
    prevCheck_ = CHECK_NONE;
    phase_ = 0;
    remiIndex_ = -1;
}

THUMB void twn::TownFurnitureManager::terminate()
{
    object_ = NULL;
    TownFurnitureControlManager::getSingleton().terminate();
}

THUMB void twn::TownFurnitureManager::execute()
{
    TownFurnitureControlManager::getSingleton().execute();
    if (object_ != NULL) {
        object_->execute();
        if (object_->isFinish()) {
            object_ = NULL;
            TownPlayerManager::getSingleton().setLock(false);
        }
    }
    if (remiIndex_ >= 0 && TownRiseupManager::getSingleton().isFinish(remiIndex_)) {
        TownPlayerManager::getSingleton().setLock(false);
        remiIndex_ = -1;
    }
}

THUMB bool twn::TownFurnitureManager::isProcess()
{
    if (object_ != NULL) {
        return true;
    }
    return false;
}

THUMB int twn::TownFurnitureManager::getFurnitureIndex(int uid)
{
    int index = -1;
    for (int i = 0; i < size_; i++) {
        if (uid == dq5::level::FurnitureData::getRecord(list_ + i)->uid) {
            index = list_ + i;
            break;
        }
    }
    return index;
}

THUMB void twn::TownFurnitureManager::draw()
{
    switch (phase_) {
    case 0:
        break;
    case 1:
        setTwinklePoint();
        phase_ = 2;
        break;
    case 2:
        setTwinklePoint();
        phase_ = 3;
        break;
    case 3:
        drawTwinklePoint();
        phase_ = 0;
        break;
    }
}

THUMB void twn::TownFurnitureManager::returnFurnitureEncount()
{
    if (status::g_StageInfo.encountMapUid_ != 0 && status::g_BattleResult.playerVictory_ == 1) {
        status::g_StageInfo.setFurnFlag(dq5::level::FurnitureData::getRecord(getFurnitureIndex(status::g_StageInfo.encountMapUid_))->flagIndex);
    }
    status::g_StageInfo.encountMapUid_ = 0;
}

THUMB void twn::TownFurnitureManager::openDoor(int uid)
{
    int index = getFurnitureIndex(uid);
    if (index >= 0) {
        status::g_StageInfo.setDoorOpenFlag(dq5::level::FurnitureData::getRecord(index)->openIndex);
    }
}

THUMB void twn::TownFurnitureManager::closeDoor(int uid)
{
    int index = getFurnitureIndex(uid);
    if (index >= 0) {
        status::g_StageInfo.removeDoorOpenFlag(dq5::level::FurnitureData::getRecord(index)->openIndex);
    }
}

THUMB bool twn::TownFurnitureManager::isOpenDoor(int uid)
{
    int index = getFurnitureIndex(uid);
    if (index < 0) {
        return false;
    }
    return status::g_StageInfo.getDoorOpenFlag(dq5::level::FurnitureData::getRecord(index)->openIndex);
}

THUMB void twn::TownFurnitureManager::setFurnFlag(int uid, int flag)
{
    int index = getFurnitureIndex(uid);
    if (index >= 0) {
        if (flag) {
            status::g_StageInfo.setFurnFlag(dq5::level::FurnitureData::getRecord(index)->flagIndex);
        } else {
            status::g_StageInfo.removeFurnFlag(dq5::level::FurnitureData::getRecord(index)->flagIndex);
        }
    }
}

THUMB bool twn::TownFurnitureManager::checkObject(int uid, bool rev, bool search, int lock)
{
    int set = false;
    int index = getFurnitureIndex(uid);
    if (index < 0) {
        return false;
    }
    dq5::level::FurnitureData* data = dq5::level::FurnitureData::getRecord(index);
    force_ = false;
    switch (data->type) {
    case 0x22:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x49:
        if (data->message == 0 && data->item == 0 && data->gold == 0 && !data->getScript()) {
            return false;
        }
        break;
    }
    if (rev && checkRevMessage(index)) {
        return true;
    }
    dq5::level::FurnitureParam* param;
    if (data->type == 0) {
        if (data->message == 0 && data->item == 0 && data->gold == 0) {
            return false;
        }
        param = dq5::level::FurnitureParam::getRecord(0);
    } else {
        param = dq5::level::FurnitureParam::getRecord(data->type);
    }
    if ((unsigned char)(data->type + 0xff) <= 2) {
        bootSlot(data->uid);
        return true;
    }
    if (data->type == 4) {
        if (status::g_Story.chapter_ == 5) {
            TownWindowSystem::getSingleton().openSystemMessage(0xccd8b, 1);
        } else if (g_LocalFlag.check(0xe)) {
            TownWindowSystem::getSingleton().openSystemMessage(0xccd89, 1);
        } else {
            window::gShopMenuControl.startMenu(0x27);
        }
        return true;
    }
    TownPlayerManager::getSingleton().setLock(true);
    if ((unsigned char)(data->type + 0xee) <= 1) {
        return mirrorTalk();
    }
    if (param->getBroken() && !search) {
        status::g_StageInfo.setFurnBreakFlag(data->furnIndex);
    }
    if (data->item != 0 || data->gold != 0 || data->encount != 0) {
        if (status::g_StageInfo.getFurnFlag(data->flagIndex)) {
            set = true;
        }
    } else if (data->message == 0 && data->item == 0 && data->gold == 0 && data->encount == 0) {
        set = true;
    }
    if (set) {
        prevCheck_ = CHECK_NONE;
        if (lock == 1) {
            TownPlayerManager::getSingleton().setLock(false);
            return false;
        }
        object_ = &nothingObject_;
        object_->setup(data->uid, param->nothingMsg, param, search);
        if (data->type == 0x44) {
            if (!status::g_StageInfo.getFurnFlag(data->flagIndex)) {
                status::g_StageInfo.setFurnFlag(data->flagIndex);
                object_->furniture_.remove(TownFurnitureObject::CLOSE_ANIM_ENABLE);
            } else {
                object_->furniture_.remove(TownFurnitureObject::OPEN_ANIM_ENABLE | TownFurnitureObject::CLOSE_ANIM_ENABLE | TownFurnitureObject::CHECK_ANIM_FLAG);
            }
        }
    } else {
    if (data->message != 0) {
        prevCheck_ = CHECK_MESSAGE;
        object_ = &msgObject_;
        object_->setup(data->uid, data->message, param, search);
    } else if (data->item != 0) {
        prevCheck_ = CHECK_ITEM;
        object_ = &itemObject_;
        object_->setup(data->uid, data->item, param, search);
        status::g_StageInfo.setFurnFlag(data->flagIndex);
    } else if (data->gold != 0) {
        prevCheck_ = CHECK_GOLD;
        object_ = &goldObject_;
        object_->setup(data->uid, data->gold, param, search);
        status::g_StageInfo.setFurnFlag(data->flagIndex);
    } else if (data->encount != 0) {
        prevCheck_ = CHECK_MONSTER;
        object_ = &encountObject_;
        object_->setup(data->uid, data->encount, param, search);
        object_->setupExtend(dq5::level::EncountSpecial::getRecord(dq5::level::EncountData::getRecord(data->encount)->particulParty)->monsterID1);
    }
    if (data->type == 0x44) {
        object_->furniture_.remove(TownFurnitureObject::CLOSE_ANIM_ENABLE);
    }
    }
    return true;
}

THUMB bool twn::TownFurnitureManager::checkRevMessage(int index)
{
    dq5::level::FurnitureParam* param = dq5::level::FurnitureParam::getRecord(dq5::level::FurnitureData::getRecord(index)->type);
    if (param->backMsg != 0) {
        ui_MsgSndSet(0x30);
        TownWindowSystem::getSingleton().openSystemMessage();
        if (param->checkMsg != 0) {
            TownWindowSystem::getSingleton().addCommonMessage(param->checkMsg);
        }
        TownWindowSystem::getSingleton().serialCommonMessage(param->backMsg);
        return true;
    }
    return false;
}

THUMB int twn::TownFurnitureManager::checkCoffer(int uid)
{
    int index = getFurnitureIndex(uid);
    if (index < 0) {
        return 0;
    }
    if (status::g_StageInfo.getFurnFlag(dq5::level::FurnitureData::getRecord(index)->flagIndex)) {
        return 1;
    }
    if (dq5::level::FurnitureData::getRecord(index)->item != 0) {
        return 3;
    }
    if (dq5::level::FurnitureData::getRecord(index)->gold != 0) {
        return 4;
    }
    if (dq5::level::FurnitureData::getRecord(index)->encount != 0) {
        return 5;
    }
    return 2;
}

THUMB int twn::TownFurnitureManager::getCofferType(int uid)
{
    int index = getFurnitureIndex(uid);
    if (index < 0) {
        return 0;
    }
    return dq5::level::FurnitureData::getRecord(index)->type;
}

THUMB int twn::TownFurnitureManager::searchFloorItem()
{
    int count = 0;
    for (int i = 0; i < size_; i++) {
        if ((dq5::level::FurnitureData::getRecord(i + list_)->item != 0 || dq5::level::FurnitureData::getRecord(i + list_)->gold != 0
                || dq5::level::FurnitureData::getRecord(i + list_)->encount != 0)
            && !status::g_StageInfo.getFurnFlag(dq5::level::FurnitureData::getRecord(i + list_)->flagIndex)
            && dq5::level::FurnitureData::getRecord(i + list_)->uid < 30000) {
            count++;
        }
    }
    return count;
}

THUMB void twn::TownFurnitureManager::setTwinklePoint()
{
    for (int i = 0; i < floorItem_; i++) {
        if (fldBoxTest(&twinkle[i].position, &s_twinkleRot, &s_twinkleScale, &s_twinkleBox, &s_twinkleRate)) {
            twinkle[i].enable = true;
        }
    }
}

THUMB void twn::TownFurnitureManager::drawTwinklePoint()
{
    int count = 0;
    for (int i = 0; i < floorItem_; i++) {
        if (twinkle[i].enable) {
            remiIndex_ = TownRiseupManager::getSingleton().setupSprite(twinkleEffect, twinkle[i].position, true, count * interval_);
            count++;
        }
    }
    if (remiIndex_ < 0) {
        TownPlayerManager::getSingleton().setLock(false);
    }
}

THUMB bool twn::TownFurnitureManager::isActive()
{
    if (object_ != NULL) {
        return true;
    }
    return false;
}

THUMB void twn::TownFurnitureManager::bootSlot(int uid)
{
    int index = getFurnitureIndex(uid);
    window::gShopMenuControl.startMenu(0x1b);
    menu::gMaterielMenu_SlotEnter.setSlotType(dq5::level::FurnitureData::getRecord(index)->getSlot());
}

THUMB bool twn::TownFurnitureManager::mirrorTalk()
{
    int count = 0;
    int list[32];
    for (unsigned int i = 0; i < dq5::level::MirrorMessage::getArraySize(); i++) {
        switch (status::g_Story.chapter_) {
        case 1:
            if (!dq5::level::MirrorMessage::getRecord(i)->getYounenki()) {
                continue;
            }
            break;
        case 2:
            if (!dq5::level::MirrorMessage::getRecord(i)->getSeinenki()) {
                continue;
            }
            break;
        case 3:
            if (!dq5::level::MirrorMessage::getRecord(i)->getSounenki()) {
                continue;
            }
            break;
        }
        switch (getLeaderIndex()) {
        case 0:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 0) {
                continue;
            }
            break;
        case 1:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 1) {
                continue;
            }
            break;
        case 2:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 2) {
                continue;
            }
            break;
        case 3:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 3) {
                continue;
            }
            break;
        case 4:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 4) {
                continue;
            }
            break;
        case 6:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 6) {
                continue;
            }
            break;
        case 7:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 7) {
                continue;
            }
            break;
        case 8:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 8) {
                continue;
            }
            break;
        case 9:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 9) {
                continue;
            }
            break;
        case 13:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 13) {
                continue;
            }
            break;
        case 14:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 14) {
                continue;
            }
            break;
        case 16:
        case 17:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 16) {
                continue;
            }
            break;
        default:
            if (dq5::level::MirrorMessage::getRecord(i)->leader != 0x58) {
                continue;
            }
            break;
        }
        list[count] = i;
        count++;
    }
    if (count == 0) {
        TownPlayerManager::getSingleton().setLock(false);
        return false;
    }
    int index = list[UnkDssRand::rand(count)];
    object_ = &msgObject_;
    int voice[5];
    voice[0] = 0;
    voice[1] = dq5::level::MirrorMessage::getRecord(index)->getVoice1();
    voice[2] = dq5::level::MirrorMessage::getRecord(index)->getVoice2();
    voice[3] = dq5::level::MirrorMessage::getRecord(index)->getVoice3();
    voice[4] = 0;
    if (getLeaderIndex() == 16 || getLeaderIndex() == 17) {
        for (int i = 0; i < 5; i++) {
            if (voice[i] != 0) {
                if (status::g_Story.chapter_ == 1) {
                    voice[i] = 1;
                } else {
                    voice[i] = 2;
                }
            }
        }
    }
    int sound[5];
    for (int i = 0; i < 5; i++) {
        switch (voice[i]) {
        case 0:
            sound[i] = 0x30;
            break;
        case 1:
            sound[i] = 0x31;
            break;
        case 2:
            sound[i] = 0x32;
            break;
        case 3:
            sound[i] = 0x33;
            break;
        }
    }
    sound[dq5::level::MirrorMessage::getRecord(index)->getCount() + 1] = 0x39;
    ui_MsgSndSet(sound);
    TownWindowSystem::getSingleton().openTalkMessage();
    dq5::level::FurnitureParam* param = dq5::level::FurnitureParam::getRecord(0x12);
    TownWindowSystem::getSingleton().addCommonMessage(param->checkMsg);
    TownWindowSystem::getSingleton().serialCommonMessage(dq5::level::MirrorMessage::getRecord(index)->message);
    return true;
}

THUMB int twn::TownFurnitureManager::getLeaderIndex()
{
    status::g_Party.setNormalMode();
    for (int i = 0; i < status::g_Party.getCarriageOutCount(); i++) {
        if (!status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath()) {
            return dq5::level::CharacterInitData::getRecord(status::g_Party.getPlayerStatus(i).getPlayerKindIndex())->talk1;
        }
    }
    return 0;
}
