#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

namespace menu {
    struct TOUCHRECT;
}

// battle menu item layouts
void unkfunc_02175a5c(menu::MenuItem* menuItem);                          // cancel button
void unkfunc_02175a70(menu::MenuItem* menuItem);                          // cancel button (attack)
void unkfunc_02175a84(menu::MenuItem* menuItem, int max, int active);     // command icons (2x2)
void unkfunc_02175ab8(menu::MenuItem* menuItem, int max);                  // magic list (2x3)
void unkfunc_02175acc(menu::MenuItem* menuItem, int active);              // tactics (3x2)
void unkfunc_02175ae8(menu::MenuItem* menuItem, int max);                  // party targets (2x2)
void unkfunc_02175afc(menu::MenuItem* menuItem, int active);              // array menu (2x1)
void unkfunc_02175b18(menu::MenuItem* menuItem, int active, int max);     // tactics characters (5x1)
void unkfunc_02175b34(menu::MenuItem* menuItem, int active, int max);     // array change members (4x1)
void unkfunc_02175b50(menu::MenuItem* menuItem, int active, int max);     // array change carriage (4x1)
void unkfunc_02175b6c(menu::MenuItem* menuItem, int active, int max);     // array all (5x2)
void unkfunc_02175b88(menu::MenuItem* menuItem, int active, menu::TOUCHRECT* rect, int count);   // monster icons
void unkfunc_02175be0(menu::MenuItem* menuItem);                          // monster area
void unkfunc_02175c0c(menu::MenuItem* menuItem, int active, int max, int x, int y);   // page arrows
