#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_ADD_PLAYER.hpp"
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_ROOT.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/status/GameFlag.hpp"
#include "ov033/leveldata/LuidaMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
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

inline void MaterielMenu_LUIDA_ROOT::setActiveMenu(char active)
{
    active_ = active;
}

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_LUIDA_ADD_PLAYER::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    status::g_Menu.drawFlag_ = 2;
    int luidaCount = status::PlayerDataAll::getPlayerCountInRuida();
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(5, 1, luidaCount);
    mode_ = MODE_OPEN;
    if (status::g_Menu.bookingFlag_ == menu::BOOKING_RETURN) {
        status::g_Menu.bookingFlag_ = 0;
        status::g_Menu.returnMenuType_ = 0;
        if (partyCount < 8 && luidaCount > 0) {
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(12));
            mode_ = MODE_OPEN;
            return;
        }
        mode_ = MODE_BOOKING;
        returnRoot();
    }
}

THUMB void MaterielMenu_LUIDA_ADD_PLAYER::menuExecute()
{
    setupCharaRowLayout5x1(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void MaterielMenu_LUIDA_ADD_PLAYER::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true && mode_ == MODE_OPEN) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        int page = navigator_.getPageNo();
        int pageMax = navigator_.getPageMaxCount() - 1;
        unkfunc_0217c3dc(page, pageMax, 6, 0);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_LUIDA_ADD_PLAYER::menuUpdate()
{
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            messageUpdate();
        }
        return;
    }
    if (mode_ != MODE_OPEN) {
        return;
    }
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(menuItem_.active_);
        if (result == 3) {
            returnRoot();
        }
        if (result == 2) {
            int& active = menuItem_.active_;
            int index = navigator_.getIndex(active);
            gTownMenu_MESSAGE.openMessageForTALK();
            TextAPI::setMACRO0(0x12, 0x50000000, MenuStatusInfo::getPlayerIndex(index));
            gTownMenu_MESSAGE.addMessage(getMessageNo(8), getMessageNo(9));
            mode_ = MODE_SELECT;
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_LUIDA_ADD_PLAYER::messageUpdate()
{
    gTownMenu_MESSAGE.close();
    switch (mode_) {
        case MODE_SELECT: {
            int& active = menuItem_.active_;
            int index = MenuStatusInfo::getPlayerIndex(navigator_.getIndex(active));
            setFlag(index);
            gTownMenu_MESSAGE.openMessageForMENU();
            TextAPI::setMACRO0(0x12, 0x50000000, index);
            gTownMenu_MESSAGE.addMessage(getMessageNo(10));
            status::g_Menu.drawFlag_ = 0;
            if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT) == 4) {
                gTownMenu_MESSAGE.addMessage(getMessageNo(11));
            }
            if (status::PlayerDataAll::getPlayerCountInRuida() > 0) {
                status::g_Menu.drawFlag_ = 2;
            }
            unsigned int localFlag = 0;
            switch (index) {
                case 13:
                    localFlag = 0x3c;
                    break;
                case 14:
                    localFlag = 0x3d;
                    break;
                case 11:
                    localFlag = 0x3e;
                    break;
                case 12:
                    localFlag = 0x3f;
                    break;
                case 4:
                    localFlag = 0x40;
                    break;
                case 9:
                    localFlag = 0x41;
                    break;
                case 10:
                    localFlag = 0x42;
                    break;
            }
            g_GlobalFlag.set(localFlag);
            mode_ = MODE_RETURN;
            break;
        }
        case MODE_RETURN: {
            int& active = menuItem_.active_;
            int ctrl = status::PlayerDataAll::getPlayerCtrlInRuida(navigator_.getIndex(active));
            MenuStatusInfo::addPlayer(ctrl);
            status::PlayerDataAll::setRuidaFlag(ctrl, false);
            cmn::GameManager::getSingleton().resetParty();
            status::g_Menu.bookingFlag_ = menu::BOOKING_LUIDA;
            status::g_Menu.returnMenuType_ = 4;
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            break;
        }
        case MODE_BOOKING:
            returnRoot();
            break;
    }
}

THUMB void MaterielMenu_LUIDA_ADD_PLAYER::returnRoot()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(28));
    gTownMenu_MESSAGE.addMessageWAITKEY();
    close();
    gMaterielMenu_LUIDA_ROOT.setActiveMenu(0);
    gMaterielMenu_LUIDA_ROOT.open();
}

THUMB int MaterielMenu_LUIDA_ADD_PLAYER::getMessageNo(int index)
{
    return dq5::level::LuidaMessage::getRecord(index)->getMessage1();
}

THUMB void MaterielMenu_LUIDA_ADD_PLAYER::setFlag(int index)
{
    switch (index) {
        case 11:
            if (g_AreaFlag.check(0x1c3) == true) {
                if (!g_AreaFlag.check(0x1ce)) {
                    g_AreaFlag.set(0x1ce);
                }
            }
            else if (!g_AreaFlag.check(0x164)) {
                g_AreaFlag.set(0x164);
            }
            break;
        case 12:
            if (!g_AreaFlag.check(0x165)) {
                g_AreaFlag.set(0x165);
            }
            break;
        case 13:
            if (g_AreaFlag.check(0x1c3) == true) {
                if (!g_AreaFlag.check(0x1cc)) {
                    g_AreaFlag.set(0x1cc);
                }
            }
            break;
        case 14:
            if (g_AreaFlag.check(0x1c3) == true) {
                if (!g_AreaFlag.check(0x1cd)) {
                    g_AreaFlag.set(0x1cd);
                }
            }
            break;
        case 4:
            if (!g_AreaFlag.check(0x1ca)) {
                g_AreaFlag.set(0x1ca);
            }
            break;
        case 9:
            if (!g_AreaFlag.check(0x1cb)) {
                g_AreaFlag.set(0x1cb);
            }
            break;
        case 10:
            if (!g_AreaFlag.check(0x25b)) {
                g_AreaFlag.set(0x25b);
            }
            break;
    }
}
