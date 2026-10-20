#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// passing communication: envoy name and message entry
struct UnkMaterielMenu_02187c60 : menu::MenuBase {
    int isForScript_;                                 // 0x1C  opened by a script
    int isError_;                                 // 0x20  error message shown
    short icon_;                               // 0x24  envoy icon
    char messageBackup_[0x88];                          // 0x26  message backup
    signed char mode_;                          // 0xAE
    signed char editMode_;                         // 0xAF  0 name, 1 message
    menu::MenuItem menuItem_;                   // 0xB0
    CursorMoveGridLoop navigator_;           // 0x114

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_02186c38();
    void unkfunc_02186d58();
};

extern UnkMaterielMenu_02187c60 data_ov019_0218616c;
