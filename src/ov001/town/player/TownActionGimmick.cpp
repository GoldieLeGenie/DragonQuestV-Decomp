#include "ov001/town/player/TownActionGimmick.hpp"

#pragma thumb on

int twn::TownActionGimmick::setup()
{
    for (int i = 0; i < MAP_GIMMICK_COUNT; i++) {
        mapGimmick_[i] = 0;
    }
    gimmickIndex_ = 0;
    townGimmickTrap_.setData(0x59d8, 0x59d8, 0x14, 0x834);
    registGimmick(townGimmickTrap_);
    townGimmickYari_.setData(0x5208, 0x5243, 0x11, 0x214);
    registGimmick(townGimmickYari_);
    townGimmickKanbotsuUpper_.setData(0x55f0, 0x560a, 0x15, 0x1c);
    registGimmick(townGimmickKanbotsuUpper_);
    townGimmickKanbotsuLower_.setData(0x56b8, 0x56d2, 0x15, 0x419);
    registGimmick(townGimmickKanbotsuLower_);
    for (int i = 0; i < MAP_GIMMICK_COUNT; i++) {
        if (mapGimmick_[i]) {
            mapGimmick_[i]->setup();
        }
    }
    return -1;
}

void twn::TownActionGimmick::execute()
{
    if (mapGimmick_[gimmickIndex_]) {
        mapGimmick_[gimmickIndex_]->execute();
    }
}

int twn::TownActionGimmick::update()
{
    if (mapGimmick_[gimmickIndex_] && mapGimmick_[gimmickIndex_]->isEnd() == true) {
        return prevAction_;
    }
    return -1;
}

int twn::TownActionGimmick::startCheck(int action)
{
    for (int i = 0; i < MAP_GIMMICK_COUNT; i++) {
        if (mapGimmick_[i]) {
            int ret = mapGimmick_[i]->isStart();
            if (ret != -1) {
                prevAction_ = action;
                gimmickIndex_ = i;
                return ret;
            }
        }
    }
    return -1;
}

void twn::TownActionGimmick::registGimmick(MapGimmickBase& gimmick)
{
    for (int i = 0; i < MAP_GIMMICK_COUNT; i++) {
        if (mapGimmick_[i] == 0) {
            mapGimmick_[i] = &gimmick;
            return;
        }
    }
}
