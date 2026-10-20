#pragma ipa file
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_SETTING.hpp"
#include "ov019/townmenu/town_operation/TownMenu_OPERATION_ROOT.hpp"
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/MenuUpdateAssist.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/status/OptionStatus.hpp"

using menu::MenuStatusInfo;

static UnkMenuParts s_parts[] = {
    { 0x15, 0xb5, 0, 0, 0, 0x20, 0, 0 },
    { 0x15, 0xb5, 0, 0, 0, 0x3c, 0, 0 },
    { 0x15, 0xb5, 0, 0, 0, 0x4e, 0, 0 },
    { 0x15, 0xb4, 0, 0, 0, 0, 0, 0 },
    { 0xff, 0, 0, 0, 0, 0, 0, 0 },
};

inline void menu::MenuItem::setSEenable(bool flag)
{
    enableSE_ = flag;
}

THUMB void TownMenu_OPERATION_SETTING::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    bgmItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    seItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
    battleItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    navigator_.setupBase();
    bgmItem_.setSEenable(false);
    seItem_.setSEenable(false);
    battleItem_.setSEenable(false);
    mode_ = 0;
    prevMode_ = 0;
    loadOptionValues();
}

THUMB void TownMenu_OPERATION_SETTING::menuExecute()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    townMenuBgmVolume(&bgmItem_, bgmItem_.active_);
    townMenuEffectVolume(&seItem_, seItem_.active_);
    townMenuBattleSpeed(&battleItem_, battleItem_.active_);
}

THUMB void TownMenu_OPERATION_SETTING::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    drawSettingScreen();
    drawSettingCursors();
    bgmItem_.drawActive();
    seItem_.drawActive();
    battleItem_.drawActive();
}

THUMB void TownMenu_OPERATION_SETTING::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    navigator_.setup(1, 1, 1);
    if (!updateSettingItem(&battleItem_, 0)) {
        return;
    }
    if (!updateSettingItem(&bgmItem_, 1)) {
        return;
    }
    if (!updateSettingItem(&seItem_, 2)) {
        return;
    }
    if (mode_ != prevMode_) {
        switch (mode_) {
            case 1:
                bgmItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
                seItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
                battleItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
                break;
            case 2:
                bgmItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
                seItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
                battleItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
                break;
            case 0:
                bgmItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
                seItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH, menu::MenuItem::CURSORTYPE_NONE);
                battleItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
                break;
        }
        bgmItem_.setSEenable(false);
        seItem_.setSEenable(false);
        battleItem_.setSEenable(false);
        loadOptionValues();
        prevMode_ = mode_;
    }
}

THUMB void TownMenu_OPERATION_SETTING::loadOptionValues()
{
    bgmItem_.active_ = g_Option.getBgmVolume();
    seItem_.active_ = g_Option.getSeVolume();
    battleItem_.active_ = g_Option.getBattleSpeed();
}

THUMB bool TownMenu_OPERATION_SETTING::updateSettingItem(menu::MenuItem* menuItem, int mode)
{
    int result = MenuUpdate_Assist::menuSelect(*menuItem, navigator_);
    if (result != 0) {
        if (result == 1) {
            if (mode == 1) {
                mode_ = 1;
                g_Option.setBgmVolume(menuItem->active_);
            }
            if (mode == 2) {
                mode_ = 2;
                g_Option.setSeVolume(menuItem->active_);
            }
            if (mode == 0) {
                mode_ = 0;
                g_Option.setBattleSpeed(menuItem->active_);
            }
            redraw_ = 1;
        }
        if (result == 4) {
            if (mode == 1) {
                mode_ = 0;
            }
            if (mode == 2) {
                mode_ = 1;
            }
            if (mode == 0) {
                mode_ = 2;
            }
        }
        if (result == 5) {
            if (mode == 1) {
                mode_ = 2;
            }
            if (mode == 2) {
                mode_ = 0;
            }
            if (mode == 0) {
                mode_ = 1;
            }
        }
        if (result == 7) {
            menuItem->active_ = 4;
        }
        if (result == 6) {
            menuItem->active_ = 0;
        }
        if (result == 3) {
            close();
            gTownMenu_OPERATION_ROOT.open();
            return false;
        }
    }
    return true;
}

THUMB void TownMenu_OPERATION_SETTING::drawSettingCursors()
{
    s_parts[0].x_ = battleItem_.active_ * 0x18 + 0x6e;
    s_parts[1].x_ = bgmItem_.active_ * 0x18 + 0x6e;
    s_parts[2].x_ = seItem_.active_ * 0x18 + 0x6e;
    s_parts[3].x_ = 0xc;
    switch (mode_) {
        case 0:
            s_parts[3].y_ = 0x20;
            break;
        case 1:
            s_parts[3].y_ = 0x3c;
            break;
        case 2:
            s_parts[3].y_ = 0x4e;
            break;
    }
    drawMenuPartsAt(s_parts, 0, 0, 0);
}
