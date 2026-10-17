#pragma once
#include <globaldefs.h>
#include "main/leveldata/SlotDrum.hpp"

namespace casino {
    struct Casino_SlotReel {
        static const int REEL_TOP_SPEED = 0x555;
        static const int REEL_UNDER_SPEED = 0xac;
        static const int IMAGE_SIZE = 0x1000;
        static const int MAX_REEL_SIZE = 16;
        static const int MIN_ROLL_COUNT = 3;

        enum SLOT_ROLL_STATE {
            ROLLING = 0,
            BRAKE = 1,
            STOP = 2,
        };

        enum REEL_POS {
            REEL_POS_CENTER = 0,
            REEL_POS_TOP = 1,
            REEL_POS_BOTTOM = 2,
        };

        char reelNumber_;                       // 0x00
        int rollCount_;                         // 0x04
        int subRollCount_;                      // 0x08
        int rollPosition_;                      // 0x0C
        int rollFirstPosition_;                 // 0x10
        int rollStopPosition_;                  // 0x14
        int deBoostPosition_;                   // 0x18
        int deBoostFlag_;                       // 0x1C
        int drumPos_;                           // 0x20
        int rollSpeed_;                         // 0x24
        int tableNo_;                           // 0x28
        SLOT_ROLL_STATE rollState_;             // 0x2C

        Casino_SlotReel();
        ~Casino_SlotReel();
        void setReel(int table);
        void setStopImageNum(int num);
        void setStopPosition(int position);
        void resetReel();
        SLOT_ROLL_STATE scrollReel();
        void rollSpeedUp();
        void rollSpeedDown();
        void reelRolling();
        bool checkPassingPoint(int point);
        int getImageNum(REEL_POS pos);
        int searchDeBoost(int speed);
        dq5::level::SlotDrum* getDrumData(int num);
        unsigned char getDrumImage(int num);
        void setNumber(char number);
        void enableDeBoost();
        int getReelRot();
    };
}
