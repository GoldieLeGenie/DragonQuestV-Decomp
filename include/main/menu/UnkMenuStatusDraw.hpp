#pragma once
#include <globaldefs.h>

// Status windows of the town menus drawn with menu parts (frames, names, HP/MP, equipment, magic, money)
void drawMenuFrame(int x, int y, int w, int h, int lineY);  // window frame (+ separator line)
void drawMenuFrameLine(int x, int y, int w);                     // separator line
void drawPartyStatusWindows();                                        // frames of the party members
int getActorConditionColor(int actor);                          // 0 normal, 1 near death, 2 dead
void drawMoneyWindow(int x, int y, int type);                  // gold (0), coins (1) or medals (2)
void drawCharaStatusWindow(int activeChara, int mode);               // status of one member
void drawCharaIcon(int icon, int x, int y);                  // character icon
void drawCharaIconWithCondition(int activeChara, int x, int y);           // character icon with its condition marks
void drawCharaDetailWindow(int activeChara, int flag, int ctrl);     // detailed status
void drawCharaAbilityWindow(int activeChara, int ctrl);               // abilities
void drawCharaEquipWindow(int activeChara, int mode);               // equipment
void drawCharaSpellWindow(int activeChara, int mode);               // spells
void drawMoneyTimeWindow();                                        // money and play time
void drawPartyHpMpWindows(int mode);                                // HP/MP of the party
void drawPartyAttackDefenceWindows(int mode);                                // attack/defence of the party
void drawCharaItemWindow(int activeChara);                         // items of a member
void drawCharaSpellListWindow(int activeChara, int ctrl);               // spells of a member
void drawPartyMemberWindow(int activeChara, int pos);                // member window
void drawCharaHpMp(int activeChara, int x, int y);           // HP/MP of a member
void drawCharaAttackDefence(int activeChara, int x, int y);           // attack/defence of a member
void drawCharaLevel(int activeChara, int pos, int w, int y);  // level of a member
