#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_ROOT.hpp"
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_ADD_PLAYER.hpp"
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_LEAVE_MESSAGE.hpp"
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_LEAVE_PLAYER.hpp"
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_STATUS.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov033/leveldata/LuidaMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline dq5::level::LuidaMessage* dq5::level::LuidaMessage::getRecord(int index)
{
    return (LuidaMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::LuidaMessage::getMessage1()
{
    return message1;
}

THUMB void MaterielMenu_LUIDA_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    status::g_Menu.drawFlag_ = 0;
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = active_;
    navigator_.setupBase();
    mode_ = MODE_START;
    unk_1c = 0;
    if (status::g_Menu.returnMenuType_ == 4) {
        close();
        gMaterielMenu_LUIDA_ADD_PLAYER.open();
        return;
    }
    if (status::g_Menu.returnMenuType_ == 5) {
        close();
        gMaterielMenu_LUIDA_LEAVE_MESSAGE.open();
    }
}

THUMB void MaterielMenu_LUIDA_ROOT::menuExecute()
{
    menu::MenuTemplate_materiel::unkfunc_0217d7e4(&menuItem_, menuItem_.active_);
}

THUMB void MaterielMenu_LUIDA_ROOT::menuDraw()
{
    if (gTownMenu_MESSAGE.isMessageWAITPROG() == true) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217bdec();
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_LUIDA_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        if (gTownMenu_MESSAGE.isMessageWAITPROG()) {
            if (mode_ == MODE_START || mode_ == MODE_OPEN_DRAW) {
                mode_ = MODE_SELECT;
                redraw_ = 1;
                return;
            }
            if (mode_ == MODE_SELECT) {
                navigator_.setup(1, 4, 4);
                int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
                if (result != 0) {
                    if (result == 3) {
                        selectYameru();
                    }
                    if (result == 2) {
                        switch (menuItem_.active_) {
                            case 0:
                                selectKuwaeru();
                                break;
                            case 1:
                                selectAzuke();
                                break;
                            case 2:
                                selectList();
                                break;
                            case 3:
                                selectYameru();
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
            if (menuItem_.active_ == 3) {
                status::g_Menu.bookingFlag_ = 0;
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                return;
            }
            if (mode_ == MODE_CHANGE_MENU) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(28));
                gTownMenu_MESSAGE.addMessageWAITKEY();
                mode_ = MODE_OPEN_DRAW;
                return;
            }
            if (unk_1c == 1) {
                close();
                switch (menuItem_.active_) {
                    case 0:
                        gMaterielMenu_LUIDA_ADD_PLAYER.open();
                        return;
                    case 1:
                        gMaterielMenu_LUIDA_LEAVE_PLAYER.open();
                        return;
                    case 2:
                        gMaterielMenu_LUIDA_STATUS.open();
                        return;
                    case 3:
                        return;
                }
            }
        }
        return;
    }
    if (mode_ == MODE_OPEN) {
        gTownMenu_MESSAGE.openMessageForTALK();
        gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(3));
        gTownMenu_MESSAGE.addMessageWAITKEY();
        mode_ = MODE_OPEN_DRAW;
    }
    if (mode_ == MODE_START) {
        openMessage(1, 2);
        mode_ = MODE_OPEN;
    }
}

THUMB void MaterielMenu_LUIDA_ROOT::selectKuwaeru()
{
    MenuStatusInfo::setMode(MenuStatusInfo::ALL_PLAYER_MODE);
    if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) == 8) {
        openMessage(4, 5);
        mode_ = MODE_CHANGE_MENU;
    }
    else if (status::PlayerDataAll::getPlayerCountInRuida() == 0) {
        openMessage(6, 0);
        mode_ = MODE_CHANGE_MENU;
    }
    else {
        openMessage(7, 0);
        unk_1c = 1;
    }
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
}

THUMB void MaterielMenu_LUIDA_ROOT::selectAzuke()
{
    if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) == 1) {
        openMessage(13, 0);
        mode_ = MODE_CHANGE_MENU;
    }
    else {
        openMessage(14, 0);
        unk_1c = 1;
    }
}

THUMB void MaterielMenu_LUIDA_ROOT::selectList()
{
    if (status::PlayerDataAll::getPlayerCountInRuida() == 0) {
        openMessage(25, 0);
        mode_ = MODE_CHANGE_MENU;
    }
    else {
        openMessage(26, 0);
        unk_1c = 1;
    }
}

THUMB void MaterielMenu_LUIDA_ROOT::selectYameru()
{
    openMessage(29, 0);
    gTownMenu_MESSAGE.setMessageLastCursor(false);
    menuItem_.active_ = 3;
}

THUMB int MaterielMenu_LUIDA_ROOT::getMessageNo(int index)
{
    return dq5::level::LuidaMessage::getRecord(index)->getMessage1();
}

THUMB void MaterielMenu_LUIDA_ROOT::openMessage(int mes1, int mes2)
{
    int m1 = getMessageNo(mes1);
    int m2 = getMessageNo(mes2);
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(m1);
    if (m2 != 0) {
        gTownMenu_MESSAGE.addMessage(m2);
    }
}
