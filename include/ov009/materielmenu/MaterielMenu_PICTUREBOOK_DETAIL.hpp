#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster book: page of one monster (overlay 9)
struct MaterielMenu_PICTUREBOOK_DETAIL : menu::MenuBase {
    menu::MenuItem menuItem_;                   // 0x1C
    UnkCursorMoveGridLoop navigator_;           // 0x80
    short activeMonster_;                       // 0x8C book index
    short monsterIndex_;                        // 0x8E
    int isOpen_;                                // 0x90

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void checkPage(bool next);
};

extern MaterielMenu_PICTUREBOOK_DETAIL gMaterielMenu_PICTUREBOOK_DETAIL;
