#pragma once
#include <globaldefs.h>
#include "ov000/btl/BattleMonster.hpp"
#include "ov000/btl/BattleArray.hpp"

namespace btl {
    struct BattleMonsterDraw2 {
        static const int MONSTER_MAX = 12;

        BattleMonster monsters_[MONSTER_MAX];           // 0x0000
        int monsterCount_;                              // 0xB940
        int enable_;                                    // 0xB944
        BattleArray battleArray_;                       // 0xB948

        static int airMonsterHeight_;

        BattleMonsterDraw2();
        ~BattleMonsterDraw2();
        static BattleMonsterDraw2& getSingleton();
        void setup();
        void cleanup();
        void draw();
        void setupBattleArray(int ctrl, int air);
        void addBattleArray(int ctrl, int monsterGroup, int monsterIndex);
        void delBattleArray(int ctrl);
        int setup(int monsterGroup, int monsterIndex, bool flag);
        void cleanup(int ctrl);
        BattleMonster& getMonster(int index);
        bool isCallFriend(int monsterIndex);
        bool isAppearKingSlime2();
        void startAnimationWithLoop(int ctrl, int animIndex, int flag);
        void changeArrayCtrl(int oldCtrl, int newCtrl);
    };
}
