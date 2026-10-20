#pragma ipa file
#include "ov019/townmenu/town_status/TownMenu_STATUS.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/TownMenu_ROOT.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/UnkMenuTemplate.hpp"

using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline void menu::MenuItem::setSEenable(bool flag)
{
    enableSE_ = flag;
}

inline void TownMenuPlayerControl::setActiveChara(unsigned char chara)
{
    activeChara_ = chara;
}

THUMB void TownMenu_STATUS::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    mode_ = 0;
    navigator_.setupBase();
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1);
    updateSelectSound();
}

THUMB void TownMenu_STATUS::menuExecute()
{
    setupCharaRowLayout5x1(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void TownMenu_STATUS::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int page = navigator_.getPageNo();
    switch (mode_) {
        case 0:
            drawStatusMainPage(page);
            break;
        case 1:
            drawStatusSpellPage(page);
            break;
        case 2:
            drawStatusMoneyScreen(page);
            break;
        case 3:
            drawStatusPartySummaryScreen(-2, 1, page);
            break;
        case 4:
            drawStatusPartySummaryScreen(-2, 0, page);
            break;
    }
    menuItem_.drawActive();
}

THUMB void TownMenu_STATUS::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int fukuro = 0;
    int index = navigator_.getIndex(menuItem_.active_);
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    if (activeChara == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        fukuro = 1;
    }
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        if (result == 3) {
            mode_--;
            if (fukuro == 1 && mode_ >= 2) {
                redraw_ = 1;
                return;
            }
            if (fukuro == 0 && mode_ >= 0) {
                redraw_ = 1;
                return;
            }
            close();
            gTownMenu_ROOT.open();
            gTownMenu_ROOT.menuItem_.active_ = TownMenu_ROOT::ROOT_STATUS;
            return;
        }
        if (result == 2) {
            if (fukuro == 1) {
                mode_++;
                if (mode_ > 4) {
                    mode_ = 2;
                }
            } else if (MenuStatusInfo::isPlayerActionEnable(TownMenuPlayerControl::getSingleton()->activeChara_) == true) {
                mode_++;
                if (mode_ > 1) {
                    mode_ = 0;
                }
            }
        }
        TownMenuPlayerControl::getSingleton()->setActiveChara(navigator_.getIndex(menuItem_.active_));
        if (index != TownMenuPlayerControl::getSingleton()->activeChara_) {
            activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
            if (activeChara == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
                mode_ = 2;
            } else {
                mode_ = 0;
            }
        }
        updateSelectSound();
        redraw_ = 1;
    }
}

THUMB void TownMenu_STATUS::updateSelectSound()
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    bool enable = false;
    if (activeChara == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        enable = true;
    } else if (MenuStatusInfo::isPlayerActionEnable(activeChara) == true) {
        enable = true;
    }
    menuItem_.setSEenable(enable);
}

THUMB int getRootMenuKind(int index)
{
    int table[6] = {8, 2, 3, 0, 4, 1};
    return table[index];
}

THUMB int getRootMenuName(int index)
{
    int table[6] = {(int)0xe0000064, (int)0xe0000065, (int)0xe0000066, (int)0xe0000067, (int)0xe0000068, (int)0xe0000069};
    return table[index];
}
