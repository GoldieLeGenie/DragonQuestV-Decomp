#pragma once
#include <globaldefs.h>
#include "nitro/fx.hpp"

namespace dss {
    // display mode of the two screens (mobile dss_displayplugin.h)
    struct UnkDisplayPlugin {
        virtual void initialize();
        virtual void finalize();
        virtual void update(int frame);

        int displayTextCounter_;                // 0x04
        int type_;                              // 0x08

        void drawCaptureObjs(int chr);         // OAM of the captured screen
        void setupDisplayText(int textType, int screen1, int screen2, int bg0, int bg1, int unk_10, int palette);   // setup the text
        void updateDisplayText();
        void setDisplayText(int counter);
        int getType();
    };

    struct UnkDisplayPluginTextonly : UnkDisplayPlugin {
        virtual void initialize();
        virtual void finalize();
        virtual void update(int frame);
    };

    struct UnkDisplayPluginStop : UnkDisplayPlugin {
        virtual void initialize();
        virtual void finalize();
        virtual void update(int frame);
    };

    struct UnkDisplayPluginSingle3d : UnkDisplayPlugin {
        virtual void initialize();
        virtual void finalize();
        virtual void update(int frame);
    };

    struct UnkDisplayPluginDouble3d : UnkDisplayPlugin {
        virtual void initialize();
        virtual void finalize();
        virtual void update(int frame);
        void ReqBlurMode(int blur);
        void SetBlur(int eva, int evb);

        int blur_;                              // 0x0C
        int eva_;                               // 0x10
        int evb_;                               // 0x14
    };

    struct UnkDisplayPluginCapture : UnkDisplayPlugin {
        virtual void initialize();
        virtual void finalize();
        virtual void update(int frame);
    };

    extern UnkDisplayPluginStop g_DISPLAYPLUGIN_STOP;
    extern UnkDisplayPluginTextonly g_DISPLAYPLUGIN_TEXTONLY;
    extern UnkDisplayPluginDouble3d g_DISPLAYPLUGIN_DOUBLE3D;
    extern UnkDisplayPluginSingle3d g_DISPLAYPLUGIN_SINGLE3D;
    extern UnkDisplayPluginCapture g_DISPLAYPLUGIN_CAPTURE;
}

extern "C" {
    void func_020749e4(int bg, int unk);        // BG VRAM bank
    void func_020759d4(volatile void* reg, const MtxFx22* mtx, int centerX, int centerY, int x, int y);   // BG affine
}
