#include "ov001/town/player/TownActionKaifuku.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "main/global/Global.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/PartyStatus.hpp"

#pragma thumb on

int twn::TownActionKaifuku::setup()
{
    return -1;
}

void twn::TownActionKaifuku::execute()
{
}

int twn::TownActionKaifuku::update()
{
    int ret = -1;
    if (fadeEffector.isFadeEnd() == false) {
        return ret;
    }
    switch (state_) {
    case 0:
        g_Global.fadeInWhite(0x1e);
        SoundManager::playSe(0x454, 0);
        status::PartyStatusUtility::kaifukuyuka();
        state_ = 1;
    case 1: {
        int message = 0x413e;
        status::g_Party.setBattleMode();
        if (status::g_Party.getCarriageOutAliveCount() == 1 && status::g_Party.getCarriageAliveCount() == 0) {
            message += 2;
        }
        TownWindowSystem::getSingleton().openSystemMessage(message, 1);
        ret = 0;
        break;
    }
    }
    return ret;
}

void twn::TownActionKaifuku::start()
{
    g_Global.fadeOutWhite(0x1e, true);
    state_ = 0;
}
