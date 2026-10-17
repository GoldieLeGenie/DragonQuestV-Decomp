#pragma once
#include <globaldefs.h>
#include "main/dss/GameSystemManager.hpp"
#include "main/data/DataObject.hpp"
#include "main/dss/UnkSprite2D.hpp"
#include "main/dss/UnkTextureObject.hpp"

namespace ceremony {
    // "The end" screen of the non-japanese versions: one texture per frame, copied into the displayed texture
    struct UnkCeremonyEndingFin : args::GameSystem {
        int enable_;                            // 0x04
        int frame_;                             // 0x08
        UnkLZDataObject frameData_;             // 0x0C current frame file
        UnkSprite2D sprite_;                    // 0x1C
        void* frameAddr_;                       // 0x54
        UnkLZDataObject textureData_;           // 0x58
        UnkTextureObject* texture_;             // 0x68

        UnkCeremonyEndingFin();
        ~UnkCeremonyEndingFin();
        static UnkCeremonyEndingFin* getSingleton();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual void draw();
        void animTheEnd();
        bool isEnd();
    };
}
