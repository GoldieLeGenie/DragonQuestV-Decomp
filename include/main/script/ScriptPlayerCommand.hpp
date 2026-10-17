#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

bool cmdIsPlayerStatusDead(void* param);
bool cmd_isMonster(void* param);
bool cmd_set_player_ride_on(void* param);
bool cmd_set_player_recovery(void* param);
bool cmd_party_display(void* param);
bool cmd_party_display2(void* param);
bool cmd_party_redisplay(void* param);
bool cmdCharacterSetPartyJoin(void* param);
bool cmdCharacterSetPartyQuit(void* param);
bool cmd_set_player_in_carriage(void* param);
bool cmdSetPartyJoinCarriage();
bool cmd_set_party_call_carriage(void* param);
bool cmdSetPartyTotalRecovery(void* param);
bool cmdIsPartyOrder(void* param);
bool cmdSearchMapObject(void* param);
bool cmdIsPlayerName(void* param);
bool cmdBookingPantherName(void* param);
bool cmdSetPantherName(void* param);
bool cmd_set_player_magic(void* param);
bool cmd_set_player_equip(void* param);
bool cmdChangePlayerDraw(void* param);
bool cmdSetVehicle(void* param);
bool cmd_set_player_shadow_field(void* param);
bool cmd_set_player_shadow_town(void* param);
bool cmdPlayerItemIntoFukuro(void* param);
bool cmdSetPlayerAzuke(void* param);
bool cmdSetPartyDirectionByPlayerNo(void* param);
bool cmdResetPartyDirectionByPlayerNo(void* param);
bool cmdIsPartyOrder2(void* param);

