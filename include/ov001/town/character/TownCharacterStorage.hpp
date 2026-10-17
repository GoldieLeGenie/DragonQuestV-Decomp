#pragma once
#include <globaldefs.h>
#include "ov001/town/character/TownCharacterDraw.hpp"
#include "ov001/town/character/TownMonsterDraw.hpp"
#include "ov001/town/character/TownModelDraw.hpp"
#include "ov001/town/character/TownMotionlessDraw.hpp"
#include "ov001/town/character/TownCharacterFuniture.hpp"

namespace twn {
    struct TownCharacterStorage {
        enum {
            STORAGE_CHARACTER_NONE = 0,
            STORAGE_CHARACTER_NORMAL = 1,
            STORAGE_CHARACTER_SPRITE = 2,
            STORAGE_CHARACTER_MODEL = 3,
            STORAGE_CHARACTER_MOTIONLESS = 4,
            STORAGE_CHARACTER_FURNITURE = 5,
        };

        static const int CHARACTER_MAX = 32;
        static const int SPRITE_MAX = 3;
        static const int MODEL_MAX = 1;
        static const int MOTIONLESS_MAX = 10;
        static const int FUNITURE_MAX = 2;

        int characterCount_;                    // 0x0000
        int monsterCount_;                      // 0x0004
        int modelCount_;                        // 0x0008
        int unk_000c;                           // 0x000C motionless count
        int spriteCount_;                       // 0x0010
        int funitureCount_;                     // 0x0014
        TownCharacterDraw normal_[CHARACTER_MAX];       // 0x0018
        TownMonsterDraw monster_[SPRITE_MAX];           // 0x8318
        TownModelDraw model_[MODEL_MAX];                // 0xB624
        TownMotionlessDraw motionless_[MOTIONLESS_MAX]; // 0xBA98
        TownCharacterFuniture funitureChara_[FUNITURE_MAX]; // 0xDB68

        TownCharacterStorage();
        ~TownCharacterStorage();
        void initialize();
        void terminate();
        TownCharacterBase* getContainer(int type);
        void restoreContainer(int type);
    };
}
