#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/fld/FldStage.hpp"

namespace casino {
    extern const char* CASINO_MAP_PATH;

    struct CasinoStage {
        FldStage stage_;                        // 0x000
        dss::Fix32Vector3 prev_;                // 0x8C0
        dss::Fix32Vector3 next_;                // 0x8CC
        int frame_;                             // 0x8D8
        int counter_;                           // 0x8DC

        CasinoStage();
        ~CasinoStage();
        static CasinoStage* getSingleton();
        void initialize();
        void terminate();
        void setObjectDraw(int id, int draw, int uidFlag);
        void setRotObjectUid(int uid, dss::Fix32Vector3& angle);
    };
}
