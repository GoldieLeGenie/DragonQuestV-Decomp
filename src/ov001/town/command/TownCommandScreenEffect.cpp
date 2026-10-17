#include "ov001/town/command/TownCommandScreenEffect.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/window/ScreenEffectManager.hpp"

#pragma thumb on

inline bool window::ScreenEffectManager::isSetup()
{
    return setupFlag_;
}

int twn::TownCommandScreenEffect::isExec()
{
    return window::gScreenEffect.isSetup();
}

int twn::TownCommandScreenEffect::isEnd()
{
    if (window::gScreenEffect.isEnd()) {
        window::gScreenEffect.cleanUp();
        return true;
    }
    return false;
}

void twn::TownCommandScreenEffect::exec()
{
    CommandObjectDefineTownSystem::setScreenEffect();
}
