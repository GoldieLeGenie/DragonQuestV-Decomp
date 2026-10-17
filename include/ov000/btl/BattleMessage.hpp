#pragma once
#include <globaldefs.h>

namespace status {
    struct UseActionParam;
}

namespace btl {
    struct BattleMessage {
        static void setMessage(int mes0, int mes1, int mes2, int mes3);
        static void setMessageNoSeqNum(int mes0, int mes1, int mes2, int mes3, int mes4, int mes5, int mes6, int mes7);
        static void setMessageInTown(int mes0, int mes1, int mes2, int mes3);
        static bool setBeforeMessage(status::UseActionParam& useActionParam);
        static bool setExecMessage(status::UseActionParam& useActionParam);
        static bool setSpecialMessage(status::UseActionParam& useActionParam, int currentTarget);
        static bool setResultMessage(status::UseActionParam& useActionParam, int currentTarget);
        static bool setAfterMessage(status::UseActionParam& useActionParam, int currentTarget);
        static void setShakeMessage(status::UseActionParam& useActionParam, int currentTarget);
        static void openMessage();
        static void openEncountMessage();
        static void addEncountMessage(int message);
    };
}
