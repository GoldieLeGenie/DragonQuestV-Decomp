#pragma once
#include <globaldefs.h>
#include "main/task/BaseTask.hpp"

namespace btl {
    struct EncountTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct StatusTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct FirstReorderTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct BattleEndTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct StadiumEndTask : BaseTask {
        int messageCount_;                      // 0x08

        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        void setCount(int count);
    };

    struct StadiumDrawTask : BaseTask {
        int messageCount_;                      // 0x08

        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        void setCount(int count);
    };

    struct ExitTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct StadiumResultTask : BaseTask {
        int messageCount_;                      // 0x08

        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        void setCount(int count);
    };

    struct CommandTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct EscapeTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct TimeReverseEndTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct TimeReverseTask : BaseTask {
        int counter_;                           // 0x08

        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct DemolitionTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct ExitWaitTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct PartyReorderTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct FirstAttackTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };

    struct RoundTask : BaseTask {
        int waitFlag_;                          // 0x08

        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        void setWaitFlag(bool flag);
    };

    struct RoundEndTask : BaseTask {
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
    };
}
