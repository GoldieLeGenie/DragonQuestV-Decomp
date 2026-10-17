#pragma once
#include <globaldefs.h>
#include "main/cmn/CommonEffectResource.hpp"
#include "main/data/DataObject.hpp"
#include "main/leveldata/MonsterData.hpp"
#include "main/object/GameMonster.hpp"
#include "main/object/UnkPaletteAnimationObject.hpp"
#include "ov009/book/BookEffectGroup.hpp"

namespace book
{
    struct BookSystem;

    // monster of the monster book page, with its attack animations and effects
    struct BookMonsterDraw {
        dq5::level::MonsterData* monster_;      // 0x0000
        int actionIndex_;                       // 0x0004
        int defaultAnimation_;                  // 0x0008
        int counter_;                           // 0x000C
        BookSystem* system_;                    // 0x0010
        GameMonster character_;                 // 0x0014
        DataObject dataObject_;                 // 0x0F2C palette animation file
        UnkPaletteAnimationObject paletteAnim_; // 0x0F3C
        BookEffectGroup effect_;                // 0x0F5C
        cmn::CommonEffectResource resource_;    // 0x1350
        int wait_;                              // 0x1BC0
        int effectID_;                          // 0x1BC4
        unsigned short anim_[6];                // 0x1BC8
        unsigned short action_[6];              // 0x1BD4
        int animIndexCount_;                    // 0x1BE0

        BookMonsterDraw();
        ~BookMonsterDraw();
        static BookMonsterDraw& getSingleton();
        void initialize();
        void terminate();
        void setup(int index);
        void cleanup();
        void execute();
        void draw();
        void startAnimation(int animIndex);
        bool isActivate();
        void setPaletteAnim(int animNo);
        void setupEffect(int index);
        void cleanupEffect();
        int getMonsterAnimIndex(unsigned short monsterId, unsigned short actionId, unsigned short animId);
    };
} // namespace book
