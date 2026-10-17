#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/UnkCursorMoveGridLoop.hpp"

// town item menu: selection of the character (or the bag) whose items are listed
struct UnkTownMenuItemCharaSelect : menu::MenuBase {
    int fromMateriel_;                          // 0x1C  1: opened by a materiel menu window
    int unk_20;                                 // 0x20  close the town menu after the message
    unsigned char charaCount_;                  // 0x24
    menu::MenuItem menuItem_;                   // 0x28
    UnkCursorMoveGridLoop navigator_;           // 0x8C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void unkfunc_02178480();
};

extern UnkTownMenuItemCharaSelect data_ov019_02183524;
