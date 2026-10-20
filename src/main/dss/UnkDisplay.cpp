#include "main/dss/UnkDisplay.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "nitro/g2.hpp"

inline int dss::UnkDisplayPlugin::getType()
{
    return type_;
}

THUMB UnkDisplay::UnkDisplay()
{
    oam_[0].unkfunc_0204db88();
    oam_[1].unkfunc_0204db88();
    unkfunc_0204c9d8(NULL);
    unkfunc_0204ccdc(0);
    unkfunc_0204cce8(0x7c0f);
    data_020fe6b0.capture_ = 0;
    data_020fe6b0.captureStep_ = 0;
    data_020fe6b0.captureX_ = -4;
    data_020fe6b0.captureY_ = -4;
    data_020fe6b0.blendA_ = 10;
    data_020fe6b0.blendB_ = 5;
}

UnkDisplay data_020fe6b0;

THUMB void unkfunc_0204c9ac(int* x, int* y)
{
    *x = data_020fe6b0.captureX_;
    *y = data_020fe6b0.captureY_;
}

THUMB void unkfunc_0204c9bc(int x, int y)
{
    data_020fe6b0.captureX_ = x;
    data_020fe6b0.captureY_ = y;
}

THUMB void unkfunc_0204c9c8()
{
    data_020fe6b0.captureX_ = -4;
    data_020fe6b0.captureY_ = -4;
}

THUMB void unkfunc_0204c9d8(dss::UnkDisplayPlugin* plugin)
{
    UnkDisplay* display = &data_020fe6b0;
    unkfunc_0204e83c(&data_020fe6b0.screen_, data_020fe6b0.screenData_, 32, 48);
    data_020fe6b0.nextPlugin_ = plugin;
    data_020fe6b0.plugin_ = plugin;
    data_020fe6b0.frame_ = 0;
    data_020fe6b0.blendMode_ = 0;
    unkfunc_0204ccf4(2);
    unkfunc_0204ccdc(0);
    if (plugin == NULL) {
        return;
    }
    plugin->initialize();
    MI_CpuFill(0xc0, (void*)0x07000000, 0x400);
    MI_CpuFill(0xc0, (void*)0x07000400, 0x400);
    display->oam_[0].unkfunc_0204db8c();
    display->oam_[1].unkfunc_0204db8c();
}

THUMB void unkfunc_0204ca54()
{
    data_020fe6b0.oam_[0].unkfunc_0204db8c();
    data_020fe6b0.oam_[1].unkfunc_0204db8c();
}

THUMB void unkfunc_0204ca6c()
{
    UnkDisplay* display = &data_020fe6b0;
    if (unkfunc_0204cca8()) {
        int odd = getDisplayFrame() & 1;
        int bg = unkfunc_0204ced8(odd * 192);
        if (bg != -1) {
            unkfunc_0204dca8(unkfunc_0204de5c(bg), 0, display->screenData_[odd], sizeof(display->screenData_[0]));
        }
    }
    if (!(display->frame_ & 1) && display->plugin_ != display->nextPlugin_) {
        if (display->plugin_ != NULL) {
            display->plugin_->finalize();
        }
        unkfunc_0204d068(0);
        unkfunc_0204d074(0);
        unkfunc_0204c9d8(display->nextPlugin_);
    }
    display->plugin_->update(display->frame_);
    display->plugin_->updateDisplayText();
    display->frame_++;
    getBgPaletteBuffer(1)->unkfunc_0204dbe8(0, 0, display->backColor_);
    getBgPaletteBuffer(5)->unkfunc_0204dbe8(0, 0, display->backColor_);
    display->bgPalette_[0].unkfunc_0204dbd4(0xf);
    display->bgPalette_[1].unkfunc_0204dbd4(0x1f);
    display->objPalette_[0].unkfunc_0204dbd4(0xe);
    display->objPalette_[1].unkfunc_0204dbd4(0x1e);
    display->oam_[0].unkfunc_0204dbb0(0x12);
    display->oam_[1].unkfunc_0204dbb0(0x22);
    G2_SetWndOutsidePlane(0x1f, 1);
    int window0 = display->windowEnable_[0];
    int window1 = display->windowEnable_[1];
    if (display->plugin_ == &dss::g_DISPLAYPLUGIN_DOUBLE3D && (getDisplayFrame() & 1) == 1) {
        window0 = 0;
        window1 = 0;
    }
    if (window0 != 0) {
        G2_SetWnd0InsidePlane(display->window_[0].plane_, 1);
        G2_SetWnd0Position(display->window_[0].x_, display->window_[0].y_, display->window_[0].x_ + display->window_[0].w_,
                           display->window_[0].y_ + display->window_[0].h_);
    } else {
        G2_SetWnd0InsidePlane(0x1f, 1);
        G2_SetWnd0Position(0, 0, 0, 0);
    }
    if (window1 != 0) {
        G2_SetWnd1InsidePlane(display->window_[1].plane_, 1);
        G2_SetWnd1Position(display->window_[1].x_, display->window_[1].y_, display->window_[1].x_ + display->window_[1].w_,
                           display->window_[1].y_ + display->window_[1].h_);
    } else {
        G2_SetWnd1InsidePlane(0x1f, 1);
        G2_SetWnd1Position(0, 0, 0, 0);
    }
}

THUMB void unkfunc_0204cc9c(dss::UnkDisplayPlugin* plugin)
{
    data_020fe6b0.nextPlugin_ = plugin;
}

THUMB int unkfunc_0204cca8()
{
    UnkDisplay* display = &data_020fe6b0;
    if (display->text_.type_ == 0) {
        return 0;
    }
    return display->plugin_ == display->nextPlugin_;
}

THUMB int getDisplayFrame()
{
    return data_020fe6b0.frame_;
}

THUMB void unkfunc_0204ccdc(unsigned short color)
{
    data_020fe6b0.backColor_ = color;
}

THUMB void unkfunc_0204cce8(unsigned short value)
{
    data_020fe6b0.unk_0e = value;
}

THUMB void unkfunc_0204ccf4(int mode)
{
    UnkDisplay* display = &data_020fe6b0;
    *(volatile unsigned short*)0x04000050 = 0;
    *(volatile unsigned short*)0x04001050 = 0;
    if (display->blendMode_ == 1) {
        mode = 1;
    }
    int eva = display->blendA_;
    int evb = display->blendB_;
    switch (mode) {
    case 0:
        break;
    case 1:
        func_02075aa0((unsigned int*)0x04001050, 0x3d, -8);
        break;
    case 2:
        _G2_SetBlend((unsigned int*)0x04000050, 5, 0x3b, eva, evb);
        _G2_SetBlend((unsigned int*)0x04001050, 5, 0x3b, eva, evb);
        break;
    case 3:
        _G2_SetBlend((unsigned int*)0x04000050, 1, 0x3e, eva, evb);
        _G2_SetBlend((unsigned int*)0x04001050, 1, 0x3e, eva, evb);
        break;
    }
}

THUMB UnkPaletteBuffer* getBgPaletteBuffer(int bg)
{
    UnkDisplay* display = &data_020fe6b0;
    switch (bg) {
    case 0:
        return &display->bgPalette_[0];
    case 1:
        return &display->bgPalette_[0];
    case 2:
        return &display->bgPalette_[0];
    case 3:
        return &display->bgPalette_[0];
    case 4:
        return &display->bgPalette_[1];
    case 5:
        return &display->bgPalette_[1];
    case 6:
        return &display->bgPalette_[1];
    case 7:
        return &display->bgPalette_[1];
    }
    return NULL;
}

THUMB UnkPaletteBuffer* getObjPaletteBuffer(int screen)
{
    UnkDisplay* display = &data_020fe6b0;
    switch (screen) {
    case 0:
        return &display->objPalette_[0];
    case 1:
        return &display->objPalette_[1];
    }
    return NULL;
}

THUMB UnkOamBuffer* unkfunc_0204ce18(int screen)
{
    UnkDisplay* display = &data_020fe6b0;
    switch (screen) {
    case 0:
        return &display->oam_[0];
    case 1:
        return &display->oam_[1];
    }
    return NULL;
}

THUMB UnkOamBuffer* unkfunc_0204ce40(int y)
{
    UnkDisplay* display = &data_020fe6b0;
    int screen = 0;
    if (display->plugin_ == NULL) {
        return NULL;
    }
    if (display->nextPlugin_ == NULL) {
        return NULL;
    }
    if (y < 0) {
        return NULL;
    }
    if (y >= 384) {
        return NULL;
    }
    switch (display->text_.type_) {
    case 0:
        return NULL;
    case 1:
        if (y >= 192) {
            screen = 1;
        }
        break;
    case 2:
        if (y < 192) {
            screen = 1;
        }
        break;
    case 3:
        if ((getDisplayFrame() & 1) == 0) {
            if (y >= 192) {
                return NULL;
            }
        } else {
            if (y < 192) {
                return NULL;
            }
        }
        screen = 0;
        break;
    }
    switch (screen) {
    case 0:
        return &display->oam_[0];
    case 1:
        return &display->oam_[1];
    }
    return NULL;
}

THUMB int unkfunc_0204ced8(int y)
{
    UnkDisplay* display = &data_020fe6b0;
    int ret = 0;
    if (display->plugin_ == NULL) {
        return -1;
    }
    if (display->nextPlugin_ == NULL) {
        return -1;
    }
    if (y < 0) {
        return -1;
    }
    if (y >= 384) {
        return -1;
    }
    switch (display->text_.type_) {
    case 0:
        ret = -1;
        break;
    case 1:
        ret = y < 192 ? display->text_.screen1_ : display->text_.screen2_;
        break;
    case 2:
        ret = y < 192 ? display->text_.screen2_ : display->text_.screen1_;
        break;
    case 3:
        if ((getDisplayFrame() & 1) == 0) {
            if (y >= 192) {
                return -1;
            }
        } else {
            if (y < 192) {
                return -1;
            }
        }
        ret = display->text_.screen1_;
        break;
    }
    return ret;
}

THUMB int unkfunc_0204cf7c(int y)
{
    UnkDisplay* display = &data_020fe6b0;
    int ret = 0;
    if (display->plugin_ == NULL) {
        return -1;
    }
    if (display->nextPlugin_ == NULL) {
        return -1;
    }
    if (y < 0) {
        return -1;
    }
    if (y >= 384) {
        return -1;
    }
    switch (display->text_.type_) {
    case 0:
        ret = -1;
        break;
    case 1:
        ret = y < 192 ? display->text_.unk_0c : display->text_.unk_10;
        break;
    case 2:
        ret = y < 192 ? display->text_.unk_10 : display->text_.unk_0c;
        break;
    case 3:
        if ((getDisplayFrame() & 1) == 0) {
            if (y >= 192) {
                return -1;
            }
        } else {
            if (y < 192) {
                return -1;
            }
        }
        ret = display->text_.unk_0c;
        break;
    }
    return ret;
}

THUMB void unkfunc_0204d020(int type, int screen1, int screen2, int unk_0c, int unk_10, int unk_14)
{
    data_020fe6b0.text_.type_ = type;
    data_020fe6b0.text_.screen1_ = screen1;
    data_020fe6b0.text_.screen2_ = screen2;
    data_020fe6b0.text_.unk_0c = unk_0c;
    data_020fe6b0.text_.unk_10 = unk_10;
    data_020fe6b0.text_.unk_14 = unk_14;
}

THUMB int unkfunc_0204d03c()
{
    return data_020fe6b0.text_.unk_14;
}

THUMB UnkScreenBuffer* getDebugScreenBuffer()
{
    return &data_020fe6b0.screen_;
}

THUMB void setDisplayTextCounter(int counter)
{
    if (data_020fe6b0.plugin_ != NULL) {
        data_020fe6b0.plugin_->setDisplayText(counter);
    }
}

THUMB void unkfunc_0204d068(int enable)
{
    data_020fe6b0.windowEnable_[0] = enable;
}

THUMB void unkfunc_0204d074(int enable)
{
    data_020fe6b0.windowEnable_[1] = enable;
}

THUMB void unkfunc_0204d080(int plane, int x, int y, int w, int h)
{
    data_020fe6b0.window_[0].plane_ = plane;
    data_020fe6b0.window_[0].x_ = x;
    data_020fe6b0.window_[0].y_ = y;
    data_020fe6b0.window_[0].w_ = w;
    data_020fe6b0.window_[0].h_ = h;
}

THUMB void unkfunc_0204d098(int plane, int x, int y, int w, int h)
{
    data_020fe6b0.window_[1].plane_ = plane;
    data_020fe6b0.window_[1].x_ = x;
    data_020fe6b0.window_[1].y_ = y;
    data_020fe6b0.window_[1].w_ = w;
    data_020fe6b0.window_[1].h_ = h;
}

THUMB int unkfunc_0204d0b8()
{
    if (data_020fe6b0.plugin_ == NULL) {
        return 0;
    }
    return data_020fe6b0.plugin_->getType();
}

THUMB void unkfunc_0204d0cc()
{
    data_020fe6b0.capture_ = 1;
    data_020fe6b0.captureStep_ = 0;
    dss::g_DISPLAYPLUGIN_DOUBLE3D.ReqBlurMode(1);
    dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(0, 0x10);
}

THUMB void unkfunc_0204d0f4()
{
    UnkDisplay* display = &data_020fe6b0;
    if (data_020fe6b0.capture_ == 0) {
        return;
    }
    GX_ResetBankForSubBg();
    GX_ResetBankForSubObj();
    switch (display->captureStep_) {
    case 0:
        data_020f4f74.transferToVram(0, (void*)0x06860000, 0, 0x8000, 0);
        break;
    case 1:
        data_020f4f74.transferToVram(0, (void*)0x06868000, 0x8000, 0x8000, 0);
        break;
    case 2:
        data_020f4f74.transferToVram(0, (void*)0x06870000, 0x10000, 0x8000, 0);
        break;
    case 3:
        data_020f4f74.transferToVram(0, (void*)0x06840000, 0x20000, 0x8000, 0);
        break;
    case 4:
        data_020f4f74.transferToVram(0, (void*)0x06848000, 0x28000, 0x8000, 0);
        break;
    case 5:
        data_020f4f74.transferToVram(0, (void*)0x06850000, 0x30000, 0x8000, 0);
        break;
    }
    if (display->captureStep_ < 6) {
        display->captureStep_++;
    }
    if (display->captureStep_ == 6) {
        display->capture_ = 0;
    }
}

THUMB int unkfunc_0204d1f4()
{
    return data_020fe6b0.captureStep_ == 6;
}
