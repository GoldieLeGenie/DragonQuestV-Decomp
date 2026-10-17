#pragma once
#include <globaldefs.h>

// window types / message ids picked by the town menu window functions
struct UnkTownMenuDrawPair {
    int first;
    int second;
};

// windows of the town menus
void unkfunc_02172ef0(int messageOpen);                                       // town menu root windows
void unkfunc_02172f1c(int messageOpen);                                       // item character selection window
void unkfunc_02172f6c(int messageOpen, int page);                             // item list window
void unkfunc_02173098(int messageOpen, int a1, int itemID, int page);          // item command window
void unkfunc_02173194(int messageOpen, int itemID, int page);                 // item target selection window
void unkfunc_021731f8(int messageOpen);                                       // give target selection window
void unkfunc_021732b0(int messageOpen);                                       // exchanged item selection window
void unkfunc_021733b0(int messageOpen);                                       // spell caster selection window
void unkfunc_02173400(int messageOpen);                                       // spell list window
void unkfunc_02173478(int messageOpen, int page);                             // return spell destination window
void unkfunc_021734f8(int messageOpen, int page);                             // spell target selection window
void unkfunc_02173560(int page);                                              // status window, strength page
void unkfunc_02173590(int page);                                              // status window, equipment page
void unkfunc_021735b8(int chara, int flag, int page);                         // status window, spell pages
void unkfunc_021735d8(int page);                                              // status window, bag page
void unkfunc_021735ec(int messageOpen);                                       // misc menu windows
void unkfunc_02173610(int messageOpen, int mode);                             // item sorting window
void unkfunc_02173720(char* playerList, int chara);                           // tactics character selection window
void unkfunc_02173770(char* playerList, int chara, int active);               // tactics selection window
void unkfunc_021737e4(char* allocation, char* list, int active, int count); // party order window
void unkfunc_0217386c(int messageOpen);                                       // equipment character selection window
void unkfunc_02173894(short* itemPosList, int itemCount, int itemType, int itemListActive); // equipment item window
void unkfunc_02173940(int type);                                              // town map shop list page
void unkfunc_02173948(int chara, int a, int b, int c);
void unkfunc_0217399c(int chara);
void unkfunc_021739d8(int chara, int page);
void unkfunc_02173a18(int chara);
void unkfunc_02173a58(int a, int b);
void unkfunc_02173ac8(int page);
void unkfunc_02173c50(int chara, int flag);
void unkfunc_02173c80(int chara, int page, int flag);
void unkfunc_02173e24(int page);
void unkfunc_02173e7c(int page);
void unkfunc_02173e94(int chara);
void unkfunc_02173efc();
void unkfunc_02173f68();
void unkfunc_02173fa4(char* list, int mode);
void unkfunc_02174124(char* list);
void unkfunc_02174170(int chara, short* itemPosList, int itemCount, int page);
void unkfunc_02174248(int chara, int activeItem, int itemType, int itemListActive);
void unkfunc_0217428c();                                                     // settings window
