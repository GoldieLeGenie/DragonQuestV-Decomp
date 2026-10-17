#include "main/script/ScriptCommand.hpp"
#include "main/script/ScriptBattleCommand.hpp"
#include "main/script/ScriptCommandCommon.hpp"
#include "main/script/ScriptFlagCommand.hpp"
#include "main/script/ScriptLinkCommand.hpp"
#include "main/script/ScriptMessageCommand.hpp"
#include "main/script/ScriptPartyCommand.hpp"
#include "main/script/ScriptPlayerCommand.hpp"
#include "main/script/ScriptSoundCommand.hpp"
#include "main/script/ScriptStatusCommand.hpp"
#include "main/script/ScriptSystemCommand.hpp"
#include "ov001/script/ScriptCameraCommand.hpp"
#include "ov001/script/ScriptCharaCommand.hpp"
#include "ov001/script/ScriptCommandTown.hpp"
#include "ov001/script/ScriptEffectCommandTown.hpp"
#include "ov001/script/ScriptMapCommand.hpp"
#include "ov001/script/ScriptMeisanhinCommand.hpp"
#include "ov001/script/ScriptMessageCommandTown.hpp"
#include "ov001/script/ScriptPlayerCommandTown.hpp"
#include "ov001/script/ScriptSurechigaiCommand.hpp"
#include "ov005/script/ScriptCommandField.hpp"

inline int CommandParameter::getCommandIndex()
{
    return command_;
}

inline bool CommandParameter::isTypeB()
{
    return flag_ & FLAG_TYPE_B;
}

inline void CommandParameter::setTerminated()
{
    flag_ |= FLAG_TERMINATED;
}

inline bool CommandParameter::isTerminated()
{
    return flag_ & FLAG_TERMINATED;
}

inline char* CommandParameter::getParam()
{
    return param_;
}

THUMB bool checkCommandType(CommandParameter* param)
{
    if (param->isTypeB()) {
        if (param->isTerminated()) {
            return false;
        }
        param->setTerminated();
    }
    return true;
}

THUMB bool CommandFunction(void* cmdParam)
{
    bool ret = true;
    CommandParameter* param = (CommandParameter*)cmdParam;
    switch (param->getCommandIndex()) {
    case 0:
        checkCommandType(param);
        break;
    case 1:
        if (checkCommandType(param)) {
            ret = true;
        }
        break;
    case 2:
        if (checkCommandType(param)) {
            ret = true;
        }
        break;
    case 3:
        if (checkCommandType(param)) {
            ret = cmdGetFlag(param->getParam());
        }
        break;
    case 4:
        if (checkCommandType(param)) {
            ret = cmdSetFlag(param->getParam());
        }
        break;
    case 5:
        if (checkCommandType(param)) {
            ret = cmdSetup(param->getParam());
        }
        break;
    case 11:
        if (checkCommandType(param)) {
            ret = cmdIsSpeaked(param->getParam());
        }
        break;
    case 13:
        if (checkCommandType(param)) {
            ret = cmd_is_talked_at_shop(param->getParam());
        }
        break;
    case 361:
        if (checkCommandType(param)) {
            ret = cmdChangeField(param->getParam());
        }
        break;
    case 22:
        if (checkCommandType(param)) {
            ret = cmd_character_not_change_direction(param->getParam());
        }
        break;
    case 23:
        if (checkCommandType(param)) {
            ret = cmd_character_swing_round(param->getParam());
        }
        break;
    case 17:
        if (checkCommandType(param)) {
            ret = cmdCharacterActionStepping(param->getParam());
        }
        break;
    case 18:
        if (checkCommandType(param)) {
            ret = cmdCharacterActionStill(param->getParam());
        }
        break;
    case 19:
        if (checkCommandType(param)) {
            ret = cmdCharacterActionWriggle(param->getParam());
        }
        break;
    case 20:
        if (checkCommandType(param)) {
            ret = cmdCharacterActionSleep(param->getParam());
        }
        break;
    case 21:
        if (checkCommandType(param)) {
            ret = cmdCharacterMoveRoam(param->getParam());
        }
        break;
    case 24:
        if (checkCommandType(param)) {
            ret = cmdSetCharacterPosition(param->getParam());
        }
        break;
    case 25:
        if (checkCommandType(param)) {
            ret = cmdSetCharacterDirection(param->getParam());
        }
        break;
    case 6:
        if (checkCommandType(param)) {
            ret = cmdPlayerLock(param->getParam());
        }
        break;
    case 12:
        if (checkCommandType(param)) {
            ret = Cmd_chara_start_action(param->getParam());
        }
        break;
    case 31:
        if (checkCommandType(param)) {
            ret = cmdSetPlayerPosition(param->getParam());
        }
        break;
    case 32:
        if (checkCommandType(param)) {
            ret = cmdSetPlayerDirection(param->getParam());
        }
        break;
    case 26:
        if (checkCommandType(param)) {
            ret = cmdPlayerActionWriggle(param->getParam());
        }
        break;
    case 27:
        if (checkCommandType(param)) {
            ret = cmdPlayerActionStepping(param->getParam());
        }
        break;
    case 28:
        if (checkCommandType(param)) {
            ret = cmdPlayerActionStill(param->getParam());
        }
        break;
    case 40:
        if (checkCommandType(param)) {
            ret = cmdCharacterActionNear(param->getParam());
        }
        break;
    case 49:
        if (checkCommandType(param)) {
            ret = cmdSetCharacterCollision(param->getParam());
        }
        break;
    case 47:
        if (checkCommandType(param)) {
            ret = cmd_chara_shadow(param->getParam());
        }
        break;
    case 48:
        if (checkCommandType(param)) {
            ret = cmd_chara_alpha(param->getParam());
        }
        break;
    case 50:
        if (checkCommandType(param)) {
            ret = cmd_set_player_sleep(param->getParam());
        }
        break;
    case 337:
        if (checkCommandType(param)) {
            ret = cmdSetCharacterScale(param->getParam());
        }
        break;
    case 52:
        if (checkCommandType(param)) {
            ret = cmd_check_search_action(param->getParam());
        }
        break;
    case 53:
        if (checkCommandType(param)) {
            ret = cmd_set_no_search_message(param->getParam());
        }
        break;
    case 54:
        if (checkCommandType(param)) {
            ret = cmdMiniGame(param->getParam());
        }
        break;
    case 55:
        if (checkCommandType(param)) {
            ret = cmdSetItem(param->getParam());
        }
        break;
    case 56:
        if (checkCommandType(param)) {
            ret = cmdSetGold(param->getParam());
        }
        break;
    case 57:
        if (checkCommandType(param)) {
            ret = cmdSetCoin(param->getParam());
        }
        break;
    case 58:
        if (checkCommandType(param)) {
            ret = cmd_set_random(param->getParam());
        }
        break;
    case 59:
        if (checkCommandType(param)) {
            ret = cmd_set_random2(param->getParam());
        }
        break;
    case 60:
        if (!checkCommandType(param)) {
            break;
        }
        ret = cmdCharcter3DRotate(param->getParam());
    case 61:
        if (checkCommandType(param)) {
            ret = cmd_set_sleep_near(param->getParam());
        }
        break;
    case 62:
        if (checkCommandType(param)) {
            ret = cmdSetRulaLook(param->getParam());
        }
        break;
    case 63:
        if (checkCommandType(param)) {
            ret = cmd_set_ranaruta(param->getParam());
        }
        break;
    case 64:
        if (checkCommandType(param)) {
            ret = cmdCheckMoney(param->getParam());
        }
        break;
    case 65:
        if (checkCommandType(param)) {
            ret = cmd_set_wait_counter(param->getParam());
        }
        break;
    case 66:
        if (checkCommandType(param)) {
            ret = isWaitCounter(param->getParam());
        }
        break;
    case 67:
        if (checkCommandType(param)) {
            ret = waitOperation(param->getParam());
        }
        break;
    case 68:
        ret = gCmd_key_wait_typeB.exec(param);
        break;
    case 69:
        if (checkCommandType(param)) {
            ret = cmd_set_day_count(param->getParam());
        }
        break;
    case 70:
        if (checkCommandType(param)) {
            ret = cmd_set_forward_counter(param->getParam());
        }
        break;
    case 71:
        if (checkCommandType(param)) {
            ret = isDayCount(param->getParam());
        }
        break;
    case 77:
        if (checkCommandType(param)) {
            ret = cmd_set_macro_actor();
        }
        break;
    case 78:
        if (checkCommandType(param)) {
            ret = cmd_set_macro_target();
        }
        break;
    case 79:
        if (checkCommandType(param)) {
            ret = cmd_set_macro_target_index(param->getParam());
        }
        break;
    case 80:
        if (checkCommandType(param)) {
            ret = cmd_set_macro_i_name(param->getParam());
        }
        break;
    case 73:
        if (checkCommandType(param)) {
            ret = cmd_set_chapter(param->getParam());
        }
        break;
    case 74:
        if (checkCommandType(param)) {
            ret = cmdCheckHeroLevel(param->getParam());
        }
        break;
    case 75:
        if (checkCommandType(param)) {
            ret = cmd_chpater_store(param->getParam());
        }
        break;
    case 76:
        if (checkCommandType(param)) {
            ret = cmd_chpater_restore(param->getParam());
        }
        break;
    case 81:
        if (checkCommandType(param)) {
            ret = cmd_check_shoplist(param->getParam());
        }
        break;
    case 82:
        if (checkCommandType(param)) {
            ret = cmd_set_basha_go_into(param->getParam());
        }
        break;
    case 83:
        if (checkCommandType(param)) {
            ret = cmd_is_load_init(param->getParam());
        }
        break;
    case 334:
        if (checkCommandType(param)) {
            ret = cmdSetVehicle(param->getParam());
        }
        break;
    case 84:
        if (checkCommandType(param)) {
            ret = cmd_not_use_load_message();
        }
        break;
    case 395:
        if (checkCommandType(param)) {
            ret = cmd_start_opening(param->getParam());
        }
        break;
    case 397:
        if (checkCommandType(param)) {
            ret = cmd_the_end(param->getParam());
        }
        break;
    case 402:
        if (checkCommandType(param)) {
            ret = cmd_check_the_end(param->getParam());
        }
        break;
    case 403:
        if (checkCommandType(param)) {
            ret = cmd_check_endroll(param->getParam());
        }
        break;
    case 396:
        if (checkCommandType(param)) {
            ret = cmd_save_last_party();
        }
        break;
    case 85:
        if (checkCommandType(param)) {
            ret = cmd_map_black(param->getParam());
        }
        break;
    case 86:
        if (checkCommandType(param)) {
            ret = cmdIsTimezone(param->getParam());
        }
        break;
    case 435:
        if (checkCommandType(param)) {
            ret = cmdIsTimezone2(param->getParam());
        }
        break;
    case 87:
        if (checkCommandType(param)) {
            ret = cmdSetTimezone(param->getParam());
        }
        break;
    case 88:
        if (checkCommandType(param)) {
            ret = cmdSetTimezonePause(param->getParam());
        }
        break;
    case 44:
        if (checkCommandType(param)) {
            ret = cmdCharacterActionDisplay(param->getParam());
        }
        break;
    case 102:
        if (checkCommandType(param)) {
            ret = cmd_character_set_coll_stage(param->getParam());
        }
        break;
    case 100:
        if (checkCommandType(param)) {
            ret = cmd_character_move_passive(param->getParam());
        }
        break;
    case 99:
        if (checkCommandType(param)) {
            ret = cmd_character_move_reverse(param->getParam());
        }
        break;
    case 98:
        if (checkCommandType(param)) {
            ret = cmd_character_move_random(param->getParam());
        }
        break;
    case 97:
        if (checkCommandType(param)) {
            ret = cmdCharacterActionPursue(param->getParam());
        }
        break;
    case 103:
        if (checkCommandType(param)) {
            ret = cmd_is_character_direction(param->getParam());
        }
        break;
    case 104:
        if (checkCommandType(param)) {
            ret = cmd_is_character_front(param->getParam());
        }
        break;
    case 105:
        if (checkCommandType(param)) {
            ret = cmd_is_trigger_distance(param->getParam());
        }
        break;
    case 108:
        if (checkCommandType(param)) {
            ret = cmd_character_pose_change(param->getParam());
        }
        break;
    case 114:
        if (checkCommandType(param)) {
            ret = cmd_copy_party_chara(param->getParam());
        }
        break;
    case 115:
        if (checkCommandType(param)) {
            ret = cmd_set_chara_map_uid(param->getParam());
        }
        break;
    case 106:
        if (checkCommandType(param)) {
            ret = cmd_chara_voice(param->getParam());
        }
        break;
    case 112:
        if (checkCommandType(param)) {
            ret = cmd_character_anim(param->getParam());
        }
        break;
    case 113:
        if (checkCommandType(param)) {
            ret = cmd_set_chara_motion2(param->getParam());
        }
        break;
    case 126:
        if (checkCommandType(param)) {
            ret = cmd_isMonster(param->getParam());
        }
        break;
    case 127:
        if (checkCommandType(param)) {
            ret = cmd_set_player_ride_on(param->getParam());
        }
        break;
    case 354:
        if (checkCommandType(param)) {
            ret = cmd_set_player_shadow_town(param->getParam());
        }
        break;
    case 346:
        if (checkCommandType(param)) {
            ret = cmd_set_player_shadow_field(param->getParam());
        }
        break;
    case 138:
        if (checkCommandType(param)) {
            ret = cmdCharacterPartyJoin(param->getParam());
        }
        break;
    case 139:
        if (checkCommandType(param)) {
            ret = cmdCharacterPartyQuit(param->getParam());
        }
        break;
    case 136:
        if (checkCommandType(param)) {
            ret = cmdCharacterSetPartyJoin(param->getParam());
        }
        break;
    case 137:
        if (checkCommandType(param)) {
            ret = cmdCharacterSetPartyQuit(param->getParam());
        }
        break;
    case 143:
        if (checkCommandType(param)) {
            ret = cmdSetPartyTotalRecovery(param->getParam());
        }
        break;
    case 144:
        if (checkCommandType(param)) {
            ret = cmdIsPartyOrder(param->getParam());
        }
        break;
    case 442:
        if (checkCommandType(param)) {
            ret = cmdIsPartyOrder2(param->getParam());
        }
        break;
    case 125:
        if (checkCommandType(param)) {
            ret = cmdIsPlayerStatusDead(param->getParam());
        }
        break;
    case 141:
        if (checkCommandType(param)) {
            ret = cmdSetPartyJoinCarriage();
        }
        break;
    case 122:
        if (checkCommandType(param)) {
            ret = cmd_player_action_not_change_direction(param->getParam());
        }
        break;
    case 124:
        if (checkCommandType(param)) {
            ret = cmd_is_player_direction(param->getParam());
        }
        break;
    case 129:
        if (checkCommandType(param)) {
            ret = cmd_set_player_recovery(param->getParam());
        }
        break;
    case 140:
        if (checkCommandType(param)) {
            ret = cmd_set_player_in_carriage(param->getParam());
        }
        break;
    case 132:
        if (checkCommandType(param)) {
            ret = cmd_party_display(param->getParam());
        }
        break;
    case 133:
        if (checkCommandType(param)) {
            ret = cmd_party_display2(param->getParam());
        }
        break;
    case 134:
        if (checkCommandType(param)) {
            ret = cmd_party_redisplay(param->getParam());
        }
        break;
    case 123:
        if (checkCommandType(param)) {
            ret = cmd_player_set_coll(param->getParam());
        }
        break;
    case 142:
        if (checkCommandType(param)) {
            ret = cmd_set_party_call_carriage(param->getParam());
        }
        break;
    case 130:
        if (checkCommandType(param)) {
            ret = cmd_set_party_mark(param->getParam());
        }
        break;
    case 135:
        if (checkCommandType(param)) {
            ret = cmd_set_Van_and_Basha(param->getParam());
        }
        break;
    case 159:
        if (checkCommandType(param)) {
            ret = cmd_battle_end_flag_set(param->getParam());
        }
        break;
    case 163:
        if (checkCommandType(param)) {
            ret = cmdMapAnimationA(param->getParam());
        }
        break;
    case 166:
        if (checkCommandType(param)) {
            ret = cmdSetMapCollision(param->getParam());
        }
        break;
    case 157:
        if (checkCommandType(param)) {
            ret = cmdEncount(param->getParam());
        }
        break;
    case 158:
        if (checkCommandType(param)) {
            ret = cmd_encount_set_flag(param->getParam());
        }
        break;
    case 162:
        if (checkCommandType(param)) {
            ret = cmd_is_procure_item(param->getParam());
        }
        break;
    case 145:
        if (checkCommandType(param)) {
            ret = cmdIsPartyMember(param->getParam());
        }
        break;
    case 146:
        if (checkCommandType(param)) {
            ret = cmdIsPartyRideCarriage(param->getParam());
        }
        break;
    case 147:
        if (checkCommandType(param)) {
            ret = cmd_is_party_top(param->getParam());
        }
        break;
    case 148:
        if (checkCommandType(param)) {
            ret = cmd_is_not_party_top(param->getParam());
        }
        break;
    case 160:
        if (checkCommandType(param)) {
            ret = cmd_disable_demolition();
        }
        break;
    case 175:
        if (checkCommandType(param)) {
            ret = cmdSetEventDoor(param->getParam());
        }
        break;
    case 173:
        if (checkCommandType(param)) {
            ret = cmdSearchMapObject(param->getParam());
        }
        break;
    case 155:
        if (checkCommandType(param)) {
            ret = cmd_set_encount_disable(param->getParam());
        }
        break;
    case 156:
        if (checkCommandType(param)) {
            ret = cmd_set_encount_stage_disable(param->getParam());
        }
        break;
    case 161:
        if (checkCommandType(param)) {
            ret = cmd_is_battle_turn(param->getParam());
        }
        break;
    case 171:
        if (checkCommandType(param)) {
            ret = cmdSetFloorMapObject(param->getParam());
        }
        break;
    case 425:
        if (checkCommandType(param)) {
            ret = cmd_check_smallmedal(param->getParam());
        }
        break;
    case 426:
        if (checkCommandType(param)) {
            ret = cmd_delete_furniture_item(param->getParam());
        }
        break;
    case 169:
        if (checkCommandType(param)) {
            ret = cmdFurnitureMoveRequest(param->getParam());
        }
        break;
    case 153:
        if (checkCommandType(param)) {
            ret = cmd_set_party_reserve_order(param->getParam());
        }
        break;
    case 154:
        if (checkCommandType(param)) {
            ret = cmd_party_copy_character(param->getParam());
        }
        break;
    case 174:
        if (checkCommandType(param)) {
            ret = cmdIsMapTreasure(param->getParam());
        }
        break;
    case 170:
        if (checkCommandType(param)) {
            ret = cmdSetFurniturePosition(param->getParam());
        }
        break;
    case 165:
        if (checkCommandType(param)) {
            ret = cmdFurnitureFadeout(param->getParam());
        }
        break;
    case 149:
        if (checkCommandType(param)) {
            ret = cmd_check_player_item(param->getParam());
        }
        break;
    case 183:
        if (checkCommandType(param)) {
            ret = cmd_floor_change(param->getParam());
        }
        break;
    case 184:
        if (checkCommandType(param)) {
            ret = cmd_floor_exit(param->getParam());
        }
        break;
    case 204:
        if (checkCommandType(param)) {
            ret = cmd_map_change_timezone(param->getParam());
        }
        break;
    case 203:
        if (checkCommandType(param)) {
            ret = cmd_map_effect_sepia();
        }
        break;
    case 329:
        if (checkCommandType(param)) {
            ret = cmdSetReturnChurch(param->getParam());
        }
        break;
    case 406:
        if (checkCommandType(param)) {
            ret = cmdSetOverviewPosition(param->getParam());
        }
        break;
    case 407:
        if (checkCommandType(param)) {
            ret = cmdSetOverviewChurchPosition(param->getParam());
        }
        break;
    case 208:
        if (checkCommandType(param)) {
            ret = cmd_set_se(param->getParam());
        }
        break;
    case 209:
        if (checkCommandType(param)) {
            ret = cmd_cut_se(param->getParam());
        }
        break;
    case 411:
        if (checkCommandType(param)) {
            ret = cmdSetSe2(param->getParam());
        }
        break;
    case 412:
        if (checkCommandType(param)) {
            ret = cmdCutSe2(param->getParam());
        }
        break;
    case 185:
        if (checkCommandType(param)) {
            ret = cmd_set_map_link_on_off(param->getParam());
        }
        break;
    case 186:
        if (checkCommandType(param)) {
            ret = cmd_change_map_link(param->getParam());
        }
        break;
    case 207:
        if (checkCommandType(param)) {
            ret = cmdSetMapTexture(param->getParam());
        }
        break;
    case 187:
        if (checkCommandType(param)) {
            ret = cmd_set_town_to_field_link(param->getParam());
        }
        break;
    case 188:
        if (checkCommandType(param)) {
            ret = cmn_set_field_to_town_link(param->getParam());
        }
        break;
    case 189:
        if (checkCommandType(param)) {
            ret = cmd_map_link_field_direct(param->getParam());
        }
        break;
    case 191:
        if (checkCommandType(param)) {
            ret = cmd_field_symbol_disp(param->getParam());
        }
        break;
    case 382:
        if (checkCommandType(param)) {
            ret = cmd_floor_change_ending(param->getParam());
        }
        break;
    case 205:
        if (checkCommandType(param)) {
            ret = cmdMapTexture(param->getParam());
        }
        break;
    case 190:
        if (checkCommandType(param)) {
            ret = cmd_field_erase_symbol(param->getParam());
        }
        break;
    case 217:
        if (checkCommandType(param)) {
            ret = cmdIsTrigger(param->getParam());
        }
        break;
    case 216:
        if (checkCommandType(param)) {
            ret = cmd_is_doorway(param->getParam());
        }
        break;
    case 222:
        if (checkCommandType(param)) {
            ret = cmd_is_party_all(param->getParam());
        }
        break;
    case 223:
        if (checkCommandType(param)) {
            ret = cmd_is_not_party_all(param->getParam());
        }
        break;
    case 181:
        if (checkCommandType(param)) {
            ret = cmd_is_open_door(param->getParam());
        }
        break;
    case 180:
        if (checkCommandType(param)) {
            ret = cmd_set_door_close(param->getParam());
        }
        break;
    case 182:
        if (checkCommandType(param)) {
            ret = cmd_map_animation(param->getParam());
        }
        break;
    case 197:
        if (checkCommandType(param)) {
            ret = cmd_map_shake(param->getParam());
        }
        break;
    case 196:
        if (checkCommandType(param)) {
            ret = cmd_effect_blur(param->getParam());
        }
        break;
    case 193:
        if (checkCommandType(param)) {
            ret = cmdEffectTransfer(param->getParam());
        }
        break;
    case 358:
        if (checkCommandType(param)) {
            ret = cmdEffectModel(param->getParam());
        }
        break;
    case 210:
        if (checkCommandType(param)) {
            ret = cmd_set_music(param->getParam());
        }
        break;
    case 214:
        ret = gPlayMusic.exec(param);
        break;
    case 211:
        if (checkCommandType(param)) {
            ret = cmd_music_pause(param->getParam());
        }
        break;
    case 215:
        if (checkCommandType(param)) {
            ret = cmd_play_music_now_map(param->getParam());
        }
        break;
    case 213:
        if (checkCommandType(param)) {
            ret = cmd_not_play_normal_sound(param->getParam());
        }
        break;
    case 131:
        if (checkCommandType(param)) {
            ret = cmd_set_ship_pos(param->getParam());
        }
        break;
    case 252:
        if (checkCommandType(param)) {
            ret = cmd_check_player_hp_mp(param->getParam());
        }
        break;
    case 256:
        if (checkCommandType(param)) {
            ret = cmd_set_player_hp_mp(param->getParam());
        }
        break;
    case 261:
        if (checkCommandType(param)) {
            ret = cmd_check_inn_count(param->getParam());
        }
        break;
    case 259:
        if (checkCommandType(param)) {
            ret = cmd_set_lura_message(param->getParam());
        }
        break;
    case 258:
        if (checkCommandType(param)) {
            ret = cmd_set_player_magic(param->getParam());
        }
        break;
    case 260:
        if (checkCommandType(param)) {
            ret = cmd_set_player_equip(param->getParam());
        }
        break;
    case 282:
        if (checkCommandType(param)) {
            ret = cmd_check_event_item(param->getParam());
        }
        break;
    case 359:
        if (checkCommandType(param)) {
            ret = cmd_check_event_item2(param->getParam());
        }
        break;
    case 283:
        if (checkCommandType(param)) {
            ret = cmd_check_event_magic(param->getParam());
        }
        break;
    case 288:
        if (checkCommandType(param)) {
            ret = cmd_set_macro_x_times_can_cast();
        }
        break;
    case 284:
        if (checkCommandType(param)) {
            ret = cmd_set_particle_draw(param->getParam());
        }
        break;
    case 285:
        if (checkCommandType(param)) {
            ret = cmd_set_particle_max(param->getParam());
        }
        break;
    case 286:
        if (checkCommandType(param)) {
            ret = cmd_reset_ninepuzzle(param->getParam());
        }
        break;
    case 290:
        if (checkCommandType(param)) {
            ret = cmd_set_ninepuzzle(param->getParam());
        }
        break;
    case 325:
        if (checkCommandType(param)) {
            ret = cmd_set_furniture_gaze(param->getParam());
        }
        break;
    case 121:
        ret = gCmd_ikada_move2_player_get_on.exec(param);
        break;
    case 120:
        ret = gCmd_ikada_move_player_get_on.exec(param);
        break;
    case 267:
        if (checkCommandType(param)) {
            ret = cmdCameraActionSet(param->getParam());
        }
        break;
    case 344:
        if (checkCommandType(param)) {
            ret = cmdSetRockRelocation(param->getParam());
        }
        break;
    case 345:
        if (checkCommandType(param)) {
            ret = cmdSetRockSave(param->getParam());
        }
        break;
    case 356:
        if (checkCommandType(param)) {
            ret = cmdFurnitureCollMove(param->getParam());
        }
        break;
    case 380:
        if (checkCommandType(param)) {
            ret = cmdSetShadowOnly(param->getParam());
        }
        break;
    case 7:
        ret = gCmdMessage.exec(param);
        break;
    case 8:
        ret = gCmdMessage2.exec(param);
        break;
    case 9:
        ret = gCmdSpeakToPlayer.exec(param);
        break;
    case 10:
        ret = gCmdSpeakToPlayer2.exec(param);
        break;
    case 16:
        ret = g_CharacterWait.exec(param);
        break;
    case 14:
        ret = g_CharacterMoveTo.exec(param);
        break;
    case 15:
        ret = g_CharacterMove2To.exec(param);
        break;
    case 29:
        ret = g_PlayerMoveTo.exec(param);
        break;
    case 30:
        ret = g_PlayerMove2To.exec(param);
        break;
    case 39:
        ret = gPlayerRot.exec(param);
        break;
    case 41:
        ret = g_CharacterTremble.exec(param);
        break;
    case 42:
        ret = gCharacterActionMiniJump.exec(param);
        break;
    case 43:
        ret = g_CharacterActionGaze.exec(param);
        break;
    case 45:
        ret = gFadeinCharacter.exec(param);
        break;
    case 46:
        ret = gFadeoutCharacter.exec(param);
        break;
    case 51:
        ret = gPlayerEffectMark.exec(param);
        break;
    case 72:
        ret = gRiseup_move.exec(param);
        break;
    case 89:
        ret = g_CharacterRiseup.exec(param);
        break;
    case 90:
        ret = gCharaRot.exec(param);
        break;
    case 91:
        ret = g_CharacterActionTurn.exec(param);
        break;
    case 101:
        ret = gCharacterActionNormalJump.exec(param);
        break;
    case 96:
        ret = gCmd_chara_move_line_to_player.exec(param);
        break;
    case 95:
        ret = g_CharacterMove2ToPlayer.exec(param);
        break;
    case 92:
        ret = g_CharacterMoveToParty.exec(param);
        break;
    case 93:
        ret = g_CharacterMove2ToParty.exec(param);
        break;
    case 94:
        ret = g_CharacterMoveToPlayer.exec(param);
        break;
    case 333:
        ret = g_CharacterHueChange.exec(param);
        break;
    case 192:
        ret = g_LocationEffect.exec(param);
        break;
    case 194:
        ret = g_LocationEffectMove.exec(param);
        break;
    case 195:
        ret = g_LocationEffectFade.exec(param);
        break;
    case 109:
        ret = gCmd_character_rgb_anim2.exec(param);
        break;
    case 111:
        ret = gCharcter_3d_motion.exec(param);
        break;
    case 107:
        ret = gCmd_set_camera_target_chara_frame.exec(param);
        break;
    case 128:
        ret = g_PlayerWait.exec(param);
        break;
    case 118:
        ret = g_PlayerMoveJump.exec(param);
        break;
    case 119:
        ret = g_PlayerMove2Jump.exec(param);
        break;
    case 116:
        ret = gCmd_player_line_move.exec(param);
        break;
    case 117:
        ret = gCmd_player_line_move2.exec(param);
        break;
    case 164:
        ret = g_MapAnimationB.exec(param);
        break;
    case 167:
        ret = g_FurnitureMove.exec(param);
        break;
    case 168:
        ret = g_FurnitureMove2.exec(param);
        break;
    case 287:
        ret = g_FurnitureRotate.exec(param);
        break;
    case 302:
        ret = g_FurnitureGroupMove.exec(param);
        break;
    case 303:
        ret = g_FurnitureGroupRotate.exec(param);
        break;
    case 172:
        ret = g_CofferProcess.exec(param);
        break;
    case 151:
        ret = g_PartyOrder.exec(param);
        break;
    case 152:
        ret = g_PartyMoveOverlap.exec(param);
        break;
    case 150:
        ret = g_PartyMove2Formation.exec(param);
        break;
    case 176:
        ret = g_MenuShop.exec(param);
        break;
    case 177:
        ret = g_MenuYesNo.exec(param);
        break;
    case 178:
        ret = gMenu_save.exec(param);
        break;
    case 218:
        ret = gCmdMessageWaitClosing.exec(param);
        break;
    case 219:
        ret = gCmdMessage2WaitClosing.exec(param);
        break;
    case 220:
        ret = gCmdSpeakToPlayerWaitClosing.exec(param);
        break;
    case 221:
        ret = gCmdSpeakToPlayer2WaitClosing.exec(param);
        break;
    case 249:
        ret = g_GameWait.exec(param);
        break;
    case 251:
        ret = g_BgmFade.exec(param);
        break;
    case 224:
        if (checkCommandType(param)) {
            ret = cmd_is_trigger_common(param->getParam());
        }
        break;
    case 227:
        if (checkCommandType(param)) {
            ret = cmd_is_trigger_character(param->getParam());
        }
        break;
    case 228:
        if (checkCommandType(param)) {
            ret = cmd_is_trigger2_character(param->getParam());
        }
        break;
    case 225:
        if (checkCommandType(param)) {
            ret = cmdIsTrigger2(param->getParam());
        }
        break;
    case 233:
        if (checkCommandType(param)) {
            ret = cmn_camera_lock_pov(param->getParam());
        }
        break;
    case 243:
        if (checkCommandType(param)) {
            ret = cmd_set_camera_limit(param->getParam());
        }
        break;
    case 240:
        if (checkCommandType(param)) {
            ret = cmd_camera_clip_distance(param->getParam());
        }
        break;
    case 236:
        if (checkCommandType(param)) {
            ret = cmd_camera_lock_target_player(param->getParam());
        }
        break;
    case 241:
        if (checkCommandType(param)) {
            ret = cmd_camera_near(param->getParam());
        }
        break;
    case 226:
        if (checkCommandType(param)) {
            ret = cmd_is_trigger3(param->getParam());
        }
        break;
    case 242:
        if (checkCommandType(param)) {
            ret = cmd_map_camera_default_angle(param->getParam());
        }
        break;
    case 244:
        ret = g_FadeIn.exec(param);
        break;
    case 245:
        ret = g_FadeOut.exec(param);
        break;
    case 246:
        ret = g_FadeIn2.exec(param);
        break;
    case 247:
        ret = g_FadeOut2.exec(param);
        break;
    case 330:
        ret = g_SpotLightON.exec(param);
        break;
    case 331:
        ret = g_SpotLightOFF.exec(param);
        break;
    case 229:
        ret = gMapCameraPosition.exec(param);
        break;
    case 234:
        ret = gMapCameraPositionAbs.exec(param);
        break;
    case 230:
        ret = gMapCameraAngle.exec(param);
        break;
    case 231:
        ret = gMapCameraGaze.exec(param);
        break;
    case 239:
        ret = gMapEventCamera.exec(param);
        break;
    case 232:
        ret = gCameraChangeDistance.exec(param);
        break;
    case 237:
        ret = gCameraResetDistance.exec(param);
        break;
    case 212:
        ret = gMusic_volume.exec(param);
        break;
    case 248:
        ret = gCameraMovePov.exec(param);
        break;
    case 235:
        ret = gCameraMoveToPlayer.exec(param);
        break;
    case 238:
        ret = gCmd_set_camera_angle_abs.exec(param);
        break;
    case 323:
        if (checkCommandType(param)) {
            ret = cmdChangePlayerDraw(param->getParam());
        }
        break;
    case 274:
        if (checkCommandType(param)) {
            ret = cmd_field_player_set_ship(param->getParam());
        }
        break;
    case 277:
        if (checkCommandType(param)) {
            ret = cmd_set_field_player_pos(param->getParam());
        }
        break;
    case 269:
        if (checkCommandType(param)) {
            ret = cmd_random_message(param->getParam());
        }
        break;
    case 275:
        ret = gFieldGetDownShip.exec(param);
        break;
    case 299:
        ret = gFieldSymbolAnim.exec(param);
        break;
    case 388:
        ret = gFieldGoldOrbEvent.exec(param);
        break;
    case 268:
        ret = gSpeak_to_player_self_closing.exec(param);
        break;
    case 271:
        ret = g_MessageWithSound.exec(param);
        break;
    case 279:
        ret = gFieldMoveLine.exec(param);
        break;
    case 278:
        ret = gFieldPlayerMoveTo.exec(param);
        break;
    case 270:
        if (checkCommandType(param)) {
            ret = cmd_set_message_sound(param->getParam());
        }
        break;
    case 280:
        if (checkCommandType(param)) {
            ret = cmd_set_ikada_info(param->getParam());
        }
        break;
    case 272:
        ret = gCmd_chara_line_move.exec(param);
        break;
    case 273:
        ret = gCmd_chara_line_move2.exec(param);
        break;
    case 281:
        ret = gMessage1SelfClosing.exec(param);
        break;
    case 289:
        if (checkCommandType(param)) {
            ret = Cmd_sugoroku_end_type(param->getParam());
        }
        break;
    case 291:
        if (checkCommandType(param)) {
            ret = cmd_party_add_npc(param->getParam());
        }
        break;
    case 292:
        if (checkCommandType(param)) {
            ret = cmd_party_del_npc(param->getParam());
        }
        break;
    case 293:
        ret = gEventInn.exec(param);
        break;
    case 294:
        if (checkCommandType(param)) {
            ret = cmd_is_party_item(param->getParam());
        }
        break;
    case 295:
        if (checkCommandType(param)) {
            ret = cmd_is_not_party_item(param->getParam());
        }
        break;
    case 296:
        if (checkCommandType(param)) {
            ret = cmd_is_party_head_count(param->getParam());
        }
        break;
    case 297:
        if (checkCommandType(param)) {
            ret = cmd_is_not_party_head_count(param->getParam());
        }
        break;
    case 298:
        ret = g_SugorokuTime.exec(param);
        break;
    case 179:
        ret = gCmd_door_action.exec(param);
        break;
    case 253:
        if (checkCommandType(param)) {
            ret = cmdBookingPantherName(param->getParam());
        }
        break;
    case 254:
        if (checkCommandType(param)) {
            ret = cmdSetPantherName(param->getParam());
        }
        break;
    case 198:
        ret = g_MapFlash.exec(param);
        break;
    case 301:
        if (checkCommandType(param)) {
            ret = cmd_field_trriger(param->getParam());
        }
        break;
    case 300:
        if (checkCommandType(param)) {
            ret = cmd_set_sugoroku_treasure(param->getParam());
        }
        break;
    case 306:
        if (checkCommandType(param)) {
            ret = cmdSetSugorokuEnd(param->getParam());
        }
        break;
    case 264:
        if (checkCommandType(param)) {
            ret = cmdCheckAllPlayerCount(param->getParam());
        }
        break;
    case 257:
        if (checkCommandType(param)) {
            ret = cmdSetPartyQuitToAzuke(param->getParam());
        }
        break;
    case 307:
        if (checkCommandType(param)) {
            ret = cmdIsPlayerItem(param->getParam());
        }
        break;
    case 308:
        if (checkCommandType(param)) {
            ret = cmdIsNotPlayerItem(param->getParam());
        }
        break;
    case 310:
        ret = g_PlayerActionGetOnOff.exec(param);
        break;
    case 311:
        if (checkCommandType(param)) {
            ret = cmdSetShopList(param->getParam());
        }
        break;
    case 312:
        if (checkCommandType(param)) {
            ret = cmdSetPlayerTownVehicle(param->getParam());
        }
        break;
    case 262:
        if (checkCommandType(param)) {
            ret = cmdSetPlayerParam(param->getParam());
        }
        break;
    case 309:
        if (checkCommandType(param)) {
            ret = cmdSetSackItem(param->getParam());
        }
        break;
    case 266:
        if (checkCommandType(param)) {
            ret = cmdSetPlayerCondition(param->getParam());
        }
        break;
    case 199:
        ret = g_MapBlendColor.exec(param);
        break;
    case 200:
        ret = g_MapBlendColorInit.exec(param);
        break;
    case 201:
        ret = gMapBackGroundColor.exec(param);
        break;
    case 202:
        ret = gMapBackGroundColorInit.exec(param);
        break;
    case 313:
        ret = g_GlobalMapOpen.exec(param);
        break;
    case 314:
        ret = g_GlobalMapClose.exec(param);
        break;
    case 315:
        if (checkCommandType(param)) {
            ret = cmdSetGlobalMapPosition(param->getParam());
        }
        break;
    case 263:
        ret = g_NameSetMenu.exec(param);
        break;
    case 304:
        if (checkCommandType(param)) {
            ret = cmdCheckJisanMax(param->getParam());
        }
        break;
    case 305:
        if (checkCommandType(param)) {
            ret = cmdIsPutinMonsterJisan(param->getParam());
        }
        break;
    case 324:
        if (checkCommandType(param)) {
            ret = cmdCheckSpaceItemChara(param->getParam());
        }
        break;
    case 332:
        if (checkCommandType(param)) {
            ret = cmdSetPartyKeep(param->getParam());
        }
        break;
    case 328:
        if (checkCommandType(param)) {
            ret = cmdSetSurfaceOnOff(param->getParam());
        }
        break;
    case 326:
        if (checkCommandType(param)) {
            ret = cmdTruckSwitch(param->getParam());
        }
        break;
    case 327:
        if (checkCommandType(param)) {
            ret = cmdSetTruckSwitch(param->getParam());
        }
        break;
    case 335:
        if (checkCommandType(param)) {
            ret = cmdSetMacroBaby(param->getParam());
        }
        break;
    case 336:
        if (checkCommandType(param)) {
            ret = cmdExecRuraLink(param->getParam());
        }
        break;
    case 255:
        if (checkCommandType(param)) {
            ret = cmdStoreRestorePlayerItem(param->getParam());
        }
        break;
    case 341:
        if (checkCommandType(param)) {
            ret = cmd_setup_gimmick_move(param->getParam());
        }
        break;
    case 342:
        if (checkCommandType(param)) {
            ret = cmd_set_scope(param->getParam());
        }
        break;
    case 347:
        ret = gSurechigaiRoot.exec(param);
        break;
    case 348:
        ret = gMakeTaishi.exec(param);
        break;
    case 349:
        ret = gSurechigaiTaishiMessage.exec(param);
        break;
    case 355:
        ret = gShakeMessage.exec(param);
        break;
    case 353:
        ret = gSetMeisanhinItem.exec(param);
        break;
    case 338:
        if (checkCommandType(param)) {
            ret = cmdCheckHitMapUid(param->getParam());
        }
        break;
    case 352:
        if (checkCommandType(param)) {
            ret = cmdSearchMapObj2(param->getParam());
        }
        break;
    case 357:
        if (checkCommandType(param)) {
            ret = cmdPlayerItemIntoFukuro(param->getParam());
        }
        break;
    case 360:
        if (checkCommandType(param)) {
            ret = cmdCheckSurface(param->getParam());
        }
        break;
    case 362:
        if (checkCommandType(param)) {
            ret = cmdCheckMuseumLevel(param->getParam());
        }
        break;
    case 363:
        if (checkCommandType(param)) {
            ret = cmdCheckMeisanCount(param->getParam());
        }
        break;
    case 364:
        if (checkCommandType(param)) {
            ret = cmdCheckSpecialMuseum(param->getParam());
        }
        break;
    case 365:
        if (checkCommandType(param)) {
            ret = cmdCheckMeisanhin(param->getParam());
        }
        break;
    case 366:
        if (checkCommandType(param)) {
            ret = cmdCheckPenaltyPoint(param->getParam());
        }
        break;
    case 367:
        if (checkCommandType(param)) {
            ret = cmdStartSurechigaiParty(param->getParam());
        }
        break;
    case 368:
        ret = gSurechigaiTaishiInfo.exec(param);
        break;
    case 369:
        if (checkCommandType(param)) {
            ret = cmdRedrawSurechigaiTaishi(param->getParam());
        }
        break;
    case 370:
        if (checkCommandType(param)) {
            ret = cmdIsCompleteMeisanhin(param->getParam());
        }
        break;
    case 350:
        if (checkCommandType(param)) {
            ret = cmdCheckMeisanhinCount(param->getParam());
        }
        break;
    case 371:
        if (checkCommandType(param)) {
            ret = cmdCheckLevel3Meisanhin(param->getParam());
        }
        break;
    case 372:
        if (checkCommandType(param)) {
            ret = cmdCheckUseEventItem(param->getParam());
        }
        break;
    case 373:
        ret = gDelayMessage.exec(param);
        break;
    case 374:
        ret = g_FriendMonsterAzuke.exec(param);
        break;
    case 375:
        if (checkCommandType(param)) {
            ret = cmdSetMacroSpecialty(param->getParam());
        }
        break;
    case 376:
        if (checkCommandType(param)) {
            ret = cmdSetCharaPosToMapObj(param->getParam());
        }
        break;
    case 377:
        if (checkCommandType(param)) {
            ret = cmdSetTruck_Start(param->getParam());
        }
        break;
    case 378:
        if (checkCommandType(param)) {
            ret = cmdCheckTruck_End(param->getParam());
        }
        break;
    case 381:
        if (checkCommandType(param)) {
            ret = cmdSetPlayerAzuke(param->getParam());
        }
        break;
    case 383:
        if (checkCommandType(param)) {
            ret = cmdCoercionSort(param->getParam());
        }
        break;
    case 384:
        if (checkCommandType(param)) {
            ret = cmdSetCoercionSortEnable(param->getParam());
        }
        break;
    case 385:
        if (checkCommandType(param)) {
            ret = cmdSetCollPlayerToChara(param->getParam());
        }
        break;
    case 386:
        if (checkCommandType(param)) {
            ret = cmd_set_sound_in_setup(param->getParam());
        }
        break;
    case 387:
        if (checkCommandType(param)) {
            ret = cmdSetTruckWagon(param->getParam());
        }
        break;
    case 394:
        if (checkCommandType(param)) {
            ret = cmd_set_lura_message2(param->getParam());
        }
        break;
    case 389:
        if (checkCommandType(param)) {
            ret = cmdSaveClearMonsterParty(param->getParam());
        }
        break;
    case 390:
        if (checkCommandType(param)) {
            ret = cmdCheckSaveMonster(param->getParam());
        }
        break;
    case 391:
        if (checkCommandType(param)) {
            ret = cmdCopySaveMonster(param->getParam());
        }
        break;
    case 392:
        ret = gCmdFriendMonsterMessage.exec(param);
        break;
    case 393:
        if (checkCommandType(param)) {
            ret = cmdSetMacroPMName(param->getParam());
        }
        break;
    case 250:
        if (checkCommandType(param)) {
            ret = cmdIsPlayerName(param->getParam());
        }
        break;
    case 401:
        if (checkCommandType(param)) {
            ret = cmdLevelUpLocket(param->getParam());
        }
        break;
    case 398:
        if (checkCommandType(param)) {
            ret = cmdSetPlayerPosAtMapObj(param->getParam());
        }
        break;
    case 399:
        ret = g_PartyJumpByPlayerNo.exec(param);
        break;
    case 400:
        if (checkCommandType(param)) {
            ret = cmdSetPartyDirectionByPlayerNo(param->getParam());
        }
        break;
    case 404:
        if (checkCommandType(param)) {
            ret = cmdResetPartyDirectionByPlayerNo(param->getParam());
        }
        break;
    case 408:
        if (checkCommandType(param)) {
            ret = cmdSetIkadaArea(param->getParam());
        }
        break;
    case 409:
        if (checkCommandType(param)) {
            ret = cmdDelTruckWagon(param->getParam());
        }
        break;
    case 433:
        if (checkCommandType(param)) {
            ret = cmdDelScriptMapObject(param->getParam());
        }
        break;
    case 405:
        if (checkCommandType(param)) {
            ret = cmdSetShipInfo(param->getParam());
        }
        break;
    case 413:
        if (checkCommandType(param)) {
            ret = cmdSetMacroSecond(param->getParam());
        }
        break;
    case 414:
        if (checkCommandType(param)) {
            ret = cmdSetMacroTargetForPosition(param->getParam());
        }
        break;
    case 415:
        ret = g_NarrationMessage.exec(param);
        break;
    case 416:
        ret = g_NarrationMessage2.exec(param);
        break;
    case 417:
        if (checkCommandType(param)) {
            ret = cmdSetMacroTargetForIndex(param->getParam());
        }
        break;
    case 418:
        if (checkCommandType(param)) {
            ret = cmd_set_chara_synchro(param->getParam());
        }
        break;
    case 430:
        if (checkCommandType(param)) {
            ret = cmd_set_chara_mortion_lock(param->getParam());
        }
        break;
    case 440:
        if (checkCommandType(param)) {
            ret = cmd_set_chara_coll(param->getParam());
        }
        break;
    case 420:
        if (checkCommandType(param)) {
            ret = cmdSetMacroMName(param->getParam());
        }
        break;
    case 421:
        if (checkCommandType(param)) {
            ret = cmdChengeShopChater(param->getParam());
        }
        break;
    case 422:
        if (checkCommandType(param)) {
            ret = cmdResetReorderFlag(param->getParam());
        }
        break;
    case 423:
        if (checkCommandType(param)) {
            ret = cmdSetBasicMenu(param->getParam());
        }
        break;
    case 429:
        if (checkCommandType(param)) {
            ret = cmdCheckPlayerHpMp(param->getParam());
        }
        break;
    case 419:
        if (checkCommandType(param)) {
            ret = cmdSetMagicMove(param->getParam());
        }
        break;
    case 439:
        if (checkCommandType(param)) {
            ret = cmdSetMagicMoveSetDisable(param->getParam());
        }
        break;
    case 431:
        if (checkCommandType(param)) {
            ret = cmdUpdateMuseumLevel(param->getParam());
        }
        break;
    case 424:
        ret = g_CmdRiseupPlayerEquip.exec(param);
        break;
    case 343:
        if (checkCommandType(param)) {
            ret = cmdSetHeadChara(param->getParam());
        }
        break;
    case 434:
        if (checkCommandType(param)) {
            ret = cmdSetMacroSpell(param->getParam());
        }
        break;
    case 436:
        if (checkCommandType(param)) {
            ret = cmdSetMacroTargetWithDeath(param->getParam());
        }
        break;
    case 437:
        if (checkCommandType(param)) {
            ret = cmdReturnInCarriage(param->getParam());
        }
        break;
    case 438:
        if (checkCommandType(param)) {
            ret = cmdSetFadeDisable(param->getParam());
        }
        break;
    case 441:
        if (checkCommandType(param)) {
            ret = cmdSortPartyKind(param->getParam());
        }
        break;
    case 443:
        if (checkCommandType(param)) {
            ret = cmd_field_set_formation(param->getParam());
        }
        break;
    case 444:
        if (checkCommandType(param)) {
            ret = cmdReorderFormerMember(param->getParam());
        }
        break;
    case 316:
        if (checkCommandType(param)) {
            ret = cmdGetBattleTransition(param->getParam());
        }
        break;
    case 318:
        if (checkCommandType(param)) {
            ret = cmdBattleSystemLock(param->getParam());
        }
        break;
    case 319:
        if (checkCommandType(param)) {
            ret = cmdBattlePartyAdd(param->getParam());
        }
        break;
    case 320:
        if (checkCommandType(param)) {
            ret = cmdBattlePartyReorder(param->getParam());
        }
        break;
    case 321:
        if (checkCommandType(param)) {
            ret = cmdBattleEnd(param->getParam());
        }
        break;
    case 322:
        if (checkCommandType(param)) {
            ret = cmdIsBattleUseItem(param->getParam());
        }
        break;
    case 317:
        ret = g_BattleMessage.exec(param);
        break;
    case 410:
        ret = g_BattleMessage2.exec(param);
        break;
    case 340:
        ret = g_BattleEffect.exec(param);
        break;
    case 339:
        ret = g_MapObjGimmickMove.exec(param);
        break;
    case 351:
        if (checkCommandType(param)) {
            ret = cmdSetBattleNpcMonsterIndex(param->getParam());
        }
        break;
    case 379:
        if (checkCommandType(param)) {
            ret = cmdSetBattleMonsterIndex(param->getParam());
        }
        break;
    case 427:
        if (checkCommandType(param)) {
            ret = cmdSetBattleMonsterAnimationIndex(param->getParam());
        }
        break;
    case 428:
        if (checkCommandType(param)) {
            ret = cmdSetBattleMonsterLoopAnimationIndex(param->getParam());
        }
        break;
    case 432:
        if (checkCommandType(param)) {
            ret = cmdSetDisableEscape(param->getParam());
        }
        break;
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 110:
    case 206:
    case 265:
    case 276:
    default:
        if (checkCommandType(param)) {
            ret = true;
        }
        break;
    }
    return ret;
}
