#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

namespace menu {
    struct TOUCHRECT;
}

// battle menu item layouts
void setupBattleCancel(menu::MenuItem* menuItem);                          // cancel button
void setupBattleFightCancel(menu::MenuItem* menuItem);                          // cancel button (attack)
void setupBattleMenuIcon2x2(menu::MenuItem* menuItem, int max, int active);     // command icons (2x2)
void setupBattleMagic2x3(menu::MenuItem* menuItem, int max);                  // magic list (2x3)
void setupBattleTactics3x2(menu::MenuItem* menuItem, int active);              // tactics (3x2)
void setupBattleParty2x2(menu::MenuItem* menuItem, int max);                  // party targets (2x2)
void setupBattleArrayMenu2x1(menu::MenuItem* menuItem, int active);              // array menu (2x1)
void setupBattleTacticsChange5x1(menu::MenuItem* menuItem, int active, int max);     // tactics characters (5x1)
void setupBattleArrayChange4x1(menu::MenuItem* menuItem, int active, int max);     // array change members (4x1)
void setupBattleArrayChangeTo4x1(menu::MenuItem* menuItem, int active, int max);     // array change carriage (4x1)
void setupBattleArrayAll5x2(menu::MenuItem* menuItem, int active, int max);     // array all (5x2)
void setupBattleEnemyIcons(menu::MenuItem* menuItem, int active, menu::TOUCHRECT* rect, int count);   // monster icons
void setupBattleEnemyRect(menu::MenuItem* menuItem);                          // monster area
void setupBattlePageArrow(menu::MenuItem* menuItem, int active, int max, int x, int y);   // page arrows
