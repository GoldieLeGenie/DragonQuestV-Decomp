#include "ov001/town/command/UnkTownCommandMenuTalk.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/town/TownCommandEncount.hpp"

#pragma thumb on

inline cmn::MENU_ACTION cmn::CommonPartyInfo::getMenuAction()
{
    return menuAction_;
}

int twn::UnkTownCommandMenuTalk::isExec()
{
    if (cmn::g_cmnPartyInfo.getMenuAction() == cmn::MENU_TALK) {
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        return true;
    }
    return false;
}

void twn::UnkTownCommandMenuTalk::exec()
{
    CommandObjectDefineTownSystem::setMenuTalk();
}

int twn::UnkTownCommandMenuTalk::isEnd()
{
    return true;
}
