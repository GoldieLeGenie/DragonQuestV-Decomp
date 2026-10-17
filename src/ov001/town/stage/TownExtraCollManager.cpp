#pragma ipa file
#include "ov001/town/stage/TownExtraCollManager.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/fld/Coll.hpp"

#pragma thumb on

inline void fld::FLDObject::CollEraseObjId(int obj_id)
{
    coll_EraseObjId(m_coll, obj_id);
}

inline void fld::FLDObject::CollResetObjId(int obj_id)
{
    coll_ResetObjId(m_coll, obj_id);
}

inline void FldStage::eraseCollision(int objectID)
{
    m_fld.CollEraseObjId(objectID);
}

inline void FldStage::resetCollision(int objectID)
{
    m_fld.CollResetObjId(objectID);
}

inline void twn::TownStageManager::eraseCollision(int objectID)
{
    stage_.eraseCollision(objectID);
}

inline void twn::TownStageManager::resetCollision(int objectID)
{
    stage_.resetCollision(objectID);
}

inline int cmn::CommonPartyInfo::getCollFlag()
{
    return collFlag_;
}

inline dss::Fix32Vector3 cmn::CommonPartyInfo::getCharaColl()
{
    return collVec_;
}

dss::Fix32 twn::TownExtraCollManager::sleepCharaW;
dss::Fix32 twn::TownExtraCollManager::sleepCharaH;
dss::Fix32 twn::TownExtraCollManager::sleepCharaY;

namespace twn {
    const dss::Fix32 sleepFixX((fx32)0x333);
    const dss::Fix32 sleepFixZ((fx32)0x99a);
}

twn::TownExtraCollManager& twn::TownExtraCollManager::getSingleton()
{
    static TownExtraCollManager townExtraCollManager;
    return townExtraCollManager;
}

void twn::TownExtraCollManager::setup()
{
    for (int i = 0; i < EXTRA_COLL_COUNT_MAX; i++) {
        extraCollData_[i].id = -1;
    }
    sleepCharaW.value = 0x604;
    sleepCharaH.value = 0x85c;
    sleepCharaY.value = 0x800;
    extraCollCount_ = 0;
    rectCollCount_ = 0;
}

void twn::TownExtraCollManager::resetCharaColl(int charaNo, int type)
{
    for (int i = 0; i < EXTRA_COLL_COUNT_MAX; i++) {
        if (type == extraCollData_[i].type && charaNo == extraCollData_[i].id) {
            extraCollData_[i].flag = false;
            TownStageManager::getSingleton()->eraseCollision(extraCollData_[i].objectId);
        }
    }
}

void twn::TownExtraCollManager::addCharacterColl(int ctrl, int type)
{
    dss::Fix32Vector3 vec;
    vec.vx.value = vec.vy.value = vec.vz.value = 0x1000;
    vec /= 3;
    static const dss::Fix32 len((fx32)0x119a);
    int charaNo = TownCharacterManager::getSingleton()->getCharaIndex(ctrl);
    dss::Fix32Vector3 pos = TownCharacterManager::getSingleton()->getPosition(ctrl);
    if (charaNo == 0x5a) {
        return;
    }
    if (cmn::g_cmnPartyInfo.getCollFlag() == true) {
        vec = cmn::g_cmnPartyInfo.getCharaColl();
    }
    short direction = TownCharacterManager::getSingleton()->getDirection(ctrl);
    for (int i = 0; i < EXTRA_COLL_COUNT_MAX; i++) {
        if (extraCollData_[i].type == 2 && ctrl == extraCollData_[i].id && extraCollData_[i].flag == false) {
            extraCollData_[i].flag = true;
            TownStageManager::getSingleton()->addBoxCollision(pos, direction, vec, extraCollData_[i].objectId);
            return;
        }
    }
    int no = extraCollCount_;
    extraCollData_[no].objectId = -1;
    extraCollData_[no].flag = true;
    extraCollData_[no].type = 2;
    extraCollData_[no].id = ctrl;
    TownStageManager::getSingleton()->addBoxCollision(pos, direction, vec, extraCollData_[no].objectId);
    extraCollCount_++;
}

int twn::TownExtraCollManager::isExtraCollChara(int objectNo, int& charaNo)
{
    for (int i = 0; i < extraCollCount_; i++) {
        if (objectNo == extraCollData_[i].objectId) {
            charaNo = extraCollData_[i].id;
            return extraCollData_[i].type;
        }
    }
    return -1;
}

void twn::TownExtraCollManager::addSleepChara(int charaNo)
{
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 pos;
    pos = TownCharacterManager::getSingleton()->getPosition(charaNo);
    short direction = TownCharacterManager::getSingleton()->getDirection(charaNo);
    vec.vy = sleepCharaY;
    vec.vx = sleepCharaW;
    vec.vz = sleepCharaH;
    if (cmn::g_cmnPartyInfo.getCollFlag() == true) {
        vec = cmn::g_cmnPartyInfo.getCharaColl();
    }
    for (int i = 0; i < EXTRA_COLL_COUNT_MAX; i++) {
        if (extraCollData_[i].type == 0 && charaNo == extraCollData_[i].id && extraCollData_[i].flag == false) {
            extraCollData_[i].flag = true;
            TownStageManager::getSingleton()->resetCollision(extraCollData_[i].objectId);
            return;
        }
    }
    extraCollCount_++;
    int no = extraCollCount_ - 1;
    extraCollData_[no].objectId = -1;
    extraCollData_[no].flag = true;
    extraCollData_[no].type = 0;
    extraCollData_[no].id = charaNo;
    TownStageManager::getSingleton()->addBoxCollision(pos, direction, vec, extraCollData_[no].objectId);
}

void twn::TownExtraCollManager::addMoveColl(int charNo, int type, dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos)
{
    switch (type) {
    case 2:
    case 3:
        type = 2;
        break;
    case 1:
        type = 0;
        break;
    }
    for (int i = 0; i < extraCollCount_; i++) {
        if (type == extraCollData_[i].type && charNo == extraCollData_[i].id) {
            TownStageManager::getSingleton()->addMovePosByObjNo(extraCollData_[i].objectId, nowPos, nextPos);
        }
    }
}

bool twn::TownExtraCollManager::checkInArea(dss::Fix32Vector3& pos)
{
    for (int i = 0; i < rectCollCount_; i++) {
        if (rect_[i].v[0] <= pos.vx && pos.vx <= rect_[i].v[1] && rect_[i].v[2] <= pos.vz && pos.vz <= rect_[i].v[3]) {
            return true;
        }
    }
    return false;
}

void twn::TownExtraCollManager::setCheckArea(dss::Fix32 a, dss::Fix32 b, dss::Fix32 c, dss::Fix32 d)
{
    dss::Rectangle<dss::Fix32>& rect = rect_[rectCollCount_];
    rect.v[0] = a;
    rect.v[1] = b;
    rect.v[2] = c;
    rect.v[3] = d;
    rectCollCount_++;
}
