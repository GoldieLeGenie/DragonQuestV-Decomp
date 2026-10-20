#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

// menu showing the debug message pages (methods at 0x02044330)
struct UnkMenu_02044330 : menu::MenuBase {
    int messageQueue_[8];                       // 0x01C message IDs to show
    int unk_3c;                                 // 0x03C
    int messageId_;                             // 0x040 current message
    unsigned char text_[4][0x100];              // 0x044 split message
    int lineCount_;                             // 0x444
    int unk_448;                                // 0x448
    int unk_44c;                                // 0x44C

    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
    void startNextMessage();                    // next message
};

extern UnkMenu_02044330 data_020a2c3c;
