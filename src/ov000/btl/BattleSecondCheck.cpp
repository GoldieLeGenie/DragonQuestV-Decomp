#include "ov000/btl/BattleSecondCheck.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/btl/Encount.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/leveldata/ActionParam.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"

inline status::CharacterStatus* btl::BattleSelectTargetParam::getActorCharacterStatus() { return actorCharacterStatus_; }
inline int btl::BattleSelectTargetParam::getActionIndex() { return actionIndex_; }
inline int btl::BattleSelectTargetParam::getSourceCount() { return sourceCount_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline status::HaveBattleStatus& status::CharacterStatus::getHaveBattleStatus() { return haveBattleStatus_; }
inline CharacterType status::CharacterStatus::getCharacterType() { return characterType_; }
inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::ActionDefence& status::HaveStatusInfo::getActionDefence() { return actionDefence_; }
inline unsigned char status::HaveBattleStatus::getBrains() { return brains_; }
inline int status::HaveStatus::getPlayerKindIndex() const { return playerKindIndex_; }
inline int status::HaveStatusInfo::getPlayerKindIndex() const { return haveStatus_.getPlayerKindIndex(); }
inline bool status::HaveStatus::isFriendMonster() const { return playerType_ == TYPE_FRIENDMONSTER; }
inline bool status::HaveStatus::isBattleNpc() const { return playerType_ == TYPE_BATTLENPC; }
inline int status::HaveStatus::getLevel() const { return level_; }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
inline int status::MonsterStatus::getMonsterGroup() { return characterGroup_; }
inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline unsigned char dq5::level::ActionParam::getFool() { return fool; }
inline unsigned char dq5::level::ActionParam::getHuman() { return human; }
inline unsigned char dq5::level::ActionParam::getGod() { return god; }
inline int btl::EncountData::getTileLevel() { return tileLevel_; }
inline int btl::Encount::getLevel() { return encountData_.getTileLevel(); }

inline bool btl::BattleSecondCheck::checkNotZeroPercent(int enableCount)
{
    if (enableCount > 0) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::secondCheckFirst(BattleSelectTargetParam* targetParam)
{
    unsigned char checkParam = getSecondCheckParam(targetParam);

    switch (checkParam) {
    case 0x27:
        return personalCheckNakamayobi(targetParam);
    case 0x24:
        return checkFizzleZone(targetParam);
    case 0x33:
        return checkBashaModoshi(targetParam);
    case 0x34:
        return checkBashaShime(targetParam);
    case 0x2b:
        return !checkPartHalf(targetParam);
    case 0xd:
        return personalCheckMyMahokanta(targetParam);
    case 0xe:
        return personalCheckMahokantaForGod(targetParam);
    case 0x1f:
        return personalCheckChargeAttack(targetParam);
    case 3:
        return checkPartHalf(targetParam);
    case 2:
        return checkPartThree(targetParam);
    case 0x30:
        return checkPartFourth(targetParam);
    case 0x2a:
        return checkAnkoku(targetParam);
    case 0x26:
        return checkEscape(targetParam);
    case 0x2f:
        return checkMySukara(targetParam);
    case 0x19:
        return checkMyHoimi(targetParam);
    case 0x29:
        return personalCheckGattai(targetParam);
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::secondCheckLast(unsigned char checkParam, status::CharacterStatus* targetStatus, status::CharacterStatus* actorStatus)
{
    CharacterType type = actorStatus->getCharacterType();
    int ret;

    switch (checkParam) {
    case 1:
    case 5:
    case 0xa:
    case 0xc:
    case 0x10:
    case 0x12:
    case 0x15:
    case 0x1a:
    case 0x2d:
    case 0x32:
    case 0x37:
    case 0x38:
        ret = personalCheckMahokanta(targetStatus);
        break;
    default:
        ret = true;
        break;
    }
    if (!ret) {
        return false;
    }

    switch (checkParam) {
    case 4:
    case 5:
    case 0x38:
        return checkRarihoma(targetStatus);
    case 6:
        return checkManusa(targetStatus);
    case 7:
        return checkMahoton(targetStatus);
    case 8:
        return checkMahotonForGod(targetStatus);
    case 0x31:
    case 0x32:
        return checkMahokite(targetStatus);
    case 0x20:
        return checkPoison(targetStatus);
    case 0x21:
        return checkDeepPoison(targetStatus);
    case 0x22:
        return checkParalyse(targetStatus);
    case 0x1e:
        return !checkParalyse(targetStatus);
    case 0x14:
    case 0x15:
        return checkBaikiruto(targetStatus);
    case 0x18:
    case 0x1b:
        return checkHoimi(targetStatus);
    case 0x1a:
        return checkThereHoimi(targetStatus);
    case 0x1c:
    case 0x1d:
        return checkZaoriku(targetStatus, type);
    case 9:
    case 0xa:
        return checkMedapani(targetStatus);
    case 0xb:
    case 0xc:
        return checkMahotora(targetStatus);
    case 0xf:
        return checkRukani(targetStatus);
    case 0x10:
        return checkRukaniForGod(targetStatus);
    case 0x37:
        return checkRukananForGod(targetStatus);
    case 0x11:
    case 0x12:
    case 0x2d:
    case 0x2e:
        return checkSukara(targetStatus);
    case 0x13:
        return checkFubaha(targetStatus);
    case 0x28:
        return checkHadou(targetStatus);
    case 0x25:
        return checkBukimi(targetStatus);
    case 0x33:
        return checkBashaModoshi(targetStatus);
    case 0x16:
        return checkMosyasu(targetStatus);
    case 0x23:
        return checkOtakebi(targetStatus);
    case 0x36:
        return checkOthers(targetStatus, actorStatus);
    default:
        return personalCheckRandom();
    }
}

THUMB bool btl::BattleSecondCheck::secondCheckPercent(BattleSelectTargetParam* targetParam, int member, int enable, int mahokanta)
{
    bool result = false;
    unsigned char checkParam = getSecondCheckParam(targetParam);

    if (member == 0) {
        return result;
    }

    switch (checkParam) {
    case 1:
        result = checkMahokantakeiPercent(member, mahokanta);
        break;
    case 0x1b:
        result = checkMahokantakeiPercent(member, mahokanta);
        if (result) {
            result = checkBehomaraPercent(member, enable);
        }
        break;
    case 0x1d:
        result = checkMahokantakeiPercent(member, mahokanta);
        if (result) {
            result = checkMegazaruPercent(member, enable);
        }
        break;
    case 5:
    case 0xa:
    case 0x12:
    case 0x1e:
    case 0x37:
        result = checkMahokantakeiPercent(member, mahokanta);
        if (result) {
            result = checkNotZeroPercent(enable);
        }
        break;
    default:
        result = checkNotZeroPercent(enable);
        break;
    }
    return result;
}

THUMB int btl::BattleSecondCheck::secondCheckTarget(BattleSelectTargetParam* targetParam, int max, int actor)
{
    unsigned char checkParam = getSecondCheckParam(targetParam);
    int target;

    switch (checkParam) {
    case 0x1a:
    case 0x2c:
    case 0x2d:
    case 0x2e:
        if (max == 1) {
            return 0;
        }
        target = UnkDssRand::rand(max - 1);
        if (target == actor) {
            target++;
        }
        break;
    default:
        target = UnkDssRand::rand(max);
        break;
    }
    return target;
}

THUMB bool btl::BattleSecondCheck::personalCheckFirst(BattleSelectTargetParam* targetParam)
{
    return secondCheckFirst(targetParam);
}

THUMB bool btl::BattleSecondCheck::personalCheckLast(BattleSelectTargetParam* targetParam, int group, int num)
{
    unsigned char checkParam = getSecondCheckParam(targetParam);
    status::CharacterStatus* targetStatus = targetParam->getSourceCharacterStatusForGroupDead(group, num);
    status::CharacterStatus* actorStatus = targetParam->getActorCharacterStatus();
    return secondCheckLast(checkParam, targetStatus, actorStatus);
}

THUMB bool btl::BattleSecondCheck::myselfCheck(BattleSelectTargetParam* targetParam)
{
    return secondCheckFirst(targetParam);
}

THUMB unsigned char btl::BattleSecondCheck::getSecondCheckParam(BattleSelectTargetParam* targetParam)
{
    int actionIndex = targetParam->getActionIndex();
    dq5::level::ActionParam* action = dq5::level::ActionParam::getRecord(actionIndex);
    unsigned char checkParam = action->getFool();

    if (targetParam->getActorCharacterStatus() == NULL) {
        return checkParam;
    }

    switch (targetParam->getActorCharacterStatus()->getHaveBattleStatus().getBrains()) {
    case 2:
        checkParam = action->getGod();
        break;
    case 1:
        checkParam = action->getHuman();
        break;
    }
    return checkParam;
}

THUMB bool btl::BattleSecondCheck::personalCheckRandom()
{
    return true;
}

THUMB int btl::BattleSecondCheck::personalCheckMahokanta(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkRarihoma(status::CharacterStatus* characterStatus)
{
    if (characterStatus == NULL) {
        return true;
    }
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkFubaha(status::CharacterStatus* characterStatus)
{
    status::HaveStatusInfo& statusInfo = characterStatus->getHaveStatusInfo();
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (!statusInfo.isFubahaFlag()) {
        return false;
    }
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_FUBAHA)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkManusa(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MANUSA)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkMahoton(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkMahokite(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKITE)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkMedapani(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkPoison(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU)) {
        return false;
    }
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkDeepPoison(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkParalyse(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkMahotora(status::CharacterStatus* characterStatus)
{
    status::HaveStatus& status = characterStatus->getHaveStatusInfo().getHaveStatus();
    if (status.getMp() != 0) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkRukani(status::CharacterStatus* characterStatus)
{
    status::HaveStatusInfo& statusInfo = characterStatus->getHaveStatusInfo();
    if (statusInfo.getDefence(0) != 0) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkSukara(status::CharacterStatus* characterStatus)
{
    status::HaveStatusInfo& statusInfo = characterStatus->getHaveStatusInfo();
    if (statusInfo.getDefence(0) < statusInfo.getHaveStatus().getDefence() * 2) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkMySukara(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::HaveStatusInfo& statusInfo = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo();
    if (statusInfo.getDefence(0) < statusInfo.getHaveStatus().getDefence() * 2) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkBaikiruto(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkHoimi(status::CharacterStatus* characterStatus)
{
    status::HaveStatus& status = characterStatus->getHaveStatusInfo().getHaveStatus();
    if (status.getHp() <= status.getHpMax() >> 1) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkMyHoimi(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::HaveStatusInfo& myStatusInfo = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo();
    if (myStatusInfo.getHaveStatus().getHp() < myStatusInfo.getHaveStatus().getHpMax() >> 1) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkThereHoimi(status::CharacterStatus* characterStatus)
{
    status::HaveStatusInfo& statusInfo = characterStatus->getHaveStatusInfo();
    if (statusInfo.getHaveStatus().getHp() <= statusInfo.getHaveStatus().getHpMax() >> 1) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkZaoriku(status::CharacterStatus* characterStatus, CharacterType type)
{
    status::HaveStatusInfo& statusInfo = characterStatus->getHaveStatusInfo();
    if (!statusInfo.isDeath()) {
        return false;
    }
    if (statusInfo.isEscapeFlag()) {
        return false;
    }
    if (statusInfo.isDisappearFlag()) {
        return false;
    }
    if (type == MONSTER) {
        int monsterIndex = ((status::MonsterStatus*)characterStatus)->getMonsterIndex();
        if (!BattleMonsterDraw2::getSingleton().isCallFriend(monsterIndex)) {
            return false;
        }
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkOthers(status::CharacterStatus* targetStatus, status::CharacterStatus* actorStatus)
{
    if (targetStatus != actorStatus) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkOtakebi(status::CharacterStatus* characterStatus)
{
    status::StatusChange& condition = characterStatus->getHaveStatusInfo().getStatusChange();
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkHadou(status::CharacterStatus* characterStatus)
{
    status::StatusChange& condition = characterStatus->getHaveStatusInfo().getStatusChange();
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA)) {
        return true;
    }
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA)) {
        if (condition.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA) == 0x29
            || condition.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA) == 0x2a
            || condition.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA) == 0x2b
            || condition.getActionIndex(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA) == 0x2c) {
            return true;
        }
    }
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_FUBAHA)) {
        return true;
    }
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO)) {
        return true;
    }
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
        return true;
    }
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)) {
        return true;
    }
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_DORAGORAM)) {
        return true;
    }
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_SPD_PLUS)) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkBashaModoshi(status::CharacterStatus* characterStatus)
{
    status::StatusChange& condition = characterStatus->getHaveStatusInfo().getStatusChange();
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
        return false;
    }
    switch (characterStatus->getHaveStatusInfo().getHaveStatus().isPlayer()) {
    case false:
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkBukimi(status::CharacterStatus* characterStatus)
{
    status::StatusChange& condition = characterStatus->getHaveStatusInfo().getStatusChange();
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_BUKIMINAHIKARI)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkMahotonForGod(status::CharacterStatus* characterStatus)
{
    status::StatusChange& statusChange = characterStatus->getHaveStatusInfo().getStatusChange();
    status::HaveStatus& status = characterStatus->getHaveStatusInfo().getHaveStatus();
    if (statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON)) {
        return false;
    }
    if (status.getMp() == 0) {
        return false;
    }
    if (personalCheckMahokanta(characterStatus)) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkRukaniForGod(status::CharacterStatus* characterStatus)
{
    status::HaveStatusInfo& statusInfo = characterStatus->getHaveStatusInfo();
    if (statusInfo.getDefence(0) == 0) {
        return false;
    }
    if (statusInfo.getActionDefence().getEffectValue(0x26) == 0) {
        return false;
    }
    if (personalCheckMahokanta(characterStatus)) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkRukananForGod(status::CharacterStatus* characterStatus)
{
    status::HaveStatusInfo& statusInfo = characterStatus->getHaveStatusInfo();
    if (statusInfo.getDefence(0) == 0) {
        return false;
    }
    if (statusInfo.getActionDefence().getEffectValue(0x27) != 0) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkMosyasu(status::CharacterStatus* characterStatus)
{
    status::HaveStatusInfo& statusInfo = characterStatus->getHaveStatusInfo();
    if (statusInfo.isMosyasTarget()) {
        return false;
    }
    if (!statusInfo.getHaveStatus().isFriendMonster() || statusInfo.getPlayerKindIndex() == 0x3a || statusInfo.getPlayerKindIndex() == 0x3b) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::personalCheckMyMahokanta(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::StatusChange& condition = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange();
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::personalCheckChargeAttack(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::StatusChange& condition = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange();
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_TAMEKEI)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkPartFourth(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::HaveStatus& status = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().getHaveStatus();
    int maxHp = status.getHpMax();
    int hp = status.getHp();
    if (maxHp >= hp * 4) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkPartThree(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::HaveStatus& status = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().getHaveStatus();
    int maxHp = status.getHpMax();
    int hp = status.getHp();
    if (maxHp * 10 / 3 >= hp * 10) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkPartHalf(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::HaveStatus& status = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().getHaveStatus();
    int maxHp = status.getHpMax();
    int hp = status.getHp();
    if (maxHp >= hp * 2) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkAnkoku(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::HaveStatus& status = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().getHaveStatus();
    if (status.getMp() == 0) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkFizzleZone(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::StatusChange& condition = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange();
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_FIZZLEZONE)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::checkEscape(BattleSelectTargetParam* battleSelectTargetParam)
{
    int tileLevel = Encount::getSingleton()->getLevel();
    int playerLevel = 0;

    status::g_Party.setPlayerMode();
    for (int i = 0; i < status::g_Party.getCarriageOutCount(); i++) {
        if (!status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath()
            && playerLevel < status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getLevel()) {
            playerLevel = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().getLevel();
        }
    }
    if (playerLevel - tileLevel >= 5) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkBashaModoshi(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::g_Party.setBattleMode();
    if (battleSelectTargetParam->getActorCharacterStatus()->getCharacterType() != MONSTER) {
        return false;
    }
    if (!status::g_Party.isCarriageEnableOnGame()) {
        return false;
    }

    int member = status::g_Party.getCarriageOutCount();
    int enableCount = 0;
    for (int i = 0; i < member; i++) {
        int mahi = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI);
        bool npc = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().getHaveStatus().isBattleNpc();
        bool death = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isDeath();
        if (!mahi && !npc && !death) {
            enableCount++;
        }
    }
    if (enableCount >= 2) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkBashaShime(BattleSelectTargetParam* battleSelectTargetParam)
{
    if (battleSelectTargetParam->getActorCharacterStatus()->getCharacterType() != MONSTER) {
        return false;
    }
    if (!status::g_Party.isCarriageEnableOnGame()) {
        return false;
    }
    status::StatusChange& status = status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getStatusChange();
    if (status.isEnable(dq5::level::ActionParam::ACTIONTYPE_CLOSEDOOR)) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::personalCheckNakamayobi(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::MonsterStatus* status = (status::MonsterStatus*)battleSelectTargetParam->getActorCharacterStatus();
    int friends = battleSelectTargetParam->getActionIndex();
    int monsterIndex = 0;
    int myIndex = status->getMonsterIndex();
    bool otherFriend = true;

    switch (friends) {
    case 0xb5:
    case 0xb6:
    case 0xb7:
    case 0xc2:
        monsterIndex = myIndex;
        otherFriend = false;
        break;
    case 0xb8:
        monsterIndex = 0x1e;
        break;
    case 0xb9:
        monsterIndex = 0x27;
        break;
    case 0xba:
        monsterIndex = 0x1b;
        break;
    case 0xbb:
        monsterIndex = 0x61;
        break;
    case 0xbc:
        monsterIndex = 0x67;
        break;
    case 0xbd:
        monsterIndex = 0x8c;
        break;
    case 0xbe:
        monsterIndex = 0xb2;
        break;
    case 0xbf:
        monsterIndex = 0xcf;
        break;
    case 0xc0:
        monsterIndex = 0xae;
        break;
    case 0xc1:
        monsterIndex = 0xb7;
        break;
    case 0xc3:
        monsterIndex = 0x24;
        otherFriend = false;
        break;
    }

    bool ret = BattleMonsterDraw2::getSingleton().isCallFriend(monsterIndex);
    if (ret && otherFriend) {
        int group[4] = {0};
        for (int i = 0; i < 4; i++) group[i] = 0;
        int target[4] = {0};
        for (int i = 0; i < 4; i++) target[i] = 0;

        for (int i = 0; i < status::g_Monster.getCount(); i++) {
            if (!status::g_Monster.getMonsterStatus(i).getHaveStatusInfo().isDeath()) {
                int groupIndex = status::g_Monster.getMonsterGroup(i);
                if (groupIndex != -1) {
                    group[groupIndex]++;
                    if (monsterIndex == status::g_Monster.getMonsterIndexInGroup(groupIndex)) {
                        target[groupIndex]++;
                    }
                }
            }
        }

        int count = 0;
        bool maxOnly = true;
        for (int i = 0; i < 4; i++) {
            if (group[i] != 0) {
                count++;
            }
            if (target[i] != 0 && target[i] < 8) {
                maxOnly = false;
            }
        }
        if (!maxOnly || count < 4) {
            return true;
        }
        return false;
    }
    if (ret) {
        if (status::g_Monster.getMonsterCountInGroup(status->getMonsterGroup()) < 8) {
            return true;
        }
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::personalCheckGattai(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::MonsterStatus* status = (status::MonsterStatus*)battleSelectTargetParam->getActorCharacterStatus();
    int monsterGroup = status->getMonsterGroup();
    if (status::g_Monster.getMonsterCountInGroup(monsterGroup) != 8) {
        return false;
    }

    int i = 0;
    int count = 0;
    for (; i < 8; ) {
        status::MonsterStatus& monster = status::g_Monster.getMonsterInGroup(monsterGroup, i);
        i++;
        if (monster.getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)
            || monster.getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)
            || monster.getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN)
            || monster.getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)) {
            break;
        }
        count++;
    }
    if (count >= 8) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::personalCheckMahokantaForGod(BattleSelectTargetParam* battleSelectTargetParam)
{
    status::StatusChange& condition = battleSelectTargetParam->getActorCharacterStatus()->getHaveStatusInfo().getStatusChange();
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA)) {
        return false;
    }
    if (condition.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKITE)) {
        return false;
    }

    int mpFlag = false;
    int mahotonFlag = false;
    if (battleSelectTargetParam->getActorCharacterStatus()->getCharacterType() == PLAYER) {
        for (int i = 0; i < status::g_Monster.getCount(); i++) {
            status::HaveStatusInfo& statusInfo = status::g_Monster.getMonsterStatus(i).getHaveStatusInfo();
            if (!statusInfo.isDeath()) {
                if (statusInfo.getMp() != 0) {
                    mpFlag = true;
                }
                if (!statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON)) {
                    mahotonFlag = true;
                }
            }
        }
    } else {
        status::g_Party.setBattleMode();
        for (int i = 0; i < status::g_Party.getCarriageOutCount(); i++) {
            status::HaveStatusInfo& statusInfo = status::g_Party.getPlayerStatus(i).getHaveStatusInfo();
            if (!statusInfo.isDeath()) {
                if (statusInfo.getMp() != 0) {
                    mpFlag = true;
                }
                if (!statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON)) {
                    mahotonFlag = true;
                }
            }
        }
    }
    if (mpFlag && mahotonFlag) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::everyCheckLast(BattleSelectTargetParam* targetParam, int index)
{
    unsigned char checkParam = getSecondCheckParam(targetParam);
    status::CharacterStatus* targetStatus = targetParam->getSourceCharacterStatus(index);
    return secondCheckLast(checkParam, targetStatus, targetParam->getActorCharacterStatus());
}

THUMB bool btl::BattleSecondCheck::everyCheckPercent(BattleSelectTargetParam* targetParam, int enable, int mahokanta)
{
    return secondCheckPercent(targetParam, targetParam->getSourceCount(), enable, mahokanta);
}

THUMB bool btl::BattleSecondCheck::checkBehomaraPercent(int member, int enable)
{
    if (member * 10 / 3 * 2 <= enable * 10) {
        return true;
    }
    return false;
}

THUMB bool btl::BattleSecondCheck::checkMegazaruPercent(int member, int enable)
{
    if (member > enable * 2 || enable == 0) {
        return false;
    }
    return true;
}

THUMB bool btl::BattleSecondCheck::multipleCheckFirst(BattleSelectTargetParam* targetParam)
{
    return secondCheckFirst(targetParam);
}

THUMB bool btl::BattleSecondCheck::multipleCheckPercent(BattleSelectTargetParam* targetParam, int member, int enable, int mahokanta)
{
    return secondCheckPercent(targetParam, member, enable, mahokanta);
}

THUMB bool btl::BattleSecondCheck::checkMahokantakeiPercent(int member, int mahokanta)
{
    if (member * 10 / 3 > (member - mahokanta) * 10) {
        return true;
    }
    return false;
}
