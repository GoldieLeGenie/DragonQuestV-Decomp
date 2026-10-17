#pragma once
#include <globaldefs.h>

// Status windows of the town menus drawn with menu parts (frames, names, HP/MP, equipment, magic, money)
void unkfunc_0201b0f8(int x, int y, int w, int h, int lineY);  // window frame (+ separator line)
void unkfunc_0201b128(int x, int y, int w);                     // separator line
void unkfunc_0201b158();                                        // frames of the party members
int getActorConditionColor(int actor);                          // 0 normal, 1 near death, 2 dead
void unkfunc_0201b1cc(int x, int y, int type);                  // gold (0), coins (1) or medals (2)
void unkfunc_0201b2a8(int activeChara, int mode);               // status of one member
void unkfunc_0201b3c8(int icon, int x, int y);                  // character icon
void unkfunc_0201b3e4(int activeChara, int x, int y);           // character icon with its condition marks
void unkfunc_0201b4d4(int activeChara, int flag, int ctrl);     // detailed status
void unkfunc_0201b6b4(int activeChara, int ctrl);               // abilities
void unkfunc_0201b7dc(int activeChara, int mode);               // equipment
void unkfunc_0201ba48(int activeChara, int mode);               // spells
void unkfunc_0201bbb4();                                        // money and play time
void unkfunc_0201bcc8(int mode);                                // HP/MP of the party
void unkfunc_0201be24(int mode);                                // attack/defence of the party
void unkfunc_0201bfbc(int activeChara);                         // items of a member
void unkfunc_0201c084(int activeChara, int ctrl);               // spells of a member
void unkfunc_0201c188(int activeChara, int pos);                // member window
void unkfunc_0201c218(int activeChara, int x, int y);           // HP/MP of a member
void unkfunc_0201c29c(int activeChara, int x, int y);           // attack/defence of a member
void unkfunc_0201c300(int activeChara, int pos, int w, int y);  // level of a member
