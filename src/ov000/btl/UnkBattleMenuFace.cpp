#include "ov000/btl/UnkBattleMenuFace.hpp"

THUMB UnkBattleMenuFace::UnkBattleMenuFace()
{
}

THUMB UnkBattleMenuFace::~UnkBattleMenuFace()
{
}

THUMB UnkBattleMenuFace* UnkBattleMenuFace::getSingleton()
{
    static UnkBattleMenuFace battleMenuFace;
    return &battleMenuFace;
}

THUMB void UnkBattleMenuFace::setDisplayOn(int type, int x, int y)
{
    if (type == 3) {
        enable_ = 1;
    }
    x_ = x;
    y_ = y;
    face_.unkfunc_02051b14(x_ - 8, (y - 26) / 2);
}

THUMB void UnkBattleMenuFace::setDisplayOff(int type)
{
    if (type == 3) {
        enable_ = 0;
    }
}
