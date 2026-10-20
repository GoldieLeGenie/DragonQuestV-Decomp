#include "main/part/CeremonyPart.hpp"
#include "main/debug/UnkDebugDisplay.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "nitro/gx.h"
#include "nitro/gx.hpp"
#include "ov004/ceremony/CeremonySystem.hpp"
#include <nitro/os/interrupt.h>

ceremony::CeremonyPart g_CeremonyPart;

ARM void ceremony::CeremonyPart::initialize()
{
    func_02075360();
    func_0207534c();
    GX_ResetBankForTex();
    GX_ResetBankForSubObj();
    GX_ResetBankForSubBg();
    GX_SetBankForTex(GX_VRAM_AB);
    data_020f4f74.initVramManagers(0x40000, 0x4000);
    changeDisplayPlugin(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    setBackgroundGradientEnable(0);
    loadOverlay((int)&OVERLAY_4_ID);
    ov004_entry();
    loadOverlay((int)&OVERLAY_19_ID);
    ov019_entry();
    CeremonySystem::getSingleton()->initialize();
    g_Global.fadeIn(30);
    initDebugDisplay();
}

ARM void ceremony::CeremonyPart::terminate()
{
    CeremonySystem::getSingleton()->terminate();
    unloadOverlay((int)&OVERLAY_4_ID);
    unloadOverlay((int)&OVERLAY_19_ID);
    dss::g_Pad.setMaskL(0);
    data_020f4f74.onPartTerminate();
}

ARM void ceremony::CeremonyPart::onExecutePart()
{
    CeremonySystem::getSingleton()->execute();
}

ARM void ceremony::CeremonyPart::onDrawPart()
{
    CeremonySystem::getSingleton()->draw();
}

ARM void ceremony::CeremonyPart::onWindowPart()
{
}

ARM void ceremony::CeremonyPart::onDebugPart()
{
    updateDebugDisplay();
}

ARM void ceremony::CeremonyPart::onSwapBuffersPart()
{
    BOOL enable = OS_DisableIME();
    REG_GFX_FIFO_SWAP_BUFFERS = 1;
    OS_RestoreIME(enable);
}
