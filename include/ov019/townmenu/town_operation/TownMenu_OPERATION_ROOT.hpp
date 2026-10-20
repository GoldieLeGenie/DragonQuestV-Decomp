#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"
#include "main/menu/CursorMoveGridLoop.hpp"

namespace status {
    struct UseActionParam;
}

// town misc menu (full recovery, equipment, party order, tactics, item sorting, settings, quit)
struct TownMenu_OPERATION_ROOT : menu::MenuBase {
    enum OPERATION_ROOT_COMMAND {
        OP_MANTAN = 0,
        OP_EQUIP = 1,
        OP_ARRAY = 2,
        OP_TACTICS = 3,
        OP_SORTITEM = 4,
        OP_SORTFUKURO = 5,
        OP_SETTING = 6,
        OP_ABORT = 7,
        OP_EOF = 8,
    };
    enum MODE_TYPE {
        MODE_SORT_NONE = 0,
        MODE_ALL_RECOVERY = 1,
    };

    unsigned char mode_;                        // 0x1C
    unsigned char abortMode_;                   // 0x1D
    unsigned char unk_1e;                       // 0x1E
    unsigned char seCount_;                     // 0x1F
    unsigned short actionIndex_;                // 0x20
    int saveResult_;                            // 0x24
    int isMantan_;                              // 0x28
    menu::MenuItem menuItem_;                   // 0x2C
    CursorMoveGridLoop navigator_;           // 0x90

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void hpMax();
    void boxUpArray();
    void allRecoveryMessage(status::UseActionParam& useActionParam);
    void unkfunc_02175c8c();
};

extern TownMenu_OPERATION_ROOT gTownMenu_OPERATION_ROOT;
