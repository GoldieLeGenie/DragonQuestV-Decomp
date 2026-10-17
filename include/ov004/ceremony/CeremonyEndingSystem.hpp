#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/dss/UnkSprite2D.hpp"
#include "main/dss/UnkTextureObject.hpp"
#include "main/object/DSSAObject.hpp"

namespace ceremony {
    // ending staff roll with the falling petals
    struct CeremonyEndingSystem : args::GameSystem {
        static const int DIVISION = 3;
        static const int MAX_PETAL = 3;

        enum {
            ENDING_PHASE_FADEIN = 0,
            ENDING_PHASE_KEYWAIT = 1,
            ENDING_PHASE_FADEOUT = 2,
            ENDING_PHASE_LASTROLL = 3,
            ENDING_PHASE_STOP = 4,
        };

        int lineY_[128];                        // 0x004
        int pageY_[DIVISION];                   // 0x204
        UnkSprite2D rollSprite_[DIVISION];      // 0x210
        UnkLZDataObject rollData_[DIVISION];    // 0x2B8
        UnkTextureObject* rollTexture_[DIVISION];   // 0x2E8
        int rollStart_[6];                      // 0x2F4
        int rollEnd_[6];                        // 0x30C
        DataObject petalData_[MAX_PETAL];       // 0x324
        DSSAObject2D petalDssa_[MAX_PETAL];     // 0x354
        DataObject petalTextureData_;           // 0x528
        UnkTextureObject* petalTexture_;        // 0x538
        int index_;                             // 0x53C
        int lineCount_;                         // 0x540
        int phase_;                             // 0x544
        int counter_;                           // 0x548
        int endStaff_;                          // 0x54C

        CeremonyEndingSystem();
        ~CeremonyEndingSystem();
        static CeremonyEndingSystem* getSingleton();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        void setNextPhase(int phase);
        bool isEnd();
    };
}
