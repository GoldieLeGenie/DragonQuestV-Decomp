#pragma once
#include <globaldefs.h>
#include "main/dss/Sprite2D.hpp"

namespace btl
{
    struct BattleMonsterMask {
        static const int MASK_MAX = 2;
        static const int MONSTER_MAX = 12;

        int select_;                                // 0x000
        Sprite2D sprite_;                        // 0x004
        UnkMenuSprite mask_[MASK_MAX];              // 0x03C
        dss::Vector2<int> targetPos[MONSTER_MAX];   // 0x0DC
        dss::Fix32 scale_;                          // 0x13C

        static int monsterRectTemp[MONSTER_MAX];

        BattleMonsterMask();
        ~BattleMonsterMask();
        static BattleMonsterMask* getSingleton();
        void initialize();
        void setup();
        void terminate();
        void execute();
        void select(int groupId);
        void draw();
        void calcTargetPos(int actorindex);
        dss::Vector2<int> getTargetPos(int actorindex);
        int* getMonsterTouchRect(int actorindex);
    };
} // namespace btl
