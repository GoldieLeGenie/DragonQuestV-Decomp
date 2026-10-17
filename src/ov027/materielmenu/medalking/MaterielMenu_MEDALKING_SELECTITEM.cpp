#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_SELECTITEM.hpp"
#include "ov027/materielmenu/medalking/MaterielMenuMedalKingManager.hpp"
#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_SELECTCHARA.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/materielmenu/MenuTemplate_materiel.hpp"
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void menu::MenuPlayerControl::setActiveItem(short item)
{
    activeItem_ = item;
}

THUMB void MaterielMenu_MEDALKING_SELECTITEM::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menuItem_.setup(menu::MenuItem::MENUITEM_TYPE_TOUCH_PAD_CANCEL, menu::MenuItem::CURSORTYPE_ACTIVE);
    menuItem_.active_ = 0;
    navigator_.setupBase();
    m_mode = MODE_ITEM_SELECT;
    unkfunc_0204c9bc(-4, 0);
}

THUMB void MaterielMenu_MEDALKING_SELECTITEM::menuExecute()
{
    menu::MenuTemplate_materiel::MATERIEL_CELECT_BUY(&menuItem_, menuItem_.active_, 6);
}

THUMB void MaterielMenu_MEDALKING_SELECTITEM::menuDraw()
{
    if (gTownMenu_MESSAGE.isOpen() == false) {
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
        unkfunc_0217be4c(2);
        menuItem_.drawActive();
    }
}

THUMB void MaterielMenu_MEDALKING_SELECTITEM::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            switch (m_mode) {
                case MODE_ITEM_SELECT:
                    break;
                case MODE_YESNO:
                    MaterielMenuMedalKingManager::showMessage(5, 0, 0);
                    m_mode = MODE_ITEM_SELECT;
                    break;
                case MODE_NEXT:
                    unkfunc_0204c9c8();
                    close();
                    gMaterielMenu_MEDALKING_SELECTCHARA.open();
                    break;
                case MODE_END:
                    unkfunc_0204c9c8();
                    MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                    break;
            }
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            MaterielMenuMedalKingManager::showMessage(0x13, 0, 0);
            m_mode = MODE_END;
        }
        return;
    }
    navigator_.setup(1, 6, 6);
    int result = MenuUpdate_Assist::menuSelect(menuItem_, navigator_);
    if (result != 0) {
        menu::MaterielMenuPlayerControl::getSingleton()->setActiveItem((char)menuItem_.active_);
        if (result == 3) {
            MaterielMenuMedalKingManager::showMessage(0x12, 0, 0);
            gTownMenu_MESSAGE.setYesNo();
            m_mode = MODE_YESNO;
        }
        if (result == 2) {
            if (MaterielMenuMedalKingManager::isNeedMedal() == true) {
                TextAPI::setMACRO0(10, 0x40000000, MaterielMenuMedalKingManager::getItemID());
                MaterielMenuMedalKingManager::showMessage(7, 8, 0);
                gTownMenu_MESSAGE.setMessageLastCursor(true);
                m_mode = MODE_NEXT;
            }
            else {
                MaterielMenuMedalKingManager::showMessage(6, 0x12, 0);
                gTownMenu_MESSAGE.setYesNo();
                m_mode = MODE_YESNO;
            }
        }
        redraw_ = 1;
    }
}
