#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct PlayerMoveTo : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct PlayerMove2To : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct PlayerWait : ScriptCommand {
    int count_;                         // 0x04
    int countFrame_;                    // 0x08
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct PlayerRot : ScriptCommand {
    int endFlag_;                       // 0x04
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct PlayerEffectMark : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct PlayerMoveJump : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct PlayerMove2Jump : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct Cmd_player_line_move : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct Cmd_player_line_move2 : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct PartyOrder : ScriptCommand {
    int change_;                        // 0x04
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct PartyMoveOverlap : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct PartyMove2Formation : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct PlayerActionGetOnOff : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct PartyJumpByPlayerNo : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

bool cmdPlayerActionWriggle(void* param);
bool cmdPlayerActionStepping(void* param);
bool cmdPlayerActionStill(void* param);
bool cmdSetPlayerPosition(void* param);
bool cmdSetPlayerDirection(void* param);
bool cmd_set_player_sleep(void* param);
bool cmd_player_action_not_change_direction(void* param);
bool cmd_player_set_coll(void* param);
bool cmd_is_player_direction(void* param);
bool cmd_set_party_mark(void* param);
bool cmd_set_Van_and_Basha(void* param);
bool cmdCharacterPartyJoin(void* param);
bool cmdCharacterPartyQuit(void* param);
bool cmdStoreRestorePlayerItem(void* param);
bool cmdSetPartyKeep(void* param);
bool cmdSetCollPlayerToChara(void* param);
bool cmdSetPlayerPosAtMapObj(void* param);

extern PlayerMoveTo g_PlayerMoveTo;
extern PlayerMove2To g_PlayerMove2To;
extern PlayerRot gPlayerRot;
extern PlayerEffectMark gPlayerEffectMark;
extern Cmd_player_line_move gCmd_player_line_move;
extern Cmd_player_line_move2 gCmd_player_line_move2;
extern PlayerMoveJump g_PlayerMoveJump;
extern PlayerMove2Jump g_PlayerMove2Jump;
extern PlayerWait g_PlayerWait;
extern PartyMove2Formation g_PartyMove2Formation;
extern PartyOrder g_PartyOrder;
extern PartyMoveOverlap g_PartyMoveOverlap;
extern PlayerActionGetOnOff g_PlayerActionGetOnOff;
extern PartyJumpByPlayerNo g_PartyJumpByPlayerNo;
