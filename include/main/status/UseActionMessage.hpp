#pragma once 
#include <globaldefs.h>
#include "GameInfo.hpp"

namespace status
{
    struct UseActionMessage {
        int beforeMessage_[2];
        int execMessage_[4];
        int spclMessage_[2];
        int resultMessage_[2];
        int addMessage_[2];
        UseActionMessage();
        void clear();
        void setExecMessage(int index, int message);
        int getExecMessage(int index);
        void setResultMessage(int index, int message);
        int getResultMessage(int index);
        void setAddMessage(int index, int message);
        int getAddMessage(int index);
        void setSpclMessage(int index, int message);
        void setBeforeMessage(int index, int message);
    };
} // namespace status
