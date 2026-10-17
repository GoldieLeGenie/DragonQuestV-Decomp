#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct FadeIn : ScriptCommand {
    short count_;                       // 0x04
    short countFrame_;                  // 0x06
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FadeOut : ScriptCommand {
    short count_;                       // 0x04
    short countFrame_;                  // 0x06
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FadeIn2 : ScriptCommand {
    short count_;                       // 0x04
    short countFrame_;                  // 0x06
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FadeOut2 : ScriptCommand {
    short count_;                       // 0x04
    short countFrame_;                  // 0x06
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct Music_volume : ScriptCommand {
    int endVolume_;                     // 0x04
    dss::Fix32 add_;                    // 0x08
    int frame_;                         // 0x0C
    int counter_;                       // 0x10
    int start_;                         // 0x14
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

struct PlayMusic : ScriptCommand {
    int musicNo_;                       // 0x04
    int playTime_;                      // 0x08
    int soundCount_;                    // 0x0C
    int playEnd_;                       // 0x10
    int flag_;                          // 0x14
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

bool cmd_is_trigger_common(void* scriptParam);
bool cmd_set_music(void* scriptParam);
bool cmd_music_pause(void* scriptParam);
bool cmd_play_music_now_map(void* scriptParam);
bool cmd_not_play_normal_sound(void* scriptParam);
bool cmd_set_ship_pos(void* scriptParam);
bool cmdChangeField(void* scriptParam);
bool cmd_check_smallmedal(void* scriptParam);

extern FadeIn g_FadeIn;
extern FadeOut g_FadeOut;
extern FadeIn2 g_FadeIn2;
extern FadeOut2 g_FadeOut2;
extern Music_volume gMusic_volume;
extern PlayMusic gPlayMusic;
