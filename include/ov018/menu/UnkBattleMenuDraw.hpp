#pragma once
#include <globaldefs.h>

namespace status {
    struct HaveStatusInfo;
    struct BaseHaveItem;
    struct HaveAction;
}

// battle menu draw helpers
void drawBattleCommandIcons(int command0, int command1, int command2, int command3);   // command icons
void drawBattleMemberHpPercent(int x, int y, int hp, status::HaveStatusInfo* info);         // HP gauge
void drawBattleActiveMember(status::HaveStatusInfo* info, int hp, int flag);
void drawMonsterNamePlates(int group);                                                  // monster name plates
void drawBattleCommandIcon(int command, int x, int y, int flag);                        // command icon
void drawBattleHelpMessage(int x, int y, int message);
void drawBattlePageNumber(int x, int y, int max, int page);                            // page number
void drawBattleItemEntry(int x, int y, int item, int flag);                           // item name
void drawBattleActionName(int x, int y, int action);                                   // action name
void drawBattleMemberStatusPanel(status::HaveStatusInfo* info, int index);                    // party member status
void drawBattleCharaStatus(int x, int y, status::HaveStatusInfo* info);                 // status window
void drawBattleMemberSelectList(int* list, int count, int page);                             // member icons
void drawBattleMemberConditionMarks(status::HaveStatusInfo* info, int x, int y);                 // condition marks
void drawBattleCancelButton();
void drawBattleTopStatusWindow(status::HaveStatusInfo* info, int a, int b, int c, int index);
void drawBattleActionHistory(int index, int value, int message, int color);
void drawBattleMemberIconInSlot(int x, int y, int value, int type);
void drawBattleMpCost(int mp, int useMp);                                          // MP cost
void drawFriendSelectPageFrame(int page, int max);
void drawFriendStatusProfile(int hp, int mp, int hpMax, int mpMax, int sex, int level, int ctrl, int monster);
void drawFriendStatusAbilities(short hp, unsigned short hpMax, unsigned short strength, unsigned short agility, unsigned short protection, unsigned short wisdom, unsigned short luck, unsigned short attack, unsigned short defence);
void drawBattleMemberIcon(int x, int y, int icon);
void drawFriendStatusItems(status::BaseHaveItem* items, int hp, int hpMax);
void drawFriendStatusSpells(status::HaveAction* actions, int hp, int hpMax);
void drawBattleMemberFace(int x, int y, status::HaveStatusInfo* info, int flag);       // face
int getBattleHpColorIndexByHp(int hpMax, int hp);                                           // HP color
int BattleDrawParts_getStatusColor(status::HaveStatusInfo& statusInfo);
void drawBattleRootMenu();
void drawBattleActionMenu(int x);
void drawAttackCancelMenu();
void drawItemMenu(int* items, int count, int page);
void drawItemUseEquipMenu(int* items, int count, int page);
void drawItemUseOnPartyMenu();
void drawItemUseOnEnemyMenu();
void drawMagicMenu(int* actions, int count, int page);
void drawAttackTargetMenu(int group);
void drawMagicOnEnemyMenu();
void drawMagicOnPartyMenu();
void drawTacticsMemberMenu();
void drawTacticsSelectMenu();
void drawFormationMenu();
void drawFormationChangeMemberMenu();
void drawFormationChangeTargetMenu(int* list, int count, int page);
void drawFormationAllMenu(int* list, int count, int* select, int selectCount);
void drawPartyHpPercents();
void drawFriendSelectMenu(int page, int maxPage, int player);
void drawEnemyTargetSelect(int group);
void drawPartyTargetSelect();
void drawItemList(int* items, int count, int page);
void drawAttackCommandButton();
void drawMagicCommandHeader();
void drawItemCommandHeader();
void drawTacticsCommandButton();
void drawFormationCommandButton();
void drawFormationMemberIcons(int* list, int count);
void drawSelectedCharaHp(int chara);
void drawMemberIcon(int x, int y, int index);
void drawBattleHistory(int chara);
void drawCharaBattleSpellList(int* actions, int count, int chara);
