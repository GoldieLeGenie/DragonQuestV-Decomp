#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// casino slot menu (overlay 12)
struct MaterielMenu_SLOT : menu::MenuBase {
    enum {
        SLOT_START = 0,
        SLOT_GAME = 1,
        SLOT_RESULT = 2,
        SLOT_RESULT_EFFECT = 3,
        SLOT_RETRY = 4,
        SLOT_END = 5,
    };
    static const short MAX_BETCOIN = 9;

    unsigned char unk_1c[0x84 - 0x1c];      // 0x1C
    menu::MenuItem menuItem_;               // 0x84
    int status_;                            // 0xE8
    int messageCount_;                      // 0xEC
    int betCost_;                           // 0xF0
    int betCoin_;                           // 0xF4
    int haveCoin_;                          // 0xF8
    int resultCoin_;                        // 0xFC
    int slotType_;                          // 0x100

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    bool messageUpdate();
    void statusUpdate();
    void inputUpdate();
    void showEffect();
    void startSlot();
    void showMessage(int messageID);
    void closeMessage();
};

extern MaterielMenu_SLOT gMaterielMenu_SLOT;
