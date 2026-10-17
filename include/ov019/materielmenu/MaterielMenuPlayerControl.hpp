#pragma once
#include <globaldefs.h>
#include "ov019/commonmenu/MenuPlayerControl.hpp"

namespace menu {

// selection state shared by the materiel menus (shops, church, casino...)
struct MaterielMenuPlayerControl : MenuPlayerControl {
    int activeItemPage_;                        // 0x0C
    int churchCommandNum_;                      // 0x10

    static MaterielMenuPlayerControl* getSingleton();
    void initialize();
    void setActiveItemPage(int active);
};

}  // namespace menu
