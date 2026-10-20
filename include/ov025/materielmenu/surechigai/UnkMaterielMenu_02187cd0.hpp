#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// passing communication: received envoys list
struct UnkMaterielMenu_02187cd0 : menu::MenuBase {
    int isShowDetail_;                                 // 0x1C  envoy shown
    unsigned char taishiCount_;                       // 0x20  envoy count
    menu::MenuItem menuItem_;                   // 0x24
    CursorMoveGridLoop navigator_;           // 0x88
    int isDeleteMode_;                                 // 0x94  delete mode
    int deleteStep_;                                 // 0x98

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_02187928();
    void unkfunc_021879ec();
};

extern UnkMaterielMenu_02187cd0 data_ov019_02185864;
