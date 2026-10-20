#include "main/part/TownPart.hpp"
#include "main/debug/UnkDebugDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "main/sound/UnkNnsSound.hpp"
#include "nitro/gx.h"
#include "nitro/gx.hpp"
#include "nnsys/g3d.hpp"
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownWindowSystem.hpp"

static unsigned int s_minFreeSize = 0x100000;
twn::TownPart g_TownPart;

ARM void twn::TownPart::initialize()
{
    func_02075360();
    func_0207534c();
    GX_ResetBankForTex();
    GX_ResetBankForSubObj();
    GX_ResetBankForSubBg();
    GX_SetBankForTex(GX_VRAM_AB);
    data_020f4f74.unkfunc_0204a53c(0x40000, 0x4000);
    unkfunc_0204c9d8(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    data_02101584.unkfunc_0205027c();
    unkfunc_0204afe0();
    unkfunc_0204b5d4((int)&OVERLAY_1_ID);
    ov001_entry();
    unkfunc_02018e6c(1);
    ov019_entry();
    unkfunc_0204afe0();
    twn::TownSystem::getSingleton().initialize();
    twn::TownWindowSystem::getSingleton().initialize();
    func_02082654(1);
    g_Global.fadeIn(33);
    if (unkfunc_0204c604(&data_020fd24c) < s_minFreeSize) {
        s_minFreeSize = unkfunc_0204c604(&data_020fd24c);
    }
    unkfunc_020270dc();
}

ARM void twn::TownPart::terminate()
{
    twn::TownWindowSystem::getSingleton().terminate();
    twn::TownSystem::getSingleton().terminate();
    data_02101584.unkfunc_0205027c();
    unkfunc_0204afe0();
    data_020a29f4.unkfunc_0204b5a8();
    unkfunc_02018eac();
    unkfunc_0204b5e8((int)&OVERLAY_1_ID);
    data_020f4f74.unkfunc_0204a5f0();
}

ARM void twn::TownPart::onExecutePart()
{
    twn::TownSystem::getSingleton().execute();
}

ARM void twn::TownPart::onDrawPart()
{
    twn::TownSystem::getSingleton().draw();
}

ARM void twn::TownPart::onWindowPart()
{
}

ARM void twn::TownPart::onDebugPart()
{
    twn::TownSystem::getSingleton().debug();
    unkfunc_0202711c();
}
