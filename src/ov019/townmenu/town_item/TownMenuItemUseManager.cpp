#pragma ipa file
#include "ov019/townmenu/town_item/TownMenuItemUseManager.hpp"

menu::TownMenuItemUseManager menu::gTownMenuItemUseManager;

THUMB menu::TownMenuItemUseManager& menu::TownMenuItemUseManager::getSingleton()
{
    return gTownMenuItemUseManager;
}

THUMB bool menu::TownMenuItemUseManager::getDefaultCloseMenuItem(int itemID)
{
    if (itemID == 0xa3) {
        return true;
    }
    if (itemID == 0xaa) {
        return true;
    }
    if (itemID == 0xc3) {
        return true;
    }
    if (itemID == 0xc6) {
        return true;
    }
    return false;
}

THUMB bool menu::TownMenuItemUseManager::isEquipSpecialItem(int itemID)
{
    if (itemID == 0xdd || itemID == 0xe2 || itemID == 0xec || itemID == 0xe1) {
        return true;
    }
    return false;
}
