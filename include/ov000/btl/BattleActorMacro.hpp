#pragma once
#include <globaldefs.h>

namespace status {
    struct CharacterStatus;
    struct UseActionParam;
}

namespace btl {
    struct BattleActorMacro {
        static void setExecMacro(status::UseActionParam& useActionParam);
        static void setResultMacro(status::UseActionParam& useActionParam, int currentTarget);
        static void setMacroActor(status::CharacterStatus* actor, int actionIndex);
        static void setMacroTarget(status::CharacterStatus* target, int actionIndex, int currentTarget);
        static void setAddMacro(status::UseActionParam& useActionParam, int currentTarget);
    };
}
