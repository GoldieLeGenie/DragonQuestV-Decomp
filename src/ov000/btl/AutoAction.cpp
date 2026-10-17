#include "ov000/btl/AutoAction.hpp"
#include "ov000/status/MonsterStatus.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseItem.hpp"

inline status::HaveAction& status::HaveStatusInfo::getHaveAction() { return haveAction_; }
inline status::HaveItem& status::HaveStatusInfo::getHaveItem() { return haveItem_; }
inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline int status::HaveStatus::getLevel() const { return level_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::HaveStatus::getCommand() const { return command_; }
inline int status::HaveStatusInfo::getCommandType() const { return haveStatus_.getCommand(); }
inline int status::CharacterStatus::getCommandType() const { return haveStatusInfo_.getCommandType(); }
inline int status::HaveStatusInfo::getCommandTypeDebug() { return commandTypeDebug_; }
inline void status::HaveBattleStatus::setSelectGroup(int group) { selectedGroup_ = group; }
inline void status::HaveBattleStatus::setSelectTarget(int playerIndex) { selectedTarget_ = playerIndex; }
inline int status::MonsterStatus::getMonsterGroup() { return characterGroup_; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline char dq5::level::ActionParam::getMosyasu() { return (byte_4 & 0x4) >> 2; }
inline int btl::EncountData::getTileLevel() { return tileLevel_; }
inline int btl::Encount::getLevel() { return encountData_.getTileLevel(); }
inline int btl::AutoActionParam::getActionIndex() { return actionIndex_; }
inline int btl::AutoActionParam::getAction() { return actionIndex_; }
inline int btl::AutoActionParam::getItem() { return itemIndex_; }
inline int btl::AutoActionParam::getSelectGroup() { return maxGroup_; }
inline int btl::AutoActionParam::getSelectIndex() { return maxIndex_; }
inline int btl::AutoActionParam::getDamageRatio() { return lastDamageRate_[0]; }
inline void btl::AutoActionParam::setSelectGroup(int grp) { maxGroup_ = grp; }
inline void btl::AutoActionParam::setSelectIndex(int idx) { maxIndex_ = idx; }
inline void btl::AutoActionParam::setFlag(int group, int actionIndex) { actionFlag_[group].set(actionIndex); }
inline void btl::AutoActionParam::setBossMode(bool flag) { bossFlag_ = flag; }
inline void btl::AutoActionParam::setTurnCount(int count) { turnCount_ = count; }
inline void btl::AttackAutoActionParam::setNormalAttack(bool flag) { normalAttack_ = flag; }
inline void btl::AttackAutoActionParam::setNormalAttackRatio(int ratio) { normalAttackRatio_ = ratio; }
inline void btl::AttackAutoActionParam::setAttackActionRatio(int ratio) { attackActionRatio_ = ratio; }

int btl::AutoAction::attackActionRatio_ = 30;

THUMB btl::AutoAction::AutoAction()
{
    clear();
}

inline btl::AttackAutoActionParam::AttackAutoActionParam() {}
inline btl::AttackAutoActionParam::~AttackAutoActionParam() {}
inline btl::RecoveryAutoActionParam::RecoveryAutoActionParam() {}
inline btl::RecoveryAutoActionParam::~RecoveryAutoActionParam() {}
inline btl::DefenceAutoActionParam::DefenceAutoActionParam() {}
inline btl::DefenceAutoActionParam::~DefenceAutoActionParam() {}
inline btl::AssistAutoActionParam::AssistAutoActionParam() {}
inline btl::AssistAutoActionParam::~AssistAutoActionParam() {}

THUMB btl::AutoAction::~AutoAction()
{
}

THUMB void btl::AutoAction::clear()
{
    attackCount_ = 0;
    defenceCount_ = 0;
    assistCount_ = 0;
    recoveryCount_ = 0;
    for (int i = 0; i < ACTION_MAX; i++) {
        attackActionParam_[i].clear();
        defenceActionParam_[i].clear();
        assistActionParam_[i].clear();
        recoveryActionParam_[i].clear();
    }
    selectAction_ = 0;
    selectGroup_ = 0;
}

THUMB void btl::AutoAction::setup(status::PlayerStatus* player, int count, bool round)
{
    clear();
    turnCount_ = count;
    AutoActionParam::setTurnCount(count);
    player_ = player;
    if (player_->getCommandType() == 6) {
        setDebugAction();
        return;
    }
    setLevelDifference();
    if (Encount::getSingleton()->getLevel() == 0) {
        AutoActionParam::setBossMode(true);
    }
    else {
        AutoActionParam::setBossMode(false);
    }
    if (player_->getHaveStatusInfo().getCommandType() == 4) {
        AttackAutoActionParam::setNormalAttack(true);
        AttackAutoActionParam::setNormalAttackRatio(150);
        AttackAutoActionParam::setAttackActionRatio(120);
    }
    else if (player_->getHaveStatusInfo().getCommandType() == 1) {
        AttackAutoActionParam::setNormalAttack(true);
        AttackAutoActionParam::setNormalAttackRatio(130);
        AttackAutoActionParam::setAttackActionRatio(120);
    }
    else {
        AttackAutoActionParam::setNormalAttack(false);
        AttackAutoActionParam::setNormalAttackRatio(100);
        AttackAutoActionParam::setAttackActionRatio(100);
    }
    selectAction();
    selectMaxAction();
    setSelectAction();
    setRandomAction();
    if (!round) {
        switch (status::UseAction::getUseArea(selectAction_)) {
        case status::UseAction::Zero:
            break;
        case status::UseAction::One:
            if (selectGroup_ != -1) {
                AutoActionParam::setFlag(selectGroup_, selectAction_);
            }
            break;
        case status::UseAction::Group:
            if (selectGroup_ != -1) {
                AutoActionParam::setFlag(selectGroup_, selectAction_);
            }
            break;
        case status::UseAction::All:
            AutoActionParam::setFlag(0, selectAction_);
            AutoActionParam::setFlag(1, selectAction_);
            AutoActionParam::setFlag(2, selectAction_);
            AutoActionParam::setFlag(3, selectAction_);
            break;
        case status::UseAction::Horse:
            break;
        case status::UseAction::UsuallyHorse:
            break;
        case status::UseAction::BattleHorse:
            break;
        }
    }
}

THUMB void btl::AutoAction::selectAction()
{
    add(0x47, 0);
    if (player_->getHaveStatusInfo().isCommandRandom()) {
        add(0x49, 0);
    }
    {
        status::HaveAction& haveAction = player_->getHaveStatusInfo().getHaveAction();
        int count = haveAction.getCount();
        for (int i = 0; i < count; i++) {
            if (player_->getHaveStatusInfo().getCommandType() == 3) {
                if (status::UseAction::getActionType(haveAction.getAction(i)) == status::UseAction::ActionTypeMagic) {
                    if (!player_->getHaveStatusInfo().isCommandRandom()) {
                        continue;
                    }
                }
            }
            add(haveAction.getAction(i), 0);
        }
    }
    {
        status::HaveItem& haveItem = player_->getHaveStatusInfo().getHaveItem();
        int count = haveItem.getCount();
        for (int i = 0; i < count; i++) {
            int itemIndex = haveItem.getItem(i);
            if (!status::UseItem::isLost(itemIndex)) {
                add(status::UseItem::getBattleUseAction(itemIndex), itemIndex);
            }
        }
    }
}

THUMB void btl::AutoAction::selectMaxAction()
{
    int max = -1;
    attackMaxIndex_ = -1;
    for (int i = 0; i < attackCount_; i++) {
        if (max < attackActionParam_[i].getSelectValue()) {
            max = attackActionParam_[i].getSelectValue();
            attackMaxIndex_ = i;
        }
    }
    if (attackMaxIndex_ == -1) {
        for (int i = 0; i < attackCount_; i++) {
            if (attackActionParam_[i].getActionIndex() == 0x47) {
                attackMaxIndex_ = i;
                break;
            }
        }
    }
    max = 0;
    recoveryMaxIndex_ = -1;
    for (int i = 0; i < recoveryCount_; i++) {
        if (max < recoveryActionParam_[i].getSelectValue()) {
            max = recoveryActionParam_[i].getSelectValue();
            recoveryMaxIndex_ = i;
        }
    }
    max = -1;
    defenceMaxIndex_ = -1;
    for (int i = 0; i < defenceCount_; i++) {
        if (max < defenceActionParam_[i].getSelectValue()) {
            max = defenceActionParam_[i].getSelectValue();
            defenceMaxIndex_ = i;
        }
    }
    max = 0;
    assistMaxIndex_ = -1;
    for (int i = 0; i < assistCount_; i++) {
        if (max < assistActionParam_[i].getSelectValue()) {
            max = assistActionParam_[i].getSelectValue();
            assistMaxIndex_ = i;
        }
    }
}

THUMB void btl::AutoAction::setRandomAction()
{
    if (!player_->getHaveStatusInfo().isCommandRandom()) {
        return;
    }
    AutoActionParam* autoActionParam[16] = {};
    for (int i = 0; i < 16; i++) {
        autoActionParam[i] = NULL;
    }
    int idx = 0;
    for (int i = 0; i < attackCount_; i++) {
        autoActionParam[idx] = &attackActionParam_[i];
        idx++;
    }
    for (int i = 0; i < recoveryCount_; i++) {
        autoActionParam[idx] = &recoveryActionParam_[i];
        if ((recoveryActionParam_[i].getActionIndex() == 0x3D || recoveryActionParam_[i].getActionIndex() == 0x3E) && player_->getCharacterType() == PLAYER) {
            int count = status::g_Party.getCarriageOutCount();
            recoveryActionParam_[i].setSelectGroup(0);
            int index = UnkDssRand::rand(count);
            recoveryActionParam_[i].setSelectIndex(index);
        }
        idx++;
    }
    for (int i = 0; i < defenceCount_; i++) {
        autoActionParam[idx] = &defenceActionParam_[i];
        idx++;
    }
    for (int i = 0; i < assistCount_; i++) {
        autoActionParam[idx] = &assistActionParam_[i];
        idx++;
    }
    int index = UnkDssRand::rand(idx);
    int actionIndex = autoActionParam[index]->getAction();
    int itemIndex = autoActionParam[index]->getItem();
    int groupIndex = autoActionParam[index]->getSelectGroup();
    int targetIndex = autoActionParam[index]->getSelectIndex();
    switch (status::UseAction::getUseArea(actionIndex)) {
    case status::UseAction::Zero:
    case status::UseAction::One:
        break;
    case status::UseAction::Group:
        targetIndex = -1;
        break;
    case status::UseAction::All:
        targetIndex = -1;
        break;
    case status::UseAction::Horse:
    case status::UseAction::UsuallyHorse:
    case status::UseAction::BattleHorse:
        targetIndex = -1;
        break;
    }
    setAction(actionIndex, itemIndex, groupIndex, targetIndex);
}

THUMB void btl::AutoAction::setLevelDifference()
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    int level = 0;
    for (int i = 0; i < count; i++) {
        level += status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getLevel();
    }
    playerLevel_ = level / count;
    monsterLevel_ = Encount::getSingleton()->getLevel();
    if (monsterLevel_ == 0) {
        monsterLevel_ = 99;
    }
}

THUMB void btl::AutoAction::setSelectAction()
{
    if (player_->getHaveStatusInfo().getCommandType() == 4) {
        setSelectAttackAction(false);
        setSelectDefenceAction();
        setSelectAssistAction();
        setForceDefenceAction();
    }
    else {
        setSelectAttackAction(false);
        setSelectAssistAction();
        setSelectDefenceAction();
        setForceDefenceAction();
    }
    setSelectAttackAction(true);
    setSelectRecoveryAction();
}

THUMB void btl::AutoAction::add(int actionIndex, int itemIndex)
{
    if (!validAction(actionIndex)) {
        return;
    }
    switch (status::UseAction::getAIType(actionIndex)) {
    case status::UseAction::Attack:
        attackActionParam_[attackCount_].setup(actionIndex, itemIndex, player_);
        attackCount_++;
        break;
    case status::UseAction::Defence:
        defenceActionParam_[defenceCount_].setup(actionIndex, itemIndex, player_);
        defenceCount_++;
        break;
    case status::UseAction::Assist:
        assistActionParam_[assistCount_].setup(actionIndex, itemIndex, player_);
        assistCount_++;
        break;
    case status::UseAction::Recovery:
        recoveryActionParam_[recoveryCount_].setup(actionIndex, itemIndex, player_);
        recoveryCount_++;
        break;
    case status::UseAction::Invalid:
        break;
    }
}

THUMB bool btl::AutoAction::validAction(int actionIndex)
{
    if (actionIndex == 0x3F) {
        return false;
    }
    if (status::UseAction::getUseMp(actionIndex) != 0) {
        if (status::UseAction::getUseMp(actionIndex) > player_->getHaveStatusInfo().getMp()) {
            return false;
        }
    }
    if (status::UseAction::isMahoton(actionIndex)) {
        status::StatusChange& statusChange = player_->getHaveStatusInfo().getStatusChange();
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON)) {
            return false;
        }
        if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_FIZZLEZONE)) {
            return false;
        }
    }
    if (!dq5::level::ActionParam::getRecord(actionIndex)->getMosyasu() && player_->getHaveStatusInfo().isMosyasExec()) {
        return false;
    }
    if (actionIndex == 0x49) {
        if (player_->getHaveStatusInfo().isCommandRandom() != false) {
            return true;
        }
        return false;
    }
    if (player_->getHaveStatusInfo().getCommandType() == 4) {
        if (actionIndex == 3) {
            return false;
        }
        if (actionIndex == 6) {
            return false;
        }
        if (actionIndex == 9) {
            return false;
        }
        if (actionIndex == 0xC) {
            return false;
        }
        if (actionIndex == 0x10) {
            return false;
        }
        if (actionIndex == 0x11) {
            return false;
        }
    }
    return true;
}

THUMB void btl::AutoAction::setSelectAttackAction(bool flag)
{
    if (selectAction_ != 0) {
        return;
    }
    if (attackMaxIndex_ == -1) {
        return;
    }
    if (player_->getHaveStatusInfo().getCommandType() == 2) {
        if (flag && selectAction_ == 0) {
            setAction(0x49, 0, -1, -1);
        }
        return;
    }
    {
        int actionIndex = attackActionParam_[attackMaxIndex_].getAction();
        int itemIndex = attackActionParam_[attackMaxIndex_].getItem();
        int groupIndex = attackActionParam_[attackMaxIndex_].getSelectGroup();
        int targetIndex = attackActionParam_[attackMaxIndex_].getSelectIndex();
        if (attackActionParam_[attackMaxIndex_].getDamageRatio() > attackActionRatio_) {
            setAction(actionIndex, itemIndex, groupIndex, targetIndex);
            if (actionIndex == 0x47 && groupIndex == -1) {
                setAction(0x49, 0, -1, -1);
            }
            return;
        }
        if (flag && selectAction_ == 0) {
            setAction(actionIndex, itemIndex, groupIndex, targetIndex);
            if (actionIndex == 0x47 && groupIndex == -1) {
                setAction(0x49, 0, -1, -1);
            }
        }
    }
}

THUMB void btl::AutoAction::setSelectRecoveryAction()
{
    setAntiPoisonAction();
    setRecoveryAction();
    setAntiSpazzAction();
    setAntiVenomAction();
    setRebirthAction();
}

THUMB void btl::AutoAction::setSelectAssistAction()
{
    if (selectAction_ == 0) {
        setAssistAction();
    }
}

THUMB void btl::AutoAction::setAssistAction()
{
    if (player_->getHaveStatusInfo().getCommandType() == 0) {
        return;
    }
    if (assistMaxIndex_ == -1) {
        return;
    }
    int actionIndex = assistActionParam_[assistMaxIndex_].getAction();
    int itemIndex = assistActionParam_[assistMaxIndex_].getItem();
    int groupIndex = assistActionParam_[assistMaxIndex_].getSelectGroup();
    int targetIndex = assistActionParam_[assistMaxIndex_].getSelectIndex();
    if (status::UseAction::getUseArea(actionIndex) != status::UseAction::One) {
        targetIndex = -1;
    }
    setAction(actionIndex, itemIndex, groupIndex, targetIndex);
}

THUMB void btl::AutoAction::setSelectDefenceAction()
{
    if (selectAction_ == 0) {
        setDefenceAction();
    }
}

THUMB void btl::AutoAction::setForceDefenceAction()
{
    int ratio = player_->getHaveStatusInfo().getHp() * 100 / player_->getHaveStatusInfo().getHpMax();
    if (player_->getHaveStatusInfo().getCommandType() == 4 || player_->getHaveStatusInfo().getCommandType() == 3) {
        if (ratio <= 30) {
            setAction(0x49, 0, -1, -1);
        }
    }
    if (selectAction_ == 0) {
        if (player_->getHaveStatusInfo().getCommandType() == 1 || player_->getHaveStatusInfo().getCommandType() == 2) {
            bool recoveryFlag = false;
            if (recoveryMaxIndex_ != -1 && recoveryActionParam_[recoveryMaxIndex_].getSelectValue() != 0) {
                recoveryFlag = true;
            }
            if (recoveryFlag && ratio <= 30) {
                setAction(0x49, 0, -1, -1);
            }
        }
    }
}

THUMB void btl::AutoAction::setDefenceAction()
{
    if (player_->getHaveStatusInfo().getCommandType() == 0) {
        return;
    }
    if (defenceMaxIndex_ == -1) {
        return;
    }
    int actionIndex = defenceActionParam_[defenceMaxIndex_].getAction();
    int itemIndex = defenceActionParam_[defenceMaxIndex_].getItem();
    int groupIndex = defenceActionParam_[defenceMaxIndex_].getSelectGroup();
    int targetIndex = defenceActionParam_[defenceMaxIndex_].getSelectIndex();
    if (status::UseAction::getUseArea(actionIndex) != status::UseAction::One) {
        targetIndex = -1;
    }
    setAction(actionIndex, itemIndex, groupIndex, targetIndex);
}

THUMB void btl::AutoAction::setRecoveryAction()
{
    if (recoveryMaxIndex_ == -1) {
        return;
    }
    int hp = 30;
    if (player_->getHaveStatusInfo().getCommandType() == 0) {
        hp = 30;
    }
    if (player_->getHaveStatusInfo().getCommandType() == 4) {
        hp = 70;
    }
    if (player_->getHaveStatusInfo().getCommandType() == 1) {
        hp = 50;
    }
    if (player_->getHaveStatusInfo().getCommandType() == 3) {
        hp = 50;
    }
    if (player_->getHaveStatusInfo().getCommandType() == 2) {
        hp = 50;
    }
    if (recoveryActionParam_[recoveryMaxIndex_].isMemberHpDown(100 - hp)) {
        int actionIndex = recoveryActionParam_[recoveryMaxIndex_].getAction();
        int itemIndex = recoveryActionParam_[recoveryMaxIndex_].getItem();
        int groupIndex = recoveryActionParam_[recoveryMaxIndex_].getSelectGroup();
        int targetIndex = recoveryActionParam_[recoveryMaxIndex_].getSelectIndex();
        if (status::UseAction::getUseType(actionIndex) == 0) {
            int tempHp = player_->getHaveStatusInfo().getHp();
            int tempHpMax = player_->getHaveStatusInfo().getHpMax();
            if (tempHp * 100 / tempHpMax >= hp) {
                return;
            }
        }
        if (status::UseAction::getUseArea(actionIndex) != status::UseAction::One) {
            targetIndex = -1;
        }
        setAction(actionIndex, itemIndex, groupIndex, targetIndex);
    }
}

THUMB void btl::AutoAction::setRebirthAction()
{
    if (recoveryMaxIndex_ == -1) {
        return;
    }
    if (!recoveryActionParam_[recoveryMaxIndex_].isMemberDeath()) {
        return;
    }
    int recoveryIndex = -1;
    for (int i = 0; i < recoveryCount_; i++) {
        if (recoveryActionParam_[i].getActionIndex() == 0x3D) {
            recoveryIndex = i;
            break;
        }
    }
    for (int i = 0; i < recoveryCount_; i++) {
        if (recoveryActionParam_[i].getActionIndex() == 0x3E) {
            recoveryIndex = i;
            break;
        }
    }
    if (recoveryIndex != -1) {
        setAction(recoveryActionParam_[recoveryIndex].getActionIndex(), 0, recoveryActionParam_[recoveryIndex].getSelectGroup(), recoveryActionParam_[recoveryIndex].getSelectIndex());
    }
}

THUMB void btl::AutoAction::setAntiSpazzAction()
{
    if (recoveryCount_ == 0) {
        return;
    }
    if (!recoveryActionParam_[0].getMemberSpazz()) {
        return;
    }
    int recoveryIndex = -1;
    for (int i = 0; i < recoveryCount_; i++) {
        if (recoveryActionParam_[i].getActionIndex() == 0x41) {
            recoveryIndex = i;
            break;
        }
    }
    if (recoveryIndex != -1) {
        int actionIndex = recoveryActionParam_[recoveryIndex].getActionIndex();
        setAction(actionIndex, 0, 0, -1);
    }
}

THUMB void btl::AutoAction::setAntiPoisonAction()
{
    if (recoveryCount_ == 0) {
        return;
    }
    if (!recoveryActionParam_[0].getMemberPoison()) {
        return;
    }
    int recoveryIndex = -1;
    for (int i = 0; i < recoveryCount_; i++) {
        if (recoveryActionParam_[i].getActionIndex() == 0x40) {
            recoveryIndex = i;
            break;
        }
    }
    if (recoveryIndex != -1) {
        int actionIndex = recoveryActionParam_[recoveryIndex].getActionIndex();
        int groupIndex = recoveryActionParam_[recoveryIndex].getSelectGroup();
        int targetIndex = recoveryActionParam_[recoveryIndex].getSelectIndex();
        setAction(actionIndex, -1, groupIndex, targetIndex);
    }
}

THUMB void btl::AutoAction::setAntiVenomAction()
{
    if (recoveryCount_ == 0) {
        return;
    }
    if (!recoveryActionParam_[0].getMemberVenom()) {
        return;
    }
    int recoveryIndex = -1;
    for (int i = 0; i < recoveryCount_; i++) {
        if (recoveryActionParam_[i].getActionIndex() == 0x40) {
            recoveryIndex = i;
            break;
        }
    }
    if (recoveryIndex != -1) {
        int actionIndex = recoveryActionParam_[recoveryIndex].getActionIndex();
        int groupIndex = recoveryActionParam_[recoveryIndex].getSelectGroup();
        int targetIndex = recoveryActionParam_[recoveryIndex].getSelectIndex();
        setAction(actionIndex, -1, groupIndex, targetIndex);
    }
}

THUMB void btl::AutoAction::setAction(int actionIndex, int itemIndex, int groupIndex, int targetIndex)
{
    if (player_->getCharacterType() == MONSTER) {
        if (groupIndex == ((status::MonsterStatus*)(status::CharacterStatus*)player_)->getMonsterGroup()) {
            if (actionIndex == 0x32) {
                actionIndex = 0x33;
            }
            if (actionIndex == 0x35) {
                actionIndex = 0x36;
            }
            if (actionIndex == 0x38) {
                actionIndex = 0x39;
            }
        }
        else {
            if (actionIndex == 0x32) {
                actionIndex = 0x34;
            }
            if (actionIndex == 0x35) {
                actionIndex = 0x37;
            }
            if (actionIndex == 0x38) {
                actionIndex = 0x3A;
            }
        }
    }
    if (actionIndex == 0x47) {
        player_->getHaveBattleStatus().setSelectCommand(status::HaveBattleStatus::Attack, actionIndex);
    }
    else if (actionIndex == 0x49) {
        player_->getHaveBattleStatus().setSelectCommand(status::HaveBattleStatus::Defence, actionIndex);
    }
    else if (actionIndex >= 0xDB && actionIndex <= 0x10C) {
        status::HaveItem& haveItem = player_->getHaveStatusInfo().getHaveItem();
        int count = haveItem.getCount();
        for (int i = 0; i < count; i++) {
            if (itemIndex == haveItem.getItem(i)) {
                player_->getHaveBattleStatus().setSelectCommand(status::HaveBattleStatus::UseItem, i);
                break;
            }
        }
    }
    else {
        player_->getHaveBattleStatus().setSelectCommand(status::HaveBattleStatus::UseAction, actionIndex);
    }
    player_->getHaveBattleStatus().setActionIndex(actionIndex);
    player_->getHaveBattleStatus().setSelectGroup(groupIndex);
    player_->getHaveBattleStatus().setSelectTarget(targetIndex);
    selectAction_ = actionIndex;
    selectGroup_ = groupIndex;
}

THUMB void btl::AutoAction::setDebugAction()
{
    switch (player_->getHaveStatusInfo().getCommandTypeDebug()) {
    case 0:
        setDebugDefenceAction();
        break;
    case 1:
        setDebugConfuseAction();
        break;
    case 2:
        setDebugNormalAttackAction(100);
        break;
    case 3:
        setDebugNormalAttackAction(50);
        break;
    case 4:
        setDebugNormalAttackAction(20);
        break;
    case 5:
        setDebugParupunteAction();
        break;
    }
    debugCount_++;
}

THUMB void btl::AutoAction::setDebugDefenceAction()
{
    setAction(0x49, 0, 0, -1);
}

THUMB void btl::AutoAction::setDebugConfuseAction()
{
    player_->getHaveStatusInfo().getStatusChange().setup(dq5::level::ActionParam::ACTIONTYPE_KONRAN, false);
}

THUMB void btl::AutoAction::setDebugNormalAttackAction(int count)
{
    switch (count) {
    case 100:
        setAction(0x47, 0, 0, -1);
        break;
    case 50:
        if (debugCount_ % 2 == 0) {
            setAction(0x47, 0, 0, -1);
        }
        else {
            setAction(0x49, 0, 0, -1);
        }
        break;
    case 20:
        if (debugCount_ % 5 == 0) {
            setAction(0x47, 0, 0, -1);
        }
        else {
            setAction(0x49, 0, 0, -1);
        }
        break;
    }
}

THUMB void btl::AutoAction::setDebugParupunteAction()
{
    setAction(0x42, -1, -1, -1);
}
