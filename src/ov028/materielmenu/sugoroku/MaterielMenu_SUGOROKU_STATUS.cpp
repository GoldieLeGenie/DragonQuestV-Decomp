#include "ov028/materielmenu/sugoroku/MaterielMenu_SUGOROKU_STATUS.hpp"
#include "ov028/materielmenu/sugoroku/MaterielMenu_SUGOROKU_ROOT.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_SUGOROKU_STATUS::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    navigator_.setupBase();
    navigator_.setup(2, 1, 2);
    menu::MaterielMenuPlayerControl::getSingleton()->activeChara_ = 0;
    mode_ = 0;
}

THUMB void MaterielMenu_SUGOROKU_STATUS::menuExecute()
{
    unkfunc_0201c904(&menuItem_, 2, menuItem_.active_);
}

THUMB void MaterielMenu_SUGOROKU_STATUS::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unkfunc_0217c520(mode_);
    menuItem_.drawActive();
}

THUMB void MaterielMenu_SUGOROKU_STATUS::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int prevActive = menuItem_.active_;
    navigator_.setup(2, 1, 2);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        bool fukuro = false;
        if (menuItem_.active_ == 1) {
            fukuro = true;
        }
        if (result == 3) {
            mode_--;
            if (fukuro == true && mode_ == 0) {
                redraw_ = 1;
                return;
            }
            if (mode_ >= 2) {
                redraw_ = 1;
                return;
            }
            close();
            gMaterielMenu_SUGOROKU_ROOT.open();
        }
        if (result == 2) {
            if (fukuro == true) {
                mode_++;
                if (mode_ > 4) {
                    mode_ = 2;
                }
            }
            else if (MenuStatusInfo::isPlayerActionEnable(0) == true) {
                mode_++;
                if (mode_ > 1) {
                    mode_ = 0;
                }
            }
        }
        if (fukuro == true) {
            menu::MaterielMenuPlayerControl::getSingleton()->activeChara_ = -2;
        }
        else {
            menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara(menuItem_.active_);
        }
        if (prevActive != menuItem_.active_) {
            if (menuItem_.active_ == 0) {
                mode_ = 0;
            }
            else {
                mode_ = 2;
            }
        }
        redraw_ = 1;
    }
}
