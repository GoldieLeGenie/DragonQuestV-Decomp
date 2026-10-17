#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_SELECTCHARA.hpp"
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_EQUIPCHECK.hpp"
#include "ov027/materielmenu/changegift/MaterielMenu_CHANGEGIFT_ROOT.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveChara(short chara)
{
    activeChara_ = chara;
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTCHARA::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    maxCharaCount_ = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1;
    navigator_.setupBase();
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTCHARA::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_ICON32_5x2(&menuItem_, menuItem_.active_, maxCharaCount_);
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTCHARA::menuDraw()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    unkfunc_0217be90(1, 0);
    menuItem_.drawActive();
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTCHARA::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK || stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
        }
        return;
    }
    navigator_.setup(5, 2, maxCharaCount_);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveChara((char)menuItem_.active_);
        if (result == 3) {
            cancelChange();
        }
        if (result == 2) {
            close();
            gMaterielMenu_CHANGEGIFT_EQUIPCHECK.open();
        }
        redraw_ = 1;
    }
}

THUMB void MaterielMenu_CHANGEGIFT_SELECTCHARA::cancelChange()
{
    gTownMenu_MESSAGE.openMessageForTALK();
    gTownMenu_MESSAGE.addMessage(gMaterielMenu_CHANGEGIFT_ROOT.getMessageNo(0x13));
    gTownMenu_MESSAGE.setYesNo();
    close();
    gMaterielMenu_CHANGEGIFT_ROOT.open();
    gMaterielMenu_CHANGEGIFT_ROOT.mode_ = MaterielMenu_CHANGEGIFT_ROOT::CHANGEGIFT_BACK;
}
