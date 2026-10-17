#pragma once
#include <globaldefs.h>

namespace status {
    struct CharacterStatus;

    struct UseActionMacro {
        static void setBeforeMacro(CharacterStatus* actor, int actionIndex);
        static void setExecMacro(CharacterStatus* actor, CharacterStatus* target, int actionIndex);
        static void setResultMacro(CharacterStatus* actor, CharacterStatus* target, int actionIndex);
        static void setAddMacro(CharacterStatus* actor, CharacterStatus* target, int actionIndex);
        static void setStatusChangeMacro(CharacterStatus* actor);
    };

    extern int localizeTemp;
}
