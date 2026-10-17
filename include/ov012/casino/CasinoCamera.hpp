#pragma once
#include <globaldefs.h>
#include "main/dss/Camera.hpp"

namespace casino {
    struct CasinoCamera {
        dss::UnkDualCamera camera_;             // 0x000

        CasinoCamera();
        ~CasinoCamera();
        static CasinoCamera* getSingleton();
        void initialize();
        void terminate();
        void draw();
    };
}
