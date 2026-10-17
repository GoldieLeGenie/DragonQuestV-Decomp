#include "ov012/casino/PokerDoubleupHighAndLow.hpp"
#include "main/dss/UnkRandom.hpp"

THUMB void casino::PokerDoubleupHighAndLow::initialize()
{
    baseCard_ = 0;
    doubleupCount_ = 0;
    for (int i = 0; i < SAVE_COUNT_MAX; i++) {
        selectCard_[i] = 0;
        answer_[i] = ANSWER_LOW;
    }
}

THUMB void casino::PokerDoubleupHighAndLow::startHighAndLow(char base)
{
    initialize();
    int maxCount = SAVE_COUNT_MAX + 1;
    char temp[SAVE_COUNT_MAX + 1] = {0};
    for (int i = 0; i < maxCount; i++) {
        temp[i] = 0;
    }
    for (int i = 0; i < maxCount; i++) {
        temp[i] = UnkDssRand::rand(53);
        if (i > 0) {
            int count = 0;
            while (count < i) {
                if (temp[i] == temp[count]) {
                    temp[i] = UnkDssRand::rand(53);
                    count = 0;
                } else {
                    count++;
                }
                if (base != -1 && base == temp[count]) {
                    temp[i] = UnkDssRand::rand(53);
                    count = 0;
                }
            }
        }
    }
    baseCard_ = temp[0];
    for (int i = 1; i < maxCount; i++) {
        selectCard_[i - 1] = temp[i];
    }
}

THUMB int casino::PokerDoubleupHighAndLow::getSelectCardNo()
{
    return selectCard_[doubleupCount_ % SAVE_COUNT_MAX];
}

THUMB void casino::PokerDoubleupHighAndLow::setAnswer(ANSWER answer)
{
    answer_[doubleupCount_ % SAVE_COUNT_MAX] = answer;
}

THUMB casino::DOUBLEUP_RESULT casino::PokerDoubleupHighAndLow::getResult()
{
    int count = doubleupCount_ % SAVE_COUNT_MAX;
    doubleupCount_++;
    DOUBLEUP_RESULT ret = DOUBLEUP_LOSE;
    int baseCard = getCardNo(baseCard_);
    int compareCard = getCardNo(selectCard_[count]);
    if (baseCard > compareCard && answer_[count] == ANSWER_LOW) {
        ret = DOUBLEUP_WIN;
    } else if (baseCard < compareCard && answer_[count] == ANSWER_HIGH) {
        ret = DOUBLEUP_WIN;
    } else if (baseCard == compareCard) {
        ret = DOUBLEUP_DRAW;
        startHighAndLow(-1);
    }
    if (ret != DOUBLEUP_DRAW) {
        char card = selectCard_[count];
        if (count == SAVE_COUNT_MAX - 1) {
            startHighAndLow(card);
        }
        baseCard_ = card;
    }
    return ret;
}

THUMB char casino::PokerDoubleupHighAndLow::getCardNo(char cardNo)
{
    char retNo = cardNo % 13;
    if (cardNo == 52) {
        return 14;
    }
    if (retNo == 0) {
        return 13;
    }
    return retNo;
}
