#pragma ipa file
#include "main/part/UnkMenuPart.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/Render.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkLanguage.hpp"
#include "main/dss/Sprite2D.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "nitro/gx.h"
#include "nitro/gx.hpp"

#pragma thumb on

static int s_frame;
UnkMenuPart data_0209cfd0;
static int s_isEnd;
static Render s_render;
static UnkMenuSprite s_logo[2];

THUMB void UnkMenuPart::initialize()
{
    func_02075360();
    func_0207534c();
    GX_ResetBankForTex();
    GX_ResetBankForSubObj();
    GX_ResetBankForSubBg();
    GX_SetBankForTex(GX_VRAM_AB);
    data_020f4f74.initVramManagers(0x40000, 0x4000);
    unkfunc_0204c9d8(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    s_render.unkfunc_02048860();
    if (getGameRegion() == 1) {
        s_logo[0].loadFile("data/2d/sqex_logo.tex", 0);
    }
    if (getGameRegion() == 2) {
        s_logo[0].loadFile("data/2d/sqex_logo_na.tex", 0);
    }
    if (getGameRegion() == 3) {
        s_logo[0].loadFile("data/2d/sqex_logo_eu.tex", 0);
    }
    s_logo[0].attachRender(&s_render);
    s_logo[0].setSubScreen();
    s_logo[0].setPolygonID(1);
    s_logo[0].setAlpha(0x1f);
    if (getGameRegion() == 1) {
        s_logo[1].loadFile("data/2d/arte_logo.tex", 0);
    }
    if (getGameRegion() == 2) {
        s_logo[1].loadFile("data/2d/arte_logo_na.tex", 0);
    }
    if (getGameRegion() == 3) {
        s_logo[1].loadFile("data/2d/arte_logo_eu.tex", 0);
    }
    s_logo[1].attachRender(&s_render);
    s_logo[1].setMainScreen();
    s_logo[1].setPolygonID(1);
    s_logo[1].setAlpha(0x1f);
    s_isEnd = 0;
    s_frame = 0;
    g_Global.fadeInBlack(60);
}

THUMB void UnkMenuPart::terminate()
{
    s_logo[0].unload();
    s_logo[1].unload();
    s_render.unkfunc_020488b4();
    data_020f4f74.onPartTerminate();
}

THUMB void UnkMenuPart::onExecutePart()
{
    s_frame++;
    if (s_isEnd == 0 && s_frame > (getGameRegion() == 1 ? 120 : 240)) {
        g_Global.startOpeningStaff();
        s_isEnd = 1;
    }
}

THUMB void UnkMenuPart::onDrawPart()
{
    s_render.unkfunc_02048908();
}

THUMB void UnkMenuPart::onWindowPart()
{
}

THUMB void UnkMenuPart::onDebugPart()
{
}
