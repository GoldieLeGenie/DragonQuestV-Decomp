#pragma once
#include <globaldefs.h>
#include "main/data/ExcelBinaryData.hpp"
#include "nitro/fx.hpp"

namespace dq5 {
namespace level {
    struct EffectParam {
        fx32 scale;                                 // 0x00
        unsigned short index;                       // 0x04
        unsigned short frame;                       // 0x06
        unsigned short homing;                      // 0x08
        unsigned short sound;                       // 0x0A
        unsigned short camera;                      // 0x0C
        unsigned short camera2;                     // 0x0E
        unsigned char interval;                     // 0x10
        unsigned char color;                        // 0x11
        unsigned char hold;                         // 0x12
        unsigned char wait;                         // 0x13
        char byte_1;                                // 0x14
        char byte_2;                                // 0x15
        unsigned char dummy0;                       // 0x16
        unsigned char dummy1;                       // 0x17

        static const char* filename_;
        static ExcelBinaryData binary_;
        static void* addr_;
        static dss::File::LoadSwitch loadSwitch_;

        static void setup();
        static void cleanup();
        static EffectParam* getRecord(int index);
        static unsigned int getArraySize();
        unsigned short getIndex();
        unsigned short getFrame();
        unsigned short getHoming();
        unsigned short getSound();
        unsigned short getCamera();
        unsigned short getCamera2();
        unsigned char getInterval();
        unsigned char getColor();
        unsigned char getHold();
        unsigned char getWait();
        char getFailed();
        char getWay();
        char getFlicker();
        char getDisplay();
        void setDisplay(char data);
        void setFrame(unsigned short data);
        void setScale(fx32 data);
    };
}
}
