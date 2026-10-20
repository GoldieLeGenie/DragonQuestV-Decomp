#pragma once
#include <globaldefs.h>

// window types / message ids picked by the town menu window functions
struct UnkTownMenuDrawPair {
    int first;
    int second;
};

// windows of the town menus
void drawRootMenuScreen(int messageOpen);                                       // town menu root windows
void drawItemCharaSelectScreen(int messageOpen);                                       // item character selection window
void drawItemSelectScreen(int messageOpen, int page);                             // item list window
void drawItemCommandScreen(int messageOpen, int a1, int itemID, int page);          // item command window
void drawItemUseTargetScreen(int messageOpen, int itemID, int page);                 // item target selection window
void drawItemTargetCharaScreen(int messageOpen);                                       // give target selection window
void drawItemTargetItemScreen(int messageOpen);                                       // exchanged item selection window
void drawMagicCasterSelectScreen(int messageOpen);                                       // spell caster selection window
void drawMagicSpellSelectScreen(int messageOpen);                                       // spell list window
void drawWarpTownSelectScreen(int messageOpen, int page);                             // return spell destination window
void drawMagicTargetSelectScreen(int messageOpen, int page);                             // spell target selection window
void drawStatusMainPage(int page);                                              // status window, strength page
void drawStatusSpellPage(int page);                                              // status window, equipment page
void drawStatusPartySummaryScreen(int chara, int flag, int page);                         // status window, spell pages
void drawStatusMoneyScreen(int page);                                              // status window, bag page
void drawOperationRootScreen(int messageOpen);                                       // misc menu windows
void drawSortItemScreen(int messageOpen, int mode);                             // item sorting window
void drawTacticsScreen(char* playerList, int chara);                           // tactics character selection window
void drawTacticsSelectScreen(char* playerList, int chara, int active);               // tactics selection window
void drawShiftPartyScreen(char* allocation, char* list, int active, int count); // party order window
void drawEquipCharaSelectScreen(int messageOpen);                                       // equipment character selection window
void drawEquipScreen(short* itemPosList, int itemCount, int itemType, int itemListActive); // equipment item window
void drawTownShopScreen(int type);                                              // town map shop list page
void drawItemMenuHeader(int chara, int a, int b, int c);
void drawMagicMenuHeader(int chara);
void drawStatusMenuHeader(int chara, int page);
void drawEquipMenuHeader(int chara);
void drawCharaSelectWindow(int a, int b);
void drawStatusPartyIcons(int page);
void drawCharaItemList(int chara, int flag);
void drawItemListPage(int chara, int page, int flag);
void drawPartyHpMpList(int page);
void drawPartyHpMpListBattle(int page);
void drawFieldSpellList(int chara);
void drawOperationCommandList();
void drawSortSackOptions();
void drawPartyOrderIcons(char* list, int mode);
void drawPartyTacticsList(char* list);
void drawEquipItemList(int chara, short* itemPosList, int itemCount, int page);
void drawEquipItemInfo(int chara, int activeItem, int itemType, int itemListActive);
void drawSettingScreen();                                                     // settings window
