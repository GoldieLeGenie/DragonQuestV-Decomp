#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

namespace menu {

// MenuItem layouts of the materiel (shop/church/casino/diary/surechigai...) menus
struct MenuTemplate_materiel {
    static void MATERIEL_SHOP_ROOT(menu::MenuItem* menuitem, int active);
    static void MATERIEL_CHURCH_ROOT(menu::MenuItem* menuitem, int maxCommand, int active);
    static void MATERIEL_ICON32_5x2_CHURCH(menu::MenuItem* menuitem, int active, int max);
    static void MATERIEL_BET_COIN(menu::MenuItem* menuitem, int active, int max, int x, int y);
    static void MATERIEL_POKER_SELECT_CARD(menu::MenuItem* menuitem, int active);
    static void MATERIEL_POKER_SELECT_DEAL(menu::MenuItem* menuitem, int active);
    static void MATERIEL_POKER_BET_COIN(menu::MenuItem* menuitem, int active);
    static void MATERIEL_POKER_HI_AND_LOW(menu::MenuItem* menuitem, int active);
    static void MATERIEL_MONSTER_LIST(menu::MenuItem* menuitem, int active, int max);
    static void MATERIEL_GET_UPDOWN(menu::MenuItem* menuitem);
    static void MATERIEL_DIARY_MENU(menu::MenuItem* menuitem, int num);
    static void MATERIEL_DIARY_SELECT(menu::MenuItem* menuitem);
    static void MATERIEL_DIARY_LOAD(menu::MenuItem* menuitem);
    static void MATERIEL_DIARY_RESUME(menu::MenuItem* menuitem);
    static void MATERIEL_KEYBOARD_JAP(menu::MenuItem* menuitem);
    static void MATERIEL_KEYBOARD_JAP_MESSAGE(menu::MenuItem* menuitem);
    static void MATERIEL_RACE_ENTRANCE(menu::MenuItem* menuitem);
    static void MATERIEL_SEXUALITY(menu::MenuItem* menuitem);
    static void MATERIEL_CHOICE_SLIME(menu::MenuItem* menuitem, int max);
    static void MATERIEL_RACE_ODDS_2x6(menu::MenuItem* menuitem, int max);
    static void MATERIEL_RACE_ODDS_2x8(menu::MenuItem* menuitem, int max);
    static void MATERIEL_SLIME_TOUCH(menu::MenuItem* menuitem);
    static void MATERIEL_CELECT_BUY(menu::MenuItem* menuitem, int active, int max);
    static void MATERIEL_ICON32_5x2(menu::MenuItem* menuitem, int active, int max);
    static void MATERIEL_MONEY_SELECT(menu::MenuItem* menuitem, int active, int digit);
    static void MATERIEL_COIN_SELECT(menu::MenuItem* menuitem, int active, int digit);
    static void MATERIEL_PICTUREBOOK_SELECT(menu::MenuItem* menuitem, int active, int max);
    static void MATERIEL_PICTUREBOOK_MONSTERANIME(menu::MenuItem* menuitem);
    static void MATERIEL_CANCEL(menu::MenuItem* menuitem);
    static void shopSellQuantity(menu::MenuItem* menuitem, int active);
    static void surechigaiRoot(menu::MenuItem* menuitem, int active);
    static void surechigaiViewCommand(menu::MenuItem* menuitem, int active);
    static void suretigaiSelectChiaus(menu::MenuItem* menuitem, int active, int max);
    static void surechigaiSelectObject(menu::MenuItem* menuitem, int active, int max);
    static void surechigaiSelectList(menu::MenuItem* menuitem, int active, int max);
    static void surechigaiSelectPrice(menu::MenuItem* menuitem, int active);
    static void MATERIEL_SUGOROKU_ROOT(menu::MenuItem* menuitem, int active);
    static void MATERIEL_LUIDA_ROOT(menu::MenuItem* menuitem, int active);
    static void surechigaiSelectSkill(menu::MenuItem* menuitem, int active);
};

}  // namespace menu
