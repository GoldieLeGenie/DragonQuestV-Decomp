#include "ov001/town/player/gimmick/MapGimmickBase.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/sound/SoundManager.hpp"

#pragma thumb on

inline void twn::MapGimmickBase::execute()
{
}

void twn::TownGimmickKanbotsuUpper::useGlobalSetup(int uid)
{
    TownStageManager::getSingleton()->setObjectDraw(uid, 3, 1);
}

void twn::TownGimmickKanbotsuUpper::setAnimation(int uid)
{
    TownStageManager::getSingleton()->setMapObjAnimRegist(uid, 1);
    TownStageManager::getSingleton()->setMapObjAnimRegist(uid, 2);
    TownStageManager::getSingleton()->startMapObjAnimRegist(uid);
    SoundManager::playSe(0x456, 0);
    counter_ = 0;
}

bool twn::TownGimmickKanbotsuUpper::isEnd()
{
    counter_++;
    if (counter_ >= 15) {
        return true;
    }
    return false;
}
