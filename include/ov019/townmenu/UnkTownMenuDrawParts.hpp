#pragma once
#include <globaldefs.h>

// parts of the town menu windows (names, icons, values, arrows...)
void drawRootMenuButtonFrames(int x, int y, int flag);
void drawRootMenuCommands(int type, int sub);
void drawPartyMemberIcon(int chara, int x, int y);
void drawCharaItemNameList(int chara);
void drawBagItemNameList();
void drawActiveCharaNameBar(int chara, int a, int b, int c);
void drawTargetCharaNameBar(int chara);
void drawItemSlot(int itemID, int x, int y);
void drawBagItemSlot(int itemID, int index, int x, int y);
void drawItemEquippedMark(int index);
void drawPageIndicator(int x, int max, int page, int flag);
void drawPageIndicatorWide(int x, int max, int page);
void drawMenuDescription(int id, int a, int b);
void drawItemUsageInfo(int itemID);
void drawEquipCompareWindow(int chara, int itemID, int equipIndex, int fukuro, int flag, int mode);
void drawItemUseCommands(int commandFlag);
void drawPartyIconRow(int a, int b);
void drawCharaSummaryPanel(int chara, int index, int page);
void drawCasterMpBar(int chara, int a, int b);
void drawTownSpellList(int chara);
void drawSpellName(int x, int y, int text, int chara);
void drawRuraTownList(int page);
void drawCarriageOrderNumber(int a, int x, int y, int chara);
void drawMenuHeaderText(int a, int b, int text);
void drawCommandLabel(int x, int y, int text);
void drawCharaTacticsRow(int chara, int a, int y);
void drawTacticsOptions();
void drawShiftPartyIconList(char* allocation, char* list, int count);
void drawShiftPartyFrontSlots(char* allocation);
void drawOperationTitle(int type);
void drawEquipListCaption(int itemType);
void drawSettingScreenLabels();
void unkfunc_02172804();
void drawTownCommandCursor(int x, int y);
void drawItemTargetInfo(int chara, int itemID, int flag);
void drawChooseCharaPrompt(int flag);
void drawSpellOrTownSelectPrompt(int flag);
void drawTownShopGoods(int type);
int getCharaTextColorIndex(int chara);                                 // text color of a character
int getEquipCompareValues(int chara, int itemID, int* values);         // status change of an item
int getEquipSlotCompareValues(int chara, int equipIndex, int* values);     // status change of an equipment slot
