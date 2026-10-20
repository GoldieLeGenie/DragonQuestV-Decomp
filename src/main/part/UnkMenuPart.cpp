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
    data_020f4f74.unkfunc_0204a53c(0x40000, 0x4000);
    unkfunc_0204c9d8(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    s_render.unkfunc_02048860();
    if (unkfunc_020464e8() == 1) {
        s_logo[0].unkfunc_02051a50("data/2d/sqex_logo.tex", 0);
    }
    if (unkfunc_020464e8() == 2) {
        s_logo[0].unkfunc_02051a50("data/2d/sqex_logo_na.tex", 0);
    }
    if (unkfunc_020464e8() == 3) {
        s_logo[0].unkfunc_02051a50("data/2d/sqex_logo_eu.tex", 0);
    }
    s_logo[0].unkfunc_02051adc(&s_render);
    s_logo[0].unkfunc_02051b80();
    s_logo[0].unkfunc_02051ba0(1);
    s_logo[0].unkfunc_02051b90(0x1f);
    if (unkfunc_020464e8() == 1) {
        s_logo[1].unkfunc_02051a50("data/2d/arte_logo.tex", 0);
    }
    if (unkfunc_020464e8() == 2) {
        s_logo[1].unkfunc_02051a50("data/2d/arte_logo_na.tex", 0);
    }
    if (unkfunc_020464e8() == 3) {
        s_logo[1].unkfunc_02051a50("data/2d/arte_logo_eu.tex", 0);
    }
    s_logo[1].unkfunc_02051adc(&s_render);
    s_logo[1].unkfunc_02051b78();
    s_logo[1].unkfunc_02051ba0(1);
    s_logo[1].unkfunc_02051b90(0x1f);
    s_isEnd = 0;
    s_frame = 0;
    g_Global.fadeInBlack(60);
}

THUMB void UnkMenuPart::terminate()
{
    s_logo[0].unkfunc_02051ac4();
    s_logo[1].unkfunc_02051ac4();
    s_render.unkfunc_020488b4();
    data_020f4f74.unkfunc_0204a5f0();
}

THUMB void UnkMenuPart::onExecutePart()
{
    s_frame++;
    if (s_isEnd == 0 && s_frame > (unkfunc_020464e8() == 1 ? 120 : 240)) {
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
