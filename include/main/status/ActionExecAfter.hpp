#pragma once
#include <globaldefs.h>

namespace status
{
    struct UseActionParam;

    struct ActionExecAfter {
        static bool execAfterOne(UseActionParam* useActionParam);
        static bool execAfter(UseActionParam* useActionParam, int flag);
    };
} // namespace status
