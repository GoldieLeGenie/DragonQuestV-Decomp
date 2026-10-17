#pragma once
#include "globaldefs.h"
#include "GameInfo.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkMemory.hpp"

namespace cmn{
    struct CommonCounterInfo{
        int waitCounter_;
        int waitMax_;
        unsigned char dayCounter_[8];
        unsigned char freeCounter_[4];
        void initialize();
        bool isEndWaitCounter();
        void setWaitZero(int frame);
        bool checkBottun();
        int setDayCounter(int index, unsigned char value);
        void setChangeDay();
        bool isEndDayCounter(int index);
        unsigned char getCounter(int index);
        void setCounter(int index, unsigned char counter);
    };
    extern CommonCounterInfo g_CommonCounterInfo;
}


 
