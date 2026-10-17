#include "main/town/TownCommandPlaySound.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/cmn/CommonSoundManager.hpp"

inline int cmn::CommonSoundManager::isPlaySound()
{
    return isPlaySound_;
}

THUMB int twn::TownCommandPlaySound::isExec()
{
    if (cmn::g_cmnSoundManager.isPlaySound() == true) {
        cmn::g_cmnSoundManager.execSound();
        return true;
    }
    return false;
}

THUMB int twn::TownCommandPlaySound::isEnd()
{
    return true;
}

THUMB void twn::TownCommandPlaySound::exec()
{
    CommandObjectDefineTownSystem::setPlaySound();
}
