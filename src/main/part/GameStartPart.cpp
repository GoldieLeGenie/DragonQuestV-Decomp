#include "main/part/GameStartPart.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/global/Global.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuOverlay.hpp"
#include "main/profile/SaveLoad.hpp"
#include "main/sound/Sound.hpp"
#include "main/sound/SoundManager.hpp"

static int active;
GameStartPart g_GameStartPart;

THUMB void GameStartPart::initialize()
{
    changeDisplayPlugin(&dss::g_DISPLAYPLUGIN_SINGLE3D);
    Sound::strmStop(0);
    SoundManager::stop(0);
    g_Global.fadeIn(30);
    loadOverlay((int)&OVERLAY_19_ID);
    cardcheck_ = profile::SaveLoad::isCardOK();
    if (cardcheck_ == 0) {
        return;
    }
    unkfunc_02018d64(14);
    MenuAPI::openMenu(&gMaterielMenu_LOAD);
    active = 1;
    SoundManager::play(0x17, 5);
}

THUMB void GameStartPart::terminate()
{
    SoundManager::stop(0);
    unloadOverlay((int)&OVERLAY_19_ID);
}

THUMB void GameStartPart::onExecutePart()
{
    if (cardcheck_ == 0) {
        if (gTownMenu_MESSAGE.isOpen()) {
            return;
        }
        gTownMenu_MESSAGE.openMessageForMENU();
        gTownMenu_MESSAGE.addMessage(0xcb60b);
        return;
    }
    if (active == 0) {
        return;
    }
    if (gMaterielMenu_LOAD.stat_ == menu::MenuBase::MENUBASE_STAT_OK) {
        gMaterielMenu_LOAD.close();
        cardcheck_ = 0;
        active = 0;
    }
    if (gMaterielMenu_LOAD.stat_ == menu::MenuBase::MENUBASE_STAT_CANCEL) {
        gMaterielMenu_LOAD.close();
        g_Global.startDebugTown();
        active = 0;
    }
}

THUMB void GameStartPart::onDrawPart()
{
}

THUMB void GameStartPart::onWindowPart()
{
}

THUMB void GameStartPart::onDebugPart()
{
}
