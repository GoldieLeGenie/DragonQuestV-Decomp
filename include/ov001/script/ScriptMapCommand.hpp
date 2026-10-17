#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

namespace twn {
    struct MapObjGridMove;
}

struct MapAnimationB : ScriptCommand {
    int target;                         // 0x04
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FurnitureMove : ScriptCommand {
    int index;                          // 0x04
    virtual void initialize(char* param);
    virtual void terminate();
    virtual int isEnd();
};

struct FurnitureMove2 : ScriptCommand {
    int index;                          // 0x04
    virtual void initialize(char* param);
    virtual void terminate();
    virtual int isEnd();
};

struct FurnitureRotate : ScriptCommand {
    int index;                          // 0x04
    virtual void initialize(char* param);
    virtual void terminate();
    virtual int isEnd();
};

struct FurnitureGroupMove : ScriptCommand {
    int index;                          // 0x04
    virtual void initialize(char* param);
    virtual void terminate();
    virtual int isEnd();
};

struct FurnitureGroupRotate : ScriptCommand {
    int index;                          // 0x04
    virtual void initialize(char* param);
    virtual void terminate();
    virtual int isEnd();
};

struct CofferProcess : ScriptCommand {
    bool change_;                       // 0x04
    int uid_;                           // 0x08
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct SpotLightON : ScriptCommand {
    dss::Fix32Vector3 vec;              // 0x04
    int maxCount;                       // 0x10
    int count;                          // 0x14
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct SpotLightOFF : ScriptCommand {
    int r;                              // 0x04
    int r2;                             // 0x08
    int maxCount;                       // 0x0C
    int count;                          // 0x10
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct MapObjGimmickMove : ScriptCommand {
    twn::MapObjGridMove* move_[2];      // 0x04
    int count_;                         // 0x0C
    int execNo_;                        // 0x10
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
    void clear();
    void regist(int uid, int flag, dss::Fix32 length);
};

bool cmdMapAnimationA(void* param);
bool cmdFurnitureFadeout(void* param);
bool cmdSetMapCollision(void* param);
bool cmdFurnitureMoveRequest(void* param);
bool cmdSetFurniturePosition(void* param);
bool cmdSetFloorMapObject(void* param);
bool cmdIsMapTreasure(void* param);
bool cmdSetEventDoor(void* param);
bool cmdMapTexture(void* param);
bool cmdSetMapTexture(void* param);
bool cmdCameraActionSet(void* param);
bool cmd_set_particle_draw(void* param);
bool cmd_set_particle_max(void* param);
bool cmd_reset_ninepuzzle(void* param);
bool Cmd_sugoroku_end_type(void* param);
bool cmd_set_ninepuzzle(void* param);
bool cmd_set_furniture_gaze(void* param);
bool cmdTruckSwitch(void* param);
bool cmdSetTruckSwitch(void* param);
bool cmdSetSurfaceOnOff(void* param);
bool cmdCheckHitMapUid(void* param);
bool cmd_setup_gimmick_move(void* param);
bool cmd_set_scope(void* param);
bool cmdSearchMapObj2(void* param);
bool cmdFurnitureCollMove(void* param);
bool cmdCheckSurface(void* param);
bool cmdSetCharaPosToMapObj(void* param);
bool cmdSetTruck_Start(void* param);
bool cmdCheckTruck_End(void* param);
bool cmdSetTruckWagon(void* param);
bool cmdSetShipInfo(void* param);
bool cmdSetIkadaArea(void* param);
bool cmdDelTruckWagon(void* param);
bool cmdDelScriptMapObject(void* param);

extern MapAnimationB g_MapAnimationB;
extern FurnitureMove g_FurnitureMove;
extern FurnitureMove2 g_FurnitureMove2;
extern CofferProcess g_CofferProcess;
extern FurnitureRotate g_FurnitureRotate;
extern FurnitureGroupMove g_FurnitureGroupMove;
extern FurnitureGroupRotate g_FurnitureGroupRotate;
extern SpotLightON g_SpotLightON;
extern SpotLightOFF g_SpotLightOFF;
extern MapObjGimmickMove g_MapObjGimmickMove;
