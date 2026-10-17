#pragma once
#include <globaldefs.h>
#include "main/cmn/PlayerManager.hpp"

namespace cmn
{
    struct GameManager {
        PlayerManager* playerManager_;          // 0x00

        GameManager();
        static GameManager& getSingleton();
        PlayerManager* getPlayerManager();
        void setPlayerManager(PlayerManager* playerManager);
        void initialize();
        void terminate();
        void execute();
        void resetParty();
    };
} // namespace cmn
