#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

bool cmd_floor_change(void* param);
bool cmd_floor_exit(void* param);
bool cmd_set_map_link_on_off(void* param);
bool cmd_change_map_link(void* param);
bool cmd_set_town_to_field_link(void* param);
bool cmn_set_field_to_town_link(void* param);
bool cmd_map_link_field_direct(void* param);
bool cmd_field_erase_symbol(void* param);
bool cmd_field_symbol_disp(void* param);
bool cmd_is_doorway(void* param);
bool cmd_floor_change_ending(void* param);

