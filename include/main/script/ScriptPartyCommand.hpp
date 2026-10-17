#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

bool cmd_is_party_all(void* param);
bool cmd_is_not_party_all(void* param);
bool cmdSetPartyQuitToAzuke(void* param);
bool cmd_check_inn_count(void* param);
bool cmdCheckAllPlayerCount(void* param);
bool cmd_party_add_npc(void* param);
bool cmd_party_del_npc(void* param);
bool cmdSetHeadChara(void* param);
bool cmdReturnInCarriage(void* param);
bool cmdSortPartyKind(void* param);

