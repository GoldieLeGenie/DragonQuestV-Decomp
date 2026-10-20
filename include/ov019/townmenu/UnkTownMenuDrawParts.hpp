#pragma once
#include <globaldefs.h>

// parts of the town menu windows (names, icons, values, arrows...)
void drawRootMenuButtonFrames(int x, int y, int flag);
void unkfunc_021715fc(int type, int sub);
void unkfunc_021716f0(int chara, int x, int y);
void unkfunc_021716f8(int chara);
void unkfunc_0217178c();
void unkfunc_02171820(int chara, int a, int b, int c);
void unkfunc_02171914(int chara);
void unkfunc_021719e0(int itemID, int x, int y);
void unkfunc_02171a30(int itemID, int index, int x, int y);
void unkfunc_02171a88(int index);
void unkfunc_02171ad4(int x, int max, int page, int flag);
void drawPageIndicatorWide(int x, int max, int page);
void unkfunc_02171b70(int id, int a, int b);
void unkfunc_02171bd4(int itemID);
void unkfunc_02171c0c(int chara, int itemID, int equipIndex, int fukuro, int flag, int mode);
void unkfunc_02171d90(int commandFlag);
void unkfunc_02171eb4(int a, int b);
void unkfunc_02172094(int chara, int index, int page);
void unkfunc_021721d4(int chara, int a, int b);
void unkfunc_02172228(int chara);
void unkfunc_021722a8(int x, int y, int text, int chara);
void unkfunc_021722d8(int page);
void unkfunc_02172390(int a, int x, int y, int chara);
void drawMenuHeaderText(int a, int b, int text);
void drawCommandLabel(int x, int y, int text);
void unkfunc_0217243c(int chara, int a, int y);
void unkfunc_02172498();
void unkfunc_021724f4(char* allocation, char* list, int count);
void unkfunc_021725bc(char* allocation);
void unkfunc_0217269c(int type);
void unkfunc_021726d0(int itemType);
void unkfunc_02172728();
void unkfunc_02172804();
void unkfunc_0217283c(int x, int y);
void unkfunc_02172850(int chara, int itemID, int flag);
void unkfunc_021729dc(int flag);
void unkfunc_02172a60(int flag);
void unkfunc_02172ad0(int type);
int unkfunc_02172c00(int chara);                                 // text color of a character
int unkfunc_02172c08(int chara, int itemID, int* values);         // status change of an item
int unkfunc_02172da0(int chara, int equipIndex, int* values);     // status change of an equipment slot
