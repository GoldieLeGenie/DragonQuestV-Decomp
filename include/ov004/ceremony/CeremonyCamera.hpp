#pragma once
#include <globaldefs.h>
#include "main/dss/Camera.hpp"

namespace ceremony {
    struct CeremonyCamera {
        dss::UnkDualCamera camera_;             // 0x000

        CeremonyCamera();
        ~CeremonyCamera();
        static CeremonyCamera* getSingleton();
        void initialize();
        void terminate();
        void draw();
    };
}
