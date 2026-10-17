#pragma once
#include <globaldefs.h>

namespace btl
{
    extern int CorrectValue[31];
    extern int LandSubtractValue[9];
    extern int TileSubtractValue[8];

    struct EncountCountDown {
        static const int STANDARD_VALUE = 0x1e00;

        int counter_;                           // 0x00
        int correctValue_;                      // 0x04
        int tileIdRate_;                        // 0x08
        int landType_;                          // 0x0C
        int subtractValue_;                     // 0x10
        int fix_;                               // 0x14

        EncountCountDown();
        ~EncountCountDown();
        void setup();
        void exec();
        void setTileIdRate(int rate);
        void setLandType(int landType);
        int getCounter();
        void setLandSubtranctValeu();
    };
} // namespace btl
