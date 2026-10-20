#pragma ipa file
#include "main/status/BaseActionStatus.hpp"
#include "main/status/ActionExecItem.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/btl/Encount.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/dss/UnkRandom.hpp"
#include "ov000/btl/BattleActorManager.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"

using namespace dq5::level;

int status::BaseActionStatus::actionIndex_;
int status::BaseActionStatus::effectValue_;
int status::BaseActionStatus::playerEffectValue_;
int status::BaseActionStatus::monsterEffectValue_;
dss::Flag status::BaseActionStatus::flag_;
int status::BaseActionStatus::work_;
int status::BaseActionStatus::eventBattle_;
int status::BaseActionStatus::execCallFriend_;
int status::BaseActionStatus::execCallKingSlime_;
int status::BaseActionStatus::mahokantaMessFlag_;
int status::BaseActionStatus::confusionMessFlag_;
int status::BaseActionStatus::sleepMessFlag_;
int status::BaseActionStatus::spazzMessFlag_;
int status::BaseActionStatus::baikirutoMessFlag_;
int status::BaseActionStatus::manusaMessFlag_;
int status::BaseActionStatus::mahotoneMessFlag_;
int status::BaseActionStatus::parameterDisable_;
int status::BaseActionStatus::dragoramMessFlag_;
int status::BaseActionStatus::poisonMessFlag_;
int status::BaseActionStatus::meganteDamage_;

inline bool status::HaveStatusInfo::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)haveStatus_.playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

inline btl::BattleMonster& btl::BattleMonsterDraw2::getMonster(int index)
{
    return monsters_[index];
}

inline void status::CharacterStatus::setCommandType(CommandType type)
{
    haveStatusInfo_.haveStatus_.command_ = type;
}

inline void btl::BattleActorManager::setDeathLog(int deathLog)
{
    deathLog_ = deathLog;
}

inline int btl::BattleActorManager::getDeathLog()
{
    return deathLog_;
}

THUMB void status::BaseActionStatus::clear()
{
    work_ = 0;
}

THUMB void status::BaseActionStatus::setEffectValue(int effectValue, int playerEffectValue, int monsterEffectValue)
{
    effectValue_ = effectValue;
    playerEffectValue_ = playerEffectValue;
    monsterEffectValue_ = monsterEffectValue;
}

THUMB int status::BaseActionStatus::getEffectValue(CharacterStatus* target)
{
    if (target->characterType_ == PLAYER) {
        return playerEffectValue_;
    }
    if (target->characterType_ == MONSTER) {
        return monsterEffectValue_;
    }
    return 0;
}

THUMB bool status::BaseActionStatus::actionTypeDamage(CharacterStatus* actor, CharacterStatus* target)
{
    bool ret = true;
    if (actionIndex_ == 0x52) {
        int value = target->haveStatusInfo_.getHp() * 80 / 100;
        value = value * target->haveStatusInfo_.actionDefence_.getEffectValueAI(0x18) / 1000;
        value = dss::clamp(value - 1, 0, 0x3ff);
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DEFENCE)) {
            value /= 2;
        }
        playerEffectValue_ = value;
        monsterEffectValue_ = value;
    }
    if (actionIndex_ == 0x1c7) {
        int damage = target->haveStatusInfo_.getHp() - 1;
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -damage);
        target->haveStatusInfo_.setDamage(true);
        target->haveStatusInfo_.setUseActionEffectValue(damage);
        target->haveStatusInfo_.setDamage(false);
        if (damage != 0) {
            target->setDamageAnimation();
        }
        if (damage == 0) {
            ret = false;
        }
        return ret;
    }
    if (actionIndex_ == 0x1c4) {
        int damage = target->haveStatusInfo_.getHp() / 2;
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -damage);
        target->haveStatusInfo_.setDamage(true);
        target->haveStatusInfo_.setUseActionEffectValue(damage);
        target->haveStatusInfo_.setDamage(false);
        target->setDamageAnimation();
        return true;
    }
    if (actionIndex_ == 0xb4 && target->characterType_ == MONSTER) {
        target->haveStatusInfo_.haveStatus_.setExp(0);
        target->haveStatusInfo_.haveStatus_.gold_ = 0;
    }
    if (actionIndex_ == 0x1c2) {
        int hp = target->haveStatusInfo_.getHp();
        int damage = hp * (UnkDssRand::rand(0x9c) + 100) / 128;
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -damage);
        target->haveStatusInfo_.setDamage(true);
        target->haveStatusInfo_.setUseActionEffectValue(damage);
        target->haveStatusInfo_.setDamage(false);
        if (!target->haveStatusInfo_.isDeath()) {
            target->haveStatusInfo_.statusChange_.setup(ActionParam::ACTIONTYPE_DORAGORAM, false);
            target->haveBattleStatus_.changeMonsterFromPlayer(0xcc);
        }
        if (damage != 0) {
            return true;
        }
        return false;
    }
    if (actionIndex_ == 0x18 || actionIndex_ == 0x1ec) {
        if (target->haveStatusInfo_.haveEquipment_.isEquipment(0x98)) {
            meganteDamage_ = 0;
            return false;
        }
        actor->haveStatusInfo_.setKillMyself(true);
        if (UnkDssRand::rand(2) == 0) {
            if (ActionExecItem::checkLifeStone(actionIndex_, actor, target)) {
                return true;
            }
            target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -0x3ff);
            target->haveStatusInfo_.setUseActionEffectValue(0);
            meganteDamage_ = 0;
        } else {
            short hp = target->haveStatusInfo_.getHp();
            short damage = hp - (short)(hp * 5 / 100 - 1);
            damage = dss::clamp<int>(damage, 1, 0x3ff);
            target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -damage);
            target->haveStatusInfo_.setDamage(true);
            target->haveStatusInfo_.setUseActionEffectValue(damage);
            target->haveStatusInfo_.setDamage(false);
            if (!target->haveStatusInfo_.isDeath()) {
                target->setDamageAnimation();
                meganteDamage_ = 1;
            } else {
                meganteDamage_ = 0;
                target->haveStatusInfo_.setUseActionEffectValue(0);
            }
        }
        if (target->characterType_ == MONSTER) {
            target->setDamageAnimation();
        }
        return true;
    }
    int damage = getEffectValue(target);
    if (damage != 0) {
        if (actionIndex_ == 0xf4 && target->haveBattleStatus_.metal_ != 0) {
            target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -1);
            target->haveStatusInfo_.setDamage(true);
            target->haveStatusInfo_.setUseActionEffectValue(1);
            target->haveStatusInfo_.setDamage(false);
            target->setDamageAnimation();
            return true;
        }
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -damage);
        target->haveStatusInfo_.setDamage(true);
        target->haveStatusInfo_.setUseActionEffectValue(damage);
        target->haveStatusInfo_.setDamage(false);
        target->setDamageAnimation();
        return true;
    }
    target->haveStatusInfo_.setUseActionEffectValue(0);
    return false;
}

THUMB bool status::BaseActionStatus::actionTypeRecovery(CharacterStatus* target)
{
    bool ret = false;
    if (target->haveStatusInfo_.getHp() < target->haveStatusInfo_.getHpMax()) {
        int value = getEffectValue(target);
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, value);
        target->haveStatusInfo_.setUseActionEffectValue(value);
        ret = true;
    } else {
        playerEffectValue_ = ret;
    }
    return ret;
}

THUMB void status::BaseActionStatus::actionTypeInstantDeath(CharacterStatus* target)
{
    getEffectValue(target);
    if (actionIndex_ == 0x1ec) {
        HaveStatusInfo::setGlbMeganteRing(false);
    }
    if (actionIndex_ == 0x1e0 && target->characterType_ == MONSTER) {
        characterClearOut(target, 0);
    }
    if (actionIndex_ == 0x1e4 && target->characterType_ == MONSTER) {
        characterClearOut(target, 0);
    }
    if (actionIndex_ == 0x1ce) {
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -0xffc);
        target->haveStatusInfo_.setUseActionEffectValue(0);
        target->haveStatusInfo_.haveStatus_.setExp(0);
        target->haveStatusInfo_.haveStatus_.gold_ = 0;
        target->setDeathAnimation();
        return;
    }
    if (!ActionExecItem::checkLifeStone(actionIndex_, 0, target)) {
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -0xffc);
        target->haveStatusInfo_.setUseActionEffectValue(0);
        target->setDeathAnimation();
        if (target->haveStatusInfo_.getHp() != 0) {
            target->clearDeathAnimation();
        }
    }
}

THUMB int status::BaseActionStatus::actionTypeRebirth(CharacterStatus* target)
{
    int ret = 0;
    bool flag = true;
    int value = 0x3ff;
    if (target->characterType_ == MONSTER) {
        int callFriend;
        int index = target->characterIndex_;
        int group = target->characterGroup_;
        int emptyGroup = ret;
        callFriend = btl::BattleMonsterDraw2::getSingleton().isCallFriend(index);
        flag = false;
        if (g_Monster.getMonsterCountInGroupAlive(0) == 0) {
            emptyGroup = 0;
            flag = true;
        } else if (g_Monster.getMonsterCountInGroupAlive(1) == 0) {
            emptyGroup = 1;
            flag = true;
        } else if (g_Monster.getMonsterCountInGroupAlive(2) == 0) {
            emptyGroup = 2;
            flag = true;
        } else if (g_Monster.getMonsterCountInGroupAlive(3) == 0) {
            emptyGroup = 3;
            flag = true;
        }
        if (callFriend && flag) {
            flag = true;
        } else {
            flag = false;
        }
        if (g_Monster.getMonsterCountInGroupAlive(group)) {
            int monsterIndex = g_Monster.getMonsterIndexInGroup(group);
            if (monsterIndex != index) {
                target->characterGroup_ = emptyGroup;
            }
        }
    }
    if (actionIndex_ == 0x3d || actionIndex_ == 0x7f || actionIndex_ == 0x130 || actionIndex_ == 0xe2) {
        if (UnkDssRand::rand(2) != 0) {
            target->haveStatusInfo_.setZaoraruFailed(true);
            return 0;
        }
        if (target->haveStatusInfo_.isDeath()) {
            if (target->haveStatusInfo_.getHpMax() == 1) {
                value = 1;
            } else {
                value = target->haveStatusInfo_.getHpMax() / 2;
            }
        }
    }
    if (actionIndex_ == 0x1d6) {
        if (target->haveStatusInfo_.isDeath()) {
            if (flag) {
                target->haveStatusInfo_.setMegazaruRebirth(true);
            }
        } else {
            target->haveStatusInfo_.setMegazaruRebirth(false);
        }
    }
    if (actionIndex_ == 0x1d4) {
        if (target->haveStatusInfo_.isDeath()) {
            target->haveStatusInfo_.setMegazaruRebirth(true);
            flag_.set(1);
        } else {
            flag_.set(2);
            target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, 0x3ff);
            target->haveStatusInfo_.setUseActionEffectValue(0x3ff);
            ret = 1;
        }
    }
    if (flag && target->haveStatusInfo_.isDeath()) {
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, value);
        target->haveStatusInfo_.setUseActionEffectValue(value);
        target->haveStatusInfo_.statusChange_.clear();
        target->haveStatusInfo_.rebirthFlag_ = 1;
        target->haveStatusInfo_.setStatusChangeRelease(true);
        target->haveStatusInfo_.setZaorikuRebirth(true);
        target->setRebirthAnimation();
        ret = 1;
        if (target->characterType_ == MONSTER) {
            if (data_02101c88.isCurrentPart(5)) {
                for (int i = 0; i < g_Monster.getCount(); i++) {
                    if (&g_Monster.getMonsterStatus(i) == target) {
                        int deathLog = btl::BattleActorManager::getSingleton()->getDeathLog();
                        if (deathLog & (1 << g_Monster.getCtrlId(i))) {
                            btl::BattleActorManager::getSingleton()->setDeathLog(deathLog ^ (1 << g_Monster.getCtrlId(i)));
                        }
                    }
                }
            }
            int ctrlId = btl::BattleMonsterDraw2::getSingleton().setup(target->characterGroup_, target->characterIndex_, false);
            btl::BattleMonsterDraw2::getSingleton().getMonster(ctrlId).startAnimation(0x21);
            btl::BattleMonsterDraw2::getSingleton().getMonster(ctrlId).setNextAnimationIndex(0);
            target->haveStatusInfo_.setDrawCtrlId(ctrlId);
            target->haveStatusInfo_.haveStatus_.resetExpGold();
        }
    }
    if (actionIndex_ == 0x1eb) {
        target->haveStatusInfo_.setStatusChangeRelease(false);
        target->haveStatusInfo_.setRebirthForRebirthStone(true);
        HaveStatusInfo::setGlbRebirthStone(false);
    }
    return ret;
}

THUMB bool status::BaseActionStatus::actionTypeAddMP(CharacterStatus* target)
{
    bool ret = false;
    if (target->haveStatusInfo_.getMp() < target->haveStatusInfo_.getMpMax()) {
        int value = getEffectValue(target);
        value = dss::clamp(value, 0, target->haveStatusInfo_.getMpMax() - target->haveStatusInfo_.getMp());
        target->haveStatusInfo_.addMpInBattle(HaveStatusInfo::ResultAction, value);
        target->haveStatusInfo_.setUseActionEffectValue(value);
        ret = true;
    }
    if (actionIndex_ == 0x1c6) {
        ret = true;
    }
    return ret;
}

THUMB bool status::BaseActionStatus::actionTypeSubMP(CharacterStatus* actor, CharacterStatus* target)
{
    bool ret = false;
    int value = getEffectValue(target);
    if (target->haveStatusInfo_.getMp() < value) {
        value = target->haveStatusInfo_.getMp();
    }
    if (value > 0) {
        target->haveStatusInfo_.addMpInBattle(HaveStatusInfo::ResultAction, -value);
        target->haveStatusInfo_.setUseActionEffectValue(value);
        ret = true;
    }
    if (actionIndex_ == 0x23) {
        if (target->haveStatusInfo_.getMpMax() != 0) {
            actor->haveStatusInfo_.addMpInBattle(HaveStatusInfo::ResultAction, value);
            actor->haveStatusInfo_.setUseActionEffectValue(value);
            ret = true;
        } else {
            ret = false;
        }
        if (actor == target) {
            ret = false;
        }
    }
    if (actionIndex_ == 0x1bc) {
        ret = true;
    }
    if (actionIndex_ == 0x1bd) {
        ret = true;
    }
    return ret;
}

THUMB bool status::BaseActionStatus::actionTypeStatusClear(CharacterStatus* target)
{
    bool ret = false;
    if (actionIndex_ == 0xf3 || actionIndex_ == 0x139) {
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DOKU)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_DOKU);
            ret = true;
        }
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MOUDOKU)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_MOUDOKU);
            ret = true;
        }
        if (!ret) {
            return false;
        }
    }
    if (actionIndex_ == 0xf5 || actionIndex_ == 0x13e) {
        if (!target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MAHI)) {
            return false;
        }
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MAHI)) {
            target->haveStatusInfo_.setStatusChangeRelease(true);
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_MAHI);
        }
    }
    if (actionIndex_ == 0x40 || actionIndex_ == 0x7e) {
        if (!target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DOKU) &&
            !target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MOUDOKU)) {
            return false;
        }
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DOKU)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_DOKU);
        }
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MOUDOKU)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_MOUDOKU);
        }
    }
    if (actionIndex_ == 0x41 || actionIndex_ == 0xe9) {
        if (!target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MAHI)) {
            return false;
        }
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MAHI)) {
            target->haveStatusInfo_.setStatusChangeRelease(true);
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_MAHI);
        }
    }
    if (actionIndex_ == 0x87) {
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE1)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_CURSE1);
            ret = true;
        }
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE2)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_CURSE2);
            ret = true;
        }
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE3)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_CURSE3);
            ret = true;
        }
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE4)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_CURSE4);
            ret = true;
        }
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE5)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_CURSE5);
            ret = true;
        }
        if (!ret) {
            return false;
        }
    }
    if (actionIndex_ == 0x69 || actionIndex_ == 0xea) {
        statusChangeRelease(target);
        target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_FIZZLEZONE);
    }
    if (actionIndex_ == 0xff) {
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_KONRAN)) {
            target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_KONRAN);
            target->haveStatusInfo_.setStatusChangeRelease(true);
        } else {
            return false;
        }
    }
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    return true;
}

THUMB int status::BaseActionStatus::actionTypeCallFriend(CharacterStatus* target)
{
    int ret = 0;
    if (actionIndex_ == 0xb5) {
        int index = target->characterIndex_;
        int group = target->characterGroup_;
        initCallMonster();
        ret = callDifferentMonster(group, index);
    }
    if (actionIndex_ == 0xb6) {
        int index = target->characterIndex_;
        int group = target->characterGroup_;
        initCallMonster();
        ret = callDifferentMonster(group, index);
        if (ret) {
            execCallFriend_ = 1;
        }
        target->haveStatusInfo_.statusChange_.setup(0x49, true);
    }
    if (actionIndex_ == 0xb7) {
        int index = target->characterIndex_;
        int group = target->characterGroup_;
        initCallMonster();
        ret = 0;
        while (true) {
            if (!callDifferentMonster(group, index)) {
                break;
            }
            setCallMonster(true);
            btl::BattleActorManager::getSingleton()->checkDeathMonster();
            ret++;
        }
        if (ret) {
            ret = 1;
        } else {
            ret = 0;
        }
    }
    if (actionIndex_ == 0xb8) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0x1e);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0x1e);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xb9) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0x27);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0x27);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xba) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0x1b);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0x1b);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xbb) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0x61);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0x61);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xbc) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0x67);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0x67);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xbd) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0x8c);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0x8c);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xbe) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0xb2);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0xb2);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xbf) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0xcf);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0xcf);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xc0) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0xae);
        ret |= callDifferentMonster(-1, 0xae);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0xae);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xc1) {
        initCallMonster();
        ret = callDifferentMonster(-1, 0xb7);
        ret |= callDifferentMonster(-1, 0xb7);
        if (ret) {
            int bookIndex = g_BattleResult.getMonsterBookIndex(0xb7);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    if (actionIndex_ == 0xc2) {
        int index = target->characterIndex_;
        int group = target->characterGroup_;
        ret = 0;
        if (btl::BattleMonsterDraw2::getSingleton().isCallFriend(index) && g_Monster.getCount() < 12) {
            setCallMonster(true);
            UseActionFlag::setCallFriend(true, group, index);
            ret = 1;
        }
    }
    if (actionIndex_ == 0xc3) {
        ret = 0;
        int group = g_Monster.getMonsterGroupForMonsterIndex(0x24);
        if (group == -1) {
            if (g_Monster.getMonsterCountInGroupAlive(0) == 0) {
                group = 0;
            } else if (g_Monster.getMonsterCountInGroupAlive(1) == 0) {
                group = 1;
            } else if (g_Monster.getMonsterCountInGroupAlive(2) == 0) {
                group = 2;
            } else if (g_Monster.getMonsterCountInGroupAlive(3) == 0) {
                group = 3;
            }
            if (group == -1) {
                return 0;
            }
        }
        if (btl::BattleMonsterDraw2::getSingleton().isCallFriend(0x24) && g_Monster.getCount() < 12) {
            setCallMonster(true);
            UseActionFlag::setCallFriend(true, group, 0x24);
            ret = 1;
            int bookIndex = g_BattleResult.getMonsterBookIndex(0x24);
            if (bookIndex != -1) {
                g_BattleResult.setMonsterEncount(bookIndex, true);
            }
        }
    }
    return ret;
}

THUMB bool status::BaseActionStatus::actionTypePartyReorder(CharacterStatus* target)
{
    if (actionIndex_ == 0xca || actionIndex_ == 0x1a3) {
        int targetIndex = 0;
        g_Party.setBattleMode();
        int count = g_Party.getCount();
        int i;
        for (i = 0; i < count; i++) {
            if (target == &g_Party.getPlayerStatus(i)) {
                targetIndex = i;
                break;
            }
        }
        int order[4] = {-1, -1, -1, -1};
        int* p = order;
        for (i = 0; i < count; i++) {
            if (!g_Party.isInsideCarriage(i) && i != targetIndex) {
                *p++ = i;
            }
        }
        g_Party.reorder(order[0], order[1], order[2], order[3]);
    }
    return true;
}

THUMB void status::BaseActionStatus::actionTypeChangeTactics()
{
    g_Party.setBattleMode();
    int count = g_Party.getCount();
    work_ = UseActionFlag::workParam_[0];
    for (int i = 0; i < count; i++) {
        if (g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.playerIndex_ != 1) {
            g_Party.getPlayerStatus(i).setCommandType((CommandType)work_);
        }
    }
}

THUMB bool status::BaseActionStatus::actionTypeDisappear(CharacterStatus* target)
{
    characterClearOut(target, 0);
    return true;
}

THUMB bool status::BaseActionStatus::actionTypeAddStrength(CharacterStatus* target)
{
    parameterDisable_ = 0;
    bool ret = true;
    if (!target->haveStatusInfo_.isPlayer()) {
        ret = false;
    } else {
        int strength = target->haveStatusInfo_.haveStatus_.baseStatus_.strength_;
        if (strength != 0xff) {
            if (playerEffectValue_ + strength > 0xff) {
                playerEffectValue_ = 0xff - strength;
            }
            target->haveStatusInfo_.haveStatus_.addStrength(playerEffectValue_);
            target->haveStatusInfo_.setUseActionEffectValue(playerEffectValue_);
        } else {
            ret = false;
            parameterDisable_ = 1;
        }
    }
    return ret;
}

THUMB bool status::BaseActionStatus::actionTypeAddAgility(CharacterStatus* target)
{
    parameterDisable_ = 0;
    bool ret = true;
    if (!target->haveStatusInfo_.isPlayer()) {
        ret = false;
    } else if (target->haveStatusInfo_.haveStatus_.getAgility() != 0xff) {
        if (playerEffectValue_ + target->haveStatusInfo_.haveStatus_.getAgility() > 0xff) {
            playerEffectValue_ = 0xff - target->haveStatusInfo_.haveStatus_.getAgility();
        }
        target->haveStatusInfo_.haveStatus_.addAgility(playerEffectValue_);
        target->haveStatusInfo_.setUseActionEffectValue(playerEffectValue_);
    } else {
        ret = false;
        parameterDisable_ = 1;
    }
    return ret;
}

THUMB bool status::BaseActionStatus::actionTypeAddProtection(CharacterStatus* target)
{
    parameterDisable_ = 0;
    bool ret = true;
    if (!target->haveStatusInfo_.isPlayer()) {
        ret = false;
    } else {
        int protection = target->haveStatusInfo_.haveStatus_.baseStatus_.protection_;
        if (protection != 0xff) {
            if (playerEffectValue_ + protection > 0xff) {
                playerEffectValue_ = 0xff - protection;
            }
            target->haveStatusInfo_.haveStatus_.addProtection(playerEffectValue_);
            target->haveStatusInfo_.setUseActionEffectValue(playerEffectValue_);
        } else {
            ret = false;
            parameterDisable_ = 1;
        }
    }
    return ret;
}

THUMB bool status::BaseActionStatus::actionTypeAddWisdom(CharacterStatus* target)
{
    parameterDisable_ = 0;
    bool ret = true;
    if (!target->haveStatusInfo_.isPlayer()) {
        ret = false;
    } else if (target->haveStatusInfo_.haveStatus_.getWisdom() != 0xff) {
        if (playerEffectValue_ + target->haveStatusInfo_.haveStatus_.getWisdom() > 0xff) {
            playerEffectValue_ = 0xff - target->haveStatusInfo_.haveStatus_.getWisdom();
        }
        target->haveStatusInfo_.haveStatus_.addWisdom(playerEffectValue_);
        target->haveStatusInfo_.setUseActionEffectValue(playerEffectValue_);
    } else {
        ret = false;
        parameterDisable_ = 1;
    }
    return ret;
}

THUMB bool status::BaseActionStatus::actionTypeAddMaxHp(CharacterStatus* target)
{
    parameterDisable_ = 0;
    bool ret = true;
    if (!target->haveStatusInfo_.isPlayer()) {
        ret = false;
    } else if (target->haveStatusInfo_.haveStatus_.getHpMax() != 999) {
        if (playerEffectValue_ + target->haveStatusInfo_.haveStatus_.getHpMax() > 999) {
            playerEffectValue_ = 999 - target->haveStatusInfo_.haveStatus_.getHpMax();
        }
        target->haveStatusInfo_.addHpMax((char)playerEffectValue_);
        target->haveStatusInfo_.setUseActionEffectValue(playerEffectValue_);
    } else {
        ret = false;
        parameterDisable_ = 1;
    }
    return ret;
}

THUMB bool status::BaseActionStatus::actionTypeAddMaxMp(CharacterStatus* target)
{
    parameterDisable_ = 0;
    bool ret = true;
    if (!target->haveStatusInfo_.isPlayer()) {
        ret = false;
    } else if (target->haveStatusInfo_.haveStatus_.getMpMax() != 999 && target->haveStatusInfo_.haveStatus_.getMpMax() != 0) {
        if (playerEffectValue_ + target->haveStatusInfo_.haveStatus_.getMpMax() > 999) {
            playerEffectValue_ = 999 - target->haveStatusInfo_.haveStatus_.getMpMax();
        }
        target->haveStatusInfo_.haveStatus_.addMpMax(playerEffectValue_);
        target->haveStatusInfo_.setUseActionEffectValue(playerEffectValue_);
    } else {
        ret = false;
        parameterDisable_ = 1;
    }
    return ret;
}

THUMB void status::BaseActionStatus::actionTypeAstoron(CharacterStatus* target)
{
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    if (target->characterType_ == PLAYER) {
        target->haveStatusInfo_.statusChange_.setTurn(ActionParam::ACTIONTYPE_ASTORON, 3);
    }
    if (target->characterType_ == MONSTER) {
        target->haveStatusInfo_.statusChange_.setTurn(ActionParam::ACTIONTYPE_ASTORON, 4);
    }
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    target->haveStatusInfo_.setAstoron(true);
    int drawCtrlId = target->haveStatusInfo_.drawCtrlId_;
    btl::BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setPaletteAstoron(1);
}

THUMB bool status::BaseActionStatus::actionTypeSpazz(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DEFENCE)) {
        target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_DEFENCE);
        int drawCtrlId = target->haveStatusInfo_.drawCtrlId_;
        btl::BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0x10);
        btl::BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setNextAnimationIndex(0);
    }
    if (target->haveStatusInfo_.isCloseDoor() && target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CLOSEDOOR)) {
        target->haveStatusInfo_.setCloseDoor(false);
        target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_CLOSEDOOR);
    }
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MAHI)) {
        spazzMessFlag_ = 1;
        work_ = target->haveStatusInfo_.statusChange_.getAgainEnableMessage(ActionParam::ACTIONTYPE_MAHI);
        return true;
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    return true;
}

THUMB bool status::BaseActionStatus::actionTypeSleep(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DEFENCE)) {
        target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_DEFENCE);
        int drawCtrlId = target->haveStatusInfo_.drawCtrlId_;
        btl::BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0x10);
        btl::BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setNextAnimationIndex(0);
    }
    if (target->haveStatusInfo_.isCloseDoor() && target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CLOSEDOOR)) {
        target->haveStatusInfo_.setCloseDoor(false);
        target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_CLOSEDOOR);
    }
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_NEMURI)) {
        sleepMessFlag_ = 1;
        work_ = target->haveStatusInfo_.statusChange_.getAgainEnableMessage(ActionParam::ACTIONTYPE_NEMURI);
    }
    if (!target->haveStatusInfo_.statusChange_.setup(actionIndex_, true)) {
        return false;
    }
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    return true;
}

THUMB void status::BaseActionStatus::actionTypeManusa(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MANUSA)) {
        target->haveStatusInfo_.setManusaAlready(true);
        if (actionIndex_ == target->haveStatusInfo_.statusChange_.getActionIndex(ActionParam::ACTIONTYPE_MANUSA)) {
            manusaMessFlag_ = 1;
            work_ = target->haveStatusInfo_.statusChange_.getAgainEnableMessage(ActionParam::ACTIONTYPE_MANUSA);
        }
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

THUMB bool status::BaseActionStatus::actionTypeBaikiruto(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_BAIKIRUTO)) {
        baikirutoMessFlag_ = 1;
        if (actionIndex_ == target->haveStatusInfo_.statusChange_.getActionIndex(ActionParam::ACTIONTYPE_BAIKIRUTO)) {
            work_ = target->haveStatusInfo_.statusChange_.getAgainDisableMessage(ActionParam::ACTIONTYPE_BAIKIRUTO);
            return false;
        }
        work_ = 0xc3ad0;
        if (target->haveStatusInfo_.statusChange_.getActionIndex(ActionParam::ACTIONTYPE_BAIKIRUTO) != 0x2e && actionIndex_ == 0x2e) {
            work_ = 0xc3b41;
        }
        return false;
    }
    target->haveStatusInfo_.setAttackChange();
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    return true;
}

THUMB bool status::BaseActionStatus::actionTypeDefenceChange(CharacterStatus* target)
{
    if (!target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DF_HENKA)) {
        target->haveStatusInfo_.clearDefenceChange();
    }
    short change = target->haveStatusInfo_.setDefenceChange(actionIndex_);
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    if (change != 0) {
        target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
        target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
        target->haveStatusInfo_.setUseActionEffectValue(dss::abs(change));
        return true;
    }
    return false;
}

THUMB void status::BaseActionStatus::actionTypeEerieLight(CharacterStatus* target)
{
    target->haveStatusInfo_.actionDefence_.disable_ = 1;
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
}

THUMB void status::BaseActionStatus::actionTypeFubaha(CharacterStatus* target)
{
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

THUMB void status::BaseActionStatus::actionTypeMahokanta(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MAHOKANTA)) {
        mahokantaMessFlag_ = 1;
        work_ = target->haveStatusInfo_.statusChange_.getAgainEnableMessage(ActionParam::ACTIONTYPE_MAHOKANTA);
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

THUMB bool status::BaseActionStatus::actionTypeMosyas(CharacterStatus* actor, CharacterStatus* target)
{
    if (target->haveStatusInfo_.isMosyasTarget()) {
        return false;
    }
    actor->haveStatusInfo_.setDisableTextureCache(true);
    actor->setMosyasChange(target);
    actor->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    ((MonsterStatus*)actor)->mosyasIndex_ = target->haveStatusInfo_.haveStatus_.playerIndex_;
    actor->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    actor->haveStatusInfo_.setMosyasStart(true);
    return true;
}

THUMB void status::BaseActionStatus::actionTypePowerSave(CharacterStatus* target)
{
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
}

THUMB void status::BaseActionStatus::actionTypeMahoton(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MAHOTON)) {
        mahotoneMessFlag_ = 1;
        work_ = target->haveStatusInfo_.statusChange_.getAgainEnableMessage(ActionParam::ACTIONTYPE_MAHOTON);
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

THUMB void status::BaseActionStatus::actionTypeDragoram(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DORAGORAM)) {
        dragoramMessFlag_ = 1;
        return;
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    target->haveBattleStatus_.changeMonsterFromPlayer(0xcb);
}

THUMB void status::BaseActionStatus::actionTypeConfusion(CharacterStatus* target)
{
    if (target->haveStatusInfo_.isCloseDoor() && target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CLOSEDOOR)) {
        target->haveStatusInfo_.setCloseDoor(false);
        target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_CLOSEDOOR);
    }
    confusionMessFlag_ = 0;
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_KONRAN)) {
        confusionMessFlag_ = 1;
        work_ = target->haveStatusInfo_.statusChange_.getAgainEnableMessage(ActionParam::ACTIONTYPE_KONRAN);
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

THUMB void status::BaseActionStatus::actionTypePath1(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DEFENCE)) {
        target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_DEFENCE);
        int drawCtrlId = target->haveStatusInfo_.drawCtrlId_;
        btl::BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).startAnimation(0x10);
        btl::BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setNextAnimationIndex(0);
    }
    if (target->haveStatusInfo_.isCloseDoor() && target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CLOSEDOOR)) {
        target->haveStatusInfo_.setCloseDoor(false);
        target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_CLOSEDOOR);
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

THUMB void status::BaseActionStatus::actionTypePoison(CharacterStatus* target)
{
    poisonMessFlag_ = 0;
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MOUDOKU)) {
        poisonMessFlag_ = 1;
        work_ = 0xc3b15;
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

THUMB void status::BaseActionStatus::actionTypeCloseDoor(CharacterStatus* target)
{
    target->haveStatusInfo_.setCloseDoor(true);
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

THUMB bool status::BaseActionStatus::actionTypeCurse1(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE1)) {
        return false;
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    return true;
}

THUMB bool status::BaseActionStatus::actionTypeCurse2(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE2)) {
        return false;
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    return true;
}

THUMB bool status::BaseActionStatus::actionTypeCurse3(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE3)) {
        return false;
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    return true;
}

THUMB bool status::BaseActionStatus::actionTypeCurse4(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE4)) {
        return false;
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    return true;
}

THUMB bool status::BaseActionStatus::actionTypeCurse5(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_CURSE5)) {
        return false;
    }
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
    return true;
}

THUMB void status::BaseActionStatus::actionTypeMahokite(CharacterStatus* target)
{
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

THUMB void status::BaseActionStatus::actionTypeDefence(CharacterStatus* target)
{
    target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
}

THUMB void status::BaseActionStatus::actionTypeFizzleZone(CharacterStatus* target)
{
    statusChangeRelease(target);
    target->haveStatusInfo_.statusChange_.setup(ActionParam::ACTIONTYPE_FIZZLEZONE, false);
    target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
    target->haveStatusInfo_.setUseActionEffectValue(0);
}

inline void status::StatusChange::setCharacterTypeForTimeStop(CharacterType type)
{
    characterTypeForTimeStop_ = type;
}

THUMB void status::BaseActionStatus::actionTypeTimeStop(CharacterStatus* target)
{
    if (target->characterType_ == PLAYER) {
        target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
        target->haveStatusInfo_.statusChange_.setCharacterTypeForTimeStop(MONSTER);
    } else {
        target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
        target->haveStatusInfo_.statusChange_.setCharacterTypeForTimeStop(PLAYER);
    }
}

THUMB bool status::BaseActionStatus::actionTypeToherosu(CharacterStatus* target)
{
    if (isExecToherosu()) {
        target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA);
        target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
        return true;
    }
    return false;
}

THUMB bool status::BaseActionStatus::actionTypeSinobiasi(CharacterStatus* target)
{
    if (g_StageAttribute.isEncount()) {
        target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_NORMAL_MAMONONOESA);
        target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
        return true;
    }
    return false;
}

THUMB bool status::BaseActionStatus::actionTypeMonstersFood(CharacterStatus* target)
{
    if (g_StageAttribute.isEncount()) {
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_TOHEROSU)) {
            return true;
        }
        target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_SINOBIASI);
        target->haveStatusInfo_.statusChange_.setup(actionIndex_, true);
        return true;
    }
    return false;
}

THUMB bool status::BaseActionStatus::actionTypeMsgOnly(CharacterStatus* target)
{
    if (actionIndex_ == 0x19f) {
        g_Party.setBattleMode();
        int count = g_Party.getCount();
        int order[4] = {-1, -1, -1, -1};
        int i;
        int* p = order;
        for (i = 0; i < count; i++) {
            *p = i;
            if (target->haveStatusInfo_.haveStatus_.playerIndex_ == g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.playerIndex_) {
                order[0] = i;
                order[i] = 0;
                break;
            }
            p++;
        }
        g_Party.reorder(order[0], order[1], order[2], order[3]);
        return true;
    }
    return false;
}

THUMB bool status::BaseActionStatus::actionTypeMsgSuccess()
{
    return true;
}

THUMB bool status::BaseActionStatus::actionTypeMsgFailed()
{
    return false;
}

THUMB void status::BaseActionStatus::statusChangeRelease(CharacterStatus* target)
{
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MOSYASU)) {
        target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_MOSYASU);
        target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
        target->setMosyasRelease();
        target->haveStatusInfo_.setStatusChangeRelease(true);
    }
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_DORAGORAM)) {
        target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_DORAGORAM);
        target->haveBattleStatus_.changeMonsterReverse();
        target->haveStatusInfo_.setStatusChangeRelease(true);
    }
    if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_ASTORON)) {
        target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_ASTORON);
        target->haveStatusInfo_.setStatusChangeRelease(true);
        int drawCtrlId = target->haveStatusInfo_.drawCtrlId_;
        btl::BattleMonsterDraw2::getSingleton().getMonster(drawCtrlId).setPaletteAstoron(0);
    }
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_BUKIMINAHIKARI);
    target->haveStatusInfo_.actionDefence_.disable_ = 0;
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_MAHOKITE);
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_MAHOKANTA);
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_DF_HENKA);
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_FUBAHA);
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_BAIKIRUTO);
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_MOSYASU);
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_MAHOTON);
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_MANUSA);
    target->haveStatusInfo_.statusChange_.cleanup(ActionParam::ACTIONTYPE_DORAGORAM);
}

THUMB int status::BaseActionStatus::actionTypeNone(CharacterStatus* actor, CharacterStatus* target)
{
    int ret = 1;
    signed char value = playerEffectValue_;
    if (actionIndex_ == 0x157) {
        ret = 0;
    }
    if (actionIndex_ == 0x125) {
        ret = 0;
    }
    if (actionIndex_ == 0x156) {
        ret = 0;
    }
    if (actionIndex_ == 0x119) {
        ret = 0;
    }
    if (actionIndex_ == 0xbe) {
        ret = 0;
    }
    if (actionIndex_ == 0x1b9 && target->characterType_ == MONSTER) {
        characterClearOut(target, 0);
    }
    if (actionIndex_ == 0x1ba) {
        target->haveStatusInfo_.setAllKaishin(true);
    }
    if (actionIndex_ == 0x1c3 && target->characterType_ == MONSTER) {
        characterClearOut(target, 0);
    }
    if (actionIndex_ == 0x1c5 && target->characterType_ == MONSTER) {
        characterClearOut(target, 0);
    }
    if (actionIndex_ == 0x1ce && target->characterType_ == MONSTER) {
        characterClearOut(target, 0);
    }
    if (actionIndex_ == 0x1c8) {
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -value);
        target->haveStatusInfo_.setDamage(true);
        target->haveStatusInfo_.setUseActionEffectValue(value);
        target->haveStatusInfo_.setDamage(false);
    }
    if (actionIndex_ == 0x1d4) {
        if (target->haveStatusInfo_.isDeath()) {
            target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, 0x3ff);
            target->haveStatusInfo_.rebirthFlag_ = 1;
            target->setRebirthAnimation();
            target->haveStatusInfo_.setStatusChangeRelease(true);
        } else {
            target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, 0x3ff);
        }
    }
    if (actionIndex_ == 0x9e) {
        execCallKingSlime_ = 1;
    }
    if (actionIndex_ == 0x3f) {
        int flag = 1;
        if (target == 0) {
            return flag;
        }
        if (target->characterType_ == MONSTER) {
            int callFriend = btl::BattleMonsterDraw2::getSingleton().isCallFriend(target->characterIndex_);
            flag = 0;
            if (g_Monster.getMonsterCountInGroupAlive(0) == 0) {
                flag = 1;
            } else if (g_Monster.getMonsterCountInGroupAlive(1) == 0) {
                flag = 1;
            } else if (g_Monster.getMonsterCountInGroupAlive(2) == 0) {
                flag = 1;
            } else if (g_Monster.getMonsterCountInGroupAlive(3) == 0) {
                flag = 1;
            }
            if (callFriend && flag) {
                flag = 1;
            } else {
                flag = 0;
                ret = flag;
            }
        }
        flag_.set(4);
        if (target->haveStatusInfo_.isDeath()) {
            flag_.set(1);
            target->haveStatusInfo_.setStatusChangeRelease(1);
            target->haveStatusInfo_.setMegazaruRebirth(true);
        } else {
            flag_.set(2);
            target->haveStatusInfo_.setMegazaruRecovery(true);
        }
        if (flag) {
            target->haveStatusInfo_.getHp();
            target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, 0x3ff);
            target->haveStatusInfo_.rebirthFlag_ = 1;
            if (actor->characterType_ == MONSTER) {
                actor->haveStatusInfo_.haveStatus_.setExp(0);
                actor->haveStatusInfo_.haveStatus_.gold_ = 0;
            }
            ret = 1;
            if (target->characterType_ == MONSTER && target->haveStatusInfo_.isMegazaruRebirth()) {
                int ctrlId = btl::BattleMonsterDraw2::getSingleton().setup(target->characterGroup_, target->characterIndex_, false);
                btl::BattleMonsterDraw2::getSingleton().getMonster(ctrlId).startAnimation(0x21);
                btl::BattleMonsterDraw2::getSingleton().getMonster(ctrlId).setNextAnimationIndex(0);
                target->haveStatusInfo_.setDrawCtrlId(ctrlId);
                target->haveStatusInfo_.haveStatus_.resetExpGold();
                target->setRebirthAnimation();
            }
        } else if (!target->haveStatusInfo_.isDeath()) {
            target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, 0x3ff);
            ret = 1;
        } else {
            target->haveStatusInfo_.setRebirthFailed(true);
        }
    }
    if (actionIndex_ == 0x82) {
        ret = isExecRiremito();
        if (ret) {
            PartyStatusUtility::resetForceReorderMember();
        }
    }
    if (actionIndex_ == 0x81 || actionIndex_ == 0x11e) {
        ret = isExecRula();
    }
    if (actionIndex_ == 0x13b || actionIndex_ == 0x137) {
        if (isExecRula() == 1) {
            if (g_StageInfo.kimeraSymbol_ == 0) {
                ret = 0;
            } else {
                ret = 1;
            }
        } else {
            ret = 0;
        }
    }
    if (actionIndex_ == 0x86) {
        if (data_02101c88.isCurrentPart(4)) {
            ret = isExecLanaruta();
        } else if (data_02101c88.isCurrentPart(6)) {
            if (!g_StageAttribute.isLanaruta() || g_StageAttribute.isLanarutaDisable() || g_StageAttribute.timestop_ != 0) {
                ret = 0;
            } else {
                ret = 1;
            }
        }
        if (ret) {
            PartyStatusUtility::resetForceReorderMember();
        }
    }
    if (actionIndex_ == 0x14b) {
        ret = 0;
        if (g_StageInfo.getTimeZone() != 4) {
            if (data_02101c88.isCurrentPart(4)) {
                if (isExecLanaruta() && g_StageAttribute.getYami()) {
                    ret = 1;
                }
            } else if (data_02101c88.isCurrentPart(6)) {
                if (!g_StageAttribute.isLanaruta() || g_StageAttribute.isLanarutaDisable() || g_StageAttribute.timestop_ != 0 ||
                    !g_StageAttribute.getYami()) {
                    ret = 0;
                } else {
                    ret = 1;
                }
            }
            if (ret) {
                PartyStatusUtility::resetForceReorderMember();
            }
        }
    }
    if (actionIndex_ == 0x84) {
        if (isExecImpas()) {
            ret = 1;
        } else {
            ret = 0;
        }
    }
    if (actionIndex_ == 0x85) {
        StageAttribute::setToramana(1);
    }
    if (actionIndex_ == 0x120 || actionIndex_ == 0x126) {
        ret = 0;
        if (data_02101c88.isCurrentPart(6) == 1 && g_Global.getFieldType() == 0) {
            ret = fld::FieldPlayerManager::getSingleton().player_.fieldActionCarpet_.isCarpetGetOnOffAttr();
        }
    }
    if (actionIndex_ == 0x88 || actionIndex_ == 0x176) {
        ret = isExecFloomi();
    }
    if (actionIndex_ == 0x8a) {
        if (!data_02101c88.isCurrentPart(4)) {
            ret = 0;
        } else if (!twn::TownFurnitureManager::getSingleton()->searchFloorItem()) {
            ret = 0;
        }
    }
    if (actionIndex_ == 0x8b) {
        if (g_StageAttribute.isEncount() && btl::Encount::getSingleton()->enable_) {
            if (data_02101c88.isCurrentPart(4)) {
                if (!twn::TownPlayerManager::getSingleton().isSaveAndBattleOK()) {
                    ret = 0;
                } else {
                    btl::Encount::getSingleton()->forceEncount();
                    ret = 1;
                }
            } else {
                btl::Encount::getSingleton()->forceEncount();
                ret = 1;
            }
        } else {
            ret = 0;
        }
    }
    if (actionIndex_ == 0xfe) {
        if (target->haveStatusInfo_.statusChange_.isEnable(ActionParam::ACTIONTYPE_MOSYASU)) {
            target->haveStatusInfo_.statusChange_.release(ActionParam::ACTIONTYPE_MOSYASU);
            target->haveStatusInfo_.setStatusChangeInBattle(HaveStatusInfo::ResultAction);
            target->setMosyasRelease();
            target->haveStatusInfo_.setStatusChangeRelease(true);
            actor->haveStatusInfo_.setDisableTextureCache(true);
        } else {
            ret = 0;
        }
    }
    if (actionIndex_ == 0x119) {
        ret = 0;
    }
    if (actionIndex_ == 0xdb) {
        ret = 0;
    }
    if (actionIndex_ == 0xdc) {
        ret = 0;
    }
    if ((actionIndex_ == 0x48 || actionIndex_ == 0x1a6) && actor->characterType_ == MONSTER) {
        characterClearOut(actor, 0);
        if (actor->haveStatusInfo_.isDeath()) {
            actor->haveStatusInfo_.setDisappearFlag(false);
            actor->haveStatusInfo_.setEscapeFlag(true);
            actor->haveBattleStatus_.escape_ = 1;
            actor->setEscapeAnimation();
        }
        if (actionIndex_ == 0x48) {
            actor->haveStatusInfo_.setActionDisable(true);
        }
    }
    if (actionIndex_ == 0x19e) {
        work_ = actor->haveStatusInfo_.haveEquipment_.getEquipment(ITEM_ARMOR, 0);
        actor->haveStatusInfo_.resetEquipment(ITEM_ARMOR);
    }
    if (actionIndex_ == 0x19f) {
        g_Party.setBattleMode();
        int count = g_Party.getCarriageOutCount();
        int index[4] = {-1, -1, -1, -1};
        int* p = index;
        int i;
        for (i = 0; i < count; i++) {
            *p++ = i;
        }
        int order[4] = {-1, -1, -1, -1};
        for (i = 0; i < count; i++) {
            if (actor->haveStatusInfo_.haveStatus_.playerIndex_ == g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.playerIndex_) {
                switch (i) {
                    case 0:
                        order[0] = index[0];
                        order[1] = index[1];
                        order[2] = index[2];
                        order[3] = index[3];
                        break;
                    case 1:
                        order[0] = index[1];
                        order[1] = index[0];
                        order[2] = index[2];
                        order[3] = index[3];
                        break;
                    case 2:
                        order[0] = index[2];
                        order[1] = index[0];
                        order[2] = index[1];
                        order[3] = index[3];
                        break;
                    case 3:
                        order[0] = index[3];
                        order[1] = index[0];
                        order[2] = index[1];
                        order[3] = index[2];
                        break;
                }
                break;
            }
        }
        g_Party.reorder(order[0], order[1], order[2], order[3]);
    }
    if (actionIndex_ == 0x1aa) {
        target->haveStatusInfo_.statusChange_.setup(ActionParam::ACTIONTYPE_MAHI, true);
    }
    if (actionIndex_ == 0x1a4) {
        int damage = UnkDssRand::rand(3) + 4;
        actor->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -damage);
        actor->haveStatusInfo_.setDamage(true);
        actor->haveStatusInfo_.setUseActionEffectValue(damage);
        actor->haveStatusInfo_.setDamage(false);
    }
    if (actionIndex_ == 0x1de) {
        int damage = getEffectValue(target);
        actor->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -damage);
        actor->haveStatusInfo_.setDamage(true);
        actor->haveStatusInfo_.setUseActionEffectValue(damage);
        actor->haveStatusInfo_.setDamage(false);
    }
    return ret;
}

THUMB void status::BaseActionStatus::characterClearOut(CharacterStatus* target, int drop)
{
    if (drop == 1) {
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -0x3ff);
        target->haveStatusInfo_.setUseActionEffectValue(0);
    } else if (drop == 2) {
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -0x3ff);
        target->haveStatusInfo_.haveStatus_.setExp(0);
        target->haveStatusInfo_.setUseActionEffectValue(0);
    } else {
        target->haveStatusInfo_.addHpInBattle(HaveStatusInfo::ResultAction, -0x3ff);
        target->haveStatusInfo_.haveStatus_.setExp(0);
        target->haveStatusInfo_.haveStatus_.gold_ = 0;
        target->haveStatusInfo_.setUseActionEffectValue(0);
    }
    if (target->haveStatusInfo_.isDeath()) {
        target->haveStatusInfo_.setDisappearFlag(true);
        target->setDisappearAnimation();
    }
}

THUMB void status::BaseActionStatus::setMpZero(bool flag)
{
    if (flag) {
        flag_.set(FLAG_MP_ZERO);
    } else {
        flag_.remove(FLAG_MP_ZERO);
    }
}

THUMB bool status::BaseActionStatus::isMpZero()
{
    return flag_.check(FLAG_MP_ZERO);
}

// unreferenced (dead-stripped by the linker); keeps eventBattle_ in this TU's static data list
THUMB void unkfunc_unused_15()
{
    status::BaseActionStatus::eventBattle_ = 0;
}
