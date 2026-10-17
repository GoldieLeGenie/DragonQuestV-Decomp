#pragma ipa file
#include "ov000/btl/BattleSelectTarget.hpp"
#include "ov000/btl/BattleSecondCheck.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/menu/StadiumData.hpp"
#include "main/status/ActionEffectValue.hpp"
#include "main/status/ExtraAction.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseActionParam.hpp"

inline void btl::BattleSelectTargetParam::setActorCharacterStatus(status::CharacterStatus* info) { actorCharacterStatus_ = info; }
inline status::CharacterStatus* btl::BattleSelectTargetParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline void btl::BattleSelectTargetParam::setTargetGroupIndex(int group) { targetGroup_ = group; }
inline int btl::BattleSelectTargetParam::getTargetGroupIndex() { return targetGroup_; }
inline void btl::BattleSelectTargetParam::setTargetIndex(int index) { targetIndex_ = index; }
inline int btl::BattleSelectTargetParam::getTargetIndex() { return targetIndex_; }
inline void btl::BattleSelectTargetParam::setSourceCount(int count) { sourceCount_ = count; }
inline int btl::BattleSelectTargetParam::getSourceCount() { return sourceCount_; }
inline void btl::BattleSelectTargetParam::setTargetCount(int count) { targetCount_ = count; }
inline int btl::BattleSelectTargetParam::getTargetCount() { return targetCount_; }
inline void btl::BattleSelectTargetParam::setActionIndex(int actionIndex) { actionIndex_ = actionIndex; }
inline int btl::BattleSelectTargetParam::getActionIndex() { return actionIndex_; }
inline void btl::BattleSelectTargetParam::setCallTarget(CallTargetSelect call) { callTarget_ = call; }
inline btl::BattleSelectTargetParam::CallTargetSelect btl::BattleSelectTargetParam::getCallTarget() { return callTarget_; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline status::CharacterStatus* status::UseActionParam::getTargetCharacterStatus(int index) { return targetCharacterStatus_[index]; }
inline void status::UseActionParam::setTargetCharacterStatus(int index, CharacterStatus* info) { targetCharacterStatus_[index] = info; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline void status::UseActionParam::setTargetCount(int count) { targetCount_ = count; }
inline int status::UseActionParam::getTargetCount() { return targetCount_; }
inline void status::UseActionParam::setEffectValue(int value) { effectValue_ = value; }
inline int status::UseActionParam::getEffectValue() { return effectValue_; }
inline int status::UseActionParam::getPlayerEffectValue() { return playerEffectValue_; }
inline void status::UseActionParam::setItemSortIndex(int sortIndex) { itemSortIndex_ = sortIndex; }
inline void status::UseActionParam::setDamage(int dm) { damage_ = dm; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::CharacterStatus::getGroupIndex() { return characterGroup_; }
inline int status::CharacterStatus::getArrayIndex() { return arrayIndex_; }
inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment() { return haveEquipment_; }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}
inline unsigned char status::HaveBattleStatus::getBrains() { return brains_; }
inline void status::HaveBattleStatus::setSelectGroup(int group) { selectedGroup_ = group; }
inline int status::HaveBattleStatus::getSelectGroup() { return selectedGroup_; }
inline void status::HaveBattleStatus::setSelectTarget(int playerIndex) { selectedTarget_ = playerIndex; }
inline int status::HaveBattleStatus::getSelectTarget() { return selectedTarget_; }
inline bool status::HaveBattleStatus::isAutoSelect() { return selectCommand_ == AISelect; }
inline int status::HaveBattleStatus::getActionIndex() { return actionIndex_; }
inline int status::HaveBattleStatus::getItemSortIndex() { return sortIndex_; }
inline int status::HaveBattleStatus::getCrossFire() { return crossFire_; }
inline void status::HaveBattleStatus::setCrossFireTarget(int index) { crossFireTarget_ = index; }
inline int status::HaveBattleStatus::getCrossFireTarget() { return crossFireTarget_; }
inline void status::ActionEffectValue::clearEffectValue() { specialTargetEffectValue_ = 0; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline char dq5::level::ActionParam::getKakutou() { return (byte_4 & 0x8) >> 3; }
inline bool StadiumData::isStadiumBattle() { return stadiumFlag_; }

status::CharacterStatus* btl::BattleSelectTarget::specialTarget_[8];

THUMB void btl::BattleSelectTarget::setTarget(status::UseActionParam* useActionParam, BattleSelectTargetParam::CallTargetSelect call)
{
    bool result;

    if (useActionParam->getActionIndex() == 0) {
        return;
    }

    unsigned char brain = useActionParam->getActorCharacterStatus()->getHaveBattleStatus().getBrains();
    if (call == BattleSelectTargetParam::StartRound && brain == 2) {
        return;
    }
    if (call == BattleSelectTargetParam::StartTurn && brain == 2) {
        status::CharacterStatus* actor = useActionParam->getActorCharacterStatus();
        actor->getHaveBattleStatus().setSelectGroup(0);
        actor->getHaveBattleStatus().setSelectTarget(0);
        int selectCount = useActionParam->getTargetCount();
        useActionParam->setTargetCount(0);
        for (int i = 0; i < selectCount; i++) {
            useActionParam->setTargetCharacterStatus(i, NULL);
        }
    }

    do {
        result = setTargetSet(useActionParam, call);
    } while (!result);
}

THUMB bool btl::BattleSelectTarget::setTargetSet(status::UseActionParam* useActionParam, BattleSelectTargetParam::CallTargetSelect call)
{
    int actionIndex = useActionParam->getActionIndex();
    if (actionIndex == 0) {
        return true;
    }

    status::CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    BattleSelectTargetParam battleSelectTargetParam;
    battleSelectTargetParam.clear();
    battleSelectTargetParam.setActionIndex(useActionParam->getActionIndex());
    battleSelectTargetParam.setActorCharacterStatus(actor);
    battleSelectTargetParam.setCallTarget(call);

    if (useActionParam->getActorCharacterStatus()->getHaveBattleStatus().isAutoSelect()) {
        if (call == BattleSelectTargetParam::StartTurn) {
            int selectGroup = checkCurseSecond(actor, actionIndex);
            battleSelectTargetParam.setTargetGroupIndex(selectGroup);
            int selectTarget = actor->getHaveBattleStatus().getSelectTarget();
            battleSelectTargetParam.setTargetIndex(selectTarget);
            int selectCount = useActionParam->getTargetCount();
            battleSelectTargetParam.setTargetCount(selectCount);
            for (int i = 0; i < selectCount; i++) {
                battleSelectTargetParam.setTargetCharacterStatus(i, useActionParam->getTargetCharacterStatus(i));
            }
        }
    } else {
        int selectGroup = checkCurseSecond(actor, actionIndex);
        battleSelectTargetParam.setTargetGroupIndex(selectGroup);
        int selectTarget = actor->getHaveBattleStatus().getSelectTarget();
        battleSelectTargetParam.setTargetIndex(selectTarget);
        int selectCount = useActionParam->getTargetCount();
        if (call == BattleSelectTargetParam::StartTurn) {
            battleSelectTargetParam.setTargetCount(selectCount);
            for (int i = 0; i < selectCount; i++) {
                battleSelectTargetParam.setTargetCharacterStatus(i, useActionParam->getTargetCharacterStatus(i));
            }
        }
    }

    bool result = true;
    switch (status::UseAction::getUseType(actionIndex)) {
    case status::UseAction::Myself:
        result = setTargetMyself(actor, &battleSelectTargetParam);
        break;
    case status::UseAction::Friend:
        result = setTargetFriend(actor, actionIndex, &battleSelectTargetParam);
        break;
    case status::UseAction::Enemy:
        result = setTargetEnemy(actor, actionIndex, &battleSelectTargetParam);
        break;
    case status::UseAction::Both:
        result = setTargetBoth(actionIndex, &battleSelectTargetParam);
        break;
    case status::UseAction::None:
        result = setTargetNone(actor, &battleSelectTargetParam);
        break;
    }

    if (g_StadiumData.isStadiumBattle() && !checkStadiumAction(battleSelectTargetParam.getActionIndex())) {
        setNextAction(&battleSelectTargetParam);
        result = false;
    }

    if (result) {
        int count = battleSelectTargetParam.getTargetCount();
        for (int i = 0; i < count; i++) {
            useActionParam->setTargetCharacterStatus(i, battleSelectTargetParam.getTargetCharacterStatus(i));
        }
        useActionParam->setTargetCount(count);
        if (battleSelectTargetParam.getActionIndex() == 0x1e2) {
            useActionParam->setActionIndex(0x1e2);
        }
        if (count != 0) {
            actor->getHaveBattleStatus().setSelectGroup(battleSelectTargetParam.getTargetCharacterStatus(0)->getGroupIndex());
        } else {
            actor->getHaveBattleStatus().setSelectGroup(battleSelectTargetParam.getActorCharacterStatus()->getGroupIndex());
        }
        actor->getHaveBattleStatus().setSelectTarget(battleSelectTargetParam.getTargetIndex());
        actor->getHaveBattleStatus().setActionIndex(battleSelectTargetParam.getActionIndex());
    } else {
        useActionParam->setActionIndex(battleSelectTargetParam.getActorCharacterStatus()->getHaveBattleStatus().getActionIndex());
    }
    return result;
}

THUMB void btl::BattleSelectTarget::setTargetPlayer(BattleSelectTargetParam* battleSelectTargetParam)
{
    if (g_StadiumData.isStadiumBattle()) {
        setTargetStadiumMonster(battleSelectTargetParam);
        return;
    }

    status::g_Party.setBattleMode();
    int playerCount = status::g_Party.getCarriageOutCount();
    int count = 0;
    for (int i = 0; i < playerCount; i++) {
        if (!status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            battleSelectTargetParam->setSourceCharacterStatus(count, &status::g_Party.getPlayerStatus(i));
            count++;
        }
    }
    battleSelectTargetParam->setSourceCount(count);
}

THUMB void btl::BattleSelectTarget::setTargetPlayerWithDeath(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::g_Party.setBattleMode();
    int playerCount = status::g_Party.getCarriageOutCount();
    int count = 0;
    for (int i = 0; i < playerCount; i++) {
        battleSelectTargetParam->setSourceCharacterStatus(count, &status::g_Party.getPlayerStatus(i));
        count++;
    }
    battleSelectTargetParam->setSourceCount(count);
}

THUMB void btl::BattleSelectTarget::setTargetPlayerAll(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::g_Party.setBattleMode();
    int playerCount = status::g_Party.getCount();
    int count = 0;
    if (!status::g_Party.isCarriageEnableOnGame()) {
        playerCount = status::g_Party.getCarriageOutCount();
    }
    for (int i = 0; i < playerCount; i++) {
        if (!status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            battleSelectTargetParam->setSourceCharacterStatus(count, &status::g_Party.getPlayerStatus(i));
            count++;
        }
    }
    battleSelectTargetParam->setSourceCount(count);
}

THUMB void btl::BattleSelectTarget::setTargetPlayerAllWithDeath(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::g_Party.setBattleMode();
    int playerCount = status::g_Party.getCount();
    int count = 0;
    if (!status::g_Party.isCarriageEnableOnGame()) {
        playerCount = status::g_Party.getCarriageOutCount();
    }
    for (int i = 0; i < playerCount; i++) {
        battleSelectTargetParam->setSourceCharacterStatus(count, &status::g_Party.getPlayerStatus(i));
        count++;
    }
    battleSelectTargetParam->setSourceCount(count);
}

THUMB void btl::BattleSelectTarget::setTargetMonster(BattleSelectTargetParam* battleSelectTargetParam)
{
    if (g_StadiumData.isStadiumBattle()) {
        battleSelectTargetParam->setSourceCharacterStatus(0, battleSelectTargetParam->getActorCharacterStatus());
        battleSelectTargetParam->setSourceCount(1);
        return;
    }

    status::g_Party.setBattleMode();
    int monsterCount = status::g_Monster.getCount();
    int count = 0;
    for (int i = 0; i < monsterCount; i++) {
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()
            && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isEscapeFlag()
            && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDisappearFlag()) {
            battleSelectTargetParam->setSourceCharacterStatus(count, &status::g_Monster.getMonsterStatus(i));
            count++;
        }
    }
    battleSelectTargetParam->setSourceCount(count);
}

THUMB void btl::BattleSelectTarget::setTargetMonsterWithDeath(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::g_Party.setBattleMode();
    int monsterCount = status::g_Monster.getCount();
    int count = 0;
    for (int i = 0; i < monsterCount; i++) {
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isEscapeFlag()
            && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDisappearFlag()) {
            battleSelectTargetParam->setSourceCharacterStatus(count, &status::g_Monster.getMonsterStatus(i));
            count++;
        }
    }
    battleSelectTargetParam->setSourceCount(count);
}

THUMB void btl::BattleSelectTarget::setTargetStadiumMonster(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::g_Party.setBattleMode();
    int monsterCount = status::g_Monster.getCount();
    int count = 0;
    for (int i = 0; i < monsterCount; i++) {
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()
            && &status::g_Monster.getMonsterStatus(i) != battleSelectTargetParam->getActorCharacterStatus()
            && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isEscapeFlag()
            && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDisappearFlag()) {
            battleSelectTargetParam->setSourceCharacterStatus(count, &status::g_Monster.getMonsterStatus(i));
            count++;
        }
    }
    battleSelectTargetParam->setSourceCount(count);
}

THUMB void btl::BattleSelectTarget::setTargetPlayerAndMonster(BattleSelectTargetParam* targetParam, int playerMax, int monsterMax)
{
    status::g_Party.setBattleMode();
    int actionIndex = targetParam->getActionIndex();
    int liveCount = 0;
    bool alive = status::UseAction::isTargetDeadOrAlive(actionIndex);
    bool typePlayer = targetParam->getActorCharacterStatus()->getCharacterType() == PLAYER;
    if (actionIndex == 0x1b9) {
        typePlayer = !typePlayer;
    }

    if (typePlayer) {
        for (int i = 0; i < playerMax; i++) {
            if (!status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() || !alive) {
                targetParam->setSourceCharacterStatus(liveCount, &status::g_Party.getPlayerStatus(i));
                liveCount++;
            }
        }
        for (int i = 0; i < monsterMax; i++) {
            if ((!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath() || !alive)
                && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isEscapeFlag()
                && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDisappearFlag()) {
                targetParam->setSourceCharacterStatus(liveCount, &status::g_Monster.getMonsterStatus(i));
                liveCount++;
            }
        }
    } else {
        for (int i = 0; i < monsterMax; i++) {
            if ((!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath() || !alive)
                && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isEscapeFlag()
                && !status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDisappearFlag()) {
                targetParam->setSourceCharacterStatus(liveCount, &status::g_Monster.getMonsterStatus(i));
                liveCount++;
            }
        }
        if (!g_StadiumData.isStadiumBattle()) {
            for (int i = 0; i < playerMax; i++) {
                if (!status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath() || !alive) {
                    targetParam->setSourceCharacterStatus(liveCount, &status::g_Party.getPlayerStatus(i));
                    liveCount++;
                }
            }
        }
    }
    targetParam->setSourceCount(liveCount);
}

THUMB bool btl::BattleSelectTarget::setTargetBoth(int actionIndex, BattleSelectTargetParam* battleSelectTargetParam)
{
    battleSelectTargetParam->setActionIndex(actionIndex);
    int playerCount = status::g_Party.getCarriageOutCount();
    int monsterCount = status::g_Monster.getCount();
    setTargetPlayerAndMonster(battleSelectTargetParam, playerCount, monsterCount);

    bool result = true;
    switch (status::UseAction::getUseArea(actionIndex)) {
    case status::UseAction::Zero:
        result = setTargetOne(battleSelectTargetParam);
        break;
    case status::UseAction::One:
        battleSelectTargetParam->setTargetGroupIndex(-1);
        result = setTargetOne(battleSelectTargetParam);
        break;
    case status::UseAction::Group:
        result = setTargetGroup(battleSelectTargetParam);
        break;
    case status::UseAction::All:
        result = setTargetAll(battleSelectTargetParam);
        break;
    case status::UseAction::Horse:
    case status::UseAction::UsuallyHorse:
    case status::UseAction::BattleHorse:
        playerCount = status::g_Party.getCount();
        if (!status::g_Party.isCarriageEnableOnGame()) {
            playerCount = status::g_Party.getCarriageOutCount();
        }
        setTargetPlayerAndMonster(battleSelectTargetParam, playerCount, monsterCount);
        result = setTargetAllWithCarriage(battleSelectTargetParam);
        break;
    }
    return result;
}

THUMB bool btl::BattleSelectTarget::setTargetNone(status::CharacterStatus* actor, BattleSelectTargetParam* battleSelectTargetParam)
{
    if (battleSelectTargetParam->getActionIndex() == 0x1d4) {
        if (UnkDssRand::rand(300) > 99) {
            setTargetPlayer(battleSelectTargetParam);
        } else {
            setTargetMonster(battleSelectTargetParam);
        }
        return setTargetAll(battleSelectTargetParam);
    }
    battleSelectTargetParam->setSourceCharacterStatus(0, actor);
    battleSelectTargetParam->setSourceCount(1);
    return setTargetOne(battleSelectTargetParam);
}

THUMB bool btl::BattleSelectTarget::setTargetMyself(status::CharacterStatus* actor, BattleSelectTargetParam* battleSelectTargetParam)
{
    if (actor->getCharacterType() == PLAYER) {
        setTargetPlayer(battleSelectTargetParam);
    }
    if (actor->getCharacterType() == MONSTER) {
        setTargetMonster(battleSelectTargetParam);
    }
    if (battleSelectTargetParam->getCallTarget() == BattleSelectTargetParam::StartTurn
        && battleSelectTargetParam->getTargetCount() > 0
        && !battleSelectTargetParam->getTargetCharacterStatus(0)->getHaveStatusInfo().isDeath()) {
        return true;
    }

    bool ret = BattleSecondCheck::myselfCheck(battleSelectTargetParam);
    if (battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().isMosyasExec()) {
        ret = true;
    }
    if (!ret) {
        battleSelectTargetParam->getActorCharacterStatus()->getHaveBattleStatus().setActionDisable2nd();
        battleSelectTargetParam->getActorCharacterStatus()->getHaveBattleStatus().setActionSelect(status::HaveBattleStatus::StartRound, true);
        return false;
    }

    battleSelectTargetParam->setTargetCharacterStatus(0, battleSelectTargetParam->getActorCharacterStatus());
    battleSelectTargetParam->setTargetCount(1);
    return true;
}

THUMB bool btl::BattleSelectTarget::setTargetFriend(status::CharacterStatus* actor, int actionIndex, BattleSelectTargetParam* battleSelectTargetParam)
{
    bool aliveAction = status::UseAction::isTargetDeadOrAlive(actionIndex);
    if (actor->getCharacterType() == PLAYER) {
        if (aliveAction) {
            setTargetPlayer(battleSelectTargetParam);
        } else {
            setTargetPlayerWithDeath(battleSelectTargetParam);
        }
        if (actionIndex == 0x1f3) {
            battleSelectTargetParam->setTargetIndex(-1);
        }
        if (checkFriendTarget(battleSelectTargetParam)) {
            return true;
        }
    }
    if (actor->getCharacterType() == MONSTER) {
        if (status::UseAction::isTargetDeadOrAlive(actionIndex)) {
            if (battleSelectTargetParam->getActionIndex() == 0x192) {
                setTargetStadiumMonster(battleSelectTargetParam);
            } else {
                setTargetMonster(battleSelectTargetParam);
            }
        } else {
            setTargetMonsterWithDeath(battleSelectTargetParam);
        }
    }

    bool result = true;
    switch (status::UseAction::getUseArea(actionIndex)) {
    case status::UseAction::Zero:
        result = setTargetOne(battleSelectTargetParam);
        break;
    case status::UseAction::One:
        result = setTargetOne(battleSelectTargetParam);
        break;
    case status::UseAction::Group:
        result = setTargetGroup(battleSelectTargetParam);
        break;
    case status::UseAction::All:
        result = setTargetAll(battleSelectTargetParam);
        break;
    case status::UseAction::Horse:
    case status::UseAction::UsuallyHorse:
    case status::UseAction::BattleHorse:
        if (actor->getCharacterType() == PLAYER) {
            if (status::UseAction::isTargetDeadOrAlive(actionIndex)) {
                setTargetPlayerAll(battleSelectTargetParam);
            } else {
                setTargetPlayerAllWithDeath(battleSelectTargetParam);
            }
        }
        result = setTargetAllWithCarriage(battleSelectTargetParam);
        break;
    }
    return result;
}

THUMB bool btl::BattleSelectTarget::checkFriendTarget(BattleSelectTargetParam* targetParam)
{
    status::CharacterStatus* actor = targetParam->getActorCharacterStatus();
    status::CharacterStatus* target = targetParam->getTargetCharacterStatus(0);
    int selectTarget = targetParam->getTargetIndex();
    bool aliveAction = status::UseAction::isTargetDeadOrAlive(targetParam->getActionIndex());

    if (selectTarget != -1 && actor->getHaveBattleStatus().getBrains() == 0) {
        setTargetPlayerWithDeath(targetParam);
        if (target == NULL) {
            target = targetParam->getSourceCharacterStatus(selectTarget);
        }
        if (aliveAction && targetParam->getCallTarget() == BattleSelectTargetParam::StartTurn && target->getHaveStatusInfo().isDeath()) {
            setTargetPlayer(targetParam);
            return false;
        }
        for (int i = 0; i < targetParam->getSourceCount(); i++) {
            if (target == targetParam->getSourceCharacterStatus(i)) {
                targetParam->setTargetCharacterStatus(0, targetParam->getSourceCharacterStatus(i));
                targetParam->setTargetCount(1);
                targetParam->setTargetIndex(i);
                return true;
            }
        }
    }
    return false;
}

THUMB status::UseAction::UseArea btl::BattleSelectTarget::setWeaponArea(status::CharacterStatus* actor, int actionIndex)
{
    if (actionIndex != 0x47) {
        return status::UseAction::getUseArea(actionIndex);
    }
    switch (actor->getHaveStatusInfo().getHaveEquipment().getEquipment(ITEM_WEAPON, 0)) {
    case 0x17:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x3d:
        return status::UseAction::All;
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
        return status::UseAction::Group;
    }
    return status::UseAction::getUseArea(actionIndex);
}

THUMB int btl::BattleSelectTarget::checkCurseSecond(status::CharacterStatus* actor, int actionIndex)
{
    if (actionIndex == 0x1f3) {
        return -1;
    }
    return actor->getHaveBattleStatus().getSelectGroup();
}

THUMB bool btl::BattleSelectTarget::setTargetEnemy(status::CharacterStatus* actor, int actionIndex, BattleSelectTargetParam* battleSelectTargetParam)
{
    status::UseAction::UseArea area = status::UseAction::One;
    if (actor->getCharacterType() == PLAYER) {
        setTargetMonster(battleSelectTargetParam);
        area = setWeaponArea(actor, actionIndex);
    } else if (actor->getCharacterType() == MONSTER) {
        setTargetPlayer(battleSelectTargetParam);
        area = status::UseAction::getUseArea(actionIndex);
    }

    bool result = true;
    switch (area) {
    case status::UseAction::Zero:
        result = setTargetOne(battleSelectTargetParam);
        break;
    case status::UseAction::One:
        result = setTargetOne(battleSelectTargetParam);
        break;
    case status::UseAction::Group:
        result = setTargetGroup(battleSelectTargetParam);
        break;
    case status::UseAction::All:
        result = setTargetAll(battleSelectTargetParam);
        break;
    case status::UseAction::Horse:
    case status::UseAction::UsuallyHorse:
    case status::UseAction::BattleHorse:
        result = setTargetAllWithCarriage(battleSelectTargetParam);
        break;
    }
    return result;
}

THUMB bool btl::BattleSelectTarget::setTargetOne(BattleSelectTargetParam* battleSelectTargetParam)
{
    if (battleSelectTargetParam->getCallTarget() == BattleSelectTargetParam::StartTurn && checkTurnSelectOne(battleSelectTargetParam)) {
        return true;
    }
    return setPersonalTarget(battleSelectTargetParam);
}

THUMB bool btl::BattleSelectTarget::checkTurnSelectOne(BattleSelectTargetParam* targetParam)
{
    if (targetParam->getActorCharacterStatus()->getHaveBattleStatus().getBrains() == 2) {
        return false;
    }
    if (targetParam->getActionIndex() == 0) {
        return false;
    }
    if (targetParam->getTargetCount() == 0) {
        return false;
    }
    if (targetParam->getActionIndex() == 0xca) {
        return false;
    }
    int maxNum = targetParam->getSourceCount();
    if (maxNum == 0) {
        return false;
    }

    status::CharacterStatus* targetStatus = targetParam->getTargetCharacterStatus(0);
    for (int i = 0; i < targetParam->getTargetCount(); i++) {
        targetParam->setTargetCharacterStatus(i, NULL);
    }
    targetParam->setTargetCount(0);
    targetParam->setTargetIndex(0);
    for (int i = 0; i < maxNum; i++) {
        status::CharacterStatus* status = targetParam->getSourceCharacterStatus(i);
        if (status == targetStatus) {
            targetParam->setTargetCharacterStatus(0, status);
            targetParam->setTargetCount(1);
            targetParam->setTargetIndex(i);
            return true;
        }
    }
    return false;
}

THUMB bool btl::BattleSelectTarget::checkTurnSelectGroup(BattleSelectTargetParam* targetParam)
{
    int maxNum;
    int group = targetParam->getTargetGroupIndex();
    bool alive = true;

    if (targetParam->getActorCharacterStatus()->getHaveBattleStatus().getBrains() == 2) {
        return false;
    }
    if (targetParam->getActionIndex() == 0) {
        return false;
    }
    if (status::UseAction::isTargetDeadOrAlive(targetParam->getActionIndex())) {
        maxNum = targetParam->getSourceCountForGroup(group);
    } else {
        maxNum = targetParam->getSourceCountForGroupDead(group);
        alive = false;
    }
    if (maxNum == 0) {
        return false;
    }

    for (int i = 0; i < targetParam->getTargetCount(); i++) {
        targetParam->setTargetCharacterStatus(i, NULL);
    }
    targetParam->setTargetCount(0);
    targetParam->setTargetIndex(0);
    for (int i = 0; i < maxNum; i++) {
        if (alive) {
            targetParam->setTargetCharacterStatus(i, targetParam->getSourceCharacterStatusForGroup(group, i));
        } else {
            targetParam->setTargetCharacterStatus(i, targetParam->getSourceCharacterStatusForGroupDead(group, i));
        }
    }
    targetParam->setTargetCount(maxNum);
    targetParam->setTargetIndex(0);
    return true;
}

THUMB bool btl::BattleSelectTarget::checkTurnSelectAll(BattleSelectTargetParam* targetParam)
{
    int maxNum = targetParam->getSourceCount();

    if (targetParam->getActorCharacterStatus()->getHaveBattleStatus().getBrains() == 2) {
        return false;
    }
    if (targetParam->getActionIndex() == 0) {
        return false;
    }
    if (maxNum == 0) {
        return false;
    }

    for (int i = 0; i < targetParam->getTargetCount(); i++) {
        targetParam->setTargetCharacterStatus(i, NULL);
    }
    targetParam->setTargetCount(0);
    targetParam->setTargetIndex(0);
    int count = 0;
    for (int i = 0; i < maxNum; i++) {
        status::CharacterStatus* targetStatus = targetParam->getSourceCharacterStatus(i);
        status::HaveStatusInfo& statusInfo = targetStatus->getHaveStatusInfo();
        if (!statusInfo.isEscapeFlag() && !statusInfo.isDisappearFlag()) {
            if (targetParam->getActionIndex() != 0x3f || targetStatus != targetParam->getActorCharacterStatus()) {
                targetParam->setTargetCharacterStatus(count, targetStatus);
                count++;
            }
        }
    }
    targetParam->setTargetCount(count);
    targetParam->setTargetIndex(0);
    return true;
}

THUMB bool btl::BattleSelectTarget::checkStadiumAction(int actionIndex)
{
    if (dq5::level::ActionParam::getRecord(actionIndex)->getKakutou()) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSelectTarget::setPersonalTarget(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::CharacterStatus* targetCharacterStatus[18] = {0};
    for (int i = 0; i < 18; i++) targetCharacterStatus[i] = NULL;
    unsigned char targetCharacterGroup[18] = {0};
    for (int i = 0; i < 18; i++) targetCharacterGroup[i] = 0;
    unsigned char targetCharacterIndex[18] = {0};
    for (int i = 0; i < 18; i++) targetCharacterIndex[i] = 0;

    status::CharacterStatus* actorStatus = battleSelectTargetParam->getActorCharacterStatus();
    int targetGroup = battleSelectTargetParam->getTargetGroupIndex();
    int targetCount = battleSelectTargetParam->getSourceCountForGroupDead(targetGroup);
    int actorIndex = -1;

    if (!BattleSecondCheck::personalCheckFirst(battleSelectTargetParam)
        && !battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().isMosyasExec()) {
        setNextAction(battleSelectTargetParam);
        return false;
    }

    int tempCount = 0;
    for (int i = 0; i < targetCount; i++) {
        targetCharacterStatus[tempCount] = battleSelectTargetParam->getSourceCharacterStatusForGroupDead(targetGroup, i);
        targetCharacterGroup[tempCount] = targetGroup;
        targetCharacterIndex[tempCount] = i;
        if (BattleSecondCheck::personalCheckLast(battleSelectTargetParam, targetGroup, i)) {
            if (actorStatus == targetCharacterStatus[tempCount]) {
                actorIndex = tempCount;
            }
            tempCount++;
        }
    }
    targetCount = tempCount;

    if (targetCount == 0 || battleSelectTargetParam->getActorCharacterStatus()->getCharacterType() == MONSTER) {
        for (int i = 0; i < 4; i++) {
            if (targetGroup != i) {
                int count = battleSelectTargetParam->getSourceCountForGroupDead(i);
                if (count > 0) {
                    for (int j = 0; j < count; j++) {
                        targetCharacterStatus[targetCount] = battleSelectTargetParam->getSourceCharacterStatusForGroupDead(i, j);
                        targetCharacterGroup[targetCount] = i;
                        targetCharacterIndex[targetCount] = j;
                        if (battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().isMosyasExec()) {
                            targetCount++;
                        } else if (BattleSecondCheck::personalCheckLast(battleSelectTargetParam, i, j)) {
                            if (actorStatus == targetCharacterStatus[tempCount]) {
                                actorIndex = tempCount;
                            }
                            targetCount++;
                        }
                    }
                }
            }
        }
    }

    if (targetCount == 0) {
        setNextAction(battleSelectTargetParam);
        return false;
    }

    int index;
    if (battleSelectTargetParam->getActionIndex() == 0x47) {
        unsigned char normalTarget[18] = {0};
        for (int i = 0; i < 18; i++) normalTarget[i] = 0;
        int normalCount = 0;
        for (int i = 0; i < targetCount; i++) {
            status::HaveStatusInfo& statusInfo = targetCharacterStatus[i]->getHaveStatusInfo();
            if (!statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA)) {
                normalTarget[normalCount] = i;
                normalCount++;
            }
        }
        if (normalCount > 0) {
            index = UnkDssRand::rand(normalCount);
        }
        index = UnkDssRand::rand(targetCount);
    } else {
        index = BattleSecondCheck::secondCheckTarget(battleSelectTargetParam, targetCount, actorIndex);
    }

    battleSelectTargetParam->setTargetCharacterStatus(0, targetCharacterStatus[index]);
    battleSelectTargetParam->setTargetCount(1);
    battleSelectTargetParam->setTargetGroupIndex(targetCharacterGroup[index]);
    battleSelectTargetParam->setTargetIndex(targetCharacterIndex[index]);
    return true;
}

THUMB bool btl::BattleSelectTarget::setTargetGroup(BattleSelectTargetParam* battleSelectTargetParam)
{
    int groupList[4] = {-1};
    for (int i = 0; i < 4; i++) groupList[i] = -1;
    int groupCount;
    int memberCount;
    int liveCount;
    int targetGroup = battleSelectTargetParam->getTargetGroupIndex();

    liveCount = 0;
    groupCount = 0;
    if (battleSelectTargetParam->getCallTarget() == BattleSelectTargetParam::StartTurn && checkTurnSelectGroup(battleSelectTargetParam)) {
        return true;
    }
    if (!BattleSecondCheck::multipleCheckFirst(battleSelectTargetParam)
        && !battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().isMosyasExec()) {
        setNextAction(battleSelectTargetParam);
        return false;
    }

    memberCount = battleSelectTargetParam->getSourceCountForGroupDead(targetGroup);
    int enableCount = 0;
    int mahokantaCount = 0;
    for (; liveCount < memberCount; liveCount++) {
        if (BattleSecondCheck::personalCheckMahokanta(battleSelectTargetParam->getSourceCharacterStatusForGroupDead(targetGroup, liveCount))) {
            mahokantaCount++;
        }
        if (BattleSecondCheck::personalCheckLast(battleSelectTargetParam, targetGroup, liveCount)) {
            enableCount++;
        }
    }
    if (BattleSecondCheck::multipleCheckPercent(battleSelectTargetParam, memberCount, enableCount, mahokantaCount)) {
        groupList[groupCount] = targetGroup;
        groupCount++;
    }

    if (groupCount == 0 || battleSelectTargetParam->getActorCharacterStatus()->getCharacterType() == MONSTER) {
        for (int i = 0; i < 4; i++) {
            memberCount = battleSelectTargetParam->getSourceCountForGroupDead(i);
            if (memberCount != 0) {
                enableCount = 0;
                mahokantaCount = 0;
                for (; liveCount < memberCount; liveCount++) {
                    if (BattleSecondCheck::personalCheckMahokanta(battleSelectTargetParam->getSourceCharacterStatusForGroupDead(i, liveCount))) {
                        mahokantaCount++;
                    }
                    if (BattleSecondCheck::personalCheckLast(battleSelectTargetParam, i, liveCount)) {
                        enableCount++;
                    }
                }
                if (BattleSecondCheck::multipleCheckPercent(battleSelectTargetParam, memberCount, enableCount, mahokantaCount)) {
                    groupList[groupCount] = i;
                    groupCount++;
                } else if (battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().isMosyasExec()) {
                    groupList[groupCount] = i;
                    groupCount++;
                }
            }
        }
    }

    if (groupCount == 0) {
        setNextAction(battleSelectTargetParam);
        return false;
    }

    targetGroup = groupList[UnkDssRand::rand(groupCount)];
    memberCount = battleSelectTargetParam->getSourceCountForGroupDead(targetGroup);
    for (int i = 0; i < memberCount; i++) {
        battleSelectTargetParam->setTargetCharacterStatus(i, battleSelectTargetParam->getSourceCharacterStatusForGroupDead(targetGroup, i));
    }
    battleSelectTargetParam->setTargetCount(memberCount);
    battleSelectTargetParam->setTargetGroupIndex(targetGroup);
    return true;
}

THUMB bool btl::BattleSelectTarget::setTargetAllWithCarriage(BattleSelectTargetParam* battleSelectTargetParam)
{
    return setTargetAll(battleSelectTargetParam);
}

THUMB bool btl::BattleSelectTarget::setTargetAll(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::CharacterStatus* targetCharacterStatus;
    int targetCount = battleSelectTargetParam->getSourceCount();
    int enableCount = 0;
    int mahokantaCount = 0;

    if (battleSelectTargetParam->getCallTarget() == BattleSelectTargetParam::StartTurn && checkTurnSelectAll(battleSelectTargetParam)) {
        return true;
    }
    if (!BattleSecondCheck::personalCheckFirst(battleSelectTargetParam)
        && !battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().isMosyasExec()) {
        setNextAction(battleSelectTargetParam);
        return false;
    }

    for (int i = 0; i < targetCount; i++) {
        if (BattleSecondCheck::personalCheckMahokanta(battleSelectTargetParam->getSourceCharacterStatus(i))) {
            mahokantaCount++;
        }
        if (BattleSecondCheck::everyCheckLast(battleSelectTargetParam, i)) {
            enableCount++;
        }
    }

    if (!BattleSecondCheck::everyCheckPercent(battleSelectTargetParam, enableCount, mahokantaCount)) {
        if (battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().getHaveStatus().isPlayer() && battleSelectTargetParam->getActionIndex() == 0x1ec) {
            battleSelectTargetParam->setTargetCharacterStatus(0, battleSelectTargetParam->getActorCharacterStatus());
            battleSelectTargetParam->setTargetCount(1);
            return true;
        }
        if (!battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().isMosyasExec()) {
            setNextAction(battleSelectTargetParam);
            return false;
        }
    }

    int acceptCount = 0;
    for (int i = 0; i < targetCount; i++) {
        targetCharacterStatus = battleSelectTargetParam->getSourceCharacterStatus(i);
        status::HaveStatusInfo& statusInfo = targetCharacterStatus->getHaveStatusInfo();
        if (!statusInfo.isEscapeFlag() && !statusInfo.isDisappearFlag()) {
            if (battleSelectTargetParam->getActionIndex() != 0x3f || targetCount <= 1 || targetCharacterStatus != battleSelectTargetParam->getActorCharacterStatus()) {
                battleSelectTargetParam->setTargetCharacterStatus(acceptCount, targetCharacterStatus);
                acceptCount++;
            }
        }
    }
    battleSelectTargetParam->setTargetCount(acceptCount);
    return true;
}

THUMB void btl::BattleSelectTarget::setNextAction(BattleSelectTargetParam* targetParam)
{
    targetParam->getActorCharacterStatus()->getHaveBattleStatus().setActionDisable2nd();
    targetParam->getActorCharacterStatus()->getHaveBattleStatus().setActionSelect(status::HaveBattleStatus::StartRound, true);
}

THUMB void btl::BattleSelectTarget::setTargetSpecial(status::UseActionParam* useActionParam)
{
    if (useActionParam->getActorCharacterStatus()->getCharacterType() == PLAYER) {
        setTargetSpecialToMonster(useActionParam);
    }
    if (useActionParam->getActorCharacterStatus()->getCharacterType() == MONSTER) {
        setTargetSpecialToPlayer(useActionParam);
        useActionParam->getTargetCharacterStatus(0)->getHaveStatusInfo().addSpecialTargetCount();
    }
}

THUMB void btl::BattleSelectTarget::setTargetSpecialToPlayer(status::UseActionParam* useActionParam)
{
    if (g_StadiumData.isStadiumBattle()) {
        return;
    }

    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    int aliveCount = 0;
    for (int i = 0; i < count; i++) {
        if (!status::g_Party.isInsideCarriage(i) && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            aliveCount++;
        }
    }

    int index;
    switch (aliveCount) {
    case 1:
        index = 0;
        break;
    case 2: {
        int ratio[2] = {146, 110};
        index = dss::arrayToIndex(ratio, UnkDssRand::rand(256), 2);
        break;
    }
    case 3: {
        int ratio[3] = {114, 85, 57};
        index = dss::arrayToIndex(ratio, UnkDssRand::rand(256), 3);
        break;
    }
    default: {
        int ratio[4] = {113, 77, 45, 21};
        index = dss::arrayToIndex(ratio, UnkDssRand::rand(256), 4);
        break;
    }
    }

    int i;
    int alive = 0;
    for (i = 0; i < count; i++) {
        if (!status::g_Party.isInsideCarriage(i) && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            if (index == alive) {
                index = i;
                break;
            }
            alive++;
        }
    }

    useActionParam->setTargetCharacterStatus(0, &status::g_Party.getPlayerStatus(index));
    useActionParam->setTargetCount(1);
    int effectValue = status::getUsuallyAttackEffectValue(useActionParam->getActorCharacterStatus(), &status::g_Party.getPlayerStatus(index));
    useActionParam->setEffectValue(effectValue);
    useActionParam->setPlayerEffectValue(effectValue);
    useActionParam->setMonsterEffectValue(effectValue);
    useActionParam->setDamage(effectValue);
}

THUMB void btl::BattleSelectTarget::setTargetSpecialToMonster(status::UseActionParam* useActionParam)
{
    BattleSelectTargetParam battleSelectTargetParam;
    battleSelectTargetParam.clear();
    setTargetMonster(&battleSelectTargetParam);

    int selectGroup = useActionParam->getActorCharacterStatus()->getHaveBattleStatus().getSelectGroup();
    battleSelectTargetParam.setTargetGroupIndex(selectGroup);
    int targetGroup = selectGroup;
    int targetCount = battleSelectTargetParam.getSourceCountForGroup(targetGroup);
    for (int i = 0; i < targetCount; i++) {
        specialTarget_[i] = battleSelectTargetParam.getSourceCharacterStatusForGroup(targetGroup, i);
    }
    for (int j = 0; j < 4; j++) {
        if (j != targetGroup && targetCount == 0) {
            targetCount = battleSelectTargetParam.getSourceCountForGroup(j);
            for (int i = 0; i < targetCount; i++) {
                targetGroup = j;
                specialTarget_[i] = battleSelectTargetParam.getSourceCharacterStatusForGroup(j, i);
            }
        }
    }

    int damage[8];
    for (int i = 0; i < 8; i++) damage[i] = 0;
    for (int i = 0; i < targetCount; i++) {
        specialTarget_[i]->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA);
    }
    for (int i = 0; i < targetCount; i++) {
        if (!specialTarget_[i]->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA)) {
            useActionParam->setTargetCharacterStatus(0, specialTarget_[i]);
            status::ActionEffectValue::clearEffectValue();
            status::ActionEffectValue::setEffectValue(useActionParam, true);
            int effectValue = useActionParam->getEffectValue();
            useActionParam->setDamage(effectValue);
            break;
        }
    }
    for (int i = 0; i < targetCount; i++) {
        damage[i] = useActionParam->getPlayerEffectValue();
        specialTarget_[i]->getHaveStatusInfo().setSpecialTargetDamage(damage[i]);
    }

    int count = targetCount;
    count = setTargetSpecialToMonsterNoAstoron(count);
    if (count == 1) {
        setTargetSpecialToParam2(useActionParam);
        return;
    }
    count = setTargetSpecialToMonsterNoSleep(count);
    if (count == 1) {
        setTargetSpecialToParam2(useActionParam);
        return;
    }
    count = setTargetSpecialToMonsterNoSpazz2(count);
    if (count == 1) {
        setTargetSpecialToParam2(useActionParam);
        return;
    }
    count = setTargetSpecialToMonsterNoConfusion2(count);
    if (count == 1) {
        setTargetSpecialToParam2(useActionParam);
        return;
    }
    count = setTargetSpecialToMonsterNearDeath2(count);
    if (count == 1) {
        setTargetSpecialToParam2(useActionParam);
        return;
    }
    count = setTargetSpecialToMonsterHpMin2(count);
    if (count == 1) {
        setTargetSpecialToParam2(useActionParam);
        return;
    }
}

THUMB int btl::BattleSelectTarget::setTargetSpecialToMonsterNoAstoron(int targetCount)
{
    int tempCount = 0;
    status::CharacterStatus* tempTarget[8] = {0};
    for (int i = 0; i < 8; i++) tempTarget[i] = NULL;
    for (int i = 0; i < targetCount; i++) {
        status::StatusChange& statusChange = specialTarget_[i]->getHaveStatusInfo().getStatusChange();
        if (!statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
            tempTarget[tempCount++] = specialTarget_[i];
        }
    }
    if (tempCount != 0) {
        for (int i = 0; i < 8; i++) specialTarget_[i] = NULL;
        for (int i = 0; i < tempCount; i++) specialTarget_[i] = tempTarget[i];
    } else {
        tempCount = targetCount;
    }
    return tempCount;
}

THUMB int btl::BattleSelectTarget::setTargetSpecialToMonsterNoSleep(int targetCount)
{
    int tempCount = 0;
    status::CharacterStatus* tempTarget[8] = {0};
    for (int i = 0; i < 8; i++) tempTarget[i] = NULL;
    for (int i = 0; i < targetCount; i++) {
        status::StatusChange& statusChange = specialTarget_[i]->getHaveStatusInfo().getStatusChange();
        if (!statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
            tempTarget[tempCount++] = specialTarget_[i];
        }
    }
    if (tempCount != 0) {
        for (int i = 0; i < 8; i++) specialTarget_[i] = NULL;
        for (int i = 0; i < tempCount; i++) specialTarget_[i] = tempTarget[i];
    } else {
        tempCount = targetCount;
    }
    return tempCount;
}

THUMB int btl::BattleSelectTarget::setTargetSpecialToMonsterNoSpazz2(int targetCount)
{
    int tempCount = 0;
    status::CharacterStatus* tempTarget[8] = {0};
    for (int i = 0; i < 8; i++) tempTarget[i] = NULL;
    for (int i = 0; i < targetCount; i++) {
        status::StatusChange& statusChange = specialTarget_[i]->getHaveStatusInfo().getStatusChange();
        if (!statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            tempTarget[tempCount++] = specialTarget_[i];
        }
    }
    if (tempCount != 0) {
        for (int i = 0; i < 8; i++) specialTarget_[i] = NULL;
        for (int i = 0; i < tempCount; i++) specialTarget_[i] = tempTarget[i];
    } else {
        tempCount = targetCount;
    }
    return tempCount;
}

THUMB int btl::BattleSelectTarget::setTargetSpecialToMonsterNoConfusion2(int targetCount)
{
    int tempCount = 0;
    status::CharacterStatus* tempTarget[8] = {0};
    for (int i = 0; i < 8; i++) tempTarget[i] = NULL;
    for (int i = 0; i < targetCount; i++) {
        status::StatusChange& statusChange = specialTarget_[i]->getHaveStatusInfo().getStatusChange();
        if (!statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
            tempTarget[tempCount++] = specialTarget_[i];
        }
    }
    if (tempCount != 0) {
        for (int i = 0; i < 8; i++) specialTarget_[i] = NULL;
        for (int i = 0; i < tempCount; i++) specialTarget_[i] = tempTarget[i];
    } else {
        tempCount = targetCount;
    }
    return tempCount;
}

THUMB int btl::BattleSelectTarget::setTargetSpecialToMonsterNearDeath2(int targetCount)
{
    int tempCount = 0;
    status::CharacterStatus* tempTarget[8] = {0};
    for (int i = 0; i < 8; i++) tempTarget[i] = NULL;
    for (int i = 0; i < targetCount; i++) {
        int damage = specialTarget_[i]->getHaveStatusInfo().getSpecialTargetDamage();
        if (specialTarget_[i]->getHaveStatusInfo().getHp() <= damage) {
            tempTarget[tempCount++] = specialTarget_[i];
        }
    }
    if (tempCount != 0) {
        for (int i = 0; i < 8; i++) specialTarget_[i] = NULL;
        for (int i = 0; i < tempCount; i++) specialTarget_[i] = tempTarget[i];

        int hpMax = 0;
        status::CharacterStatus* hpMaxTarget = NULL;
        for (int i = 0; i < tempCount; i++) {
            if (hpMax < specialTarget_[i]->getHaveStatusInfo().getHp()) {
                hpMax = specialTarget_[i]->getHaveStatusInfo().getHp();
                hpMaxTarget = specialTarget_[i];
            }
        }
        if (hpMaxTarget != NULL) {
            tempCount = 1;
            for (int i = 0; i < 8; i++) specialTarget_[i] = NULL;
            specialTarget_[0] = hpMaxTarget;
        }
    } else {
        tempCount = targetCount;
    }
    return tempCount;
}

THUMB int btl::BattleSelectTarget::setTargetSpecialToMonsterHpMin2(int targetCount)
{
    status::CharacterStatus* tempTarget;
    int rest[8];
    for (int i = 0; i < targetCount; i++) rest[i] = 0;
    for (int i = 0; i < targetCount; i++) {
        int damage = specialTarget_[i]->getHaveStatusInfo().getSpecialTargetDamage();
        rest[i] = specialTarget_[i]->getHaveStatusInfo().getHp() - damage;
    }
    int index = dss::arrayToMinIndex(rest, targetCount);
    tempTarget = specialTarget_[index];
    for (int i = 0; i < 8; i++) specialTarget_[i] = NULL;
    specialTarget_[0] = tempTarget;
    return 1;
}

THUMB void btl::BattleSelectTarget::setTargetSpecialToParam2(status::UseActionParam* useActionParam)
{
    if (specialTarget_[0] == NULL) {
        return;
    }
    if (specialTarget_[0]->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA)) {
        useActionParam->setTargetCharacterStatus(0, specialTarget_[0]);
        status::ActionEffectValue::clearEffectValue();
        status::ActionEffectValue::setEffectValue(useActionParam, true);
        int effectValue = useActionParam->getEffectValue();
        specialTarget_[0]->getHaveStatusInfo().setSpecialTargetDamage(effectValue);
    }
    useActionParam->setTargetCharacterStatus(0, specialTarget_[0]);
    useActionParam->setTargetCount(1);
    useActionParam->setDamage(specialTarget_[0]->getHaveStatusInfo().getSpecialTargetDamage());
}

THUMB bool btl::BattleSelectTarget::setTargetCrossFire(status::UseActionParam* useActionParam)
{
    BattleSelectTargetParam battleSelectTargetParam;
    battleSelectTargetParam.clear();
    battleSelectTargetParam.setActorCharacterStatus(useActionParam->getActorCharacterStatus());
    if (useActionParam->getActorCharacterStatus()->getCharacterType() == PLAYER) {
        setTargetMonster(&battleSelectTargetParam);
    }
    if (useActionParam->getActorCharacterStatus()->getCharacterType() == MONSTER) {
        setTargetPlayer(&battleSelectTargetParam);
    }

    int crossFire = useActionParam->getActorCharacterStatus()->getHaveBattleStatus().getCrossFire();
    if (crossFire == 0) {
        return false;
    }
    if (crossFire == 1) {
        int selectIndex = -1;
        int crossFireTarget = useActionParam->getActorCharacterStatus()->getHaveBattleStatus().getCrossFireTarget();
        if (crossFireTarget != -1) {
            int targetCount = battleSelectTargetParam.getSourceCount();
            for (int i = 0; i < targetCount; i++) {
                if (crossFireTarget == battleSelectTargetParam.getSourceCharacterStatus(i)->getArrayIndex()) {
                    selectIndex = i;
                    break;
                }
            }
        }
        if (selectIndex == -1) {
            crossFireTarget = -1;
        }
        if (crossFireTarget == -1) {
            int targetCount = battleSelectTargetParam.getSourceCount();
            selectIndex = UnkDssRand::rand(targetCount);
            battleSelectTargetParam.getActorCharacterStatus()->getHaveBattleStatus().setCrossFireTarget(battleSelectTargetParam.getSourceCharacterStatus(selectIndex)->getArrayIndex());
        }
        useActionParam->setTargetCharacterStatus(0, battleSelectTargetParam.getSourceCharacterStatus(selectIndex));
        useActionParam->setTargetCount(1);
    }
    if (crossFire == 2) {
        int rest[8];
        for (int i = 0; i < 8; i++) rest[i] = 0;
        int targetCount = battleSelectTargetParam.getTargetCount();
        for (int i = 0; i < targetCount; i++) {
            rest[i] = battleSelectTargetParam.getSourceCharacterStatus(i)->getHaveStatusInfo().getHp();
        }
        int index = dss::arrayToMinIndex(rest, targetCount);
        useActionParam->setTargetCharacterStatus(0, battleSelectTargetParam.getSourceCharacterStatus(index));
        useActionParam->setTargetCount(1);
    }
    if (crossFire == 3) {
        int targetCount = battleSelectTargetParam.getTargetCount();
        battleSelectTargetParam.setTargetCharacterStatus(0, battleSelectTargetParam.getSourceCharacterStatus(targetCount - 1));
        battleSelectTargetParam.setTargetCount(1);
        useActionParam->setTargetCharacterStatus(0, battleSelectTargetParam.getSourceCharacterStatus(0));
        useActionParam->setTargetCount(1);
    }
    return true;
}

THUMB void btl::BattleSelectTarget::setActorAction(status::UseActionParam* useActionParam, BattleSelectTargetParam::CallTargetSelect call)
{
    status::CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor->getHaveStatusInfo().isDeath()) {
        return;
    }
    if (actor->getHaveStatusInfo().isMosyasExec()) {
        return;
    }
    if (actor->getHaveBattleStatus().getActionIndex() == 0x1de) {
        int actionIndex = actor->getHaveBattleStatus().getActionIndex();
        useActionParam->setActionIndex(actionIndex);
        return;
    }

    if (call == BattleSelectTargetParam::StartTurn) {
        if (actor->getHaveBattleStatus().getBrains() == 2) {
            actor->getHaveBattleStatus().setActionSelect(status::HaveBattleStatus::StartTurn, false);
        }
    } else {
        actor->getHaveBattleStatus().setActionSelect(status::HaveBattleStatus::StartRound, false);
    }
    if (useActionParam->getActionIndex() == 0) {
        if (call == BattleSelectTargetParam::StartTurn) {
            actor->getHaveBattleStatus().setActionSelect(status::HaveBattleStatus::StartTurn, false);
        } else {
            actor->getHaveBattleStatus().setActionSelect(status::HaveBattleStatus::StartRound, false);
        }
    }

    useActionParam->getActorCharacterStatus()->getHaveBattleStatus().setupTurnBeforeAction();
    int actionIndex = actor->getHaveBattleStatus().getActionIndex();
    useActionParam->setActionIndex(actionIndex);
    int sortIndex = actor->getHaveBattleStatus().getItemSortIndex();
    useActionParam->setItemSortIndex(sortIndex);
}
