#include "ov018/menu/BattleMenu.hpp"
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/status/HaveBattleStatus.hpp"

using menu::MenuStatusInfo;

THUMB void BattleMenu_ITEMUSE2PARTY::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD, menu::MenuItem::CURSORTYPE_ACTIVE);
    cancelItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    activeChara_ = BattleMenuPlayerControl::getSingleton()->activeChara_;
    activeItem_ = BattleMenuPlayerControl::getSingleton()->activeItem_;
    partyMax_ = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    if (unkfunc_02173308(MenuStatusInfo::getPlayerItemID(activeChara_, activeItem_))) {
        for (int i = 0; i < partyMax_; i++) {
            if (MenuStatusInfo::getHaveStatusInfo(i).isDeath()) {
                menuItem_.active_ = i;
                return;
            }
        }
    }
}

THUMB void BattleMenu_ITEMUSE2PARTY::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    navigator_.setup(2, 2, partyMax_);
    unkfunc_02175ae8(&menuItem_, partyMax_);
    unkfunc_02175a5c(&cancelItem_);
}

THUMB void BattleMenu_ITEMUSE2PARTY::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unkfunc_02170078();
    menuItem_.drawActive();
}

THUMB void BattleMenu_ITEMUSE2PARTY::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (MenuUpdate_Assist::isCancel(cancelItem_)) {
        int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
        int item = BattleMenuPlayerControl::getSingleton()->activeItem_;
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
        if (info.isEquipEnable(info.haveItem_.getItem(item))) {
            gUnkBattleMenuEquipItem.open();
        } else {
            gBattleMenu_ITEM.open();
        }
        MenuStatusInfo::getHaveBattleStatus(chara).setSelectCommand(status::HaveBattleStatus::UseItem, -1);
        close();
        return;
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        redraw_ = 1;
        if (result == 2) {
            close();
            BattleMenuJudge::getSingleton()->setItemParty(activeItem_, menuItem_.active_);
            BattleMenuJudge::getSingleton()->setNextPlayer();
        }
        int target = menuItem_.active_;
        BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
    }
    int target = menuItem_.active_;
    BattleMenuPlayerControl::getSingleton()->targetChara_ = target;
}

THUMB bool BattleMenu_ITEMUSE2PARTY::unkfunc_02173308(int item)
{
    if (item == 0x27) {
        return true;
    }
    if (item == 0xa5) {
        return true;
    }
    return false;
}
