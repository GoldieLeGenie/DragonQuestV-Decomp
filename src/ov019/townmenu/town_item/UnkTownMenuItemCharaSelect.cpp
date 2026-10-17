#pragma ipa file
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov019/townmenu/town_item/TownMenuItemSelectChara.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline int menu::MenuItem::getActive()
{
    return active_;
}

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

inline void TownMenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

inline void TownMenuPlayerControl::setActiveItemPage(char page)
{
    activeItemPage_ = page;
}

inline void TownMenuPlayerControl::setActiveFukuro()
{
    activeFukuro_ = true;
}

inline void TownMenuPlayerControl::resetActiveFukuro()
{
    activeFukuro_ = false;
}

THUMB void UnkTownMenuItemCharaSelect::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = TownMenuPlayerControl::getSingleton()->activeChara_;
    charaCount_ = TownMenuPlayerControl::getSingleton()->getDrawCharaCount(menu::TOWN_MENU_ITEM);
    navigator_.setupBase();
    navigator_.setup(5, 2, charaCount_);
    unk_20 = 0;
}

THUMB void UnkTownMenuItemCharaSelect::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (charaCount_ <= 5) {
        unkfunc_02171514(&menuItem_, charaCount_, menuItem_.active_);
    } else {
        unkfunc_021714f8(&menuItem_, charaCount_, menuItem_.active_);
    }
}

THUMB void UnkTownMenuItemCharaSelect::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_02172f1c(open);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void UnkTownMenuItemCharaSelect::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        if (gTownMenu_MESSAGE.stat_ == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            if (unk_20 == 1) {
                close();
                gTownMenu_ROOT.stat_ = MENUBASE_STAT_OK;
                return;
            }
        }
        return;
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    navigator_.setup(5, 2, charaCount_);
    if (result != 0) {
        if (menuItem_.getActive() == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
            TownMenuPlayerControl::getSingleton()->setActiveFukuro();
        } else {
            TownMenuPlayerControl::getSingleton()->resetActiveFukuro();
        }
        TownMenuPlayerControl::getSingleton()->menu::MenuPlayerControl::setActiveChara(menuItem_.active_);
        if (result == 3) {
            close();
            if (fromMateriel_ == 1) {
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            } else {
                gTownMenu_ROOT.open();
                gTownMenu_ROOT.menuItem_.active_ = TownMenu_ROOT::ROOT_ITEM;
            }
        }
        if (result == 2) {
            if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
                int count = MenuStatusInfo::getFukuroItemCount();
                if (count > 0) {
                    int item;
                    int page;
                    if (fromMateriel_ == 1) {
                        item = status::g_Menu.meisanSackActive_;
                        page = status::g_Menu.meisanSackActivePage_;
                    } else {
                        item = status::g_Menu.sackActive_;
                        page = status::g_Menu.sackActivePage_;
                    }
                    if (count <= item + page * 6) {
                        item = count % 6 - 1;
                        page = count / 6;
                        if (item < 0) {
                            item = 5;
                            page--;
                        }
                    }
                    TownMenuPlayerControl::getSingleton()->setActiveItem(item);
                    TownMenuPlayerControl::getSingleton()->setActiveItemPage(page);
                    close();
                    gTownMenuItemSelectChara.meisanhinFlag_ = fromMateriel_;
                    gTownMenuItemSelectChara.open();
                } else {
                    gTownMenu_MESSAGE.openMessageForMENU();
                    gTownMenu_MESSAGE.addMessage(0xc4249);
                }
            } else if (MenuStatusInfo::getPlayerItemCount(menuItem_.active_) > 0) {
                unkfunc_02178480();
                close();
                gTownMenuItemSelectChara.meisanhinFlag_ = fromMateriel_;
                gTownMenuItemSelectChara.open();
            } else {
                gTownMenu_MESSAGE.openMessageForMENU();
                TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(menuItem_.active_));
                gTownMenu_MESSAGE.addMessage(0xc40da);
            }
        }
        redraw_ = 1;
    }
}

THUMB void UnkTownMenuItemCharaSelect::unkfunc_02178480()
{
    int count = MenuStatusInfo::getPlayerItemCount(menuItem_.active_);
    int equipCount = 0;
    int page = 0;
    for (int i = 0; i < count; i++) {
        if (MenuStatusInfo::isPlayerEquipItemIndex(menuItem_.active_, i) == true) {
            equipCount++;
        }
    }
    if (equipCount == count) {
        equipCount = 0;
    }
    if (equipCount >= 6) {
        page = 1;
    }
    int item = equipCount - page * 6;
    item = dss::clamp<int>(0, item, 5);
    TownMenuPlayerControl::getSingleton()->setActiveItem(item);
    TownMenuPlayerControl::getSingleton()->setActiveItemPage(page);
}
