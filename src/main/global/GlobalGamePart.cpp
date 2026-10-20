#include "GameInfo.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/global/Global.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/Pad.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkFog.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/dss/UnkSleep.hpp"
#include "main/dss/Sprite2D.hpp"
#include "main/dss/UnkVramRequest.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/menu/MenuManager.hpp"
#include "main/menu/UnkMenuSystem.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/sound/UnkNnsSound.hpp"
#include "main/text/TextAPI.hpp"
#include "main/window/UnkMapPoint.hpp"
#include "nitro/g3.hpp"
#include "nitro/gx.h"
#include "nitro/os.hpp"
#include <nitro/os/interrupt.h>

enum UnkFadeResult {
    FADE_RUNNING = 0,
    FADE_END = 1,
};

inline GlobalSpriteFade::GlobalSpriteFade()
{
    sprite_[0].unkfunc_02047e88(0, 0);
    sprite_[0].setSize(256, 192);
    sprite_[0].texture_ = NULL;
    sprite_[0].screens_ = 1;
    sprite_[0].setColor(0, 0, 0);
    sprite_[0].setPolygonID(63);
    sprite_[0].setAlpha(0);
    sprite_[0].depth_ = 0;
    sprite_[1].unkfunc_02047e88(0, 0);
    sprite_[1].setSize(256, 192);
    sprite_[1].texture_ = NULL;
    sprite_[1].screens_ = 2;
    sprite_[1].setColor(0, 0, 0);
    sprite_[1].setAlpha(0);
    sprite_[1].setPolygonID(63);
    sprite_[1].depth_ = 0;
}

static void unkfunc_02067a58();
static void updatePolygonOverflow();
static void updateRenderedLines();

int data_0209aea0 = 2;
static unsigned int s_swapLine;
static unsigned int s_frameEndLine;
static int s_unk28;
static void (*s_callback)();
static unsigned int s_drawLine;
static unsigned int s_endLine;
static unsigned int s_renderedLines;
static int s_unk14;
static int s_textureSize;
static int s_polygonOverflow;
args::GamePart data_0211b150;
static long long s_taskTick;
static unsigned int s_lineLog[2][16];
static unsigned int s_tickLog[2][16];
GlobalSpriteFade data_0211b27c;

ARM void args::GamePart::vf00()
{
    s_taskTick = getTick();
    func_020624b0();
    TextAPI::Init();
    data_020f4f74.vblankTransfer_ = 1;
    initialize();
    data_020f4f74.vblankTransfer_ = 0;
    unkfunc_02067a58();
    data_02101584.unkfunc_0205027c();
    func_020624bc();
    TextAPI::unkfunc_0206cc94();
    s_taskTick = getTick() - s_taskTick;
}

ARM void args::GamePart::initialize()
{
}

ARM void args::GamePart::vf04()
{
    s_taskTick = getTick();
    data_020f6f9c.clear();
    func_020624c8();
    TextAPI::unkfunc_0206cc98();
    data_02101584.unkfunc_0205027c();
    terminate();
    unkfunc_02067a58();
    data_02101584.unkfunc_0205027c();
    s_taskTick = getTick() - s_taskTick;
}

ARM void args::GamePart::terminate()
{
}

ARM void args::GamePart::vf08()
{
    func_02075c44();
    func_02075d70();
    dss::g_Pad.update();
    clearOamBuffers();
    func_020624cc();
    TextAPI::unkfunc_0206cd20();
}

ARM void args::GamePart::vf10()
{
    updateSleep();
    if (GX_GetVCount() > 180) {
        while (GX_GetVCount() > 180) {
        }
    }
    s_swapLine = GX_GetVCount();
    func_020624e8();
    TextAPI::unkfunc_0206cd2c();
    func_02082604();
    onSwapBuffersPart();
    func_02052180();
    updateFog();
    s_drawLine = GX_GetVCount();
    OS_Wait();
    updatePolygonOverflow();
    updateRenderedLines();
    updateScreenCapture();
    s_textureSize = data_020f4f74.texSize_;
    data_020f4f74.doTransfers();
    s_frameEndLine = GX_GetVCount();
    if (REG_GFX_VTX_RAM_COUNT == 0) {
        updateDisplay();
        flushVramRequests();
    }
    data_02101d14.unkfunc_02051958();
    s_endLine = GX_GetVCount();
}

ARM void args::GamePart::vf0c()
{
    int index = (getDisplayFrame() & 1) ? 0 : 1;
    s_tickLog[index][0] = getTick();
    s_lineLog[index][0] = GX_GetVCount();
    func_020624d8();
    TextAPI::unkfunc_0206cd28();
    if (unkfunc_02067ac0()) {
        onExecutePart();
        unkfunc_02067a58();
    }
    s_tickLog[index][1] = getTick();
    s_lineLog[index][1] = GX_GetVCount();
    onDrawPart();
    s_tickLog[index][2] = getTick();
    s_lineLog[index][2] = GX_GetVCount();
    setupOrtho2DFine();
    data_0211b27c.sprite_[0].draw();
    data_0211b27c.sprite_[1].draw();
    onWindowPart();
    s_tickLog[index][3] = getTick();
    s_lineLog[index][3] = GX_GetVCount();
    onDebugPart();
    s_tickLog[index][4] = getTick();
    s_lineLog[index][4] = GX_GetVCount();
    data_02101d14.unkfunc_02051908();
    data_02101584.unkfunc_0205027c();
    s_tickLog[index][5] = getTick();
    s_lineLog[index][5] = GX_GetVCount();
    if (s_callback) {
        s_callback();
    }
    while (REG_GFX_STATUS & 0x8000000) {
    }
    s_tickLog[index][6] = getTick();
    s_lineLog[index][6] = GX_GetVCount();
    s_tickLog[index][7] = getTick();
    s_lineLog[index][7] = GX_GetVCount();
    s_tickLog[index][8] = getTick();
    s_lineLog[index][8] = GX_GetVCount();
}

ARM void args::GamePart::onExecutePart()
{
}

ARM void args::GamePart::onDrawPart()
{
}

ARM void args::GamePart::onWindowPart()
{
}

ARM void args::GamePart::onDebugPart()
{
}

ARM static void unkfunc_02067a58()
{
    unkfunc_0204afdc();
}

ARM static void updatePolygonOverflow()
{
    if (!(REG_DISP3DCNT & 0x1000)) {
        s_polygonOverflow = 0;
        return;
    }
    REG_DISP3DCNT |= 0x1000;
    s_polygonOverflow = 1;
}

ARM static void updateRenderedLines()
{
    s_renderedLines = REG_RDLINES_COUNT;
}

ARM int args::GamePart::unkfunc_02067ac0()
{
    return MenuManager::isExtraMenu() == 0;
}

ARM void args::GamePart::onSwapBuffersPart()
{
    BOOL enable = OS_DisableIME();
    REG_GFX_FIFO_SWAP_BUFFERS = 3;
    OS_RestoreIME(enable);
}

ARM void unkfunc_02067b00(void (*callback)())
{
    s_callback = callback;
}

ARM int GlobalSpriteFade::isEnd()
{
    return count_ != frames_ ? FADE_RUNNING : FADE_END;
}

ARM void GlobalSpriteFade::draw()
{
}

ARM void GlobalSpriteFade::update()
{
    count_++;
    count_ = dss::clamp<int>(count_, 0, frames_);
    alpha_ = count_ * 31 / frames_;
    switch (state_) {
    case FadeEffector::FADE_NONE:
        break;
    case FadeEffector::FADE_OUT_BLACK:
        alpha_ = 31 - alpha_;
        break;
    case FadeEffector::FADE_OUT_WHITE:
        alpha_ = 31 - alpha_;
        break;
    case 6:
        alpha_ = 31 - alpha_;
        break;
    }
    alpha_ = dss::clamp<int>(alpha_, 0, 31);
    sprite_[0].setAlpha((unsigned char)alpha_);
    sprite_[1].setAlpha((unsigned char)alpha_);
}
