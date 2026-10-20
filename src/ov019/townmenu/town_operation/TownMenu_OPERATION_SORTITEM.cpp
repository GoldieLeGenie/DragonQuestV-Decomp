#pragma ipa file
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_SORTITEM.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_ROOT.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/OptionStatus.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline void TownMenuPlayerControl::setActiveChara(unsigned char chara)
{
    activeChara_ = chara;
}

THUMB void TownMenu_OPERATION_SORTITEM::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    m_selectPlayerCount = 0;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < 8; i++) {
        m_selectPlayer[i] = -1;
    }
    for (short i = 0; i < count; i++) {
        if (!MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_BATTLE_NPC)) {
            m_selectPlayer[m_selectPlayerCount] = i;
            m_selectPlayerCount++;
        }
    }
    m_selectPlayer[m_selectPlayerCount] = count;
    m_selectPlayerCount++;
    TownMenuPlayerControl::getSingleton()->setActiveChara(m_selectPlayer[0]);
}

THUMB void TownMenu_OPERATION_SORTITEM::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int active = menuItem_.active_;
    if (m_mode == SORT_SACK) {
        townMenuTacticsBoxUp(&menuItem_, active);
    } else if (m_selectPlayerCount - 1 < 5) {
        townMenuItemSelectHalfChara(&menuItem_, m_selectPlayerCount, active);
    } else {
        townMenuTacticsSelectChara(&menuItem_, m_selectPlayerCount, active, -1, -1);
    }
}

THUMB void TownMenu_OPERATION_SORTITEM::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int open = gTownMenu_MESSAGE.isOpen();
    drawSortItemScreen(open, m_mode);
    if (!open) {
        menuItem_.drawActive();
    }
}

THUMB void TownMenu_OPERATION_SORTITEM::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (stat == MENUBASE_STAT_OK) {
                if (m_mode == SORT_END) {
                    close();
                    gTownMenu_OPERATION_ROOT.open();
                }
                if (m_mode == SORT_SACK) {
                    boxUpSack();
                }
                if (m_mode == SORT_ITEM) {
                    boxUpItem();
                }
            }
        }
        return;
    }
    if (m_mode == SORT_SACK) {
        navigator_.setup(2, 1, 2);
        int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
        if (result != 0) {
            if (result == 3) {
                close();
                gTownMenu_OPERATION_ROOT.open();
                return;
            }
            if (result == 2) {
                gTownMenu_MESSAGE.openMessageForMENU();
                if (MenuStatusInfo::getFukuroItemCount() == 0) {
                    gTownMenu_MESSAGE.addMessage(0xc4249);
                } else {
                    if (menuItem_.active_ == 0) {
                        g_Option.setSackSort(0);
                        gTownMenu_MESSAGE.addMessage(0xc4241);
                    } else {
                        g_Option.setSackSort(1);
                        gTownMenu_MESSAGE.addMessage(0xc4246);
                    }
                    gTownMenu_MESSAGE.setYesNo();
                }
            }
            TownMenuPlayerControl::getSingleton()->setActiveChara(menuItem_.active_);
            redraw_ = 1;
        }
    }
    if (m_mode == SORT_ITEM) {
        navigator_.setup(5, 2, m_selectPlayerCount);
        int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
        if (result != 0) {
            if (result == 3) {
                close();
                gTownMenu_OPERATION_ROOT.open();
                return;
            }
            if (result == 2) {
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xc423c);
                gTownMenu_MESSAGE.setYesNo();
            }
            TownMenuPlayerControl::getSingleton()->setActiveChara(m_selectPlayer[menuItem_.active_]);
            redraw_ = 1;
        }
    }
}

THUMB void TownMenu_OPERATION_SORTITEM::boxUpSack()
{
    if (MenuStatusInfo::getFukuroItemCount() != 0) {
        MenuStatusInfo::sortFukuroItem();
        gTownMenu_MESSAGE.openMessageForMENU();
        gTownMenu_MESSAGE.addMessage(0xc4244);
        status::g_Menu.sackActive_ = 0;
        status::g_Menu.sackActivePage_ = 0;
        m_mode = SORT_END;
    }
}

THUMB void TownMenu_OPERATION_SORTITEM::boxUpItem()
{
    int last = m_selectPlayerCount - 1;
    if (last == menuItem_.active_) {
        for (int i = 0; i < last; i++) {
            MenuStatusInfo::sortPlayerItem(m_selectPlayer[i]);
        }
    } else {
        MenuStatusInfo::sortPlayerItem(m_selectPlayer[menuItem_.active_]);
    }
    gTownMenu_MESSAGE.openMessageForMENU();
    gTownMenu_MESSAGE.addMessage(0xc423f);
    status::g_Menu.sackActive_ = 0;
    status::g_Menu.sackActivePage_ = 0;
    m_mode = SORT_END;
}
