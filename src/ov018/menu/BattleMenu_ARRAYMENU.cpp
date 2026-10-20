#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"

using menu::MenuStatusInfo;

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

THUMB void BattleMenu_ARRAYMENU::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    if (!gBattleMenuSub_HISTORY.isOpen()) {
        BattleMenuPlayerControl::getSingleton()->clear();
        BattleMenuPlayerControl::getSingleton()->activeChara_ = -1;
        gBattleMenuSub_HISTORY.open();
        gBattleMenuSub_HISTORY.commandChara_ = -1;
    }
    gBattleMenuSub_HISTORY.history_ = 1;
    gBattleMenuSub_HISTORY.update_ = 1;
    gBattleMenuSub_HISTORY.select_ = 0;
    BattleMenuPlayerControl::getSingleton()->activeChara_ = -1;
    cursorPos_ = 0;
}

THUMB void BattleMenu_ARRAYMENU::menuExecute()
{
    setupBattleArrayMenu2x1(&menuItem_, cursorPos_);
    setupBattleCancel(&cancelItem_);
}

THUMB void BattleMenu_ARRAYMENU::menuDraw()
{
    if (!gTownMenu_MESSAGE.isOpen()) {
        drawFormationMenu();
        menuItem_.drawActive();
    }
}

THUMB BattleMenu_ARRAYMENU::CHANGE_RESULT BattleMenu_ARRAYMENU::isChangeling()
{
    if (!BattleMenuJudge::getSingleton()->judgeBattleArrayChange() && menuItem_.active_ == 0) {
        return CHANGE_DISABLE;
    }
    if (MenuStatusInfo::isCarriageEnable()) {
        return isBlocking();
    }
    if (menuItem_.active_ == 1) {
        int count = status::g_Party.getCount();
        int num = 0;
        for (int i = 0; i < count; i++) {
            if (MenuStatusInfo::getHaveStatusInfo(i).getHaveStatus().isPlayer()) {
                num++;
            }
        }
        if (num > 1) {
            return CHANGE_ENABLE;
        }
    }
    return CHANGE_DISABLE;
}

THUMB BattleMenu_ARRAYMENU::CHANGE_RESULT BattleMenu_ARRAYMENU::isBlocking()
{
    status::g_Party.setBattleMode();
    if (status::g_Party.getCount() == 1) {
        return CHANGE_DISABLE;
    }
    if (status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_CLOSEDOOR)) {
        if (menuItem_.active_ == 1 && status::g_Party.getCarriageOutCount() > 1) {
            return CHANGE_ENABLE;
        }
        return CHANGE_BLOCK;
    }
    return CHANGE_ENABLE;
}

THUMB void BattleMenu_ARRAYMENU::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        cancelItem_.result_ = 0;
        cancelItem_.lastresult_ = 0;
        close();
        gBattleMenu_ROOT.open();
        gBattleMenu_ROOT.menuItem_.active_ = 1;
        redraw_ = 1;
        return;
    }
    menuItem_.execInput();
    switch (menuItem_.result_) {
    case menu::MenuItem::MENUITEM_RESULT_CHANGE:
        cursorPos_ = menuItem_.active_;
        break;
    case menu::MenuItem::MENUITEM_RESULT_OK:
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        redraw_ = 1;
        changeUpdate();
        break;
    case menu::MenuItem::MENUITEM_RESULT_LEFT:
        cursorPos_ = 1;
        menuItem_.active_ = 1;
        break;
    case menu::MenuItem::MENUITEM_RESULT_RIGHT:
        cursorPos_ = 0;
        menuItem_.active_ = 0;
        break;
    }
}

THUMB void BattleMenu_ARRAYMENU::changeUpdate()
{
    switch (isChangeling()) {
    case CHANGE_ENABLE:
        close();
        BattleMenuPlayerControl::getSingleton()->activeChara_ = 0;
        if (menuItem_.active_ == 0) {
            gBattleMenu_ARRAY_CHANGE.open();
        } else {
            gBattleMenu_ARRAY_ALL.open();
        }
        break;
    case CHANGE_DISABLE:
        gTownMenu_MESSAGE.openMessageForBATTLE();
        gTownMenu_MESSAGE.addMessage(0xc3b71);
        gTownMenu_MESSAGE.setMessageLastCursor(false);
        break;
    case CHANGE_BLOCK:
        gTownMenu_MESSAGE.openMessageForBATTLE();
        gTownMenu_MESSAGE.addMessage(0xc3b71);
        gTownMenu_MESSAGE.setMessageLastCursor(false);
        break;
    }
}
