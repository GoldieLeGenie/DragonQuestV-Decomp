#include "main/part/GameEndPart.hpp"
#include "main/global/Global.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"

GameEndPart g_GameEndPart;

THUMB GameEndPart::GameEndPart()
{
    type_ = 1;
}

THUMB void GameEndPart::initialize()
{
    g_Global.fadeIn(30);
}

THUMB void GameEndPart::terminate()
{
}

THUMB void GameEndPart::onExecutePart()
{
    if (type_ == 0) {
        return;
    }
    if (!gTownMenu_MESSAGE.isOpen()) {
        gTownMenu_MESSAGE.openMessageForMENU();
        gTownMenu_MESSAGE.addMessage(message_);
    }
    if (nextPart_ == -1) {
        return;
    }
    if (gTownMenu_MESSAGE.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
        data_02101c88.unkfunc_02051800(nextPart_);
        type_ = 0;
    }
}

THUMB void GameEndPart::onDrawPart()
{
}

THUMB void GameEndPart::onWindowPart()
{
}

THUMB void GameEndPart::onDebugPart()
{
}

THUMB void GameEndPart::unkfunc_02041a4c(int type)
{
    unkfunc_02041a58(type, -1);
}

THUMB void GameEndPart::unkfunc_02041a58(int type, int nextPart)
{
    type_ = type;
    nextPart_ = nextPart;
    switch (type_) {
    case 0:
        message_ = 0;
        break;
    case 1:
        message_ = 0xcb60b;
        break;
    case 2:
        message_ = 0xcb5fa;
        break;
    case 3:
        message_ = 0xcb608;
        break;
    case 4:
        message_ = 0xcb9e5;
        break;
    case 5:
        message_ = 0xcb60e;
        break;
    default:
        message_ = 0;
        break;
    }
}

THUMB void GameEndPart::unkfunc_02041ab8(int type)
{
    unkfunc_02041a4c(type);
    data_02101c88.unkfunc_02051800(GAME_END_PART);
}

THUMB void GameEndPart::unkfunc_02041acc(int type, int nextPart)
{
    unkfunc_02041a58(type, nextPart);
    data_02101c88.unkfunc_02051800(GAME_END_PART);
}
