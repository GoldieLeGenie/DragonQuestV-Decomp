#pragma once
#include <globaldefs.h>
#include "main/menu/MenuFrameDisplay.hpp"
#include "main/menu/MenuFaceDisplay.hpp"
#include "main/menu/MenuIconDisplay.hpp"
#include "main/menu/UnkMenuDummyDisplay.hpp"
#include "main/menu/MessageWindow.hpp"
#include "main/menu/UnkMenuYesNoDisplay.hpp"
#include "main/menu/UnkMenuTextDisplay.hpp"
#include "main/menu/MenuWindowFrame.hpp"
#include "main/menu/UnkMenuSpriteDisplay.hpp"
#include "main/menu/MenuArrowDisplay.hpp"

// Menu display objects, set up, updated and drawn together by setupMenuDisplays...unkfunc_02064154
struct UnkMenuDisplays {
    MenuFrameDisplay frames_;                // 0x0000
    MenuFaceDisplay face_;                   // 0x1034
    MenuIconDisplay icon_;                   // 0x1070
    UnkMenuDummyDisplay dummy_;                 // 0x10E0
    MessageWindow message_;                     // 0x1110
    UnkMenuYesNoDisplay yesNo_;                 // 0x2B1C
    UnkMenuTextDisplay texts_[4];               // 0x2E74
    MenuWindowFrame windowFrame1_;           // 0x5DD4
    MenuWindowFrame windowFrame2_;           // 0x5E24
    UnkMenuSpriteDisplay sprite_;               // 0x5E74
    MenuArrowDisplay arrow_;                 // 0x5EE4
    HoppingNumberDisplay hopping_;                  // 0x6024
};

extern UnkMenuDisplays data_02114dd4;
