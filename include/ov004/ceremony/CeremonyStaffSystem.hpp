#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/dss/TextureObject.hpp"
#include "main/object/DSSAObject.hpp"

namespace ceremony {
    // staff roll after the opening
    struct CeremonyStaffSystem : args::GameSystem {
        enum {
            STAFF_PHASE_FADEIN = 0,
            STAFF_PHASE_KEYWAIT = 1,
            STAFF_PHASE_FADEOUT = 2,
            STAFF_PHASE_STOP = 3,
        };

        DataObject staffUpData_;                // 0x004
        DSSAObject2D staffUpDssa_;              // 0x014
        DataObject staffDownData_;              // 0x0B0
        DSSAObject2D staffDownDssa_;            // 0x0C0
        UnkLZDataObject textureData_;           // 0x15C
        TextureObject* texture_;             // 0x16C
        int phase_;                             // 0x170
        int counter_;                           // 0x174

        CeremonyStaffSystem();
        ~CeremonyStaffSystem();
        static CeremonyStaffSystem* getSingleton();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        void setNextPhase(int phase);
    };
}
