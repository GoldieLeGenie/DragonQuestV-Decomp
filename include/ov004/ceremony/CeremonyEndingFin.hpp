#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/dss/GameSystemManager.hpp"
#include "main/dss/Sprite2D.hpp"
#include "main/dss/TextureObject.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/object/PaletteAnimationObject.hpp"

namespace ceremony {
    // "The end" screen of the japanese version
    struct CeremonyEndingFin : args::GameSystem {
        int enable_;                            // 0x004
        int m_frame;                            // 0x008
        int m_pam_index;                        // 0x00C
        UnkMenuSprite theSprite_[2];            // 0x010
        UnkMenuSprite endSprite_[2];            // 0x0B0
        unsigned short palette_[256];           // 0x150
        DataObject pamData_;                    // 0x350
        PaletteAnimationObject pam_;         // 0x360
        DataObject penData_;                    // 0x380
        DSSAObject2D penDssa_;                  // 0x390
        DataObject penTextureData_;             // 0x42C
        TextureObject* penTexture_;          // 0x43C

        CeremonyEndingFin();
        ~CeremonyEndingFin();
        static CeremonyEndingFin* getSingleton();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        void animTheEnd();
        bool isEnd();
    };
}
