#pragma once
#include <globaldefs.h>
#include "main/fld/FldStage.hpp"

namespace ceremony {
    extern const char* CEREMONY_MAP_PATH;

    struct CeremonyStage {
        int enable_;                                // 0x00
        FldStage stage_;                            // 0x04

        CeremonyStage();
        ~CeremonyStage();
        static CeremonyStage* getSingleton();
        void initialize();
        void terminate();
        void draw();
        int getCameraNo(int idx);
        VecFx32* getCameraPosFX32(int idx);
        VecFx32* getCameraCentFX32(int idx);
        VecFx32* getCameraUpFX32(int idx);
    };
}
