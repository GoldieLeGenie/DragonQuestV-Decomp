#pragma ipa file
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_EQUIP.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_ROOT.hpp"
#include "ov019/townmenu/town_operation/UnkTownMenuOperationEquipItem.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline void TownMenuPlayerControl::setActiveChara(unsigned char chara)
{
    activeChara_ = chara;
}

THUMB void TownMenu_OPERATION_EQUIP::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = TownMenuPlayerControl::getSingleton()->activeChara_;
    navigator_.setupBase();
}

THUMB void TownMenu_OPERATION_EQUIP::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (count < 6) {
        townMenuItemSelectHalfChara(&menuItem_, count, menuItem_.active_);
    } else {
        townMenuItemSelectChara(&menuItem_, count, menuItem_.active_);
    }
}

THUMB void TownMenu_OPERATION_EQUIP::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    drawEquipCharaSelectScreen(open);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenu_OPERATION_EQUIP::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    navigator_.setup(5, 2, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        TownMenuPlayerControl::getSingleton()->setActiveChara(menuItem_.active_);
        if (result == 3) {
            close();
            gTownMenu_OPERATION_ROOT.open();
        }
        if (result == 2) {
            close();
            data_ov019_02183b54.open();
        }
        redraw_ = 1;
    }
}
