#include "ov005/fld/FieldSystem.hpp"
#include "main/window/ScreenEffectManager.hpp"

THUMB fld::FieldSystemScreenEffect::FieldSystemScreenEffect()
{
}

THUMB fld::FieldSystemScreenEffect::~FieldSystemScreenEffect()
{
}

THUMB void fld::FieldSystemScreenEffect::initialize()
{
    window::gScreenEffect.initialize();
}

THUMB void fld::FieldSystemScreenEffect::terminate()
{
    window::gScreenEffect.terminate();
}

THUMB void fld::FieldSystemScreenEffect::execute()
{
    window::gScreenEffect.execute();
}

THUMB void fld::FieldSystemScreenEffect::draw()
{
    if (window::gScreenEffect.isActivate()) {
        args::GameSystemManager::getSingleton().setDrawExclusion(6, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(7, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(10, false);
        args::GameSystemManager::getSingleton().setDrawExclusion(1, false);
    }
    window::gScreenEffect.draw();
}
