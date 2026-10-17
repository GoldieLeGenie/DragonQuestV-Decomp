#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/BattleMonsterNamePlate.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/status/MonsterParty.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/status/HaveBattleStatus.hpp"

using menu::MenuStatusInfo;

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline CharacterType status::HaveStatusInfo::getCharacterType() { return characterType_; }
inline CharacterType status::StatusChange::getCharacterTypeForTimeStop() { return characterTypeForTimeStop_; }
inline int status::HaveStatus::getCommand() const { return command_; }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}
inline void status::HaveBattleStatus::setSelectGroup(int group) { selectedGroup_ = group; }
inline void status::HaveBattleStatus::setSelectTarget(int playerIndex) { selectedTarget_ = playerIndex; }
inline int BattleMenuJudge::getPlayerIndex() { return BattleMenuPlayerControl::getSingleton()->activeChara_; }

BattleMenuJudge BattleMenuJudge::m_singleton;

THUMB void BattleMenuJudge::baseSetup()
{
    turnCount_ = 0;
    prevturnCount_ = 0;
    unk_08 = 0;
    minadeinFlag_ = 0;
}

THUMB void BattleMenuJudge::turnSetup()
{
    BattleMenuPlayerControl::getSingleton()->activeChara_ = -1;
    unk_08 = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < unk_08; i++) {
        MenuStatusInfo::getHaveBattleStatus(i).clearSelectCommand();
    }
}

THUMB BattleMenuJudge* BattleMenuJudge::getSingleton()
{
    return &m_singleton;
}

THUMB bool BattleMenuJudge::judgeBackChara()
{
    bool result = true;
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    MenuStatusInfo::getHaveBattleStatus(chara).setSelectCommand(status::HaveBattleStatus::NoSelect, 0);
    for (;;) {
        if (--chara < 0) {
            result = false;
            break;
        }
        if (isCommandingPlayer(chara)) {
            MenuStatusInfo::getHaveBattleStatus(chara).setSelectCommand(status::HaveBattleStatus::NoSelect, 0);
            break;
        }
    }
    BattleMenuPlayerControl::getSingleton()->activeChara_ = chara;
    return result;
}

THUMB bool BattleMenuJudge::judgeNextChara()
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    bool result = true;
    for (;;) {
        chara++;
        if (chara >= MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT)) {
            result = false;
            break;
        }
        if (isCommandingPlayer(chara)) {
            break;
        }
    }
    BattleMenuPlayerControl::getSingleton()->activeChara_ = chara;
    return result;
}

THUMB void BattleMenuJudge::backActionMenu(int page)
{
    BattleMonsterNamePlate::getSingleton().init();
    BattleMonsterNamePlate::getSingleton().setMonster();
    gBattleMenu_ACTIONMENU.open();
    gBattleMenu_ACTIONMENU.pageItem_.active_ = page;
}

THUMB void BattleMenuJudge::setAttack(int group)
{
    status::HaveBattleStatus& battleStatus = MenuStatusInfo::getHaveBattleStatus(BattleMenuPlayerControl::getSingleton()->activeChara_);
    battleStatus.setSelectCommand(status::HaveBattleStatus::Attack, 0);
    battleStatus.setSelectGroup(group);
}

THUMB void BattleMenuJudge::setMagicEnemy(int magic, int group)
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    status::HaveBattleStatus& battleStatus = MenuStatusInfo::getHaveBattleStatus(chara);
    battleStatus.setSelectCommand(status::HaveBattleStatus::UseAction, info.haveAction_.getAction(magic));
    battleStatus.setSelectGroup(group);
}

THUMB void BattleMenuJudge::setMagicParty(int magic, int target)
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    status::HaveBattleStatus& battleStatus = MenuStatusInfo::getHaveBattleStatus(chara);
    battleStatus.setSelectCommand(status::HaveBattleStatus::UseAction, info.haveAction_.getAction(magic));
    battleStatus.setSelectGroup(0);
    battleStatus.setSelectTarget(target);
}

THUMB void BattleMenuJudge::setItemEnemy(int item, int group)
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    MenuStatusInfo::getHaveStatusInfo(chara);
    status::HaveBattleStatus& battleStatus = MenuStatusInfo::getHaveBattleStatus(chara);
    battleStatus.setSelectCommand(status::HaveBattleStatus::UseItem, item);
    battleStatus.setSelectGroup(group);
}

THUMB void BattleMenuJudge::setItemEnemyAll(int item)
{
    setItemEnemy(item, 0);
}

THUMB void BattleMenuJudge::setItemParty(int item, int target)
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    MenuStatusInfo::getHaveStatusInfo(chara);
    status::HaveBattleStatus& battleStatus = MenuStatusInfo::getHaveBattleStatus(chara);
    battleStatus.setSelectCommand(status::HaveBattleStatus::UseItem, item);
    battleStatus.setSelectGroup(0);
    battleStatus.setSelectTarget(target);
}

THUMB void BattleMenuJudge::setItemPartyAll(int item)
{
    status::HaveBattleStatus& battleStatus = MenuStatusInfo::getHaveBattleStatus(BattleMenuPlayerControl::getSingleton()->activeChara_);
    setItemEnemy(item, 0);
    battleStatus.setSelectTarget(-1);
}

THUMB int BattleMenuJudge::getMonsterTouchRect(menu::TOUCHRECT* rect)
{
    int count = status::g_Monster.getBattleCount();
    int num = 0;
    for (int i = 0; num < count; i++) {
        if (status::g_Monster.getMonsterStatus(i).isBattleEnable()) {
            int* monsterRect = btl::BattleMonsterMask::getSingleton()->getMonsterTouchRect(i);
            touchRect_[num].group = monsterRect[0];
            touchRect_[num].x = monsterRect[1];
            touchRect_[num].y = monsterRect[2];
            touchRect_[num].width = monsterRect[3] - monsterRect[1];
            touchRect_[num].height = monsterRect[4] - monsterRect[2];
            rect[num].x = touchRect_[num].x;
            rect[num].y = touchRect_[num].y;
            rect[num].width = touchRect_[num].width;
            rect[num].height = touchRect_[num].height;
            rect[num].group = touchRect_[num].group;
            num++;
        }
    }
    return count;
}

THUMB int BattleMenuJudge::getLiveMonsterID()
{
    int i = 0;
    int count = status::g_Monster.getCount();
    for (; i < count; i++) {
        if (status::g_Monster.getMonsterStatus(i).isEnable()) {
            break;
        }
    }
    return i;
}

THUMB bool BattleMenuJudge::judgeBattleArrayChange()
{
    return MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_IN) != 0;
}

THUMB void BattleMenuJudge::setNextPlayer()
{
    BattleMenuPlayerControl::getSingleton()->makePlayerHistory();
    if (getSingleton()->judgeNextChara()) {
        getSingleton()->backActionMenu(0);
        gBattleMenu_ACTIONMENU.activeCharacter_ = getSingleton()->getPlayerIndex();
        return;
    }
    BattleMenuPlayerControl::getSingleton()->activeChara_ = -1;
    btl::BattleMonsterMask::getSingleton()->select(-1);
    gBattleMenuSub_HISTORY.commandChara_ = -1;
    gBattleMenu_ROOT.stat_ = menu::MenuBase::MENUBASE_STAT_OK;
}

THUMB void BattleMenuJudge::setPrevPlayer()
{
    if (getSingleton()->judgeBackChara()) {
        getSingleton()->backActionMenu(0);
        gBattleMenu_ACTIONMENU.activeCharacter_ = getSingleton()->getPlayerIndex();
        gBattleMenuSub_HISTORY.select_ = getSingleton()->getPlayerIndex();
        return;
    }
    gBattleMenu_ROOT.open();
    gBattleMenuSub_HISTORY.commandChara_ = -1;
}

THUMB bool BattleMenuJudge::isCommandingPlayer(int index)
{
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(index);
    int command = info.getHaveStatus().getCommand();
    if (info.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_TIMESTOP)
        && info.getCharacterType() == info.getStatusChange().getCharacterTypeForTimeStop()) {
        return false;
    }
    if (command == COMMAND_MEIREISASERO
        && info.getHaveStatus().isPlayer()
        && !info.isDeath()
        && !info.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI)
        && !info.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)
        && !info.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1)
        && !info.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON)
        && !info.getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_DORAGORAM)) {
        if (minadeinFlag_ == 0) {
            return true;
        }
        return false;
    }
    return false;
}
