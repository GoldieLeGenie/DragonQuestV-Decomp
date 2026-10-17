#pragma once
#include <globaldefs.h>

namespace status
{
    struct UseActionParam;

    struct ActionExecBefore {
        static bool execBefore(UseActionParam* useActionParam);
        static bool execBeforeOne(UseActionParam* useActionParam);
    };
} // namespace status
