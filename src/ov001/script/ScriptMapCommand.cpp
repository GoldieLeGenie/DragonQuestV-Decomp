#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "ov001/script/ScriptMapCommand.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/TownFurnitureControl.hpp"
#include "ov001/town/TownExtraMapObjManager.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/MapObjGridMove.hpp"
#include "main/town/TownSugorokuInfo.hpp"
#include "main/town/TownTruckData.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/script/CommandParam.hpp"
#include "main/dss/UnkDssMath.hpp"
#include <nitro/fx/fx_atan.h>

#pragma thumb on

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline void twn::TownStageManager::setMapUidOnOff(int id, int flag)
{
    stage_.setMapUidOnOff(id, flag);
}

inline void twn::TownStageManager::collResetMapUid(int id)
{
    stage_.m_fld.CollResetMapUid(id);
}

inline int twn::TownStageManager::IsCommonAnimationEnd(int obj_uid)
{
    return stage_.IsCommonAnimationEnd(obj_uid);
}

inline int twn::TownStageManager::getCommonID(int objectID)
{
    if (objectID == -1) {
        return -1;
    }
    return stage_.m_fld.GetMapObjCommonId(objectID);
}

inline void FldStage::setRotObjectUid(int uId, dss::Fix32Vector3& angle)
{
    m_fld.SetMapUidRotFX32(uId, (VecFx32*)&angle);
}

inline void twn::TownStageManager::setRotObjectUid(int uid, dss::Fix32Vector3& angle)
{
    stage_.setRotObjectUid(uid, angle);
}

inline void twn::TownStageManager::setEraseSurface(int surfaceId, bool flag)
{
    coll_.setEraseSurface(surfaceId, flag);
}

inline int fld::FLDObject::CollGetObjId(int poly_no)
{
    return coll_GetObjId(m_coll, poly_no);
}

inline int FldStage::collGetObjId(int polygonNo)
{
    return m_fld.CollGetObjId(polygonNo);
}

inline int twn::TownStageManager::getObjectID(int polygonNo)
{
    return stage_.collGetObjId(polygonNo);
}

inline int twn::TownStageManager::getMapObjUid(int obj_id)
{
    return stage_.m_fld.GetMapObjUid(obj_id);
}

inline bool twn::TownStageManager::isEraseHitSurface(int id)
{
    return coll_.isEraseHitSurface(id);
}

inline void twn::TownStageManager::addCollisionPosByMapUid(int uid_id, dss::Fix32Vector3& add)
{
    stage_.m_fld.CollAddPolyPosByMapUid(uid_id, (VecFx32*)&add);
}

inline void twn::TownFurnitureManager::forceProcess()
{
    force_ = 1;
}

inline void twn::TownActionWalk::setSearchObjectId(int id)
{
    TownPlayerManager::getSingleton().player_.townActionWalk_.searchObjectId_ = id;
}

inline void twn::TownPlayerManager::setSearchMapUid(int uid)
{
    searchMapUid_ = uid;
}

inline int twn::TownPlayerManager::getSearchMapUid()
{
    return searchMapUid_;
}

inline void twn::TownPlayerManager::setScriptSearchRange(int uid1, int uid2)
{
    uid1_ = uid1;
    uid2_ = uid2;
}

inline void twn::TownStageEffectManager::setBlindAlpha(unsigned char alpha)
{
    spotlight_.setBlindAlpha(alpha);
}

inline void twn::TownStageWrap::setDisplay(int flag)
{
    isDisplay_ = flag;
}

inline void twn::TownStageEffectManager::setDraw(int flag)
{
    wrap_.setDisplay(flag);
}

inline void twn::TownStageEffectManager::initPuzzle()
{
    puzzle_.initPuzzle();
}

inline void twn::TownStageEffectManager::setPuzzle()
{
    puzzle_.setup();
}

inline int cmn::CommonParticleEmitter::isEnable()
{
    return enable_;
}

inline int twn::TownSugorokuInfo::getSugorokuEndMode()
{
    return sugorokuEndMode_;
}

inline int twn::TownActionWalk::getCollId()
{
    return TownPlayerManager::getSingleton().player_.townActionWalk_.collId_;
}

inline int twn::TownActionWalk::getPrevCollId()
{
    return TownPlayerManager::getSingleton().player_.townActionWalk_.prevCollId_;
}

inline int twn::TownActionWalk::getFloorMapUid()
{
    return TownPlayerManager::getSingleton().player_.townActionWalk_.floorMapUid_;
}

inline int twn::TownActionWalk::getPrevFloorMapUid()
{
    return TownPlayerManager::getSingleton().player_.townActionWalk_.prevFloorMapUid_;
}

inline int twn::TownActionWalk::getPrevSurfaceId()
{
    return TownPlayerManager::getSingleton().player_.townActionWalk_.prevSurface_;
}

inline void twn::TownActionWalk::setPrevSurfaceId(int id)
{
    TownPlayerManager::getSingleton().player_.townActionWalk_.prevSurface_ = id;
}

inline twn::TownSystemScript& twn::TownSystem::getScriptSystem()
{
    return townSystemScript_;
}

inline int twn::TownSystemScript::isScriptSearch()
{
    return scriptSearch_;
}

inline int twn::MapObjGridMove::getUid()
{
    return uid_;
}

inline bool twn::MapObjGridMove::isExecEnd()
{
    return endCount_ == 0;
}

inline void cmn::CommonPartyInfo::setBackupPos(dss::Fix32Vector3& pos)
{
    backupPos_ = pos;
}

inline void cmn::CommonPartyInfo::setBackupDirIdx(short idx)
{
    backupDirIdx_ = idx;
}

inline void TownCharacterManager::setObjectMove(int ctrl, int uid, dss::Fix32Vector3& offset, int dir)
{
    character_[ctrl]->setObjectMove(uid, offset, dir);
}

inline int twn::TownActionTruck::isScriptMove()
{
    return TownPlayerManager::getSingleton().player_.townActionTruck_.scriptFlag_;
}

inline void twn::TownTruckWagon::setPos(dss::Fix32Vector3& pos)
{
    pos_ = pos;
}

inline void cmn::CommonPartyInfo::setNotResetShipIkada(bool flag)
{
    shipIkadaArea_ = flag;
}

inline void twn::TownTruckSystem::setDelWagonUid(int uid)
{
    TownPlayerManager::getSingleton().player_.townActionTruck_.system_.delWagonUid_ = uid;
}

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

inline void MapAnimationB::execute()
{
}

inline void MapAnimationB::terminate()
{
}

inline void FurnitureMove::terminate()
{
}

inline void FurnitureMove2::terminate()
{
}

inline void FurnitureRotate::terminate()
{
}

inline void FurnitureGroupMove::terminate()
{
}

inline void FurnitureGroupRotate::terminate()
{
}

inline void CofferProcess::execute()
{
}

inline void CofferProcess::terminate()
{
}

inline void SpotLightON::execute()
{
}

inline void SpotLightON::terminate()
{
}

inline void SpotLightOFF::execute()
{
}

inline void SpotLightOFF::terminate()
{
}

inline void MapObjGimmickMove::terminate()
{
}

bool cmdMapAnimationA(void* scriptParam)
{
    PARAM_MAP_ANIMATION_A* param = (PARAM_MAP_ANIMATION_A*)scriptParam;
    twn::TownStageManager::getSingleton()->setObjectDraw(param->target, param->animation, 1);
    return true;
}

bool cmdSetMapCollision(void* scriptParam)
{
    PARAM_SET_MAP_COLLISION* param = (PARAM_SET_MAP_COLLISION*)scriptParam;
    if (param->collision == 1) {
        twn::TownStageManager::getSingleton()->setMapUidOnOff(param->target, 0);
        twn::TownStageManager::getSingleton()->collResetMapUid(param->target);
    } else {
        twn::TownStageManager::getSingleton()->setMapUidOnOff(param->target, 1);
        twn::TownStageManager::getSingleton()->collEraseMapUid(param->target);
    }
    return true;
}

bool cmdSetEventDoor(void* scriptParam)
{
    PARAM_SET_EVENT_DOOR* param = (PARAM_SET_EVENT_DOOR*)scriptParam;
    twn::TownActionDoor::DOOR_OPEN_TYPE type;
    int mess = 0;
    switch (param->type) {
    case 1:
    case 4:
        mess = 0xc45b2;
        type = twn::TownActionDoor::DOOR_NOT_OPEN_EVENT;
        break;
    case 5:
        mess = 0xc45b4;
        type = twn::TownActionDoor::DOOR_NOT_OPEN_EVENT;
        break;
    case 6:
        mess = 0xc45e0;
        type = twn::TownActionDoor::DOOR_NOT_OPEN_EVENT;
        break;
    case 7:
        mess = 0xc45e2;
        type = twn::TownActionDoor::DOOR_NOT_OPEN_EVENT;
        break;
    case 8:
        mess = 0xc45e4;
        type = twn::TownActionDoor::DOOR_NOT_OPEN_EVENT;
        break;
    case 2:
        type = twn::TownActionDoor::DOOR_OPEN_EVENT;
        break;
    case 3:
        type = twn::TownActionDoor::DOOR_LOCK;
        break;
    default:
        type = twn::TownActionDoor::DOOR_OPEN_KEY;
        break;
    }
    if (mess != 0) {
        twn::TownPlayerManager::getSingleton().player_.townActionDoor_.eventMess_ = mess;
    }
    twn::TownPlayerManager::getSingleton().player_.townActionDoor_.setEventDoor(param->uid, type);
    return true;
}

bool cmdSetFloorMapObject(void* scriptParam)
{
    PARAM_SET_FLOOR_MAP_OBJECT* param = (PARAM_SET_FLOOR_MAP_OBJECT*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    twn::TownExtraMapObjManager::getSingleton().setData(param->mapUid, pos);
    return true;
}

bool cmdFurnitureMoveRequest(void* scriptParam)
{
    PARAM_FURNITURE_MOVE2* param = (PARAM_FURNITURE_MOVE2*)scriptParam;
    dss::Fix32Vector3 end, start;
    start = twn::TownStageManager::getSingleton()->getMapUidPos(param->target);
    end.vx.value = param->endX + start.vx.value;
    end.vy.value = param->endY + start.vy.value;
    end.vz.value = param->endZ + start.vz.value;
    if (param->rate == 0) {
        param->rate = 0x1000;
    }
    int frame = (start - end).length().value / (param->rate * TownCharacterManager::defaultSpeed.value / 4096);
    twn::TownFurnitureControlManager::getSingleton().setFurnitureMove(param->target, frame, end);
    return true;
}

bool cmdIsMapTreasure(void* scriptParam)
{
    PARAM_IS_MAP_TREASURE* param = (PARAM_IS_MAP_TREASURE*)scriptParam;
    bool check;
    switch (twn::TownFurnitureManager::getSingleton()->checkCoffer(param->target)) {
    case 0:
    case 1:
    case 2:
        check = true;
        break;
    case 3:
    case 4:
    case 5:
        check = false;
        break;
    }
    if (check == param->flag) {
        return true;
    }
    return false;
}

bool cmdSetFurniturePosition(void* scriptParam)
{
    PARAM_SET_FURNITURE_POSITION* param = (PARAM_SET_FURNITURE_POSITION*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    twn::TownStageManager::getSingleton()->setMapUidPosFX32(param->uid, pos);
    return true;
}

bool cmdFurnitureFadeout(void* scriptParam)
{
    PARAM_FURNITURE_FADEOUT* param = (PARAM_FURNITURE_FADEOUT*)scriptParam;
    twn::TownFurnitureControlManager::getSingleton().setFurnitureFade(param->target, param->frame, param->fade, param->priority);
    return true;
}

bool cmdSetMapTexture(void* scriptParam)
{
    PARAM_SET_MAP_TEXTURE* param = (PARAM_SET_MAP_TEXTURE*)scriptParam;
    switch (param->texture) {
    case 0:
        twn::TownStageEffectManager::getSingleton()->setEffect(twn::TownStageWrap::EFFECT_TYPE(0));
        break;
    case 1:
        twn::TownStageEffectManager::getSingleton()->setEffect(twn::TownStageWrap::EFFECT_TYPE(1));
        break;
    }
    return true;
}

bool cmdMapTexture(void* scriptParam)
{
    PARAM_MAP_TEXTURE* param = (PARAM_MAP_TEXTURE*)scriptParam;
    twn::TownStageEffectManager::getSingleton()->setDraw(param->display);
    return true;
}

bool cmdCameraActionSet(void* scriptParam)
{
    PARAM_CAMERA_ACTION_SET* param = (PARAM_CAMERA_ACTION_SET*)scriptParam;
    TownCamera::getSingleton()->setCameraLock(param->flag);
    return true;
}

void MapAnimationB::initialize(char* scriptParam)
{
    PARAM_MAP_ANIMATION_B* param = (PARAM_MAP_ANIMATION_B*)scriptParam;
    twn::TownStageManager::getSingleton()->setObjectDraw(param->target, param->animation, 1);
    target = param->target;
}

int MapAnimationB::isEnd()
{
    if (twn::TownStageManager::getSingleton()->IsCommonAnimationEnd(target)) {
        return true;
    }
    return false;
}

MapAnimationB g_MapAnimationB;

void FurnitureMove::initialize(char* scriptParam)
{
    PARAM_FURNITURE_MOVE* param = (PARAM_FURNITURE_MOVE*)scriptParam;
    dss::Fix32Vector3 end, start;
    start = twn::TownStageManager::getSingleton()->getMapUidPos(param->target);
    end.vx.value = param->endX + start.vx.value;
    end.vy.value = param->endY + start.vy.value;
    end.vz.value = param->endZ + start.vz.value;
    index = twn::TownFurnitureControlManager::getSingleton().setFurnitureMove(param->target, param->frame, end);
    twn::TownFurnitureControlManager::getSingleton().setGarbageCorrect(index, false);
}

int FurnitureMove::isEnd()
{
    if (twn::TownFurnitureControlManager::getSingleton().isEnd(index)) {
        twn::TownFurnitureControlManager::getSingleton().cleanup(index);
        return true;
    }
    return false;
}

FurnitureMove g_FurnitureMove;

void FurnitureMove2::initialize(char* scriptParam)
{
    PARAM_FURNITURE_MOVE2* param = (PARAM_FURNITURE_MOVE2*)scriptParam;
    dss::Fix32Vector3 end, start;
    start = twn::TownStageManager::getSingleton()->getMapUidPos(param->target);
    end.vx.value = param->endX + start.vx.value;
    end.vy.value = param->endY + start.vy.value;
    end.vz.value = param->endZ + start.vz.value;
    if (param->rate == 0) {
        param->rate = 0x1000;
    }
    int frame = (start - end).length().value / (param->rate * TownCharacterManager::defaultSpeed.value / 4096);
    index = twn::TownFurnitureControlManager::getSingleton().setFurnitureMove(param->target, frame, end);
    twn::TownFurnitureControlManager::getSingleton().setGarbageCorrect(index, false);
}

int FurnitureMove2::isEnd()
{
    if (twn::TownFurnitureControlManager::getSingleton().isEnd(index)) {
        twn::TownFurnitureControlManager::getSingleton().cleanup(index);
        return true;
    }
    return false;
}

FurnitureMove2 g_FurnitureMove2;

void FurnitureRotate::initialize(char* scriptParam)
{
    PARAM_FURNITURE_ROTATE* param = (PARAM_FURNITURE_ROTATE*)scriptParam;
    dss::Fix32Vector3 end, start;
    end.vx.value = param->endX;
    end.vy.value = param->endY;
    end.vz.value = param->endZ;
    end.vx.value = degreeToAngle(end.vx);
    end.vy.value = degreeToAngle(end.vy);
    end.vz.value = degreeToAngle(end.vz);
    index = twn::TownFurnitureControlManager::getSingleton().setFurnitureRotate(param->target, param->frame, end);
    twn::TownFurnitureControlManager::getSingleton().setGarbageCorrect(index, false);
}

int FurnitureRotate::isEnd()
{
    if (twn::TownFurnitureControlManager::getSingleton().isEnd(index)) {
        twn::TownFurnitureControlManager::getSingleton().cleanup(index);
        return true;
    }
    return false;
}

FurnitureRotate g_FurnitureRotate;

void FurnitureGroupMove::initialize(char* scriptParam)
{
    PARAM_FURNITURE_GROUP_MOVE* param = (PARAM_FURNITURE_GROUP_MOVE*)scriptParam;
    dss::Fix32Vector3 speed;
    speed.vx.value = param->speedX;
    speed.vy.value = param->speedY;
    speed.vz.value = param->speedZ;
    index = twn::TownFurnitureControlManager::getSingleton().setFurnitureGroupMove(param->target, param->frame, speed);
    twn::TownFurnitureControlManager::getSingleton().setGarbageCorrect(index, false);
}

int FurnitureGroupMove::isEnd()
{
    if (twn::TownFurnitureControlManager::getSingleton().isEnd(index)) {
        twn::TownFurnitureControlManager::getSingleton().cleanup(index);
        return true;
    }
    return false;
}

FurnitureGroupMove g_FurnitureGroupMove;

void FurnitureGroupRotate::initialize(char* scriptParam)
{
    PARAM_FURNITURE_GROUP_ROTATE* param = (PARAM_FURNITURE_GROUP_ROTATE*)scriptParam;
    dss::Fix32Vector3 speed;
    speed.vx.value = param->speedX;
    speed.vy.value = param->speedY;
    speed.vz.value = param->speedZ;
    speed.vx.value = degreeToAngle(speed.vx);
    speed.vy.value = degreeToAngle(speed.vy);
    speed.vz.value = degreeToAngle(speed.vz);
    index = twn::TownFurnitureControlManager::getSingleton().setFurnitureGroupRotate(param->target, param->frame, speed);
    twn::TownFurnitureControlManager::getSingleton().setGarbageCorrect(index, false);
}

int FurnitureGroupRotate::isEnd()
{
    if (twn::TownFurnitureControlManager::getSingleton().isEnd(index)) {
        twn::TownFurnitureControlManager::getSingleton().cleanup(index);
        return true;
    }
    return false;
}

FurnitureGroupRotate g_FurnitureGroupRotate;

void CofferProcess::initialize(char* scriptParam)
{
    PARAM_FURNITURE_OPEN* param = (PARAM_FURNITURE_OPEN*)scriptParam;
    twn::TownFurnitureManager::getSingleton()->forceProcess();
    twn::TownFurnitureManager::getSingleton()->checkObject(param->target, false, false, 0);
    uid_ = param->target;
}

int CofferProcess::isEnd()
{
    if (twn::TownFurnitureManager::getSingleton()->isProcess() == false) {
        int objectId = twn::TownStageManager::getSingleton()->getObjectIDfromMapUid(uid_);
        int common = twn::TownStageManager::getSingleton()->getCommonID(objectId);
        if (common == 0xc1c || common == 0xd48) {
            twn::TownActionWalk::setSearchObjectId(-1);
            twn::TownPlayerManager::getSingleton().setSearchMapUid(0);
        }
        return true;
    }
    return false;
}

CofferProcess g_CofferProcess;

void SpotLightON::initialize(char* scriptParam)
{
    PARAM_SET_SPOT_LIGHT* param = (PARAM_SET_SPOT_LIGHT*)scriptParam;
    maxCount = param->frame;
    count = 0;
    vec.vx.value = param->posX;
    vec.vy.value = param->posY;
    vec.vz.value = param->posZ;
    twn::TownStageEffectManager::getSingleton()->setSpotlight(&vec);
    twn::TownStageEffectManager::getSingleton()->setLightSize(param->R);
    twn::TownStageEffectManager::getSingleton()->setLightAlpha(1);
    twn::TownStageEffectManager::getSingleton()->setBlindAlpha(0);
}

int SpotLightON::isEnd()
{
    int cnt = count;
    int max = maxCount;
    if (max <= cnt) {
        return true;
    }
    twn::TownStageEffectManager::getSingleton()->setLightAlpha(1);
    twn::TownStageEffectManager::getSingleton()->setBlindAlpha(((30 << 8) / max * cnt) >> 8);
    count++;
    return false;
}

SpotLightON g_SpotLightON;

void SpotLightOFF::initialize(char* scriptParam)
{
    PARAM_SET_SPOT_CLOSE* param = (PARAM_SET_SPOT_CLOSE*)scriptParam;
    maxCount = param->frame;
    count = 0;
    r = param->R;
    r2 = param->R2;
    twn::TownStageEffectManager::getSingleton()->setLightSize(param->R);
}

int SpotLightOFF::isEnd()
{
    if (maxCount <= count) {
        twn::TownStageEffectManager::getSingleton()->clearTorchlight();
        return true;
    }
    twn::TownStageEffectManager::getSingleton()->setLightSize(r + (r2 - r) * count / maxCount);
    unsigned char alpha = 30 - count * 30 / maxCount;
    twn::TownStageEffectManager::getSingleton()->setBlindAlpha(alpha);
    count++;
    return false;
}

SpotLightOFF g_SpotLightOFF;

bool cmd_set_particle_draw(void* scriptParam)
{
    PARAM_SET_PARTICLE_DRAW* param = (PARAM_SET_PARTICLE_DRAW*)scriptParam;
    if (cmn::CommonParticleEmitter::getSingleton()->isEnable()) {
        cmn::CommonParticleEmitter::getSingleton()->cleanup();
    }
    cmn::CommonParticleEmitter::getSingleton()->setup(param->type);
    return true;
}

bool cmd_set_particle_max(void* scriptParam)
{
    PARAM_SET_PARTICLE_MAX* param = (PARAM_SET_PARTICLE_MAX*)scriptParam;
    cmn::CommonParticleEmitter::getSingleton()->setCount(param->max);
    return true;
}

bool cmd_reset_ninepuzzle(void* scriptParam)
{
    twn::TownStageEffectManager::getSingleton()->initPuzzle();
    return true;
}

bool cmd_set_ninepuzzle(void* scriptParam)
{
    twn::TownStageEffectManager::getSingleton()->setPuzzle();
    return true;
}

bool cmd_set_furniture_gaze(void* scriptParam)
{
    PARAM_SET_FURNITURE_GAZE* param = (PARAM_SET_FURNITURE_GAZE*)scriptParam;
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 rot;
    vec = twn::TownPlayerManager::getSingleton().getPosition() - twn::TownStageManager::getSingleton()->getMapUidPos(param->id);
    vec.vy.value = 0;
    vec.normalize();
    rot.vy.value = FX_Atan2Idx(vec.vx.value, vec.vz.value);
    twn::TownStageManager::getSingleton()->setRotObjectUid(param->id, rot);
    return true;
}

bool Cmd_sugoroku_end_type(void* scriptParam)
{
    PARAM_SUGOROKU_END_TYPE* param = (PARAM_SUGOROKU_END_TYPE*)scriptParam;
    switch (twn::g_SugorokuInfo.getSugorokuEndMode()) {
    case 1:
        if (param->endType == 0) {
            return true;
        }
        break;
    case 2:
        if (param->endType == 1) {
            return true;
        }
        break;
    case 3:
        if (param->endType == 2) {
            return true;
        }
        break;
    case 4:
        if (param->endType == 3) {
            return true;
        }
        break;
    case 5:
        if (param->endType == 4) {
            return true;
        }
        break;
    case 6:
        if (param->endType == 5) {
            return true;
        }
        break;
    }
    return false;
}

bool cmdSetTruckSwitch(void* scriptParam)
{
    PARAM_SET_TRUCK_SWITCH* param = (PARAM_SET_TRUCK_SWITCH*)scriptParam;
    twn::TownPlayerManager::getSingleton().player_.townActionTruck_.system_.setupSwitch(param->rootNo, param->setNo, param->switchUid, param->switchAnim, param->railUid, param->railAnim);
    return true;
}

bool cmdTruckSwitch(void* scriptParam)
{
    PARAM_TRUCK_SWITCH* param = (PARAM_TRUCK_SWITCH*)scriptParam;
    twn::TownPlayerManager::getSingleton().player_.townActionTruck_.system_.switchRail(param->uid);
    return true;
}

bool cmdSetSurfaceOnOff(void* scriptParam)
{
    PARAM_SET_SURFACE_ON_OFF* param = (PARAM_SET_SURFACE_ON_OFF*)scriptParam;
    int id = param->surfaceId;
    if (param->setFlag == 1) {
        twn::TownStageManager::getSingleton()->setEraseSurface(id, false);
        twn::TownStageManager::getSingleton()->resetSurface(id);
        return true;
    }
    if (param->collFlag == 1) {
        twn::TownStageManager::getSingleton()->setEraseSurface(id, true);
    } else {
        twn::TownStageManager::getSingleton()->eraseSurface(id);
    }
    return true;
}

bool cmdCheckHitMapUid(void* scriptParam)
{
    PARAM_TOUCH_MAP_OBJ* param = (PARAM_TOUCH_MAP_OBJ*)scriptParam;
    int nowId = twn::TownActionWalk::getCollId();
    int prevId = twn::TownActionWalk::getPrevCollId();
    nowId = twn::TownStageManager::getSingleton()->getObjectID(nowId);
    nowId = twn::TownStageManager::getSingleton()->getMapObjUid(nowId);
    prevId = twn::TownStageManager::getSingleton()->getObjectID(prevId);
    prevId = twn::TownStageManager::getSingleton()->getMapObjUid(prevId);
    if (nowId == 0) {
        nowId = twn::TownActionWalk::getFloorMapUid();
        prevId = twn::TownActionWalk::getPrevFloorMapUid();
    }
    if (param->flag == 0 && prevId == nowId) {
        return false;
    }
    if (param->uid2 == 0) {
        if (nowId == param->uid1) {
            return true;
        }
    } else if (param->uid1 <= nowId && param->uid2 >= nowId) {
        return true;
    }
    return false;
}

bool cmdSearchMapObj2(void* scriptParam)
{
    PARAM_SEARCH_MAP_OBJ2* param = (PARAM_SEARCH_MAP_OBJ2*)scriptParam;
    twn::TownPlayerManager::getSingleton().setScriptSearchRange(param->uid1, param->uid2);
    if (twn::TownSystem::getSingleton().getScriptSystem().isScriptSearch()) {
        if (twn::TownPlayerManager::getSingleton().getSearchMapUid() >= (int)param->uid1 && twn::TownPlayerManager::getSingleton().getSearchMapUid() <= (int)param->uid2) {
            cmn::PartyTalk::getSingleton().resetPartyTalk();
            return true;
        }
    }
    return false;
}

bool cmdCheckSurface(void* scriptParam)
{
    PARAM_CHECK_SURFACE* param = (PARAM_CHECK_SURFACE*)scriptParam;
    int prevId = twn::TownActionWalk::getPrevSurfaceId();
    int nowId = -1;
    for (int i = 0; i < 22; i++) {
        if (param->surface == twn::TownStageManager::getSingleton()->getHitSurfaceIdByType(i)) {
            nowId = twn::TownStageManager::getSingleton()->getHitSurfaceIdByType(i);
            break;
        }
    }
    if (nowId == -1) {
        if (twn::TownStageManager::getSingleton()->isEraseHitSurface(param->surface)) {
            nowId = param->surface;
        }
    }
    twn::TownActionWalk::setPrevSurfaceId(nowId);
    if (param->flag == 0 && prevId == nowId) {
        return false;
    }
    if (nowId == param->surface) {
        twn::TownActionWalk::setPrevSurfaceId(prevId);
        return true;
    }
    return false;
}

void MapObjGimmickMove::initialize(char* scriptParam)
{
    PARAM_MAP_OBJ_GMMICK_MOVE* param = (PARAM_MAP_OBJ_GMMICK_MOVE*)scriptParam;
    dss::Fix32 speed;
    speed.value = param->speedRate;
    for (int i = 0; i < count_; i++) {
        if (param->uid == move_[i]->getUid()) {
            move_[i]->setMove(param->direction, speed);
            execNo_ = i;
            return;
        }
    }
}

void MapObjGimmickMove::execute()
{
    if (execNo_ != -1) {
        move_[execNo_]->execute();
    }
}

int MapObjGimmickMove::isEnd()
{
    if (move_[execNo_]->isExecEnd()) {
        execNo_ = -1;
        return true;
    }
    return false;
}

void MapObjGimmickMove::regist(int uid, int flag, dss::Fix32 length)
{
    move_[count_] = &twn::g_GridMove[count_];
    move_[count_]->setup(uid, flag, length);
    count_++;
}

MapObjGimmickMove g_MapObjGimmickMove;

bool cmd_setup_gimmick_move(void* scriptParam)
{
    PARAM_SETUP_GRID_MOVE* param = (PARAM_SETUP_GRID_MOVE*)scriptParam;
    dss::Fix32 length;
    length.value = param->length;
    g_MapObjGimmickMove.regist(param->uid, param->flag, length);
    return true;
}

bool cmd_set_scope(void* scriptParam)
{
    cmn::g_cmnPartyInfo.setMenuAction(cmn::SCOPE);
    cmn::g_cmnPartyInfo.setBackupPos(cmn::g_cmnPartyInfo.position_);
    cmn::g_cmnPartyInfo.setBackupDirIdx(cmn::g_cmnPartyInfo.dirIdx_);
    dss::Fix32Vector3 pos(0, 0, 0);
    cmn::g_extraMapLink.setExtraLinkTown(0xaa, pos, 0);
    return true;
}

bool cmdFurnitureCollMove(void* scriptParam)
{
    PARAM_FURNITURE_COLL_MOVE* param = (PARAM_FURNITURE_COLL_MOVE*)scriptParam;
    dss::Fix32Vector3 end;
    end.vx.value = param->endX;
    end.vy.value = param->endY;
    end.vz.value = param->endZ;
    twn::TownStageManager::getSingleton()->addCollisionPosByMapUid(param->target, end);
    return true;
}

bool cmdSetCharaPosToMapObj(void* scriptParam)
{
    PARAM_SET_CHARA_POS_TO_MAPOBJ* param = (PARAM_SET_CHARA_POS_TO_MAPOBJ*)scriptParam;
    int ctrl = getPlacementCtrlId();
    dss::Fix32Vector3 offset;
    offset.vx.value = param->offsetX;
    offset.vy.value = param->offsetY;
    offset.vz.value = param->offsetZ;
    TownCharacterManager::getSingleton()->setObjectMove(ctrl, param->uid, offset, param->dir);
    return true;
}

bool cmdSetTruck_Start(void* scriptParam)
{
    PARAM_SET_TRUCK_START* param = (PARAM_SET_TRUCK_START*)scriptParam;
    int start = twn::TownPlayerManager::getSingleton().player_.townActionTruck_.system_.getRailNoByIndex(param->railstart);
    int next = twn::TownPlayerManager::getSingleton().player_.townActionTruck_.system_.getRailNoByIndex(param->railnext);
    twn::TownPlayerManager::getSingleton().player_.townActionTruck_.scriptStart(param->wagonUid, next, start);
    return true;
}

bool cmdCheckTruck_End(void* scriptParam)
{
    if (twn::TownActionTruck::isScriptMove() == 0) {
        return true;
    }
    return false;
}

bool cmdSetTruckWagon(void* scriptParam)
{
    PARAM_SET_WAGON_POSITION* param = (PARAM_SET_WAGON_POSITION*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    twn::TownPlayerManager::getSingleton().player_.townActionTruck_.system_.getWagonByUid(param->uid).setPos(pos);
    twn::TownStageManager::getSingleton()->setMapUidPosFX32(param->uid, pos);
    return true;
}

bool cmdSetIkadaArea(void* scriptParam)
{
    cmn::g_cmnPartyInfo.setNotResetShipIkada(true);
    return true;
}

bool cmdDelTruckWagon(void* scriptParam)
{
    PARAM_DEL_TRUCK_WAGON* param = (PARAM_DEL_TRUCK_WAGON*)scriptParam;
    twn::TownTruckSystem::setDelWagonUid(param->uid);
    return true;
}

bool cmdDelScriptMapObject(void* scriptParam)
{
    PARAM_DEL_SCRIPT_MAP_OBJECT* param = (PARAM_DEL_SCRIPT_MAP_OBJECT*)scriptParam;
    twn::TownPlayerManager::getSingleton().delScriptSearchObject(param->uid);
    return true;
}

bool cmdSetShipInfo(void* scriptParam)
{
    PARAM_SET_TOWN_SHIP* param = (PARAM_SET_TOWN_SHIP*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    dss::Fix32 deg;
    deg.value = param->idx;
    short idx = degreeToAngle(deg);
    twn::TownPlayerManager::getSingleton().player_.townActionShip_.setShipDataByScript(param->name, pos, idx);
    return true;
}

void ScriptMapCommand_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
