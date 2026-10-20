#include "main/status/ExtraAction.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/dss/UnkRandom.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment()
{
    return haveEquipment_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline CharacterType status::CharacterStatus::getCharacterType()
{
    return characterType_;
}

THUMB bool status::isNormalAttack(int actionIndex)
{
    if (actionIndex == 0x47) {
        return true;
    }
    return false;
}

THUMB bool status::isNormalAttackForSE(int actionIndex)
{
    if (actionIndex == 0x47) {
        return true;
    }
    if (actionIndex == 0x191) {
        return true;
    }
    if (actionIndex == 0x192) {
        return true;
    }
    if (actionIndex == 0x1F3) {
        return true;
    }
    return false;
}

THUMB bool status::isDoubleAction(status::CharacterStatus* actor, int actionIndex)
{
    if (actor == 0) {
        return false;
    }
    if (UseAction::isMultiF(actionIndex)) {
        if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x11)) {
            return true;
        }
        if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x34)) {
            return true;
        }
        if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x102)) {
            return true;
        }
        if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x103)) {
            return true;
        }
    }
    return false;
}

THUMB bool status::isMultiTargetEquipment(status::CharacterStatus* actor)
{
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x17)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x35)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x36)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x37)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x38)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x3B)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x39)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x3A)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x3B)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x3C)) {
        return true;
    }
    return actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x3D) != false;
}

THUMB bool status::isGroupTargetEquipment(status::CharacterStatus* actor)
{
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x38)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x3B)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x39)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x3A)) {
        return true;
    }
    return actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x3C) != false;
}

THUMB bool status::isAllTargetEquipment(status::CharacterStatus* actor)
{
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x17)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x35)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x36)) {
        return true;
    }
    if (actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x37)) {
        return true;
    }
    return actor->getHaveStatusInfo().getHaveEquipment().isEquipment(0x3D) != false;
}

THUMB int status::getUsuallyAttackEffectValue(status::CharacterStatus* actor, status::CharacterStatus* target)
{
    int AT = actor->getHaveStatusInfo().getAttack(0);
    int DF = target->getHaveStatusInfo().getDefence(0);
    int DM = (AT - DF / 2) / 2;
    int X = 0;

    if (DM <= 0) {
        X = UnkDssRand::rand(2);
    } else {
        if (target->getCharacterType() == PLAYER) {
            if (DM <= AT / 12) {
                X = UnkDssRand::rand(AT / 12);
            } else if (DM < 8) {
                X = DM - 1 + UnkDssRand::rand(3);
            } else {
                X = ((DM * 700) / 8 + (UnkDssRand::rand(256) * ((DM * 100) / 4 + 100)) / 256) / 100;
            }
        }
        if (target->getCharacterType() == MONSTER) {
            if (DM < 8) {
                X = DM - 1 + UnkDssRand::rand(3);
            } else {
                X = ((DM * 700) / 8 + (UnkDssRand::rand(256) * ((DM * 100) / 4 + 100)) / 256) / 100;
            }
        }
    }

    if (actor->getHaveStatusInfo().isKaishin()) {
        X = getKaishinAttackEffectValue(actor, target);
    }
    if (actor->getHaveStatusInfo().isTsukon1()) {
        X = getTsukon1AttackEffectValue(actor);
    }
    if (actor->getHaveStatusInfo().isTsukon2()) {
        X = getTsukon2AttackEffectValue(actor);
    }
    return X;
}

THUMB int status::getUsuallyAttackEffectValueForAI(status::CharacterStatus* actor, status::CharacterStatus* target)
{
    int AT = actor->getHaveStatusInfo().getAttack(0);
    int DF = target->getHaveStatusInfo().getDefence(0);
    int DM = (AT - DF / 2) / 2;
    int X = 0;

    if (DM > 0) {
        if (target->getCharacterType() == PLAYER) {
            if (DM <= AT / 12) {
                X = UnkDssRand::rand(AT / 12);
            } else if (DM < 8) {
                X = DM - 1;
            } else {
                X = ((DM * 700) / 8) / 100;
            }
        }
        if (target->getCharacterType() == MONSTER) {
            if (DM < 8) {
                X = DM - 1 + UnkDssRand::rand(3);
            } else {
                X = ((DM * 700) / 8) / 100;
            }
        }
    }

    if (actor->getHaveStatusInfo().isKaishin()) {
        X = getKaishinAttackEffectValue(actor, target);
    }
    if (actor->getHaveStatusInfo().isTsukon1()) {
        X = getTsukon1AttackEffectValue(actor);
    }
    if (actor->getHaveStatusInfo().isTsukon2()) {
        X = getTsukon2AttackEffectValue(actor);
    }
    return X;
}

THUMB int status::getKaishinAttackEffectValue(status::CharacterStatus* actor, status::CharacterStatus* target)
{
    int AT = actor->getHaveStatusInfo().getAttack(0);
    target->getHaveStatusInfo().getDefence(0);
    int DM = (AT * (UnkDssRand::rand(11) + 64)) / 64;
    return DM;
}

THUMB int status::getTsukon1AttackEffectValue(status::CharacterStatus* actor)
{
    int DM = getRandomVariation(actor->getHaveStatusInfo().getAttack(0), 0, 5);
    return DM;
}

THUMB int status::getTsukon2AttackEffectValue(status::CharacterStatus* actor)
{
    int DM = actor->getHaveStatusInfo().getAttack(0) * 5;
    return DM;
}

THUMB int status::getRandomVariation(int value, int under, int over)
{
    int spread = UnkDssRand::rand(under + over + 1);
    int ratio = 100 - under + spread;
    return value * ratio / 100;
}

THUMB bool status::isExecRula()
{
    if (!g_StageAttribute.isRula()) {
        return false;
    }
    if (!g_StageAttribute.isRulaDisable()) {
        return true;
    }
    return false;
}

THUMB bool status::isExecRiremito()
{
    if (!g_StageAttribute.isRiremito()) {
        return false;
    }
    if (g_StageAttribute.isRiremitoDisable()) {
        return false;
    }
    if (g_StageInfo.riremitMap_ == 0) {
        return false;
    }
    if (data_02101c88.isCurrentPart(4)) {
        return true;
    }
    return false;
}

THUMB bool status::isExecImpas()
{
    if (data_02101c88.isCurrentPart(4) == 1) {
        int uid = twn::TownPlayerManager::getSingleton().getInpasMapObj();
        int coffer = twn::TownFurnitureManager::getSingleton()->checkCoffer(uid);
        if (uid == 0 || coffer == 0) {
            return false;
        }
        int furniture = twn::TownFurnitureManager::getSingleton()->getCofferType(uid);
        if (furniture == 0x44 || furniture == 0x33) {
            return true;
        }
    }
    return false;
}

THUMB bool status::isExecLanaruta()
{
    if (!g_StageAttribute.isLanaruta()) {
        return false;
    }
    if (g_StageAttribute.isLanarutaDisable()) {
        return false;
    }
    if (g_StageAttribute.timestop_) {
        return false;
    }
    if (data_02101c88.isCurrentPart(4)) {
        if (g_StageInfo.lastFldSurface_ == -1) {
            return false;
        }
        if (g_StageInfo.lastRanaStageNameId_ == 0) {
            return false;
        }
    }
    return true;
}

THUMB bool status::isExecFloomi()
{
    if (data_02101c88.isCurrentPart(5)) {
        return false;
    }
    if (data_02101c88.isCurrentPart(6)) {
        return false;
    }
    data_02101c88.isCurrentPart(4);
    return true;
}

THUMB bool status::isExecToherosu()
{
    return g_StageAttribute.isEncount() != false;
}

int status::metalSlimeBeforeIndex;
int status::callMonsterFlag;
int status::metalSlimeCount;
int status::callMonsterCount;
int status::callMonsterIndex;
status::CharacterStatus* status::callMonsterStatus[12];

THUMB void status::initCallMonster()
{
    callMonsterIndex = 0;
    callMonsterCount = 0;
    for (int i = 0; i < 12; i++) {
        callMonsterStatus[i] = 0;
    }
}

THUMB void status::addCallMonster(status::CharacterStatus* monster)
{
    callMonsterStatus[callMonsterCount] = monster;
    callMonsterCount++;
    monster->getHaveStatusInfo().setCallFriend(true);
    unsigned short hpMax = monster->getHaveStatusInfo().getHpMax();
    unsigned short rate = UnkDssRand::rand(25) + 76;
    hpMax = hpMax * rate / 100;
    if (hpMax == 0) {
        hpMax = 1;
    }
    monster->getHaveStatusInfo().setHp(hpMax);
}

THUMB int status::getCallMonsterCount()
{
    return callMonsterCount;
}

THUMB status::CharacterStatus* status::getCallMonsterStatus(int index)
{
    return callMonsterStatus[index];
}

THUMB void status::setCallMonster(bool flag)
{
    callMonsterFlag = flag;
}

THUMB int status::isCallMonster()
{
    return callMonsterFlag;
}

THUMB bool status::callDifferentMonster(int monsterGroup, int monsterIndex)
{
    callMonsterIndex = monsterIndex;
    if (btl::BattleMonsterDraw2::getSingleton().isCallFriend(monsterIndex) && g_Monster.getCount() < 12) {
        if (monsterGroup != -1) {
            if (g_Monster.getMonsterCountInGroup(monsterGroup) == 8) {
                return false;
            }
            if (g_Monster.getMonsterCountInGroup(monsterGroup) == 8) {
                return false;
            }
            addCallMonster(&g_Monster.getMonsterStatus(g_Monster.add(monsterGroup, monsterIndex, false)));
            setCallMonster(true);
            return true;
        }
        int group = g_Monster.getMonsterGroupForMonsterIndex(monsterIndex);
        if (group != -1) {
            if (g_Monster.getMonsterCountInGroup(group) == 8) {
                return false;
            }
            addCallMonster(&g_Monster.getMonsterStatus(g_Monster.add(group, monsterIndex, false)));
            setCallMonster(true);
            return true;
        }
        if (g_Monster.getMonsterCountInGroupAlive(0) == 0) {
            addCallMonster(&g_Monster.getMonsterStatus(g_Monster.add(0, monsterIndex, false)));
            setCallMonster(true);
            return true;
        }
        if (g_Monster.getMonsterCountInGroupAlive(1) == 0) {
            addCallMonster(&g_Monster.getMonsterStatus(g_Monster.add(1, monsterIndex, false)));
            setCallMonster(true);
            return true;
        }
        if (g_Monster.getMonsterCountInGroupAlive(2) == 0) {
            addCallMonster(&g_Monster.getMonsterStatus(g_Monster.add(2, monsterIndex, false)));
            setCallMonster(true);
            return true;
        }
        if (g_Monster.getMonsterCountInGroupAlive(3) == 0) {
            addCallMonster(&g_Monster.getMonsterStatus(g_Monster.add(3, monsterIndex, false)));
            setCallMonster(true);
            return true;
        }
    }
    return false;
}

THUMB void status::checkCloseDoor(status::CharacterStatus* target)
{
    if (target->getHaveStatusInfo().isCloseDoor()) {
        if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_CLOSEDOOR)) {
            target->getHaveStatusInfo().setCloseDoor(false);
            target->getHaveStatusInfo().getStatusChange().release(dq5::level::ActionParam::ACTIONTYPE_CLOSEDOOR);
        }
    }
}
