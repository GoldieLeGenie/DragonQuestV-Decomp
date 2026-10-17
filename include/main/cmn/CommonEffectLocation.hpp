#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace cmn {
    struct CommonEffectLocation {
        dss::Fix32Vector3 prev_;                    // 0x00
        dss::Fix32Vector3 next_;                    // 0x0C
        int frame_;                                 // 0x18
        int counter_;                               // 0x1C
        int extend_;                                // 0x20
        int enable_;                                // 0x24
        int index_;                                 // 0x28

        CommonEffectLocation();
        ~CommonEffectLocation();
        static CommonEffectLocation& getSingleton();
        void initialize();
        void terminate();
        void execute();
        void start(int index, int extend);
        bool setPaletteRate(int index);
        bool calcPaletteRate();
    };
}
