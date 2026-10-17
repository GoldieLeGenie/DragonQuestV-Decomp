#pragma ipa file
#include "main/cmn/MoveBase.hpp"
#include "main/cmn/ActionBase.hpp"
#include "main/cmn/CommonPartyInfo.hpp"

inline short& cmn::CommonPartyInfo::getDirIdx2()
{
    return dirIdx_;
}

dss::Fix32Vector3& cmn::ActionBase::position_ = g_cmnPartyInfo.position_;
short& cmn::ActionBase::dirIdx_ = g_cmnPartyInfo.getDirIdx2();
const dss::Fix32 cmn::MoveBase::grav(0x29);

THUMB void cmn::MoveBase::setup()
{
    endMoveFrame_ = 0;
    endRotFrame_ = 0;
    moveCounter_ = 0;
    rotCounter_ = 0;
    actionFlag_.clear();
    moveType_ = 0;
}

THUMB void cmn::MoveBase::execMove(dss::Fix32Vector3& pos)
{
    switch (moveType_) {
        case 1:
            simpleMove(pos);
            break;
        case 2:
            moveVibMotion(pos);
            break;
        case 3:
            shakeExecute(pos);
            break;
        case 4:
            jumpExecute(pos);
            break;
        case 5:
            moveAddExecute(pos);
            break;
        case 6:
            dirMoveExec(pos);
            break;
        case 7:
            execWait();
            break;
    }
}

THUMB void cmn::MoveBase::execRot(dss::Vector3<short>& rot)
{
    simpleRot(rot);
}

THUMB bool cmn::MoveBase::moveUpdate()
{
    switch (moveType_) {
        case 1:
            return simpleMoveUpdate();
        case 2:
            return updateVibMotion();
        case 3:
            return updateShake();
        case 4:
            return updateJump();
        case 5:
            return updateMoveAdd();
        case 6:
            return updateDirMove();
        case 7:
            return updateWait();
    }
    return false;
}

THUMB bool cmn::MoveBase::rotUpdate()
{
    return simpleRotUpdata();
}

THUMB bool cmn::MoveBase::isEnd()
{
    if (actionFlag_.check(1) == false && actionFlag_.check(2) == false) {
        return true;
    }
    return false;
}

THUMB void cmn::MoveBase::setActionMove(dss::Fix32Vector3& start, dss::Fix32Vector3& target)
{
    moveType_ = 1;
    startPos_ = start;
    targetPos_ = target;
    actionFlag_.set(1);
    moveCounter_ = 0;
}

THUMB void cmn::MoveBase::setActionRot(dss::Vector3<short>& start, dss::Vector3<short>& target)
{
    moveType_ = 1;
    startDirIdx_ = start;
    targetDirIdx_ = target;
    actionFlag_.set(2);
    rotCounter_ = 0;
}

THUMB void cmn::MoveBase::setMoveSpeed(dss::Fix32 speed)
{
    moveVec_ = targetPos_ - startPos_;
    dss::Fix32 frame = moveVec_.length() / speed;
    endMoveFrame_ = frame.value / 0x1000;
    setMoveFrame(endMoveFrame_);
}

THUMB void cmn::MoveBase::setMoveFrame(int frame)
{
    endMoveFrame_ = frame;
    int div = dss::max<int>(frame, 1);
    moveVec_ = (targetPos_ - startPos_) / div;
}

THUMB void cmn::MoveBase::setRotFrame(int frame, int type)
{
    endRotFrame_ = frame;
    rotIdx_.vx = (short)(targetDirIdx_.vx - startDirIdx_.vx);
    rotIdx_.vy = (short)(targetDirIdx_.vy - startDirIdx_.vy);
    rotIdx_.vz = (short)(targetDirIdx_.vz - startDirIdx_.vz);
    if (frame != 0) {
        rotIdx_.vx = setRot(rotIdx_.vx, frame, type);
        rotIdx_.vy = setRot(rotIdx_.vy, frame, type);
        rotIdx_.vz = setRot(rotIdx_.vz, frame, type);
    }
}

THUMB short cmn::MoveBase::setRot(short rot, int frame, int type)
{
    if (rot == 0) {
        return rot;
    }
    switch (type) {
        case 1:
            if (rot >= 0) {
                rot = (unsigned short)(0xffff - rot);
                rot *= -1;
            }
            break;
        case 2:
            if (rot <= 0) {
                rot = (unsigned short)rot;
            }
            break;
    }
    return rot;
}

THUMB void cmn::MoveBase::simpleMove(dss::Fix32Vector3& pos)
{
    if (actionFlag_.check(1) == true) {
        if (moveCounter_ < endMoveFrame_) {
            if (actionFlag_.check(0x40) == true) {
                pos = startPos_ + moveVec_ * moveCounter_;
            } else {
                pos = (startPos_ * (endMoveFrame_ - moveCounter_) + targetPos_ * moveCounter_) / endMoveFrame_;
            }
        } else {
            pos = targetPos_;
            actionFlag_.remove(0x40);
        }
    }
}

THUMB void cmn::MoveBase::simpleRot(dss::Vector3<short>& rot)
{
    if (actionFlag_.check(2) == true) {
        if (rotCounter_ < endRotFrame_) {
            rot.vx = targetDirIdx_.vx * rotCounter_ / endRotFrame_ + startDirIdx_.vx * (endRotFrame_ - rotCounter_) / endRotFrame_;
            rot.vy = startDirIdx_.vy + rotIdx_.vy * rotCounter_ / endRotFrame_;
            rot.vz = startDirIdx_.vz + rotIdx_.vz * rotCounter_ / endRotFrame_;
        } else {
            rot = targetDirIdx_;
        }
    }
}

THUMB void cmn::MoveBase::setSimpleRot(dss::Vector3<short>& start, dss::Vector3<short>& add, int frame)
{
    endRotFrame_ = frame;
    startDirIdx_ = start;
    targetDirIdx_.vx = start.vx + add.vx * frame;
    targetDirIdx_.vy = start.vy + add.vy * frame;
    targetDirIdx_.vz = start.vz + add.vz * frame;
    rotIdx_.vx = add.vx * frame;
    rotIdx_.vy = add.vy * frame;
    rotIdx_.vz = add.vz * frame;
    rotCounter_ = 0;
    actionFlag_.set(2);
}

THUMB void cmn::MoveBase::setRotSpeedY(short speed)
{
    rotIdx_.vx = 0;
    rotIdx_.vy = (short)(targetDirIdx_.vy - startDirIdx_.vy);
    endRotFrame_ = rotIdx_.vy / speed;
    endRotFrame_ = dss::abs<short>(endRotFrame_);
    rotIdx_.vz = 0;
    rotIdx_.vy = setRot(rotIdx_.vy, endRotFrame_, 0);
    rotCounter_ = 0;
    actionFlag_.set(2);
}

template <>
THUMB short dss::abs<short>(short a)
{
    if (a < 0) {
        return -a;
    }
    return a;
}

THUMB bool cmn::MoveBase::simpleMoveUpdate()
{
    if (actionFlag_.check(1) == true) {
        if (moveCounter_ > endMoveFrame_) {
            actionFlag_.remove(1);
            return true;
        }
        moveCounter_++;
    } else {
        return true;
    }
    return false;
}

THUMB bool cmn::MoveBase::simpleRotUpdata()
{
    if (actionFlag_.check(2) == true) {
        if (rotCounter_ > endRotFrame_) {
            actionFlag_.remove(2);
            return true;
        }
        rotCounter_++;
    } else {
        return true;
    }
    return false;
}

namespace cmn
{
    static dss::Fix32Vector3 shakeOffset;
}

THUMB void cmn::MoveBase::setVibMotion(dss::Fix32Vector3& start, dss::Fix32Vector3& target, int amp, int damp, int frame)
{
    endMoveFrame_ = frame;
    startPos_ = start;
    targetPos_ = start;
    moveVec_ = (target - start) * 4 / 8;
    moveCounter_ = 0;
    dampFrame_ = damp;
    ampFrame_ = amp;
    moveType_ = 2;
    actionFlag_.set(1);
    shakeOffset.set(0, 0, 0);
}

THUMB void cmn::MoveBase::moveVibMotion(dss::Fix32Vector3& pos)
{
    int frame = moveCounter_ % 8;
    int sign = (frame < 4) ? 1 : -1;
    int count = frame % 4;
    if (count >= 2) {
        count = 4 - count;
    }
    dss::Fix32Vector3 vec = moveVec_ * (sign * count) / 2;
    if (moveCounter_ < ampFrame_) {
        vec = vec * moveCounter_ / ampFrame_;
    } else if (moveCounter_ > dampFrame_) {
        vec = vec * (endMoveFrame_ - moveCounter_) / (endMoveFrame_ - dampFrame_);
    }
    shakeOffset += vec;
    if (actionFlag_.check(4) == true) {
        pos += shakeOffset;
    } else {
        pos += vec;
    }
    if (moveCounter_ >= endMoveFrame_) {
        pos -= shakeOffset;
    }
}

THUMB bool cmn::MoveBase::updateVibMotion()
{
    if (moveCounter_ >= endMoveFrame_) {
        actionFlag_.remove(1);
        return true;
    }
    moveCounter_++;
    return false;
}

namespace cmn
{
    static dss::Fix32 randomL(0x10a);
}

THUMB void cmn::MoveBase::setRandomShake(dss::Fix32Vector3& start, dss::Fix32Vector3& target, int count)
{
    moveType_ = 3;
    dampFrame_ = 0;
    moveCounter_ = 0;
    endMoveFrame_ = 2;
    startPos_ = start;
    dss::Fix32Vector3 vec = target - start;
    vec.normalize();
    vec *= randomL;
    targetPos_ = start + vec;
    ampFrame_ = count * 6;
    moveVec_ = getShakeVec(dampFrame_);
    actionFlag_.set(1);
    shakeOffset.set(0, 0, 0);
}

THUMB void cmn::MoveBase::shakeExecute(dss::Fix32Vector3& pos)
{
    shakeOffset += moveVec_;
    if (actionFlag_.check(4) == true) {
        pos += shakeOffset;
    } else {
        pos += moveVec_;
    }
    if (moveCounter_ == endMoveFrame_ && dampFrame_ == ampFrame_) {
        pos -= shakeOffset;
        shakeOffset.set(0, 0, 0);
    }
}

THUMB bool cmn::MoveBase::updateShake()
{
    if (moveCounter_ >= endMoveFrame_) {
        dampFrame_++;
        if (dampFrame_ > ampFrame_) {
            moveType_ = 0;
            actionFlag_.remove(1);
            return true;
        }
        moveVec_ = getShakeVec(dampFrame_ % 6);
        moveCounter_ = 0;
        return false;
    }
    moveCounter_++;
    return false;
}

THUMB dss::Fix32Vector3 cmn::MoveBase::getShakeVec(int index)
{
    dss::Fix32Vector3 vec[2];
    vec[0] = targetPos_ - startPos_;
    vec[0].normalize();
    vec[0] *= randomL;
    vec[1].set(dss::Fix32(0L), randomL, dss::Fix32(0L));
    static const int add0[6] = {1, -2, 1, 1, -2, 1};
    static const int add1[6] = {1, 0, -1, -1, 0, 1};
    return vec[0] * add0[index] + vec[1] * add1[index];
}

THUMB void cmn::MoveBase::setJumpMove(dss::Fix32Vector3& start, dss::Fix32Vector3& target, int frame)
{
    startPos_ = start;
    targetPos_ = target;
    endMoveFrame_ = frame;
    moveCounter_ = 0;
    moveVec_ = target - start;
    moveVec_.vy += grav * frame * frame / 2;
    moveVec_ /= frame;
    moveType_ = 4;
    actionFlag_.set(1);
}

THUMB void cmn::MoveBase::jumpExecute(dss::Fix32Vector3& pos)
{
    pos += moveVec_;
    moveVec_.vy -= grav;
    if (moveCounter_ >= endMoveFrame_) {
        pos = targetPos_;
    }
}

THUMB bool cmn::MoveBase::updateJump()
{
    if (moveCounter_ >= endMoveFrame_) {
        actionFlag_.remove(1);
        return true;
    }
    moveCounter_++;
    return false;
}

namespace cmn
{
    static dss::Fix32Vector3 unk_020a1438;
}

THUMB void cmn::MoveBase::setAddMove(dss::Fix32Vector3& start, dss::Fix32Vector3& target, int frame)
{
    endMoveFrame_ = frame;
    moveCounter_ = 0;
    moveVec_ = target - start;
    if (frame != 0) {
        moveVec_ /= frame;
    }
    moveType_ = 5;
    actionFlag_.set(1);
}

THUMB void cmn::MoveBase::moveAddExecute(dss::Fix32Vector3& pos)
{
    pos += moveVec_;
}

THUMB bool cmn::MoveBase::updateMoveAdd()
{
    moveCounter_++;
    if (moveCounter_ >= endMoveFrame_) {
        actionFlag_.remove(1);
        moveType_ = 0;
        return true;
    }
    return false;
}

THUMB void cmn::MoveBase::dirMoveExec(dss::Fix32Vector3& pos)
{
    pos += moveVec_;
    dss::Fix32 dist;
    dss::Fix32 speed;
    if (targetPos_.vx != dss::Fix32(0L)) {
        dist = targetPos_.vx - pos.vx;
        speed = moveVec_.vx;
    } else {
        dist = targetPos_.vy - pos.vy;
        speed = moveVec_.vy;
    }
    if (dss::abs<long>(dist.value) < dss::abs<long>(speed.value)) {
        moveCounter_ = 0;
    }
}

template <>
THUMB long dss::abs<long>(long a)
{
    if (a < 0) {
        return -a;
    }
    return a;
}

THUMB bool cmn::MoveBase::updateDirMove()
{
    if (moveCounter_ == 0) {
        actionFlag_.remove(1);
        moveType_ = 0;
        return true;
    }
    return false;
}

THUMB void cmn::MoveBase::setDirMove(dss::Fix32 value, int dir, dss::Fix32 speed)
{
    actionFlag_.remove(1);
    moveType_ = 6;
    moveCounter_ = 1;
    targetPos_.set(0, 0, 0);
    moveVec_.set(0, 0, 0);
    switch (dir) {
        case 0:
            moveVec_.vy = speed;
            targetPos_.vy = value;
            break;
        case 1:
            moveVec_.vx = speed;
            targetPos_.vx = value;
            break;
        case 2:
            moveVec_.vy = speed * -1;
            targetPos_.vy = value;
            break;
        case 3:
            moveVec_.vx = speed * -1;
            targetPos_.vx = value;
            break;
    }
}

THUMB void cmn::MoveBase::setMoveLock(bool flag)
{
    if (flag == true) {
        actionFlag_.set(4);
    } else {
        actionFlag_.remove(4);
    }
}

THUMB void cmn::MoveBase::execWait()
{
}

THUMB bool cmn::MoveBase::updateWait()
{
    if (moveCounter_ >= endMoveFrame_) {
        actionFlag_.remove(1);
        moveType_ = 0;
        return true;
    }
    moveCounter_++;
    return false;
}

THUMB dss::Vector3<short> cmn::MoveBase::getRotIdx()
{
    dss::Vector3<short> rot;
    rot.vx = rotIdx_.vx / endRotFrame_;
    rot.vy = rotIdx_.vy / endRotFrame_;
    rot.vz = rotIdx_.vz / endRotFrame_;
    return rot;
}

THUMB void cmn::MoveBase::setRough(bool flag)
{
    if (flag == true) {
        actionFlag_.set(0x40);
    } else {
        actionFlag_.remove(0x40);
    }
}
