#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct SurechigaiRoot : ScriptCommand {
    unsigned int connectFlag_;          // 0x04
    unsigned int connectIndex_;         // 0x08
    unsigned int makeFlag_;             // 0x0C
    unsigned int makeIndex_;            // 0x10
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct MakeTaishi : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct SurechigaiTaishiMessage : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

struct SurechigaiTaishiInfo : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

void setFlagByType(unsigned int type, unsigned int index, bool flag);
bool cmdRedrawSurechigaiTaishi(void* param);
bool cmdSetMacroSpecialty(void* param);

extern SurechigaiRoot gSurechigaiRoot;
extern MakeTaishi gMakeTaishi;
extern SurechigaiTaishiMessage gSurechigaiTaishiMessage;
extern SurechigaiTaishiInfo gSurechigaiTaishiInfo;
