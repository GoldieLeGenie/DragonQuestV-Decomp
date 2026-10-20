#include "ov035/materielmenu/meisanhin/MaterielMenu_MIMI_ROOT.hpp"
#include "ov035/materielmenu/meisanhin/MaterielMenu_MIMI_DETAIL.hpp"
#include "ov019/commonmenu/UnkMenuDrawText.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "ov019/materielmenu/meisanhin/MaterielMenuMeisanhinUtil.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/leveldata/MeisanhinData.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/status/GameFlag.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

inline void menu::MaterielMenuPlayerControl::setActiveItemPage(int active)
{
    activeItemPage_ = active;
}

inline dq5::level::MeisanhinData* dq5::level::MeisanhinData::getRecord(int index)
{
    return (MeisanhinData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

THUMB void MaterielMenu_MIMI_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    navigator_.setupBase();
    navigator_.setup(2, 8, 28);
    navigator_.setPageNo(menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_);
}

THUMB void MaterielMenu_MIMI_ROOT::menuExecute()
{
    int max = 28 - navigator_.getPageNo() * 16;
    menu::MenuTemplate_materiel::MATERIEL_PICTUREBOOK_SELECT(&menuItem_, menuItem_.active_, dss::clamp(1, max, 28));
}

THUMB void MaterielMenu_MIMI_ROOT::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        drawMeisanhinList(mode_);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_MIMI_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    navigator_.setup(2, 8, 28);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(navigator_.getIndex(menuItem_.active_));
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(navigator_.getPageNo());
        if (result == 2) {
            if (mode_ == MODE_HINT) {
                openMimiMessage();
            }
            else {
                close();
                gMaterielMenu_MIMI_DETAIL.open();
            }
        }
        if (result == 3) {
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
        }
        redraw_ = 1;
    }
}

THUMB bool MaterielMenu_MIMI_ROOT::checkHaveMeisan(int active)
{
    int flagNo = 0;
    switch (active) {
        case 0:
            flagNo = getMeisanhinFlagNo(0xdb);
            break;
        case 1:
            flagNo = getMeisanhinFlagNo(0xde);
            break;
        case 2:
            flagNo = getMeisanhinFlagNo(0xe1);
            break;
        case 3:
            flagNo = getMeisanhinFlagNo(0xd7);
            break;
        case 4:
            flagNo = getMeisanhinFlagNo(0xe4);
            break;
        case 5:
            flagNo = getMeisanhinFlagNo(0xe5);
            break;
        case 6:
            flagNo = getMeisanhinFlagNo(0xdf);
            break;
        case 7:
            flagNo = getMeisanhinFlagNo(0xe2);
            break;
        case 8:
            flagNo = getMeisanhinFlagNo(0xf4);
            break;
        case 9:
            flagNo = getMeisanhinFlagNo(0xe6);
            break;
        case 10:
            flagNo = getMeisanhinFlagNo(0xe3);
            break;
        case 11:
            flagNo = getMeisanhinFlagNo(0xea);
            break;
        case 12:
            flagNo = getMeisanhinFlagNo(0xe9);
            break;
        case 13:
            flagNo = getMeisanhinFlagNo(0xeb);
            break;
        case 14:
            flagNo = getMeisanhinFlagNo(0xec);
            break;
        case 15:
            flagNo = getMeisanhinFlagNo(0xf5);
            break;
        case 16:
            flagNo = getMeisanhinFlagNo(0xed);
            break;
        case 17:
            flagNo = getMeisanhinFlagNo(0xee);
            break;
        case 18:
            flagNo = getMeisanhinFlagNo(0xf8);
            break;
        case 19:
            flagNo = getMeisanhinFlagNo(0xf6);
            break;
        case 20:
            flagNo = getMeisanhinFlagNo(0xef);
            break;
        case 21:
            flagNo = getMeisanhinFlagNo(0xd6);
            break;
        case 22:
            flagNo = getMeisanhinFlagNo(0xdd);
            break;
        case 23:
            flagNo = getMeisanhinFlagNo(0xf2);
            break;
        case 24:
            flagNo = getMeisanhinFlagNo(0xf0);
            break;
        case 25:
            flagNo = getMeisanhinFlagNo(0xf3);
            break;
        case 26:
            flagNo = getMeisanhinFlagNo(0xf7);
            break;
        case 27:
            flagNo = getMeisanhinFlagNo(0xfa);
            break;
    }
    return g_AreaFlag.check(flagNo);
}

THUMB void MaterielMenu_MIMI_ROOT::openMimiMessage()
{
    int active = navigator_.getIndex(menuItem_.active_);
    int record = getMeisanhinRecordIndex(active);
    int message;
    if (checkHaveMeisan(active) == true) {
        message = dq5::level::MeisanhinData::getRecord(record)->message4;
    }
    else {
        message = dq5::level::MeisanhinData::getRecord(record)->message3;
    }
    gTownMenu_MESSAGE.openMessageForTALK();
    MenuAPI::addMessageSerial(message);
    gTownMenu_MESSAGE.addMessage(0x3663);
}
