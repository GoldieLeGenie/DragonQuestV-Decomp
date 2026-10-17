#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/status/HaveStatusInfo.hpp"

namespace menu {
    struct TOUCHRECT {
        short x;                                // 0x0
        short y;                                // 0x2
        short width;                            // 0x4
        short height;                           // 0x6
        short group;                            // 0x8
    };
}

struct BattleMenu_ROOT : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    menu::MenuItem cancelItem_;                 // 0x80
    UnkCursorMoveGridLoop navigator_;           // 0xE4
    short unk_f0;                               // 0xF0
    int unk_f4;                                 // 0xF4

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

struct BattleMenu_FRIEND_ENTRANCE : menu::MenuBase {
    enum MENU_MODE {
        MODE_START = 0,
        MODE_GOOD_BYE = 1,
        MODE_IN_PARTY = 2,
        MODE_SELECT = 3,
        MODE_IS_CANCEL = 4,
        MODE_IS_LAST = 5,
        MODE_IS_LEAVE = 6,
        MODE_LEAVE_OLD = 7,
        MODE_LEAVE_NEW = 8,
        MODE_EXEC = 9,
        MODE_END = 10,
    };

    int monster_;                               // 0x1C
    int monsterCtrl_;                           // 0x20
    int monsterArray_;                          // 0x24
    int friend_;                                // 0x28
    int friendIndex_;                           // 0x2C
    int friendCtrl_;                            // 0x30
    int bashaFlag_;                             // 0x34
    int partyFlag_;                             // 0x38
    int oldLeaveFlag_;                          // 0x3C
    MENU_MODE mode_;                            // 0x40

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void commandUpdate();
    void unkfunc_02171178();
    int unkfunc_021711ec(int num);
    int unkfunc_02171244(int num);
};

// selection of the friend monster that leaves the party
struct UnkBattleMenuFriendSelect : menu::MenuBase {
    int unk_1c;                                 // 0x1C
    int unk_20;                                 // 0x20
    int unk_24;                                 // 0x24
    int unk_28;                                 // 0x28
    int unk_2c[8];                              // 0x2C
    int unk_4c;                                 // 0x4C
    int unk_50;                                 // 0x50
    int unk_54;                                 // 0x54
    int unk_58;                                 // 0x58
    menu::MenuItem menuItem_;                   // 0x5C
    UnkCursorMoveGridLoop navigator_;           // 0xC0

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_021713c4();
};

struct BattleMenu_StadiumAbort : menu::MenuBase {
    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

struct BattleMenuSub_HISTORY : menu::MenuBase {
    int select_;                                // 0x1C
    int history_;                               // 0x20
    int update_;                                // 0x24
    int isRedraw_;                              // 0x28
    int commandChara_;                          // 0x2C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setUpdate(bool flag);
};

struct BattleMenu_NGMESSAGE : menu::MenuBase {
    enum RETURN_MENU {
        MENU_ROOT = 0,
        MENU_ACTIONMENU = 1,
    };

    int messageID_;                             // 0x1C
    int returnPos_;                             // 0x20
    RETURN_MENU returnMenu_;                    // 0x24

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

struct BattleMenu_ACTIONMENU : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    menu::MenuItem pageItem_;                   // 0x80
    menu::MenuItem cancelItem_;                 // 0xE4
    int activeCharacter_;                       // 0x148
    int unk_14c;                                // 0x14C
    UnkCursorMoveGridLoop navigator_;           // 0x150

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int getUseActionNum(int& index);
    void selectAttack();
    void selectMagic();
    void selectItem();
    void selectDefence();
    bool isWeaponAll(int weapon);
};

struct BattleMenu_ATTACK : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    menu::MenuItem cancelItem_;                 // 0x80
    int enemyMaxNum_;                           // 0xE4
    int unk_e8;                                 // 0xE8
    int unk_ec;                                 // 0xEC
    int unk_f0;                                 // 0xF0
    int unk_f4;                                 // 0xF4
    menu::TOUCHRECT touchRect_[12];             // 0xF8

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_02175df0(int index);
    void unkfunc_02175e34(int index);
    void unkfunc_02175e7c();
    bool unkfunc_02175f50();
};

// cancel button shown with the attack target selection
struct UnkBattleMenuAttackCancel : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    int unk_80;                                 // 0x80
    int unk_84;                                 // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_021726f0();
};

struct BattleMenu_ITEM : menu::MenuBase {
    int activeChara_;                           // 0x1C
    int unk_20;                                 // 0x20
    menu::MenuItem menuItem_;                   // 0x24
    menu::MenuItem cancelItem_;                 // 0x88
    menu::MenuItem pageItem_;                   // 0xEC
    UnkCursorMoveGridLoop navigator_;           // 0x150

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectUseItem();
    bool unkfunc_02172ba8();
};

struct UnkBattleMenuEquipItem : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    menu::MenuItem cancelItem_;                 // 0x80
    menu::MenuItem unk_e4;                      // 0xE4
    int unk_148;                                // 0x148
    int unk_14c;                                // 0x14C
    int unk_150;                                // 0x150
    int unk_154;                                // 0x154

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int unkfunc_02172d4c();
    void unkfunc_02172d78();
    void selectUseItem();
    void unkfunc_02172fc8();
    void unkfunc_0217300c();
};

struct BattleMenu_ITEMUSE2ENEMY : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    char unk_80[0xc8];                          // 0x80
    int unk_148;                                // 0x148
    int unk_14c;                                // 0x14C
    int unk_150;                                // 0x150
    int unk_154;                                // 0x154
    int unk_158;                                // 0x158
    int unk_15c;                                // 0x15C
    int unk_160;                                // 0x160

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_021730b8();
    void unkfunc_0217310c();
    int unkfunc_02173134();
    void unkfunc_0217316c(int chara, int item);
};

struct BattleMenu_ITEMUSE2PARTY : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    menu::MenuItem cancelItem_;                 // 0x80
    int unk_e4;                                 // 0xE4
    int unk_e8;                                 // 0xE8
    int unk_ec;                                 // 0xEC
    UnkCursorMoveGridLoop navigator_;           // 0xF0

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool unkfunc_02173308(int item);
};

struct BattleMenu_MAGIC : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    menu::MenuItem cancelItem_;                 // 0x80
    menu::MenuItem pageItem_;                   // 0xE4
    UnkCursorMoveGridLoop navigator_;           // 0x148
    int count_;                                 // 0x154
    int haveAction_[30];                        // 0x158
    int haveActionIndex_[30];                   // 0x1D0

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setActiveMagicPos(int pos);
    void unkfunc_02173adc(int action, int magic);
    void unkfunc_02173bd8();
    void setMagicTargetFree(int magic);
};

struct BattleMenu_MAGIC2ENEMY : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    int activeMagic_;                           // 0x80
    int activeMagicPos_;                        // 0x84
    int activeMagicIndex_;                      // 0x88

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

struct BattleMenu_MAGIC2PARTY : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    menu::MenuItem cancelItem_;                 // 0x80
    int unk_e4;                                 // 0xE4
    int unk_e8;                                 // 0xE8
    int m_magic;                                // 0xEC
    int activeMagicPos_;                        // 0xF0
    UnkCursorMoveGridLoop navigator_;           // 0xF4

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool unkfunc_02173ed4(int action);
};

struct BattleMenu_ARRAYMENU : menu::MenuBase {
    enum CHANGE_RESULT {
        CHANGE_ENABLE = 0,
        CHANGE_DISABLE = 1,
        CHANGE_BLOCK = 2,
    };

    int unk_1c;                                 // 0x1C
    menu::MenuItem menuItem_;                   // 0x20
    menu::MenuItem cancelItem_;                 // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    CHANGE_RESULT isChangeling();
    CHANGE_RESULT isBlocking();
    void changeUpdate();
};

struct BattleMenu_ARRAY_ALL : menu::MenuBase {
    int unk_1c[4];                              // 0x1C
    int unk_2c;                                 // 0x2C
    int unk_30;                                 // 0x30
    int unk_34[25];                             // 0x34
    menu::MenuItem menuItem_;                   // 0x98
    menu::MenuItem cancelItem_;                 // 0xFC
    UnkCursorMoveGridLoop navigator_;           // 0x160

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_02171cc0();
    void unkfunc_02171d9c();
    void unkfunc_02171f9c();
    bool unkfunc_02171fb8();
    int unkfunc_02171fec();
    void unkfunc_02172008(int index);
    void unkfunc_02172034();
    void unkfunc_0217206c();
    int unkfunc_021720bc();
};

struct BattleMenu_ARRAY_CHANGE : menu::MenuBase {
    int unk_1c;                                 // 0x1C
    int unk_20;                                 // 0x20
    int unk_24;                                 // 0x24
    menu::MenuItem menuItem_;                   // 0x28
    menu::MenuItem unk_8c;                      // 0x8C
    menu::MenuItem unk_f0;                      // 0xF0
    menu::MenuItem cancelItem_;                 // 0x154
    UnkCursorMoveGridLoop unk_1b8;              // 0x1B8
    UnkCursorMoveGridLoop unk_1c4;              // 0x1C4

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int unkfunc_02172454();
    int unkfunc_0217249c();
    int unkfunc_0217262c();
};

struct BattleMenu_TACTICSMENU : menu::MenuBase {
    int unk_1c;                                 // 0x1C
    int unk_20;                                 // 0x20
    int unk_24;                                 // 0x24
    int unk_28;                                 // 0x28
    int unk_2c[10];                             // 0x2C
    int unk_54;                                 // 0x54
    int unk_58[25];                             // 0x58
    menu::MenuItem menuItem_;                   // 0xBC
    menu::MenuItem unk_120;                     // 0x120
    menu::MenuItem cancelItem_;                 // 0x184
    UnkCursorMoveGridLoop unk_1e8;              // 0x1E8
    UnkCursorMoveGridLoop unk_1f4;              // 0x1F4

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    int unkfunc_02174f78();
    void unkfunc_02174fd4();
    int unkfunc_0217503c();
    void unkfunc_02175088();
    void unkfunc_021750cc();
};

// test menu with one item
struct UnkBattleMenuTest : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

struct BattleMenuJudge {
    int turnCount_;                             // 0x00
    int prevturnCount_;                         // 0x04
    int unk_08;                                 // 0x08
    int minadeinFlag_;                          // 0x0C
    menu::TOUCHRECT touchRect_[12];             // 0x10

    static BattleMenuJudge m_singleton;

    static BattleMenuJudge* getSingleton();
    void turnSetup();
    void baseSetup();
    void setAttack(int group);
    void setMagicEnemy(int magic, int group);
    void setMagicParty(int magic, int target);
    void setItemEnemy(int item, int group);
    void setItemEnemyAll(int item);
    void setItemParty(int item, int target);
    void setItemPartyAll(int item);
    bool judgeNextChara();
    bool judgeBackChara();
    void backActionMenu(int page);
    bool judgeBattleArrayChange();
    int getPlayerIndex();
    void setNextPlayer();
    void setPrevPlayer();
    int getMonsterTouchRect(menu::TOUCHRECT* rect);
    int getLiveMonsterID();
    bool isCommandingPlayer(int index);
    void setMinadeinFlag(bool flag);
};

struct BattleMenuPlayerControl {
    struct BATTLEMENU_HISTORY {
        int index;                              // 0x00
        int special;                            // 0x04
        int firstHistory;                       // 0x08
        int secondHistory;                      // 0x0C
        short item;                             // 0x10
        short monster;                          // 0x12
    };

    struct BATTLEMENU_STATUS {
        int condition;                          // 0x00
        int conditionFlag;                      // 0x04
        short hp;                               // 0x08
        short mp;                               // 0x0A
        short Lv;                               // 0x0C
        short color;                            // 0x0E
    };

    int activeChara_;                           // 0x000
    int targetChara_;                           // 0x004
    int activeItem_;                            // 0x008
    int activeMagic_;                           // 0x00C
    int tacticsSex_;                            // 0x010
    BATTLEMENU_HISTORY historyData_[4];         // 0x014
    BATTLEMENU_STATUS statusData_[4];           // 0x064
    unsigned char mosyasA[256];                 // 0x0A4
    unsigned char mosyasB[256];                 // 0x1A4
    unsigned char mosyas[256];                  // 0x2A4

    static BattleMenuPlayerControl m_singleton;

    static BattleMenuPlayerControl* getSingleton();
    int getPlayerItemId();
    bool flashStatus(int memberNum);
    bool flashHP(int memberNum);
    bool flashHPColor(int memberNum);
    bool flashMP(int memberNum);
    bool flashCondition(int memberNum);
    int isFlashCondition(int memberNum, status::HaveStatusInfo::MenuStatusChange menuStatus);
    bool resetPlayerHistory(int playerNum);
    bool makePlayerHistory();
    void clear();
    void allClear();
    void setTargetChara(int target);
    void setActiveItem(int item);
    void setActiveMagic(int magic);
    int getSpecialFlag(int memberNum);
    int getPartyHP(int memberNum);
    int getHPColor(int memberNum);
    int getCondition(int memberNum);
    bool isConditionChange(int memberNum);
    int getTargetGroup();
    void setTargetGroup(int monsterNum);
    void resetTargetGroup();
    void setMagicPosition(int pos);
    int getMagicPosition();
    void setAttackHistory();
    void setDefenceHistory();
    void setItemHistory();
    void setMagicHistory();
    void setTacticsHistory(int playerNum);
    void checkSpecialFlag(int playerNum);
    bool changeHistory();
};

extern BattleMenu_ROOT gBattleMenu_ROOT;
extern BattleMenu_FRIEND_ENTRANCE gBattleMenu_FRIEND_ENTRANCE;
extern UnkBattleMenuFriendSelect gUnkBattleMenuFriendSelect;
extern BattleMenu_StadiumAbort gBattleMenu_StadiumAbort;
extern BattleMenuSub_HISTORY gBattleMenuSub_HISTORY;
extern BattleMenu_NGMESSAGE gBattleMenu_NGMESSAGE;
extern BattleMenu_ACTIONMENU gBattleMenu_ACTIONMENU;
extern BattleMenu_ATTACK gBattleMenu_ATTACK;
extern UnkBattleMenuAttackCancel gUnkBattleMenuAttackCancel;
extern BattleMenu_ITEM gBattleMenu_ITEM;
extern UnkBattleMenuEquipItem gUnkBattleMenuEquipItem;
extern BattleMenu_ITEMUSE2ENEMY gBattleMenu_ITEMUSE2ENEMY;
extern BattleMenu_ITEMUSE2PARTY gBattleMenu_ITEMUSE2PARTY;
extern BattleMenu_MAGIC gBattleMenu_MAGIC;
extern BattleMenu_MAGIC2ENEMY gBattleMenu_MAGIC2ENEMY;
extern BattleMenu_MAGIC2PARTY gBattleMenu_MAGIC2PARTY;
extern BattleMenu_ARRAYMENU gBattleMenu_ARRAYMENU;
extern BattleMenu_ARRAY_ALL gBattleMenu_ARRAY_ALL;
extern BattleMenu_ARRAY_CHANGE gBattleMenu_ARRAY_CHANGE;
extern BattleMenu_TACTICSMENU gBattleMenu_TACTICSMENU;
extern UnkBattleMenuTest gUnkBattleMenuTest;
