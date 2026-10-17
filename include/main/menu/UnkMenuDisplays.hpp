#pragma once
#include <globaldefs.h>
#include "main/menu/UnkMenuFrameDisplay.hpp"
#include "main/menu/UnkMenuFaceDisplay.hpp"
#include "main/menu/UnkMenuIconDisplay.hpp"
#include "main/menu/UnkMenuDummyDisplay.hpp"
#include "main/menu/UnkMessageWindow.hpp"
#include "main/menu/UnkMenuYesNoDisplay.hpp"
#include "main/menu/UnkMenuTextDisplay.hpp"
#include "main/menu/UnkMenuWindowFrame.hpp"
#include "main/menu/UnkMenuSpriteDisplay.hpp"
#include "main/menu/UnkMenuArrowDisplay.hpp"

// Menu display objects, set up, updated and drawn together by unkfunc_02063c00...unkfunc_02064154
struct UnkMenuDisplays {
    UnkMenuFrameDisplay frames_;                // 0x0000
    UnkMenuFaceDisplay face_;                   // 0x1034
    UnkMenuIconDisplay icon_;                   // 0x1070
    UnkMenuDummyDisplay dummy_;                 // 0x10E0
    UnkMessageWindow message_;                     // 0x1110
    UnkMenuYesNoDisplay yesNo_;                 // 0x2B1C
    UnkMenuTextDisplay texts_[4];               // 0x2E74
    UnkMenuWindowFrame windowFrame1_;           // 0x5DD4
    UnkMenuWindowFrame windowFrame2_;           // 0x5E24
    UnkMenuSpriteDisplay sprite_;               // 0x5E74
    UnkMenuArrowDisplay arrow_;                 // 0x5EE4
    UnkHoppingNumber hopping_;                  // 0x6024
};

extern UnkMenuDisplays data_02114dd4;
