#pragma once
#include <globaldefs.h>

// name plates of the monster groups shown above the battle menu
struct BattleMonsterNamePlate {
    static const short BASE_LINE = 74;
    static const short PLATE_SIZE = 20;
    static const short BLANK_SIZE = 8;
    static const short MAX_STRING_SIZE = 256;
    static const short MAX_DISPLAY_SIZE_X = 256;
    static const short MAX_DISPLAY_SIZE_Y = 128;
    static const short PLATE_LENG = 4;
    static const short CURSOR_BLANK = 8;

    struct Monster_DATA {
        char index;                             // 0x00
        int name;                               // 0x04
        short num;                              // 0x08
        short drawID;                           // 0x0A
        short group;                            // 0x0C
        short center;                           // 0x0E
        short leng;                             // 0x10
        short height;                           // 0x12
        int flying;                             // 0x14
    };

    int addCount_;                              // 0x00
    Monster_DATA monsterData_[4];               // 0x04
    short sortList_[4];                         // 0x64
    int flyAndRand_;                            // 0x6C

    static BattleMonsterNamePlate m_singleton;

    static BattleMonsterNamePlate& getSingleton();
    void init();
    void setMonster();
    void maxPriority(int group);
    Monster_DATA& getMonsterData(int index);
    int seekMonster(int group);
    void movePumpUp(Monster_DATA& monster);
    void setMonsterParameter(int group, int monsterCount);
    void sortPosition();
    bool changeHeight(Monster_DATA& m_from, Monster_DATA& m_to);
    short adjustPosition(short height, int fly);
    short getGroupCenter(int group);
    void makeSortList();
    void adjustPlateCenter(Monster_DATA& monster, bool pumpUp);
    void adjustFlyHeight();
};
