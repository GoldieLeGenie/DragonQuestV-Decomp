#include "main/part/CardCheckPart.hpp"
#include "main/part/GameEndPart.hpp"
#include "main/profile/SaveLoad.hpp"

CardCheckPart g_CardCheckPart;

THUMB void CardCheckPart::initialize()
{
    switch (profile::SaveLoad::checkBackup()) {
    case 1:
        data_02101c88.unkfunc_02051800(MENU_PART);
        break;
    case -1:
        data_02101c88.unkfunc_02051800(MENU_PART);
        break;
    case -2:
        g_GameEndPart.startWithNextPart(5, MENU_PART);
        break;
    case -3:
        g_GameEndPart.start(1);
        break;
    case -4:
        g_GameEndPart.start(4);
        break;
    case -5:
        g_GameEndPart.start(3);
        break;
    }
}

THUMB void CardCheckPart::terminate()
{
}

THUMB void CardCheckPart::onExecutePart()
{
}

THUMB void CardCheckPart::onDrawPart()
{
}

THUMB void CardCheckPart::onWindowPart()
{
}

THUMB void CardCheckPart::onDebugPart()
{
}
