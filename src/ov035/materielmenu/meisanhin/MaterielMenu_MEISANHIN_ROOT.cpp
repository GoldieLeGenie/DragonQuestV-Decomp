#include "ov035/materielmenu/meisanhin/MaterielMenu_MEISANHIN_ROOT.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/town_item/UnkTownMenuItemCharaSelect.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline int twn::TownPlayerManager::getSearchMapUid()
{
    return searchMapUid_;
}

inline status::MuseumItemStatus& status::MuseumStatus::getMuseumItemStatus(int index)
{
    return museumitem_[index];
}

inline unsigned short status::MuseumItemStatus::getIconID()
{
    return iconid_;
}

THUMB void MaterielMenu_MEISANHIN_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(1, 1, 1);
    dq5::DAY_NIGHT timeZone = status::g_StageInfo.getDayNight();
    int uid = twn::TownPlayerManager::getSingleton().getSearchMapUid();
    daizaNo_ = status::g_MuseumStatus.findMuseumItemStatus(uid);
    meisanItem_ = status::g_MuseumStatus.getMuseumItemStatus(daizaNo_).getIconID();
    waitCount_ = -1;
    if (meisanItem_ != 0) {
        if (timeZone == dq5::DAY_NIGHT_DAY) {
            mode_ = MODE_DAY_TIME;
        }
        else {
            mode_ = MODE_NIGHT_TIME;
        }
        if (meisanItem_ == 0xdf || meisanItem_ == 0xe0) {
            SoundManager::interrupt_ = 1;
            SoundManager::play(0x1e, 5);
            if (mode_ == MODE_DAY_TIME) {
                waitCount_ = 0;
            }
        }
    }
    else {
        gTownMenu_MESSAGE.openMessageForMENU();
        if (timeZone == dq5::DAY_NIGHT_DAY) {
            gTownMenu_MESSAGE.addMessage(0xc54bd);
            mode_ = MODE_END;
        }
        else {
            gTownMenu_MESSAGE.addMessage(0xc5493);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_SET_ITEM;
        }
    }
}

THUMB void MaterielMenu_MEISANHIN_ROOT::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_PICTUREBOOK_MONSTERANIME(&menuItem_);
}

THUMB void MaterielMenu_MEISANHIN_ROOT::menuDraw()
{
    if (!gTownMenu_MESSAGE.isOpen()) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217b360(daizaNo_);
    }
}

THUMB void MaterielMenu_MEISANHIN_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (waitCount_ > -1) {
        if (waitCount_ < 15) {
            waitCount_++;
        }
        else {
            waitCount_ = -1;
        }
        return;
    }
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            selectYes();
            return;
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            selectNo();
        }
        return;
    }
    navigator_.setup(1, 1, 1);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        if (mode_ == MODE_DAY_TIME) {
            if (meisanItem_ == 0xdf || meisanItem_ == 0xe0) {
                SoundManager::townPlay(twn::TownSystem::getFloorBgmIndex());
            }
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            return;
        }
        if (mode_ == MODE_NIGHT_TIME) {
            TextAPI::setMACRO0(10, 0x40000000, meisanItem_);
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xc54b6);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_CLEARANCE;
        }
    }
}

THUMB void MaterielMenu_MEISANHIN_ROOT::selectYes()
{
    switch (mode_) {
        case MODE_SET_ITEM:
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xc5499);
            mode_ = MODE_NEXT_MENU;
            break;
        case MODE_CHANGE_ITEM:
            gTownMenu_MESSAGE.openMessageForMENU();
            gTownMenu_MESSAGE.addMessage(0xc549c);
            mode_ = MODE_NEXT_MENU;
            break;
        case MODE_CLEARANCE: {
            int uid = twn::TownPlayerManager::getSingleton().getSearchMapUid();
            int no = status::g_MuseumStatus.findMuseumItemStatus(uid);
            status::MuseumItemStatus& item = status::g_MuseumStatus.getMuseumItemStatus(no);
            MenuStatusInfo::addFukuroItem(meisanItem_, 1);
            item.setIconIDandRedraw(0);
            gTownMenu_MESSAGE.openMessageForMENU();
            TextAPI::setMACRO0(10, 0x40000000, meisanItem_);
            gTownMenu_MESSAGE.addMessage(0xc54b8);
            if (meisanItem_ == 0xdf || meisanItem_ == 0xe0) {
                SoundManager::townPlay(twn::TownSystem::getFloorBgmIndex());
            }
            mode_ = MODE_END;
            break;
        }
        case MODE_NEXT_MENU:
            close();
            menu::TownMenuPlayerControl::getSingleton()->initialize();
            data_ov019_02183524.fromMateriel_ = 1;
            data_ov019_02183524.open();
            break;
        case MODE_END:
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}

THUMB void MaterielMenu_MEISANHIN_ROOT::selectNo()
{
    switch (mode_) {
        case MODE_CHANGE_ITEM:
            gTownMenu_MESSAGE.openMessageForMENU();
            TextAPI::setMACRO0(10, 0x40000000, meisanItem_);
            gTownMenu_MESSAGE.addMessage(0xc54b6);
            gTownMenu_MESSAGE.setYesNo();
            mode_ = MODE_CLEARANCE;
            break;
        case MODE_SET_ITEM:
        case MODE_CLEARANCE:
        case MODE_NEXT_MENU:
        case MODE_END:
            if (meisanItem_ == 0xdf || meisanItem_ == 0xe0) {
                SoundManager::townPlay(twn::TownSystem::getFloorBgmIndex());
            }
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
    }
}
