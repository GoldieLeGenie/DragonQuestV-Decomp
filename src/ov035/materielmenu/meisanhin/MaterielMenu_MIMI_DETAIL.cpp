#include "ov035/materielmenu/meisanhin/MaterielMenu_MIMI_DETAIL.hpp"
#include "ov035/materielmenu/meisanhin/MaterielMenu_MIMI_ROOT.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "main/menu/MenuStatusInfo.hpp"

using menu::MenuStatusInfo;

inline void menu::MaterielMenuPlayerControl::setActiveItemPage(int active)
{
    activeItemPage_ = active;
}

inline void MaterielMenu_MIMI_ROOT::setMimiMode(MIMI_MODE mode)
{
    mode_ = mode;
}

THUMB void MaterielMenu_MIMI_DETAIL::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_NONE);
    menuItem_.active_ = 0;
    menuItem_.enableSE_ = 0;
    navigator_.setupBase();
    navigator_.setup(1, 1, 1);
    navigator_.setPageNo(menu::MaterielMenuPlayerControl::getSingleton()->activeItem_);
}

THUMB void MaterielMenu_MIMI_DETAIL::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_PICTUREBOOK_MONSTERANIME(&menuItem_);
}

THUMB void MaterielMenu_MIMI_DETAIL::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unkfunc_0217b144();
}

THUMB void MaterielMenu_MIMI_DETAIL::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    navigator_.setup(1, 1, 28);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        int active = navigator_.getPageNo();
        menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = active;
        if (result == 3) {
            menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(0);
            if (active >= 16) {
                active -= 16;
                menu::MaterielMenuPlayerControl::getSingleton()->setActiveItemPage(1);
            }
            menu::MaterielMenuPlayerControl::getSingleton()->activeItem_ = active;
            close();
            gMaterielMenu_MIMI_ROOT.setMimiMode(MaterielMenu_MIMI_ROOT::MODE_MEMO);
            gMaterielMenu_MIMI_ROOT.open();
        }
        redraw_ = 1;
    }
}
