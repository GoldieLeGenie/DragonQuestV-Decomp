#pragma once
#include <globaldefs.h>
#include "main/task/ExecTask.hpp"

namespace btl {
    struct BattleExecEncount : ExecTask {
        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecStatus : ExecTask {
        int monsterCount_;                          // 0x08
        int index_;                                 // 0x0C
        int group_;                                 // 0x10
        int all_;                                   // 0x14

        virtual void setup();
        virtual bool isEnd();
        void setupLast();
        bool isNext();
    };

    struct BattleExecFirstAttack : ExecTask {
        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecVictory00 : ExecTask {
        virtual void setup();
    };

    struct BattleExecVictory01 : ExecTask {
        virtual void setup();
    };

    struct BattleExecVictory02 : ExecTask {
        virtual void setup();
    };

    struct BattleExecVictory03 : ExecTask {
        virtual void setup();
    };

    struct BattleExecVictory20 : ExecTask {
        virtual void setup();
    };

    struct BattleExecVictory30 : ExecTask {
        int monsterIndex_;                          // 0x08
        int itemIndex_;                             // 0x0C

        virtual void setup();
        void setMonsterIndex(int monsterIndex);
        void setItemIndex(int itemIndex);
    };

    struct BattleExecVictory31 : ExecTask {
        virtual void setup();
    };

    struct BattleExecVictory31a : ExecTask {
        int itemIndex_;                             // 0x08

        virtual void setup();
        void setItemIndex(int itemIndex);
    };

    struct BattleExecVictory32 : ExecTask {
        int itemIndex_;                             // 0x08

        virtual void setup();
        void setItemIndex(int itemIndex);
    };

    struct BattleExecVictory33 : ExecTask {
        int playerIndex_;                           // 0x08

        virtual void setup();
        virtual bool isEnd();
        void setPlayerIndex(int playerIndex);
    };

    struct BattleExecVictory34 : ExecTask {
        int playerIndex_;                           // 0x08

        virtual void setup();
        virtual bool isEnd();
        void setPlayerIndex(int playerIndex);
    };

    struct BattleExecVictory35 : ExecTask {
        int playerIndex_;                           // 0x08

        virtual void setup();
        virtual bool isEnd();
        void setPlayerIndex(int playerIndex);
    };

    struct BattleExecVictory36 : ExecTask {
        int playerIndex_;                           // 0x08

        virtual void setup();
        virtual bool isEnd();
        void setPlayerIndex(int playerIndex);
    };

    struct BattleExecVictory37 : ExecTask {
        virtual void setup();
        virtual void cleanup();
    };

    struct BattleExecVictory38 : ExecTask {
        int counter_;                               // 0x08

        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecVictory39 : ExecTask {
        virtual void setup();
    };

    struct BattleExecVictory40 : ExecTask {
        int counter_;                               // 0x08

        virtual void setup();
        virtual void cleanup();
        virtual bool isEnd();
    };

    struct BattleExecEvent00 : ExecTask {
        int counter_;                               // 0x08

        virtual void setup();
        virtual void cleanup();
        virtual bool isEnd();
        int setupMonster(int group);
        int getRealVelorinman();
    };

    struct BattleExecEvent00b : ExecTask {
        int counter_;                               // 0x08

        static const int COUNT;

        virtual void setup();
        virtual void cleanup();
        virtual bool isEnd();
        void move();
    };

    struct BattleExecEvent14 : ExecTask {
        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecEvent15 : ExecTask {
        int counter;                                // 0x08

        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecMonster00 : ExecTask {
        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecMonster01 : ExecTask {
        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecMonster02 : ExecTask {
        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecMonster03 : ExecTask {
        virtual void setup();
        virtual bool isEnd();
    };

    struct BattleExecMonsterEscape : ExecTaskManager {
        BattleExecVictory02 battleExecVictory02;    // 0x4C

        virtual void initialize();
        void terminate();
    };

    struct BattleExecMonsterDisappear : ExecTaskManager {
        BattleExecVictory03 battleExecVictory03;    // 0x4C

        virtual void initialize();
        void terminate();
    };

    struct BattleExecDefeatMonster : ExecTaskManager {
        BattleExecVictory00 battleExecVictory00;    // 0x4C
        BattleExecVictory01 battleExecVictory01;    // 0x54

        virtual void initialize();
        void terminate();
    };

    struct BattleExecExp : ExecTaskManager {
        BattleExecVictory01 battleExecVictory01;    // 0x4C

        virtual void initialize();
        void terminate();
    };

    struct BattleExecGold : ExecTaskManager {
        BattleExecVictory20 battleExecVictory20;    // 0x4C

        virtual void initialize();
        void terminate();
    };

    struct BattleExecItem : ExecTaskManager {
        BattleExecVictory30 battleExecVictory30;    // 0x4C
        BattleExecVictory31 battleExecVictory31;    // 0x5C
        BattleExecVictory31a battleExecVictory31a;  // 0x64
        BattleExecVictory32 battleExecVictory32;    // 0x70

        virtual void initialize();
        void terminate();
    };

    struct BattleExecMonster : ExecTaskManager {
        BattleExecMonster00 battleExecMonster00;    // 0x4C
        BattleExecMonster01 battleExecMonster01;    // 0x54
        BattleExecMonster02 battleExecMonster02;    // 0x5C
        BattleExecMonster03 battleExecMonster03;    // 0x64

        virtual void initialize();
        void terminate();
    };

    struct BattleExecReorder : ExecTaskManager {
        BattleExecVictory33 battleExecVictory33;    // 0x4C
        BattleExecVictory34 battleExecVictory34;    // 0x58
        BattleExecVictory35 battleExecVictory35;    // 0x64
        BattleExecVictory36 battleExecVictory36;    // 0x70

        virtual void initialize();
    };

    struct BattleExecDemolition : ExecTaskManager {
        BattleExecVictory37 battleExecVictory37;    // 0x4C
        BattleExecVictory38 battleExecVictory38;    // 0x54
        BattleExecVictory39 battleExecVictory39;    // 0x60
        BattleExecVictory40 battleExecVictory40;    // 0x68

        virtual void initialize();
        void terminate();
    };

    struct BattleExecEscape : ExecTask {
        virtual void setup();
        virtual bool isEnd();
    };

    extern BattleExecEncount g_BattleExecEncount;
    extern BattleExecStatus g_BattleExecStatus;
    extern BattleExecFirstAttack g_BattleExecFirstAttack;
    extern BattleExecMonsterEscape g_BattleExecMonsterEscape;
    extern BattleExecMonsterDisappear g_BattleExecMonsterDisappear;
    extern BattleExecDefeatMonster g_BattleExecDefeatMonster;
    extern BattleExecExp g_BattleExecExp;
    extern BattleExecGold g_BattleExecGold;
    extern BattleExecItem g_BattleExecItem;
    extern BattleExecMonster g_BattleExecMonster;
    extern BattleExecReorder g_BattleExecReorder;
    extern BattleExecDemolition g_BattleExecDemolition;
    extern BattleExecEscape g_BattleExecEscape;
}
