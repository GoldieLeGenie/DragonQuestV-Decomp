#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster book: list of the monsters, 16 per page (overlay 9)
struct MaterielMenu_PICTUREBOOK_ROOT : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    CursorMoveGridLoop navigator_;           // 0x80
    char m_bookCount;                                // 0x8C book entries
    char m_activeMonster;                       // 0x8D
    char m_nowPage;                             // 0x8E

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool checkPage();
};

extern MaterielMenu_PICTUREBOOK_ROOT gMaterielMenu_PICTUREBOOK_ROOT;
