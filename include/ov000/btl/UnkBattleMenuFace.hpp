#pragma once
#include <globaldefs.h>
#include "main/dss/UnkSprite2D.hpp"

struct UnkBattleMenuFace {
    UnkMenuSprite face_;                        // 0x00
    int enable_;                                // 0x50
    int x_;                                     // 0x54
    int y_;                                     // 0x58

    UnkBattleMenuFace();
    ~UnkBattleMenuFace();
    static UnkBattleMenuFace* getSingleton();
    void setDisplayOn(int type, int x, int y);
    void setDisplayOff(int type);
};
