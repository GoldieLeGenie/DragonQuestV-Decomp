#pragma once
#include <globaldefs.h>

namespace status {
    struct UseActionParam;
}

namespace btl {
    struct BattleActorSound {
        static void playActionStartSound(status::UseActionParam& useActionParam);
        static void playActionResultSound(status::UseActionParam& useActionParam, int currentTarget);
        static void playCriticalSound(status::UseActionParam& useActionParam);
    };
}
