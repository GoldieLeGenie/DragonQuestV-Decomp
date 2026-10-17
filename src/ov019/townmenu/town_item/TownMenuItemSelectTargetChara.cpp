#pragma ipa file
#include "ov019/townmenu/town_item/TownMenuItemSelectTargetChara.hpp"
#include "ov019/townmenu/town_item/TownMenu_ITEM_CHECKTARGET.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectCommand.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectTargetItem.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline int menu::MenuItem::getActive()
{
    return active_;
}

inline void TownMenuPlayerControl::setTargetChara(unsigned char target)
{
    targetChara_ = target;
}

THUMB void TownMenuItemSelectTargetChara::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = TownMenuPlayerControl::getSingleton()->targetChara_;
    navigator_.setupBase();
    unk_1c = TownMenuPlayerControl::getSingleton()->getDrawCharaCount(menu::TOWN_MENU_ITEM);
}

THUMB void TownMenuItemSelectTargetChara::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (unk_1c <= 5) {
        unkfunc_02171514(&menuItem_, unk_1c, menuItem_.active_);
    } else {
        unkfunc_021714f8(&menuItem_, unk_1c, menuItem_.active_);
    }
}

THUMB void TownMenuItemSelectTargetChara::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_021731f8(open);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenuItemSelectTargetChara::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    navigator_.setup(5, 2, unk_1c);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result == 0) {
        return;
    }
    if (menuItem_.getActive() == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        TownMenuPlayerControl::getSingleton()->targetFukuro_ = 1;
    } else {
        TownMenuPlayerControl::getSingleton()->targetFukuro_ = 0;
    }
    TownMenuPlayerControl::getSingleton()->setTargetChara(menuItem_.active_);
    if (result == 3) {
        TownMenuPlayerControl::getSingleton()->targetChara_ = 0;
        TownMenuPlayerControl::getSingleton()->targetFukuro_ = 0;
        close();
        gTownMenuItemSelectCommand.open();
        return;
    }
    if (result == 2) {
        if (TownMenuPlayerControl::getSingleton()->targetFukuro_ == 1) {
            close();
            gTownMenu_ITEM_CHECKTARGET.open();
            return;
        }
        int itemCount = MenuStatusInfo::getPlayerItemCount(menuItem_.active_);
        if (itemCount < 12) {
            if (itemCount == 6) {
                TownMenuPlayerControl::getSingleton()->targetItem_ = 0;
                TownMenuPlayerControl::getSingleton()->targetItemPage_ = 1;
            } else {
                TownMenuPlayerControl::getSingleton()->targetItemPage_ = itemCount / 6;
                if (itemCount > 6) {
                    itemCount -= 6;
                }
                TownMenuPlayerControl::getSingleton()->targetItem_ = (unsigned char)itemCount;
            }
        } else {
            TownMenuPlayerControl::getSingleton()->targetItem_ = 5;
            TownMenuPlayerControl::getSingleton()->targetItemPage_ = 1;
        }
        close();
        gTownMenuItemSelectTargetItem.open();
        return;
    }
    redraw_ = 1;
}
