#include "ov005/fld/FieldSystem.hpp"
#include "main/window/NormalControl.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

THUMB fld::FieldSystemPlayer::FieldSystemPlayer()
{
}

THUMB fld::FieldSystemPlayer::~FieldSystemPlayer()
{
}

THUMB void fld::FieldSystemPlayer::initialize()
{
    FieldPlayerManager::getSingleton().initialize();
    FieldPlayerManager::getSingleton().setup();
}

THUMB void fld::FieldSystemPlayer::terminate()
{
    FieldPlayerManager::getSingleton().cleanup();
    FieldPlayerManager::getSingleton().terminate();
}

THUMB void fld::FieldSystemPlayer::execute()
{
    window::gNormalControl.execute();
    FieldPlayerManager::getSingleton().execute();
}

THUMB void fld::FieldSystemPlayer::draw()
{
    FieldPlayerManager::getSingleton().draw();
}
