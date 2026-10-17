#pragma ipa file
#include "ov005/fld/FieldParty.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"
#include "ov005/fld/FieldAction.hpp"
#include "ov005/fld/FieldActionCalculate.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"

inline cmn::PartyMoveAction::PartyMoveAction()
{
}

inline void cmn::PartyMoveAction::setPartyState(PARTY_ACTION_STATE state)
{
    state_ = state;
}

inline cmn::PartyMoveAction::PARTY_ACTION_STATE cmn::PartyMoveAction::getPartyState()
{
    return state_;
}

inline void cmn::PartyMoveAction::setSpeed(dss::Fix32 speed)
{
    memberSpeed_ = speed;
}

THUMB inline const dss::Fix32Vector3& cmn::PartyMoveAction::getMemberPos(int no)
{
    return partyData_[no].position;
}

THUMB inline short cmn::PartyMoveAction::getMemberDir(int no)
{
    return partyData_[no].direction;
}

inline int status::PartyStatus::isCarriage()
{
    return carriage_;
}

inline int status::StageInfo::getEncountFlag()
{
    return encount_;
}

inline int cmn::CommonPartyInfo::isPrevLocation()
{
    return prevLocation_;
}

inline void fld::FieldParty::resetLRMove(bool flag)
{
    LRreset_ = flag;
}

THUMB fld::FieldParty::FieldParty()
{
}

THUMB fld::FieldParty::~FieldParty()
{
}

THUMB void fld::FieldParty::setup()
{
    LRreset_ = false;
    if (status::g_Party.isCarriage()) {
        flagBashaArray_ = true;
        setPartyState(MOVE_BASHA);
    } else {
        flagBashaArray_ = false;
        setPartyState(MOVE_NORMAL);
    }
    if (status::g_StageInfo.getEncountFlag() == false && cmn::g_cmnPartyInfo.isPrevLocation() == false) {
        initialize();
        setAllMemberPos(cmn::g_cmnPartyInfo.position_, cmn::g_cmnPartyInfo.dirIdx_);
        bashaLPos_ = getMemberPos(2);
        bashaRPos_ = bashaLPos_;
        bashaLIdx_ = getMemberDir(2);
        bashaRIdx_ = bashaLIdx_;
        flagMoveToFirst_ = false;
        countPartyArray_ = 0;
        countLFix_ = 0;
        countRFix_ = 0;
    }
    setSpeed(FieldActionBase::Speed);
}

THUMB void fld::FieldParty::cleanup()
{
}

THUMB void fld::FieldParty::execute()
{
    prevDirIdx_ = getMemberDir(2);
    setNextArray(cmn::g_cmnPartyInfo.position_, cmn::g_cmnPartyInfo.dirIdx_);
    switch (getPartyState()) {
    case MOVE_TO_FIRST:
        moveToFirstUpdate();
        if (flagBashaArray_ == true) {
            getSidePos(dq5::TYPE_DIR4_LEFT, bashaLPos_, &bashaLPos_, &bashaLIdx_);
            getSidePos(dq5::TYPE_DIR4_RIGHT, bashaRPos_, &bashaRPos_, &bashaRIdx_);
            setMemberPos(6, (dss::Fix32Vector3&)getMemberPos(4));
            setMemberPos(7, (dss::Fix32Vector3&)getMemberPos(5));
            setMemberDir(6, getMemberDir(4));
            setMemberDir(7, getMemberDir(5));
            setMemberPos(4, bashaLPos_);
            setMemberDir(4, bashaLIdx_);
            setMemberPos(5, bashaRPos_);
            setMemberDir(5, bashaRIdx_);
        }
        break;
    case MOVE_BASHA:
        moveBashaUpdate();
        countPartyArray_++;
        break;
    case MOVE_NORMAL:
        moveNormalUpdate();
        break;
    }
}

THUMB void fld::FieldParty::moveBashaUpdate()
{
    static const dss::Fix32 speed = 1.2f;
    moveNormalUpdate();
    if (prevDirIdx_ != getMemberDir(2)) {
        countPartyArray_ = 0;
    }
    getSidePos(dq5::TYPE_DIR4_LEFT, bashaLPos_, &bashaLPos_, &bashaLIdx_);
    getSidePos(dq5::TYPE_DIR4_RIGHT, bashaRPos_, &bashaRPos_, &bashaRIdx_);
    setMemberPos(6, (dss::Fix32Vector3&)getMemberPos(4));
    setMemberPos(7, (dss::Fix32Vector3&)getMemberPos(5));
    setMemberDir(6, getMemberDir(4));
    setMemberDir(7, getMemberDir(5));
    setMemberPos(4, bashaLPos_);
    setMemberDir(4, bashaLIdx_);
    setMemberPos(5, bashaRPos_);
    setMemberDir(5, bashaRIdx_);
}

THUMB int fld::FieldParty::getMemberCount()
{
    return FieldPlayerManager::getSingleton().partyDraw_.countReal_;
}

THUMB void fld::FieldParty::setBashaArray(bool flag)
{
    flagBashaArray_ = flag;
    if (flag == true) {
        setPartyState(MOVE_BASHA);
    } else {
        setPartyState(MOVE_NORMAL);
    }
}

THUMB void fld::FieldParty::getSidePos(dq5::TYPE_DIR4 side, dss::Fix32Vector3& nowPos, dss::Fix32Vector3* nextPos, short* retIdx)
{
    short idx = getMemberDir(2);
    short bashaIdx;
    dss::Fix32Vector3 bashaPos(getMemberPos(2));
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 pos;
    dss::Fix32Vector3 tempPos;
    dss::Fix32Vector3 retPos;
    dss::Fix32 len;
    if (side == dq5::TYPE_DIR4_LEFT) {
        bashaIdx = FieldActionCalculate::getDir8RotIdx(idx, -2);
        len = getDistance(2, 3) + getDistance(4, 2);
    } else if (side == dq5::TYPE_DIR4_RIGHT) {
        bashaIdx = FieldActionCalculate::getDir8RotIdx(idx, 2);
        len = getDistance(2, 2) + getDistance(5, 3);
    }
    vec = FieldActionCalculate::getVector3ByDir8(bashaIdx);
    vec.normalize();
    pos = bashaPos + vec * len;
    collisionSide(side, &pos, idx);
    countPartyArray_ = dss::clamp(0, countPartyArray_, COUNT_MAX);
    *nextPos = nowPos * (COUNT_MAX - countPartyArray_) / COUNT_MAX + pos * countPartyArray_ / COUNT_MAX;
    *retIdx = idx;
    if (LRreset_ == true) {
        fixSidePos(side, 0);
    }
}

THUMB void fld::FieldParty::fixSidePos(dq5::TYPE_DIR4 side, int fix)
{
    dss::Fix32Vector3* nextPos;
    int* cont;
    if (side == dq5::TYPE_DIR4_LEFT) {
        nextPos = &bashaLPos_;
        cont = &countLFix_;
    } else {
        cont = &countRFix_;
        nextPos = &bashaRPos_;
    }
    *cont += fix;
    *cont = (*cont > COUNT_MAX) ? COUNT_MAX : ((*cont < 0) ? 0 : *cont);
    *nextPos = getMemberPos(2) * *cont / COUNT_MAX + *nextPos * (COUNT_MAX - *cont) / COUNT_MAX;
}

THUMB void fld::FieldParty::collisionSide(dq5::TYPE_DIR4 side, dss::Fix32Vector3* nextPos, short dirIdx)
{
    dss::Fix32Vector3 colPos;
    dss::Fix32Vector3 fixPos;
    dss::Fix32Vector3 fixVec;
    int* cont;
    short fixIdx;
    if (side == dq5::TYPE_DIR4_LEFT) {
        fixIdx = FieldActionCalculate::getDir8RotIdx(dirIdx, 2);
        cont = &countLFix_;
    } else {
        fixIdx = FieldActionCalculate::getDir8RotIdx(dirIdx, -2);
        cont = &countRFix_;
    }
    fixVec = FieldActionCalculate::getVector3ByDir8(fixIdx);
    fixVec.normalize();
    colPos = getMemberPos(1) + fixVec * -13;
    int blk1X = colPos.vx.value / 0x10000;
    int blk1Y = colPos.vy.value / 0x10000;
    int blk2X = nextPos->vx.value / 0x10000;
    int blk2Y = nextPos->vy.value / 0x10000;
    bool col1 = FieldStage::getSingleton()->getBlockAttr(blk1X, blk1Y);
    bool col2 = FieldStage::getSingleton()->getBlockAttr(blk2X, blk2Y);
    if (LRreset_ == true || col1 == false || col2 == false) {
        (*cont)++;
    } else {
        (*cont)--;
    }
    *cont = (*cont > COUNT_MAX) ? COUNT_MAX : ((*cont < 0) ? 0 : *cont);
    *nextPos += fixVec * *cont * 3 / 4;
}

THUMB void fld::FieldParty::moveAllPlayerToFirst()
{
    setPartyState(MOVE_TO_FIRST);
    if (flagBashaArray_ == true) {
        resetLRMove(true);
    }
}

THUMB const dss::Fix32Vector3& fld::FieldParty::getMemberPos(int index)
{
    return PartyMoveAction::getMemberPos(index);
}

THUMB void fld::FieldParty::setMemberPos(int index, dss::Fix32Vector3& pos)
{
    partyData_[index].position = pos;
}

THUMB short fld::FieldParty::getMemberDir(int index)
{
    return PartyMoveAction::getMemberDir(index);
}

THUMB void fld::FieldParty::setMemberDir(int index, short idx)
{
    partyData_[index].direction = idx;
}

THUMB void fld::FieldParty::setAllPlayerAtFirst()
{
    bashaLPos_ = cmn::g_cmnPartyInfo.position_;
    bashaRPos_ = cmn::g_cmnPartyInfo.position_;
    bashaLIdx_ = cmn::g_cmnPartyInfo.dirIdx_;
    bashaRIdx_ = cmn::g_cmnPartyInfo.dirIdx_;
    setAllMemberPos(cmn::g_cmnPartyInfo.position_, cmn::g_cmnPartyInfo.dirIdx_);
    resetBashaCount();
}

THUMB void fld::FieldParty::resetBashaCount()
{
    countPartyArray_ = 0;
    countRFix_ = 0;
    countLFix_ = 0;
    resetLRMove(false);
    if (status::g_Party.isCarriage()) {
        flagBashaArray_ = true;
        setPartyState(MOVE_BASHA);
    } else {
        flagBashaArray_ = false;
        setPartyState(MOVE_NORMAL);
    }
}

THUMB void fld::FieldParty::setFormation(dss::Fix32Vector3& dirVec, short dirIdx)
{
    FieldPlayerManager& manager = FieldPlayerManager::getSingleton();
    int index = top_;
    arrayCount_ = MOVE_ARRAY_MAX;
    for (int i = 0; i < MOVE_ARRAY_MAX; i++) {
        posArray_[index] = cmn::g_cmnPartyInfo.position_ + dirVec * FieldActionBase::Speed * 2 * i / 3;
        dirArray_[index] = dirIdx;
        distArray_[index] = FieldActionBase::Speed * 2 / 3;
        index--;
        if (index < 0) {
            index = MOVE_ARRAY_MAX - 1;
        }
    }
    moveNormalUpdate();
}
