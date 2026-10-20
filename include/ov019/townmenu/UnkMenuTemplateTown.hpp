#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// touch areas of the town menus
void townMenuOperation(menu::MenuItem* menuItem, int active, int max);         // operation menu (2x5)
void townMenuIcon32Grid(menu::MenuItem* menuItem, int active, int max);         // 32x32 icons (5x2)
void townMenuBgmVolume(menu::MenuItem* menuItem, int active);                  // bgm volume
void townMenuEffectVolume(menu::MenuItem* menuItem, int active);                  // effect volume
void townMenuBattleSpeed(menu::MenuItem* menuItem, int active);                  // battle speed
void unkfunc_021713c4(menu::MenuItem* menuItem, int active);                  // root menu icons
void townMenuItemCommand(menu::MenuItem* menuItem, int commandFlag, int active); // item command list
void townMenuTacticsSelectChara(menu::MenuItem* menuItem, int max, int active, int x, int y);    // tactics character list, 2 rows
void townMenuTacticsSelectHalfChara(menu::MenuItem* menuItem, int max, int active, int x, int y);    // tactics character list, 1 row
void townMenuItemSelectChara(menu::MenuItem* menuItem, int charaCount, int active);  // character list, 2 rows
void townMenuItemSelectHalfChara(menu::MenuItem* menuItem, int charaCount, int active);  // character list, 1 row
void townMenuTacticsSelectTC(menu::MenuItem* menuItem, int active);                  // tactics (3x2)
void unkfunc_unused_0217f30c(menu::MenuItem* menuItem, int active);
void townMenuPageTargetChara(menu::MenuItem* menuItem, int max, int active);         // target character pages (2x2)
void townMenuTacticsBoxUp(menu::MenuItem* menuItem, int active);                  // two buttons
void townMenuRemoveEquip(menu::MenuItem* menuItem);                              // two wide buttons
void townMenuSelectMagic(menu::MenuItem* menuItem, int max, int active);         // spell list (2x4)
