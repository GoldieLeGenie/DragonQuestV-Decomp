#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_LEAVE_MONSTER.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_LEAVE_MESSAGE.hpp"
#include "ov032/materielmenu/jisan/MaterielMenu_JISAN_ROOT.hpp"
#include "ov032/leveldata/JisanMessage.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"

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

THUMB void MaterielMenu_JISAN_LEAVE_MONSTER::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    mode_ = MODE_SELECT;
}

THUMB void MaterielMenu_JISAN_LEAVE_MONSTER::menuExecute()
{
    unkfunc_0201c904(&menuItem_, navigator_.getCountInPage(), menuItem_.active_);
}

THUMB void MaterielMenu_JISAN_LEAVE_MONSTER::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() != true) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_AND_CARRIAGE_MODE);
        int page = navigator_.getPageNo();
        int pageMax = navigator_.getPageMaxCount() - 1;
        unkfunc_0217c3dc(page, pageMax, 0, 0);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_JISAN_LEAVE_MONSTER::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (mode_ == MODE_END) {
                gTownMenu_MESSAGE.openMessageForTALK();
                gTownMenu_MESSAGE.addMessageNOWAIT(getMessageNo(0x48));
                gTownMenu_MESSAGE.addMessageWAITKEY();
                close();
                gMaterielMenu_JISAN_ROOT.setActiveMenu(0);
                gMaterielMenu_JISAN_ROOT.open();
            }
        }
        return;
    }
    navigator_.setup(5, 1, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL));
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        int active = navigator_.getIndex(menuItem_.active_);
        int page = navigator_.getPageNo();
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(active);
        menu::MaterielMenuPlayerControl::getSingleton()->activeCharaPage_ = page;
        if (result == 3) {
            mode_ = MODE_END;
            gTownMenu_MESSAGE.openMessageForTALK();
            gTownMenu_MESSAGE.addMessage(getMessageNo(0x47));
        }
        if (result == 2) {
            close();
            gMaterielMenu_JISAN_LEAVE_MESSAGE.open();
        }
        redraw_ = 1;
    }
}

THUMB int MaterielMenu_JISAN_LEAVE_MONSTER::getMessageNo(int index)
{
    return dq5::level::JisanMessage::getRecord(index)->getMessage1();
}
