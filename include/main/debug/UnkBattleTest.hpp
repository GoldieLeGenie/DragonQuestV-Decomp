#pragma once
#include <globaldefs.h>


struct UnkBattleTest {
    int mode_;                                  // 0x00
    int unk_04;                                 // 0x04
    int firstTile_;                             // 0x08
    int lastTile_;                              // 0x0C
    int playCount_;                             // 0x10
    int command_;                               // 0x14 battle command of the player 1
    int command2_;                              // 0x18 battle command of the other players
    int noDamage_;                              // 0x1C
    int hpRate_;                                // 0x20 % of the max HP at the battle start
    int noDamageTurn_;                          // 0x24 monsters take no damage until this turn
    int endTurn_;                               // 0x28 the battle is stopped after this turn
    int state_;                                 // 0x2C
    int counter_;                               // 0x30 frames in the state
    int tile_;                                  // 0x34
    int play_;                                  // 0x38
    int unk_3c;                                 // 0x3C
    int unk_40;                                 // 0x40
    int unk_44;                                 // 0x44
    int act_;                                   // 0x48
    int monsterIndex_[4];                       // 0x4C
    int monsterCount_[4];                       // 0x5C

    UnkBattleTest();
    void update();                    // update
};

extern UnkBattleTest data_020c2c40;
