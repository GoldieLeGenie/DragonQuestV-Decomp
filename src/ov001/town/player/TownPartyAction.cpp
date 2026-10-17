#pragma ipa file
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/global/Global.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline int status::PartyStatusUtility::isSeparate()
{
    return separateFlag_;
}

inline const dss::Fix32Vector3& cmn::PartyMoveAction::getMemberPrevPos(int no)
{
    return partyData_[no].prevPosition;
}

inline void cmn::PartyMoveAction::setPartyState(PARTY_ACTION_STATE state)
{
    state_ = state;
}

inline cmn::PartyMoveAction::PARTY_ACTION_STATE cmn::PartyMoveAction::getPartyState()
{
    return state_;
}

static const dss::Fix32 unk_02151958(0.3f);

THUMB void twn::TownPartyAction::setup()
{
    if (status::g_StageInfo.encount_ == 0 && cmn::g_cmnPartyInfo.prevLocation_ == 0 && status::PartyStatusUtility::isSeparate() == false) {
        initialize();
        setAllMemberPos(cmn::g_cmnPartyInfo.position_, cmn::g_cmnPartyInfo.dirIdx_);
        for (int i = 0; i < PARTY_MEMBER_MAX; i++) {
            partyAlphaFlag_[i] = START_ALPHA_CHANGE;
        }
    }
    setPartyState(MOVE_NORMAL);
    half_ = 0;
    counter_ = 0;
    fixFlag_ = 0;
    script_ = 0;
    distanceCount_ = 2;
}

THUMB void twn::TownPartyAction::cleanup()
{
}

THUMB void twn::TownPartyAction::execute()
{
}

THUMB void twn::TownPartyAction::resetFixPos()
{
    if (fixFlag_ == 1) {
        for (int i = 1; i < PARTY_MEMBER_MAX; i++) {
            setMemberPos(i, temp[i]);
        }
    }
}

THUMB int twn::TownPartyAction::getMemberCount()
{
    return TownPlayerManager::getSingleton().getPartyDrawCount();
}

THUMB const dss::Fix32Vector3& twn::TownPartyAction::getMemberPos(int index)
{
    return partyData_[index].position;
}

THUMB short twn::TownPartyAction::getMemberDir(int index)
{
    return partyData_[index].direction;
}

THUMB void twn::TownPartyAction::setPosition()
{
    static dss::Fix32 unk_0216689c(0x19a);
    switch (getPartyState()) {
    case MOVE_NORMAL:
        setNextArray(cmn::g_cmnPartyInfo.position_, cmn::g_cmnPartyInfo.dirIdx_);
        moveNormalUpdate();
        break;
    case MOVE_TO_FIRST:
        setNextArray(cmn::g_cmnPartyInfo.position_, cmn::g_cmnPartyInfo.dirIdx_);
        moveToFirstUpdate();
        break;
    case MOVE_TO_PARALLEL:
        moveParallelUpdate();
        break;
    case MOVE_TO_FORMATION:
    case SET_FORMATION:
        formationMoveUpdate();
        break;
    case MOVE_MEMBER_JUMP:
        formationMoveUpdate();
        break;
    }
    int drawCount;
    bool endFlag = true;
    if (changeAlpha_ == 1) {
        status::g_Party.setDisplayMode();
        drawCount = TownPlayerManager::getSingleton().getPartyDrawCount();
        for (int i = 0; i < drawCount; i++) {
            if (!isEqalNextPos(i) && partyAlphaFlag_[i] == START_ALPHA_CHANGE) {
                partyAlphaFlag_[i] = ALPHA_CHANGING;
            }
            if (partyAlphaFlag_[i] == ALPHA_CHANGING) {
                TownPlayerManager::getSingleton().addPartyDrawAlpha(i, 4);
            }
            if (TownPlayerManager::getSingleton().partyDraw_.charaIndex_[i] == 0xe3) {
                if (g_Global.getNowAreaNo() == 0xa || g_Global.getNowAreaNo() == 0x1e) {
                    if (TownPlayerManager::getSingleton().getPartyDrawAlpha(i) == 0x10) {
                        partyAlphaFlag_[i] = 2;
                    }
                } else {
                    if (TownPlayerManager::getSingleton().getPartyDrawAlpha(i) == 0x1f) {
                        partyAlphaFlag_[i] = 2;
                    }
                }
            } else {
                if (TownPlayerManager::getSingleton().getPartyDrawAlpha(i) == 0x1f) {
                    partyAlphaFlag_[i] = 2;
                }
            }
            if (partyAlphaFlag_[i] != 2) {
                endFlag = false;
            }
        }
        if (endFlag == true) {
            changeAlpha_ = 0;
        }
    }
}

THUMB void twn::TownPartyAction::setAllPotition(dss::Fix32Vector3& pos)
{
    setAllMemberPos(pos, cmn::g_cmnPartyInfo.dirIdx_);
}

THUMB int twn::TownPartyAction::getDrawCount()
{
    return TownPlayerManager::getSingleton().getPartyDrawCount();
}

THUMB bool twn::TownPartyAction::isEqalNextPos(int index)
{
    bool ret = false;
    if (index < 1) {
        return ret;
    }
    if (index > PARTY_MEMBER_MAX) {
        return ret;
    }
    if (getMemberPos(index) == getMemberPrevPos(index)) {
        ret = true;
    }
    return ret;
}

THUMB void twn::TownPartyAction::setMemberJump(int index)
{
    setPartyState(MOVE_TO_FORMATION);
    partyMove_[index].setJumpMove((dss::Fix32Vector3&)getMemberPos(index), (dss::Fix32Vector3&)getMemberPos(index), 0x10);
}

THUMB void twn::TownPartyAction::setFormation(dss::Fix32Vector3& dirVec, short dirIdx, dss::Fix32 speed)
{
    fixFlag_ = 0;
    formation_ = 1;
    int count = getDrawCount();
    dss::Fix32Vector3 start[8];
    for (int i = 1; i < count; i++) {
        start[i] = getMemberPos(i);
    }
    int index = top_;
    arrayCount_ = MOVE_ARRAY_MAX;
    for (int i = 0; i < MOVE_ARRAY_MAX; i++) {
        posArray_[index] = cmn::g_cmnPartyInfo.position_ + dirVec * i;
        dirArray_[index] = dirIdx;
        distArray_[index] = memberSpeed_;
        index--;
        if (index < 0) {
            index = MOVE_ARRAY_MAX - 1;
        }
    }
    moveNormalUpdate();
    if (speed != 0L) {
        dss::Fix32Vector3 end;
        for (int i = 1; i < count; i++) {
            end = getMemberPos(i);
            partyMove_[i].setActionMove(start[i], end);
            partyMove_[i].setMoveSpeed(speed);
        }
        setPartyState(MOVE_TO_FORMATION);
    } else {
        setPartyState(SET_FORMATION);
    }
}

THUMB void twn::TownPartyAction::formationMoveUpdate()
{
    if (getPartyState() == SET_FORMATION) {
        setPartyState(MOVE_NORMAL);
        return;
    }
    int count = getDrawCount();
    dss::Fix32Vector3 nowPos;
    dss::Fix32Vector3 nextPos;
    dss::Vector3<short> angle;
    int ret = true;
    for (int i = 1; i < count; i++) {
        nowPos = getMemberPos(i);
        nextPos = nowPos;
        angle.vy = getMemberDir(i);
        partyMove_[i].execMove(nextPos);
        partyMove_[i].execRot(angle);
        {
            dss::Fix32Vector3 dir = nextPos - nowPos;
            short idx = getMemberDir(i);
            TownActionCalculate::getIdxByVec(idx, dir);
            setMemberPos(i, nextPos);
            setMemberDir(i, idx);
        }
        if (partyMove_[i].moveUpdate() == false) {
            ret = false;
        } else {
            setMemberDir(i, partyData_[0].direction);
        }
    }
    if (ret == true) {
        setPartyState(MOVE_NORMAL);
    }
}

THUMB bool twn::TownPartyAction::isFormationEnd()
{
    return getPartyState() == MOVE_NORMAL;
}

THUMB void twn::TownPartyAction::setMoveToFirstHalfSpeed(SPEED_TYPE flag)
{
    half_ = flag;
    switch (flag) {
    case SPEED_TYPE1:
        distanceCount_ = 2;
        break;
    case SPEED_TYPE2:
        distanceCount_ = 4;
        break;
    default:
        distanceCount_ = 2;
        break;
    }
}

THUMB bool twn::TownPartyAction::getMoveFirstFlag()
{
    return getPartyState() == MOVE_TO_FIRST;
}

THUMB void twn::TownPartyAction::setMoveFirstFlag(bool flag)
{
    if (status::PartyStatusUtility::isSeparate() == true) {
        return;
    }
    if (flag == true) {
        setPartyState(MOVE_TO_FIRST);
    } else {
        setPartyState(MOVE_NORMAL);
    }
}
