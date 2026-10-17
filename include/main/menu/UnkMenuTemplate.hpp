#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// text colors of the menu parts by actor condition (0 normal, 1 near death, 2 dead)
extern int data_02094dd4[6];

void unkfunc_0201c8e8(menu::MenuItem* menuitem, int itemMaxCount, int active);     // 2x3 item list
void unkfunc_0201c904(menu::MenuItem* menuitem, int itemMaxCount, int active);     // 5x1 list
