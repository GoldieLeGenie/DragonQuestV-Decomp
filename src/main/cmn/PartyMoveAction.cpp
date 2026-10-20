#include "main/cmn/PartyMoveAction.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/status/PartyStatus.hpp"

inline int status::PartyStatusUtility::isSeparate()
{
    return separateFlag_;
}

inline void cmn::PartyMoveAction::setMemberPrevPos(int no, dss::Fix32Vector3& pos)
{
    partyData_[no].prevPosition = pos;
}

inline void cmn::PartyMoveAction::setMemberPrevDir(int no, short idx)
{
    partyData_[no].prevDirection = idx;
}

inline void cmn::PartyMoveAction::setPartyState(PARTY_ACTION_STATE state)
{
    state_ = state;
}

inline void cmn::CommonPartyInfo::setPosition(dss::Fix32Vector3& pos)
{
    position_ = pos;
}

dss::Fix32Vector3 cmn::PartyMoveAction::posArray_[MOVE_ARRAY_MAX];
dss::Fix32 cmn::PartyMoveAction::distArray_[MOVE_ARRAY_MAX];
short cmn::PartyMoveAction::dirArray_[MOVE_ARRAY_MAX];
cmn::PartyData cmn::PartyMoveAction::partyData_[PARTY_MEMBER_MAX];
dss::Fix32 cmn::PartyMoveAction::memberSpeed_;
int cmn::PartyMoveAction::top_;
int cmn::PartyMoveAction::arrayCount_;
int cmn::PartyMoveAction::countPartyArray_;
int cmn::PartyMoveAction::countRFix_;
int cmn::PartyMoveAction::countLFix_;
dss::Fix32Vector3 cmn::PartyMoveAction::bashaLPos_;
short cmn::PartyMoveAction::bashaLIdx_;
dss::Fix32Vector3 cmn::PartyMoveAction::bashaRPos_;
short cmn::PartyMoveAction::bashaRIdx_;
short cmn::PartyMoveAction::prevDirIdx_;
cmn::PartyMoveAction::PARTY_ACTION_STATE cmn::PartyMoveAction::state_;

namespace cmn
{
    const dss::Fix32 minDistance = dss::Fix32(1L) / 32;
    const dss::Fix32 standardDis(0x19a);
    const dss::Fix32 stantardSpeed(0x19a);
    const dss::Fix32 standardSpace(0x666);
} // namespace cmn

THUMB void cmn::PartyMoveAction::initialize()
{
    trajectoryClear();
    for (int i = 0; i < PARTY_MEMBER_MAX; i++) {
        partyData_[i].position.set(0, 0, 0);
        partyData_[i].maxDist = standardDis * 8;
        partyData_[i].orgDist = standardDis * 8;
        partyData_[i].direction = 0;
        partyData_[i].state = 0;
        partyData_[i].front = standardSpace;
        partyData_[i].back = standardSpace;
        partyData_[i].right = standardSpace;
        partyData_[i].left = standardSpace;
        setDistance(i);
    }
    formation_ = 0;
    memberSpeed_ = stantardSpeed;
    formationDir_ = 0;
}

THUMB void cmn::PartyMoveAction::trajectoryClear()
{
    for (int i = 0; i < MOVE_ARRAY_MAX; i++) {
        posArray_[i].set(0, 0, 0);
        dirArray_[i] = 0;
        distArray_[i] = 0L;
    }
    top_ = 0;
    arrayCount_ = 0;
}

THUMB void cmn::PartyMoveAction::setAllMemberPos(dss::Fix32Vector3& pos, short idx)
{
    if (status::PartyStatusUtility::isSeparate() != true) {
        for (int i = 0; i < MOVE_ARRAY_MAX; i++) {
            posArray_[i] = pos;
            dirArray_[i] = idx;
            distArray_[i] = 0L;
        }
        top_ = 0;
        arrayCount_ = MOVE_ARRAY_MAX;
    }
    for (int i = 0; i < PARTY_MEMBER_MAX; i++) {
        setMemberPos(i, pos);
        setMemberDir(i, idx);
        setMemberPrevPos(i, pos);
        setMemberPrevDir(i, idx);
    }
    countPartyArray_ = 0;
    countRFix_ = 0;
    countLFix_ = 0;
    bashaLIdx_ = idx;
    bashaRIdx_ = idx;
    bashaLPos_ = pos;
    bashaRPos_ = pos;
    prevDirIdx_ = idx;
}

THUMB inline void cmn::PartyMoveAction::setMemberPos(int index, dss::Fix32Vector3& position)
{
    partyData_[index].position = position;
}

THUMB void cmn::PartyMoveAction::setNextArray(dss::Fix32Vector3& position, short& dir)
{
    partyData_[0].prevPosition = partyData_[0].position;
    partyData_[0].prevDirection = partyData_[0].direction;
    partyData_[0].position = position;
    if ((partyData_[0].state & 1) == 0) {
        partyData_[0].direction = dir;
    }
    if (status::PartyStatusUtility::isSeparate() != true) {
        dss::Fix32Vector3 vec = position - posArray_[top_];
        dss::Fix32 vecLen = vec.lengthsq();
        dss::Fix32 tvec = memberSpeed_ - minDistance;
        if (tvec * tvec < vecLen) {
            vecLen = memberSpeed_;
        } else {
            vecLen = vecLen.sqrt();
        }
        if (vecLen > minDistance) {
            if (formation_ == 1) {
                for (int i = 0; i < MOVE_ARRAY_MAX; i++) {
                    dirArray_[i] = formationDir_;
                }
                formation_ = 0;
            }
            top_++;
            arrayCount_++;
            arrayCount_ = dss::min<int>(arrayCount_, MOVE_ARRAY_MAX);
            if (top_ >= MOVE_ARRAY_MAX) {
                top_ = 0;
            }
            posArray_[top_] = position;
            dirArray_[top_] = dir;
            distArray_[top_] = vecLen;
        }
    }
}

THUMB void cmn::PartyMoveAction::moveNormalUpdate()
{
    if (status::PartyStatusUtility::isSeparate() == true) {
        return;
    }
    int memberCount = dss::max<int>(5, getMemberCount());
    dss::Fix32 tDistArray;
    int counter = 0;
    int i = 1;
    int no = top_ - 1;
    for (; counter < arrayCount_; counter++, no--) {
        if (no < 0) {
            no = MOVE_ARRAY_MAX - 1;
        }
        tDistArray.value += distArray_[no].value;
        if (tDistArray.value >= partyData_[i].maxDist.value) {
            if (partyData_[i].maxDist == dss::Fix32(0L)) {
                partyData_[i].prevPosition = partyData_[i].position;
                partyData_[i].prevDirection = partyData_[i].direction;
                partyData_[i].position = partyData_[i - 1].position;
                partyData_[i].direction = partyData_[i - 1].direction;
                i++;
            } else if (no != top_) {
                partyData_[i].prevPosition = partyData_[i].position;
                partyData_[i].prevDirection = partyData_[i].direction;
                partyData_[i].position = posArray_[no];
                tDistArray = 0L;
                if ((partyData_[i].state & 1) == 0) {
                    partyData_[i].direction = dirArray_[no];
                }
                i++;
            }
            if (i >= memberCount) {
                break;
            }
        }
    }
    if (i < memberCount) {
        for (; i < memberCount; i++) {
            partyData_[i].position = partyData_[i].prevPosition;
            partyData_[i].direction = partyData_[i].prevDirection;
        }
    }
}

THUMB void cmn::PartyMoveAction::moveToFirstUpdate()
{
    bool ret = false;
    dss::Fix32 unkSpeed(0x29);
    int count = getMemberCount();
    if (partyData_[0].position == partyData_[0].prevPosition) {
        ret = true;
        partyData_[0].maxDist = 0L;
        for (int i = 1; i < count; i++) {
            if (i > 1 && partyData_[i - 1].position != partyData_[i - 2].position) {
                break;
            }
            if (partyData_[i - 1].maxDist == dss::Fix32(0L)) {
                if ((partyData_[i].position - partyData_[i - 1].position).lengthsq() < memberSpeed_) {
                    partyData_[i].maxDist = 0L;
                    partyData_[i].position = partyData_[i - 1].position;
                } else {
                    partyData_[i].maxDist -= memberSpeed_;
                }
                if (partyData_[i].maxDist < dss::Fix32(0L)) {
                    partyData_[i].maxDist = 0L;
                    partyData_[i].position = partyData_[i - 1].position;
                }
                if (partyData_[i].maxDist > dss::Fix32(0L)) {
                    ret = false;
                }
            }
            if (partyData_[i].position != partyData_[i - 1].position) {
                ret = false;
            }
        }
    }
    moveNormalUpdate();
    if (ret == true) {
        for (int i = 0; i < count; i++) {
            partyData_[i].maxDist = partyData_[i].orgDist;
        }
        setAllMemberPos(partyData_[0].position, partyData_[0].direction);
        setPartyState(MOVE_NORMAL);
    }
}

THUMB void cmn::PartyMoveAction::setCharaDistance(int index, dss::Fix32 front, dss::Fix32 back, dss::Fix32 right, dss::Fix32 left)
{
    partyData_[index].front = front;
    partyData_[index].back = back;
    partyData_[index].right = right;
    partyData_[index].left = left;
    setDistance(index);
    if (index < PARTY_MEMBER_MAX - 1) {
        setDistance(index + 1);
    }
}

THUMB void cmn::PartyMoveAction::setDistance(int index)
{
    if (index != 0) {
        partyData_[index].orgDist = partyData_[index - 1].back + partyData_[index].front;
        partyData_[index].maxDist = partyData_[index].orgDist;
        if (data_02101c88.isCurrentPart(6) == 1 && index == 6) {
            partyData_[index].orgDist = partyData_[3].back + partyData_[index].front;
            partyData_[index].maxDist = partyData_[index].orgDist;
        }
    }
}

THUMB dss::Fix32 cmn::PartyMoveAction::getDistance(int index, int type)
{
    switch (type) {
    case 0:
        return partyData_[index].front;
    case 1:
        return partyData_[index].back;
    case 2:
        return partyData_[index].right;
    case 3:
        return partyData_[index].left;
    }
    return dss::Fix32(0L);
}

THUMB void cmn::PartyMoveAction::moveParallelUpdate()
{
    if (moveCounter_ >= endMoveFrame_) {
        moveVec_ = target_ - partyData_[0].position;
        setPartyState(MOVE_NORMAL);
    }
    for (int i = 0; i < MOVE_ARRAY_MAX; i++) {
        posArray_[i] += moveVec_;
    }
    for (int i = 0; i < PARTY_MEMBER_MAX; i++) {
        partyData_[i].position += moveVec_;
    }
    g_cmnPartyInfo.setPosition(partyData_[0].position);
    moveCounter_++;
}

THUMB void cmn::PartyMoveAction::setParallelMove(dss::Fix32Vector3& target, int frame)
{
    setPartyState(MOVE_TO_PARALLEL);
    endMoveFrame_ = frame;
    moveCounter_ = 0;
    target_ = target;
    moveVec_ = target_ - g_cmnPartyInfo.position_;
    partyData_[0].position = g_cmnPartyInfo.position_;
    moveVec_ /= frame;
}
