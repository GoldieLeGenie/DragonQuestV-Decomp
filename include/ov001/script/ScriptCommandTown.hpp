#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct Map_texture_scale : ScriptCommand {
    int frame_;                         // 0x04
    int counter_;                       // 0x08
    fx32 scaleX_;                       // 0x0C
    fx32 scaleY_;                       // 0x10
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

struct LocationEffect : ScriptCommand {
    int index;                          // 0x04
    virtual void initialize(char* scriptParam);
    virtual void terminate();
    virtual int isEnd();
};

struct LocationEffectMove : ScriptCommand {
    int index;                          // 0x04
    virtual void initialize(char* scriptParam);
    virtual void terminate();
    virtual int isEnd();
};

struct LocationEffectFade : ScriptCommand {
    int index;                          // 0x04
    virtual void initialize(char* scriptParam);
    virtual void terminate();
    virtual int isEnd();
};

struct MapFlash : ScriptCommand {
    int count_;                         // 0x04
    int countFrame_;                    // 0x08
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct MapBackGroundColor : ScriptCommand {
    int current_;                       // 0x04
    int index_;                         // 0x08
    int count_;                         // 0x0C
    int countFrame_;                    // 0x10
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct MapBackGroundColorInit : ScriptCommand {
    int current_;                       // 0x04
    int index_;                         // 0x08
    int count_;                         // 0x0C
    int countFrame_;                    // 0x10
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct MapBlendColor : ScriptCommand {
    dss::Fix32Vector3 rate_;            // 0x04
    int count_;                         // 0x10
    int countFrame_;                    // 0x14
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct MapBlendColorInit : ScriptCommand {
    dss::Fix32Vector3 rate_;            // 0x04
    int count_;                         // 0x10
    int countFrame_;                    // 0x14
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct GlobalMapOpen : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void terminate();
    virtual int isEnd();
};

struct GlobalMapClose : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void terminate();
    virtual int isEnd();
};

struct MapCameraPosition : ScriptCommand {
    int endFlag_;                       // 0x04
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct MapCameraPositionAbs : ScriptCommand {
    int endFlag_;                       // 0x04
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct MapCameraAngle : ScriptCommand {
    int endFlag_;                       // 0x04
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct MapCameraGaze : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CameraChangeDistance : ScriptCommand {
    int endFlag_;                       // 0x04
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CameraMovePov : ScriptCommand {
    int endFlag_;                       // 0x04
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CameraResetDistance : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CameraMoveToPlayer : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct MapEventCamera : ScriptCommand {
    int count_;                         // 0x04
    int countFrame_;                    // 0x08
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct Cmd_ikada_move2_player_get_on : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

struct Cmd_ikada_move_player_get_on : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

struct Cmd_set_camera_angle_abs : ScriptCommand {
    int endFlag_;                       // 0x04
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

struct Cmd_door_action : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

bool cmd_set_door_close(void* param);
bool cmd_is_open_door(void* param);
bool cmd_map_animation(void* param);
bool cmdEffectTransfer(void* param);
bool cmd_effect_blur(void* param);
bool cmd_map_shake(void* param);
bool cmdIsTrigger2(void* param);
bool cmd_is_trigger3(void* param);
bool cmd_is_trigger_character(void* param);
bool cmd_is_trigger2_character(void* param);
bool cmn_camera_lock_pov(void* param);
bool cmd_camera_lock_target_player(void* param);
bool cmd_camera_clip_distance(void* param);
bool cmd_camera_near(void* param);
bool cmd_map_camera_default_angle(void* param);
bool cmd_set_camera_limit(void* param);
bool cmd_set_ikada_info(void* param);
bool cmdSetGlobalMapPosition(void* param);
bool cmdEffectModel(void* param);
bool cmdSetOverviewPosition(void* param);
bool cmdSetOverviewChurchPosition(void* param);
bool cmd_delete_furniture_item(void* param);

extern Cmd_ikada_move_player_get_on gCmd_ikada_move_player_get_on;
extern Cmd_ikada_move2_player_get_on gCmd_ikada_move2_player_get_on;
extern Cmd_door_action gCmd_door_action;
extern LocationEffect g_LocationEffect;
extern LocationEffectMove g_LocationEffectMove;
extern LocationEffectFade g_LocationEffectFade;
extern MapFlash g_MapFlash;
extern MapBlendColor g_MapBlendColor;
extern MapBlendColorInit g_MapBlendColorInit;
extern MapBackGroundColor gMapBackGroundColor;
extern MapBackGroundColorInit gMapBackGroundColorInit;
extern MapCameraPosition gMapCameraPosition;
extern MapCameraAngle gMapCameraAngle;
extern MapCameraGaze gMapCameraGaze;
extern CameraChangeDistance gCameraChangeDistance;
extern MapCameraPositionAbs gMapCameraPositionAbs;
extern CameraMoveToPlayer gCameraMoveToPlayer;
extern CameraResetDistance gCameraResetDistance;
extern Cmd_set_camera_angle_abs gCmd_set_camera_angle_abs;
extern MapEventCamera gMapEventCamera;
extern CameraMovePov gCameraMovePov;
extern GlobalMapOpen g_GlobalMapOpen;
extern GlobalMapClose g_GlobalMapClose;
