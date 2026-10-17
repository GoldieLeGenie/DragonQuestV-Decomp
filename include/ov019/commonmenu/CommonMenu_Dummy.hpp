#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// small window showing the name of the current map
struct CommonMenu_Dummy : menu::MenuBase {
    int mapInfo_;                               // 0x1C  0: hidden

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setMapInfo(int mapInfo);
};

extern CommonMenu_Dummy gTownMenu_MapInfo;
