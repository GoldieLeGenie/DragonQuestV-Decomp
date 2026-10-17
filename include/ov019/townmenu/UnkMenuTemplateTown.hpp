#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// touch areas of the town menus
void unkfunc_02171338(menu::MenuItem* menuItem, int active, int max);         // operation menu (2x5)
void unkfunc_02171354(menu::MenuItem* menuItem, int active, int max);         // 32x32 icons (5x2)
void unkfunc_02171370(menu::MenuItem* menuItem, int active);                  // bgm volume
void unkfunc_0217138c(menu::MenuItem* menuItem, int active);                  // effect volume
void unkfunc_021713a8(menu::MenuItem* menuItem, int active);                  // battle speed
void unkfunc_021713c4(menu::MenuItem* menuItem, int active);                  // root menu icons
void unkfunc_021713e0(menu::MenuItem* menuItem, int commandFlag, int active); // item command list
void unkfunc_02171458(menu::MenuItem* menuItem, int max, int active, int x, int y);    // tactics character list, 2 rows
void unkfunc_021714a8(menu::MenuItem* menuItem, int max, int active, int x, int y);    // tactics character list, 1 row
void unkfunc_021714f8(menu::MenuItem* menuItem, int charaCount, int active);  // character list, 2 rows
void unkfunc_02171514(menu::MenuItem* menuItem, int charaCount, int active);  // character list, 1 row
void unkfunc_02171530(menu::MenuItem* menuItem, int active);                  // tactics (3x2)
void unkfunc_unused_0217f30c(menu::MenuItem* menuItem, int active);
void unkfunc_0217154c(menu::MenuItem* menuItem, int max, int active);         // target character pages (2x2)
void unkfunc_02171568(menu::MenuItem* menuItem, int active);                  // two buttons
void unkfunc_02171584(menu::MenuItem* menuItem);                              // two wide buttons
void unkfunc_02171598(menu::MenuItem* menuItem, int max, int active);         // spell list (2x4)
