#pragma once
#include <globaldefs.h>
#include "ov001/town/riseup/TownRiseupIcon.hpp"
#include "ov001/town/riseup/TownRiseupSprite.hpp"
#include "ov001/town/riseup/TownRiseupModel.hpp"
#include "ov001/town/riseup/TownRiseupScriptMove.hpp"
#include "ov001/town/riseup/TownRiseupMedal.hpp"
#include "ov001/town/riseup/TownRiseupExhibit.hpp"

namespace twn {
    struct TownRiseupStorage {
        static const unsigned int RISEUP_ICON_MAX = 4;
        static const unsigned int RISEUP_SPRITE_MAX = 16;
        static const unsigned int RISEUP_MODEL_MAX = 1;
        static const unsigned int RISEUP_SCRIPT_MOVE_MAX = 2;
        static const unsigned int RISEUP_MEDAL_MAX = 1;
        static const unsigned int RISEUP_EXHIBIT_MAX = 32;

        TownRiseupIcon icon_[RISEUP_ICON_MAX];                  // 0x0000
        TownRiseupSprite sprite_[RISEUP_SPRITE_MAX];            // 0x00D0
        TownRiseupModel model_[RISEUP_MODEL_MAX];               // 0x12D0
        TownRiseupScriptMove script_[RISEUP_SCRIPT_MOVE_MAX];   // 0x1630
        TownRiseupMedal medal_[RISEUP_MEDAL_MAX];               // 0x16A8
        TownRiseupExhibit* exhibit_;                            // 0x17A8
        int iconCounter_;                                       // 0x17AC
        int spriteCounter_;                                     // 0x17B0
        int modelCounter_;                                      // 0x17B4
        int scriptCounter_;                                     // 0x17B8
        int medalCounter_;                                      // 0x17BC
        int exhibitCounter_;                                    // 0x17C0

        TownRiseupStorage();
        ~TownRiseupStorage();
        void initialize();
        void terminate();
        TownRiseupBase* getContainer(int type);
        void restoreContainer(int type);
        int getSpriteNum();
    };
}
