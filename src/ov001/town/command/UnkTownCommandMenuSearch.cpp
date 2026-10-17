#include "ov001/town/command/UnkTownCommandMenuSearch.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/town/TownCommandEncount.hpp"
#include "main/window/MessageControl.hpp"

#pragma thumb on

inline cmn::MENU_ACTION cmn::CommonPartyInfo::getMenuAction()
{
    return menuAction_;
}

inline twn::TownSystemScript& twn::TownSystem::getScriptSystem()
{
    return townSystemScript_;
}

inline void twn::TownSystemScript::setScriptSearch(bool flag)
{
    scriptSearch_ = flag;
}

inline twn::TOWN_PLAYER_ACTION_TYPE twn::TownPlayerManager::getActionType()
{
    return player_.actionType_;
}

inline bool window::MessageControl::isMessageEnd()
{
    return state_ == END_MESSAGE;
}

int twn::UnkTownCommandMenuSearch::isExec()
{
    if (cmn::g_cmnPartyInfo.getMenuAction() == cmn::MENU_SEARCH) {
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        script_ = false;
        search_ = false;
        ido_ = false;
        if (TownPlayerManager::getSingleton().checkScriptSearch() == true) {
            script_ = true;
            TownSystem::getSingleton().getScriptSystem().setScriptSearch(true);
            return true;
        }
        if (TownPlayerManager::getSingleton().checkSearchMapObj(true) == true) {
            search_ = true;
            return true;
        }
        if (TownPlayerManager::getSingleton().checkIdo()) {
            TownWindowSystem::getSingleton().openSystemMessage();
            TownWindowSystem::getSingleton().addCommonMessage(0xc44a8);
            ido_ = true;
            return true;
        }
        if (TownPlayerManager::getSingleton().getActionType() == ACTION_TYPE_SHIP || TownPlayerManager::getSingleton().getActionType() == ACTION_TYPE_IKADA) {
            TownWindowSystem::getSingleton().openSystemMessage();
            TownWindowSystem::getSingleton().addCommonMessage(0xc44ab);
            TownWindowSystem::getSingleton().addCommonMessage(0xc44b3);
        } else {
            TownWindowSystem::getSingleton().openSystemMessage();
            TownWindowSystem::getSingleton().addCommonMessage(0xc44a2);
            TownWindowSystem::getSingleton().addCommonMessage(0xc44b1);
        }
        return true;
    }
    return false;
}

void twn::UnkTownCommandMenuSearch::exec()
{
    if (search_ == true) {
        CommandObjectDefineTownSystem::setMenuSearchProgram();
    } else if (script_ == true) {
        CommandObjectDefineTownSystem::setMenuSearchScript();
    } else {
        CommandObjectDefineTownSystem::setMenuSearchNone();
    }
}

int twn::UnkTownCommandMenuSearch::isEnd()
{
    if (ido_ == true) {
        return true;
    }
    if (!script_ && !search_) {
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
