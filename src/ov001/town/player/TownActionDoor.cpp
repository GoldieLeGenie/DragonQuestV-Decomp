#pragma ipa file
#include "ov001/town/player/TownActionDoor.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/global/StageLink.hpp"
#include "main/menu/UiMsg.hpp"
#include "main/sound/Sound.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/StageInfo.hpp"

#pragma thumb on

inline int status::StageInfo::getEncountFlag()
{
    return encount_;
}

inline void FldCollision::clearSurfaceByType(int type)
{
    surfaceType_[type] = -1;
}

inline int fld::FLDObject::CollGetPolyNoBySurface(int surface_id, int start)
{
    return coll_GetPolyNoBySurface(m_coll, surface_id, start);
}

inline void fld::FLDObject::CollEraseObjId(int obj_id)
{
    coll_EraseObjId(m_coll, obj_id);
}

inline int FldStage::collGetObjId(int polygonNo)
{
    return coll_GetObjId(m_fld.m_coll, polygonNo);
}

inline void FldStage::eraseCollision(int objectID)
{
    m_fld.CollEraseObjId(objectID);
}

inline int twn::TownStageManager::getObjectID(int polygonNo)
{
    return stage_.collGetObjId(polygonNo);
}

inline int twn::TownStageManager::getCommonID(int objectID)
{
    if (objectID == -1) {
        return -1;
    }
    return stage_.m_fld.GetMapObjCommonId(objectID);
}

inline int twn::TownStageManager::getMapObjUid(int obj_id)
{
    return stage_.m_fld.GetMapObjUid(obj_id);
}

inline int twn::TownStageManager::collGetPolyIDbySurfaceID(int surfaceID)
{
    return stage_.m_fld.CollGetPolyNoBySurface(surfaceID, 0);
}

inline void twn::TownStageManager::eraseCollision(int objectID)
{
    stage_.eraseCollision(objectID);
}

inline void twn::TownStageManager::eraseObject(int uid, int flag)
{
    stage_.eraseObject(uid, flag);
}

inline int twn::TownStageManager::IsCommonAnimationEnd(int obj_uid)
{
    return stage_.IsCommonAnimationEnd(obj_uid);
}

inline void twn::TownStageManager::clearHitSurfaceIdByType(int type)
{
    coll_.clearSurfaceByType(type);
}

inline int twn::TownStageManager::getSearchObjectId()
{
    return coll_.getSearchObjectId();
}

inline int twn::TownStageManager::getSearchPolyNo()
{
    return coll_.getSearchPolyNo();
}

inline int FldCollision::getSurfacePolyNoByType(int type)
{
    return surfacePolyNo_[type];
}

inline int twn::TownStageManager::getHitPolyNoByType(int type)
{
    return coll_.getSurfacePolyNoByType(type);
}

inline int twn::TownStageManager::getCollPolyByPolyNo(int polyNo, COLL_POLY* coll)
{
    return stage_.collGetPoly(polyNo, coll);
}

inline short twn::TownStageManager::getObjectRotIdx(int objectId)
{
    return stage_.getObjectRotIdxY(objectId);
}

inline void twn::TownStageManager::setCommonAnimation(int objectId, int num)
{
    stage_.commonAnim(objectId, num);
}

inline void twn::TownStageManager::setMapUidOnOff(int id, int flag)
{
    stage_.setMapUidOnOff(id, flag);
}

inline void twn::TownStageManager::collResetMapUid(int id)
{
    stage_.m_fld.CollResetMapUid(id);
}

inline void twn::TownStageManager::setAlpha(int id, int alpha)
{
    stage_.setAlpha(id, alpha);
}

inline twn::TOWN_PLAYER_ACTION_TYPE twn::TownPlayerManager::getActionType()
{
    return player_.actionType_;
}

namespace twn {
    const dss::Fix32 length((fx32)0x1800);
}

int twn::TownActionDoor::setup()
{
    dss::Fix32 length;
    length.value = 0x11f4;
    wDoor1_ObjNo_ = -1;
    wDoor2_ObjNo_ = -1;
    sDoor_ObjNo_ = -1;
    tDoor_ObjNo_ = -1;
    doorType_ = DOOR_S;
    openType_ = DOOR_OPEN_KEY;
    doorKeyType_ = dq5::KEY_NONE;
    judgeType_ = JUDGE_KEY;
    eventDoorCount_ = 0;
    message_ = false;
    crackOrin_ = false;
    dss::Fix32Vector3 pos1(TownPlayerManager::getSingleton().getPosition());
    pos1.vx += 0x46;
    pos1.vz += 0x46;
    pos1.vy += 0x64;
    short dir = TownPlayerManager::getSingleton().getDirection();
    dss::Fix32Vector3 vec;
    TownActionCalculate::getDirByIdx(dir, vec);
    dss::Fix32Vector3 pos2 = pos1 - vec * length;
    int exitIndex = util::StageLink::getTownExitIndex();
    TownStageManager::getSingleton()->collGetPolyIDbySurfaceID(exitIndex);
    int polyNo;
    int surface[2] = {0x10000, 0x70000};
    if (status::g_StageInfo.getEncountFlag() == true) {
        return -1;
    }
    TownStageManager::getSingleton()->getCrossPolygonOtherSurface(pos1, pos2, surface, 2, polyNo, NULL, false);
    if (polyNo != -1) {
        int objectNo = TownStageManager::getSingleton()->getObjectID(polyNo);
        if (objectNo != -1) {
            int commonId = TownStageManager::getSingleton()->getCommonID(objectNo);
            if (isDoorObject(commonId) == true) {
                if (checkOpen(objectNo, commonId, true) == false) {
                    return -1;
                }
                int mapUid = TownStageManager::getSingleton()->getMapObjUid(objectNo);
                if (mapUid == 0) {
                    return -1;
                }
                if (doorType_ == DOOR_W) {
                    int objectNo2 = TownActionCalculate::searchPairWdoor(objectNo, NULL, NULL);
                    int mapUid2 = TownStageManager::getSingleton()->getMapObjUid(objectNo2);
                    TownFurnitureManager::getSingleton()->openDoor(mapUid);
                    TownFurnitureManager::getSingleton()->openDoor(mapUid2);
                    TownStageManager::getSingleton()->eraseObject(mapUid, 1);
                    TownStageManager::getSingleton()->eraseObject(mapUid2, 1);
                } else {
                    TownFurnitureManager::getSingleton()->openDoor(mapUid);
                    TownStageManager::getSingleton()->eraseObject(mapUid, 1);
                }
            }
        }
    }
    return -1;
}

void twn::TownActionDoor::execute()
{
    if (counter_ == 0) {
        switch (doorType_) {
        case DOOR_S:
            setDoorS(backupObj_);
            Sound::sePlayDirect(0x134);
            break;
        case DOOR_T:
            Sound::sePlayDirect(0x136);
            setDoorT(backupObj_);
            break;
        case DOOR_W:
            setDoorW(backupObj_);
            Sound::sePlayDirect(0x135);
            break;
        }
    }
    counter_++;
}

int twn::TownActionDoor::update()
{
    int ret = -1;
    int mapUid1 = TownStageManager::getSingleton()->getMapObjUid(wDoor1_ObjNo_);
    int mapUid2 = TownStageManager::getSingleton()->getMapObjUid(wDoor2_ObjNo_);
    int mapUidS = TownStageManager::getSingleton()->getMapObjUid(sDoor_ObjNo_);
    int mapUidT = TownStageManager::getSingleton()->getMapObjUid(tDoor_ObjNo_);
    switch (doorType_) {
    case DOOR_W:
        if (mapUid1 == 0 || mapUid2 == 0) {
            ret = nextAction_;
        }
        if (mapUid1 != 0 && TownStageManager::getSingleton()->IsCommonAnimationEnd(mapUid1) == true) {
            TownStageManager::getSingleton()->eraseCollision(wDoor1_ObjNo_);
            TownStageManager::getSingleton()->setSoftErase(wDoor1_ObjNo_);
            TownFurnitureManager::getSingleton()->openDoor(mapUid1);
            ret = nextAction_;
        }
        if (mapUid2 != 0 && TownStageManager::getSingleton()->IsCommonAnimationEnd(mapUid2) == true) {
            TownStageManager::getSingleton()->eraseCollision(wDoor2_ObjNo_);
            TownStageManager::getSingleton()->setSoftErase(wDoor2_ObjNo_);
            TownFurnitureManager::getSingleton()->openDoor(mapUid2);
            ret = nextAction_;
        }
        break;
    case DOOR_S:
        if (mapUidS == 0) {
            ret = nextAction_;
        }
        if (mapUidS != 0 && TownStageManager::getSingleton()->IsCommonAnimationEnd(mapUidS) == true) {
            TownStageManager::getSingleton()->eraseCollision(sDoor_ObjNo_);
            TownStageManager::getSingleton()->setSoftErase(sDoor_ObjNo_);
            TownFurnitureManager::getSingleton()->openDoor(mapUidS);
            ret = nextAction_;
        }
        break;
    case DOOR_T:
        if (mapUidT == 0) {
            return nextAction_;
        }
        if (TownStageManager::getSingleton()->isEndSoftErase(tDoor_ObjNo_)) {
            TownFurnitureManager::getSingleton()->openDoor(mapUidT);
            ret = nextAction_;
        }
        break;
    }
    if (ret != -1) {
        TownPlayerManager::getSingleton().resetMapLink(RESET_EXIT_LOCK_DOOR);
        TownPlayerManager::getSingleton().setRemote(false);
    }
    return ret;
}

void twn::TownActionDoor::objClear()
{
    prev_w1_objNo_ = -1;
    prev_w2_objNo_ = -1;
    prev_s_objNo_ = -1;
    prev_tDoorNo_ = -1;
    wDoor1_ObjNo_ = -1;
    wDoor2_ObjNo_ = -1;
    sDoor_ObjNo_ = -1;
    tDoor_ObjNo_ = -1;
    message_ = false;
}

int twn::TownActionDoor::startCheck()
{
    int ret = -1;
    wDoor1_ObjNo_ = -1;
    wDoor2_ObjNo_ = -1;
    sDoor_ObjNo_ = -1;
    tDoor_ObjNo_ = -1;
    message_ = false;
    if (checkSurface() == true) {
        TownPlayerManager::getSingleton().lockMapLink(EXIT_LOCK_DOOR);
        nextAction_ = TownPlayerManager::getSingleton().getActionType();
        TownPlayerManager::getSingleton().setRemote(true);
        ret = 10;
        if (nextAction_ == 0x12) {
            nextAction_ = 0;
        }
    } else if (checkObject() == true) {
        TownPlayerManager::getSingleton().lockMapLink(EXIT_LOCK_DOOR);
        nextAction_ = TownPlayerManager::getSingleton().getActionType();
        TownPlayerManager::getSingleton().setRemote(true);
        ret = 10;
        if (nextAction_ == 0x12) {
            nextAction_ = 0;
        }
    }
    if (message_ == true) {
        ui_MsgSndSet(0x30);
        int objectId = TownStageManager::getSingleton()->getSearchObjectId();
        int messId = -1;
        int messCount = 1;
        switch (openType_) {
        case DOOR_NOT_OPEN_KEY:
            if (checkOpenMessage(objectId) == true) {
                if (haveKey_ == dq5::KEY_NONE) {
                    messId = 0xc45b2;
                } else {
                    messId = 0xc45b4;
                }
            }
            TownStageManager::getSingleton()->clearHitSurfaceIdByType(1);
            TownStageManager::getSingleton()->clearHitSurfaceIdByType(7);
            break;
        case DOOR_NOT_OPEN_EVENT:
            if (checkOpenMessage(objectId) == true) {
                messId = eventMess_;
            }
            TownStageManager::getSingleton()->clearHitSurfaceIdByType(1);
            TownStageManager::getSingleton()->clearHitSurfaceIdByType(7);
            break;
        case DOOR_NOT_OPEN_MAP_ID:
            TownStageManager::getSingleton()->eraseCollision(objectId);
            break;
        case DOOR_CRACK_ORIN:
            messId = 0xb99e;
            messCount = 2;
            break;
        }
        if (messId != -1) {
            TownWindowSystem::getSingleton().openSystemMessage(messId, messCount);
            cmn::PartyTalk::getSingleton().setPreMessageNo(messId);
        }
    }
    prev_w1_objNo_ = wDoor1_ObjNo_;
    prev_w2_objNo_ = wDoor2_ObjNo_;
    prev_s_objNo_ = sDoor_ObjNo_;
    prev_tDoorNo_ = tDoor_ObjNo_;
    return ret;
}

bool twn::TownActionDoor::checkSurface()
{
    dss::Fix32 retLength;
    dss::Fix32Vector3 surfaceNVec;
    dss::Fix32Vector3 surfacePos;
    dss::Fix32Vector3 pos1;
    dss::Fix32Vector3 pos2;
    int doorPoly;
    int surfaceId1 = TownStageManager::getSingleton()->getHitSurfaceIdByType(1);
    if (surfaceId1 != -1 || TownStageManager::getSingleton()->getHitSurfaceIdByType(7) != -1) {
        if (surfaceId1 != -1) {
            surfaceNVec = TownStageManager::getSingleton()->getHitSurfaceDirByType(1);
            surfacePos = TownStageManager::getSingleton()->getHitSurfacePosByType(1);
            doorPoly = TownStageManager::getSingleton()->getHitPolyNoByType(1);
        } else {
            surfaceNVec = TownStageManager::getSingleton()->getHitSurfaceDirByType(7);
            surfacePos = TownStageManager::getSingleton()->getHitSurfacePosByType(7);
            doorPoly = TownStageManager::getSingleton()->getHitPolyNoByType(7);
        }
        pos1 = surfacePos + surfaceNVec;
        pos2 = surfacePos - surfaceNVec * length;
        int polyNo;
        int surface[2] = {0x10000, 0x70000};
        TownStageManager::getSingleton()->getCrossPolygonOtherSurface(pos1, pos2, surface, 2, polyNo, NULL, false);
        if (polyNo != -1) {
            int objectId = TownStageManager::getSingleton()->getObjectID(polyNo);
            int commonId = TownStageManager::getSingleton()->getCommonID(objectId);
            if (checkOpen(objectId, commonId, true) == true) {
                return true;
            }
        }
    }
    return false;
}

bool twn::TownActionDoor::checkObject()
{
    int objectId = TownStageManager::getSingleton()->getSearchObjectId();
    int commonId = TownStageManager::getSingleton()->getCommonID(objectId);
    if (commonId == -1) {
        return false;
    }
    if (checkOpen(objectId, commonId, false) == true) {
        return true;
    }
    return false;
}

bool twn::TownActionDoor::checkOpen(int objectId, int commonId, bool surface)
{
    if (isDoorObject(commonId) == false) {
        return false;
    }
    int mapUidT = TownStageManager::getSingleton()->getMapObjUid(objectId);
    if (mapUidT == 0) {
        return false;
    }
    int collId = TownStageManager::getSingleton()->getSearchPolyNo();
    COLL_POLY poly;
    int pret = TownStageManager::getSingleton()->getCollPolyByPolyNo(collId, &poly);
    if (surface == false && pret == true) {
        dss::Fix32Vector3 vec1 = FldStage::getFx32Vector3(poly.normal);
        dss::Fix32Vector3 idx = TownStageManager::getSingleton()->getMapUidRot(mapUidT);
        dss::Fix32Vector3 vec2;
        TownActionCalculate::getDirByIdx(idx.vy.value, vec2);
        if (dss::abs<long>((vec1 * vec2).value) <= 0xb50) {
            return false;
        }
    }
    openType_ = getOpenType(objectId);
    if (openType_ != DOOR_OPEN_KEY && openType_ != DOOR_OPEN_EVENT) {
        return false;
    }
    backupObj_ = objectId;
    counter_ = 0;
    return true;
}

bool twn::TownActionDoor::isDoorObject(int commonId)
{
    bool ret = true;
    switch (commonId) {
    case 0x1130:
        doorKeyType_ = dq5::KEY_NONE;
        doorType_ = DOOR_S;
        break;
    case 0x1131:
        doorKeyType_ = dq5::KEY_TOUZOKU;
        doorType_ = DOOR_S;
        break;
    case 0x1132:
        doorKeyType_ = dq5::KEY_MAHOU;
        doorType_ = DOOR_S;
        break;
    case 0x1133:
    case 0x1134:
    case 0x1135:
        doorKeyType_ = dq5::KEY_NONE;
        doorType_ = DOOR_S;
        break;
    case 0x1136:
        doorType_ = DOOR_T;
        doorKeyType_ = dq5::KEY_SAIGO;
        break;
    case 0x1137:
        doorKeyType_ = dq5::KEY_NONE;
        doorType_ = DOOR_W;
        break;
    case 0x1138:
        doorKeyType_ = dq5::KEY_TOUZOKU;
        doorType_ = DOOR_W;
        break;
    case 0x1139:
        doorKeyType_ = dq5::KEY_MAHOU;
        doorType_ = DOOR_W;
        break;
    case 0x113a:
    case 0x113b:
    case 0x113c:
        doorKeyType_ = dq5::KEY_NONE;
        doorType_ = DOOR_W;
        break;
    default:
        ret = false;
        break;
    }
    return ret;
}

void twn::TownActionDoor::setDoorT(int objectId)
{
    int mapUidT = TownStageManager::getSingleton()->getMapObjUid(objectId);
    if (mapUidT != 0) {
        TownStageManager::getSingleton()->setSoftErase(objectId);
    }
    tDoor_ObjNo_ = objectId;
}

void twn::TownActionDoor::setDoorS(int objectId)
{
    dss::Fix32Vector3 pos;
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 dir;
    static const dss::Fix32Vector3 unk_02151280(0, 0, -1);
    static const dss::Fix32Vector3 unk_0215128c(1, 0, 0);
    dss::Fix32 dot;
    dss::Fix32 cross;
    short idx = TownStageManager::getSingleton()->getObjectRotIdx(objectId);
    TownStageManager::getSingleton()->getObjectPos(objectId, 0, &pos);
    TownActionCalculate::getDirByIdx(idx, dir);
    vec = pos - position_;
    dot = vec * dir;
    sDoor_ObjNo_ = objectId;
    if (dot > dss::Fix32(0L)) {
        TownStageManager::getSingleton()->setCommonAnimation(sDoor_ObjNo_, 4);
    } else {
        TownStageManager::getSingleton()->setCommonAnimation(sDoor_ObjNo_, 2);
    }
}

void twn::TownActionDoor::setDoorW(int objectId)
{
    dss::Fix32Vector3 door1Pos;
    dss::Fix32Vector3 door2Pos;
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 playerDir;
    dss::Fix32Vector3 crossRot;
    TownActionCalculate::getDirByIdx(dirIdx_, playerDir);
    int objectId2 = TownActionCalculate::searchPairWdoor(objectId, &door1Pos, &door2Pos);
    wDoor1_ObjNo_ = objectId;
    wDoor2_ObjNo_ = objectId2;
    vec = door2Pos - door1Pos;
    crossRot = vec % playerDir;
    if (crossRot.vy > dss::Fix32(0L)) {
        TownStageManager::getSingleton()->setCommonAnimation(wDoor1_ObjNo_, 4);
        TownStageManager::getSingleton()->setCommonAnimation(wDoor2_ObjNo_, 2);
    } else {
        TownStageManager::getSingleton()->setCommonAnimation(wDoor1_ObjNo_, 2);
        TownStageManager::getSingleton()->setCommonAnimation(wDoor2_ObjNo_, 4);
    }
}

twn::TownActionDoor::DOOR_OPEN_TYPE twn::TownActionDoor::getOpenType(int objectId)
{
    int mapUid = TownStageManager::getSingleton()->getMapObjUid(objectId);
    if (mapUid == 0) {
        return DOOR_NOT_OPEN_MAP_ID;
    }
    for (int i = 0; i < eventDoorCount_; i++) {
        if (mapUid == eventDoor_[i].uid) {
            switch (eventDoor_[i].type) {
            case DOOR_NOT_OPEN_EVENT:
                message_ = true;
                return eventDoor_[i].type;
            case DOOR_OPEN_EVENT:
            case DOOR_LOCK:
                return eventDoor_[i].type;
            }
        }
    }
    if (g_AreaFlag.check(0x1a6)) {
        haveKey_ = dq5::KEY_SAIGO;
    } else if (g_AreaFlag.check(0x171)) {
        haveKey_ = dq5::KEY_MAHOU;
    } else if (g_AreaFlag.check(0xa4)) {
        haveKey_ = dq5::KEY_TOUZOKU;
    } else {
        haveKey_ = dq5::KEY_NONE;
    }
    if (doorKeyType_ <= haveKey_) {
        return DOOR_OPEN_KEY;
    }
    message_ = true;
    return DOOR_NOT_OPEN_KEY;
}

bool twn::TownActionDoor::checkOpenMessage(int objectId)
{
    bool ret = false;
    switch (doorType_) {
    case DOOR_W:
        if (objectId != prev_w1_objNo_ && objectId != prev_w2_objNo_) {
            ret = true;
        }
        wDoor1_ObjNo_ = objectId;
        break;
    case DOOR_S:
        if (objectId != prev_s_objNo_) {
            ret = true;
        }
        sDoor_ObjNo_ = objectId;
        break;
    case DOOR_T:
        if (objectId != prev_tDoorNo_) {
            ret = true;
        }
        tDoor_ObjNo_ = objectId;
        break;
    }
    return ret;
}

void twn::TownActionDoor::setEventDoor(int uid, DOOR_OPEN_TYPE type)
{
    for (int i = 0; i < eventDoorCount_; i++) {
        if (eventDoor_[i].uid == uid) {
            eventDoor_[i].type = type;
            return;
        }
    }
    eventDoor_[eventDoorCount_].uid = uid;
    eventDoor_[eventDoorCount_].type = type;
    eventDoorCount_++;
}

void twn::TownActionDoor::scriptOpen(int uid1, int uid2, int type)
{
    scriptDoor1Uid_ = uid1;
    scriptDoor2Uid_ = uid2;
    int objId1 = TownStageManager::getSingleton()->getObjectIDfromMapUid(scriptDoor1Uid_);
    int objId2;
    if (scriptDoor2Uid_ != 0) {
        objId2 = TownStageManager::getSingleton()->getObjectIDfromMapUid(scriptDoor2Uid_);
    }
    switch (type) {
    case 0:
        scriptType_ = 0;
        TownStageManager::getSingleton()->setCommonAnimation(objId1, 2);
        setDoorFlag(scriptDoor1Uid_, scriptType_, true);
        if (uid2 != 0) {
            setDoorFlag(scriptDoor2Uid_, 0, true);
            TownStageManager::getSingleton()->setCommonAnimation(objId2, 4);
        }
        break;
    case 1:
        scriptType_ = 0;
        setDoorFlag(scriptDoor1Uid_, scriptType_, true);
        TownStageManager::getSingleton()->setCommonAnimation(objId1, 4);
        if (uid2 != 0) {
            setDoorFlag(scriptDoor2Uid_, scriptType_, true);
            TownStageManager::getSingleton()->setCommonAnimation(objId2, 2);
        }
        break;
    case 2:
        scriptType_ = 1;
        setDoorFlag(scriptDoor1Uid_, scriptType_, true);
        TownStageManager::getSingleton()->setCommonAnimation(objId1, 7);
        if (uid2 != 0) {
            setDoorFlag(scriptDoor2Uid_, scriptType_, true);
            TownStageManager::getSingleton()->setCommonAnimation(objId2, 6);
        }
        break;
    case 3:
        scriptType_ = 1;
        setDoorFlag(scriptDoor1Uid_, scriptType_, true);
        TownStageManager::getSingleton()->setCommonAnimation(objId1, 6);
        if (uid2 != 0) {
            setDoorFlag(scriptDoor2Uid_, scriptType_, true);
            TownStageManager::getSingleton()->setCommonAnimation(objId2, 7);
        }
        break;
    case 4:
        scriptType_ = 0;
        TownStageManager::getSingleton()->setCommonAnimation(objId1, 1);
        setDoorFlag(scriptDoor1Uid_, scriptType_, false);
        if (scriptDoor2Uid_ != 0) {
            TownStageManager::getSingleton()->setCommonAnimation(objId2, 1);
            setDoorFlag(scriptDoor2Uid_, scriptType_, false);
        }
        scriptDoor1Uid_ = 0;
        scriptDoor2Uid_ = 0;
        break;
    case 5:
        scriptType_ = 1;
        TownStageManager::getSingleton()->setCommonAnimation(objId1, 1);
        setDoorFlag(scriptDoor1Uid_, scriptType_, false);
        if (scriptDoor2Uid_ != 0) {
            TownStageManager::getSingleton()->setCommonAnimation(objId2, 1);
            setDoorFlag(scriptDoor2Uid_, scriptType_, false);
        }
        scriptDoor1Uid_ = 0;
        scriptDoor2Uid_ = 0;
        break;
    }
}

bool twn::TownActionDoor::scriptEnd()
{
    bool ret = true;
    if (scriptDoor1Uid_ != 0) {
        if (TownStageManager::getSingleton()->IsCommonAnimationEnd(scriptDoor1Uid_) == false) {
            ret = false;
        } else {
            if (scriptType_ == 0) {
                TownFurnitureControlManager::getSingleton().setFurnitureFade(scriptDoor1Uid_, 0xf, true, 0);
            }
            scriptDoor1Uid_ = 0;
        }
    }
    if (scriptDoor2Uid_ != 0) {
        if (TownStageManager::getSingleton()->IsCommonAnimationEnd(scriptDoor2Uid_) == false) {
            ret = false;
        } else {
            if (scriptType_ == 0) {
                TownFurnitureControlManager::getSingleton().setFurnitureFade(scriptDoor2Uid_, 0xf, true, 0);
            }
            scriptDoor2Uid_ = 0;
        }
    }
    return ret;
}

void twn::TownActionDoor::setDoorFlag(int uid, int type, bool flag)
{
    TownStageManager::getSingleton()->setMapUidOnOff(uid, 0);
    int objId = TownStageManager::getSingleton()->getObjectIDfromMapUid(uid);
    if (type == 0) {
        TownStageManager::getSingleton()->collEraseMapUid(uid);
        TownFurnitureManager::getSingleton()->openDoor(uid);
        TownStageManager::getSingleton()->setAlpha(objId, 0x1f);
        if (flag == false) {
            TownStageManager::getSingleton()->setMapUidOnOff(uid, 1);
        }
    }
    if (type == 1) {
        if (flag == true) {
            TownFurnitureControlManager::getSingleton().setFurnitureFade(uid, 0xf, false, 0);
            TownStageManager::getSingleton()->setAlpha(objId, 0);
        } else {
            TownStageManager::getSingleton()->setAlpha(objId, 0x1f);
        }
        TownStageManager::getSingleton()->collResetMapUid(uid);
        TownFurnitureManager::getSingleton()->closeDoor(uid);
    }
}
