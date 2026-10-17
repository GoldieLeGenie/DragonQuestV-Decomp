#pragma once
#include <globaldefs.h>

namespace status {
    struct UseActionParam;
}

namespace btl {
    struct BattleActorEffect {
        static int wait_;
        static int both_;

        static void setResultBothEffect(status::UseActionParam& useActionParam, int target);
        static void setExecEffect(status::UseActionParam& useActionParam);
        static bool checkCommonExecEffect(status::UseActionParam& useActionParam);
        static int setPlayerEffect(status::UseActionParam& useActionParam);
        static bool checkPlayerExecEffect(status::UseActionParam& useActionParam);
        static int setEnemyEffect(status::UseActionParam& useActionParam);
        static bool checkEnemyExecEffect(status::UseActionParam& useActionParam);
        static int setResultEnemyEffect(status::UseActionParam& useActionParam);
        static bool checkEnemyResultEffect(status::UseActionParam& useActionParam);
        static void setResultEffect(status::UseActionParam& useActionParam);
        static int setMegazaruEffect(status::UseActionParam& useActionParam);
    };
}
