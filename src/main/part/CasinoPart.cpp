#include "main/part/CasinoPart.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "nitro/gx.h"
#include "nitro/gx.hpp"
#include "nitro/os.hpp"
#include "nnsys/g3d.hpp"
#include "ov012/casino/CasinoSystem.hpp"

casino::CasinoPart g_CasinoPart;

THUMB void casino::CasinoPart::initialize()
{
    func_02075360();
    func_0207534c();
    GX_ResetBankForTex();
    GX_ResetBankForSubObj();
    GX_ResetBankForSubBg();
    GX_SetBankForTex(GX_VRAM_AB);
    data_020f4f74.initVramManagers(0x40000, 0x4000);
    unkfunc_0204c9d8(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    unkfunc_0204afe0();
    loadOverlay((int)&OVERLAY_12_ID);
    ov012_entry();
    loadOverlay((int)&OVERLAY_19_ID);
    ov018_entry();
    CasinoSystem::getSingleton()->initialize();
    func_02082654(1);
    OS_Wait();
    g_Global.fadeIn(30);
}

THUMB void casino::CasinoPart::terminate()
{
    dss::g_Pad.unkfunc_0204bc24(0);
    CasinoSystem::getSingleton()->terminate();
    unloadOverlay((int)&OVERLAY_12_ID);
    unloadOverlay((int)&OVERLAY_19_ID);
    data_020f4f74.onPartTerminate();
}

THUMB void casino::CasinoPart::onExecutePart()
{
    CasinoSystem::getSingleton()->execute();
}

THUMB void casino::CasinoPart::onDrawPart()
{
    CasinoSystem::getSingleton()->draw();
}

THUMB void casino::CasinoPart::onWindowPart()
{
}

THUMB void casino::CasinoPart::onDebugPart()
{
}
