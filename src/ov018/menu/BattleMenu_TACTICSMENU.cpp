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
    unk_120.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    unk_20 = 0;
    unk_1c = 0;
    unk_28 = MenuStatusInfo::getHaveStatusInfo(0).getHaveStatus().getCommand();
    unk_24 = 0;
    unk_54 = 1;
    for (int i = 0; i < 10; i++) {
        unk_2c[i] = -1;
    }
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
        if (info.getHaveStatus().isPlayer() && info.getHaveStatus().getPlayerIndex() > 1) {
            unk_2c[unk_54] = i;
            unk_54++;
        }
    }
    unk_2c[0] = -1;
    unk_2c[unk_54] = -1;
    unk_1f4.setupBase();
}

THUMB void BattleMenu_TACTICSMENU::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unk_1f4.setup(3, 2, 6);
    unk_1e8.setup(5, 1, unk_54);
    if (unk_1c == 0) {
        unkfunc_02175b18(&menuItem_, unk_24, unk_54);
    } else {
        unkfunc_02175acc(&unk_120, unk_28);
    }
    unkfunc_02175a5c(&cancelItem_);
}

THUMB void BattleMenu_TACTICSMENU::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (unk_1c == 0) {
        unkfunc_0217015c();
    } else {
        unkfunc_02170210();
    }
    menuItem_.drawActive();
    unk_120.drawActive();
}

THUMB void BattleMenu_TACTICSMENU::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (!unkfunc_0217503c() && !unkfunc_02174f78()) {
        unkfunc_02174fd4();
    }
    unk_24 = unk_1e8.getIndex(menuItem_.active_);
    unk_28 = unk_1f4.getIndex(unk_120.active_);
    if (unk_20 != unk_1c) {
        if (unk_1c == 0) {
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
            unk_120.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
        } else {
            menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
            unk_120.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
        }
        menuItem_.active_ = unk_24;
        unk_120.active_ = unk_28;
        unk_20 = unk_1c;
    }
}

THUMB int BattleMenu_TACTICSMENU::unkfunc_02174f78()
{
    int result = MenuUpdate_Assist::menuSelect(menuItem_, unk_1e8);
    if (result != 0) {
        menuItem_.result_ = 0;
        menuItem_.lastresult_ = 0;
        redraw_ = 1;
        unk_24 = unk_1e8.getIndex(menuItem_.active_);
        unkfunc_02175088();
        if (result == 1) {
            unk_1c = 0;
        } else if (result == 2) {
            unk_1c = 1;
            unk_120.active_ = unk_28;
        }
        return 1;
    }
    return 0;
}

THUMB void BattleMenu_TACTICSMENU::unkfunc_02174fd4()
{
    int result = MenuUpdate_Assist::menuSelect(unk_120, unk_1f4);
    if (result == 0) {
        return;
    }
    if (result == 1) {
        unk_1c = 1;
        redraw_ = 1;
        return;
    }
    if (result == 2) {
        if (unk_1c == 0) {
            unk_1c = 1;
        } else if (unk_1c == 1) {
            unkfunc_021750cc();
            unk_1c = 0;
        }
        close();
        gBattleMenu_ROOT.open();
        gBattleMenu_ROOT.menuItem_.active_ = 0;
        unk_120.result_ = 0;
        unk_120.lastresult_ = 0;
        redraw_ = 1;
    }
}

THUMB int BattleMenu_TACTICSMENU::unkfunc_0217503c()
{
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        cancelItem_.result_ = 0;
        cancelItem_.lastresult_ = 0;
        if (unk_1c == 0) {
            close();
            gBattleMenu_ROOT.open();
            gBattleMenu_ROOT.menuItem_.active_ = 2;
        } else if (unk_1c == 1) {
            unk_1c = 0;
        }
        redraw_ = 1;
        return 1;
    }
    return 0;
}

THUMB void BattleMenu_TACTICSMENU::unkfunc_02175088()
{
    int chara = unk_2c[unk_24];
    BattleMenuPlayerControl::getSingleton()->activeChara_ = chara;
    unk_28 = 0;
    if (unk_24 > 0) {
        unk_28 = MenuStatusInfo::getHaveStatusInfo(chara).getHaveStatus().getCommand();
    } else if (unk_2c[1] != -1) {
        unk_28 = MenuStatusInfo::getHaveStatusInfo(unk_2c[1]).getHaveStatus().getCommand();
    } else {
        unk_28 = 0;
    }
}

THUMB void BattleMenu_TACTICSMENU::unkfunc_021750cc()
{
    CommandType command[6] = {
        COMMAND_GANGANIKOUZE,
        COMMAND_BACCHIRIGANBARE,
        COMMAND_ORENIMAKASERO,
        COMMAND_JYUMONTUKAUNA,
        COMMAND_INOCHIDAIZINI,
        COMMAND_MEIREISASERO
    };
    if (unk_24 != 0) {
        MenuStatusInfo::getHaveStatusInfo(unk_2c[unk_24]).getHaveStatus().setCommand(command[unk_28]);
        return;
    }
    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
        if (info.getHaveStatus().isPlayer() && info.getHaveStatus().getPlayerIndex() != 1) {
            info.getHaveStatus().setCommand(command[unk_28]);
        }
    }
}
