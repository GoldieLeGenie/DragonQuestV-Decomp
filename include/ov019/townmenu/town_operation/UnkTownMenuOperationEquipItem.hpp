#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

// town misc menu: equipment, selection of the item of each equipment type
struct UnkTownMenuOperationEquipItem : menu::MenuBase {
    int itemListActive_;                        // 0x1C
    short itemPosList_[12];                     // 0x20
    char itemCount_;                            // 0x38
    char itemType_;                             // 0x39
    menu::MenuItem itemItem_;                   // 0x3C
    menu::MenuItem removeItem_;                 // 0xA0
    CursorMoveGridLoop itemNavigator_;       // 0x104
    CursorMoveGridLoop removeNavigator_;     // 0x110

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void setItemTypeList();
    void unkfunc_02176424();
    void unkfunc_021764c0();
    void unkfunc_02176528();
};

extern UnkTownMenuOperationEquipItem data_ov019_02183b54;
