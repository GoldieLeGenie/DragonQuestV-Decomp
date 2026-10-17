#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ROOT.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ADD_MONSTER.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_CHANGE_NAME.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_CHECK_NAME.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_DEL_MONSTER.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_LEAVE_MESSAGE.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_LEAVE_MONSTER.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_STATUS.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov032/leveldata/JisanMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PlayerData.hpp"

using menu::MenuStatusInfo;

inline dq5::level::JisanMessage* dq5::level::JisanMessage::getRecord(int index)
{
    return (JisanMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::JisanMessage::getMessage1()
{
    return message1;
}

THUMB void MaterielMenu_JISAN_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    status::g_Menu.drawFlag_ = 0;
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = active_;
    navigator_.setupBase();
    changeMenu_ = 0;
    mode_ = MODE_START;
    if (status::g_Menu.returnMenuType_ == 1) {
        close();
        gMaterielMenu_JISAN_ADD_MONSTER.open();
        return;
    }
    if (status::g_Menu.returnMenuType_ == 2) {
        close();
        gMaterielMenu_JISAN_LEAVE_MESSAGE.open();
        return;
    }
    if (status::g_Menu.returnMenuType_ == 3) {
        close();
        gMaterielMenu_JISAN_CHECK_NAME.open();
    }
}

THUMB void MaterielMenu_JISAN_ROOT::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_CHURCH_ROOT(&menuItem_, 6, menuItem_.active_);
}

THUMB void MaterielMenu_JISAN_ROOT::menuDraw()
{
    if (gTownMenu_MESSAGE.isMessageWAITPROG() == true) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217c378();
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_JISAN_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
            if (mode_ == MODE_START) {
                mode_ = MODE_SELECT;
                redraw_ = 1;
                return;
            }
            if (mode_ == MODE_SELECT) {
                navigator_.setup(2, 3, 6);
                int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
                if (result != 0) {
                    if (result == 3) {
                        gTownMenu_MESSAGE.close();
                        selectNextMenu(false);
                        menuItem_.active_ = 5;
                    }
                    if (result == 2) {
                        gTownMenu_MESSAGE.close();
                        switch (menuItem_.active_) {
                            case 0:
                                selectAzuke();
                                break;
                            case 1:
                                selectMukae();
                                break;
                            case 2:
                                selectYousu();
                                break;
                            case 3:
                                selectWakare();
                                break;
                            case 4:
                                selectNextMenu(true);
                                break;
                            case 5:
                                selectNextMenu(false);
                                break;
                        }
                    }
                    redraw_ = 1;
                }
            }
        }
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == MODE_START) {
                openWaitMessage(1, 0x48, 0, 0);
                return;
            }
            if (menuItem_.active_ == 5) {
                status::g_Menu.bookingFlag_ = 0;
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                return;
            }
            if (changeMenu_ == 1) {
                menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = 0;
                menu::MaterielMenuPlayerControl::getSingleton()->activeItemPage_ = 0;
                close();
                switch (menuItem_.active_) {
                    case 0:
                        gMaterielMenu_JISAN_LEAVE_MONSTER.open();
                        return;
                    case 1:
                        gMaterielMenu_JISAN_ADD_MONSTER.open();
                        return;
                    case 2:
                        gMaterielMenu_JISAN_STATUS.open();
                        return;
                    case 3:
                        gMaterielMenu_JISAN_DEL_MONSTER.open();
                        return;
                    case 4:
                        gMaterielMenu_JISAN_CHANGE_NAME.open();
                        return;
                }
            }
        }
        return;
    }
    if (mode_ == MODE_START) {
        openWaitMessage(2, 1, 2, 0);
    }
}

THUMB int MaterielMenu_JISAN_ROOT::getMes(int index)
{
    return dq5::level::JisanMessage::getRecord(index)->getMessage1();
}

THUMB void MaterielMenu_JISAN_ROOT::openWaitMessage(int count, int mes1, int mes2, int mes3)
{
    int mes[3];
    mes[0] = getMes(mes1);
    mes[1] = getMes(mes2);
    mes[2] = getMes(mes3);
    gTownMenu_MESSAGE.openMessageForTALK();
    for (int i = 0; i < count - 1; i++) {
        gTownMenu_MESSAGE.addMessage(mes[i]);
    }
    gTownMenu_MESSAGE.addMessageNOWAIT(mes[count - 1]);
    gTownMenu_MESSAGE.addMessageWAITKEY();
}

THUMB void MaterielMenu_JISAN_ROOT::selectAzuke()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (status::PlayerDataAll::getMonsterCountInOldMan() >= 80) {
        mode_ = MODE_START;
        gTownMenu_MESSAGE.addMessage(getMes(3), getMes(4));
        return;
    }
    if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) == 1) {
        mode_ = MODE_START;
        gTownMenu_MESSAGE.addMessage(getMes(5));
        return;
    }
    gTownMenu_MESSAGE.addMessage(getMes(6));
    changeMenu_ = 1;
}

THUMB void MaterielMenu_JISAN_ROOT::selectMukae()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) >= 8) {
        mode_ = MODE_START;
        gTownMenu_MESSAGE.addMessage(getMes(0x13), getMes(0x14));
    }
    else if (status::PlayerDataAll::getMonsterCountInOldMan() == 0) {
        mode_ = MODE_START;
        gTownMenu_MESSAGE.addMessage(getMes(0x15));
    }
    else {
        gTownMenu_MESSAGE.addMessage(getMes(0x16));
        changeMenu_ = 1;
    }
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
}

THUMB void MaterielMenu_JISAN_ROOT::selectYousu()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (status::PlayerDataAll::getMonsterCountInOldMan() == 0) {
        mode_ = MODE_START;
        gTownMenu_MESSAGE.addMessage(getMes(0x1b));
        return;
    }
    gTownMenu_MESSAGE.addMessage(getMes(0x1c), getMes(0x1d));
    changeMenu_ = 1;
}

THUMB void MaterielMenu_JISAN_ROOT::selectWakare()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (status::PlayerDataAll::getMonsterCountInOldMan() == 0) {
        mode_ = MODE_START;
        gTownMenu_MESSAGE.addMessage(getMes(0x1f), getMes(0x20));
        return;
    }
    gTownMenu_MESSAGE.addMessage(getMes(0x21), getMes(0x22), getMes(0x23));
    changeMenu_ = 1;
}

THUMB void MaterielMenu_JISAN_ROOT::selectNextMenu(bool next)
{
    gTownMenu_MESSAGE.openMessageForTALK();
    if (next == true) {
        gTownMenu_MESSAGE.addMessage(getMes(0x2c));
        changeMenu_ = 1;
        return;
    }
    gTownMenu_MESSAGE.addMessage(getMes(0x49));
}
