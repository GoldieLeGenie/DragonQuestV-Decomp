#pragma once
#include <globaldefs.h>

// monster arena: the monsters of the current match, their odds and the battle start
struct FightStadiumManager {
    short monster_[4];                          // 0x00
    short orderNumber_[4];                      // 0x08  -1: single, else letter of a monster appearing twice or more
    short diameter_[4];                         // 0x10  odds x10
    short encount_;                             // 0x18
    short cardCount_;                           // 0x1A

    static FightStadiumManager m_singleton;

    FightStadiumManager();
    static FightStadiumManager& getSingleton();
    void setup();
    int getCardCount();
    int getMonsterID(int number);
    int getOrderCount(int number);
    int getDiameter(int number);
    bool isManyName(int number);
    int getMonsterCount();
    void setBetOnMacro();
    void battleStart();
};
