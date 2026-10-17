#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct CharacterMoveTo : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterMove2To : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterWait : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterTremble : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterActionMiniJump : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterActionGaze : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FadeinCharacter : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct FadeoutCharacter : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterRiseup : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharaRot : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterActionTurn : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterActionNormalJump : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct Cmd_chara_move_line_to_player : ScriptCommand {
    bool waitMenu_;                     // 0x04
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

struct CharacterMove2ToPlayer : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterMoveToParty : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterMove2ToParty : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CharacterMoveToPlayer : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct Cmd_character_rgb_anim2 : ScriptCommand {
    int endFlag_;                       // 0x04
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct Charcter_3d_motion : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

struct Cmd_chara_line_move : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

struct Cmd_chara_line_move2 : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual int isEnd();
};

struct CharacterHueChange : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};
bool Cmd_chara_start_action(void* param);
bool cmd_is_talked_at_shop(void* param);
bool cmdCharacterActionStepping(void* param);
bool cmdCharacterActionStill(void* param);
bool cmdCharacterActionWriggle(void* param);
bool cmdCharacterActionSleep(void* param);
bool cmdCharacterMoveRoam(void* param);
bool cmd_character_not_change_direction(void* param);
bool cmd_character_swing_round(void* param);
bool cmdSetCharacterPosition(void* param);
bool cmdSetCharacterDirection(void* param);
bool cmdCharacterActionNear(void* param);
bool cmdCharacterActionDisplay(void* param);
bool cmd_chara_shadow(void* param);
bool cmd_chara_alpha(void* param);
bool cmdSetCharacterCollision(void* param);
bool cmdCharacterActionPursue(void* param);
bool cmd_character_move_random(void* param);
bool cmd_character_move_reverse(void* param);
bool cmd_character_move_passive(void* param);
bool cmd_character_set_coll_stage(void* param);
bool cmd_is_character_direction(void* param);
bool cmd_is_character_front(void* param);
bool cmd_is_trigger_distance(void* param);
bool cmd_chara_voice(void* param);
bool cmd_character_pose_change(void* param);
bool cmd_character_anim(void* param);
bool cmd_set_chara_motion2(void* param);
bool cmd_copy_party_chara(void* param);
bool cmd_set_chara_map_uid(void* param);
bool cmdSetCharacterScale(void* param);
bool cmdSetRockRelocation(void* param);
bool cmdSetRockSave(void* param);
bool cmdSetShadowOnly(void* param);
bool cmd_set_chara_synchro(void* param);
bool cmd_set_chara_mortion_lock(void* param);
bool cmd_set_chara_coll(void* param);

extern CharacterMoveTo g_CharacterMoveTo;
extern CharacterMove2To g_CharacterMove2To;
extern CharacterWait g_CharacterWait;
extern CharacterTremble g_CharacterTremble;
extern CharacterActionMiniJump gCharacterActionMiniJump;
extern CharacterActionGaze g_CharacterActionGaze;
extern FadeinCharacter gFadeinCharacter;
extern FadeoutCharacter gFadeoutCharacter;
extern CharacterRiseup g_CharacterRiseup;
extern CharaRot gCharaRot;
extern CharacterActionTurn g_CharacterActionTurn;
extern CharacterMoveToParty g_CharacterMoveToParty;
extern CharacterMove2ToParty g_CharacterMove2ToParty;
extern CharacterMoveToPlayer g_CharacterMoveToPlayer;
extern CharacterMove2ToPlayer g_CharacterMove2ToPlayer;
extern Cmd_chara_move_line_to_player gCmd_chara_move_line_to_player;
extern CharacterActionNormalJump gCharacterActionNormalJump;
extern Cmd_character_rgb_anim2 gCmd_character_rgb_anim2;
extern Charcter_3d_motion gCharcter_3d_motion;
extern Cmd_chara_line_move gCmd_chara_line_move;
extern Cmd_chara_line_move2 gCmd_chara_line_move2;
extern CharacterHueChange g_CharacterHueChange;
