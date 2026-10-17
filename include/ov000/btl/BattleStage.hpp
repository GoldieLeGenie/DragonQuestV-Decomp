#pragma once
#include <globaldefs.h>
#include "main/fld/FldStage.hpp"

namespace btl {
    struct BattleStage {
        FldStage stage_;                            // 0x000
        dss::Fix32Vector3 prev_;                    // 0x8C0
        dss::Fix32Vector3 next_;                    // 0x8CC
        int frame_;                                 // 0x8D8
        int counter_;                               // 0x8DC
        char mapName_[32];                          // 0x8E0

        BattleStage();
        ~BattleStage();
        static BattleStage* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void execFade();
        bool isFade();
        void setRGBRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b);
    };
}
