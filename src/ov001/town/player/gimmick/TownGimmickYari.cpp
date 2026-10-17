#include "ov001/town/player/gimmick/MapGimmickBase.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/sound/SoundManager.hpp"

#pragma thumb on

inline void twn::MapGimmickBase::execute()
{
}

inline bool twn::MapGimmickBase::isEnd()
{
    return true;
}

void twn::TownGimmickYari::setAnimation(int uid)
{
    TownStageManager::getSingleton()->setMapObjAnimRegist(uid, 1);
    TownStageManager::getSingleton()->setMapObjAnimRegist(uid, 2);
    TownStageManager::getSingleton()->startMapObjAnimRegist(uid);
    SoundManager::playSe(0x1a4, 0);
}
