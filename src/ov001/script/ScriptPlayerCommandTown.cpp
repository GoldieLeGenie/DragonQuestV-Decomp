#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "ov001/script/ScriptPlayerCommandTown.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/global/Global.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/script/CommandParam.hpp"
#include "main/dss/UnkDssMath.hpp"

#pragma thumb on

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline twn::TOWN_PLAYER_ACTION_TYPE twn::TownPlayerManager::getActionType()
{
    return player_.actionType_;
}

inline void twn::TownPlayerManager::setWriggleCharacter(int flag)
{
    partyDraw_.setWriggleCharacter(flag);
}

inline void twn::TownPlayerManager::setAnimation(int flag)
{
    partyDraw_.setAnimation(flag);
}

inline void twn::TownPlayerManager::setAnimationOne(int flag)
{
    partyDraw_.setAnimationOne(flag);
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

inline status::HaveItem& status::HaveStatusInfo::getHaveItem()
{
    return haveItem_;
}

inline void status::StoryStatus::setHeroEquip(int index, short itemID)
{
    heroEquip_[index] = itemID;
}

inline short status::StoryStatus::getHeroEquip(int index)
{
    return heroEquip_[index];
}

inline void twn::TownPlayerManager::setSleep(int flag)
{
    partyDraw_.setSleep(flag);
}

inline int status::PartyStatus::isCarriage()
{
    return carriage_;
}

inline void twn::TownPlayerManager::setLockRot(int flag)
{
    rotLock_ = flag;
}

inline void twn::TownPlayerManager::setScriptColl(int scriptColl)
{
    scriptColl_ |= scriptColl;
}

inline void twn::TownPlayerManager::removeScriptColl(int scriptColl)
{
    scriptColl_ &= ~scriptColl;
}

inline bool twn::TownPlayerManager::isEndScriptRot()
{
    return scriptRotFlag_ == 0;
}

inline int twn::TownPlayerManager::isFormationEnd()
{
    return party_.isFormationEnd();
}

inline cmn::PartyMoveAction::PARTY_ACTION_STATE cmn::PartyMoveAction::getPartyState()
{
    return state_;
}

inline void twn::TownActionIkada::setScriptMove(int type)
{
    TownPlayerManager::getSingleton().player_.townActionIkada_.script_ = type;
}

inline int twn::TownActionIkada::getScriptMove()
{
    return TownPlayerManager::getSingleton().player_.townActionIkada_.script_;
}

inline void twn::TownActionIkada::setScriptTarget(dss::Fix32Vector3& pos)
{
    TownPlayerManager::getSingleton().player_.townActionIkada_.scriptTarget_ = pos;
}

inline void twn::TownPlayerManager::setScriptPlayer(int flag)
{
    scriptPlayer_ = flag;
}

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

inline void PlayerMoveTo::execute()
{
}

inline void PlayerMoveTo::terminate()
{
}

inline void PlayerMove2To::execute()
{
}

inline void PlayerMove2To::terminate()
{
}

inline void PlayerWait::terminate()
{
}

inline void PlayerRot::execute()
{
}

inline void PlayerRot::terminate()
{
}

inline void PlayerEffectMark::execute()
{
}

inline void PlayerMoveJump::execute()
{
}

inline void PlayerMoveJump::terminate()
{
}

inline void PlayerMove2Jump::execute()
{
}

inline void PlayerMove2Jump::terminate()
{
}

inline void PartyOrder::execute()
{
}

inline void PartyOrder::terminate()
{
}

inline void PartyMoveOverlap::execute()
{
}

inline void PartyMoveOverlap::terminate()
{
}

inline void PartyMove2Formation::terminate()
{
}

inline void PlayerActionGetOnOff::terminate()
{
}

inline void PartyJumpByPlayerNo::terminate()
{
}

bool cmdSetPlayerPosition(void* scriptParam)
{
    PARAM_SET_CHARACTER_POSITION* param = (PARAM_SET_CHARACTER_POSITION*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    twn::TownPlayerManager::getSingleton().setPosition(pos);
    twn::TownPlayerManager::getSingleton().setPartyToFirst(pos);
    if (twn::TownPlayerManager::getSingleton().getActionType() == twn::ACTION_TYPE_IKADA) {
        twn::TownPlayerManager::getSingleton().player_.townActionIkada_.setIkadaPosition(pos);
    }
    return true;
}

bool cmdSetPlayerDirection(void* scriptParam)
{
    PARAM_SET_PLAYER_DIRECTION* param = (PARAM_SET_PLAYER_DIRECTION*)scriptParam;
    twn::TownPlayerManager::getSingleton().setDirection(param->direction << 14);
    return true;
}

bool cmdPlayerActionStepping(void* scriptParam)
{
    twn::TownPlayerManager::getSingleton().setWriggleCharacter(0);
    twn::TownPlayerManager::getSingleton().setAnimation(1);
    return true;
}

bool cmdPlayerActionStill(void* scriptParam)
{
    twn::TownPlayerManager::getSingleton().setWriggleCharacter(0);
    twn::TownPlayerManager::getSingleton().setAnimation(0);
    return true;
}

bool cmdSetPartyKeep(void* scriptParam)
{
    PARAM_SET_PARTY_KEEP* param = (PARAM_SET_PARTY_KEEP*)scriptParam;
    cmn::g_cmnPartyInfo.setKeep(param->flag, g_Global.getMapNameId(), true);
    return true;
}

bool cmdStoreRestorePlayerItem(void* scriptParam)
{
    PARAM_STORE_RESTORE_PLAYER_ITEM* param = (PARAM_STORE_RESTORE_PLAYER_ITEM*)scriptParam;
    int active = status::g_Party.getSortIndex(1);
    status::HaveItem& item = status::g_Party.getPlayerStatus(active).getHaveStatusInfo().getHaveItem();
    if (param->flag == 0) {
        status::g_Story.setHeroEquip(0, item.getEquipmentItem(ITEM_WEAPON, 0));
        status::g_Story.setHeroEquip(1, item.getEquipmentItem(ITEM_ARMOR, 0));
        status::g_Story.setHeroEquip(2, item.getEquipmentItem(ITEM_SHIELD, 0));
        status::g_Story.setHeroEquip(3, item.getEquipmentItem(ITEM_HELMET, 0));
        status::g_Story.setHeroEquip(4, item.getEquipmentItem(ITEM_ACCESSORY, 0));
        status::g_Story.setHeroEquip(5, item.getEquipmentItem(ITEM_ACCESSORY, 1));
        status::g_Story.setHeroEquip(6, item.getEquipmentItem(ITEM_ACCESSORY, 2));
        status::g_Story.setHeroEquip(7, item.getEquipmentItem(ITEM_ACCESSORY, 3));
        status::g_Story.setHeroEquip(8, item.getEquipmentItem(ITEM_ACCESSORY, 4));
        int itemCount = item.getCount();
        for (int i = 0; i < itemCount; i++) {
            if (!item.isEquipment(i)) {
                status::g_Party.haveItemSack_.add(item.getItem(i));
            }
        }
        for (int i = 0; i < itemCount; i++) {
            status::g_Party.getPlayerStatus(active).getHaveStatusInfo().execThrow(0);
        }
    } else {
        for (int i = 0; i < 9; i++) {
            if (status::g_Story.getHeroEquip(i) != 0) {
                item.add(status::g_Story.getHeroEquip(i));
                item.setEquipment(item.getCount() - 1);
            }
        }
    }
    return true;
}

bool cmdPlayerActionWriggle(void* scriptParam)
{
    twn::TownPlayerManager::getSingleton().setAnimationOne(1);
    twn::TownPlayerManager::getSingleton().setWriggleCharacter(1);
    return true;
}

bool cmd_set_player_sleep(void* scriptParam)
{
    PARAM_SET_PLAYER_SLEEP* param = (PARAM_SET_PLAYER_SLEEP*)scriptParam;
    twn::TownPlayerManager::getSingleton().setSleep(param->flag);
    return true;
}

bool cmdCharacterPartyJoin(void* scriptParam)
{
    PARAM_PARTY_JOIN* param = (PARAM_PARTY_JOIN*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int ctrl = getPlacementCtrlId(param->objNo);
    int carriageOutCount = status::g_Party.getCarriageOutCount();
    int addIndex = param->index;
    int pos = param->pos - 1;
    if (addIndex > 16) {
        addIndex = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(addIndex);
        status::PlayerDataAll::setFriendMonsterFlag(addIndex, true);
    }
    status::g_Party.add(addIndex, true);
    if (pos != -1 && pos < carriageOutCount) {
        int count = 0;
        int playerPos[4] = {-1};
        for (int i = 0; i < 4; i++) {
            playerPos[i] = -1;
        }
        playerPos[pos] = carriageOutCount;
        for (int i = 0; i < carriageOutCount + 1; i++) {
            if (playerPos[i] != -1) {
                i++;
            }
            playerPos[i] = count;
            count++;
        }
        status::g_Party.reorder(playerPos[0], playerPos[1], playerPos[2], playerPos[3]);
    }
    cmn::GameManager::getSingleton().resetParty();
    cmn::PartyTalk::getSingleton().setAddPlayer(param->index);
    twn::TownPlayerManager::getSingleton().resetParty();
    TownCharacterManager::getSingleton()->setDisplay(ctrl, false);
    TownCharacterManager::getSingleton()->setCollFlag(ctrl, false);
    return true;
}

bool cmdCharacterPartyQuit(void* scriptParam)
{
    PARAM_PARTY_QUIT* param = (PARAM_PARTY_QUIT*)scriptParam;
    status::g_Party.setAllPlayerMode();
    int ctrl = getPlacementCtrlId(param->objNo);
    int delIndex;
    if (param->index > 16) {
        delIndex = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(param->index);
        status::PlayerDataAll::setFriendMonsterFlag(delIndex, false);
    } else {
        delIndex = status::g_Party.getSortIndex(param->index);
    }
    if (delIndex != -1) {
        int memberPos = delIndex;
        if (param->index == 8 || param->index == 15) {
            status::g_Party.setDisplayMode();
            memberPos = status::g_Party.getSortIndex(param->index);
        }
        if (status::g_StageAttribute.isCarriageEnter() && status::g_Party.isCarriage() && delIndex >= 1) {
            memberPos += 2;
        }
        dss::Fix32Vector3 pos(twn::TownPlayerManager::getSingleton().party_.getMemberPos(memberPos));
        TownCharacterManager::getSingleton()->setDisplay(ctrl, true);
        TownCharacterManager::getSingleton()->setCollFlag(ctrl, true);
        TownCharacterManager::getSingleton()->setPosition(ctrl, pos);
        status::g_Party.setAllPlayerMode();
        status::g_Party.del(delIndex);
        cmn::GameManager::getSingleton().resetParty();
    }
    return true;
}

bool cmd_player_action_not_change_direction(void* scriptParam)
{
    PARAM_PLAYER_ACTION_NOT_CHANGE_DIRECTION* param = (PARAM_PLAYER_ACTION_NOT_CHANGE_DIRECTION*)scriptParam;
    twn::TownPlayerManager::getSingleton().setLockRot(param->flag);
    return true;
}

bool cmd_player_set_coll(void* scriptParam)
{
    int flag = 0;
    PARAM_PLAYER_SET_COLL* param = (PARAM_PLAYER_SET_COLL*)scriptParam;
    if (param->floorFlag == 1) {
        flag |= 2;
    }
    if (param->wallFlag == 1) {
        flag |= 1;
    }
    twn::TownPlayerManager::getSingleton().setScriptColl(flag);
    return true;
}

bool cmd_set_party_mark(void* scriptParam)
{
    PARAM_SET_PARTY_MARK* param = (PARAM_SET_PARTY_MARK*)scriptParam;
    twn::TownPlayerManager::getSingleton().rizeupSetParty(param->player, param->mark);
    return true;
}

bool cmd_set_Van_and_Basha(void* scriptParam)
{
    twn::TownPlayerManager::getSingleton().setVanAndBasha();
    return true;
}

bool cmd_is_player_direction(void* scriptParam)
{
    PARAM_IS_PLAYER_DIRECTION* param = (PARAM_IS_PLAYER_DIRECTION*)scriptParam;
    short idx = twn::TownPlayerManager::getSingleton().getDirection();
    return cmn::CommonCalculate::directionCheckByScriptParam(param->direction, idx);
}

void PlayerMoveTo::initialize(char* scriptParam)
{
    PARAM_PLAYER_MOVE_TO* param = (PARAM_PLAYER_MOVE_TO*)scriptParam;
    dss::Fix32Vector3 endPos;
    dss::Fix32Vector3 playerPos(twn::TownPlayerManager::getSingleton().getPosition());
    dss::Fix32Vector3 startPos(playerPos);
    endPos.vx.value = param->endX;
    endPos.vy.value = param->endY;
    endPos.vz.value = param->endZ;
    if (param->absFlag == 1) {
        endPos += playerPos;
    }
    twn::TownPlayerManager::getSingleton().setSimpleMove(startPos, endPos, param->frame);
}

int PlayerMoveTo::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().isFinish()) {
        return true;
    }
    return false;
}

PlayerMoveTo g_PlayerMoveTo;

void PlayerMove2To::initialize(char* scriptParam)
{
    PARAM_PLAYER_MOVE2_TO* param = (PARAM_PLAYER_MOVE2_TO*)scriptParam;
    dss::Fix32Vector3 startPos, endPos;
    dss::Fix32Vector3 playerPos(twn::TownPlayerManager::getSingleton().getPosition());
    startPos = playerPos;
    endPos.vx.value = param->endX;
    endPos.vy.value = param->endY;
    endPos.vz.value = param->endZ;
    if (param->absFlag == 1) {
        endPos += playerPos;
    }
    dss::Fix32 rate;
    rate.value = param->rate;
    twn::TownPlayerManager::getSingleton().setSpeedMove(startPos, endPos, rate);
}

int PlayerMove2To::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().isFinish()) {
        return true;
    }
    return false;
}

PlayerMove2To g_PlayerMove2To;

void PlayerRot::initialize(char* scriptParam)
{
    PARAM_PLAYER_ROT* param = (PARAM_PLAYER_ROT*)scriptParam;
    dss::Fix32 idx;
    idx.value = param->idx;
    twn::TownPlayerManager::getSingleton().setScriptRot(param->frame, degreeToAngle(idx), param->rotFlag);
    endFlag_ = param->endFlag;
}

int PlayerRot::isEnd()
{
    if (endFlag_ == false) {
        if (twn::TownPlayerManager::getSingleton().isEndScriptRot()) {
            return true;
        }
        return false;
    }
    return true;
}

PlayerRot gPlayerRot;

void PlayerEffectMark::initialize(char* scriptParam)
{
    PARAM_PLAYER_EFFECT_MARK* param = (PARAM_PLAYER_EFFECT_MARK*)scriptParam;
    twn::TownPlayerManager::getSingleton().rizeupSet(param->mark);
}

int PlayerEffectMark::isEnd()
{
    return twn::TownPlayerManager::getSingleton().rizeupEnd();
}

PlayerEffectMark gPlayerEffectMark;

void PlayerMoveJump::initialize(char* scriptParam)
{
    PARAM_PLAYER_MOVE_JUMP* param = (PARAM_PLAYER_MOVE_JUMP*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.set(param->endX, param->endY, param->endZ);
    twn::TownPlayerManager::getSingleton().setJumpMove(pos, param->frame);
}

int PlayerMoveJump::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().isFinish()) {
        return true;
    }
    return false;
}

PlayerMoveJump g_PlayerMoveJump;

void PlayerMove2Jump::initialize(char* scriptParam)
{
    PARAM_PLAYER_MOVE2_JUMP* param = (PARAM_PLAYER_MOVE2_JUMP*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.set(param->endX, param->endY, param->endZ);
    dss::Fix32Vector3 start(twn::TownPlayerManager::getSingleton().getPosition());
    dss::Fix32 rate;
    rate.value = param->rate;
    dss::Fix32 speed(TownCharacterManager::defaultSpeed * rate);
    int frame = cmn::CommonCalculate::getFrameByVector(start, pos, speed);
    twn::TownPlayerManager::getSingleton().setJumpMove(pos, frame);
}

int PlayerMove2Jump::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().isFinish()) {
        return true;
    }
    return false;
}

PlayerMove2Jump g_PlayerMove2Jump;

void Cmd_player_line_move::initialize(char* scriptParam)
{
    PARAM_PLAYER_LINE_MOVE* param = (PARAM_PLAYER_LINE_MOVE*)scriptParam;
    dss::Fix32Vector3 start(twn::TownPlayerManager::getSingleton().getPosition());
    dss::Fix32Vector3 target = cmn::CommonCalculate::getAxisMoveTargetByParam(param->axis, param->absFlag, param->value, start);
    twn::TownPlayerManager::getSingleton().setSimpleMove(start, target, param->frame);
}

void Cmd_player_line_move::execute()
{
}

int Cmd_player_line_move::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().isFinish()) {
        return true;
    }
    return false;
}

Cmd_player_line_move gCmd_player_line_move;

void Cmd_player_line_move2::initialize(char* scriptParam)
{
    PARAM_PLAYER_LINE_MOVE2* param = (PARAM_PLAYER_LINE_MOVE2*)scriptParam;
    dss::Fix32Vector3 start(twn::TownPlayerManager::getSingleton().getPosition());
    dss::Fix32Vector3 target = cmn::CommonCalculate::getAxisMoveTargetByParam(param->axis, param->absFlag, param->value, start);
    dss::Fix32 speed;
    speed.value = param->rate;
    twn::TownPlayerManager::getSingleton().setSpeedMove(start, target, speed);
}

void Cmd_player_line_move2::execute()
{
}

int Cmd_player_line_move2::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().isFinish()) {
        return true;
    }
    return false;
}

Cmd_player_line_move2 gCmd_player_line_move2;

void PlayerWait::initialize(char* scriptParam)
{
    PARAM_PLAYER_WAIT* param = (PARAM_PLAYER_WAIT*)scriptParam;
    count_ = 0;
    countFrame_ = param->frame;
}

void PlayerWait::execute()
{
    count_++;
}

int PlayerWait::isEnd()
{
    if (count_ >= countFrame_) {
        return true;
    }
    return false;
}

PlayerWait g_PlayerWait;

void PartyOrder::initialize(char* scriptParam)
{
    PARAM_SET_PARTY_ORDER* param = (PARAM_SET_PARTY_ORDER*)scriptParam;
    status::g_Party.setBattleModeAndCarriage();
    int party[4] = {-1};
    for (int i = 0; i < 4; i++) {
        party[i] = -1;
    }
    int carriageOutCount = status::g_Party.getCarriageOutCount();
    party[0] = status::g_Party.getSortIndex(param->index);
    status::g_Party.setMemberShiftMode();
    int tmp = 1;
    for (int i = 0; i < carriageOutCount; i++) {
        if (i != party[0]) {
            party[tmp] = i;
            tmp++;
        }
    }
    change_ = false;
    if (party[0] != 0) {
        change_ = true;
    }
    if (change_) {
        status::g_Party.reorder(party[0], party[1], party[2], party[3]);
        cmn::GameManager::getSingleton().resetParty();
        twn::TownPlayerManager::getSingleton().setMoveToFirstFlag();
        twn::TownPlayerManager::getSingleton().party_.setMoveToFirstHalfSpeed(twn::SPEED_TYPE(1));
    }
}

int PartyOrder::isEnd()
{
    if (change_) {
        if (twn::TownPlayerManager::getSingleton().getMoveToFirstFlag() == false) {
            return true;
        }
        return false;
    }
    return true;
}

PartyOrder g_PartyOrder;

void PartyMoveOverlap::initialize(char* scriptParam)
{
    twn::TownPlayerManager::getSingleton().setMoveToFirstFlag();
}

int PartyMoveOverlap::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().getMoveToFirstFlag() == false) {
        return true;
    }
    return false;
}

PartyMoveOverlap g_PartyMoveOverlap;

void PartyMove2Formation::initialize(char* scriptParam)
{
    PARAM_PARTY_MOVE2_FORMATION* param = (PARAM_PARTY_MOVE2_FORMATION*)scriptParam;
    dss::Fix32 speed;
    speed.value = param->rate;
    speed *= TownCharacterManager::defaultSpeed;
    twn::TownPlayerManager::getSingleton().setFormation(param->frmDir, param->charaDir, speed);
}

void PartyMove2Formation::execute()
{
}

int PartyMove2Formation::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().isFormationEnd()) {
        return true;
    }
    return false;
}

PartyMove2Formation g_PartyMove2Formation;

void PlayerActionGetOnOff::initialize(char* scriptParam)
{
    PARAM_SET_PLAYER_GET_ON_OFF* param = (PARAM_SET_PLAYER_GET_ON_OFF*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    switch (param->type) {
    case 0:
        twn::TownActionIkada::setScriptMove(1);
        twn::TownPlayerManager::getSingleton().setScriptPlayer(true);
        break;
    case 1:
        twn::TownActionIkada::setScriptMove(2);
        twn::TownActionIkada::setScriptTarget(pos);
        twn::TownPlayerManager::getSingleton().setScriptPlayer(true);
        break;
    }
}

void PlayerActionGetOnOff::execute()
{
}

int PlayerActionGetOnOff::isEnd()
{
    if (twn::TownActionIkada::getScriptMove() == 0) {
        return true;
    }
    return false;
}

PlayerActionGetOnOff g_PlayerActionGetOnOff;

bool cmdSetCollPlayerToChara(void* scriptParam)
{
    PARAM_SET_COLL_PLAYER_TO_CHARA* param = (PARAM_SET_COLL_PLAYER_TO_CHARA*)scriptParam;
    if (param->flag == 1) {
        twn::TownPlayerManager::getSingleton().setScriptColl(4);
    } else {
        twn::TownPlayerManager::getSingleton().removeScriptColl(4);
    }
    return true;
}

bool cmdSetPlayerPosAtMapObj(void* scriptParam)
{
    PARAM_SET_PLAYERPOS_AT_MAPOBJ* param = (PARAM_SET_PLAYERPOS_AT_MAPOBJ*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->offsetX;
    pos.vy.value = param->offsetY;
    pos.vz.value = param->offsetZ;
    twn::TownPlayerManager::getSingleton().setMapObjMove(param->flag, param->uid, pos);
    return true;
}

void PartyJumpByPlayerNo::initialize(char* scriptParam)
{
    PARAM_PARTY_JUMP_BY_PLAYER_NO* param = (PARAM_PARTY_JUMP_BY_PLAYER_NO*)scriptParam;
    int index = status::g_Party.getSortIndex(param->playerNo);
    if (index != -1) {
        twn::TownPlayerManager::getSingleton().party_.setMemberJump(index);
    }
}

void PartyJumpByPlayerNo::execute()
{
}

int PartyJumpByPlayerNo::isEnd()
{
    if (twn::TownPlayerManager::getSingleton().party_.getPartyState() != cmn::PartyMoveAction::MOVE_TO_FORMATION) {
        return true;
    }
    return false;
}

PartyJumpByPlayerNo g_PartyJumpByPlayerNo;

void ScriptPlayerCommandTown_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
