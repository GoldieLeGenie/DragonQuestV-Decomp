#pragma ipa file

#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/UseAction.hpp"

using menu::MenuStatusInfo;

inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }

THUMB void BattleMenu_ARRAY_CHANGE::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    gBattleMenuSub_HISTORY.close();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    targetItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    pageItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    prevPhase_ = 0;
    phase_ = 0;
    targetPos_ = 0;
    memberNavigator_.setupBase();
    targetNavigator_.setupBase();
}

THUMB void BattleMenu_ARRAY_CHANGE::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    if (phase_ == 0) {
        int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
        memberNavigator_.setup(4, 1, count);
        setupBattleArrayChange4x1(&menuItem_, BattleMenuPlayerControl::getSingleton()->activeChara_, count);
    } else {
        int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) - MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
        targetNavigator_.setup(4, 1, count);
        int num = count - targetNavigator_.getMaxCountInPage() * targetNavigator_.getPageNo();
        int page;
        int last = targetNavigator_.getPageMaxCount() - 1;
        page = targetNavigator_.getPageNo();
        if (page != last) {
            num = targetNavigator_.getMaxCountInPage();
        }
        setupBattleArrayChangeTo4x1(&targetItem_, targetPos_, num);
        int max = targetNavigator_.getPageMaxCount() - 1;
        setupBattlePageArrow(&pageItem_, pageItem_.active_, max, 0xc4, 0x88);
    }
    setupBattleCancel(&cancelItem_);
}

THUMB void BattleMenu_ARRAY_CHANGE::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        return;
    }
    if (phase_ == 0) {
        drawFormationChangeMemberMenu();
    } else {
        int list[8] = {-1};
        for (int i = 0; i < 8; i++) list[i] = -1;
        int out = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
        int num = 0;
        for (int i = out; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
            list[num] = i;
            num++;
        }
        int target = out + targetNavigator_.getIndex(targetPos_);
        BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
        drawFormationChangeTargetMenu(list, num, targetNavigator_.getPageNo());
    }
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    if (phase_ != 0) {
        chara = BattleMenuPlayerControl::getSingleton()->targetChara_;
    }
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    int count = info.haveAction_.getCount();
    int num = 0;
    int actions[20] = {0};
    for (int i = 0; i < 20; i++) actions[i] = 0;
    for (int i = 0; i < count; i++) {
        if (status::UseAction::isBattleUse(info.haveAction_.getAction(i))) {
            actions[num] = info.haveAction_.getAction(i);
            num++;
        }
    }
    drawCharaBattleSpellList(actions, num, chara);
    menuItem_.drawActive();
    targetItem_.drawActive();
}

THUMB void BattleMenu_ARRAY_CHANGE::menuUpdate()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    if (!cancelUpdate()) {
        if (phase_ == 0) {
            memberUpdate();
        } else {
            targetUpdate();
        }
    }
    if (prevPhase_ != phase_) {
        if (phase_ == 0) {
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            targetItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
            menuItem_.active_ = BattleMenuPlayerControl::getSingleton()->activeChara_;
            targetItem_.active_ = 0;
        } else {
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
            targetItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            menuItem_.active_ = BattleMenuPlayerControl::getSingleton()->activeChara_;
            targetItem_.active_ = targetPos_;
        }
        prevPhase_ = phase_;
    }
}

THUMB int BattleMenu_ARRAY_CHANGE::memberUpdate()
{
    int result = MenuUpdate_Assist::menuSelect(menuItem_, memberNavigator_);
    if (result != 0) {
        redraw_ = 1;
        if (result == 1) {
            phase_ = 0;
        }
        if (result == 2) {
            phase_ = 1;
            menuItem_.result_ = 0;
            menuItem_.lastresult_ = 0;
        }
        int chara = menuItem_.active_;
        BattleMenuPlayerControl::getSingleton()->activeChara_ = chara;
        return 1;
    }
    int chara = menuItem_.active_;
    BattleMenuPlayerControl::getSingleton()->activeChara_ = chara;
    return 0;
}

THUMB int BattleMenu_ARRAY_CHANGE::targetUpdate()
{
    int result = MenuUpdate_Assist::menuSelect(targetItem_, targetNavigator_);
    if (result != 0) {
        redraw_ = 1;
        targetPos_ = targetItem_.active_;
        if (result == 1) {
            phase_ = 1;
        }
        if (result == 2) {
            int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
            int flag = 1;
            int order[4] = {-1};
            for (int i = 0; i < 4; i++) order[i] = -1;
            for (int i = 0; i < count; i++) {
                order[i] = i;
                if (i == BattleMenuPlayerControl::getSingleton()->activeChara_) {
                    int target = BattleMenuPlayerControl::getSingleton()->targetChara_;
                    order[i] = target;
                    if (!MenuStatusInfo::getHaveStatusInfo(target).isDeath()
                        && !MenuStatusInfo::getHaveStatusInfo(target).getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
                        flag = 0;
                    }
                } else if (!MenuStatusInfo::getHaveStatusInfo(i).isDeath()
                    && !MenuStatusInfo::getHaveStatusInfo(i).getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
                    flag = 0;
                }
            }
            if (flag) {
                gTownMenu_MESSAGE.openMessageForBATTLE();
                gTownMenu_MESSAGE.addMessage(0xc3d50);
                gTownMenu_MESSAGE.setMessageLastCursor(false);
                targetItem_.result_ = 0;
                targetItem_.lastresult_ = 0;
                redraw_ = 1;
                return 1;
            }
            MenuStatusInfo::reorder(order[0], order[1], order[2], order[3]);
            targetItem_.result_ = 0;
            targetItem_.lastresult_ = 0;
            redraw_ = 1;
            BattleMenuPlayerControl::getSingleton()->resetTargetGroup();
            close();
            gBattleMenu_ROOT.open();
            gBattleMenu_ROOT.menuItem_.active_ = 0;
        }
        return 1;
    }
    targetPos_ = targetItem_.active_;
    int active = targetItem_.active_;
    if (MenuUpdate_Assist::isPageFlipOne(pageItem_, targetNavigator_, active)) {
        targetItem_.active_ = active;
        targetPos_ = active;
        redraw_ = 1;
        return 1;
    }
    return 0;
}

THUMB int BattleMenu_ARRAY_CHANGE::cancelUpdate()
{
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        if (phase_ == 0) {
            close();
            gBattleMenu_ARRAYMENU.open();
            gBattleMenu_ARRAYMENU.cursorPos_ = 0;
        } else if (phase_ == 1) {
            phase_ = 0;
        }
        redraw_ = 1;
        return 1;
    }
    return 0;
}
