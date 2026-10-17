#pragma once
#include <globaldefs.h>

namespace menu {

// selection state shared by the menus (base of the town/materiel menu player controls)
struct MenuPlayerControl {
    short activeChara_;                         // 0x00
    char activeCharaPage_;                      // 0x02
    short activeItem_;                          // 0x04
    short targetChara_;                         // 0x06
    short targetCharaPage_;                     // 0x08
    short activeMagic_;                         // 0x0A

    void setup();
    void setActiveChara(short chara);
    void setActiveItem(short item);
    void setTargetChara(short target);
    void setTargetCharaPage(short page);
};

}  // namespace menu
