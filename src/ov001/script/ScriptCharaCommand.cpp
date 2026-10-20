#pragma ipa file
#include "main/script/ScriptBaseCommand.hpp"

// The original TU also emitted ScriptCommand's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ScriptCommandWeakVtable : ScriptCommand {
    virtual void initialize(char* scriptParam);
    virtual int isEnd();
};

#include "ov001/script/ScriptCharaCommand.hpp"
#include "main/script/CommandParam.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/dss/UnkDssMath.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/status/StageInfo.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownExtraCollManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownSystem.hpp"

#pragma thumb on

inline ScriptCommand::ScriptCommand()
{
}

inline ScriptCommand::~ScriptCommand()
{
}

inline void ScriptCommandWeakVtable::initialize(char* scriptParam)
{
}

inline int ScriptCommandWeakVtable::isEnd()
{
    return 0;
}

inline twn::TownSystemScript& twn::TownSystem::getScriptSystem()
{
    return townSystemScript_;
}

inline int twn::TownSystemScript::isTriggerOk()
{
    return trigger_;
}

inline void twn::TownSystemScript::setTriggerFlag(bool flag)
{
    trigger_ = flag;
}

inline int status::StageInfo::getRockFlag(int index)
{
    return rockFlag_[index];
}

inline dss::Fix32Vector3& status::StageInfo::getRockLocation(int index)
{
    return rock_[index];
}

inline void status::StageInfo::setRockFlag(int index, bool flag)
{
    rockFlag_[index] = flag;
}

inline void twn::TownCharacterBase::setMoveType(SCRIPT_MOVE_TYPE type)
{
    moveType_ = type;
}

inline twn::SCRIPT_MOVE_TYPE twn::TownCharacterBase::getMoveType()
{
    return moveType_;
}

inline void twn::TownCharacterBase::setMoveData(SCRIPT_MOVE_DATA& data)
{
    moveData_ = data;
}

inline void twn::TownCharacterBase::setStageColl(char flag)
{
    stageColl_ = flag;
}

inline void TownCharacterManager::setScriptData(int index, twn::TOWN_SCRIPT_DATA& script)
{
    character_[index]->setScriptData(script);
}

inline int TownCharacterManager::isScriptEnd(int index)
{
    return character_[index]->isScriptEnd();
}

inline void TownCharacterManager::execWait(int index)
{
    character_[index]->execWait();
}

inline void TownCharacterManager::execRiseup(int index)
{
    character_[index]->execRiseup();
}

inline void TownCharacterManager::execTremble(int index)
{
    character_[index]->execTremble();
}

inline void TownCharacterManager::setFadeType(int index, int type, int frame)
{
    character_[index]->setFadeType(type, frame);
}

inline bool TownCharacterManager::isEndFade(int index)
{
    return character_[index]->isEndFade();
}

inline void TownCharacterManager::setScale(int index, dss::Fix32 scale)
{
    character_[index]->setScale(scale);
}

inline void TownCharacterManager::setChangePaletteRate(int index, unsigned char r, unsigned char g, unsigned char b, int rgbFrame)
{
    character_[index]->setChangePaletteRate(r, g, b, rgbFrame);
}

inline bool TownCharacterManager::isEndChangePalletRate(int index)
{
    return character_[index]->isEndPalletRate();
}

inline void TownCharacterManager::setMotion(int index, int motion, bool flag)
{
    character_[index]->setMotion(motion, flag);
}

inline bool TownCharacterManager::isMotion(int index)
{
    return character_[index]->isMotion();
}

inline void TownCharacterManager::setHueChange(int index, int type, int frame)
{
    character_[index]->setHueChange(type, frame);
}

inline bool TownCharacterManager::isHueChange(int index)
{
    return character_[index]->isHueChange();
}

inline void TownCharacterManager::setShadowOnly(int index, int flag)
{
    character_[index]->setShadowOnly(flag);
}

inline void TownCharacterManager::setEventLock(int index, bool flag)
{
    character_[index]->setPersonalEventLock(flag);
}

inline void TownCharacterManager::setSimpleMove(int index)
{
    character_[index]->setSimpleMove();
}

inline void TownCharacterManager::setSimpleRot(int index, short idx, int frame, int mode)
{
    character_[index]->setSimpleRot(idx, frame, mode);
}

inline void TownCharacterManager::setLockRot(int index, int lockRot)
{
    character_[index]->setLockRot(lockRot);
}

inline void TownCharacterManager::setMoveType(int index, twn::SCRIPT_MOVE_TYPE type, twn::SCRIPT_MOVE_DATA& moveData)
{
    character_[index]->setMoveType(type);
    character_[index]->setMoveData(moveData);
}

inline twn::SCRIPT_MOVE_TYPE TownCharacterManager::getMoveType(int index)
{
    return character_[index]->getMoveType();
}

inline void TownCharacterManager::setMoveToParty(int index)
{
    character_[index]->setMoveToParty();
}

inline void TownCharacterManager::setMoveRandom(int index)
{
    character_[index]->setMoveRandom();
}

inline void TownCharacterManager::setMovePassive(int index)
{
    character_[index]->setMovePassive();
}

inline void TownCharacterManager::setMoveReverse(int index)
{
    character_[index]->setMoveReverse();
}

inline bool TownCharacterManager::isRotEnd(int index)
{
    return character_[index]->isRotEnd();
}

inline void TownCharacterManager::setRotFrame(int index, int frame, short idx, int flag, int typeA)
{
    character_[index]->setRotFrame(frame, idx, flag, typeA);
}

inline bool TownCharacterManager::isRotFrameEnd(int index)
{
    return character_[index]->isRotFrameEnd();
}

inline void TownCharacterManager::setStageColl(int index, char flag)
{
    character_[index]->setStageColl(flag);
}

inline bool TownCharacterManager::getCounterTalk(int index)
{
    return character_[index]->getCounterTalk();
}

inline void TownCharacterManager::setMapUid(int index, int uid)
{
    character_[index]->setMapUid(uid);
}

inline void TownCharacterManager::setVoice(int ctrl, int voice)
{
    character_[ctrl]->setVoice(voice);
}

inline void TownCharacterManager::setSwingRound(int index, int flag)
{
    character_[index]->setSwingRound(flag);
}

inline void TownCharacterManager::setJumpMove(int index, dss::Fix32Vector3& target, int frame)
{
    character_[index]->setJumpMove(target, frame);
}

inline void TownCharacterManager::setSynchronous(int index, int flag, int no)
{
    character_[index]->setSynchronous(flag, no);
}

inline void TownCharacterManager::setMotionLock(int index, int flag)
{
    character_[index]->setMotionLock(flag);
}

inline void CharacterMoveTo::terminate()
{
}

inline void CharacterMove2To::terminate()
{
}

inline void CharacterWait::terminate()
{
}

inline void CharacterTremble::terminate()
{
}

inline void CharacterActionMiniJump::execute()
{
}

inline void CharacterActionMiniJump::terminate()
{
}

inline void CharacterActionGaze::execute()
{
}

inline void CharacterActionGaze::terminate()
{
}

inline void FadeinCharacter::execute()
{
}

inline void FadeinCharacter::terminate()
{
}

inline void FadeoutCharacter::execute()
{
}

inline void FadeoutCharacter::terminate()
{
}

inline void CharacterRiseup::terminate()
{
}

inline void CharaRot::execute()
{
}

inline void CharaRot::terminate()
{
}

inline void CharacterActionTurn::execute()
{
}

inline void CharacterActionTurn::terminate()
{
}

inline void CharacterActionNormalJump::execute()
{
}

inline void CharacterActionNormalJump::terminate()
{
}

inline void Cmd_chara_move_line_to_player::execute()
{
}

inline void CharacterMove2ToPlayer::terminate()
{
}

inline void CharacterMoveToParty::terminate()
{
}

inline void CharacterMove2ToParty::terminate()
{
}

inline void CharacterMoveToPlayer::terminate()
{
}

inline void Cmd_character_rgb_anim2::execute()
{
}

inline void Cmd_character_rgb_anim2::terminate()
{
}

inline void Charcter_3d_motion::execute()
{
}

inline void CharacterHueChange::execute()
{
}

inline void CharacterHueChange::terminate()
{
}

bool cmd_is_talked_at_shop(void* scriptParam)
{
    PARAM_IS_TALKED_AT_SHOP* param = (PARAM_IS_TALKED_AT_SHOP*)scriptParam;
    int ctrl = getPlacementCtrlId();
    if (param->flag == 1) {
        if (TownCharacterManager::getSingleton()->getCounterTalk(ctrl) == true) {
            if (TownCharacterManager::getSingleton()->isTalked(ctrl) == true) {
                return true;
            }
        }
    } else {
        if (TownCharacterManager::getSingleton()->getCounterTalk(ctrl) == false) {
            if (TownCharacterManager::getSingleton()->isTalked(ctrl) == true) {
                return true;
            }
        }
    }
    return false;
}

bool cmd_character_not_change_direction(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_CHARACTER_NOT_CHANGE_DIRECTION* param = (PARAM_CHARACTER_NOT_CHANGE_DIRECTION*)scriptParam;
    TownCharacterManager::getSingleton()->setLockRot(ctrl, param->flag);
    return true;
}

bool cmd_character_swing_round(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_CHARACTER_SWING_ROUND* param = (PARAM_CHARACTER_SWING_ROUND*)scriptParam;
    TownCharacterManager::getSingleton()->setSwingRound(ctrl, param->flag);
    return true;
}

bool cmdCharacterActionStepping(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setWriggleCharacter(ctrl, 0);
    TownCharacterManager::getSingleton()->setAnimation(ctrl, 1);
    return true;
}

bool cmdCharacterActionStill(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setWriggleCharacter(ctrl, 0);
    TownCharacterManager::getSingleton()->setAnimation(ctrl, 0);
    return true;
}

bool cmdCharacterActionWriggle(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setAnimation(ctrl, 1);
    TownCharacterManager::getSingleton()->setWriggleCharacter(ctrl, 1);
    return true;
}

bool cmdCharacterActionSleep(void* scriptParam)
{
    PARAM_CHARACTER_ACTION_SLEEP* param = (PARAM_CHARACTER_ACTION_SLEEP*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setSleepCharacter(ctrl, param->onoff);
    return true;
}

bool cmdCharacterMoveRoam(void* scriptParam)
{
    PARAM_CHARACTER_MOVE_ROAM* param = (PARAM_CHARACTER_MOVE_ROAM*)scriptParam;
    int ctrl = getPlacementCtrlId();
    twn::SCRIPT_MOVE_DATA data;
    data.counter = UnkDssRand::rand(0x50);
    data.frame = 0;
    data.vector[0].vx.value = param->startX;
    data.vector[0].vy.value = 0;
    data.vector[0].vz.value = param->startZ;
    data.vector[1].vx.value = param->endX;
    data.vector[1].vy.value = 0;
    data.vector[1].vz.value = param->endZ;
    data.speed.value = param->rate;
    data.speed *= TownCharacterManager::defaultSpeed;
    TownCharacterManager::getSingleton()->setMoveType(ctrl, twn::MOVE_TYPE_AREA, data);
    return true;
}

bool cmdSetCharacterPosition(void* scriptParam)
{
    PARAM_SET_CHARACTER_POSITION* param = (PARAM_SET_CHARACTER_POSITION*)scriptParam;
    int ctrl = getPlacementCtrlId();
    dss::Fix32Vector3 pos;
    pos.vx.value = param->posX;
    pos.vy.value = param->posY;
    pos.vz.value = param->posZ;
    TownCharacterManager::getSingleton()->setPosition(ctrl, pos);
    return true;
}

bool cmdSetCharacterDirection(void* scriptParam)
{
    PARAM_SET_CHARACTER_DIRECTION* param = (PARAM_SET_CHARACTER_DIRECTION*)scriptParam;
    int ctrl = getPlacementCtrlId();
    short direction;
    switch (param->direction) {
        case 0:
        case 1:
        case 2:
        case 3:
            direction = param->direction << 14;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            direction = ((param->direction - 4) << 14) + 0x2000;
            break;
    }
    TownCharacterManager::getSingleton()->setRotate(ctrl, direction);
    return true;
}

bool Cmd_chara_start_action(void* scriptParam)
{
    PARAM_CHARA_START_ACTION* param = (PARAM_CHARA_START_ACTION*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setEventLock(ctrl, false);
    if (param->flag == 1) {
        TownCharacterManager::getSingleton()->setAnimation(ctrl, 1);
    }
    return true;
}

bool cmdCharacterActionNear(void* scriptParam)
{
    PARAM_CHARACTER_ACTION_NEAR* param = (PARAM_CHARACTER_ACTION_NEAR*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setNearCharacter(ctrl, param->flag);
    return true;
}

bool cmdSetCharacterCollision(void* scriptParam)
{
    PARAM_SET_CHARACTER_COLLISION* param = (PARAM_SET_CHARACTER_COLLISION*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setCollFlag(ctrl, param->collision);
    return true;
}

bool cmd_chara_shadow(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_CHARA_SHADOW* param = (PARAM_CHARA_SHADOW*)scriptParam;
    TownCharacterManager::getSingleton()->setShadow(ctrl, param->flag);
    return true;
}

bool cmd_chara_alpha(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_CHARA_ALPHA* param = (PARAM_CHARA_ALPHA*)scriptParam;
    TownCharacterManager::getSingleton()->setAlpha(ctrl, param->alpha);
    return true;
}

bool cmdCharacterActionDisplay(void* scriptParam)
{
    PARAM_CHARACTER_ACTION_DISPLAY* param = (PARAM_CHARACTER_ACTION_DISPLAY*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setDisplay(ctrl, param->flag);
    return true;
}

bool cmd_character_set_coll_stage(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_CHARACTER_SET_COLL_STAGE* param = (PARAM_CHARACTER_SET_COLL_STAGE*)scriptParam;
    char collFlag = 0;
    if (param->floorFlag == 1) {
        collFlag |= 2;
    }
    if (param->wallFlag == 1) {
        collFlag |= 1;
    }
    if (param->charaFlag == 1) {
        collFlag |= 4;
    }
    TownCharacterManager::getSingleton()->setStageColl(ctrl, collFlag);
    return true;
}

bool cmd_character_move_passive(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setMovePassive(ctrl);
    return true;
}

bool cmd_character_move_reverse(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setMoveReverse(ctrl);
    return true;
}

bool cmd_character_move_random(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setMoveRandom(ctrl);
    return true;
}

bool cmdCharacterActionPursue(void* scriptParam)
{
    twn::SCRIPT_MOVE_DATA data;
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->getMoveType(ctrl) != twn::MOVE_TYPE_PURSUE) {
        PARAM_CHARACTER_ACTION_PURSUE* param = (PARAM_CHARACTER_ACTION_PURSUE*)scriptParam;
        TownCharacterManager::getSingleton()->setCollFlag(ctrl, false);
        int ctrl = getPlacementCtrlId();
        data.speed.value = param->rate;
        data.speed *= TownCharacterManager::defaultSpeed;
        data.counter = 0;
        data.frame = 0;
        TownCharacterManager::getSingleton()->setMoveType(ctrl, twn::MOVE_TYPE_PURSUE, data);
    }
    return true;
}

bool cmd_character_pose_change(void* scriptParam)
{
    PARAM_CHARACTER_POSE_CHANGE* param = (PARAM_CHARACTER_POSE_CHANGE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setPosing(ctrl, param->index);
    return true;
}

bool cmd_is_character_direction(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_IS_CHARACTER_DIRECTION* param = (PARAM_IS_CHARACTER_DIRECTION*)scriptParam;
    short idx = TownCharacterManager::getSingleton()->getDirection(ctrl);
    return cmn::CommonCalculate::directionCheckByScriptParam(param->direction, idx);
}

bool cmd_is_character_front(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_IS_CHARACTER_FRONT* param = (PARAM_IS_CHARACTER_FRONT*)scriptParam;
    dss::Fix32Vector3 targetPos = twn::TownPlayerManager::getSingleton().getPosition();
    dss::Fix32Vector3 pos = TownCharacterManager::getSingleton()->getPosition(ctrl);
    dss::Fix32Vector3 dir;
    short idx = TownCharacterManager::getSingleton()->getDirection(ctrl);
    twn::TownActionCalculate::getDirByIdx(idx, dir);
    if (dir * (targetPos - pos) >= dss::Fix32(0L)) {
        if (param->flag == 0) {
            return true;
        }
    } else {
        if (param->flag == 1) {
            return true;
        }
    }
    return false;
}

bool cmd_is_trigger_distance(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_IS_TRIGGER_DISTANCE* param = (PARAM_IS_TRIGGER_DISTANCE*)scriptParam;
    dss::Fix32Vector3 pos1 = twn::TownPlayerManager::getSingleton().getPosition();
    dss::Fix32Vector3 pos2 = TownCharacterManager::getSingleton()->getPosition(ctrl);
    dss::Fix32 distance;
    distance.value = param->distance;
    distance *= distance;
    if (twn::TownSystem::getSingleton().getScriptSystem().isTriggerOk() == true) {
        if (pos1.lengthsq(pos2) <= distance) {
            twn::TownSystem::getSingleton().getScriptSystem().setTriggerFlag(false);
            return true;
        }
    }
    return false;
}

bool cmd_copy_party_chara(void* scriptParam)
{
    PARAM_COPY_PARTY_CHARA* param = (PARAM_COPY_PARTY_CHARA*)scriptParam;
    dss::Fix32Vector3 pos;
    short dirIdx;
    int charaNo;
    int ctrl = getPlacementCtrlId();
    if (twn::TownPlayerManager::getSingleton().getPlayerCopyInfo(param->playerNo, pos, dirIdx, charaNo) == true) {
        TownCharacterManager::getSingleton()->setCopyPlayerChara(ctrl, pos, dirIdx, charaNo);
    }
    return true;
}

bool cmd_set_chara_map_uid(void* scriptParam)
{
    PARAM_SET_CHARA_MAP_UID* param = (PARAM_SET_CHARA_MAP_UID*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setMapUid(ctrl, param->uid);
    return true;
}

bool cmd_chara_voice(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_CHARA_VOICE* param = (PARAM_CHARA_VOICE*)scriptParam;
    int type;
    switch (param->voice) {
        case 0:
            type = 0x30;
            break;
        case 1:
            type = 0x31;
            break;
        case 2:
            type = 0x32;
            break;
        case 3:
            type = 0x33;
            break;
        case 4:
            type = 0x39;
            break;
        default:
            type = 0x32;
            break;
    }
    TownCharacterManager::getSingleton()->setVoice(ctrl, type);
    return true;
}

bool cmd_character_anim(void* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_CHARACTER_ANIM* param = (PARAM_CHARACTER_ANIM*)scriptParam;
    int count = param->count;
    if (count == 0) {
        count = -1;
    }
    TownCharacterManager::getSingleton()->setCharaAnim(ctrl, count);
    return true;
}

bool cmd_set_chara_motion2(void* scriptParam)
{
    PARAM_SET_CHARA_MOTION2* param = (PARAM_SET_CHARA_MOTION2*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setMotion(ctrl, param->motion, param->flag == 0);
    return true;
}

bool cmdSetCharacterScale(void* scriptParam)
{
    PARAM_SET_CHARACTER_SCALE* param = (PARAM_SET_CHARACTER_SCALE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    dss::Fix32 data;
    data.value = param->scale;
    TownCharacterManager::getSingleton()->setScale(ctrl, data);
    return true;
}

bool cmdSetShadowOnly(void* scriptParam)
{
    PARAM_SET_SHADOW_ONLY* param = (PARAM_SET_SHADOW_ONLY*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setShadowOnly(ctrl, param->flag);
    return true;
}

void CharacterMoveTo::initialize(char* scriptParam)
{
    PARAM_CHARACTER_MOVE_TO* param = (PARAM_CHARACTER_MOVE_TO*)scriptParam;
    int ctrl = getPlacementCtrlId();
    twn::TOWN_SCRIPT_DATA data;
    dss::memset(&data, 0, sizeof(data));
    data.frame = param->frame;
    data.node[0] = TownCharacterManager::getSingleton()->getPosition(ctrl);
    data.node[1].vx.value = param->endX;
    data.node[1].vy.value = param->endY;
    data.node[1].vz.value = param->endZ;
    if (param->absFlag == 1) {
        data.node[1] += data.node[0];
    }
    TownCharacterManager::getSingleton()->setScriptData(ctrl, data);
    TownCharacterManager::getSingleton()->setSimpleMove(ctrl);
}

void CharacterMoveTo::execute()
{
}

int CharacterMoveTo::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

CharacterMoveTo g_CharacterMoveTo;

void CharacterMove2To::initialize(char* scriptParam)
{
    PARAM_CHARACTER_MOVE2_TO* param = (PARAM_CHARACTER_MOVE2_TO*)scriptParam;
    int ctrl = getPlacementCtrlId();
    twn::TOWN_SCRIPT_DATA data;
    dss::memset(&data, 0, sizeof(data));
    data.node[0] = TownCharacterManager::getSingleton()->getPosition(ctrl);
    data.node[1].vx.value = param->endX;
    data.node[1].vy.value = param->endY;
    data.node[1].vz.value = param->endZ;
    if (param->absFlag == 1) {
        data.node[1] += data.node[0];
    }
    if (param->rate == 0) {
        param->rate = 0x1000;
    }
    data.frame = (data.node[1] - data.node[0]).length().value / (param->rate * TownCharacterManager::defaultSpeed.value / 0x1000);
    TownCharacterManager::getSingleton()->setScriptData(ctrl, data);
    TownCharacterManager::getSingleton()->setSimpleMove(ctrl);
}

void CharacterMove2To::execute()
{
}

int CharacterMove2To::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

CharacterMove2To g_CharacterMove2To;

void CharacterWait::initialize(char* scriptParam)
{
    PARAM_CHARACTER_WAIT* param = (PARAM_CHARACTER_WAIT*)scriptParam;
    twn::TOWN_SCRIPT_DATA scriptData;
    dss::memset(&scriptData, 0, sizeof(scriptData));
    scriptData.frame = param->frame;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setScriptData(ctrl, scriptData);
}

void CharacterWait::execute()
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->execWait(ctrl);
}

int CharacterWait::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

CharacterWait g_CharacterWait;

void CharacterTremble::initialize(char* scriptParam)
{
    PARAM_CHARACTER_ACTION_TREMBLE* param = (PARAM_CHARACTER_ACTION_TREMBLE*)scriptParam;
    twn::TOWN_SCRIPT_DATA scriptData;
    dss::memset(&scriptData, 0, sizeof(scriptData));
    scriptData.frame = param->frame;
    scriptData.num[0] = param->direction;
    scriptData.num[1] = param->mode;
    scriptData.num[2] = param->sycle;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setScriptData(ctrl, scriptData);
}

void CharacterTremble::execute()
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->execTremble(ctrl);
}

int CharacterTremble::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

CharacterTremble g_CharacterTremble;

void CharacterActionMiniJump::initialize(char* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    dss::Fix32Vector3 pos = TownCharacterManager::getSingleton()->getPosition(ctrl);
    TownCharacterManager::getSingleton()->setJumpMove(ctrl, pos, 0x10);
}

int CharacterActionMiniJump::isEnd()
{
    int ctrl = getPlacementCtrlId();
    return TownCharacterManager::getSingleton()->isScriptEnd(ctrl);
}

CharacterActionMiniJump gCharacterActionMiniJump;

void CharacterActionGaze::initialize(char* scriptParam)
{
    PARAM_CHARACTER_ACTION_GAZE* param = (PARAM_CHARACTER_ACTION_GAZE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    dss::Fix32Vector3 vec = twn::TownPlayerManager::getSingleton().getPosition() - TownCharacterManager::getSingleton()->getPosition(ctrl);
    short idx = TownCharacterManager::getSingleton()->getDirection(ctrl);
    twn::TownActionCalculate::getIdxByVec(idx, vec);
    TownCharacterManager::getSingleton()->setSimpleRot(ctrl, idx, param->frame, 0);
}

int CharacterActionGaze::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isRotEnd(ctrl) != false) {
        return true;
    }
    return false;
}

CharacterActionGaze g_CharacterActionGaze;

void FadeinCharacter::initialize(char* scriptParam)
{
    PARAM_FADEIN_CHARACTER* param = (PARAM_FADEIN_CHARACTER*)scriptParam;
    int ctrl = getPlacementCtrlId();
    int type;
    switch (param->pattern) {
        case 0:
            type = 2;
            break;
        case 1:
            type = 3;
            break;
    }
    TownCharacterManager::getSingleton()->setFadeType(ctrl, type, param->frame);
}

int FadeinCharacter::isEnd()
{
    int ctrl = getPlacementCtrlId();
    return TownCharacterManager::getSingleton()->isEndFade(ctrl);
}

FadeinCharacter gFadeinCharacter;

void FadeoutCharacter::initialize(char* scriptParam)
{
    PARAM_FADEIN_CHARACTER* param = (PARAM_FADEIN_CHARACTER*)scriptParam;
    int ctrl = getPlacementCtrlId();
    int type;
    switch (param->pattern) {
        case 0:
            type = 4;
            break;
        case 1:
            type = 5;
            break;
    }
    TownCharacterManager::getSingleton()->setFadeType(ctrl, type, param->frame);
}

int FadeoutCharacter::isEnd()
{
    int ctrl = getPlacementCtrlId();
    return TownCharacterManager::getSingleton()->isEndFade(ctrl);
}

FadeoutCharacter gFadeoutCharacter;

void CharacterRiseup::initialize(char* scriptParam)
{
    PARAM_CHARACTER_EFFECT_MARK* param = (PARAM_CHARACTER_EFFECT_MARK*)scriptParam;
    twn::TOWN_SCRIPT_DATA scriptData;
    dss::memset(&scriptData, 0, sizeof(scriptData));
    scriptData.num[0] = param->index;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setScriptData(ctrl, scriptData);
}

void CharacterRiseup::execute()
{
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->execRiseup(ctrl);
}

int CharacterRiseup::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

CharacterRiseup g_CharacterRiseup;

void CharaRot::initialize(char* scriptParam)
{
    PARAM_SET_CHARA_ROT* param = (PARAM_SET_CHARA_ROT*)scriptParam;
    int ctrl = getPlacementCtrlId();
    dss::Fix32 idx;
    idx.value = param->idx;
    TownCharacterManager::getSingleton()->setRotFrame(ctrl, param->frame, degreeToAngle(idx), param->rotFlag, param->endFlag);
}

int CharaRot::isEnd()
{
    int ctrl = getPlacementCtrlId();
    return TownCharacterManager::getSingleton()->isRotFrameEnd(ctrl);
}

CharaRot gCharaRot;

void CharacterActionTurn::initialize(char* scriptParam)
{
    PARAM_CHARACTER_ACTION_TURN* param = (PARAM_CHARACTER_ACTION_TURN*)scriptParam;
    int ctrl = getPlacementCtrlId();
    short idx = twn::TownActionCalculate::getIdxByParam(param->direction);
    int rot = param->rot;
    TownCharacterManager::getSingleton()->setSimpleRot(ctrl, idx, param->frame, rot + 1);
}

int CharacterActionTurn::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isRotEnd(ctrl) != false) {
        return true;
    }
    return false;
}

CharacterActionTurn g_CharacterActionTurn;

void CharacterActionNormalJump::initialize(char* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_CHARACTER_NORMAL_JUMP* param = (PARAM_CHARACTER_NORMAL_JUMP*)scriptParam;
    dss::Fix32Vector3 pos;
    pos.vx.value = param->endX;
    pos.vy.value = param->endY;
    pos.vz.value = param->endZ;
    TownCharacterManager::getSingleton()->setJumpMove(ctrl, pos, param->frame);
}

int CharacterActionNormalJump::isEnd()
{
    int ctrl = getPlacementCtrlId();
    return TownCharacterManager::getSingleton()->isScriptEnd(ctrl);
}

CharacterActionNormalJump gCharacterActionNormalJump;

void Cmd_chara_move_line_to_player::initialize(char* scriptParam)
{
    int ctrl = getPlacementCtrlId();
    PARAM_CHARA_MOVE_LINE_TO_PLAYER* param = (PARAM_CHARA_MOVE_LINE_TO_PLAYER*)scriptParam;
    dss::Fix32Vector3 start = TownCharacterManager::getSingleton()->getPosition(ctrl);
    dss::Fix32Vector3 end = twn::TownPlayerManager::getSingleton().getPosition();
    end.vy = start.vy;
    dss::Fix32Vector3 vec = end - start;
    if (param->line == 0) {
        if (vec.vx < dss::Fix32(0L)) {
            end.vx.value += param->offset;
        } else {
            end.vx.value -= param->offset;
        }
        end.vz = start.vz;
    } else {
        if (vec.vz < dss::Fix32(0L)) {
            end.vz.value += param->offset;
        } else {
            end.vz.value -= param->offset;
        }
        end.vx = start.vx;
    }
    twn::TOWN_SCRIPT_DATA scriptData;
    dss::memset(&scriptData, 0, sizeof(scriptData));
    scriptData.node[0] = start;
    scriptData.node[1] = end;
    if (param->rate == 0) {
        param->rate = 0x1000;
    }
    scriptData.frame = (scriptData.node[1] - scriptData.node[0]).length().value / (param->rate * TownCharacterManager::defaultSpeed.value / 0x1000);
    TownCharacterManager::getSingleton()->setScriptData(ctrl, scriptData);
    TownCharacterManager::getSingleton()->setSimpleMove(ctrl);
}

int Cmd_chara_move_line_to_player::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

Cmd_chara_move_line_to_player gCmd_chara_move_line_to_player;

void CharacterMove2ToPlayer::initialize(char* scriptParam)
{
    PARAM_CHARACTER_MOVE2_PLAYER* param = (PARAM_CHARACTER_MOVE2_PLAYER*)scriptParam;
    int ctrl = getPlacementCtrlId();
    twn::TOWN_SCRIPT_DATA data;
    dss::memset(&data, 0, sizeof(data));
    data.num[0] = param->mode;
    data.node[0] = TownCharacterManager::getSingleton()->getPosition(ctrl);
    data.node[1] = twn::TownPlayerManager::getSingleton().getPosition();
    unsigned char dir = param->direction;
    dss::Fix32Vector3 vec = twn::TownActionCalculate::getParamVec(dir);
    dss::Fix32 rate;
    rate.value = param->adjust;
    data.node[1] += vec * rate;
    if (param->rate == 0) {
        param->rate = 0x1000;
    }
    data.frame = (data.node[1] - data.node[0]).length().value / (param->rate * TownCharacterManager::defaultSpeed.value / 0x1000);
    TownCharacterManager::getSingleton()->setScriptData(ctrl, data);
    TownCharacterManager::getSingleton()->setMoveToParty(ctrl);
    TownCharacterManager::getSingleton()->setSimpleMove(ctrl);
    TownCharacterManager::getSingleton()->setCollFlag(ctrl, false);
}

void CharacterMove2ToPlayer::execute()
{
}

int CharacterMove2ToPlayer::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

CharacterMove2ToPlayer g_CharacterMove2ToPlayer;

void CharacterMoveToParty::initialize(char* scriptParam)
{
    PARAM_CHARACTER_MOVE_PARTY* param = (PARAM_CHARACTER_MOVE_PARTY*)scriptParam;
    int ctrl = getPlacementCtrlId();
    twn::TOWN_SCRIPT_DATA data;
    dss::memset(&data, 0, sizeof(data));
    data.num[0] = param->mode;
    data.node[0] = TownCharacterManager::getSingleton()->getPosition(ctrl);
    int drawCount = twn::TownPlayerManager::getSingleton().getPartyDrawCount();
    data.node[1] = twn::TownPlayerManager::getSingleton().party_.getMemberPos(drawCount);
    data.frame = param->frame;
    TownCharacterManager::getSingleton()->setScriptData(ctrl, data);
    TownCharacterManager::getSingleton()->setMoveToParty(ctrl);
    TownCharacterManager::getSingleton()->setSimpleMove(ctrl);
    TownCharacterManager::getSingleton()->setCollFlag(ctrl, false);
}

void CharacterMoveToParty::execute()
{
}

int CharacterMoveToParty::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

CharacterMoveToParty g_CharacterMoveToParty;

void CharacterMove2ToParty::initialize(char* scriptParam)
{
    PARAM_CHARACTER_MOVE2_PARTY* param = (PARAM_CHARACTER_MOVE2_PARTY*)scriptParam;
    int ctrl = getPlacementCtrlId();
    twn::TOWN_SCRIPT_DATA data;
    dss::memset(&data, 0, sizeof(data));
    data.node[0] = TownCharacterManager::getSingleton()->getPosition(ctrl);
    int drawCount = twn::TownPlayerManager::getSingleton().getPartyDrawCount();
    data.node[1] = twn::TownPlayerManager::getSingleton().party_.getMemberPos(drawCount);
    if (param->rate == 0) {
        param->rate = 0x1000;
    }
    dss::Fix32Vector3 vec = data.node[1] - data.node[0];
    dss::Fix32 speed;
    dss::Fix32 dv;
    speed.value = param->rate;
    speed *= TownCharacterManager::defaultSpeed;
    dv = vec.length() / speed;
    data.frame = dv.value / 0x1000;
    data.num[0] = param->mode;
    TownCharacterManager::getSingleton()->setScriptData(ctrl, data);
    TownCharacterManager::getSingleton()->setMoveToParty(ctrl);
    TownCharacterManager::getSingleton()->setSimpleMove(ctrl);
    TownCharacterManager::getSingleton()->setCollFlag(ctrl, false);
}

void CharacterMove2ToParty::execute()
{
}

int CharacterMove2ToParty::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

CharacterMove2ToParty g_CharacterMove2ToParty;

void CharacterMoveToPlayer::initialize(char* scriptParam)
{
    PARAM_CHARACTER_MOVE_PLAYER* param = (PARAM_CHARACTER_MOVE_PLAYER*)scriptParam;
    int ctrl = getPlacementCtrlId();
    twn::TOWN_SCRIPT_DATA data;
    dss::memset(&data, 0, sizeof(data));
    data.num[0] = param->mode;
    data.node[0] = TownCharacterManager::getSingleton()->getPosition(ctrl);
    data.node[1] = twn::TownPlayerManager::getSingleton().getPosition();
    unsigned char dir = param->direction;
    dss::Fix32Vector3 vec = twn::TownActionCalculate::getParamVec(dir);
    dss::Fix32 rate;
    rate.value = param->adjust;
    data.node[1] += vec * rate;
    data.frame = param->frame;
    TownCharacterManager::getSingleton()->setScriptData(ctrl, data);
    TownCharacterManager::getSingleton()->setMoveToParty(ctrl);
    TownCharacterManager::getSingleton()->setSimpleMove(ctrl);
    TownCharacterManager::getSingleton()->setCollFlag(ctrl, false);
}

void CharacterMoveToPlayer::execute()
{
}

int CharacterMoveToPlayer::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

CharacterMoveToPlayer g_CharacterMoveToPlayer;

void Cmd_character_rgb_anim2::initialize(char* scriptParam)
{
    PARAM_CHARACTER_RGB_ANIM2* param = (PARAM_CHARACTER_RGB_ANIM2*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setChangePaletteRate(ctrl, param->R, param->G, param->B, param->frame);
    endFlag_ = param->flag;
}

int Cmd_character_rgb_anim2::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (endFlag_ == 0) {
        return true;
    }
    return TownCharacterManager::getSingleton()->isEndChangePalletRate(ctrl);
}

Cmd_character_rgb_anim2 gCmd_character_rgb_anim2;

void Charcter_3d_motion::initialize(char* scriptParam)
{
    PARAM_CHARCTER_3D_MOTION* param = (PARAM_CHARCTER_3D_MOTION*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setMotion(ctrl, param->motion, param->flag == 0);
}

int Charcter_3d_motion::isEnd()
{
    int ctrl = getPlacementCtrlId();
    return TownCharacterManager::getSingleton()->isMotion(ctrl);
}

Charcter_3d_motion gCharcter_3d_motion;

void Cmd_chara_line_move::initialize(char* scriptParam)
{
    PARAM_CHARACTER_LINE_MOVE* param = (PARAM_CHARACTER_LINE_MOVE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    dss::Fix32Vector3 start = TownCharacterManager::getSingleton()->getPosition(ctrl);
    dss::Fix32Vector3 target = cmn::CommonCalculate::getAxisMoveTargetByParam(param->axis, param->absFlag, param->value, start);
    twn::TOWN_SCRIPT_DATA scriptData;
    dss::memset(&scriptData, 0, sizeof(scriptData));
    scriptData.frame = param->frame;
    scriptData.node[0] = start;
    scriptData.node[1] = target;
    TownCharacterManager::getSingleton()->setScriptData(ctrl, scriptData);
    TownCharacterManager::getSingleton()->setSimpleMove(ctrl);
}

void Cmd_chara_line_move::execute()
{
}

int Cmd_chara_line_move::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

Cmd_chara_line_move gCmd_chara_line_move;

void Cmd_chara_line_move2::initialize(char* scriptParam)
{
    PARAM_CHARACTER_LINE_MOVE2* param = (PARAM_CHARACTER_LINE_MOVE2*)scriptParam;
    int ctrl = getPlacementCtrlId();
    dss::Fix32Vector3 start = TownCharacterManager::getSingleton()->getPosition(ctrl);
    dss::Fix32Vector3 target = cmn::CommonCalculate::getAxisMoveTargetByParam(param->axis, param->absFlag, param->value, start);
    twn::TOWN_SCRIPT_DATA scriptData;
    dss::memset(&scriptData, 0, sizeof(scriptData));
    scriptData.node[0] = start;
    scriptData.node[1] = target;
    if (param->rate == 0) {
        param->rate = 0x1000;
    }
    scriptData.frame = (scriptData.node[1] - scriptData.node[0]).length().value / (param->rate * TownCharacterManager::defaultSpeed.value / 0x1000);
    TownCharacterManager::getSingleton()->setScriptData(ctrl, scriptData);
    TownCharacterManager::getSingleton()->setSimpleMove(ctrl);
}

void Cmd_chara_line_move2::execute()
{
}

int Cmd_chara_line_move2::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isScriptEnd(ctrl) != 0) {
        return true;
    }
    return false;
}

Cmd_chara_line_move2 gCmd_chara_line_move2;

void CharacterHueChange::initialize(char* scriptParam)
{
    PARAM_SET_CHARACTER_HUE* param = (PARAM_SET_CHARACTER_HUE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setHueChange(ctrl, param->type, param->frame);
}

int CharacterHueChange::isEnd()
{
    int ctrl = getPlacementCtrlId();
    if (TownCharacterManager::getSingleton()->isHueChange(ctrl) != false) {
        return true;
    }
    return false;
}

CharacterHueChange g_CharacterHueChange;

bool cmdSetRockRelocation(void* scriptParam)
{
    PARAM_SET_ROCK_RELOCATION* param = (PARAM_SET_ROCK_RELOCATION*)scriptParam;
    int ctrl = getPlacementCtrlId();
    if (status::g_StageInfo.getRockFlag(param->id) == 0) {
        dss::Fix32Vector3& pos = status::g_StageInfo.getRockLocation(param->id);
        TownCharacterManager::getSingleton()->setPosition(ctrl, pos);
    }
    return true;
}

bool cmdSetRockSave(void* scriptParam)
{
    PARAM_SET_ROCK_SAVE* param = (PARAM_SET_ROCK_SAVE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    status::g_StageInfo.setRockFlag(param->id, false);
    status::g_StageInfo.rock_[param->id] = TownCharacterManager::getSingleton()->getPosition(ctrl);
    return true;
}

bool cmd_set_chara_synchro(void* scriptParam)
{
    PARAM_SET_CHARA_SYNCHRONIZED_MOVE* param = (PARAM_SET_CHARA_SYNCHRONIZED_MOVE*)scriptParam;
    int ctrl = getPlacementCtrlId();
    int pair = getPlacementCtrlId(param->pairObject);
    TownCharacterManager::getSingleton()->setSynchronous(ctrl, param->flag, pair);
    TownCharacterManager::getSingleton()->setSynchronous(pair, param->flag, ctrl);
    return true;
}

bool cmd_set_chara_mortion_lock(void* scriptParam)
{
    PARAM_SET_CHARA_MORTION_LOCK* param = (PARAM_SET_CHARA_MORTION_LOCK*)scriptParam;
    int ctrl = getPlacementCtrlId();
    TownCharacterManager::getSingleton()->setMotionLock(ctrl, param->flag);
    return true;
}

bool cmd_set_chara_coll(void* scriptParam)
{
    PARAM_SET_PASSIVE_CHARA_COLL* param = (PARAM_SET_PASSIVE_CHARA_COLL*)scriptParam;
    dss::Fix32 a;
    dss::Fix32 b;
    dss::Fix32 c;
    dss::Fix32 d;
    a.value = param->minX;
    b.value = param->maxX;
    c.value = param->minZ;
    d.value = param->maxZ;
    twn::TownExtraCollManager::getSingleton().setCheckArea(a, b, c, d);
    return true;
}

void ScriptCharaCommand_weakVtable()
{
    ScriptCommandWeakVtable unused;
}
