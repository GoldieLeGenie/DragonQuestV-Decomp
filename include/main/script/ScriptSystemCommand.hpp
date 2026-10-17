#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct SugorokuTime : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct Cmd_key_wait_typeB : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct GameWait : ScriptCommand {
    int count_;                         // 0x04
    int countFrame_;                    // 0x08
    virtual void initialize(char* param);
    virtual void execute();
    virtual void terminate();
    virtual int isEnd();
};

struct CmdFriendMonsterMessage : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct CmdRiseupPlayerEquip : ScriptCommand {
    int ctrlID_;                        // 0x04
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

bool cmdSetup(void* param);
bool cmdPlayerLock(void* param);
bool cmd_check_search_action(void* param);
bool cmdMiniGame(void* param);
bool cmdSetItem(void* param);
bool cmdSetGold(void* param);
bool cmdSetCoin(void* param);
bool cmd_set_random(void* param);
bool cmd_set_random2(void* param);
bool cmdCharcter3DRotate(void* param);
bool cmd_set_sleep_near(void* param);
bool cmdSetRulaLook(void* param);
bool cmd_set_ranaruta(void* param);
bool cmdCheckMoney(void* param);
bool cmd_set_wait_counter(void* param);
bool isWaitCounter(void* param);
bool waitOperation(void* param);
bool cmd_set_day_count(void* param);
bool cmd_set_forward_counter(void* param);
bool isDayCount(void* param);
bool cmd_set_chapter(void* param);
bool cmdCheckHeroLevel(void* param);
bool cmd_chpater_store(void* param);
bool cmd_chpater_restore(void* param);
bool cmd_check_shoplist(void* param);
bool cmd_set_basha_go_into(void* param);
bool cmd_is_load_init(void* param);
bool cmd_map_black(void* param);
bool cmdIsTimezone(void* param);
bool cmdSetTimezone(void* param);
bool cmdSetTimezonePause(void* param);
bool cmd_map_change_timezone(void* param);
bool cmdIsTrigger(void* param);
bool cmd_set_lura_message(void* param);
bool cmd_check_event_item(void* param);
bool cmd_check_event_magic(void* param);
bool cmd_set_sugoroku_treasure(void* param);
bool cmdSetSugorokuEnd(void* param);
bool cmdSetSackItem(void* param);
bool cmdSetShopList(void* param);
bool cmdSetPlayerTownVehicle(void* param);
bool cmdCheckSpaceItemChara(void* param);
bool cmdSetMacroBaby(void* param);
bool cmdExecRuraLink(void* param);
bool cmd_check_event_item2(void* param);
bool cmdCheckUseEventItem(void* param);
bool cmdCoercionSort(void* param);
bool cmdSetCoercionSortEnable(void* param);
bool cmdSaveClearMonsterParty(void* param);
bool cmdCheckSaveMonster(void* param);
bool cmdCopySaveMonster(void* param);
bool cmdSetMacroPMName(void* param);
bool cmd_set_lura_message2(void* param);
bool cmd_start_opening(void* param);
bool cmd_save_last_party();
bool cmd_the_end(void* param);
bool cmd_check_the_end(void* param);
bool cmd_check_endroll(void* param);
bool cmdSetMacroSecond(void* param);
bool cmdSetMagicMove(void* param);
bool cmdChengeShopChater(void* param);
bool cmdResetReorderFlag(void* param);
bool cmdIsTimezone2(void* param);
bool cmdSetFadeDisable(void* param);
bool cmdSetMagicMoveSetDisable(void* param);
bool cmdReorderFormerMember(void* param);

extern Cmd_key_wait_typeB gCmd_key_wait_typeB;
extern GameWait g_GameWait;
extern SugorokuTime g_SugorokuTime;
extern CmdFriendMonsterMessage gCmdFriendMonsterMessage;
extern CmdRiseupPlayerEquip g_CmdRiseupPlayerEquip;
