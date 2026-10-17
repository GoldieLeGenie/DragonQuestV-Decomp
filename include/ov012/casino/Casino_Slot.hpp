#pragma once
#include <globaldefs.h>
#include "ov012/casino/Casino_SlotMachine.hpp"

namespace casino {
    struct Casino_Slot {
        static const int MAX_COIN = 9999999;
        static const int MAX_BET = 9;

        int slotTable_;                         // 0x00
        int slotState_;                         // 0x04
        int betCost_;                           // 0x08
        int betCoin_;                           // 0x0C
        int resultCoin_;                        // 0x10
        short effectCounter_;                   // 0x14
        int effectFlag_;                        // 0x18
        int luckRetryCount_;                    // 0x1C
        int rollSePlayer_;                      // 0x20
        Casino_SlotMachine slotMachine_;        // 0x24

        Casino_Slot();
        ~Casino_Slot();
        static Casino_Slot* getSingleton();
        void setSlotType(int type);
        void setBetCost(int cost);
        void resetSlot();
        void addCoin(int& coin);
        void instantAddCoin(int& coin, int count);
        void subCoin(int& coin);
        int getResultAllCoin();
        bool runningSlot();
        void cashCoin(int& coin);
        void cashAllCoin(int& coin);
        int startSlot();
        bool showEffect();
    };
}
