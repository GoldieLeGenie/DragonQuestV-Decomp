#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace status
{
    struct UseActionFlag {
        static const unsigned int FLAG_BREAK_PRAY_RING = 0x1;
        static const unsigned int FLAG_FAILED_NO_USE_MP = 0x2;
        static const unsigned int FLAG_CALLFRIEND = 0x4;
        static const unsigned int FLAG_ZAORARU_INVALID = 0x8;

        static dss::Flag flag_;
        static int eventBattle_;
        static int timeReverseFlag_;
        static int doubleFlag_;
        static int multiFlag_;
        static int workParam_[4];
        static short execActionCount_[500];

        UseActionFlag();
        ~UseActionFlag();
        static void clear();
        static void setBreakPrayRing(bool flag);
        static bool isBreakPrayRing();
        static void setFailedNoUseMp(bool flag);
        static bool isFailedNoUseMp();
        static void setZaoraruInvalid(bool flag);
        static bool isZaoraruInvalid();
        static void setCallFriend(bool flag, int monsterGroup, int monsterIndex);
        static bool isCallFriend();
        static int getCallFriendMonsterGroup();
        static int getCallFriendMonsterIndex();
        static void addExecActionCount(int actionIndex);
        static int getExecActionCount(int actionIndex);
        static void clearExecActionCount();
        static void setMultiAttack(bool flag);
        static bool isMultiAttack();
        static bool isEventBattle();
        static bool isDouble();
        static void setTimeReverse(bool flag);
        static void setWorkParam(int index, int param);
    };
} // namespace status
