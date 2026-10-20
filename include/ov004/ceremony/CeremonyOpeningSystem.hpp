#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/dss/TextureObject.hpp"
#include "main/object/DSSAObject.hpp"

namespace ceremony {
    // company logos before the title
    struct CeremonyOpeningSystem : args::GameSystem {
        enum {
            OPENING_PHASE_FADEIN = 0,
            OPENING_PHASE_KEYWAIT = 1,
            OPENING_PHASE_TO_LOGO = 2,
            OPENING_PHASE_TO_GAMELOAD = 3,
            OPENING_PHASE_TO_GAMESTART = 4,
            OPENING_PHASE_STOP = 5,
        };

        DataObject logo1Data_;                  // 0x004
        DSSAObject2D logo1Dssa_;                // 0x014
        DataObject logo3Data_;                  // 0x0B0
        DSSAObject2D logo3Dssa_;                // 0x0C0
        DataObject logo4Data_;                  // 0x15C
        DSSAObject2D logo4Dssa_;                // 0x16C
        UnkLZDataObject textureData_;           // 0x208
        TextureObject* texture_;             // 0x218
        int phase_;                             // 0x21C
        int counter_;                           // 0x220

        CeremonyOpeningSystem();
        ~CeremonyOpeningSystem();
        static CeremonyOpeningSystem* getSingleton();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        void setNextPhase(int phase);
    };
}
