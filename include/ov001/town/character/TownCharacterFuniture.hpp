#pragma once
#include <globaldefs.h>
#include "ov001/town/character/TownCharacterBase.hpp"

namespace twn {
    struct TownCharacterFuniture : TownCharacterBase {
        int mapUid_;                            // 0x15C
        dss::Fix32 collR_;                      // 0x160

        TownCharacterFuniture();
        ~TownCharacterFuniture();
        virtual void setup(TOWN_CHARACTER& chara);
        virtual void setDisplay(int flag);
        virtual int isDisplay();
        virtual void execute();
        virtual void setAnimation(int flag);
        virtual void setNearCharacter(int flag);
        virtual void cleanup();
        virtual void setPosition(dss::Fix32Vector3& pos);
        dss::Fix32Vector3 getPosition();
        virtual void execMovePassive();
        virtual void setMapUid(int uid);
        virtual void draw();
    };
}
