#pragma once
#include <globaldefs.h>

namespace status {
    struct TOUCH_RANKING_DATA {
        int score;                              // 0x0
        unsigned char stage;                    // 0x4
    };

    struct TOUCH_ITEM_DATA {
        int index;                              // 0x0
        char count;                             // 0x4
    };

    struct TouchData {
        TOUCH_RANKING_DATA ranking_[10];        // 0x00
        TOUCH_ITEM_DATA item_[17];              // 0x50
        int resultFlag_;                        // 0xD8
        int rankIn_;                            // 0xDC
        int newScore_;                          // 0xE0

        TouchData();
        void cleanUp();
        void setUp();
        bool setRanking(int score, int stage);
        TOUCH_RANKING_DATA& getRanking(int index);
        int getScore();
        TOUCH_ITEM_DATA& getItem(int index);
        void setItem(int index, int count);
        void setResultFlag(bool flag);
        bool isResultFlag();
    };

    extern TouchData g_TouchData;
}
