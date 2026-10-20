#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "ov001/script/ScriptCommandTown.hpp"
#include "main/script/CommandParam.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/status/StageInfo.hpp"
#include "main/global/Global.hpp"
#include "main/global/GlobalGamePart.hpp"
#include "main/sound/UnkSoundPlayer.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/dss/UnkDssMath.hpp"
#include "main/dss/UnkDisplayPlugin.hpp"
#include "ov001/leveldata/FloorBackColor.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownGlobalMap.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownFurniture.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

inline void status::StageInfo::setOverviewTempPosition(dss::Fix32Vector3& pos)
{
    overviewTempPosition_ = pos;
}

inline void status::StageInfo::setOverviewPosition(dss::Fix32Vector3& pos)
{
    overviewPosition_ = pos;
}

inline dq5::level::FloorBackColor* dq5::level::FloorBackColor::getRecord(int index)
{
    return (FloorBackColor*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int twn::TownStageTinction::getNextBackColor()
{
    return nextIndex_;
}

inline void twn::TownStageTinction::setNextBackColor(int index)
{
    nextIndex_ = index;
}

inline dss::Fix32Vector3& twn::TownStageTinction::getPaletteRate()
{
    return rate_;
}

inline int twn::TownStageEffectManager::getCurrentBackColor()
{
    return tinct_.getCurrentBackColor();
}

inline void twn::TownStageEffectManager::setNextBackColor(int index)
{
    tinct_.setNextBackColor(index);
}

inline int twn::TownStageEffectManager::getNextBackColor()
{
    return tinct_.getNextBackColor();
}

inline dss::Fix32Vector3& twn::TownStageEffectManager::getPaletteRate()
{
    return tinct_.getPaletteRate();
}

inline dss::Fix32Vector3 twn::TownStageEffectManager::getDefaultPaletteRate()
{
    return tinct_.getDefaultPaletteRate();
}

inline void FldStage::SetRGBRate(dss::Fix32Vector3& fldrate, int real_time)
{
    m_fld.SetRGBRate((VecFx32*)&fldrate, real_time);
}

inline void twn::TownStageManager::SetRGBRate(dss::Fix32Vector3& rate, int real_time)
{
    stage_.SetRGBRate(rate, real_time);
}

inline void twn::TownStageManager::setCameraNo(int no, int idx)
{
    stage_.m_fld.SetCameraNo(no, idx);
}

inline int twn::TownStageManager::eventAnim(int event, int objID)
{
    return stage_.eventAnim(event, objID);
}

inline void fld::FLDObject::SetBBoxFar(fx32 val)
{
    m_bbox_far = val;
}

inline void FldStage::SetBBoxFar(fx32 val)
{
    m_fld.SetBBoxFar(val);
}

inline void twn::TownStageManager::SetBBoxFar(dss::Fix32 val)
{
    stage_.SetBBoxFar(val.value);
}

inline int twn::TownStageManager::getObjectNum()
{
    return stage_.m_fld.m_map->uid_num;
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

inline void twn::TownStageManager::setAlpha(int id, int alpha)
{
    stage_.setAlpha(id, alpha);
}

inline bool TownCamera::isEndMotion()
{
    return cameraMove_.isEnd();
}

inline bool TownCamera::isEndPovMove()
{
    return isPovMove_ == 0;
}

inline void cmn::CommonPartyInfo::setPosition(dss::Fix32Vector3& pos)
{
    position_ = pos;
}

inline twn::TOWN_PLAYER_ACTION_TYPE twn::TownPlayerManager::getActionType()
{
    return player_.actionType_;
}

inline void GlobalSpriteFade::flashWhite(int r, int g, int b, int frames)
{
    state_ = FadeEffector::FADE_IN_WHITE;
    count_ = 0;
    frames_ = frames;
    sprite_[0].setColor(r, g, b);
    sprite_[1].setColor(r, g, b);
    data_02101d14.unkfunc_020519a8(this);
}

inline void LocationEffect::terminate()
{
}

inline void LocationEffectMove::terminate()
{
}

inline void LocationEffectFade::terminate()
{
}

inline void MapFlash::terminate()
{
}

inline void MapBackGroundColor::terminate()
{
}

inline void MapBackGroundColorInit::terminate()
{
}

inline void MapBlendColor::terminate()
{
}

inline void MapBlendColorInit::terminate()
{
}

inline void GlobalMapOpen::terminate()
{
}

inline void GlobalMapClose::terminate()
{
}

inline void MapCameraPosition::execute()
{
}

inline void MapCameraPosition::terminate()
{
}

inline void MapCameraPositionAbs::execute()
{
}

inline void MapCameraPositionAbs::terminate()
{
}

inline void MapCameraAngle::execute()
{
}

inline void MapCameraAngle::terminate()
{
}

inline void MapCameraGaze::execute()
{
}

inline void MapCameraGaze::terminate()
{
}

inline void CameraChangeDistance::execute()
{
}

inline void CameraChangeDistance::terminate()
{
}

inline void CameraMovePov::execute()
{
}

inline void CameraMovePov::terminate()
{
}

inline void CameraResetDistance::execute()
{
}

inline void CameraResetDistance::terminate()
{
}

inline void CameraMoveToPlayer::execute()
{
}

inline void CameraMoveToPlayer::terminate()
{
}

inline void MapEventCamera::terminate()
{
}

inline void Cmd_ikada_move2_player_get_on::execute()
{
}

inline void Cmd_ikada_move_player_get_on::execute()
{
}

inline void Cmd_set_camera_angle_abs::execute()
{
}

inline void Cmd_door_action::execute()
{
}

static const dss::Fix32 defaultSpeed(0x66);

THUMB bool cmdIsTrigger2(void* scriptParam)
{
    PARAM_IS_TRIGGER2* param = (PARAM_IS_TRIGGER2*)scriptParam;
    dss::Fix32Vector3 pos = twn::TownPlayerManager::getSingleton().getPosition();
    if (param->startX < pos.vx.value && param->endX > pos.vx.value &&
        param->startY < pos.vy.value && param->endY > pos.vy.value &&
        param->startZ < pos.vz.value && param->endZ > pos.vz.value) {
        short dirIdx = twn::TownPlayerManager::getSingleton().getDirection();
        dss::Fix32Vector3 dirVec;
        twn::TownActionCalculate::getDirByIdx(dirIdx, dirVec);
        dss::Fix32Vector3 dirParam = twn::TownActionCalculate::getParamVec(param->direction);
        dss::Fix32 dot = dirVec * dirParam;
        if (dot >= dss::Fix32(0L)) {
            return true;
        }
    }
    return false;
}

THUMB bool cmd_is_trigger_character(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_IS_TRIGGER_CHARACTER* param = (PARAM_IS_TRIGGER_CHARACTER*)scriptParam;
    dss::Fix32Vector3 pos = TownCharacterManager::getSingleton()->getPosition(ctrl);
    short idx = TownCharacterManager::getSingleton()->getDirection(ctrl);
    dss::Fix32Vector3 start;
    dss::Fix32Vector3 end;
    start.set(param->startX, param->startY, param->startZ);
    end.set(param->endX, param->endY, param->endZ);
    int checkDir = 0;
    int checkArea = param->flag == 0 ? 7 : 6;
    return cmn::CommonCalculate::areaCheck(pos, idx, start, end, checkDir, checkArea);
}

THUMB bool cmd_is_trigger2_character(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_IS_TRIGGER_CHARACTER* param = (PARAM_IS_TRIGGER_CHARACTER*)scriptParam;
    dss::Fix32Vector3 pos = TownCharacterManager::getSingleton()->getPosition(ctrl);
    short idx = TownCharacterManager::getSingleton()->getDirection(ctrl);
    dss::Fix32Vector3 start;
    dss::Fix32Vector3 end;
    start.set(param->startX, param->startY, param->startZ);
    end.set(param->endX, param->endY, param->endZ);
    int checkDir = 0;
    int checkArea = param->flag == 0 ? 7 : 6;
    return cmn::CommonCalculate::areaCheck(pos, idx, start, end, checkDir, checkArea);
}

THUMB bool cmdSetOverviewPosition(void* scriptParam)
{
    PARAM_SET_OVERVIEW_POINT* param = (PARAM_SET_OVERVIEW_POINT*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    status::g_StageInfo.setOverviewTempPosition(pos);
    return true;
}

THUMB bool cmdSetOverviewChurchPosition(void* scriptParam)
{
    PARAM_SET_OVERVIEW_CHURCH* param = (PARAM_SET_OVERVIEW_CHURCH*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    status::g_StageInfo.setOverviewPosition(pos);
    status::g_StageInfo.setOverviewTempPosition(pos);
    return true;
}

THUMB bool cmd_set_ikada_info(void* scriptParam)
{
    PARAM_SET_IKADA_INFO* param = (PARAM_SET_IKADA_INFO*)scriptParam;
    dss::Fix32Vector3 pos = cmn::CommonCalculate::setVecByParam(param->posX, param->posY, param->posZ);
    twn::TownPlayerManager::getSingleton().player_.townActionIkada_.setIkadaDataByScript(param->name, pos);
    return true;
}

THUMB void LocationEffect::initialize(char* scriptParam)
{
    PARAM_EFFECT_WAIT* param = (PARAM_EFFECT_WAIT*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    index = twn::TownRiseupManager::getSingleton().setupSprite(param->effect, pos, param->flag, 0);
}

THUMB int LocationEffect::isEnd()
{
    return twn::TownRiseupManager::getSingleton().isFinish(index);
}

LocationEffect g_LocationEffect;

THUMB void LocationEffectMove::initialize(char* scriptParam)
{
    PARAM_EFFECT_MOVE* param = (PARAM_EFFECT_MOVE*)scriptParam;
    dss::Fix32Vector3 start;
    dss::Fix32Vector3 end;
    start.vx.value = param->startX;
    start.vy.value = param->startY;
    start.vz.value = param->startZ;
    end.vx.value = param->endX;
    end.vy.value = param->endY;
    end.vz.value = param->endZ;
    index = twn::TownRiseupManager::getSingleton().setupSpriteMove(param->effect, start, end, param->frame, 0);
}

THUMB int LocationEffectMove::isEnd()
{
    return twn::TownRiseupManager::getSingleton().isFinish(index);
}

LocationEffectMove g_LocationEffectMove;

THUMB void LocationEffectFade::initialize(char* scriptParam)
{
    PARAM_EFFECT_FADE* param = (PARAM_EFFECT_FADE*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    index = twn::TownRiseupManager::getSingleton().setupSpriteFade(param->effect, pos, param->frame, param->flag);
}

THUMB int LocationEffectFade::isEnd()
{
    return twn::TownRiseupManager::getSingleton().isFinish(index);
}

LocationEffectFade g_LocationEffectFade;

THUMB void MapFlash::initialize(char* scriptParam)
{
    PARAM_MAP_FLASH* param = (PARAM_MAP_FLASH*)scriptParam;
    count_ = 0;
    countFrame_ = param->frame;
    data_021025e0.unkfunc_02055194(0, param->se);
    data_0211b27c.flashWhite((unsigned char)param->r, (unsigned char)param->g, (unsigned char)param->b, countFrame_ / 2);
}

THUMB void MapFlash::execute()
{
    count_++;
    int frame = countFrame_ / 2;
    if (count_ == frame) {
        data_0211b27c.state_ = (FadeEffector::UnkFadeState)6;
        data_0211b27c.count_ = 0;
        data_0211b27c.frames_ = frame;
    }
}

THUMB int MapFlash::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

MapFlash g_MapFlash;

THUMB void MapBackGroundColor::initialize(char* param)
{
    PARAM_MAP_SET_BACK_COLOR* data = (PARAM_MAP_SET_BACK_COLOR*)param;
    current_ = twn::TownStageEffectManager::getSingleton()->getCurrentBackColor();
    twn::TownStageEffectManager::getSingleton()->setNextBackColor(data->index);
    index_ = data->index;
    countFrame_ = data->frame;
    count_ = 0;
}

THUMB void MapBackGroundColor::execute()
{
    const int rgb_corner = 8;
    unsigned char rgbArray[rgb_corner * 3];
    dq5::level::FloorBackColor* currentBack = dq5::level::FloorBackColor::getRecord(current_);
    dq5::level::FloorBackColor* nextBack = dq5::level::FloorBackColor::getRecord(index_);
    dss::Fix32 ratio;
    dss::Fix32 one;
    one.value = 0x1000;
    count_++;
    ratio.value = (count_ << 12) / countFrame_;
    char* currentColor = (char*)currentBack;
    char* nextColor = (char*)nextBack;
    for (int i = 0; i < rgb_corner * 3; i++) {
        rgbArray[i] = ((one - ratio) * currentColor[i] + ratio * nextColor[i]).value / 0x1000;
    }
    unkfunc_02048640(&rgbArray[12], &rgbArray[15], &rgbArray[18], &rgbArray[21], &rgbArray[0], &rgbArray[3], &rgbArray[6], &rgbArray[9]);
}

THUMB int MapBackGroundColor::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

MapBackGroundColor gMapBackGroundColor;

THUMB void MapBackGroundColorInit::initialize(char* param)
{
    PARAM_MAP_RESTORE_BACK_COLOR* data = (PARAM_MAP_RESTORE_BACK_COLOR*)param;
    current_ = twn::TownStageEffectManager::getSingleton()->getCurrentBackColor();
    index_ = twn::TownStageEffectManager::getSingleton()->getNextBackColor();
    countFrame_ = data->frame;
    count_ = 0;
}

THUMB void MapBackGroundColorInit::execute()
{
    const int rgb_corner = 8;
    unsigned char rgbArray[rgb_corner * 3];
    dq5::level::FloorBackColor* currentBack = dq5::level::FloorBackColor::getRecord(current_);
    dq5::level::FloorBackColor* nextBack = dq5::level::FloorBackColor::getRecord(index_);
    dss::Fix32 ratio;
    dss::Fix32 one;
    one.value = 0x1000;
    count_++;
    ratio.value = (count_ << 12) / countFrame_;
    char* currentColor = (char*)currentBack;
    char* nextColor = (char*)nextBack;
    for (int i = 0; i < rgb_corner * 3; i++) {
        rgbArray[i] = ((one - ratio) * nextColor[i] + ratio * currentColor[i]).value / 0x1000;
    }
    unkfunc_02048640(&rgbArray[12], &rgbArray[15], &rgbArray[18], &rgbArray[21], &rgbArray[0], &rgbArray[3], &rgbArray[6], &rgbArray[9]);
}

THUMB int MapBackGroundColorInit::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

MapBackGroundColorInit gMapBackGroundColorInit;

THUMB void MapBlendColor::initialize(char* scriptParam)
{
    PARAM_MAP_BLEND_COLOR* param = (PARAM_MAP_BLEND_COLOR*)scriptParam;
    rate_.vx.value = param->r;
    rate_.vy.value = param->g;
    rate_.vz.value = param->b;
    count_ = 0;
    countFrame_ = param->frame;
}

THUMB void MapBlendColor::execute()
{
    dss::Fix32 ratio;
    dss::Fix32 one;
    one.value = 0x1000;
    dss::Fix32Vector3 defaultRate = twn::TownStageEffectManager::getSingleton()->getDefaultPaletteRate();
    dss::Fix32Vector3 current;
    count_++;
    ratio.value = (count_ << 12) / countFrame_;
    current = defaultRate * (one - ratio) + rate_ * ratio;
    twn::TownStageEffectManager::getSingleton()->setRGBRate(current, 0);
}

THUMB int MapBlendColor::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

MapBlendColor g_MapBlendColor;

THUMB void MapBlendColorInit::initialize(char* scriptParam)
{
    PARAM_MAP_BLEND_INIT* param = (PARAM_MAP_BLEND_INIT*)scriptParam;
    rate_ = twn::TownStageEffectManager::getSingleton()->getPaletteRate();
    count_ = 0;
    countFrame_ = param->frame;
}

THUMB void MapBlendColorInit::execute()
{
    dss::Fix32 ratio;
    dss::Fix32 one;
    one.value = 0x1000;
    dss::Fix32Vector3 defaultRate = twn::TownStageEffectManager::getSingleton()->getDefaultPaletteRate();
    dss::Fix32Vector3 current;
    count_++;
    ratio.value = (count_ << 12) / countFrame_;
    current = rate_ * (one - ratio) + defaultRate * ratio;
    twn::TownStageManager::getSingleton()->SetRGBRate(current, 1);
}

THUMB int MapBlendColorInit::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

MapBlendColorInit g_MapBlendColorInit;

THUMB void Map_texture_scale::initialize(char* scriptParam)
{
    PARAM_MAP_TEXTURE_SCALE* param = (PARAM_MAP_TEXTURE_SCALE*)scriptParam;
    fx32 x;
    fx32 y;
    twn::TownStageEffectManager::getSingleton()->getTextureScaling(x, y);
    frame_ = param->frame;
    scaleX_ = (param->scaleX - x) / frame_;
    scaleY_ = (param->scaleY - y) / frame_;
    counter_ = 0;
}

THUMB void Map_texture_scale::execute()
{
    fx32 x;
    fx32 y;
    twn::TownStageEffectManager::getSingleton()->getTextureScaling(x, y);
    twn::TownStageEffectManager::getSingleton()->setTextureScaling(x + scaleX_, y + scaleY_);
    counter_++;
}

THUMB int Map_texture_scale::isEnd()
{
    if (frame_ <= counter_) {
        return true;
    }
    return false;
}

Map_texture_scale gMap_texture_scale;

THUMB void GlobalMapOpen::initialize(char* scriptParam)
{
    twn::TownGlobalMap::getSingleton().setup();
    twn::TownGlobalMap::getSingleton().open();
}

THUMB int GlobalMapOpen::isEnd()
{
    if (twn::TownGlobalMap::getSingleton().isOpen() != false) {
        return true;
    }
    return false;
}

GlobalMapOpen g_GlobalMapOpen;

THUMB void GlobalMapClose::initialize(char* scriptParam)
{
    twn::TownGlobalMap::getSingleton().close();
}

THUMB int GlobalMapClose::isEnd()
{
    if (twn::TownGlobalMap::getSingleton().isClose()) {
        twn::TownGlobalMap::getSingleton().cleanup();
        return true;
    }
    return false;
}

GlobalMapClose g_GlobalMapClose;

THUMB bool cmdSetGlobalMapPosition(void* scriptParam)
{
    PARAM_SET_MAP_POSITION* param = (PARAM_SET_MAP_POSITION*)scriptParam;
    twn::TownGlobalMap::getSingleton().setupPoint(param->x, param->y, param->kind);
    return true;
}

THUMB void MapCameraPosition::initialize(char* param)
{
    PARAM_MAP_CAMERA_POSITION* data = (PARAM_MAP_CAMERA_POSITION*)param;
    dss::Fix32Vector3 target;
    target.vx.value = data->endX;
    target.vy.value = data->endY;
    target.vz.value = data->endZ;
    endFlag_ = data->endFlag;
    TownCamera::getSingleton()->setMoveTo(target, data->frame, false);
}

THUMB int MapCameraPosition::isEnd()
{
    if (endFlag_ == 1) {
        return true;
    }
    return TownCamera::getSingleton()->isEndMotion();
}

MapCameraPosition gMapCameraPosition;

THUMB void MapCameraPositionAbs::initialize(char* param)
{
    PARAM_CAMERA_MOVE_ABS* data = (PARAM_CAMERA_MOVE_ABS*)param;
    dss::Fix32Vector3 target;
    target.vx.value = data->endX;
    target.vy.value = data->endY;
    target.vz.value = data->endZ;
    TownCamera::getSingleton()->setMoveTo(target, data->frame, true);
    endFlag_ = data->endFlag;
}

THUMB int MapCameraPositionAbs::isEnd()
{
    if (endFlag_ == 1) {
        return true;
    }
    return TownCamera::getSingleton()->isEndMotion();
}

MapCameraPositionAbs gMapCameraPositionAbs;

THUMB void MapCameraAngle::initialize(char* param)
{
    PARAM_MAP_CAMERA_ANGLE* data = (PARAM_MAP_CAMERA_ANGLE*)param;
    dss::Fix32 deg;
    deg.value = data->angle;
    short dataAngle = degreeToAngle(deg);
    dss::Vector3<short> angle;
    twn::TownActionCalculate::setAngle(data->axis, dataAngle, angle);
    endFlag_ = data->endFlag;
    TownCamera::getSingleton()->setRotTo(angle, data->frame, false);
}

THUMB int MapCameraAngle::isEnd()
{
    if (endFlag_ == 1) {
        return true;
    }
    return TownCamera::getSingleton()->isEndMotion();
}

MapCameraAngle gMapCameraAngle;

THUMB void MapCameraGaze::initialize(char* param)
{
    PARAM_MAP_CAMERA_GAZE* data = (PARAM_MAP_CAMERA_GAZE*)param;
    TownCamera::getSingleton()->resetCameraMove(data->frame);
}

THUMB int MapCameraGaze::isEnd()
{
    if (TownCamera::getSingleton()->isEndChangeDistance() == false) {
        return false;
    }
    return TownCamera::getSingleton()->isEndMotion();
}

MapCameraGaze gMapCameraGaze;

THUMB void MapEventCamera::initialize(char* param)
{
    PARAM_MAP_EVENT_CAMERA* data = (PARAM_MAP_EVENT_CAMERA*)param;
    twn::TownStageManager::getSingleton()->setCameraNo(data->channel, data->screen);
    TownCamera::getSingleton()->setCameraLock(true);
    countFrame_ = data->frame;
    count_ = 0;
}

THUMB void MapEventCamera::execute()
{
    count_++;
}

THUMB int MapEventCamera::isEnd()
{
    if (count_ >= countFrame_) {
        twn::TownStageManager::getSingleton()->setCameraNo(0, 0);
        twn::TownStageManager::getSingleton()->setCameraNo(0, 1);
        TownCamera::getSingleton()->setCameraLock(false);
        return true;
    }
    return false;
}

MapEventCamera gMapEventCamera;

THUMB bool cmd_map_animation(void* scriptParam)
{
    PARAM_MAP_ANIMATION* param = (PARAM_MAP_ANIMATION*)scriptParam;
    twn::TownStageManager::getSingleton()->eventAnim(param->channel - 500, 0);
    return true;
}

THUMB bool cmd_map_shake(void* scriptParam)
{
    PARAM_MAP_SHAKE* param = (PARAM_MAP_SHAKE*)scriptParam;
    TownCamera::getSingleton()->setShake(param->type, param->count);
    return true;
}

THUMB bool cmd_effect_blur(void* scriptParam)
{
    int* param = (int*)scriptParam;
    if (param[0] == 1) {
        dss::g_DISPLAYPLUGIN_DOUBLE3D.ReqBlurMode(0);
    } else {
        dss::g_DISPLAYPLUGIN_DOUBLE3D.ReqBlurMode(1);
        dss::g_DISPLAYPLUGIN_DOUBLE3D.SetBlur(param[1], param[2]);
    }
    return true;
}

THUMB void CameraChangeDistance::initialize(char* scriptParam)
{
    PARAM_CAMERA_CHANGE_DISTANCE* param = (PARAM_CAMERA_CHANGE_DISTANCE*)scriptParam;
    dss::Fix32 distance;
    distance.value = param->distance;
    TownCamera::getSingleton()->setChangeDistance(param->frame, distance);
    endFlag_ = param->endFlag;
}

THUMB int CameraChangeDistance::isEnd()
{
    if (endFlag_ == 1) {
        return true;
    }
    return TownCamera::getSingleton()->isEndChangeDistance();
}

CameraChangeDistance gCameraChangeDistance;

THUMB bool cmn_camera_lock_pov(void* scriptParam)
{
    PARAM_CAMERA_LOCK_POV* param = (PARAM_CAMERA_LOCK_POV*)scriptParam;
    TownCamera::getSingleton()->setLockPov(param->flag);
    return true;
}

THUMB bool cmdEffectTransfer(void* scriptParam)
{
    PARAM_EFFECT_TRANSFER* param = (PARAM_EFFECT_TRANSFER*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    twn::TownRiseupManager::getSingleton().setupSprite(param->effect, pos, param->flag, 0);
    return true;
}

THUMB bool cmdEffectModel(void* scriptParam)
{
    PARAM_EFFECT_TRANSFER_3D* param = (PARAM_EFFECT_TRANSFER_3D*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    twn::TownRiseupManager::getSingleton().setupModel(param->effect, pos);
    return true;
}

THUMB bool cmd_camera_lock_target_player(void* scriptParam)
{
    PARAM_MAP_CAMERA_LOCK_TARGET_PLAYER* param = (PARAM_MAP_CAMERA_LOCK_TARGET_PLAYER*)scriptParam;
    TownCamera::getSingleton()->setTargetPlayer(param->flag);
    return true;
}

THUMB bool cmd_camera_clip_distance(void* scriptParam)
{
    PARAM_CAMERA_CLIP_DISTANCE* param = (PARAM_CAMERA_CLIP_DISTANCE*)scriptParam;
    dss::Fix32 distance;
    distance.value = param->distance;
    twn::TownStageManager::getSingleton()->SetBBoxFar(distance);
    return true;
}

THUMB bool cmd_camera_near(void* scriptParam)
{
    PARAM_MAP_CAMERA_NEAR* param = (PARAM_MAP_CAMERA_NEAR*)scriptParam;
    TownCamera* camera = TownCamera::getSingleton();
    camera->camera_.unk_004.setNear(param->_near);
    camera->camera_.unk_074.setNear(param->_near);
    return true;
}

THUMB void CameraResetDistance::initialize(char* scriptParam)
{
    PARAM_CAMERA_RESET_DISTANCE* param = (PARAM_CAMERA_RESET_DISTANCE*)scriptParam;
    TownCamera::getSingleton()->resetDistance(param->frame);
}

THUMB int CameraResetDistance::isEnd()
{
    return TownCamera::getSingleton()->isEndChangeDistance();
}

CameraResetDistance gCameraResetDistance;

THUMB void CameraMovePov::initialize(char* scriptParam)
{
    PARAM_CAMERA_MOVE_POV* param = (PARAM_CAMERA_MOVE_POV*)scriptParam;
    dss::Fix32Vector3 pos = cmn::CommonCalculate::setVecByParam(param->endX, param->endY, param->endZ);
    TownCamera::getSingleton()->setPovMove(pos, param->frame, param->absFlag);
    endFlag_ = param->endFlag;
}

THUMB int CameraMovePov::isEnd()
{
    if (endFlag_ == 1) {
        return true;
    }
    if (TownCamera::getSingleton()->isEndPovMove()) {
        return true;
    }
    return false;
}

CameraMovePov gCameraMovePov;

THUMB void CameraMoveToPlayer::initialize(char* scriptParam)
{
    PARAM_CAMERA_MOVE_TO_PLAYER* param = (PARAM_CAMERA_MOVE_TO_PLAYER*)scriptParam;
    TownCamera::getSingleton()->setMoveTargetPlayer(param->frame);
}

THUMB int CameraMoveToPlayer::isEnd()
{
    if (TownCamera::getSingleton()->isEndMotion() == true) {
        TownCamera::getSingleton()->setTargetPlayer(true);
        return true;
    }
    return false;
}

CameraMoveToPlayer gCameraMoveToPlayer;

THUMB void Cmd_ikada_move2_player_get_on::initialize(char* scriptParam)
{
    PARAM_IKADA_MOVE2_PLAYER_GET_ON* param = (PARAM_IKADA_MOVE2_PLAYER_GET_ON*)scriptParam;
    dss::Fix32Vector3 start = twn::TownPlayerManager::getSingleton().getPosition();
    dss::Fix32Vector3 target = cmn::CommonCalculate::setVecByParam(param->endX, param->endY, param->endZ);
    dss::Fix32 speed;
    speed.value = param->rate;
    if (param->absFlag == 1) {
        target += start;
    }
    twn::TownPlayerManager::getSingleton().setIkadaSpeedMove(start, target, speed);
}

THUMB int Cmd_ikada_move2_player_get_on::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().isFinish() != false) {
        return true;
    }
    return false;
}

Cmd_ikada_move2_player_get_on gCmd_ikada_move2_player_get_on;

THUMB void Cmd_ikada_move_player_get_on::initialize(char* scriptParam)
{
    PARAM_IKADA_MOVE_PLAYER_GET_ON* param = (PARAM_IKADA_MOVE_PLAYER_GET_ON*)scriptParam;
    dss::Fix32Vector3 start = twn::TownPlayerManager::getSingleton().getPosition();
    dss::Fix32Vector3 target = cmn::CommonCalculate::setVecByParam(param->endX, param->endY, param->endZ);
    if (param->absFlag == 1) {
        target += start;
    }
    twn::TownPlayerManager::getSingleton().setIkadaFrameMove(start, target, param->frame);
}

THUMB int Cmd_ikada_move_player_get_on::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().isFinish() != false) {
        return true;
    }
    return false;
}

Cmd_ikada_move_player_get_on gCmd_ikada_move_player_get_on;

THUMB void Cmd_set_camera_angle_abs::initialize(char* scriptParam)
{
    PARAM_SET_CAMERA_ANGLE_ABS* data = (PARAM_SET_CAMERA_ANGLE_ABS*)scriptParam;
    dss::Vector3<short>& nowAngle = TownCamera::getSingleton()->camera_.unk_004.getAngle();
    short x = nowAngle.vx;
    short z = nowAngle.vz;
    dss::Vector3<short> angle;
    dss::Fix32 fx;
    fx.value = data->angleY;
    angle.set(x, degreeToAngle(fx), z);
    TownCamera::getSingleton()->setRotTo(angle, data->frame, true);
    endFlag_ = data->endFlag;
}

THUMB int Cmd_set_camera_angle_abs::isEnd()
{
    if (endFlag_ == 1) {
        return true;
    }
    int ctrl = getPlacementCtrlId();
    if (TownCamera::getSingleton()->isEndMotion() == true) {
        return true;
    }
    return false;
}

Cmd_set_camera_angle_abs gCmd_set_camera_angle_abs;

THUMB void Cmd_door_action::initialize(char* scriptParam)
{
    PARAM_DOOR_ACTION* data = (PARAM_DOOR_ACTION*)scriptParam;
    twn::TownPlayerManager::getSingleton().player_.townActionDoor_.scriptOpen(data->door1, data->door2, data->action);
}

THUMB int Cmd_door_action::isEnd()
{
    return twn::TownPlayerManager::getSingleton().player_.townActionDoor_.scriptEnd();
}

Cmd_door_action gCmd_door_action;

THUMB bool cmd_is_trigger3(void* scriptParam)
{
    PARAM_IS_TRIGGER3* param = (PARAM_IS_TRIGGER3*)scriptParam;
    dss::Fix32Vector3 start;
    dss::Fix32Vector3 end;
    start.vx.value = param->startX;
    start.vy.value = param->startY;
    start.vz.value = param->startZ;
    end.vx.value = param->endX;
    end.vy.value = param->endY;
    end.vz.value = param->endZ;
    dss::Fix32Vector3 pos = twn::TownPlayerManager::getSingleton().getPosition();
    short idx = twn::TownPlayerManager::getSingleton().getDirection();
    static dss::Fix32Vector3 returnPos(0, 0, 0);
    static int firstFlag = true;
    if (cmn::CommonCalculate::areaCheck(pos, idx, start, end, 0, 6) == true) {
        cmn::g_cmnPartyInfo.setPosition(cmn::g_cmnPartyInfo.prev_position_);
        if (twn::TownPlayerManager::getSingleton().getActionType() == twn::ACTION_TYPE_IKADA) {
            twn::TownPlayerManager::getSingleton().player_.townActionIkada_.setIkadaPosition(cmn::g_cmnPartyInfo.prev_position_);
        }
        if (firstFlag == false) {
            if (cmn::CommonCalculate::areaCheck(cmn::g_cmnPartyInfo.position_, idx, start, end, 0, 6) == true) {
                cmn::g_cmnPartyInfo.setPosition(returnPos);
                if (twn::TownPlayerManager::getSingleton().getActionType() == twn::ACTION_TYPE_IKADA) {
                    twn::TownPlayerManager::getSingleton().player_.townActionIkada_.setIkadaPosition(returnPos);
                }
            }
        }
        return true;
    }
    returnPos = pos;
    firstFlag = false;
    return false;
}

THUMB bool cmd_is_open_door(void* scriptParam)
{
    PARAM_IS_OPEN_DOOR* param = (PARAM_IS_OPEN_DOOR*)scriptParam;
    bool ret = twn::TownFurnitureManager::getSingleton()->isOpenDoor(param->uid);
    if (param->type != 0) {
        if (ret == false) {
            return true;
        }
        return false;
    }
    return ret;
}

THUMB bool cmd_set_door_close(void* scriptParam)
{
    int num = twn::TownStageManager::getSingleton()->getObjectNum();
    for (int i = 0; i < num; i++) {
        switch (twn::TownStageManager::getSingleton()->getCommonID(i)) {
            case 0x1130:
            case 0x1131:
            case 0x1132:
            case 0x1133:
            case 0x1134:
            case 0x1135:
            case 0x1136:
            case 0x1137:
            case 0x1138:
            case 0x1139:
            case 0x113a:
            case 0x113b:
            case 0x113c: {
                int uid = twn::TownStageManager::getSingleton()->getMapObjUid(i);
                twn::TownStageManager::getSingleton()->setObjectDraw(uid, 1, 1);
                twn::TownStageManager::getSingleton()->setAlpha(i, 0x1f);
                break;
            }
        }
    }
    status::g_StageInfo.initDoorOpenFlag();
    return true;
}

THUMB bool cmd_map_camera_default_angle(void* scriptParam)
{
    PARAM_MAP_CAMERA_DEFAULT_ANGLE* param = (PARAM_MAP_CAMERA_DEFAULT_ANGLE*)scriptParam;
    dss::Vector3<short> angle;
    dss::Fix32Vector3 fx;
    fx.vx.value = param->angleX;
    fx.vy.value = param->angleY;
    fx.vz.value = param->angleZ;
    angle.set(degreeToAngle(fx.vx), degreeToAngle(fx.vy), degreeToAngle(fx.vz));
    TownCamera::getSingleton()->setDefaultAngle(angle);
    return true;
}

THUMB bool cmd_set_camera_limit(void* scriptParam)
{
    PARAM_SET_CAMERA_LIMIT* param = (PARAM_SET_CAMERA_LIMIT*)scriptParam;
    dss::Fix32 limit;
    switch (param->flag) {
        case 0:
            limit.value = 0;
            TownCamera::getSingleton()->setLimitL(limit);
            TownCamera::getSingleton()->setLimitR(limit);
            break;
        case 1:
            limit.value = 0x1e000;
            TownCamera::getSingleton()->setLimitL(limit);
            TownCamera::getSingleton()->setLimitR(limit);
            break;
        case 2:
            limit.value = -0x1000;
            TownCamera::getSingleton()->setLimitL(limit);
            TownCamera::getSingleton()->setLimitR(limit);
            break;
    }
    return true;
}

THUMB bool cmd_delete_furniture_item(void* scriptParam)
{
    PARAM_DELETE_FURNITURE_ITEM* param = (PARAM_DELETE_FURNITURE_ITEM*)scriptParam;
    twn::TownFurnitureManager::getSingleton()->setFurnFlag(param->uid, param->flag);
    return true;
}

void ScriptCommandTown_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
