#pragma once
#include <globaldefs.h>
#include "main/task/ExecTask.hpp"

namespace btl {
    void setMessage(int mes0, int mes1, int mes2, int mes3);

    struct BattleExecVictory10 : ExecTask {
        int index_;                             // 0x08
        int level_;                             // 0x0C

        virtual void setup();
        void setPlayerIndex(int index);
        void setLevel(int index);
    };

    struct BattleExecVictory13 : ExecTask {
        int strength_;                          // 0x08
        int agility_;                           // 0x0C
        int protection_;                        // 0x10
        int wisdom_;                            // 0x14
        int luck_;                              // 0x18

        virtual void setup();
        void setStatus(int st, int ag, int pr, int ws, int lk);
    };

    struct BattleExecVictory12a : ExecTask {
        int playerIndex_;                       // 0x08

        virtual void setup();
        void setPlayerIndex(int index);
    };

    struct BattleExecVictory16 : ExecTask {
        int counter_;                           // 0x08

        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecVictory15 : ExecTask {
        int playerIndex_;                       // 0x08
        int actionIndex_[5];                    // 0x0C
        int index_;                             // 0x20

        virtual void setup();
        void setPlayerIndex(int playerIndex);
        void setActionIndex(int index, int actionIndex);
        virtual void exec();
    };

    struct BattleExecVictory11 : ExecTask {
        int index_;                             // 0x08
        unsigned int hpMax_;                    // 0x0C

        virtual void setup();
        void setHpMax(int hp);
    };

    struct BattleExecVictory12 : ExecTask {
        int index_;                             // 0x08
        unsigned int mpMax_;                    // 0x0C

        virtual void setup();
        void setMpMax(int mp);
    };

    struct BattleExecLevelup : ExecTaskManager {
        BattleExecVictory10 battleExecVictory10;    // 0x4C
        BattleExecVictory11 battleExecVictory11;    // 0x5C
        BattleExecVictory12 battleExecVictory12;    // 0x6C
        BattleExecVictory12a battleExecVictory12a;  // 0x7C
        BattleExecVictory13 battleExecVictory13;    // 0x88
        BattleExecVictory15 battleExecVictory15;    // 0xA4
        BattleExecVictory16 battleExecVictory16;    // 0xC8

        virtual void initialize();
        void terminate();
        ~BattleExecLevelup();
    };

    extern BattleExecLevelup g_BattleExecLevelup;
}
