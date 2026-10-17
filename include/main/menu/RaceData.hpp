#pragma once
#include <globaldefs.h>

struct ODDS_DATA {
    unsigned short odds;                        // 0x00
    unsigned short coin;                        // 0x02
};

// Slime race bets
struct RaceData {
    ODDS_DATA oddsData_[15];                    // 0x00
    unsigned int betCoin_;                      // 0x3C
    int look_;                                  // 0x40
    int raceMap_;                               // 0x44
    unsigned char slimeNum_;                    // 0x48
    unsigned short winningNum_;                 // 0x4A
    unsigned short odds_;                       // 0x4C
    int monsterNumber_;                         // 0x50
    unsigned char result_;                      // 0x54
    unsigned char slimeResult_;                 // 0x55

    RaceData();
    void cleanUp();
    unsigned char getPaddock();
    bool isLookOnly();
    unsigned int getBetCoin();
    void setBetCoin(unsigned int coin);
    unsigned char getResult();
    void setResult(unsigned char result);
    void setWinningNum(unsigned short num);
    unsigned short getOdds();
    void setOdds(unsigned short odds);
    bool isSlimeWin();
    int getSlimeNumber();
    void setRaceMapId(int id);
    int getRaceMapId();
    void setDoubleBetMode();
    void setBetMode();
    void setSlimeMode();
    bool betCoin(int index);
    bool delCoin(int index);
};

extern RaceData g_RaceData;
