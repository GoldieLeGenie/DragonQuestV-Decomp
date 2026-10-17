#pragma once
#include <globaldefs.h>
#include "ov012/casino/PokerDoubleupHighAndLow.hpp"

namespace casino {
    enum CARD_TYPE {
        TYPE_SLIME,
        TYPE_CROWN,
        TYPE_SWORD,
        TYPE_SHIELD,
        TYPE_JOKER,
    };

    struct PokerManager {
        struct POKER_CARD {
            char defaultNo_;                    // 0x00
            char type_;                         // 0x01
            char no_;                           // 0x02
        };

        int defaultNo_[5];                      // 0x00
        int chengeCard_[5];                     // 0x14
        int cardNo_[5];                         // 0x28
        CARD_TYPE cardType_[5];                 // 0x3C
        int cardPosition_;                      // 0x50
        int winningCombination_;                // 0x54
        int combinationCard_[5];                // 0x58
        int betCoin_;                           // 0x6C
        int getCoin_;                           // 0x70
        POKER_CARD gameCard_[5];                // 0x74
        POKER_CARD changeCard_[5];              // 0x83
        POKER_CARD debugCard_[5];               // 0x92
        PokerDoubleupHighAndLow highAndLow_;    // 0xA4

        static PokerManager* getSingleton();
        void initialize();
        void clearCard();
        void clearDebugCard(int index);
        void dealCard(int index);
        void setBetCoin(int bet);
        void setGetCoin(int coin);
        void setCardPosition(int position);
        int getCardNo(int index);
        int getCardType(int index);
        int judgementCombination();
        int getMultiple();
        void resetCombinationCard();
        void startHighAndLow();
        void setAnswer(int answer);
        DOUBLEUP_RESULT getHighAndLowResult();
        int getHighAndLowCardType(int base);
        int getHighAndLowCardNo(int base);
        void setGameCard(POKER_CARD* card, int index, char defaultNo);
        int changeCardNo(int cardNo);
        int changeCardType(int cardNo);
    };
}
