#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct BgmFade : ScriptCommand {
    unsigned int bgm;                   // 0x04
    int count;                          // 0x08
    int frame;                          // 0x0C
    int fade;                           // 0x10
    int gain;                           // 0x14
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

bool cmd_set_se(void* param);
bool cmd_cut_se(void* param);
bool cmd_set_sound_in_setup(void* param);
bool cmdSetSe2(void* param);
bool cmdCutSe2(void* param);

extern BgmFade g_BgmFade;
