#include "main/part/FieldPart.hpp"
#include "main/debug/UnkDebugDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "nitro/gx.h"
#include "nitro/gx.hpp"
#include "ov005/fld/FieldSystem.hpp"
#include "ov005/fld/FieldWindowSystem.hpp"
#include <nitro/os/interrupt.h>

fld::FieldPart g_FieldPart;

ARM void fld::FieldPart::initialize()
{
    func_02075360();
    func_0207534c();
    GX_ResetBankForTex();
    GX_ResetBankForSubObj();
    GX_ResetBankForSubBg();
    GX_SetBankForTex(GX_VRAM_AB);
    data_020f4f74.unkfunc_0204a53c(0x40000, 0x4000);
    unkfunc_0204c9d8(&dss::g_DISPLAYPLUGIN_DOUBLE3D);
    unkfunc_02048728(0);
    unkfunc_0204b5d4((int)&OVERLAY_5_ID);
    ov005_entry();
    unkfunc_02018e6c(1);
    ov019_entry();
    FieldSystem::getSingleton()->initialize();
    FieldWindowSystem::getSingleton()->initialize();
    g_Global.fadeIn(30);
    unkfunc_020270dc();
}

ARM void fld::FieldPart::terminate()
{
    FieldWindowSystem::getSingleton()->terminate();
    FieldSystem::getSingleton()->terminate();
    unkfunc_02018eac();
    unkfunc_0204b5e8((int)&OVERLAY_5_ID);
    dss::g_Pad.unkfunc_0204bc24(0);
    data_020f4f74.unkfunc_0204a5f0();
}

ARM void fld::FieldPart::onExecutePart()
{
    FieldSystem::getSingleton()->execute();
    FieldWindowSystem::getSingleton()->execute();
}

ARM void fld::FieldPart::onDrawPart()
{
    FieldSystem::getSingleton()->draw();
    FieldWindowSystem::getSingleton()->draw();
}

ARM void fld::FieldPart::onWindowPart()
{
}

ARM void fld::FieldPart::onDebugPart()
{
    unkfunc_0202711c();
}

ARM void fld::FieldPart::onSwapBuffersPart()
{
    BOOL enable = OS_DisableIME();
    REG_GFX_FIFO_SWAP_BUFFERS = 1;
    OS_RestoreIME(enable);
}
