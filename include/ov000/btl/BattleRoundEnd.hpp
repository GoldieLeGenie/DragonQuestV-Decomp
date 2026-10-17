#pragma once
#include <globaldefs.h>
#include "main/task/ExecTask.hpp"

namespace btl {
    struct BattleTaskOracle : ExecTask2 {
        int sortIndex_;                             // 0x0C

        BattleTaskOracle();
        ~BattleTaskOracle();
        virtual void setup();
        virtual void cleanup();
        void setSortIndex(int sortIndex);
    };

    struct BattleTaskVenom : ExecTask2 {
        int sortIndex_;                             // 0x0C

        BattleTaskVenom();
        ~BattleTaskVenom();
        virtual void setup();
        virtual void cleanup();
        void setSortIndex(int sortIndex);
    };

    struct BattleTaskMysteriousArmor : ExecTask2 {
        int sortIndex_;                             // 0x0C

        BattleTaskMysteriousArmor();
        ~BattleTaskMysteriousArmor();
        virtual void setup();
        virtual void cleanup();
        void setSortIndex(int sortIndex);
    };

    struct BattleTaskVenom2 : ExecTask2 {
        int sortIndex_;                             // 0x0C

        BattleTaskVenom2();
        ~BattleTaskVenom2();
        virtual void setup();
        virtual void cleanup();
        void setSortIndex(int sortIndex);
    };

    struct BattleExecVenom : ExecTaskManager2 {
        BattleTaskVenom battleTaskVenom_[4];        // 0x04C
        BattleTaskVenom2 battleTaskVenom2_[12];     // 0x08C

        virtual void initialize_user();
        virtual void terminate_user();
    };

    struct BattleExecMysteriousArmor : ExecTaskManager2 {
        BattleTaskMysteriousArmor battleTaskMysteriousArmor_[4];    // 0x4C

        virtual void initialize_user();
        virtual void terminate_user();
    };

    struct BattleExecOracle : ExecTaskManager2 {
        BattleTaskOracle battleTaskOracle_[4];      // 0x4C

        virtual void initialize_user();
        virtual void terminate_user();
    };

    struct BattleTaskLifeRing : ExecTask2 {
        int sortIndex_;                             // 0x0C

        BattleTaskLifeRing();
        ~BattleTaskLifeRing();
        virtual void setup();
        virtual void cleanup();
        void setSortIndex(int sortIndex);
    };

    struct BattleRoundEndVenom : ExecTask2 {
        BattleExecVenom battleExecVenom_;           // 0x00C

        virtual void setup();
        virtual void cleanup();
        virtual bool isEnd();
        bool isEnable();
    };

    struct BattleExecLifeRing : ExecTaskManager2 {
        BattleTaskLifeRing battleTaskLifeRing_[4];  // 0x4C

        virtual void initialize_user();
        virtual void terminate_user();
    };

    struct BattleRoundEndLifeRing : ExecTask2 {
        BattleExecLifeRing battleExecLifeRing_;     // 0x0C

        virtual void setup();
        virtual void cleanup();
        virtual bool isEnd();
        bool isEnable();
    };

    struct BattleRoundEndMysteriousArmor : ExecTask2 {
        BattleExecMysteriousArmor battleExecMysteriousArmor_;   // 0x0C

        virtual void setup();
        virtual void cleanup();
        virtual bool isEnd();
        bool isEnable();
    };

    struct BattleRoundEndOracle : ExecTask2 {
        BattleExecOracle battleExecOracle_;         // 0x0C

        virtual void setup();
        virtual void cleanup();
        virtual bool isEnd();
        bool isEnable();
    };

    struct BattleRoundEndAstoron : ExecTask2 {
        virtual void setup();
        virtual void cleanup();
        bool isEnable();
    };

    struct BattleRoundEnd : ExecTaskManager2 {
        BattleRoundEndVenom venom_;                         // 0x04C
        BattleRoundEndLifeRing lifeRing_;                   // 0x1A4
        BattleRoundEndMysteriousArmor mysteriousArmor_;     // 0x23C
        BattleRoundEndOracle oracle_;                       // 0x2D4
        BattleRoundEndAstoron astoron_;                     // 0x36C

        virtual void initialize_user();
        virtual void terminate_user();
    };
}
