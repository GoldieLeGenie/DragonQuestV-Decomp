#include "main/town/TownTruckSwitch.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "ov001/town/TownStageManager.hpp"

THUMB void twn::TownTruckSwitch::setupSwitch(int rootIndex, int switchUid, int switchAnim, int railUid, int railAnim)
{
    surfaceIndex_ = rootIndex;
    switchUid_ = switchUid;
    switchAnim_ = switchAnim;
    railUid_ = railUid;
    railAnim_ = railAnim;
    if (data_02101c88.unkfunc_02051818(TOWN_PART)) {
        TownStageManager::getSingleton()->setObjectDraw(switchUid_, switchAnim_, 1);
        TownStageManager::getSingleton()->setObjectDraw(railUid_, railAnim_, 1);
    }
}

THUMB void twn::TownTruckSwitch::switchRail()
{
    if (switchAnim_ == 1) {
        TownStageManager::getSingleton()->setMapObjAnimRegist(switchUid_, 2);
        TownStageManager::getSingleton()->setMapObjAnimRegist(switchUid_, 3);
        switchAnim_ = 3;
    } else {
        TownStageManager::getSingleton()->setMapObjAnimRegist(switchUid_, 4);
        TownStageManager::getSingleton()->setMapObjAnimRegist(switchUid_, 1);
        switchAnim_ = 1;
    }
    if (railAnim_ == 1) {
        TownStageManager::getSingleton()->setMapObjAnimRegist(railUid_, 2);
        TownStageManager::getSingleton()->setMapObjAnimRegist(railUid_, 3);
        railAnim_ = 3;
    } else {
        TownStageManager::getSingleton()->setMapObjAnimRegist(railUid_, 4);
        TownStageManager::getSingleton()->setMapObjAnimRegist(railUid_, 1);
        railAnim_ = 1;
    }
    TownStageManager::getSingleton()->startMapObjAnimRegist(switchUid_);
    TownStageManager::getSingleton()->startMapObjAnimRegist(railUid_);
}
