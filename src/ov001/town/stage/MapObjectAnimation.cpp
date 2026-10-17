#include "ov001/town/stage/MapObjectAnimation.hpp"

#pragma thumb on

twn::MapObjectAnimation::MapObjectAnimation()
{
    clear();
}

bool twn::MapObjectAnimation::isNext()
{
    int next = playIndex_ + 1;
    if (next >= count_) {
        return false;
    }
    return animNo_[next] != -1;
}

void twn::MapObjectAnimation::clear()
{
    for (int i = 0; i < ANIM_COUNT; i++) {
        animNo_[i] = -1;
    }
    mapUid_ = 0;
    playIndex_ = -1;
    count_ = 0;
}

bool twn::MapObjectAnimation::registAnimation(int anim)
{
    if (count_ >= ANIM_COUNT) {
        return false;
    }
    animNo_[count_] = anim;
    count_++;
    return true;
}

int twn::MapObjectAnimation::getNextPlayNo()
{
    playIndex_++;
    if (playIndex_ >= count_) {
        return 0;
    }
    return animNo_[playIndex_];
}
