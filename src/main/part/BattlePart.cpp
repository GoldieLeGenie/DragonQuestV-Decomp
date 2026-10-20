#include "main/part/BattlePart.hpp"
#include "main/btl/UnkBattleSystem.hpp"
#include "main/debug/UnkDebugDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "nitro/gx.h"
#include "nitro/gx.hpp"
#include "nnsys/g3d.hpp"
#include "ov000/btl/BattleSystem.hpp"

btl::BattlePart g_BattlePart;

ARM void btl::BattlePart::initialize()
{
    func_02075360();
    func_0207534c();
    GX_ResetBankForTex();
    GX_ResetBankForSubObj();
    GX_ResetBankForSubBg();
    GX_SetBankForTex(GX_VRAM_ABCD);
    data_020f4f74.initVramManagers(0x80000, 0x4000);
    changeDisplayPlugin(&dss::g_DISPLAYPLUGIN_SINGLE3D);
    loadOverlay((int)&OVERLAY_0_ID);
    ov000_entry();
    unkfunc_02018e6c(2);
    ov018_entry();
    data_020a29f4.unload();
    BattleSystem::getSingleton()->initialize();
    UnkBattleSystem::getSingleton()->initialize();
    func_02082654(1);
    g_Global.fadeIn(30);
    dss::g_Pad.setMaskL(0);
    initDebugDisplay();
}

ARM void btl::BattlePart::terminate()
{
    dss::g_Pad.setMaskL(0);
    UnkBattleSystem::getSingleton()->terminate();
    BattleSystem::getSingleton()->terminate();
    unkfunc_02018eac();
    unloadOverlay((int)&OVERLAY_0_ID);
    data_020f4f74.onPartTerminate();
}

ARM void btl::BattlePart::onExecutePart()
{
    BattleSystem::getSingleton()->execute();
}

ARM void btl::BattlePart::onDrawPart()
{
    BattleSystem::getSingleton()->draw();
}

ARM void btl::BattlePart::onWindowPart()
{
    UnkBattleSystem::getSingleton()->execute();
    UnkBattleSystem::getSingleton()->draw();
}

ARM void btl::BattlePart::onDebugPart()
{
    updateDebugDisplay();
}
