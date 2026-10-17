#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct Cmd_set_camera_target_chara_frame : ScriptCommand {
    int objNo_;                         // 0x04
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};


extern Cmd_set_camera_target_chara_frame gCmd_set_camera_target_chara_frame;
