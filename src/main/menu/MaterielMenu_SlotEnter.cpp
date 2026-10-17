#pragma ipa file
#include "main/menu/MaterielMenu_SlotEnter.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/global/Global.hpp"
#include "main/menu/MaterielMenuWindowManager.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/text/TextAPI.hpp"
#include "ov001/town/TownPlayerManager.hpp"

inline void menu::MaterielMenu_SlotEnter::menuDraw()
{
}

inline void menu::MaterielMenu_SlotEnter::menuExecute()
{
}

inline menu::MenuBase::MENUBASE_STAT menu::MenuBase::getStat()
{
    return stat_;
}

int menu::MaterielMenu_SlotEnter::machineSelect_;

THUMB void menu::MaterielMenu_SlotEnter::menuSetup()
{
    enableFlag_ = true;
    slotType_ = machineSelect_;
}

THUMB void menu::MaterielMenu_SlotEnter::setSlotType(int type)
{
    machineSelect_ = type;
    slotType_ = type;
}

THUMB void menu::MaterielMenu_SlotEnter::menuUpdate()
{
    enableUpdate();
}

THUMB void menu::MaterielMenu_SlotEnter::enableUpdate()
{
    if (gTownMenu_MESSAGE.isOpen()) {
        MENUBASE_STAT stat = gTownMenu_MESSAGE.getStat();
        if (stat == MENUBASE_STAT_OK) {
            gTownMenu_MESSAGE.close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
            twn::TownPlayerManager::getSingleton().setLock(true);
            cmn::g_cmnPartyInfo.prevLocation_ = true;
            g_Global.setMinigame(getGameCost());
            g_Global.setGameStatus(machineSelect_);
            g_Global.startCasino();
        } else if (stat == MENUBASE_STAT_CANCEL) {
            gTownMenu_MESSAGE.close();
            MaterielMenu_WINDOW_MANAGER::getSingleton()->closeMaterielWindow();
        }
    } else {
        gTownMenu_MESSAGE.openMessageForMENU();
        TextAPI::setMACRO0(0x6b, 0xf0000000, getGameCost());
        gTownMenu_MESSAGE.addMessage(0xc96aa);
        gTownMenu_MESSAGE.setYesNo();
    }
}

THUMB int menu::MaterielMenu_SlotEnter::getGameCost()
{
    int coin;
    if (machineSelect_ < 5) {
        coin = 1;
    } else if (machineSelect_ < 9) {
        coin = 10;
    } else {
        coin = 100;
    }
    if (machineSelect_ == 0) {
        coin = 100;
    }
    return coin;
}
