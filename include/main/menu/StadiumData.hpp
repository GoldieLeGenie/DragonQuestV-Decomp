#pragma once
#include <globaldefs.h>

struct StadiumData {
    unsigned int betCoin_;                  // 0x00
    int stadiumFlag_;                       // 0x04
    int monsterDeath_;                      // 0x08
    unsigned short odds_;                   // 0x0C
    unsigned short monsterID_;              // 0x0E
    unsigned char monsterArray_;            // 0x10
    char monsterNumber_;                    // 0x11
    unsigned char result_;                  // 0x12
    int doubleUp_;                          // 0x14
    int retire_;                            // 0x18

    bool isStadiumBattle();
    unsigned char getBetArray();
    void setBetArray(unsigned char betArray);
    void setBetID(unsigned char id);
    void setBetNumber(char number);
    void betDeathON();
    StadiumData();
    void cleanUp();
};

extern StadiumData g_StadiumData;
