#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/status/HaveBattleStatus.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"
#include "main/text/TextHook.hpp"

using menu::MenuStatusInfo;

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }
inline int status::HaveStatusInfo::getPlayerIndex() const { return haveStatus_.getPlayerIndex(); }
inline int status::HaveStatus::getCommand() const { return command_; }
inline int status::HaveStatusInfo::getCommandType() const { return haveStatus_.getCommand(); }
inline int status::HaveStatus::getLevel() const { return level_; }
inline bool status::HaveStatus::isFriendMonster() const { return playerType_ == TYPE_FRIENDMONSTER; }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}
inline int status::HaveBattleStatus::getSelectGroup() { return selectedGroup_; }
inline int status::HaveBattleStatus::getSelectCommandIndex() { return selectIndex_; }
inline int status::MonsterStatus::getMonsterGroup() { return characterGroup_; }
inline int status::MonsterStatus::getMonsterIndex() { return characterIndex_; }
inline int status::MonsterStatus::getMosyasIndex() { return mosyasIndex_; }
inline int BattleMenuPlayerControl::getSpecialFlag(int memberNum) { return historyData_[memberNum].special; }

BattleMenuPlayerControl BattleMenuPlayerControl::m_singleton;

THUMB BattleMenuPlayerControl* BattleMenuPlayerControl::getSingleton()
{
    return &m_singleton;
}

THUMB int BattleMenuPlayerControl::getPlayerItemId()
{
    return MenuStatusInfo::getPlayerItemID(activeChara_, activeItem_);
}

THUMB void BattleMenuPlayerControl::clear()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    activeChara_ = -1;
    activeItem_ = -1;
    activeMagic_ = -1;
    targetChara_ = -1;
    for (int i = 0; i < 4; i++) {
        historyData_[i].secondHistory = -1;
        historyData_[i].firstHistory = -1;
        statusData_[i].hp = 0;
        statusData_[i].mp = 0;
        statusData_[i].Lv = 1;
        statusData_[i].color = 0;
        statusData_[i].condition = 0;
        historyData_[i].item = 0;
        statusData_[i].conditionFlag = 0;
        historyData_[i].special = 0;
        historyData_[i].index = 0;
    }
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < partyCount; i++) {
        setTacticsHistory(i);
        flashStatus(i);
        checkSpecialFlag(i);
        historyData_[i].index = MenuStatusInfo::getPlayerIndex(i);
    }
}

THUMB void BattleMenuPlayerControl::allClear()
{
    clear();
}

THUMB bool BattleMenuPlayerControl::makePlayerHistory()
{
    int playerNum = activeChara_;
    if (playerNum < 0 || playerNum >= MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT)) {
        return false;
    }
    int oldFirstHistory = historyData_[playerNum].firstHistory;
    int oldSecondHistory = historyData_[playerNum].secondHistory;
    status::HaveBattleStatus& statusBattle = MenuStatusInfo::getHaveBattleStatus(playerNum);
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(playerNum);
    historyData_[playerNum].index = statusInfo.getPlayerIndex();
    if (statusInfo.getCommandType() == COMMAND_DEBUG) {
        historyData_[playerNum].secondHistory = -1;
        historyData_[playerNum].firstHistory = -1;
        return false;
    }
    switch (statusBattle.getSelectCommand()) {
    case status::HaveBattleStatus::NoSelect:
        MenuStatusInfo::getPlayerIndex(playerNum);
        setTacticsHistory(playerNum);
        break;
    case status::HaveBattleStatus::Attack:
        setAttackHistory();
        break;
    case status::HaveBattleStatus::Defence:
        setDefenceHistory();
        break;
    case status::HaveBattleStatus::UseAction:
        setMagicHistory();
        break;
    case status::HaveBattleStatus::UseItem:
        setItemHistory();
        break;
    }
    if (oldFirstHistory == historyData_[playerNum].firstHistory && oldSecondHistory == historyData_[playerNum].secondHistory) {
        return false;
    }
    return true;
}

THUMB bool BattleMenuPlayerControl::resetPlayerHistory(int playerNum)
{
    status::HaveBattleStatus& statusBattle = MenuStatusInfo::getHaveBattleStatus(playerNum);
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(playerNum);
    int oldFirstHistory = historyData_[playerNum].firstHistory;
    int oldSecondHistory = historyData_[playerNum].secondHistory;
    bool redrawFlag = false;
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (historyData_[playerNum].index != MenuStatusInfo::getPlayerIndex(playerNum) && changeHistory()) {
        redrawFlag = true;
    }
    if (!MenuStatusInfo::isPlayerClever(playerNum)) {
        return false;
    }
    MenuStatusInfo::getPlayerIndex(playerNum);
    if (!statusInfo.getHaveStatus().isPlayer() || statusInfo.getCommandType() == COMMAND_DEBUG) {
        historyData_[playerNum].secondHistory = -1;
        historyData_[playerNum].firstHistory = -1;
        if (oldFirstHistory == historyData_[playerNum].firstHistory && oldSecondHistory == historyData_[playerNum].secondHistory) {
            return redrawFlag;
        }
        return true;
    }
    if (statusInfo.getCommandType() != COMMAND_MEIREISASERO) {
        setTacticsHistory(playerNum);
        if (oldFirstHistory == historyData_[playerNum].firstHistory && oldSecondHistory == historyData_[playerNum].secondHistory) {
            return redrawFlag;
        }
        return true;
    }
    switch (statusBattle.getSelectCommand()) {
    case status::HaveBattleStatus::NoSelect:
        setTacticsHistory(playerNum);
        break;
    case status::HaveBattleStatus::Attack: {
        int monsterGroup = statusBattle.getSelectGroup();
        int monsterNum = 0;
        for (; monsterNum < status::g_Monster.getCount(); monsterNum++) {
            if (monsterGroup == status::g_Monster.getMonsterGroup(monsterNum)) {
                break;
            }
        }
        int monsterIndex = status::g_Monster.getMonsterIndex(monsterNum);
        unsigned char* tmp = mosyasA;
        if (monsterGroup != 0) {
            tmp = mosyasB;
        }
        if (monsterNum < status::g_Monster.getCount()) {
            historyData_[playerNum].secondHistory = monsterIndex + 0x60000000;
            historyData_[playerNum].firstHistory = 0xe0000005;
            status::MonsterStatus& enemy = status::g_Monster.getMonsterStatus(monsterNum);
            if (enemy.getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
                TextAPI::getPlayerNamePlateTextImitation((char*)tmp, enemy.getMosyasIndex(), 1);
                historyData_[playerNum].secondHistory = (int)tmp;
            }
        }
        break;
    }
    case status::HaveBattleStatus::Defence:
        historyData_[playerNum].secondHistory = -1;
        historyData_[playerNum].firstHistory = 0xe0000008;
        break;
    case status::HaveBattleStatus::UseAction: {
        int magic = statusBattle.getSelectCommandIndex();
        historyData_[playerNum].secondHistory = magic + 0x70000000;
        historyData_[playerNum].firstHistory = 0xe0000006;
        if (getSpecialFlag(playerNum)) {
            historyData_[playerNum].firstHistory = 0xe000000d;
        }
        if (magic == 0) {
            setTacticsHistory(playerNum);
        }
        break;
    }
    case status::HaveBattleStatus::UseItem:
        if (historyData_[playerNum].item != 0) {
            historyData_[playerNum].secondHistory = historyData_[playerNum].item + 0x40000000;
            historyData_[playerNum].firstHistory = 0xe0000007;
        } else {
            setTacticsHistory(playerNum);
        }
        break;
    }
    if (oldFirstHistory == historyData_[playerNum].firstHistory && oldSecondHistory == historyData_[playerNum].secondHistory) {
        return redrawFlag;
    }
    return true;
}

THUMB void BattleMenuPlayerControl::setTacticsHistory(int playerNum)
{
    static const int commandName[6] = {
        0x90000001, 0x90000002, 0x90000005,
        0x90000003, 0x90000004, 0x90000006,
    };
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(playerNum);
    int playerID = statusInfo.getHaveStatus().getPlayerIndex();
    historyData_[playerNum].secondHistory = -1;
    historyData_[playerNum].firstHistory = -1;
    historyData_[playerNum].firstHistory = commandName[statusInfo.getCommandType()];
    if (playerID == 1 || !statusInfo.getHaveStatus().isPlayer()) {
        historyData_[playerNum].firstHistory = -1;
    }
}

THUMB void BattleMenuPlayerControl::setAttackHistory()
{
    status::HaveBattleStatus& statusBattle = MenuStatusInfo::getHaveBattleStatus(activeChara_);
    MenuStatusInfo::getHaveStatusInfo(activeChara_);
    int monsterGroup = statusBattle.getSelectGroup();
    if (monsterGroup < 0) {
        status::MonsterStatus& enemy = status::g_Monster.getMonsterInGroup(targetChara_, 0);
        int monsterIndex = enemy.getMonsterIndex();
        historyData_[activeChara_].secondHistory = monsterIndex + 0x60000000;
        historyData_[activeChara_].firstHistory = 0xe0000005;
        if (enemy.getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
            TextAPI::getPlayerNamePlateTextImitation((char*)mosyas, enemy.getMosyasIndex(), 1);
            historyData_[activeChara_].secondHistory = (int)mosyas;
        }
        return;
    }
    int monsterNum = 0;
    for (; monsterNum < status::g_Monster.getCount(); monsterNum++) {
        if (monsterGroup == status::g_Monster.getMonsterGroup(monsterNum)) {
            break;
        }
    }
    int monsterIndex = status::g_Monster.getMonsterIndex(monsterNum);
    unsigned char* tmp = mosyasA;
    if (monsterGroup != 0) {
        tmp = mosyasB;
    }
    if (monsterNum < status::g_Monster.getCount()) {
        historyData_[activeChara_].secondHistory = monsterIndex + 0x60000000;
        historyData_[activeChara_].firstHistory = 0xe0000005;
        status::MonsterStatus& enemy = status::g_Monster.getMonsterStatus(monsterNum);
        if (enemy.getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU)) {
            TextAPI::getPlayerNamePlateTextImitation((char*)tmp, enemy.getMosyasIndex(), 1);
            historyData_[activeChara_].secondHistory = (int)tmp;
        }
    }
}

THUMB void BattleMenuPlayerControl::setDefenceHistory()
{
    MenuStatusInfo::getHaveBattleStatus(activeChara_);
    MenuStatusInfo::getHaveStatusInfo(activeChara_);
    historyData_[activeChara_].secondHistory = -1;
    historyData_[activeChara_].firstHistory = 0xe0000008;
}

THUMB void BattleMenuPlayerControl::setItemHistory()
{
    status::HaveBattleStatus& statusBattle = MenuStatusInfo::getHaveBattleStatus(activeChara_);
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(activeChara_);
    int item = statusBattle.getSelectCommandIndex();
    if (item < 0) {
        historyData_[activeChara_].secondHistory = statusInfo.haveItem_.getItem(activeItem_) + 0x40000000;
        historyData_[activeChara_].firstHistory = 0xe0000007;
    } else {
        historyData_[activeChara_].secondHistory = statusInfo.haveItem_.getItem(item) + 0x40000000;
        historyData_[activeChara_].firstHistory = 0xe0000007;
    }
    historyData_[activeChara_].item = historyData_[activeChara_].secondHistory;
}

THUMB void BattleMenuPlayerControl::setMagicHistory()
{
    status::HaveBattleStatus& statusBattle = MenuStatusInfo::getHaveBattleStatus(activeChara_);
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(activeChara_);
    int magic = statusBattle.getSelectCommandIndex();
    if (magic < 0) {
        int magicNum = activeMagic_;
        historyData_[activeChara_].secondHistory = statusInfo.haveAction_.getAction(magicNum) + 0x70000000;
        historyData_[activeChara_].firstHistory = 0xe0000006;
        if (getSpecialFlag(activeChara_)) {
            historyData_[activeChara_].firstHistory = 0xe000000d;
        }
        if (statusInfo.haveAction_.getAction(magicNum) == 0) {
            setTacticsHistory(activeChara_);
        }
        return;
    }
    historyData_[activeChara_].secondHistory = magic + 0x70000000;
    historyData_[activeChara_].firstHistory = 0xe0000006;
    if (getSpecialFlag(activeChara_)) {
        historyData_[activeChara_].firstHistory = 0xe000000d;
    }
}

THUMB bool BattleMenuPlayerControl::flashStatus(int memberNum)
{
    bool reDraw = false;
    MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(memberNum);
    if (flashHP(memberNum)) {
        reDraw = true;
    }
    if (flashMP(memberNum)) {
        reDraw = true;
    }
    if (flashCondition(memberNum)) {
        reDraw = true;
    }
    if (flashHPColor(memberNum)) {
        reDraw = true;
    }
    statusData_[memberNum].Lv = statusInfo.getHaveStatus().getLevel();
    return reDraw;
}

THUMB bool BattleMenuPlayerControl::flashHP(int memberNum)
{
    MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(memberNum);
    short oldHP = statusData_[memberNum].hp;
    statusData_[memberNum].hp = statusInfo.getHp();
    if (oldHP != statusData_[memberNum].hp) {
        return true;
    }
    return false;
}

THUMB bool BattleMenuPlayerControl::flashMP(int memberNum)
{
    MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(memberNum);
    short oldMP = statusData_[memberNum].mp;
    statusData_[memberNum].mp = statusInfo.getMp();
    if (oldMP != statusData_[memberNum].mp) {
        return true;
    }
    return false;
}

THUMB bool BattleMenuPlayerControl::flashHPColor(int memberNum)
{
    MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(memberNum);
    short oldColor = statusData_[memberNum].color;
    statusData_[memberNum].color = BattleDrawParts_getStatusColor(statusInfo);
    if (oldColor != statusData_[memberNum].color) {
        return true;
    }
    return false;
}

THUMB bool BattleMenuPlayerControl::flashCondition(int memberNum)
{
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(memberNum);
    int oldCondition_ = statusData_[memberNum].condition;
    const status::HaveStatusInfo::MenuStatusChange statusList[8] = {
        (status::HaveStatusInfo::MenuStatusChange)5,
        status::HaveStatusInfo::Curse,
        status::HaveStatusInfo::Mahoton,
        status::HaveStatusInfo::Manusa,
        status::HaveStatusInfo::Venom,
        status::HaveStatusInfo::Confusion,
        status::HaveStatusInfo::Sleep,
        status::HaveStatusInfo::Spazz,
    };
    const int conditionName[9] = {
        0xe0000027, 0xe000002b, 0xe0000029, 0xe0000028, 0xe000002a,
        0xe0000026, 0xe0000025, 0xe0000024, 0,
    };
    const int conditionNameFemale[9] = {
        0xe0000031, 0xe0000035, 0xe0000033, 0xe0000032, 0xe0000034,
        0xe0000030, 0xe000002f, 0xe000002e, 0,
    };
    const int* condition = conditionName;
    if (statusInfo.getHaveStatus().getSex() == 1) {
        condition = conditionNameFemale;
    }
    if (statusInfo.getHaveStatus().getSex() == 2 && UserExtractWordHook::getOriginalWordSEX(statusInfo.getHaveStatus().playerIndex_) == 2) {
        condition = conditionNameFemale;
    }
    statusData_[memberNum].condition = 0xe0000016;
    statusData_[memberNum].conditionFlag = 0;
    for (int i = 0; conditionName[i] != 0; i++) {
        if (isFlashCondition(memberNum, statusList[i])) {
            statusData_[memberNum].conditionFlag = 1;
            statusData_[memberNum].condition = condition[i];
        }
    }
    if (statusData_[memberNum].hp == 0) {
        statusData_[memberNum].conditionFlag = 1;
        statusData_[memberNum].condition = 0xe0000023;
        if (statusInfo.getHaveStatus().getSex() == 1) {
            statusData_[memberNum].condition = 0xe000002d;
        }
        if (statusInfo.getHaveStatus().getSex() == 2 && UserExtractWordHook::getOriginalWordSEX(statusInfo.getHaveStatus().playerIndex_) == 2) {
            statusData_[memberNum].condition = 0xe000002d;
        }
        if (status::g_Story.chapter_ == 1) {
            statusData_[memberNum].condition = 0xe000002c;
            if (statusInfo.getHaveStatus().getSex() == 1) {
                statusData_[memberNum].condition = 0xe0000036;
            }
            if (statusInfo.getHaveStatus().getSex() == 2 && UserExtractWordHook::getOriginalWordSEX(statusInfo.getHaveStatus().playerIndex_) == 2) {
                statusData_[memberNum].condition = 0xe000002d;
            }
        }
    }
    if (oldCondition_ != statusData_[memberNum].condition) {
        return true;
    }
    return false;
}

THUMB int BattleMenuPlayerControl::isFlashCondition(int memberNum, status::HaveStatusInfo::MenuStatusChange menuStatus)
{
    status::HaveStatusInfo& statusInfo = MenuStatusInfo::getHaveStatusInfo(memberNum);
    switch (menuStatus) {
    case status::HaveStatusInfo::Curse: {
        bool result = statusInfo.isSpell();
        if (!result) {
            int itemCount = statusInfo.haveItem_.getMaxCount();
            for (int i = 0; i < itemCount; i++) {
                if (statusInfo.haveItem_.isEquipment(i) == true && status::UseItem::isCurse(statusInfo.haveItem_.getItem(i))) {
                    result = true;
                }
            }
        }
        return result;
    }
    case status::HaveStatusInfo::Manusa:
        return statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MANUSA);
    case status::HaveStatusInfo::Mahoton: {
        int result = statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON);
        if (result) {
            return statusInfo.getHaveStatus().getMpMax() != 0;
        }
        return result;
    }
    case status::HaveStatusInfo::Sleep:
        return statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI);
    case status::HaveStatusInfo::Confusion: {
        bool result = statusInfo.getStatusChange().isRelease(dq5::level::ActionParam::ACTIONTYPE_KONRAN);
        if (result) {
            return result;
        }
        return statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN);
    }
    case status::HaveStatusInfo::Spazz:
        return statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI);
    case (status::HaveStatusInfo::MenuStatusChange)5:
        return statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU);
    case status::HaveStatusInfo::Venom:
        return statusInfo.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU);
    }
    return false;
}

THUMB int BattleMenuPlayerControl::getTargetGroup()
{
    int group = historyData_[activeChara_].monster;
    int monsterCount = status::g_Monster.getCount();
    for (int i = 0; i < monsterCount; i++) {
        if (group == status::g_Monster.getMonsterStatus(i).getMonsterGroup() && status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
            return group;
        }
    }
    return 0;
}

THUMB void BattleMenuPlayerControl::setTargetGroup(int monsterNum)
{
    historyData_[activeChara_].monster = monsterNum;
}

THUMB void BattleMenuPlayerControl::resetTargetGroup()
{
    for (int i = 0; i < 4; i++) {
        historyData_[i].monster = 0;
    }
}

THUMB void BattleMenuPlayerControl::setMagicPosition(int pos)
{
    MenuStatusInfo::getHaveStatusInfo(activeChara_).haveStatus_.actionCursorIndex_ = pos;
}

THUMB int BattleMenuPlayerControl::getMagicPosition()
{
    return MenuStatusInfo::getHaveStatusInfo(activeChara_).haveStatus_.actionCursorIndex_;
}

THUMB void BattleMenuPlayerControl::checkSpecialFlag(int playerNum)
{
    historyData_[playerNum].special = MenuStatusInfo::getHaveStatusInfo(playerNum).getHaveStatus().isFriendMonster();
}

THUMB bool BattleMenuPlayerControl::changeHistory()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    bool redrawFlag = false;
    int memberCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int from = 0; from < memberCount; from++) {
        int fromID = MenuStatusInfo::getPlayerIndex(from);
        if (fromID != historyData_[from].index) {
            for (int to = 0; to < 4; to++) {
                if (fromID == historyData_[to].index) {
                    BATTLEMENU_HISTORY regHistory = historyData_[from];
                    historyData_[from] = historyData_[to];
                    historyData_[to] = regHistory;
                    redrawFlag = true;
                }
            }
        }
    }
    return redrawFlag;
}
