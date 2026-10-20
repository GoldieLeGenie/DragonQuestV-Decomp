#pragma ipa file
#include "ov019/townmenu/town_item/TownMenuItemSelectTargetItem.hpp"
#include "ov019/townmenu/town_item/TownMenu_ITEM_CHECKTARGET.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectTargetChara.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline int menu::MenuItem::getActive()
{
    return active_;
}

inline char TownMenuPlayerControl::getTargetItemPage()
{
    return targetItemPage_;
}

inline void TownMenuPlayerControl::setTargetItem(short target)
{
    targetItem_ = target;
}

inline void TownMenuPlayerControl::setTargetItemPage(char page)
{
    targetItemPage_ = page;
}

THUMB void TownMenuItemSelectTargetItem::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = TownMenuPlayerControl::getSingleton()->targetItem_;
    navigator_.setupBase();
    navigator_.setPageNo(TownMenuPlayerControl::getSingleton()->getTargetItemPage());
    if (MenuStatusInfo::getPlayerItemCount(TownMenuPlayerControl::getSingleton()->targetChara_) < 12) {
        TownMenuPlayerControl::getSingleton()->targetItem_ = -1;
    }
}

THUMB void TownMenuItemSelectTargetItem::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int targetChara = TownMenuPlayerControl::getSingleton()->targetChara_;
    int page = TownMenuPlayerControl::getSingleton()->targetItemPage_;
    int count;
    if (MenuStatusInfo::getPlayerItemCount(targetChara) > 5) {
        count = MenuStatusInfo::getPlayerItemCount(targetChara) - page * 6 + 1;
        if (count > 6) {
            count = 6;
        }
    } else {
        count = MenuStatusInfo::getPlayerItemCount(targetChara) + 1;
    }
    setupItemIcon32Layout2x3(&menuItem_, count, menuItem_.active_);
}

THUMB void TownMenuItemSelectTargetItem::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_021732b0(open);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenuItemSelectTargetItem::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int targetChara = TownMenuPlayerControl::getSingleton()->targetChara_;
    if (MenuStatusInfo::getPlayerItemCount(targetChara) < 12) {
        navigator_.setup(2, 3, MenuStatusInfo::getPlayerItemCount(targetChara) + 1);
    } else {
        navigator_.setup(2, 3, 12);
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result == 0) {
        return;
    }
    TownMenuPlayerControl::getSingleton()->setTargetItemPage(navigator_.getPageNo());
    if (unkfunc_02171304(navigator_.getPageNo()) == true) {
        TownMenuPlayerControl::getSingleton()->setTargetItem(-1);
    } else {
        TownMenuPlayerControl::getSingleton()->setTargetItem(menuItem_.active_);
    }
    if (result == 3) {
        close();
        gTownMenuItemSelectTargetChara.open();
    }
    if (result == 2) {
        close();
        gTownMenu_ITEM_CHECKTARGET.open();
    }
    redraw_ = 1;
}

THUMB bool TownMenuItemSelectTargetItem::unkfunc_02171304(int page)
{
    int targetChara = TownMenuPlayerControl::getSingleton()->targetChara_;
    if (MenuStatusInfo::getPlayerItemCount(targetChara) != 12 && MenuStatusInfo::getPlayerItemCount(targetChara) == page * 6 + menuItem_.getActive()) {
        return true;
    }
    return false;
}
