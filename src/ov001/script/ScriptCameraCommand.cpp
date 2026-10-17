#pragma ipa file
#include "ov001/script/ScriptCameraCommand.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "main/script/CommandParam.hpp"

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline bool TownCamera::isEndMotion()
{
    return cameraMove_.isEnd();
}

THUMB void Cmd_set_camera_target_chara_frame::initialize(char* scriptParam)
{
    PARAM_SET_CAMERA_TARGET_CHARA_FRAME* data = (PARAM_SET_CAMERA_TARGET_CHARA_FRAME*)scriptParam;
    objNo_ = data->objId;
    int ctrl = getPlacementCtrlId(objNo_);
    dss::Fix32Vector3 target = TownCharacterManager::getSingleton()->getPosition(ctrl);
    TownCamera::getSingleton()->setMoveTo(target, data->frame, true);
}

THUMB int Cmd_set_camera_target_chara_frame::isEnd()
{
    int ctrl = getPlacementCtrlId(objNo_);
    if (TownCamera::getSingleton()->isEndMotion() == true) {
        TownCamera::getSingleton()->setMoveTragetChara(ctrl);
        return true;
    }
    return false;
}

THUMB void Cmd_set_camera_target_chara_frame::execute()
{
}

Cmd_set_camera_target_chara_frame gCmd_set_camera_target_chara_frame;
