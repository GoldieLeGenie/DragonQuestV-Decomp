#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"

namespace dq5 {
namespace level {
    struct EffectMessage {
        unsigned long ConditionMsg;                 // 0x00
        unsigned long OriginalCondMsg;              // 0x04
        unsigned long PlayerCondMsg;                // 0x08
        unsigned long MonsterCondMsg;               // 0x0C
        unsigned long OverlapMsg;                   // 0x10
        unsigned long NotLapMsg;                    // 0x14
        unsigned long NaturalClearMsg;              // 0x18
        unsigned short action;                      // 0x1C
        unsigned char typeID;                       // 0x1E
        unsigned char dummy0;                       // 0x1F

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;
        static char dataRegion[1824];

        unsigned long getConditionMsg();
        unsigned long getOriginalCondMsg();
        unsigned long getPlayerCondMsg();
        unsigned long getMonsterCondMsg();
        unsigned long getOverlapMsg();
        unsigned long getNotLapMsg();
        unsigned long getNaturalClearMsg();
        unsigned short getAction();
        unsigned char getTypeID();
        static unsigned int getArraySize();
        static void setup();
        static void cleanup();
        static EffectMessage* getRecord(int index);
    };
}
}
