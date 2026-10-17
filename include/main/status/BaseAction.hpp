#pragma once
#include <globaldefs.h>
#include "main/status/UseActionParam.hpp"

namespace status
{
    struct CharacterStatus;

    struct BaseAction {
        static int executeTarget_;
        static int executeActor_;
        static int executeAction_;
        static int actionIndex_;
        static UseActionParam* useActionParam_;
        static int resultFlag_;

        static void exec(UseActionParam& useActionParam, bool battle);
        static int execMainRoot(CharacterStatus* actor, CharacterStatus* target);
        static void beforeAction(UseActionParam* useActionParam);
        static void execActionSetupPre();
        static void execActionAfterAfter();
        static void execActionTargetSetup();
        static void execActionSetup();
        static bool execActionExecute();
        static void execActionExecuteSpecial();
        static void execActionResultMessage();
        static void execActionAfter();
        static void afterAction();
    };
} // namespace status
