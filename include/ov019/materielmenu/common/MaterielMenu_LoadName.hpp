#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// name entry of the hero when starting a new adventure log
struct MaterielMenu_LoadName : menu::MenuBase {
    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern MaterielMenu_LoadName gMaterielMenu_LoadName;
