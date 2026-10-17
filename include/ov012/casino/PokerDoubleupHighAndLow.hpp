#pragma once
#include <globaldefs.h>

namespace casino {
    enum ANSWER {
        ANSWER_HIGH = 0,
        ANSWER_LOW = 1,
    };

    enum DOUBLEUP_RESULT {
        DOUBLEUP_WIN = 0,
        DOUBLEUP_LOSE = 1,
        DOUBLEUP_DRAW = 2,
    };

    struct PokerDoubleupHighAndLow {
        static const int SAVE_COUNT_MAX = 10;

        char doubleupCount_;                    // 0x00
        char baseCard_;                         // 0x01
        char selectCard_[SAVE_COUNT_MAX];       // 0x02
        ANSWER answer_[SAVE_COUNT_MAX];         // 0x0C

        void initialize();
        void startHighAndLow(char base);
        int getSelectCardNo();
        void setAnswer(ANSWER answer);
        DOUBLEUP_RESULT getResult();
        char getCardNo(char cardNo);
    };
}
