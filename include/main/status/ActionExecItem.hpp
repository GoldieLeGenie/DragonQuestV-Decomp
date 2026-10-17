#pragma once
#include <globaldefs.h>

namespace status
{
    struct CharacterStatus;
    struct UseActionParam;

    struct ActionExecItem {
        static bool checkItemForceE(UseActionParam* useActionParam);
        static void checkItemOther(UseActionParam* useActionParam);
        static bool checkLifeStone(int actionIndex, CharacterStatus* actor, CharacterStatus* target);
    };
} // namespace status
