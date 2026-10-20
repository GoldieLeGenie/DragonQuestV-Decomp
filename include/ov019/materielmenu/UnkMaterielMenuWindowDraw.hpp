#pragma once
#include <globaldefs.h>

// materiel menu windows drawn by the shop, casino, museum... menus
void drawShopRootScreen();
void drawShopBuyScreen(int type);
void drawShopWhoseScreen(int type, int itemID);
void drawShopWhoSellScreen();
void drawShopSellItemScreen(int fukuro);
void drawShopSellSackScreen();
void drawShopSellQuantityScreen(int value);
void drawShopScreen();
void drawChurchScreen(int index, int flag);
void drawChurchMiracleScreen();
void drawChangeGiftScreen();
void drawBankRootScreen();
void drawBankAmountScreen(int mode, int flag, int value);
void drawCoinSaleroomScreen(int value, int flag);
void drawPokerBetCoinScreen(int coin, int bet, int type);
void drawPokerChangeCardScreen(int mode, int coin, int bet, int* flags, int flag);
void drawPokerHighLowScreen(int mode, int coin, int bet, int flag);
void drawSlotCoins(int value, int flag);
void drawCoinsAndGold(int value, int count);
void drawRaceEntranceCommands();
void drawChoiceSlimeScreen(int chara);
void drawRaceOddsScreen(int mode, int flag);
void unkfunc_0217c2a4();
void drawSlimeTouchCommands();
void drawSlimeTouchRanking();
void drawMonsterBookScreen();
void drawMonsterBookDetailScreen(int index);
void drawJisanRootScreen();
void drawMemberStatusScreen(int mode, int page, int maxPage, int type);
void drawMemberChangeScreen(int page, int maxPage, int type, int monster);
void drawChangeNameScreen(int mode, int page, int maxPage, int type, short* list, int total);
void drawTagModeRootScreen();
void drawTagModeAmbassadorScreen(int mode, int icon, int type, int value);
void drawTagModeTenantScreen(int page, int value, int index, int icon, int flag);
void drawTagModeEditScreen(int mode, int icon, int page, int value);
void drawTagModeNameEditScreen(int mode, int flag, int icon);
void drawMoneyAndPartyWindows();
void drawSugorokuRootScreen();
void drawSugorokuStatusScreen(int mode);
