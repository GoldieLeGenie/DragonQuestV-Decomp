#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// slime race: waits for the race end and stores the result
struct MaterielMenu_SlimeRace : menu::MenuBase {
    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void dataUpdate();
};

extern MaterielMenu_SlimeRace gMaterielMenu_SlimeRace;
