#include "main/town/TownCommandEncount.hpp"
#include "main/btl/Encount.hpp"
#include "main/status/StageAttribute.hpp"
#include "ov001/town/TownDamageFloor.hpp"
#include "ov001/town/TownPlayerManager.hpp"

inline bool btl::Encount::isEnable() { return enable_; }

THUMB int twn::TownCommandEncount::isExec()
{
    TownDamageFloor::getSingleton().checkEncount();
    if (!status::g_StageAttribute.isEncount()) {
        return false;
    }
    if (!btl::Encount::getSingleton()->isEnable()) {
        return false;
    }
    if (btl::Encount::getSingleton()->isEncounted()) {
        TownPlayerManager::getSingleton().setLock(true);
        return true;
    }
    return false;
}

THUMB int twn::TownCommandEncount::isEnd()
{
    return true;
}

THUMB void twn::TownCommandEncount::exec()
{
    if (status::g_StageAttribute.isEncount() && btl::Encount::getSingleton()->isEnable()) {
        btl::Encount::getSingleton()->execDungeon();
        CommandObjectDefineTownSystem::setEncount();
    }
}
