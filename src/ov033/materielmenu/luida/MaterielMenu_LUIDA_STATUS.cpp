#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_STATUS.hpp"
#include "ov033/materielmenu/luida/MaterielMenu_LUIDA_ROOT.hpp"
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

THUMB void MaterielMenu_LUIDA_STATUS::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    status::g_Menu.drawFlag_ = 2;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    mode_ = 0;
    unkfunc_02186b1c();
}

THUMB void MaterielMenu_LUIDA_STATUS::menuExecute()
{
    setupCharaRowLayout5x1(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void MaterielMenu_LUIDA_STATUS::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        int pageMax = navigator_.getPageMaxCount() - 1;
        unkfunc_0217c380(mode_, navigator_.getPageNo(), pageMax, 8);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_LUIDA_STATUS::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == 0) {
                returnRoot();
                return;
            }
            mode_ = 0;
        }
        return;
    }
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        int active = menuItem_.active_;
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(active);
        if (result == 3) {
            gTownMenu_MESSAGE.openMessageForTALK();
            if (mode_ == 0) {
                returnRoot();
            }
            else {
                gTownMenu_MESSAGE.addMessage(getMessageNo(27));
            }
        }
        if (result == 2) {
            if (mode_ == 0) {
                if (MenuStatusInfo::isPlayerActionEnable(active) == true) {
                    mode_ = 1;
                }
            }
            else {
                mode_ = 0;
            }
        }
        unkfunc_02186b1c();
        redraw_ = 1;
    }
}

THUMB int MaterielMenu_LUIDA_STATUS::getMessageNo(int index)
{
    return dq5::level::LuidaMessage::getRecord(index)->getMessage1();
}

THUMB void MaterielMenu_LUIDA_STATUS::unkfunc_02186b1c()
{
    int flag = 0;
    if (MenuStatusInfo::isPlayerActionEnable(menu::MaterielMenuPlayerControl::getSingleton()->activeChara_) == true) {
        flag = 1;
    }
    menuItem_.enableSE_ = flag;
}

THUMB void MaterielMenu_LUIDA_STATUS::returnRoot()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(28));
    gTownMenu_MESSAGE.addMessageWAITKEY();
    close();
    gMaterielMenu_LUIDA_ROOT.setActiveMenu(2);
    gMaterielMenu_LUIDA_ROOT.open();
}
