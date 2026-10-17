#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct CmdMessage : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct CmdMessage2 : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct CmdMessageWaitClosing : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct CmdMessage2WaitClosing : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct MenuYesNo : ScriptCommand {
    unsigned int type_;                 // 0x04
    unsigned int index_;                // 0x08
    unsigned int position_;             // 0x0C
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
    void setFlag(bool flag);
};

struct Menu_save : ScriptCommand {
    int type_;                          // 0x04
    int chapter_;                       // 0x08
    bool waitFlag_;                     // 0x0C
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
    void itemMoveToSack(int index);
    void partyOut(int index);
};

struct MessageWithSound : ScriptCommand {
    int musicNo_;                       // 0x04
    int playTime_;                      // 0x08
    int soundCount_;                    // 0x0C
    int preMusicNo_;                    // 0x10
    int lastMessage_;                   // 0x14
    int stopSound_;                     // 0x18
    int playEnd_;                       // 0x1C
    int flag_;                          // 0x20
    int wait_;                          // 0x24
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct Message1SelfClosing : ScriptCommand {
    unsigned int count_;                // 0x04
    unsigned int frame_;                // 0x08
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct ShakeMessage : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct DelayMessage : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct NarrationMessage : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct NarrationMessage2 : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

bool cmd_set_no_search_message(void* param);
bool cmd_set_macro_actor();
bool cmd_set_macro_target();
bool cmd_set_macro_target_index(void* param);
bool cmd_set_macro_i_name(void* param);
bool cmd_random_message(void* param);
bool cmd_set_message_sound(void* param);
bool cmd_set_macro_x_times_can_cast();
bool cmdSetMacroTargetForPosition(void* param);
bool cmdSetMacroTargetForIndex(void* param);
bool cmdSetMacroMName(void* param);
bool cmdSetBasicMenu(void* param);
bool cmdSetMacroSpell(void* param);
bool cmdSetMacroTargetWithDeath(void* param);

extern CmdMessage gCmdMessage;
extern CmdMessage2 gCmdMessage2;
extern MenuYesNo g_MenuYesNo;
extern Menu_save gMenu_save;
extern CmdMessageWaitClosing gCmdMessageWaitClosing;
extern CmdMessage2WaitClosing gCmdMessage2WaitClosing;
extern MessageWithSound g_MessageWithSound;
extern Message1SelfClosing gMessage1SelfClosing;
extern ShakeMessage gShakeMessage;
extern DelayMessage gDelayMessage;
extern NarrationMessage g_NarrationMessage;
extern NarrationMessage2 g_NarrationMessage2;
