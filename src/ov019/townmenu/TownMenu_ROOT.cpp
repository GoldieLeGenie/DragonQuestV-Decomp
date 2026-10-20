#pragma ipa file
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/TownMenu_PARTY_TALK.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov019/townmenu/town_magic/UnkTownMenuMagicChara.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_ROOT.hpp"
#include "ov019/townmenu/town_status/TownMenu_STATUS.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

THUMB void TownMenu_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = ROOT_TALK;
    TownMenuPlayerControl::getSingleton()->initialize();
    status::g_Menu.bookingFlag_ = 0;
}

THUMB void TownMenu_ROOT::menuExecute()
{
    unkfunc_021713c4(&menuItem_, menuItem_.active_);
}

THUMB void TownMenu_ROOT::menuDraw()
{
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_02172ef0(open);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenu_ROOT::menuUpdate()
{
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (menuItem_.active_ == ROOT_SEARCH) {
                close();
                stat_ = MENUBASE_STAT_OK;
            }
        }
        return;
    }
    navigator_.setup(2, 3, 6);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        redraw_ = 1;
        if (result == 2) {
            unkfunc_02174c3c();
        }
        if (result == 3) {
            close();
            stat_ = MENUBASE_STAT_OK;
        }
    }
}

THUMB void TownMenu_ROOT::unkfunc_02174c3c()
{
    switch (menuItem_.active_) {
        case ROOT_TALK:
            if (data_02101c88.isCurrentPart(4) == 1 && twn::TownPlayerManager::getSingleton().checkTalkToCharacter() == true) {
                stat_ = MENUBASE_STAT_CANCEL;
                redraw_ = 1;
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_TALK);
                return;
            }
            close();
            gTownMenu_PARTY_TALK.open();
            break;
        case ROOT_MAGIC:
            unkfunc_02174d34();
            break;
        case ROOT_ITEM:
            close();
            data_ov019_02183524.fromMateriel_ = 0;
            data_ov019_02183524.open();
            break;
        case ROOT_SEARCH: {
            int alive = 0;
            int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
            for (int i = 0; i < count; i++) {
                if (!MenuStatusInfo::isPlayerCondition(i, MenuStatusInfo::CONDITION_DEATH)) {
                    alive = 1;
                }
            }
            if (alive == 1) {
                stat_ = MENUBASE_STAT_CANCEL;
                redraw_ = 1;
                cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_SEARCH);
            } else {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xc44a2, 0xc44b1);
            }
            break;
        }
        case ROOT_STATUS:
            close();
            gTownMenu_STATUS.open();
            break;
        case ROOT_OPERATION:
            close();
            gTownMenu_OPERATION_ROOT.open();
            break;
    }
}

THUMB void TownMenu_ROOT::unkfunc_02174d34()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int playerIndex = 0;
    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
        if (MenuStatusInfo::getPlayerActionCount(i, MenuStatusInfo::USE_TOWN) > 0) {
            close();
            data_ov019_021830a8.open();
            return;
        }
        if (playerIndex == 0) {
            playerIndex = MenuStatusInfo::getPlayerIndex(i);
        }
    }
    gTownMenu_MESSAGE.openMessageForMENU();
    TextAPI::setMACRO0(1, 0x50000000, playerIndex);
    gTownMenu_MESSAGE.addMessage(0xc40bd);
}
