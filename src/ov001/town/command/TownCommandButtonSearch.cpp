#include "ov001/town/command/TownCommandButtonSearch.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "main/dss/Pad.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/window/MessageControl.hpp"

#pragma thumb on

inline twn::TownSystemScript& twn::TownSystem::getScriptSystem()
{
    return townSystemScript_;
}

inline void twn::TownSystemScript::setScriptSearch(bool flag)
{
    scriptSearch_ = flag;
}

inline bool window::MessageControl::isMessageEnd()
{
    return state_ == END_MESSAGE;
}

int twn::TownCommandButtonSearch::isExec()
{
    if (dss::g_Pad.edge() & 1) {
        search_ = false;
        ido_ = false;
        script_ = false;
        if (TownPlayerManager::getSingleton().checkScriptSearch() == true) {
            TownSystem::getSingleton().getScriptSystem().setScriptSearch(true);
            script_ = true;
            return true;
        }
        if (TownPlayerManager::getSingleton().checkSearchMapObj(false) == true) {
            search_ = true;
            return true;
        }
        if (TownPlayerManager::getSingleton().checkIdo()) {
            TownWindowSystem::getSingleton().openSystemMessage();
            TownWindowSystem::getSingleton().addCommonMessage(0xc44a8);
            ido_ = true;
            return true;
        }
    }
    return false;
}

void twn::TownCommandButtonSearch::exec()
{
    if (search_ == true) {
        CommandObjectDefineTownSystem::setMenuSearchProgram();
    } else if (script_ == true) {
        CommandObjectDefineTownSystem::setMenuSearchScript();
    } else {
        CommandObjectDefineTownSystem::setMenuSearchNone();
    }
}

int twn::TownCommandButtonSearch::isEnd()
{
    if (ido_ == true) {
        return true;
    }
    if (TownWindowSystem::getSingleton().isMessageStart()) {
        window::gMessageControl.startMessage();
        TownWindowSystem::getSingleton().setMessageFlag(false);
    }
    if (!TownFurnitureManager::getSingleton()->isActive() && window::gMessageControl.isMessageEnd()) {
        return true;
    }
    return false;
}
