#include "main/menu/RaceData.hpp"

inline RaceData::RaceData()
{
    cleanUp();
}

RaceData g_RaceData;

THUMB void RaceData::cleanUp()
{
    odds_ = 0;
    monsterNumber_ = 0;
    result_ = 0xff;
    slimeResult_ = 0xff;
    slimeNum_ = 0;
    betCoin_ = 0;
    look_ = 0;
    raceMap_ = 0x98;
    for (int i = 0; i < 15; i++) {
        oddsData_[i].odds = 0;
        oddsData_[i].coin = 0;
    }
}

THUMB void RaceData::setDoubleBetMode()
{
    int monsterNumber = monsterNumber_;
    cleanUp();
    slimeNum_ = 6;
    look_ = 0;
    monsterNumber_ = monsterNumber;
}

THUMB void RaceData::setBetMode()
{
    cleanUp();
    slimeNum_ = 5;
    look_ = 0;
}

THUMB void RaceData::setSlimeMode()
{
    int monsterNumber = monsterNumber_;
    cleanUp();
    slimeNum_ = 6;
    look_ = 1;
    monsterNumber_ = monsterNumber;
}

THUMB bool RaceData::betCoin(int index)
{
    if (betCoin_ < 50) {
        oddsData_[index].coin++;
        betCoin_++;
        return true;
    }
    return false;
}

THUMB bool RaceData::delCoin(int index)
{
    if (oddsData_[index].coin != 0) {
        oddsData_[index].coin--;
        betCoin_--;
        return true;
    }
    return false;
}
