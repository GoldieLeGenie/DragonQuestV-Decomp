#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

bool cmdIsPartyMember(void* param);
bool cmdIsPartyRideCarriage(void* param);
bool cmd_is_party_top(void* param);
bool cmd_is_not_party_top(void* param);
bool cmd_check_player_item(void* param);
bool cmd_set_party_reserve_order(void* param);
bool cmd_party_copy_character(void* param);
bool cmd_is_procure_item(void* param);
bool cmd_map_effect_sepia();
bool cmd_check_player_hp_mp(void* param);
bool cmd_set_player_hp_mp(void* param);
bool cmdSetPlayerParam(void* param);
bool cmdSetPlayerCondition(void* param);
bool cmd_is_party_item(void* param);
bool cmd_is_not_party_item(void* param);
bool cmd_is_party_head_count(void* param);
bool cmd_is_not_party_head_count(void* param);
bool cmdCheckJisanMax(void* param);
bool cmdIsPutinMonsterJisan(void* param);
bool cmdIsPlayerItem(void* param);
bool cmdIsNotPlayerItem(void* param);
bool cmdSetReturnChurch(void* param);
bool cmdCheckPlayerHpMp(void* param);

