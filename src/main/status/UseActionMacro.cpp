#include "main/status/UseActionMacro.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/status/UseItem.hpp"
#include "main/status/BaseActionStatus.hpp"
#include "main/status/CharacterStatus.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/text/TextAPI.hpp"
#include "main/dss/UnkRandom.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov001/town/TownFurniture.hpp"

inline int status::HaveStatus::getPlayerIndex() const
{
    return playerIndex_;
}

inline int status::HaveStatusInfo::getPlayerIndex() const
{
    return haveStatus_.getPlayerIndex();
}

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus()
{
    return haveBattleStatus_;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

int status::localizeTemp;

THUMB void status::UseActionMacro::setBeforeMacro(CharacterStatus* actor, int actionIndex)
{
    TextAPI::setMACRO0(0x11, 0x70000000, UseAction::getWordDBIndex(actionIndex));
}

THUMB void status::UseActionMacro::setExecMacro(CharacterStatus* actor, CharacterStatus* target, int actionIndex)
{
    TextAPI::setMACRO0(0x11, 0x70000000, UseAction::getWordDBIndex(actionIndex));
    if (actor->getHaveBattleStatus().getSelectCommand() == HaveBattleStatus::UseItem) {
        int itemIndex = actor->haveBattleStatus_.selectItemIndex_;
        TextAPI::setMACRO0(0xa, 0x40000000, itemIndex);
    }
    if (actionIndex == 0xf2) {
        TextAPI::setMACRO0(0xa, 0x40000000, 0x6f);
    }
    if (actionIndex == 0xea && target) {
        int monsterIndex = target->characterIndex_;
        TextAPI::setMACRO0(0xd, 0x60000000, monsterIndex);
    }
    if (actionIndex == 0x5a) {
        TextAPI::setMACRO0(4, 0x70000000, 0x5a);
    }
    if (actionIndex == 0x5b) {
        TextAPI::setMACRO0(4, 0x70000000, 0x5b);
    }
    if (actionIndex == 0x5d) {
        TextAPI::setMACRO0(4, 0x70000000, 0x5d);
    }
    if (actionIndex == 0xcc) {
        int index = 0;
        CommandType type = (CommandType)UseActionFlag::workParam_[0];
        switch (type) {
            case COMMAND_GANGANIKOUZE:
                index = 1;
                break;
            case COMMAND_BACCHIRIGANBARE:
                index = 2;
                break;
            case COMMAND_ORENIMAKASERO:
                index = 5;
                break;
            case COMMAND_JYUMONTUKAUNA:
                index = 3;
                break;
            case COMMAND_INOCHIDAIZINI:
                index = 4;
                break;
            case COMMAND_MEIREISASERO:
                index = 6;
                break;
        }
        TextAPI::setMACRO0(0x83, 0x90000000, index);
    }
    if (actionIndex >= 0x1b9 && actionIndex <= 0x1d3) {
        TextAPI::setMACRO0(0x11, 0x70000000, UseAction::getWordDBIndex(0x42));
    }
    if (actionIndex == 0x1ad) {
        g_Party.setBattleMode();
        int count = g_Party.getCarriageOutAliveCount();
        localizeTemp = g_Party.getPlayerStatus(UnkDssRand::rand(count)).haveStatusInfo_.haveStatus_.getPlayerIndex();
        TextAPI::setMACRO2(0x12, 0x50000000, localizeTemp);
    }
}

THUMB void status::UseActionMacro::setResultMacro(CharacterStatus* actor, CharacterStatus* target, int actionIndex)
{
    int targetEffectValue = 0;
    if (target) {
        targetEffectValue = target->haveStatusInfo_.effectValue_;
    }
    TextAPI::setMACRO0(0x12, 0x50000000, target->haveStatusInfo_.getPlayerIndex());
    switch (UseAction::getDamageType(actionIndex)) {
        case UseAction::DamageTypeRecovery:
            TextAPI::setMACRO0(0x4d, 0xf0000000, targetEffectValue);
            break;
        case UseAction::DamageTypeAddMp:
        case UseAction::DamageTypeSubMp:
            TextAPI::setMACRO0(0x51, 0xf0000000, targetEffectValue);
            break;
        case UseAction::DamageTypeDefenceChange:
            TextAPI::setMACRO0(0x52, 0xf0000000, targetEffectValue);
            break;
    }
    if (!actor->haveStatusInfo_.isActionEnableForMacro()) {
        return;
    }
    if (actionIndex == 0x47 && actor && actor->characterType_ == PLAYER) {
        int itemIndex = actor->haveStatusInfo_.haveEquipment_.getEquipment(ITEM_WEAPON, 0);
        TextAPI::setMACRO0(0xa, 0x40000000, itemIndex);
    }
    if (actionIndex == 0x69 && target) {
        int monsterIndex = g_Monster.getMonsterCallIndex();
        TextAPI::setMACRO0(0xd, 0x60000000, monsterIndex);
    }
    if (actionIndex == 0xea && target) {
        int monsterIndex = target->characterIndex_;
        TextAPI::setMACRO0(0xd, 0x60000000, monsterIndex);
    }
    if (actor->haveStatusInfo_.isWeaponAddDamage()) {
        actor->haveStatusInfo_.setWeaponAddDamage(false);
        int itemIndex = actor->haveStatusInfo_.haveEquipment_.getEquipment(ITEM_WEAPON, 0);
        TextAPI::setMACRO0(0xa, 0x40000000, itemIndex);
    }
    if (actionIndex == 0xfe) {
        int playerIndex = static_cast<MonsterStatus*>(target)->mosyasIndex_;
        TextAPI::setMACRO0(2, 0x50000000, playerIndex);
    }
    if (actionIndex == 0x29 || actionIndex == 0x2a || actionIndex == 0x2b || actionIndex == 0x2c) {
        TextAPI::setMACRO0(0x52, 0xf0000000, targetEffectValue);
    }
    if (actionIndex == 0xf6 || actionIndex == 0x143) {
        TextAPI::setMACRO0(0x17, 0xe0000000, 0x11c);
        TextAPI::setMACRO0(0x52, 0xf0000000, targetEffectValue);
    }
    if (actionIndex == 0xf7 || actionIndex == 0x145) {
        TextAPI::setMACRO0(0x17, 0xe0000000, 0xd9);
        TextAPI::setMACRO0(0x52, 0xf0000000, targetEffectValue);
    }
    if (actionIndex == 0xf8 || actionIndex == 0x146) {
        TextAPI::setMACRO0(0x17, 0xe0000000, 0xda);
        TextAPI::setMACRO0(0x52, 0xf0000000, targetEffectValue);
    }
    if (actionIndex == 0xf9 || actionIndex == 0x144) {
        TextAPI::setMACRO0(0x17, 0xe0000000, 0x11e);
        TextAPI::setMACRO0(0x52, 0xf0000000, targetEffectValue);
    }
    if (actionIndex == 0xfa || actionIndex == 0x147) {
        TextAPI::setMACRO0(0x17, 0xe0000000, 0x3dd);
        TextAPI::setMACRO0(0x4d, 0xf0000000, targetEffectValue);
    }
    if (actionIndex == 0xfb || actionIndex == 0x148) {
        TextAPI::setMACRO0(0x17, 0xe0000000, 0x3de);
        TextAPI::setMACRO0(0x51, 0xf0000000, targetEffectValue);
    }
    if (actionIndex == 0x8a && data_02101c88.isCurrentPart(4) == 1) {
        TextAPI::setMACRO0(0x3d, 0xf0000000, twn::TownFurnitureManager::getSingleton()->searchFloorItem());
    }
    if (actionIndex == 0x88 || actionIndex == 0x176) {
        TextAPI::setMACRO0(0x82, 0xc0000000, g_Global.getMapNameId());
    }
    if (actionIndex == 0x1b9) {
        TextAPI::setMACRO0(0xd, 0x60000000, UseActionFlag::workParam_[0]);
    }
    if (actionIndex == 0x1d1) {
        TextAPI::setMACRO0(0xd, 0x60000000, UseActionFlag::workParam_[0]);
    }
    if (actionIndex == 0x1c2) {
        int value = target->haveStatusInfo_.effectValue_;
        TextAPI::setMACRO2(0x2b, 0xf0000000, value);
    }
    if (actionIndex == 0x10c) {
        TextAPI::setMACRO0(0xd, 0x60000000, UseActionFlag::workParam_[0]);
    }
    if (actionIndex == 0x1c3) {
        TextAPI::setMACRO0(0xd, 0x60000000, UseActionFlag::workParam_[0]);
    }
    if (actionIndex == 0x19e) {
        int itemIndex = BaseActionStatus::work_;
        TextAPI::setMACRO0(0xa, 0x40000000, itemIndex);
        int value = UseItem::getEffect(itemIndex);
        TextAPI::setMACRO0(0x52, 0xf0000000, value);
    }
    if (actionIndex == 0x1ad) {
        TextAPI::setMACRO2(0x12, 0x50000000, localizeTemp);
    }
    if (actionIndex == 0x1eb) {
        int playerIndex = target->haveStatusInfo_.getPlayerIndex();
        TextAPI::setMACRO0(0x80, 0x50000000, playerIndex);
    }
    if (target->haveStatusInfo_.isLifeStoneEnable()) {
        target->haveStatusInfo_.setLifeStoneEnable(false);
        TextAPI::setMACRO0(0x80, 0x50000000, target->haveStatusInfo_.getPlayerIndex());
    }
}

THUMB void status::UseActionMacro::setAddMacro(CharacterStatus* actor, CharacterStatus* target, int actionIndex)
{
    if (actionIndex == 0x47 && actor->haveStatusInfo_.haveEquipment_.isEquipment(0x1d)) {
        int mp = actor->haveStatusInfo_.effectValue_;
        TextAPI::setMACRO0(0x51, 0xf0000000, mp);
    }
    if (target) {
        if (target->haveStatusInfo_.isAddEffectMahotora()) {
            int mp = target->haveStatusInfo_.addDamage_;
            TextAPI::setMACRO0(0x51, 0xf0000000, mp);
        }
        if (target->haveStatusInfo_.isAddMahotoraExecute()) {
            int mp = target->haveStatusInfo_.addDamage_;
            TextAPI::setMACRO0(0x51, 0xf0000000, mp);
        }
    }
    if (actionIndex == 0x1ad) {
        TextAPI::setMACRO2(0x12, 0x50000000, localizeTemp);
    }
}

THUMB void status::UseActionMacro::setStatusChangeMacro(CharacterStatus* actor)
{
    StatusChange& statusChange = actor->haveStatusInfo_.getStatusChange();
    dq5::level::ActionParam::ACTIONTYPE release = statusChange.isRelease();
    unsigned int actionIndex = statusChange.getActionIndex(release);
    TextAPI::setMACRO0(0x19, 0x70000000, actionIndex);
    if (actionIndex == 0x25) {
        TextAPI::setMACRO0(0x19, 0x70000000, 0x25);
    }
    if (actionIndex == 0x1d) {
        TextAPI::setMACRO0(0x19, 0x70000000, 0x1d);
    }
    if (actionIndex == 0xe4) {
        TextAPI::setMACRO0(0x19, 0x70000000, 0x1d);
    }
    if (actionIndex == 0xef) {
        TextAPI::setMACRO0(0x19, 0x70000000, 0x25);
    }
    if (actionIndex == 0x1d3) {
        TextAPI::setMACRO0(0x19, 0x70000000, 0x1f);
    }
}
