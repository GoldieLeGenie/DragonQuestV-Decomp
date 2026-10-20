#include "main/part/BookPart.hpp"
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
#include "ov009/book/BookSystem.hpp"

book::BookPart g_BookPart;

THUMB void book::BookPart::initialize()
{
    func_02075360();
    func_0207534c();
    GX_ResetBankForTex();
    GX_ResetBankForSubObj();
    GX_ResetBankForSubBg();
    GX_SetBankForTex(GX_VRAM_AB);
    data_020f4f74.unkfunc_0204a53c(0x40000, 0x4000);
    unkfunc_0204c9d8(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    unkfunc_0204afe0();
    unkfunc_0204b5d4((int)&OVERLAY_9_ID);
    ov009_entry();
    unkfunc_0204b5d4((int)&OVERLAY_19_ID);
    ov018_entry();
    BookSystem::getSingleton().initialize();
    func_02082654(1);
    OS_Wait();
    g_Global.fadeIn(30);
}

THUMB void book::BookPart::terminate()
{
    dss::g_Pad.unkfunc_0204bc24(0);
    BookSystem::getSingleton().terminate();
    unkfunc_0204b5e8((int)&OVERLAY_9_ID);
    unkfunc_0204b5e8((int)&OVERLAY_19_ID);
    data_020f4f74.unkfunc_0204a5f0();
}

THUMB void book::BookPart::onExecutePart()
{
    BookSystem::getSingleton().execute();
}

THUMB void book::BookPart::onDrawPart()
{
    BookSystem::getSingleton().draw();
}

THUMB void book::BookPart::onWindowPart()
{
}

THUMB void book::BookPart::onDebugPart()
{
}
