#include "main/part/SlimeTouchPart.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkOverlaySlot.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/Global.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/TouchData.hpp"
#include "nitro/gx.h"
#include "nitro/gx.hpp"
#include "nitro/os.hpp"
#include "nnsys/g3d.hpp"
#include "ov002/slimetouch/SlimeTouch.hpp"
#include <nitro/os/interrupt.h>

inline void status::MenuStatus::setBooking(int flag)
{
    bookingFlag_ = flag;
}

inline void status::TouchData::setItem(int index, int count)
{
    item_[index].count = count;
}

inline void status::TouchData::setResultFlag(bool flag)
{
    resultFlag_ = flag;
}

inline bool status::TouchData::isResultFlag()
{
    return resultFlag_;
}

touch::SlimeTouchPart g_SlimeTouchPart;
static void* s_work;

THUMB void touch::SlimeTouchPart::initialize()
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
    loadOverlay((int)&OVERLAY_2_ID);
    loadOverlay((int)&OVERLAY_19_ID);
    ov019_entry();
    ST_ARG_SL_TOUCH arg;
    arg.player = 6;
    arg.dbStage = 1;
    arg.dbScore = 0;
    s_work = dssAlloc(&data_020fd24c, 0x80000, 0x20);
    SlimeTouchInit(s_work, 0x80000, &arg);
    func_02082654(1);
    OS_Wait();
    g_Global.fadeIn(30);
    status::g_TouchData.setResultFlag(false);
    status::g_TouchData.setUp();
}

THUMB void touch::SlimeTouchPart::terminate()
{
    dss::g_Pad.unkfunc_0204bc24(0);
    SlimeTouchTerm();
    dssFree(&data_020fd24c, s_work);
    s_work = NULL;
    status::g_Menu.setBooking(10);
    unloadOverlay((int)&OVERLAY_2_ID);
    unloadOverlay((int)&OVERLAY_19_ID);
    data_020f4f74.onPartTerminate();
}

THUMB void touch::SlimeTouchPart::onExecutePart()
{
    SlimeTouchExec();
    ST_ARG_SL_TOUCH arg;
    if (SlimeTouchResult(&arg) && !status::g_TouchData.isResultFlag()) {
        status::g_TouchData.setRanking(arg.score, arg.stage);
        for (int i = 0; i < 17; i++) {
            status::g_TouchData.setItem(i, arg.item[i]);
        }
        g_Global.startTown(g_Global.prevMapNameId);
        status::g_TouchData.setResultFlag(true);
    }
}

THUMB void touch::SlimeTouchPart::onDrawPart()
{
    SlimeTouchDraw();
}

THUMB void touch::SlimeTouchPart::onWindowPart()
{
}

THUMB void touch::SlimeTouchPart::onDebugPart()
{
}

THUMB void touch::SlimeTouchPart::onSwapBuffersPart()
{
    BOOL enable = OS_DisableIME();
    REG_GFX_FIFO_SWAP_BUFFERS = 0;
    OS_RestoreIME(enable);
}
