#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// monster keeper: check the new name typed for a monster (or the sack)
struct MaterielMenu_JISAN_CHECK_NAME : menu::MenuBase {
    enum {
        MODE_EDIT = 0,
        MODE_RETRY = 1,
        MODE_CANCEL = 2,
        MODE_ERROR_HUSE = 3,
        MODE_ERROR_RENSHA = 4,
        MODE_ERROR_RENSHA2 = 5,
        MODE_SET_NAME = 6,
        MODE_CURSE_NAME = 7,
        MODE_SOUND = 8,
        MODE_END = 9,
    };

    char mode_;                             // 0x1C
    short target_;                          // 0x1E
    menu::MenuItem menuItem_;               // 0x20
    UnkCursorMoveGridLoop navigator_;       // 0x84

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void selectYes();
    void selectNo();
    void setTargetMacro();
    int getMessageNo(int index);
    void openMessage(int mes1, int mes2, int mes3, int yesno);
};

extern MaterielMenu_JISAN_CHECK_NAME gMaterielMenu_JISAN_CHECK_NAME;
