#include "ov012/casino/Casino_SlotMachine.hpp"
#include "main/dss/UnkRandom.hpp"
#include "ov012/casino/CasinoSlot.hpp"

inline void casino::Casino_SlotReel::setNumber(char number)
{
    reelNumber_ = number;
}

inline void casino::Casino_SlotReel::enableDeBoost()
{
    deBoostFlag_ = true;
}

inline int casino::Casino_SlotReel::getReelRot()
{
    return rollPosition_;
}

inline void casino::CasinoSlot::setBingoType(int type)
{
    bingoType_ = type;
}

int casino::Casino_SlotMachine::bingoBonusTable_[30] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    100, 20, 10, 8, 5, 3,
    1000, 200, 100, 50, 20, 6,
    10000, 2000, 1000, 200, 100, 20,
};

THUMB casino::Casino_SlotMachine::Casino_SlotMachine()
{
}

THUMB casino::Casino_SlotMachine::~Casino_SlotMachine()
{
}

THUMB void casino::Casino_SlotMachine::setupSlot(int table)
{
    for (int i = 0; i < REEL_MAX; i++) {
        reel_[i].setReel(table);
        reel_[i].setNumber(i);
    }
    slotTable_ = table;
    for (int i = 0; i < BINGO_PATERN; i++) {
        hitData_[i] = 0;
    }
    CasinoSlot::getSingleton()->setBingoType(0);
}

THUMB void casino::Casino_SlotMachine::resetSlot()
{
    for (int i = 0; i < REEL_MAX; i++) {
        reel_[i].resetReel();
    }
    for (int i = 0; i < BINGO_PATERN; i++) {
        hitData_[i] = 0;
    }
    CasinoSlot::getSingleton()->setBingoType(0);
}

THUMB bool casino::Casino_SlotMachine::scrollSlot()
{
    int trueCount = 0;
    reel_[0].enableDeBoost();
    for (int i = 0; i < REEL_MAX; i++) {
        Casino_SlotReel::SLOT_ROLL_STATE roll = reel_[i].scrollReel();
        if (roll == Casino_SlotReel::BRAKE) {
            if (i < REEL_MAX - 1) {
                reel_[i + 1].enableDeBoost();
            }
        } else if (roll == Casino_SlotReel::STOP) {
            trueCount++;
        }
        CasinoSlot::getSingleton()->rotReel(i, reel_[i].getReelRot());
    }
    if (trueCount == REEL_MAX) {
        return true;
    }
    return false;
}

THUMB void casino::Casino_SlotMachine::setCoordinateImage()
{
    for (int i = 0; i < REEL_MAX; i++) {
        reel_[i].setStopImageNum(UnkDssRand::rand(16));
    }
}

THUMB int casino::Casino_SlotMachine::getResultCoin(int pos)
{
    int result[5] = {0};
    for (int i = 0; i < 5; i++) {
        result[i] = 0;
    }
    const Casino_SlotReel::REEL_POS poslist[9] = {
        Casino_SlotReel::REEL_POS_CENTER, Casino_SlotReel::REEL_POS_TOP, Casino_SlotReel::REEL_POS_BOTTOM,
        Casino_SlotReel::REEL_POS_CENTER, Casino_SlotReel::REEL_POS_TOP, Casino_SlotReel::REEL_POS_BOTTOM,
        Casino_SlotReel::REEL_POS_CENTER, Casino_SlotReel::REEL_POS_TOP, Casino_SlotReel::REEL_POS_BOTTOM,
    };
    int coin;
    int line;
    int hitCount;
    int i;
    int hitData;
    hitCount = 0;
    line = -1;
    coin = 0;
    i = 0;
    hitData = pos % BINGO_PATERN;
    for (; i < REEL_MAX; i++) {
        result[i] = reel_[i].getImageNum(poslist[hitData]);
        result[i] = reel_[i].getDrumImage(result[i]);
        if (line == result[i]) {
            hitCount++;
        } else {
            if (hitCount >= 2) {
                break;
            }
            hitCount = 0;
            line = result[i];
        }
    }
    if (hitCount >= 2) {
        coin = bingoBonusTable_[line + hitCount * 6];
        hitData_[hitData] = CasinoSlot::getSingleton()->setBingoAnim(line, hitCount);
        CasinoSlot::getSingleton()->judgeBingoType(0);
        if (coin >= 100) {
            CasinoSlot::getSingleton()->judgeBingoType(1);
        }
        if (coin >= 10000) {
            CasinoSlot::getSingleton()->judgeBingoType(2);
        }
    }
    if (coin > 0) {
        CasinoSlot::getSingleton()->setLineBingo(pos);
    }
    return coin;
}
