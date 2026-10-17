#include "ov000/btl/BattleActor.hpp"
#include "ov000/btl/AutoAction.hpp"
#include "ov000/btl/BattleSelectTarget.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseAction.hpp"

inline status::UseActionMessage::UseActionMessage() { clear(); }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline bool status::HaveStatus::isFriendMonster() const { return playerType_ == TYPE_FRIENDMONSTER; }
inline status::HaveItem& status::HaveStatusInfo::getHaveItem() { return haveItem_; }
inline status::UseActionParam::UseActionParam() { clear(); }
inline status::UseActionParam::~UseActionParam() {}
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::CharacterStatus::getGroupIndex() { return characterGroup_; }
inline void status::UseActionParam::setActorCharacterStatus(CharacterStatus* info) { actorCharacterStatus_ = info; }
inline status::CharacterStatus* status::UseActionParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline int status::UseActionParam::getActionIndex() { return actionIndex_; }
inline void status::UseActionParam::setTargetCharacterStatus(int index, CharacterStatus* info) { targetCharacterStatus_[index] = info; }
inline void status::UseActionParam::setTargetCount(int count) { targetCount_ = count; }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

THUMB btl::BattleTargetExec::BattleTargetExec()
{
}

THUMB btl::BattleTargetExec::~BattleTargetExec()
{
}

THUMB btl::BattleActor::BattleActor()
{
}

THUMB btl::BattleActor::~BattleActor()
{
}

THUMB void btl::BattleActor::setup(status::CharacterStatus* characterStatus)
{
    if (characterStatus) {
        characterStatus_ = characterStatus;
        haveBattleStatus_ = &characterStatus->getHaveBattleStatus();
        agility_ = characterStatus->getHaveStatusInfo().getAgility(0);
        agility_ *= 10;
        agility_ = dss::getRandomVariation(agility_, 20, 20);
    }
    else {
        characterStatus_ = NULL;
        haveBattleStatus_ = NULL;
    }
    useActionParam_.clear();
    useActionParam_.setActorCharacterStatus(characterStatus);
}

THUMB void btl::BattleActor::setup()
{
    battleActorExec2_.setup(&useActionParam_);
    end_ = false;
    actorMode_ = ActorExecute;
}

THUMB void btl::BattleActor::execute()
{
    if (actorMode_ == ActorExecute) {
        if (!battleActorExec2_.execute()) {
            actorMode_ = ActorFinish;
        }
    }
    if (actorMode_ == ActorFinish) {
        if (!battleActorFinish_.execute()) {
            actorMode_ = ActorEnd;
        }
    }
    if (actorMode_ == ActorEnd) {
        battleActorExec2_.cleanup();
        end_ = true;
    }
}

THUMB int btl::BattleActor::isEnd()
{
    return end_;
}

THUMB void btl::BattleActor::reattack()
{
    useActionParam_.clear();
    useActionParam_.setActorCharacterStatus(characterStatus_);
    BattleSelectTarget::setActorAction(&useActionParam_, BattleSelectTargetParam::StartRound);
    BattleSelectTarget::setTarget(&useActionParam_, BattleSelectTargetParam::StartRound);
}

THUMB void btl::BattleActor::meganteRing()
{
    characterStatus_->getHaveBattleStatus().setupSpecialAction(0x1EC);
    int actionIndex = characterStatus_->getHaveBattleStatus().actionIndex_;
    useActionParam_.clear();
    useActionParam_.setActionIndex(actionIndex);
    useActionParam_.setActorCharacterStatus(characterStatus_);
    BattleSelectTarget::setTarget(&useActionParam_, BattleSelectTargetParam::StartRound);
}

THUMB void btl::BattleActor::rebirthStone()
{
    characterStatus_->getHaveBattleStatus().setupSpecialAction(0x1EB);
    int actionIndex = characterStatus_->getHaveBattleStatus().actionIndex_;
    useActionParam_.clear();
    useActionParam_.setActionIndex(actionIndex);
    useActionParam_.setActorCharacterStatus(characterStatus_);
    BattleSelectTarget::setTarget(&useActionParam_, BattleSelectTargetParam::StartRound);
}

THUMB void btl::BattleActor::setActionTargetOnRound()
{
    haveBattleStatus_->setActionSelect(status::HaveBattleStatus::StartRound, false);
    useActionParam_.setActionIndex(haveBattleStatus_->actionIndex_);
    useActionParam_.setActorCharacterStatus(characterStatus_);
    useActionParam_.itemSortIndex_ = haveBattleStatus_->sortIndex_;
    if (useActionParam_.getActionIndex() != 0x1DE) {
        selectAI(&useActionParam_, true);
        selectFriendMonster(&useActionParam_);
        BattleSelectTarget::setTarget(&useActionParam_, BattleSelectTargetParam::StartRound);
    }
}

THUMB void btl::BattleActor::setActionTargetOnTurn(status::UseActionParam* useActionParam, bool action)
{
    status::CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor->getHaveStatusInfo().isMosyasExec()) {
        return;
    }
    if (action) {
        BattleSelectTarget::setActorAction(useActionParam, BattleSelectTargetParam::StartTurn);
    }
    BattleSelectTarget::setTarget(useActionParam, BattleSelectTargetParam::StartTurn);
    if (useActionParam->getActionIndex() == 0x1DE || actor->getHaveBattleStatus().actionIndex_ == 0x1DE) {
        return;
    }
    if (useActionParam->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DORAGORAM)) {
        useActionParam->clear();
        actor->getHaveBattleStatus().setActionSelect(status::HaveBattleStatus::StartRound, false);
        useActionParam->setActionIndex(actor->getHaveBattleStatus().actionIndex_);
        useActionParam->setActorCharacterStatus(actor);
        BattleSelectTarget::setTarget(useActionParam, BattleSelectTargetParam::StartRound);
    }
    if (useActionParam->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
        useActionParam->clear();
        actor->getHaveBattleStatus().setupConfuseAction();
        useActionParam->setActionIndex(actor->getHaveBattleStatus().actionIndex_);
        useActionParam->setActorCharacterStatus(actor);
        BattleSelectTarget::setTarget(useActionParam, BattleSelectTargetParam::StartRound);
        BattleSelectTarget::setTarget(useActionParam, BattleSelectTargetParam::StartTurn);
    }
}

btl::AutoAction btl::autoAction;

THUMB void btl::BattleActor::selectAI(status::UseActionParam* useActionParam, bool roundCheck)
{
    status::CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (useActionParam->getActionIndex() == 0x1DE || actor->getHaveBattleStatus().actionIndex_ == 0x1DE) {
        return;
    }
    if (actor->getCharacterType() != PLAYER) {
        if (!actor->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
            return;
        }
    }
    if (actor->getHaveStatusInfo().haveStatus_.command_ == 5) {
        return;
    }
    if (!actor->getHaveStatusInfo().haveStatus_.isPlayer()) {
        return;
    }
    if (!actor->getHaveStatusInfo().isAttackEnable()) {
        return;
    }
    if (actor->getHaveStatusInfo().isMosyasExec()) {
        actor->getHaveStatusInfo().setCommandRandom(true);
    }
    if (actor->getCharacterType() == PLAYER && actor->getHaveStatusInfo().haveStatus_.isFriendMonster() && actor->getHaveStatusInfo().isCommandRandom()) {
        return;
    }
    int turnCount = status::g_BattleResult.battleTurnCount_;
    autoAction.clear();
    autoAction.setup((status::PlayerStatus*)actor, turnCount, roundCheck);
    if (actor->getHaveBattleStatus().getSelectCommand() == status::HaveBattleStatus::UseItem) {
        actor->getHaveStatusInfo().getHaveItem().getItem(actor->getHaveBattleStatus().selectItemIndex_);
        actor->getHaveBattleStatus().setActionSelect(status::HaveBattleStatus::StartRound, false);
    }
    int actionIndex = actor->getHaveBattleStatus().actionIndex_;
    useActionParam->clear();
    useActionParam->setActorCharacterStatus(actor);
    useActionParam->setActionIndex(actionIndex);
}

THUMB void btl::BattleActor::selectFriendMonster(status::UseActionParam* useActionParam)
{
    status::CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    if (actor->getCharacterType() != PLAYER || !actor->getHaveStatusInfo().haveStatus_.isFriendMonster()) {
        return;
    }
    if (actor->getHaveStatusInfo().getWisdom(0) >= 20) {
        return;
    }
    if (UnkDssRand::rand(2)) {
        actor->getHaveStatusInfo().setCommandRandom(true);
    }
    else {
        actor->getHaveStatusInfo().setCommandRandom(false);
        return;
    }
    int turnCount = status::g_BattleResult.battleTurnCount_;
    autoAction.clear();
    autoAction.setup((status::PlayerStatus*)actor, turnCount, false);
    if (actor->getHaveBattleStatus().getSelectCommand() == status::HaveBattleStatus::UseItem) {
        actor->getHaveStatusInfo().getHaveItem().getItem(actor->getHaveBattleStatus().selectItemIndex_);
        actor->getHaveBattleStatus().setActionSelect(status::HaveBattleStatus::StartRound, false);
    }
    int actionIndex = actor->getHaveBattleStatus().actionIndex_;
    useActionParam->clear();
    useActionParam->setActorCharacterStatus(actor);
    useActionParam->setActionIndex(actionIndex);
}

THUMB void btl::BattleActor::selectMosyasTarget(status::UseActionParam* useActionParam)
{
    status::CharacterStatus* actor = useActionParam->getActorCharacterStatus();
    int actionIndex = useActionParam->getActionIndex();
    if (!actor->getHaveStatusInfo().isMosyasExec()) {
        return;
    }
    BattleSelectTargetParam battleSelectTargetParam;
    battleSelectTargetParam.clear();
    battleSelectTargetParam.actionIndex_ = useActionParam->getActionIndex();
    battleSelectTargetParam.actorCharacterStatus_ = actor;
    battleSelectTargetParam.targetGroup_ = actor->getHaveBattleStatus().selectedGroup_;
    battleSelectTargetParam.targetIndex_ = actor->getHaveBattleStatus().selectedTarget_;
    switch (status::UseAction::getUseType(actionIndex)) {
    case status::UseAction::Myself:
        setTargetMyself(&battleSelectTargetParam);
        break;
    case status::UseAction::Friend:
        setTargetFriend(actionIndex, &battleSelectTargetParam);
        break;
    case status::UseAction::Enemy:
        setTargetEnemy(actionIndex, &battleSelectTargetParam);
        break;
    case status::UseAction::Both:
        setTargetBoth(&battleSelectTargetParam);
        break;
    case status::UseAction::None:
        setTargetMyself(&battleSelectTargetParam);
        break;
    }
    int count = battleSelectTargetParam.targetCount_;
    for (int i = 0; i < count; i++) {
        useActionParam->setTargetCharacterStatus(i, battleSelectTargetParam.getTargetCharacterStatus(i));
    }
    useActionParam->setTargetCount(count);
}

THUMB void btl::BattleActor::setTargetMyself(BattleSelectTargetParam* battleSelectTargetParam)
{
    battleSelectTargetParam->setTargetCharacterStatus(0, battleSelectTargetParam->actorCharacterStatus_);
    battleSelectTargetParam->targetCount_ = 1;
}

THUMB void btl::BattleActor::setTargetFriend(int actionIndex, BattleSelectTargetParam* battleSelectTargetParam)
{
    switch (status::UseAction::getUseArea(actionIndex)) {
    case status::UseAction::Zero:
        battleSelectTargetParam->targetCount_ = 1;
        battleSelectTargetParam->setTargetCharacterStatus(0, battleSelectTargetParam->actorCharacterStatus_);
        break;
    case status::UseAction::One:
        setTargetOneFriend(battleSelectTargetParam);
        break;
    case status::UseAction::Group:
        setTargetGroupFriend(battleSelectTargetParam);
        break;
    case status::UseAction::All:
        setTargetAllFriend(battleSelectTargetParam);
        break;
    case status::UseAction::Horse:
    case status::UseAction::UsuallyHorse:
    case status::UseAction::BattleHorse:
        setTargetAllFriend(battleSelectTargetParam);
        break;
    }
}

THUMB void btl::BattleActor::setTargetEnemy(int actionIndex, BattleSelectTargetParam* battleSelectTargetParam)
{
    switch (status::UseAction::getUseArea(actionIndex)) {
    case status::UseAction::Zero:
        battleSelectTargetParam->targetCount_ = 1;
        battleSelectTargetParam->setTargetCharacterStatus(0, battleSelectTargetParam->actorCharacterStatus_);
        break;
    case status::UseAction::One:
        setTargetOneEnemy(battleSelectTargetParam);
        break;
    case status::UseAction::Group:
        setTargetGroupEnemy(battleSelectTargetParam);
        break;
    case status::UseAction::All:
        setTargetAllEnemy(battleSelectTargetParam);
        break;
    case status::UseAction::Horse:
    case status::UseAction::UsuallyHorse:
    case status::UseAction::BattleHorse:
        setTargetAllEnemy(battleSelectTargetParam);
        break;
    }
}

THUMB void btl::BattleActor::setTargetBoth(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::CharacterStatus* temp[8] = {};
    for (int i = 0; i < 8; i++) {
        temp[i] = NULL;
    }
    int idx = 0;
    int count = status::g_Monster.getCount();
    for (int i = 0; i < count; i++) {
        temp[idx] = &status::g_Monster.getMonsterStatus(i);
        idx++;
    }
    status::g_Party.setBattleMode();
    count = status::g_Party.getCount();
    for (int i = 0; i < count; i++) {
        if (!status::g_Party.isInsideCarriage(i) && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            temp[idx] = &status::g_Party.getPlayerStatus(i);
            idx++;
        }
    }
    for (int i = 0; i < idx; i++) {
        battleSelectTargetParam->setTargetCharacterStatus(i, temp[i]);
    }
    battleSelectTargetParam->targetCount_ = idx;
}

THUMB void btl::BattleActor::setTargetOneFriend(BattleSelectTargetParam* battleSelectTargetParam)
{
    int group = battleSelectTargetParam->targetGroup_;
    int count = status::g_Monster.getCount();
    status::CharacterStatus* temp[8] = {};
    for (int i = 0; i < 8; i++) {
        temp[i] = NULL;
    }
    int idx = 0;
    for (int i = 0; i < count; i++) {
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            if (group == -1) {
                temp[idx] = &status::g_Monster.getMonsterStatus(i);
                idx++;
            }
            else if (group == status::g_Monster.getMonsterStatus(i).getGroupIndex()) {
                temp[idx] = &status::g_Monster.getMonsterStatus(i);
                idx++;
            }
        }
    }
    battleSelectTargetParam->targetCount_ = 1;
    battleSelectTargetParam->setTargetCharacterStatus(0, temp[UnkDssRand::rand(idx)]);
}

THUMB void btl::BattleActor::setTargetOneEnemy(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    status::CharacterStatus* temp[8] = {};
    for (int i = 0; i < 8; i++) {
        temp[i] = NULL;
    }
    int idx = 0;
    for (int i = 0; i < count; i++) {
        if (!status::g_Party.isInsideCarriage(i) && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            temp[idx] = &status::g_Party.getPlayerStatus(i);
            idx++;
        }
    }
    battleSelectTargetParam->targetCount_ = 1;
    battleSelectTargetParam->setTargetCharacterStatus(0, temp[UnkDssRand::rand(idx)]);
}

THUMB void btl::BattleActor::setTargetGroupFriend(BattleSelectTargetParam* battleSelectTargetParam)
{
    int group = battleSelectTargetParam->targetGroup_;
    int count = status::g_Monster.getCount();
    status::CharacterStatus* temp[8] = {};
    for (int i = 0; i < 8; i++) {
        temp[i] = NULL;
    }
    int idx = 0;
    for (int i = 0; i < count; i++) {
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            if (group == -1) {
                temp[idx] = &status::g_Monster.getMonsterStatus(i);
                idx++;
            }
            else if (group == status::g_Monster.getMonsterStatus(i).getGroupIndex()) {
                temp[idx] = &status::g_Monster.getMonsterStatus(i);
                idx++;
            }
        }
    }
    for (int i = 0; i < idx; i++) {
        battleSelectTargetParam->setTargetCharacterStatus(i, temp[i]);
    }
    battleSelectTargetParam->targetCount_ = idx;
}

THUMB void btl::BattleActor::setTargetGroupEnemy(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    status::CharacterStatus* temp[8] = {};
    for (int i = 0; i < 8; i++) {
        temp[i] = NULL;
    }
    int idx = 0;
    for (int i = 0; i < count; i++) {
        if (!status::g_Party.isInsideCarriage(i) && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            temp[idx] = &status::g_Party.getPlayerStatus(i);
            idx++;
        }
    }
    for (int i = 0; i < idx; i++) {
        battleSelectTargetParam->setTargetCharacterStatus(i, temp[i]);
    }
    battleSelectTargetParam->targetCount_ = idx;
}

THUMB void btl::BattleActor::setTargetAllFriend(BattleSelectTargetParam* battleSelectTargetParam)
{
    int count = status::g_Monster.getCount();
    status::CharacterStatus* temp[8] = {};
    for (int i = 0; i < 8; i++) {
        temp[i] = NULL;
    }
    int idx = 0;
    for (int i = 0; i < count; i++) {
        if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
            temp[idx] = &status::g_Monster.getMonsterStatus(i);
            idx++;
        }
    }
    for (int i = 0; i < idx; i++) {
        battleSelectTargetParam->setTargetCharacterStatus(i, temp[i]);
    }
    battleSelectTargetParam->targetCount_ = idx;
}

THUMB void btl::BattleActor::setTargetAllEnemy(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::g_Party.setBattleMode();
    int count = status::g_Party.getCount();
    status::CharacterStatus* temp[8] = {};
    for (int i = 0; i < 8; i++) {
        temp[i] = NULL;
    }
    int idx = 0;
    for (int i = 0; i < count; i++) {
        if (!status::g_Party.isInsideCarriage(i) && !status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()) {
            temp[idx] = &status::g_Party.getPlayerStatus(i);
            idx++;
        }
    }
    for (int i = 0; i < idx; i++) {
        battleSelectTargetParam->setTargetCharacterStatus(i, temp[i]);
    }
    battleSelectTargetParam->targetCount_ = idx;
}

THUMB bool btl::BattleActor::isActionEnable()
{
    if (useActionParam_.getActorCharacterStatus()->getHaveStatusInfo().isDeath()) {
        return false;
    }
    if (useActionParam_.getActorCharacterStatus()->getHaveBattleStatus().escape_) {
        return false;
    }
    return !useActionParam_.getActorCharacterStatus()->getHaveStatusInfo().isStatusChangeRelease();
}
