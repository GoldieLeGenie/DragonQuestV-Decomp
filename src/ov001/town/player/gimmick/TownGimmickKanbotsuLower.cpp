#pragma ipa file
#include "ov001/town/player/gimmick/MapGimmickBase.hpp"
#include "ov001/town/TownStageManager.hpp"

#pragma thumb on

inline bool twn::MapGimmickBase::isEnd()
{
    return true;
}

inline void twn::MapGimmickBase::execute()
{
}

void twn::TownGimmickKanbotsuLower::useGlobalSetup(int uid)
{
    TownStageManager::getSingleton()->setObjectDraw(uid, 2, 1);
}

void twn::TownGimmickKanbotsuLower::setAnimation(int uid)
{
}
