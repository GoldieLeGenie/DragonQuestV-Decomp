#include "ov001/town/TownExtraMapObjManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"

THUMB twn::TownExtraMapObjManager& twn::TownExtraMapObjManager::getSingleton()
{
    static TownExtraMapObjManager instance;
    return instance;
}

THUMB void twn::TownExtraMapObjManager::setup()
{
    floorMapObjCount_ = 0;
}

THUMB void twn::TownExtraMapObjManager::setData(int uid, dss::Fix32Vector3 position)
{
    for (int i = 0; i < floorMapObjCount_; i++) {
        if (floorMapObj_[i].mapUid == uid || floorMapObj_[i].mapUid == 0) {
            floorMapObj_[floorMapObjCount_].position = position;
            return;
        }
    }
    floorMapObj_[floorMapObjCount_].mapUid = uid;
    floorMapObj_[floorMapObjCount_].position = position;
    floorMapObjCount_++;
}

THUMB int twn::TownExtraMapObjManager::checkFloorMapUid(dss::Fix32Vector3& position)
{
    dss::Fix32 minDist = TownPlayerAction::collR * TownPlayerAction::collR * 4;
    dss::Fix32 rangeY = TownPlayerAction::collR * 2;
    int uid = 0;
    dss::Fix32Vector3 vec;
    dss::Fix32 dist;
    dss::Fix32 dy;
    for (int i = 0; i < floorMapObjCount_; i++) {
        vec = position - floorMapObj_[i].position;
        dy.value = dss::abs<long>(vec.vy.value);
        vec.vy = 0L;
        if ((dist = vec.lengthsq()) < minDist && dy < rangeY) {
            uid = floorMapObj_[i].mapUid;
            minDist = dist;
        }
    }
    return uid;
}

THUMB bool twn::TownExtraMapObjManager::getPosition(int uid, dss::Fix32Vector3& position)
{
    switch (uid) {
    case 0x1843:
    case 0x1845:
    case 0x1848:
    case 0x184e:
        position = TownPlayerManager::getSingleton().getPosition();
        return true;
    }
    for (int i = 0; i < floorMapObjCount_; i++) {
        if (uid == floorMapObj_[i].mapUid) {
            position = floorMapObj_[i].position;
            return true;
        }
    }
    return false;
}
