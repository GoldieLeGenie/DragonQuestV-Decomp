#pragma once
#include <globaldefs.h>

namespace menu {

// items whose use is handled specially by the town item menus
struct TownMenuItemUseManager {
    unsigned char m_eventItem;                  // 0x00
    bool m_eventItemFlag;                       // 0x01

    static TownMenuItemUseManager& getSingleton();
    bool getDefaultCloseMenuItem(int itemID);
    static bool isEquipSpecialItem(int itemID);
};

extern TownMenuItemUseManager gTownMenuItemUseManager;

}  // namespace menu
