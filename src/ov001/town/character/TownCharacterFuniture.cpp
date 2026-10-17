#include "ov001/town/character/TownCharacterFuniture.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/fld/Coll.hpp"

#pragma thumb on

inline int FldCollision::getCollID()
{
    return id_;
}

inline int FldStage::collGetObjId(int polygonNo)
{
    return coll_GetObjId(m_fld.m_coll, polygonNo);
}

inline int twn::TownStageManager::getWallCollId()
{
    return coll_.getCollID();
}

inline int twn::TownStageManager::getObjectID(int polygonNo)
{
    return stage_.collGetObjId(polygonNo);
}

inline int twn::TownStageManager::getMapObjUid(int obj_id)
{
    return stage_.m_fld.GetMapObjUid(obj_id);
}

inline int twn::TownStageManager::boxCollCompute(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 rad, dss::Fix32Vector3* retVec)
{
    return coll_.boxCompute(nowPos, nextPos, rad, retVec);
}

inline dss::Fix32Vector3 twn::TownCharacterFuniture::getPosition()
{
    return data_.position;
}

void twn::TownCharacterFuniture::setup(TOWN_CHARACTER& chara)
{
    rgbFrame_ = -1;
    changeAlphaType_ = 0;
}

void twn::TownCharacterFuniture::setDisplay(int flag)
{
}

int twn::TownCharacterFuniture::isDisplay()
{
    return false;
}

void twn::TownCharacterFuniture::execute()
{
    TownCharacterBase::execute();
}

void twn::TownCharacterFuniture::setAnimation(int flag)
{
}

void twn::TownCharacterFuniture::setNearCharacter(int flag)
{
}

void twn::TownCharacterFuniture::cleanup()
{
}

void twn::TownCharacterFuniture::setPosition(dss::Fix32Vector3& pos)
{
    dss::Fix32Vector3 vec = pos - data_.position;
    TownStageManager::getSingleton()->addMapUidPosFX32(mapUid_, vec);
    data_.position = pos;
}

void twn::TownCharacterFuniture::execMovePassive()
{
    int polyId = TownStageManager::getSingleton()->getWallCollId();
    if (polyId != -1) {
        int objId = TownStageManager::getSingleton()->getObjectID(polyId);
        int uid = TownStageManager::getSingleton()->getMapObjUid(objId);
        if (uid == mapUid_) {
            dss::Fix32Vector3 nowPos = getPosition();
            dss::Fix32Vector3 playerPos = cmn::g_cmnPartyInfo.position_;
            dss::Fix32Vector3 vec = nowPos - playerPos;
            if (TownPlayerManager::getSingleton().player_.townActionWalk_.moveFlag_) {
                if (moveData_.counter % 0x28 > 0x14 || moveData_.counter % 2 != 0) {
                    moveData_.counter++;
                    return;
                }
                short idx = 0;
                TownActionCalculate::getIdxByVec(idx, vec);
                unsigned char dir = TownActionCalculate::getParamDir4ByIdx(idx);
                vec = TownActionCalculate::getParamVec(dir);
                dss::Fix32Vector3 nextPos = nowPos + vec * moveData_.speed;
                dss::Fix32Vector3 retPos;
                TownStageManager::getSingleton()->boxCollCompute(nowPos, nextPos, collR_, &retPos);
                setPosition(retPos);
                moveData_.counter++;
            }
        }
    }
}

void twn::TownCharacterFuniture::setMapUid(int uid)
{
    mapUid_ = uid;
    data_.position = TownStageManager::getSingleton()->getMapUidPos(uid);
    collR_ = (fx32)0x99a;
}

void twn::TownCharacterFuniture::draw()
{
}
