#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct BattleMessage : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct BattleEffect : ScriptCommand {
    int ctrlIndex_;                     // 0x04
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct BattleMessage2 : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

bool cmd_set_encount_disable(void* param);
bool cmd_set_encount_stage_disable(void* param);
bool cmdEncount(void* param);
bool cmd_encount_set_flag(void* param);
bool cmd_battle_end_flag_set(void* param);
bool cmd_disable_demolition();
bool cmd_is_battle_turn(void* param);
bool cmdGetBattleTransition(void* param);
bool cmdBattleSystemLock(void* param);
bool cmdBattlePartyAdd(void* param);
bool cmdBattlePartyReorder(void* param);
bool cmdBattleEnd(void* param);
bool cmdIsBattleUseItem(void* param);
bool cmdSetBattleNpcMonsterIndex(void* param);
bool cmdSetBattleMonsterIndex(void* param);
bool cmdSetBattleMonsterAnimationIndex(void* param);
bool cmdSetBattleMonsterLoopAnimationIndex(void* param);
bool cmdSetDisableEscape(void* param);

extern BattleMessage g_BattleMessage;
extern BattleEffect g_BattleEffect;
extern BattleMessage2 g_BattleMessage2;
