#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// passing communication: envoy information of a museum pedestal
struct UnkMaterielMenu_02187cec : menu::MenuBase {
    int museumItem_;                                 // 0x1C  museum item
    int mapId_;                                 // 0x20  map
    int iconId_;                                 // 0x24  icon
    menu::MenuItem menuItem_;                   // 0x28
    CursorMoveGridLoop navigator_;           // 0x8C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setTaishiMessageMacros(int index);
};

extern UnkMaterielMenu_02187cec data_ov019_02185604;
