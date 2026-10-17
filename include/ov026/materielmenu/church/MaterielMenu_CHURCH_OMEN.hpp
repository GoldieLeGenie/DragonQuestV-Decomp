#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// church: experience needed by each member for the next level
struct MaterielMenu_CHURCH_OMEN : menu::MenuBase {
    int m_expMessageCount;                      // 0x1C
    int m_firstFlag;                            // 0x20

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool rootUpdate();
    void selectNextExp();
    void oneMessage(int mes);
    int getMessageNo(int index);
};

extern MaterielMenu_CHURCH_OMEN gMaterielMenu_CHURCH_OMEN;
