#pragma once
#include <globaldefs.h>
#include "main/status/UseActionParam.hpp"

namespace status
{
    struct ActionExecRefrection {
        static int execActionEffect(UseActionParam* useActionParam);
        static void execAddDamage(UseActionParam* useActionParam);
        static void execAddDamageItemForceE(UseActionParam* useActionParam);
    };
} // namespace status
