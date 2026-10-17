#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// name entry of the hero's children
struct MaterielMenu_ChildName : menu::MenuBase {
    int childType_;                             // 0x1C  player index of the child

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setChildType(int type);
};

extern MaterielMenu_ChildName data_ov019_02183e74;
