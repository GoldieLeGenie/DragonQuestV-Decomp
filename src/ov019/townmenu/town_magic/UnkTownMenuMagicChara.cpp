#pragma ipa file
#include "ov019/townmenu/town_magic/UnkTownMenuMagicChara.hpp"
#include "ov019/townmenu/town_magic/TownMenu_MAGIC_ROOT.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline void TownMenuPlayerControl::setActiveChara(unsigned char chara)
{
    activeChara_ = chara;
}

inline void status::MenuStatus::setActorIndex(short actor)
{
    actorIndex_ = actor;
}

THUMB void UnkTownMenuMagicChara::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = TownMenuPlayerControl::getSingleton()->activeChara_;
    navigator_.setupBase();
}

THUMB void UnkTownMenuMagicChara::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    int active = menuItem_.active_;
    if (count < 6) {
        unkfunc_02171514(&menuItem_, count, active);
    } else {
        unkfunc_021714f8(&menuItem_, count, active);
    }
}

THUMB void UnkTownMenuMagicChara::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    unkfunc_021733b0(open);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void UnkTownMenuMagicChara::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (gTownMenu_MESSAGE.isOpen()) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    navigator_.setup(5, 2, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        if (result == 3) {
            close();
            gTownMenu_ROOT.open();
            gTownMenu_ROOT.menuItem_.active_ = TownMenu_ROOT::ROOT_MAGIC;
            return;
        }
        int active = menuItem_.active_;
        TownMenuPlayerControl::getSingleton()->setActiveChara(active);
        if (result == 2) {
            int playerIndex = MenuStatusInfo::getPlayerIndex(active);
            TextAPI::setMACRO0(1, 0x50000000, playerIndex);
            if (MenuStatusInfo::getPlayerActionCount(active, MenuStatusInfo::USE_TOWN) == 0) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xc40bd);
            } else if (MenuStatusInfo::isPlayerCondition(active, MenuStatusInfo::CONDITION_DEATH) == true) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xc40bf);
            } else {
                close();
                gTownMenu_MAGIC_ROOT.open();
                status::g_Menu.setActorIndex(playerIndex);
            }
            TextAPI::setMACRO0(1, 0x50000000, MenuStatusInfo::getPlayerIndex(active));
        }
        redraw_ = 1;
    }
}
