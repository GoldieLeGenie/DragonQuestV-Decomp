#pragma ipa file
#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_ROOT.hpp"
#include "ov027/materielmenu/medalking/MaterielMenuMedalKingManager.hpp"
#include "ov027/materielmenu/medalking/MaterielMenu_MEDALKING_SELECTITEM.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

inline void MaterielMenu_MEDALKING_ROOT::menuExecute()
{
}

inline void MaterielMenu_MEDALKING_ROOT::menuDraw()
{
}

THUMB void MaterielMenu_MEDALKING_ROOT::menuSetup()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    menu::MaterielMenuPlayerControl::getSingleton()->initialize();
    m_mode = MODE_START;
    resetCaptureOffset();
    if (MenuStatusInfo::getMedal() == 0) {
        MaterielMenuMedalKingManager::showMessage(1, 0x14, 0);
        m_mode = MODE_END;
        return;
    }
    TextAPI::setMACRO0(0x39, 0xf0000000, MenuStatusInfo::getMedal());
    MaterielMenuMedalKingManager::showMessage(1, 4, 0);
    gTownMenu_MESSAGE.setYesNo();
    m_mode = MODE_SELECT;
}

THUMB void MaterielMenu_MEDALKING_ROOT::menuUpdate()
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    if (gTownMenu_MESSAGE.isOpen() == true) {
        int stat = gTownMenu_MESSAGE.stat_;
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            switch (m_mode) {
                case MODE_SELECT:
                    MaterielMenuMedalKingManager::showMessage(5, 0, 0);
                    gTownMenu_MESSAGE.setMessageLastCursor(true);
                    m_mode = MODE_NEXT;
                    break;
                case MODE_NEXT:
                    close();
                    gMaterielMenu_MEDALKING_SELECTITEM.open();
                    break;
                case MODE_END:
                    MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
                    break;
            }
        }
        if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            MaterielMenuMedalKingManager::showMessage(0x13, 0, 0);
            m_mode = MODE_END;
        }
    }
}
