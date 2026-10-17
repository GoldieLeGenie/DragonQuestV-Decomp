#pragma once
#include <globaldefs.h>
#include "main/task/ExecTask.hpp"

namespace btl {
    struct BattleTaskCallFriend : ExecTask2 {
        virtual void setup();
        virtual void cleanup();
        virtual bool isEnd();
    };

    struct BattleExecRoundStart : ExecTaskManager2 {
        BattleTaskCallFriend battleTaskCallFriend_; // 0x4C

        virtual void initialize_user();
        virtual void terminate_user();
    };

    extern BattleExecRoundStart g_BattleExecRoundStart;
}
