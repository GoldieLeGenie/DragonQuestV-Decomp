#pragma once
#include <globaldefs.h>
#include "main/dss/GameSystemManager.hpp"

namespace ceremony {
    // Opening/ending ceremony 
    struct CeremonySystem {
        args::GameSystem* system_;              // 0x00

        CeremonySystem();
        ~CeremonySystem();
        static CeremonySystem* getSingleton();
        void initialize();
        void terminate();
        void execute();
        void draw();
    };
}
