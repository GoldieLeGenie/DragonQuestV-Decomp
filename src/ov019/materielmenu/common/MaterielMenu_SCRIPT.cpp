#pragma ipa file
#include "ov019/materielmenu/common/MaterielMenu_SCRIPT.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"

inline void MaterielMenu_SCRIPT::menuSetup()
{
}

inline void MaterielMenu_SCRIPT::menuExecute()
{
}

inline void MaterielMenu_SCRIPT::menuUpdate()
{
}

THUMB void MaterielMenu_SCRIPT::menuDraw()
{
    if (drawMode_ == DRAW_GOLD) {
        unkfunc_0201b1cc(-1, -1, 0);
    }
}
