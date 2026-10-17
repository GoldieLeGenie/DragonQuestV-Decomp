#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct Riseup_move : ScriptCommand {
    int index;                          // 0x04
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};


extern Riseup_move gRiseup_move;
