#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"

using menu::MenuStatusInfo;

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline int status::HaveStatus::getPlayerIndex() const { return playerIndex_; }
inline int status::HaveStatus::getCommand() const { return command_; }
inline void status::HaveStatus::setCommand(CommandType type) { command_ = type; }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

THUMB void BattleMenu_TACTICSMENU::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    tacticsItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    prevPhase_ = 0;
    phase_ = 0;
    tacticsPos_ = MenuStatusInfo::getHaveStatusInfo(0).getHaveStatus().getCommand();
    memberPos_ = 0;
    memberNum_ = 1;
    for (int i = 0; i < 10; i++) {
        memberList_[i] = -1;
    }
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
        if (info.getHaveStatus().isPlayer() && info.getHaveStatus().getPlayerIndex() > 1) {
            memberList_[memberNum_] = i;
            memberNum_++;
        }
    }
    memberList_[0] = -1;
    memberList_[memberNum_] = -1;
    tacticsNavigator_.setupBase();
}

THUMB void BattleMenu_TACTICSMENU::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    tacticsNavigator_.setup(3, 2, 6);
    memberNavigator_.setup(5, 1, memberNum_);
    if (phase_ == 0) {
        setupBattleTacticsChange5x1(&menuItem_, memberPos_, memberNum_);
    } else {
        setupBattleTactics3x2(&tacticsItem_, tacticsPos_);
    }
    setupBattleCancel(&cancelItem_);
}

THUMB void BattleMenu_TACTICSMENU::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (phase_ == 0) {
        drawTacticsMemberMenu();
    } else {
        drawTacticsSelectMenu();
    }
    menuItem_.drawActive();
    tacticsItem_.drawActive();
}

THUMB void BattleMenu_TACTICSMENU::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (!unkfunc_0217503c() && !unkfunc_02174f78()) {
        tacticsUpdate();
    }
    memberPos_ = memberNavigator_.getIndex(menuItem_.active_);
    tacticsPos_ = tacticsNavigator_.getIndex(tacticsItem_.active_);
    if (prevPhase_ != phase_) {
        if (phase_ == 0) {
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            tacticsItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
        } else {
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
            tacticsItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
        }
        menuItem_.active_ = memberPos_;
        tacticsItem_.active_ = tacticsPos_;
        prevPhase_ = phase_;
    }
}

THUMB int BattleMenu_TACTICSMENU::unkfunc_02174f78()
{
    int result = MenuUpdate_Assist::menuSelect(menuItem_, memberNavigator_);
    if (result != 0) {
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        redraw_ = 1;
        memberPos_ = memberNavigator_.getIndex(menuItem_.active_);
        unkfunc_02175088();
        if (result == 1) {
            phase_ = 0;
        } else if (result == 2) {
            phase_ = 1;
            tacticsItem_.active_ = tacticsPos_;
        }
        return 1;
    }
    return 0;
}

THUMB void BattleMenu_TACTICSMENU::tacticsUpdate()
{
    int result = MenuUpdate_Assist::menuSelect(tacticsItem_, tacticsNavigator_);
    if (result == 0) {
        return;
    }
    if (result == 1) {
        phase_ = 1;
        redraw_ = 1;
        return;
    }
    if (result == 2) {
        if (phase_ == 0) {
            phase_ = 1;
        } else if (phase_ == 1) {
            setTactics();
            phase_ = 0;
        }
        close();
        gBattleMenu_ROOT.open();
        gBattleMenu_ROOT.menuItem_.active_ = 0;
        tacticsItem_.result_ = 0;
        tacticsItem_.lastresult_ = 0;
        redraw_ = 1;
    }
}

THUMB int BattleMenu_TACTICSMENU::unkfunc_0217503c()
{
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        cancelItem_.result_ = 0;
        cancelItem_.lastresult_ = 0;
        if (phase_ == 0) {
            close();
            gBattleMenu_ROOT.open();
            gBattleMenu_ROOT.menuItem_.active_ = 2;
        } else if (phase_ == 1) {
            phase_ = 0;
        }
        redraw_ = 1;
        return 1;
    }
    return 0;
}

THUMB void BattleMenu_TACTICSMENU::unkfunc_02175088()
{
    int chara = memberList_[memberPos_];
    BattleMenuPlayerControl::getSingleton()->activeChara_ = chara;
    tacticsPos_ = 0;
    if (memberPos_ > 0) {
        tacticsPos_ = MenuStatusInfo::getHaveStatusInfo(chara).getHaveStatus().getCommand();
    } else if (memberList_[1] != -1) {
        tacticsPos_ = MenuStatusInfo::getHaveStatusInfo(memberList_[1]).getHaveStatus().getCommand();
    } else {
        tacticsPos_ = 0;
    }
}

THUMB void BattleMenu_TACTICSMENU::setTactics()
{
    CommandType command[6] = {
        COMMAND_GANGANIKOUZE,
        COMMAND_BACCHIRIGANBARE,
        COMMAND_ORENIMAKASERO,
        COMMAND_JYUMONTUKAUNA,
        COMMAND_INOCHIDAIZINI,
        COMMAND_MEIREISASERO
    };
    if (memberPos_ != 0) {
        MenuStatusInfo::getHaveStatusInfo(memberList_[memberPos_]).getHaveStatus().setCommand(command[tacticsPos_]);
        return;
    }
    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
        if (info.getHaveStatus().isPlayer() && info.getHaveStatus().getPlayerIndex() != 1) {
            info.getHaveStatus().setCommand(command[tacticsPos_]);
        }
    }
}
