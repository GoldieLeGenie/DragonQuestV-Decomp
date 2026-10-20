#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/data/DataObject.hpp"
#include "main/object/GameMonster.hpp"
#include "main/object/PaletteAnimationObject.hpp"

namespace btl {
    struct BattleMonster {
        static const unsigned int FLAG_ENABLE = 0x1;
        static const unsigned int FLAG_AIR_MONSTER = 0x2;

        GameMonster monsterDraw_;                       // 0x000
        int monsterGroup_;                              // 0xF18
        int monsterIndex_;                              // 0xF1C
        int screenPosition_;                            // 0xF20
        int screenWidth_;                               // 0xF24
        int actionindex_;                               // 0xF28
        int animindex_;                                 // 0xF2C
        dss::Vector2<int> screen;                       // 0xF30
        int animationFlag_;                             // 0xF38
        DataObject dataObject_;                         // 0xF3C
        PaletteAnimationObject paletteAnimation_;    // 0xF4C
        dss::Flag flag_;                                // 0xF6C

        BattleMonster();
        void setup(int monsterGroup, int monsterIndex);
        void cleanup();
        void draw();
        bool isEnable();
        void setAirMonster(bool flag);
        void setPosition(const dss::Fix32Vector3& position);
        dss::Fix32Vector3 getPosition();
        dss::Fix32Vector3 getNullPosition(int index, int no);
        bool isAirMonster();
        void startAnimation(int actionIndex, int animIndex);
        void startMosyasAnimation(int monsterId, int actionId);
        bool isLastFrame();
        void setCameraAnimation(int index);
        void startAnimation(int animIndex);
        void startAnimationWithLoop(int animIndex, int flag);
        int getMonsterIndex();
        bool startGattai();
        void disappearGattaiSlime();
        bool isAppearKingSlime2();
        void setPaletteAnim(int animNo);
        void setPaletteAstoron(int flag);
        void setTransOfEnd();
        void setNextAnimationIndex(int index);
    };
}
