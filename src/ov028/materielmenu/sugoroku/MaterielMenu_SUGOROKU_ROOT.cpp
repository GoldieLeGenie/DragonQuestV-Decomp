#include "ov028/materielmenu/sugoroku/MaterielMenu_SUGOROKU_ROOT.hpp"
#include "ov028/materielmenu/sugoroku/MaterielMenu_SUGOROKU_STATUS.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/town/TownSugorokuInfo.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

THUMB void MaterielMenu_SUGOROKU_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = menu::MaterielMenuPlayerControl::getSingleton()->activeItem_;
    navigator_.setupBase();
    navigator_.setup(1, 4, 4);
}

THUMB void MaterielMenu_SUGOROKU_ROOT::menuExecute()
{
    menu::MenuTemplate_materiel::unkfunc_0217d7c8(&menuItem_, menuItem_.active_);
}

THUMB void MaterielMenu_SUGOROKU_ROOT::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() == false) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217c518();
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_SUGOROKU_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            if (stat == MENUBASE_STAT_OK) {
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                twn::g_SugorokuInfo.menuState_ = 2;
            }
        }
        return;
    }
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0 && result == 2) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem(menuItem_.active_);
        switch (menuItem_.active_) {
            case 0:
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                twn::g_SugorokuInfo.menuState_ = 0;
                twn::g_SugorokuInfo.diceCount_--;
                break;
            case 1:
                MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                twn::g_SugorokuInfo.menuState_ = 1;
                break;
            case 2:
                close();
                gMaterielMenu_SUGOROKU_STATUS.open();
                break;
            case 3:
                gTownMenu_MESSAGE.openMessageForMENU();
                gTownMenu_MESSAGE.addMessage(0xc9e96);
                gTownMenu_MESSAGE.setYesNo(1);
                break;
        }
    }
}
