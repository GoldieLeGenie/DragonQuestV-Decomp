#pragma once
#include <globaldefs.h>
#include "ov012/casino/Casino_SlotReel.hpp"

namespace casino {
    struct Casino_SlotMachine {
        static const int BINGO_PATERN = 3;
        static const int REEL_MAX = 5;

        int slotTable_;                         // 0x00
        int betCoin_;                           // 0x04
        int hitData_[BINGO_PATERN];             // 0x08
        Casino_SlotReel reel_[REEL_MAX];        // 0x14

        static int bingoBonusTable_[30];

        Casino_SlotMachine();
        ~Casino_SlotMachine();
        void setupSlot(int table);
        void resetSlot();
        bool scrollSlot();
        void setCoordinateImage();
        int getResultCoin(int pos);
        int getEffectLamp(int cnt);
    };
}
