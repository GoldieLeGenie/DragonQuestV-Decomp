#include "main/status/UseActionFlag.hpp"

dss::Flag status::UseActionFlag::flag_;
int status::UseActionFlag::multiFlag_;
int status::UseActionFlag::doubleFlag_;
int status::UseActionFlag::timeReverseFlag_;
int status::UseActionFlag::eventBattle_;
int status::UseActionFlag::workParam_[4];
short status::UseActionFlag::execActionCount_[500];

THUMB status::UseActionFlag::UseActionFlag()
{
}

THUMB status::UseActionFlag::~UseActionFlag()
{
}

THUMB void status::UseActionFlag::clear()
{
    flag_.clear();
    clearExecActionCount();
}

THUMB void status::UseActionFlag::setBreakPrayRing(bool flag)
{
    if (flag) {
        flag_.set(FLAG_BREAK_PRAY_RING);
    } else {
        flag_.remove(FLAG_BREAK_PRAY_RING);
    }
}

THUMB bool status::UseActionFlag::isBreakPrayRing()
{
    return flag_.check(FLAG_BREAK_PRAY_RING);
}

THUMB void status::UseActionFlag::setFailedNoUseMp(bool flag)
{
    if (flag) {
        flag_.set(FLAG_FAILED_NO_USE_MP);
    } else {
        flag_.remove(FLAG_FAILED_NO_USE_MP);
    }
}

THUMB void status::UseActionFlag::setZaoraruInvalid(bool flag)
{
    if (flag) {
        flag_.set(FLAG_ZAORARU_INVALID);
    } else {
        flag_.remove(FLAG_ZAORARU_INVALID);
    }
}

THUMB bool status::UseActionFlag::isZaoraruInvalid()
{
    return flag_.check(FLAG_ZAORARU_INVALID);
}

THUMB void status::UseActionFlag::setCallFriend(bool flag, int monsterGroup, int monsterIndex)
{
    if (flag) {
        flag_.set(FLAG_CALLFRIEND);
    } else {
        flag_.remove(FLAG_CALLFRIEND);
    }
    workParam_[0] = monsterGroup;
    workParam_[1] = monsterIndex;
}

THUMB bool status::UseActionFlag::isCallFriend()
{
    return flag_.check(FLAG_CALLFRIEND);
}

THUMB int status::UseActionFlag::getCallFriendMonsterGroup()
{
    return workParam_[0];
}

THUMB int status::UseActionFlag::getCallFriendMonsterIndex()
{
    return workParam_[1];
}

THUMB void status::UseActionFlag::addExecActionCount(int actionIndex)
{
    execActionCount_[actionIndex]++;
}

THUMB void status::UseActionFlag::clearExecActionCount()
{
    for (int i = 0; i < 500; i++) {
        execActionCount_[i] = 0;
    }
}
