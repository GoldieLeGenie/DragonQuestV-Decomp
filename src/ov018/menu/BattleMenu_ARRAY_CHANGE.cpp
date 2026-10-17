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
    unk_8c.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    unk_f0.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    unk_20 = 0;
    unk_1c = 0;
    unk_24 = 0;
    unk_1b8.setupBase();
    unk_1c4.setupBase();
}

THUMB void BattleMenu_ARRAY_CHANGE::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    if (unk_1c == 0) {
        int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
        unk_1b8.setup(4, 1, count);
        unkfunc_02175b34(&menuItem_, BattleMenuPlayerControl::getSingleton()->activeChara_, count);
    } else {
        int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) - MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
        unk_1c4.setup(4, 1, count);
        int num = count - unk_1c4.getMaxCountInPage() * unk_1c4.getPageNo();
        int page;
        int last = unk_1c4.getPageMaxCount() - 1;
        page = unk_1c4.getPageNo();
        if (page != last) {
            num = unk_1c4.getMaxCountInPage();
        }
        unkfunc_02175b50(&unk_8c, unk_24, num);
        int max = unk_1c4.getPageMaxCount() - 1;
        unkfunc_02175c0c(&unk_f0, unk_f0.active_, max, 0xc4, 0x88);
    }
    unkfunc_02175a5c(&cancelItem_);
}

THUMB void BattleMenu_ARRAY_CHANGE::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        return;
    }
    if (unk_1c == 0) {
        unkfunc_02170364();
    } else {
        int list[8] = {-1};
        for (int i = 0; i < 8; i++) list[i] = -1;
        int out = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
        int num = 0;
        for (int i = out; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
            list[num] = i;
            num++;
        }
        int target = out + unk_1c4.getIndex(unk_24);
        BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
        unkfunc_021703dc(list, num, unk_1c4.getPageNo());
    }
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    if (unk_1c != 0) {
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
    unkfunc_02170c78(actions, num, chara);
    menuItem_.drawActive();
    unk_8c.drawActive();
}

THUMB void BattleMenu_ARRAY_CHANGE::menuUpdate()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        if ((unsigned int)(gTownMenu_MESSAGE.stat_ - 1) <= 1) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    if (!unkfunc_0217262c()) {
        if (unk_1c == 0) {
            unkfunc_02172454();
        } else {
            unkfunc_0217249c();
        }
    }
    if (unk_20 != unk_1c) {
        if (unk_1c == 0) {
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            unk_8c.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
            menuItem_.active_ = BattleMenuPlayerControl::getSingleton()->activeChara_;
            unk_8c.active_ = 0;
        } else {
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
            unk_8c.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            menuItem_.active_ = BattleMenuPlayerControl::getSingleton()->activeChara_;
            unk_8c.active_ = unk_24;
        }
        unk_20 = unk_1c;
    }
}

THUMB int BattleMenu_ARRAY_CHANGE::unkfunc_02172454()
{
    int result = MenuUpdate_Assist::menuSelect(menuItem_, unk_1b8);
    if (result != 0) {
        redraw_ = 1;
        if (result == 1) {
            unk_1c = 0;
        }
        if (result == 2) {
            unk_1c = 1;
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

THUMB int BattleMenu_ARRAY_CHANGE::unkfunc_0217249c()
{
    int result = MenuUpdate_Assist::menuSelect(unk_8c, unk_1c4);
    if (result != 0) {
        redraw_ = 1;
        unk_24 = unk_8c.active_;
        if (result == 1) {
            unk_1c = 1;
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
                unk_8c.result_ = 0;
                unk_8c.lastresult_ = 0;
                redraw_ = 1;
                return 1;
            }
            MenuStatusInfo::reorder(order[0], order[1], order[2], order[3]);
            unk_8c.result_ = 0;
            unk_8c.lastresult_ = 0;
            redraw_ = 1;
            BattleMenuPlayerControl::getSingleton()->resetTargetGroup();
            close();
            gBattleMenu_ROOT.open();
            gBattleMenu_ROOT.menuItem_.active_ = 0;
        }
        return 1;
    }
    unk_24 = unk_8c.active_;
    int active = unk_8c.active_;
    if (MenuUpdate_Assist::isPageFlipOne(unk_f0, unk_1c4, active)) {
        unk_8c.active_ = active;
        unk_24 = active;
        redraw_ = 1;
        return 1;
    }
    return 0;
}

THUMB int BattleMenu_ARRAY_CHANGE::unkfunc_0217262c()
{
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        if (unk_1c == 0) {
            close();
            gBattleMenu_ARRAYMENU.open();
            gBattleMenu_ARRAYMENU.unk_1c = 0;
        } else if (unk_1c == 1) {
            unk_1c = 0;
        }
        redraw_ = 1;
        return 1;
    }
    return 0;
}
