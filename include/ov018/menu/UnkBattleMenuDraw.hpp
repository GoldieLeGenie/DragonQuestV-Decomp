#pragma once
#include <globaldefs.h>

namespace status {
    struct HaveStatusInfo;
    struct BaseHaveItem;
    struct HaveAction;
}

// battle menu draw helpers
void unkfunc_0216f204(int command0, int command1, int command2, int command3);   // command icons
void unkfunc_0216f23c(int x, int y, int hp, status::HaveStatusInfo* info);         // HP gauge
void unkfunc_0216f2c8(status::HaveStatusInfo* info, int hp, int flag);
void unkfunc_0216f2ec(int group);                                                  // monster name plates
void unkfunc_0216f378(int command, int x, int y, int flag);                        // command icon
void unkfunc_0216f4b0(int x, int y, int message);
void unkfunc_0216f4d8(int x, int y, int max, int page);                            // page number
void unkfunc_0216f520(int x, int y, int item, int flag);                           // item name
void unkfunc_0216f570(int x, int y, int action);                                   // action name
void unkfunc_0216f5a4(status::HaveStatusInfo* info, int index);                    // party member status
void unkfunc_0216f694(int x, int y, status::HaveStatusInfo* info);                 // status window
void unkfunc_0216f78c(int* list, int count, int page);                             // member icons
void unkfunc_0216f82c(status::HaveStatusInfo* info, int x, int y);                 // condition marks
void unkfunc_0216f908();
void unkfunc_0216f91c(status::HaveStatusInfo* info, int a, int b, int c, int index);
void unkfunc_0216f9f0(int index, int value, int message, int color);
void unkfunc_0216fa74(int x, int y, int value, int type);
void unkfunc_0216faec(int mp, int useMp);                                          // MP cost
void unkfunc_0216fb38(int page, int max);
void unkfunc_0216fb94(int hp, int mp, int hpMax, int mpMax, int sex, int level, int ctrl, int monster);
void unkfunc_0216fcb8(short hp, unsigned short hpMax, unsigned short strength, unsigned short agility, unsigned short protection, unsigned short wisdom, unsigned short luck, unsigned short attack, unsigned short defence);
void unkfunc_0216fd6c(int x, int y, int icon);
void unkfunc_0216fd88(status::BaseHaveItem* items, int hp, int hpMax);
void unkfunc_0216fe48(status::HaveAction* actions, int hp, int hpMax);
void unkfunc_0216fedc(int x, int y, status::HaveStatusInfo* info, int flag);       // face
int unkfunc_0216ff50(int hpMax, int hp);                                           // HP color
int BattleDrawParts_getStatusColor(status::HaveStatusInfo& statusInfo);
void unkfunc_0216ff70();
void unkfunc_0216ff80(int x);
void unkfunc_0216fff0();
void unkfunc_0216fff8(int* items, int count, int page);
void unkfunc_02170010(int* items, int count, int page);
void unkfunc_02170078();
void unkfunc_02170084();
void unkfunc_02170094(int* actions, int count, int page);
void unkfunc_0217008c(int group);
void unkfunc_02170148();
void unkfunc_02170150();
void unkfunc_0217015c();
void unkfunc_02170210();
void unkfunc_02170324();
void unkfunc_02170364();
void unkfunc_021703dc(int* list, int count, int page);
void unkfunc_0217043c(int* list, int count, int* select, int selectCount);
void unkfunc_02170580();
void unkfunc_021705c0(int page, int maxPage, int player);
void unkfunc_0217082c(int group);
void unkfunc_02170860();
void unkfunc_02170894(int* items, int count, int page);
void unkfunc_02170950();
void unkfunc_02170960();
void unkfunc_021709fc();
void unkfunc_02170a30();
void unkfunc_02170a40();
void unkfunc_02170a50(int* list, int count);
void unkfunc_02170ad0(int chara);
void unkfunc_02170b18(int x, int y, int index);
void unkfunc_02170bcc(int chara);
void unkfunc_02170c78(int* actions, int count, int chara);
