#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct CmdSpeakToPlayer : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct CmdSpeakToPlayer2 : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct CmdSpeakToPlayerWaitClosing : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct CmdSpeakToPlayer2WaitClosing : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct MenuShop : ScriptCommand {
    int type_;                          // 0x04
    bool waitMenu_;                     // 0x08
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct Speak_to_player_self_closing : ScriptCommand {
    unsigned int frame_;                // 0x04
    unsigned int count_;                // 0x08
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct EventInn : ScriptCommand {
    unsigned int type_;                 // 0x04
    unsigned int index_;                // 0x08
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct NameSetMenu : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FriendMonsterAzuke : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

bool cmdIsSpeaked(void* param);
bool cmd_not_use_load_message();

extern CmdSpeakToPlayer gCmdSpeakToPlayer;
extern CmdSpeakToPlayer2 gCmdSpeakToPlayer2;
extern MenuShop g_MenuShop;
extern CmdSpeakToPlayerWaitClosing gCmdSpeakToPlayerWaitClosing;
extern CmdSpeakToPlayer2WaitClosing gCmdSpeakToPlayer2WaitClosing;
extern NameSetMenu g_NameSetMenu;
extern Speak_to_player_self_closing gSpeak_to_player_self_closing;
extern EventInn gEventInn;
extern FriendMonsterAzuke g_FriendMonsterAzuke;
