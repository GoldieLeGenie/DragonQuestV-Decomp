#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseAction.hpp"

using menu::MenuStatusInfo;

inline status::HaveStatus& status::HaveStatusInfo::getHaveStatus() { return haveStatus_; }
inline status::StatusChange& status::HaveStatusInfo::getStatusChange() { return statusChange_; }
inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo() { return haveStatusInfo_; }
inline bool status::HaveStatus::isBattleNpc() const { return playerType_ == TYPE_BATTLENPC; }
inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

THUMB void BattleMenu_ARRAY_ALL::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    gBattleMenuSub_HISTORY.close();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    unk_2c = 0;
    unk_30 = 0;
    unk_1c[0] = -1;
    unk_1c[1] = -1;
    unk_1c[2] = -1;
    unk_1c[3] = -1;
    navigator_.setupBase();
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        if (MenuStatusInfo::getHaveStatusInfo(i).getHaveStatus().isBattleNpc()) {
            unk_1c[i] = i;
            unk_2c++;
            unk_30++;
        }
    }
}

THUMB void BattleMenu_ARRAY_ALL::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    int num = unk_2c;
    int count = unkfunc_02171fec() - num;
    if (num - unk_30 > 0 && unkfunc_02171fb8()) {
        count++;
    }
    navigator_.setup(5, 2, count);
    unkfunc_02175b6c(&menuItem_, menuItem_.active_, count);
    unkfunc_02175a5c(&cancelItem_);
}

THUMB void BattleMenu_ARRAY_ALL::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        unkfunc_02171d9c();
        return;
    }
    unkfunc_02171cc0();
    unkfunc_02171d9c();
}

THUMB void BattleMenu_ARRAY_ALL::unkfunc_02171cc0()
{
    int list[8] = {-1};
    for (int i = 0; i < 8; i++) list[i] = -1;
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    int count = unkfunc_02171fec();
    int num = 0;
    for (int i = 0; i < count; i++) {
        int free = 1;
        for (int j = 0; j < 4; j++) {
            if (i == unk_1c[j]) {
                free = 0;
            }
        }
        if (free) {
            if (num == menuItem_.active_) {
                BattleMenuPlayerControl::getSingleton()->targetChara_ = i;
            }
            list[num] = i;
            num++;
        }
    }
    if (unk_2c - unk_30 > 0 && unkfunc_02171fb8()) {
        if (num == menuItem_.active_) {
            BattleMenuPlayerControl::getSingleton()->targetChara_ = count;
        }
        list[num] = -1;
        num++;
    }
    unkfunc_0217043c(list, num, unk_1c, unk_2c);
    menuItem_.drawActive();
    cancelItem_.drawActive();
}

THUMB void BattleMenu_ARRAY_ALL::unkfunc_02171d9c()
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    int actionCount;
    int count = unkfunc_02171fec();
    int chara = BattleMenuPlayerControl::getSingleton()->targetChara_;
    if (chara != count) {
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
        actionCount = info.haveAction_.getCount();
        int actionNum = 0;
        int actions[20] = {0};
        for (int i = 0; i < 20; i++) actions[i] = 0;
        for (int i = 0; i < actionCount; i++) {
            if (status::UseAction::isBattleUse(info.haveAction_.getAction(i))) {
                actions[actionNum] = info.haveAction_.getAction(i);
                actionNum++;
            }
        }
        unkfunc_02170c78(actions, actionNum, chara);
    }
}

THUMB void BattleMenu_ARRAY_ALL::menuUpdate()
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
        if (unk_2c - unk_30 == 0) {
            close();
            gBattleMenu_ARRAYMENU.open();
            gBattleMenu_ARRAYMENU.cursorPos_ = 1;
        } else {
            unkfunc_02172034();
        }
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        redraw_ = 1;
        return;
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result == 0) {
        return;
    }
    redraw_ = 1;
    if (result != 2) {
        return;
    }
    int used = 0;
    menuItem_.result_ = 0;
    menuItem_.lastresult_ = 0;
    int list[10] = {0};
    for (int i = 0; i < 10; i++) list[i] = 0;
    int num = 0;
    int active = menuItem_.active_;
    int count = unkfunc_02171fec();
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == unk_1c[j]) {
                used = 1;
            }
        }
        if (!used) {
            list[num] = i;
            num++;
        }
        used = 0;
    }
    if (num - 1 == active) {
        menuItem_.active_ = active - 1;
    }
    if (active == count - unk_2c && unk_2c - unk_30 != 0) {
        unkfunc_0217206c();
        return;
    }
    unkfunc_02172008(list[active]);
    int max = unkfunc_02171fec();
    if (max > 4) {
        max = 4;
    }
    if (unk_2c == max) {
        unkfunc_0217206c();
    }
}

THUMB void BattleMenu_ARRAY_ALL::unkfunc_02171f9c()
{
    MenuStatusInfo::reorder(unk_1c[0], unk_1c[1], unk_1c[2], unk_1c[3]);
    BattleMenuPlayerControl::getSingleton()->resetTargetGroup();
}

THUMB bool BattleMenu_ARRAY_ALL::unkfunc_02171fb8()
{
    if (!MenuStatusInfo::isCarriageEnable()) {
        return false;
    }
    if (status::g_Party.getPlayerStatus(0).getHaveStatusInfo().getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_CLOSEDOOR)) {
        return false;
    }
    return true;
}

THUMB int BattleMenu_ARRAY_ALL::unkfunc_02171fec()
{
    if (unkfunc_02171fb8()) {
        return MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    }
    return MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
}

THUMB void BattleMenu_ARRAY_ALL::unkfunc_02172008(int index)
{
    for (int i = 0; i < 4; i++) {
        if (unk_1c[i] == -1) {
            unk_1c[i] = index;
            unk_2c++;
            return;
        }
    }
}

THUMB void BattleMenu_ARRAY_ALL::unkfunc_02172034()
{
    for (int i = 0; i < 4; i++) {
        int index = 3 - i;
        if (unk_1c[index] != -1 && !MenuStatusInfo::getHaveStatusInfo(unk_1c[index]).getHaveStatus().isBattleNpc()) {
            unk_1c[index] = -1;
            unk_2c--;
            return;
        }
    }
}

THUMB void BattleMenu_ARRAY_ALL::unkfunc_0217206c()
{
    if (unkfunc_021720bc()) {
        unkfunc_02171f9c();
        close();
        gBattleMenu_ROOT.open();
        gBattleMenu_ROOT.menuItem_.active_ = 0;
        return;
    }
    gTownMenu_MESSAGE.openMessageForBATTLE();
    gTownMenu_MESSAGE.addMessage(0xc3d50);
    gTownMenu_MESSAGE.setMessageLastCursor(false);
    unkfunc_02172034();
}

THUMB int BattleMenu_ARRAY_ALL::unkfunc_021720bc()
{
    int result = 0;
    for (int i = 0; i < 4; i++) {
        int chara = unk_1c[i];
        if (chara != -1 && !MenuStatusInfo::getHaveStatusInfo(chara).isDeath()
            && MenuStatusInfo::getHaveStatusInfo(chara).getHaveStatus().isPlayer()
            && !MenuStatusInfo::getHaveStatusInfo(chara).getStatusChange().isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI)) {
            result = 1;
        }
    }
    return result;
}
