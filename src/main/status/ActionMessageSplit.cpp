#include "main/status/ActionMessageSplit.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/BaseActionStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/leveldata/SplitMessage.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/cmn/CommonRuraData.hpp"
#include "main/dss/UnkRandom.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

inline status::StatusChange& status::HaveStatusInfo::getStatusChange()
{
    return statusChange_;
}

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus()
{
    return haveStatus_;
}

inline status::HaveEquipment& status::HaveStatusInfo::getHaveEquipment()
{
    return haveEquipment_;
}

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline int status::UseActionMessage::getExecMessage(int index) { return execMessage_[index]; }
inline void status::UseActionMessage::setExecMessage(int index, int message) { execMessage_[index] = message; }
inline int status::UseActionMessage::getResultMessage(int index) { return resultMessage_[index]; }
inline void status::UseActionMessage::setResultMessage(int index, int message) { resultMessage_[index] = message; }
inline int status::UseActionMessage::getAddMessage(int index) { return addMessage_[index]; }
inline void status::UseActionMessage::setAddMessage(int index, int message) { addMessage_[index] = message; }
inline bool status::HaveStatus::isMonster() const { return playerType_ == TYPE_FRIENDMONSTER || playerType_ == TYPE_MONSTER; }
inline int status::StageAttribute::getTimestopFlag() { return timestop_; }
inline int status::StageInfo::getRiremitMapId() { return riremitMap_; }
inline int status::StageInfo::getRanaMapSurfaceId() { return lastFldSurface_; }
inline int status::StageInfo::getRanaMapNameId() { return lastRanaStageNameId_; }
inline int status::StageInfo::getkimeraSymbol() { return kimeraSymbol_; }
inline fld::FieldActionCarpet& fld::FieldPlayer::getActionCarpet() { return fieldActionCarpet_; }
inline dq5::level::SplitMessage* dq5::level::SplitMessage::getRecord(int index) { return (SplitMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned int dq5::level::SplitMessage::getArraySize() { return binary_.getRecordCount(); }
inline unsigned long dq5::level::SplitMessage::getBranch() { return branch; }
inline unsigned long dq5::level::SplitMessage::getCarriageTwo() { return carriageTwo; }
inline unsigned long dq5::level::SplitMessage::getAliveTwo() { return aliveTwo; }
inline unsigned long dq5::level::SplitMessage::getMonsterOne() { return monsterOne; }
inline unsigned long dq5::level::SplitMessage::getMonsterTwo() { return monsterTwo; }
inline unsigned long dq5::level::SplitMessage::getMonsterOneGroup() { return monsterOneGroup; }
inline unsigned long dq5::level::SplitMessage::getMonsterTwoGroup() { return monsterTwoGroup; }
inline unsigned long dq5::level::SplitMessage::getMonsterMore() { return monsterMore; }
inline unsigned long dq5::level::SplitMessage::getTargetMonster() { return targetMonster; }
inline unsigned long dq5::level::SplitMessage::getVenom() { return venom; }
inline unsigned long dq5::level::SplitMessage::getNotmanusa() { return notmanusa; }
inline unsigned long dq5::level::SplitMessage::getManusa() { return manusa; }
inline unsigned long dq5::level::SplitMessage::getNotempty() { return notempty; }
inline unsigned long dq5::level::SplitMessage::getEmpty() { return empty; }
inline unsigned long dq5::level::SplitMessage::getAlive() { return alive; }
inline unsigned long dq5::level::SplitMessage::getDead() { return dead; }
inline unsigned long dq5::level::SplitMessage::getAstoron() { return astoron; }
inline unsigned long dq5::level::SplitMessage::getMosyasu() { return mosyasu; }
inline unsigned long dq5::level::SplitMessage::getSplitAvoid() { return splitAvoid; }
inline unsigned long dq5::level::SplitMessage::getSplit() { return split; }
inline unsigned long dq5::level::SplitMessage::getAvoid() { return avoid; }
inline unsigned long dq5::level::SplitMessage::getEquip() { return equip; }
inline unsigned long dq5::level::SplitMessage::getNotEquit() { return notEquit; }
inline unsigned long dq5::level::SplitMessage::getMale() { return male; }
inline unsigned long dq5::level::SplitMessage::getFemale() { return female; }
inline unsigned long dq5::level::SplitMessage::getHuman() { return human; }
inline unsigned long dq5::level::SplitMessage::getMonster() { return monster; }
inline unsigned long dq5::level::SplitMessage::getJump() { return jump; }
inline unsigned long dq5::level::SplitMessage::getStrait() { return strait; }
inline unsigned long dq5::level::SplitMessage::getWastePlace() { return wastePlace; }
inline unsigned long dq5::level::SplitMessage::getRura() { return rura; }
inline unsigned long dq5::level::SplitMessage::getRiremito() { return riremito; }
inline unsigned long dq5::level::SplitMessage::getWasteTime() { return wasteTime; }
inline unsigned long dq5::level::SplitMessage::getCofferItem() { return cofferItem; }
inline unsigned long dq5::level::SplitMessage::getCofferMonster() { return cofferMonster; }
inline unsigned long dq5::level::SplitMessage::getCofferGold() { return cofferGold; }
inline unsigned long dq5::level::SplitMessage::getCofferNothing() { return cofferNothing; }
inline unsigned long dq5::level::SplitMessage::getTuboItem() { return tuboItem; }
inline unsigned long dq5::level::SplitMessage::getTuboMonster() { return tuboMonster; }
inline unsigned long dq5::level::SplitMessage::getTuboGold() { return tuboGold; }
inline unsigned long dq5::level::SplitMessage::getTuboNothing() { return tuboNothing; }
inline unsigned long dq5::level::SplitMessage::getNoTarget() { return noTarget; }
inline unsigned long dq5::level::SplitMessage::getRandom1() { return random1; }
inline unsigned long dq5::level::SplitMessage::getRandom2() { return random2; }
inline unsigned long dq5::level::SplitMessage::getRandom3() { return random3; }
inline unsigned long dq5::level::SplitMessage::getRandom4() { return random4; }
inline unsigned long dq5::level::SplitMessage::getRandom5() { return random5; }
inline unsigned long dq5::level::SplitMessage::getRandom6() { return random6; }
inline unsigned long dq5::level::SplitMessage::getRandom7() { return random7; }
inline unsigned long dq5::level::SplitMessage::getRandom8() { return random8; }
inline unsigned long dq5::level::SplitMessage::getRandom9() { return random9; }
inline unsigned long dq5::level::SplitMessage::getRandom10() { return random10; }
inline unsigned long dq5::level::SplitMessage::getRandom11() { return random11; }
inline unsigned long dq5::level::SplitMessage::getSpecial() { return special; }
inline unsigned long dq5::level::SplitMessage::getAliveOne() { return aliveOne; }
inline unsigned long dq5::level::SplitMessage::getCarriageOne() { return carriageOne; }
inline unsigned long dq5::level::SplitMessage::getNotvenom() { return notvenom; }
inline unsigned long dq5::level::SplitMessage::getTargetMale() { return targetMale; }
inline unsigned long dq5::level::SplitMessage::getTargetFemale() { return targetFemale; }
inline unsigned long dq5::level::SplitMessage::getTargetHuman() { return targetHuman; }

int status::ActionMessageSplit::actionIndex_;
int status::ActionMessageSplit::splitFlag_;

namespace status {
static dq5::level::SplitMessage* splitMessage_;

static THUMB void getSplitRecord(int index)
{
    splitMessage_ = dq5::level::SplitMessage::getRecord(index);
}
}

status::UseActionParam* status::ActionMessageSplit::useActionParam_;

THUMB int status::ActionMessageSplit::setSplitMessage(CharacterStatus* actor, CharacterStatus* target, UseActionMessage& useActionMessage, int actionIndex)
{
    int mess = useActionMessage.getExecMessage(0);
    actionIndex_ = actionIndex;
    if (mess == 0xaae62) {
        useActionMessage.setExecMessage(0, 0xc39c0);
        return true;
    }
    splitFlag_ = false;
    useActionMessage.setExecMessage(0, setSplitMessage(actor, target, useActionMessage.getExecMessage(0)));
    useActionMessage.setExecMessage(1, setSplitMessage(actor, target, useActionMessage.getExecMessage(1)));
    useActionMessage.setResultMessage(0, setSplitMessage(actor, target, useActionMessage.getResultMessage(0)));
    useActionMessage.setAddMessage(0, setSplitMessage(actor, target, useActionMessage.getAddMessage(0)));
    return splitFlag_;
}

THUMB int status::ActionMessageSplit::setSplitMessage(CharacterStatus* actor, CharacterStatus* target, int mess)
{
    int ret;
    int splitIndex = -1;
    if (mess == 0) {
        return 0;
    }
    if (mess == 0xaae62) {
        return 0xc39c0;
    }
    if (mess == 0xaae6c) {
        return 0xc392a;
    }
    if (mess > 0xc3500) {
        return mess;
    }
    unsigned int arrayMax = dq5::level::SplitMessage::getArraySize();
    for (unsigned int i = 0; i < arrayMax; i++) {
        getSplitRecord(i);
        if (mess == splitMessage_->getBranch()) {
            splitIndex = i;
            break;
        }
    }
    if (splitIndex == -1) {
        return mess;
    }
    ret = getMessagePlayerOne(target, splitIndex);
    if (ret == 0) {
        ret = getMessagePlayerMany(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessagePlayerOneInCarriage(splitIndex);
    }
    if (ret == 0) {
        ret = getMessagePlayerManyInCarriage(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageMonster1(useActionParam_, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageMonster2(useActionParam_, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageMonster1G(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageMonster2G(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageMonsterD(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetNoVenom(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetVenom(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetNoManusaAlready(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetManusaAlready(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetMpZero(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetMpNoZero(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetAlive(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetDead(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetAstoron(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetNoMosyasu(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetNoSplitNoJouk(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetSplit(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetJouk(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageWeaponEquipment(actor, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageNoWeaponEquipment(actor, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageActorMale(actor, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageActorFemale(actor, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageActorHuman(actor, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageActorMonster(actor, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetMale(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetFemale(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetHuman(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageTargetMonster(target, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageNoSpace(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageRulaOff(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageRiremitoOff(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageNoUse(actor, splitIndex);
    }
    if (ret == 0) {
        ret = getMessageVainTimeZon(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageNotNextMap(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageItemInBox(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageMonsterInBox(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageGoldInBox(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageZeroInBox(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageItemInPot(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageMonsterInPot(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageGoldInPot(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageZeroInPot(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageNoTarget(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageRandom(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageZero(splitIndex);
    }
    if (ret == 0) {
        ret = getMessageSpecial(splitIndex);
    }
    return ret;
}

THUMB int status::ActionMessageSplit::getMessagePlayerOne(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getAliveOne() == 0) {
        return mess;
    }
    if (target == NULL) {
        return mess;
    }
    if (target->getCharacterType() == PLAYER) {
        g_Party.setBattleMode();
        if (g_Party.getCarriageOutAliveCount() == 1) {
            mess = splitMessage_->getAliveOne();
            splitFlag_ = true;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessagePlayerMany(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getAliveTwo() == 0) {
        return mess;
    }
    if (target == NULL) {
        return mess;
    }
    if (target->getCharacterType() == PLAYER) {
        g_Party.setBattleMode();
        if (g_Party.getCarriageOutAliveCount() >= 2) {
            mess = splitMessage_->getAliveTwo();
            splitFlag_ = true;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessagePlayerOneInCarriage(int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getCarriageOne() == 0) {
        return mess;
    }
    g_Party.setBattleMode();
    if (g_Party.getCarriageAliveCount() == 1) {
        mess = splitMessage_->getCarriageOne();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessagePlayerManyInCarriage(int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getCarriageTwo() == 0) {
        return mess;
    }
    g_Party.setBattleMode();
    if (g_Party.getCarriageAliveCount() >= 2) {
        mess = splitMessage_->getCarriageTwo();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageMonster1(UseActionParam* useActionParam, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getMonsterOne() == 0) {
        return mess;
    }
    if (useActionParam->targetCount_ == 1) {
        mess = splitMessage_->getMonsterOne();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageMonster2(UseActionParam* useActionParam, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getMonsterTwo() == 0) {
        return mess;
    }
    if (useActionParam->targetCount_ >= 2) {
        mess = splitMessage_->getMonsterTwo();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageMonster1G(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getMonsterOneGroup() == 0) {
        return mess;
    }
    if (g_Monster.getMonsterCallType() == 0) {
        mess = splitMessage_->getMonsterOneGroup();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageMonster2G(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getMonsterTwoGroup() == 0) {
        return mess;
    }
    if (g_Monster.getMonsterCallType() == 1) {
        mess = splitMessage_->getMonsterTwoGroup();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageMonsterD(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getMonsterMore() == 0) {
        return mess;
    }
    if (g_Monster.getMonsterCallType() == 2) {
        mess = splitMessage_->getMonsterMore();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetNoVenom(CharacterStatus* target, int splitIndex)
{
    if (target == NULL) {
        return 0;
    }
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getNotvenom() == 0) {
        return mess;
    }
    if (!target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
        mess = splitMessage_->getNotvenom();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetVenom(CharacterStatus* target, int splitIndex)
{
    if (target == NULL) {
        return 0;
    }
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getVenom() == 0) {
        return mess;
    }
    if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
        mess = splitMessage_->getVenom();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetNoManusaAlready(CharacterStatus* target, int splitIndex)
{
    if (target == NULL) {
        return 0;
    }
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getNotmanusa() == 0) {
        return mess;
    }
    if (!target->getHaveStatusInfo().isManusaAlready()) {
        mess = splitMessage_->getNotmanusa();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetManusaAlready(CharacterStatus* target, int splitIndex)
{
    if (target == NULL) {
        return 0;
    }
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getManusa() == 0) {
        return mess;
    }
    if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
        mess = splitMessage_->getManusa();
        splitFlag_ = true;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetMpZero(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (target == NULL) {
        return mess;
    }
    if (BaseActionStatus::isMpZero()) {
        mess = splitMessage_->getEmpty();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetMpNoZero(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (target == NULL) {
        return mess;
    }
    if (!BaseActionStatus::isMpZero()) {
        mess = splitMessage_->getNotempty();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetAlive(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (target == NULL) {
        return mess;
    }
    if (!target->getHaveStatusInfo().isDeath()) {
        mess = splitMessage_->getAlive();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetDead(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (target == NULL) {
        return mess;
    }
    if (target->getHaveStatusInfo().isDeath()) {
        mess = splitMessage_->getDead();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetAstoron(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (target == NULL) {
        return mess;
    }
    if (target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
        mess = splitMessage_->getAstoron();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetNoMosyasu(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (target == NULL) {
        return mess;
    }
    if (!target->getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
        mess = splitMessage_->getMosyasu();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetNoSplitNoJouk(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    if (target == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getSplitAvoid() && !target->getHaveStatusInfo().isSplit() && !target->getHaveStatusInfo().isJouk()) {
        mess = splitMessage_->getSplitAvoid();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetSplit(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    if (target == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getSplit() && target->getHaveStatusInfo().isSplit()) {
        mess = splitMessage_->getSplit();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetJouk(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    if (target == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getAvoid() && target->getHaveStatusInfo().isJouk()) {
        mess = splitMessage_->getAvoid();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageWeaponEquipment(CharacterStatus* actor, int splitIndex)
{
    int mess = 0;
    if (actor == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getEquip() && actor->getHaveStatusInfo().getHaveEquipment().getEquipment(ITEM_WEAPON, 0)) {
        mess = splitMessage_->getEquip();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageNoWeaponEquipment(CharacterStatus* actor, int splitIndex)
{
    int mess = 0;
    if (actor == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getNotEquit() && !actor->getHaveStatusInfo().getHaveEquipment().getEquipment(ITEM_WEAPON, 0)) {
        mess = splitMessage_->getNotEquit();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageActorMale(CharacterStatus* actor, int splitIndex)
{
    int mess = 0;
    if (actor == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (actor->getHaveStatusInfo().getHaveStatus().getSex() == 0) {
        mess = splitMessage_->getMale();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageActorFemale(CharacterStatus* actor, int splitIndex)
{
    int mess = 0;
    if (actor == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (actor->getHaveStatusInfo().getHaveStatus().getSex() == 1) {
        mess = splitMessage_->getFemale();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageActorHuman(CharacterStatus* actor, int splitIndex)
{
    int mess = 0;
    if (actor == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (actor->getCharacterType() == PLAYER && !actor->getHaveStatusInfo().getHaveStatus().isMonster()) {
        mess = splitMessage_->getHuman();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageActorMonster(CharacterStatus* actor, int splitIndex)
{
    int mess = 0;
    if (actor == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (actor->getCharacterType() == PLAYER && actor->getHaveStatusInfo().getHaveStatus().isMonster()) {
        mess = splitMessage_->getMonster();
        splitFlag_ = false;
    }
    if (actor->getCharacterType() == MONSTER) {
        mess = splitMessage_->getMonster();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetMale(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    if (target == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (target->getHaveStatusInfo().getHaveStatus().getSex() == 0) {
        mess = splitMessage_->getTargetMale();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetFemale(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    if (target == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (target->getHaveStatusInfo().getHaveStatus().getSex() == 1) {
        mess = splitMessage_->getTargetFemale();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetHuman(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    if (target == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (target->getCharacterType() == PLAYER && !target->getHaveStatusInfo().getHaveStatus().isMonster()) {
        mess = splitMessage_->getTargetHuman();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageTargetMonster(CharacterStatus* target, int splitIndex)
{
    int mess = 0;
    if (target == NULL) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (target->getCharacterType() == PLAYER && target->getHaveStatusInfo().getHaveStatus().isMonster()) {
        mess = splitMessage_->getTargetMonster();
        splitFlag_ = false;
    }
    if (target->getCharacterType() == MONSTER) {
        mess = splitMessage_->getTargetMonster();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageNotNextMap(int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getJump()) {
        if (actionIndex_ == 0x81) {
            if (cmn::CommonRuraData::getSingleton().getRuraCount() == 0) {
                mess = splitMessage_->getJump();
                splitFlag_ = false;
            }
        }
        if (actionIndex_ == 0x137 || actionIndex_ == 0x13b) {
            if (g_StageInfo.getkimeraSymbol() == 0) {
                mess = splitMessage_->getJump();
                splitFlag_ = false;
            }
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageNoSpace(int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getStrait()) {
        if (actionIndex_ == 0x120 || actionIndex_ == 0x126) {
            if (data_02101c88.isCurrentPart(dq5::FIELD_PART) == true && g_Global.getFieldType() == 0
                && !fld::FieldPlayerManager::getSingleton().player_.fieldActionCarpet_.isCarpetGetOnOffAttr()) {
                mess = splitMessage_->getStrait();
            }
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageNoUse(CharacterStatus* actor, int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getWastePlace()) {
        if (actionIndex_ == 0x137 || actionIndex_ == 0x13b || actionIndex_ == 0x81 || actionIndex_ == 0x11e) {
            if (!g_StageAttribute.isRula()) {
                mess = splitMessage_->getWastePlace();
                splitFlag_ = false;
            }
        }
        if (actionIndex_ == 0x82) {
            if (!data_02101c88.isCurrentPart(dq5::TOWN_PART)) {
                mess = splitMessage_->getWastePlace();
                splitFlag_ = false;
            }
            if (!g_StageAttribute.isRiremito()) {
                mess = splitMessage_->getWastePlace();
                splitFlag_ = false;
            }
            if (g_StageInfo.getRiremitMapId() == 0) {
                mess = splitMessage_->getWastePlace();
                splitFlag_ = false;
            }
        }
        if (actionIndex_ == 0x86) {
            if (!g_StageAttribute.isLanaruta()) {
                mess = splitMessage_->getWastePlace();
                splitFlag_ = false;
            }
            if (data_02101c88.isCurrentPart(dq5::TOWN_PART) == true) {
                if (g_StageInfo.getRanaMapSurfaceId() == -1) {
                    mess = splitMessage_->getWastePlace();
                    splitFlag_ = false;
                }
                if (g_StageInfo.getRanaMapNameId() == 0) {
                    mess = splitMessage_->getWastePlace();
                    splitFlag_ = false;
                }
            }
        }
        if (actionIndex_ == 0x120 || actionIndex_ == 0x126) {
            if (data_02101c88.isCurrentPart(dq5::FIELD_PART) == true) {
                if (g_Global.getFieldType() != 0) {
                    mess = splitMessage_->getWastePlace();
                    splitFlag_ = false;
                }
            } else {
                mess = splitMessage_->getWastePlace();
                splitFlag_ = false;
            }
        }
        if (actionIndex_ == 0x14b) {
            if (!g_StageAttribute.getYami()) {
                mess = splitMessage_->getWastePlace();
                splitFlag_ = false;
            }
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageRulaOff(int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getRura()) {
        if (actionIndex_ == 0x81 || actionIndex_ == 0x13b || actionIndex_ == 0x137 || actionIndex_ == 0x11e) {
            if (g_StageAttribute.isRulaDisable() == true) {
                mess = splitMessage_->getRura();
                splitFlag_ = false;
            }
        }
        if (actionIndex_ == 0x86) {
            if (g_StageAttribute.isLanarutaDisable()) {
                mess = splitMessage_->getRura();
                splitFlag_ = false;
            }
            if (g_StageAttribute.getTimestopFlag()) {
                mess = splitMessage_->getRura();
                splitFlag_ = false;
            }
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageRiremitoOff(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x82) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getRiremito() && g_StageAttribute.isRiremitoDisable()) {
        mess = splitMessage_->getRiremito();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageVainTimeZon(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x14b) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getWasteTime()) {
        mess = splitMessage_->getWasteTime();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageItemInBox(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x84) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getCofferItem() && data_02101c88.isCurrentPart(dq5::TOWN_PART) == true) {
        int uid = twn::TownPlayerManager::getSingleton().getInpasMapObj();
        if (twn::TownFurnitureManager::getSingleton()->getCofferType(uid) == 0x44 && twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 3) {
            mess = splitMessage_->getCofferItem();
            splitFlag_ = false;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageMonsterInBox(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x84) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getCofferMonster() && data_02101c88.isCurrentPart(dq5::TOWN_PART) == true) {
        int uid = twn::TownPlayerManager::getSingleton().getInpasMapObj();
        if (twn::TownFurnitureManager::getSingleton()->getCofferType(uid) == 0x44 && twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 5) {
            mess = splitMessage_->getCofferMonster();
            splitFlag_ = false;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageGoldInBox(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x84) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getCofferGold() && data_02101c88.isCurrentPart(dq5::TOWN_PART) == true) {
        int uid = twn::TownPlayerManager::getSingleton().getInpasMapObj();
        if (twn::TownFurnitureManager::getSingleton()->getCofferType(uid) == 0x44 && twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 4) {
            mess = splitMessage_->getCofferGold();
            splitFlag_ = false;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageZeroInBox(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x84) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getCofferNothing() && data_02101c88.isCurrentPart(dq5::TOWN_PART) == true) {
        int uid = twn::TownPlayerManager::getSingleton().getInpasMapObj();
        if (twn::TownFurnitureManager::getSingleton()->getCofferType(uid) == 0x44
            && (twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 1 || twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 2)) {
            mess = splitMessage_->getCofferNothing();
            splitFlag_ = false;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageItemInPot(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x84) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getTuboItem() && data_02101c88.isCurrentPart(dq5::TOWN_PART) == true) {
        int uid = twn::TownPlayerManager::getSingleton().getInpasMapObj();
        if (twn::TownFurnitureManager::getSingleton()->getCofferType(uid) == 0x33 && twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 3) {
            mess = splitMessage_->getTuboItem();
            splitFlag_ = false;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageMonsterInPot(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x84) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getTuboMonster() && data_02101c88.isCurrentPart(dq5::TOWN_PART) == true) {
        int uid = twn::TownPlayerManager::getSingleton().getInpasMapObj();
        if (twn::TownFurnitureManager::getSingleton()->getCofferType(uid) == 0x33 && twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 5) {
            mess = splitMessage_->getTuboMonster();
            splitFlag_ = false;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageGoldInPot(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x84) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getTuboGold() && data_02101c88.isCurrentPart(dq5::TOWN_PART) == true) {
        int uid = twn::TownPlayerManager::getSingleton().getInpasMapObj();
        if (twn::TownFurnitureManager::getSingleton()->getCofferType(uid) == 0x33 && twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 4) {
            mess = splitMessage_->getTuboGold();
            splitFlag_ = false;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageZeroInPot(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x84) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getTuboNothing() && data_02101c88.isCurrentPart(dq5::TOWN_PART) == true) {
        int uid = twn::TownPlayerManager::getSingleton().getInpasMapObj();
        if (twn::TownFurnitureManager::getSingleton()->getCofferType(uid) == 0x33
            && (twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 1 || twn::TownFurnitureManager::getSingleton()->checkCoffer(uid) == 2)) {
            mess = splitMessage_->getTuboNothing();
            splitFlag_ = false;
        }
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageNoTarget(int splitIndex)
{
    int mess = 0;
    if (actionIndex_ != 0x84) {
        return mess;
    }
    getSplitRecord(splitIndex);
    if (splitMessage_->getNoTarget()) {
        mess = splitMessage_->getNoTarget();
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageRandom(int splitIndex)
{
    int mess = 0, count = 0;
    if (actionIndex_ != 0x154 && actionIndex_ != 0x15d && actionIndex_ != 0x17d) {
        return mess;
    }
    getSplitRecord(splitIndex);
    unsigned long randomMes[11] = { 0 };
    for (int i = 0; i < 11; i++) {
        randomMes[i] = 0;
    }
    if (splitMessage_->getRandom1()) {
        randomMes[count] = splitMessage_->getRandom1();
        count++;
    }
    if (splitMessage_->getRandom2()) {
        randomMes[count] = splitMessage_->getRandom2();
        count++;
    }
    if (splitMessage_->getRandom3()) {
        randomMes[count] = splitMessage_->getRandom3();
        count++;
    }
    if (splitMessage_->getRandom4()) {
        randomMes[count] = splitMessage_->getRandom4();
        count++;
    }
    if (splitMessage_->getRandom5()) {
        randomMes[count] = splitMessage_->getRandom5();
        count++;
    }
    if (splitMessage_->getRandom6()) {
        randomMes[count] = splitMessage_->getRandom6();
        count++;
    }
    if (splitMessage_->getRandom7()) {
        randomMes[count] = splitMessage_->getRandom7();
        count++;
    }
    if (splitMessage_->getRandom8()) {
        randomMes[count] = splitMessage_->getRandom8();
        count++;
    }
    if (splitMessage_->getRandom9()) {
        randomMes[count] = splitMessage_->getRandom9();
        count++;
    }
    if (splitMessage_->getRandom10()) {
        randomMes[count] = splitMessage_->getRandom10();
        count++;
    }
    if (splitMessage_->getRandom11()) {
        randomMes[count] = splitMessage_->getRandom11();
        count++;
    }
    if (count) {
        mess = randomMes[UnkDssRand::rand(count)];
        splitFlag_ = false;
    }
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageZero(int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    return mess;
}

THUMB int status::ActionMessageSplit::getMessageSpecial(int splitIndex)
{
    int mess = 0;
    getSplitRecord(splitIndex);
    if (splitMessage_->getSpecial()) {
        mess = splitMessage_->getSpecial();
        splitFlag_ = true;
    }
    return mess;
}
