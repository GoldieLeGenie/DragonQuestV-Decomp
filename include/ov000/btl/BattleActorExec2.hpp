#pragma once
#include <globaldefs.h>
#include "main/task/BaseTask.hpp"
#include "ov000/btl/AfterMessageTask2.hpp"
#include "ov000/btl/BeforeMessageTask2.hpp"
#include "ov000/btl/ExecActionTask2.hpp"
#include "ov000/btl/ExecMessageTask2.hpp"
#include "ov000/btl/ResultMessageTask2.hpp"
#include "ov000/btl/SpecialMessageTask2.hpp"

namespace status {
    struct UseActionParam;
}

namespace btl {
    struct EndTask : BaseTask {
        static status::UseActionParam* useActionParam_;

        static void setup(status::UseActionParam* useActionParam);
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct BattleActionExec : SequentialTaskManager {
        BeforeMessageTask2 beforeMessageTask_;      // 0x8C
        ExecActionTask3 execActionTask_;            // 0x98
        ExecMessageTask2 execMessageTask_;          // 0xA4
        SpecialMessageTask2 specialMessageTask_;    // 0xB8
        ResultMessageTask2 resultMessageTask_;      // 0xC8
        AfterMessageTask2 afterMessageTask_;        // 0xDC
        EndTask endTask_;                           // 0xE8

        virtual void initialize_user();
        virtual void terminate_user();
    };

    struct BattleTargetExec : BaseTask {
        BattleActionExec battleActionExec_;         // 0x08
        int end_;                                   // 0xF8

        BattleTargetExec();
        ~BattleTargetExec();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual int isEnd();
    };

    struct AfterActionTask2 : BaseTask {
        int mess_;                                  // 0x08

        static status::UseActionParam* useActionParam_;

        static void setup(status::UseActionParam* useActionParam);
        bool isEnableStatusChange();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual int isEnd();
        bool isMessageStatusChangeRelease();
    };

    struct BattleActorFinish : SequentialTaskManager {
        AfterActionTask2 afterActionTask_;          // 0x8C

        virtual void initialize_user();
        virtual void terminate_user();
    };

    struct BattleActorExec2 : SequentialTaskManager {
        static const int TARGET_MAX = 16;

        status::UseActionParam* useActionParam_;    // 0x08C
        BattleTargetExec battleTargetExec_[TARGET_MAX]; // 0x090

        virtual void initialize_user();
        virtual void terminate_user();
        virtual void interruptResister(int index);
        void setup(status::UseActionParam* useActionParam);
        void cleanup();
    };
}
