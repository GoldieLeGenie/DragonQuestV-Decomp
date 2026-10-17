#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_STATUS.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ROOT.hpp"
#include "ov032/leveldata/JisanMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/MenuStatus.hpp"

using menu::MenuStatusInfo;

inline dq5::level::JisanMessage* dq5::level::JisanMessage::getRecord(int index)
{
    return (JisanMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::JisanMessage::getMessage1()
{
    return message1;
}

inline void MaterielMenu_JISAN_ROOT::setActiveMenu(char select)
{
    active_ = select;
}

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_JISAN_STATUS::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    status::g_Menu.drawFlag_ = 1;
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    mode_ = SELECT_MONSTER;
    unkfunc_021889c4();
}

THUMB void MaterielMenu_JISAN_STATUS::menuExecute()
{
    unkfunc_0201c904(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void MaterielMenu_JISAN_STATUS::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
        int pageMax = navigator_.getPageMaxCount() - 1;
        unkfunc_0217c380(mode_, navigator_.getPageNo(), pageMax, 2);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_JISAN_STATUS::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == SELECT_MONSTER) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x48));
                gTownMenu_MESSAGE.addMessageWAITKEY();
                close();
                gMaterielMenu_JISAN_ROOT.setActiveMenu(2);
                gMaterielMenu_JISAN_ROOT.open();
                return;
            }
            mode_ = SELECT_MONSTER;
        }
        return;
    }
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        int active = menuItem_.active_;
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(navigator_.getIndex(active));
        if (result == 3) {
            gTownMenu_MESSAGE.openMessageForTALK();
            if (mode_ == SELECT_MONSTER) {
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x47));
            }
            else {
                gTownMenu_MESSAGE.addMessage(getMessageNo(0x1e));
            }
        }
        if (result == 2) {
            if (mode_ == SELECT_MONSTER) {
                if (MenuStatusInfo::isPlayerActionEnable(navigator_.getIndex(active)) == true) {
                    mode_ = SELECT_MAGIC;
                }
            }
            else {
                mode_ = SELECT_MONSTER;
            }
        }
        unkfunc_021889c4();
        redraw_ = 1;
    }
}

THUMB int MaterielMenu_JISAN_STATUS::getMessageNo(int index)
{
    return dq5::level::JisanMessage::getRecord(index)->getMessage1();
}

THUMB void MaterielMenu_JISAN_STATUS::unkfunc_021889c4()
{
    int flag = 0;
    if (MenuStatusInfo::isPlayerActionEnable(menu::MaterielMenuPlayerControl::getSingleton()->activeChara_) == true) {
        flag = 1;
    }
    menuItem_.enableSE_ = flag;
}
