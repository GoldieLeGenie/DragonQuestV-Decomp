#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/script/ScriptBaseCommand.hpp"

struct PARAM_CHECK_LEVEL3_MEISANHIN {
    unsigned int flag;
};

struct PARAM_CHECK_MEISANHIN_COUNT {
    unsigned int type;
    unsigned int min;
    unsigned int max;
};

struct PARAM_CHECK_PENALTY_POINT {
    unsigned int type;
    unsigned int min;
    unsigned int max;
};

struct PARAM_CHECK_MEISANHIN {
    unsigned int floor;
    unsigned int meisanhin;
    unsigned int condition;
};

struct PARAM_CHECK_SPECIAL_MUSEUM {
    unsigned int special;
};

struct PARAM_CHECK_MEISAN_COUNT {
    unsigned int floor;
    unsigned int condition;
    unsigned int count;
};

struct PARAM_CHECK_MUSEUM_LEVEL {
    unsigned int level;
};

struct SetMeisanhinItem : ScriptCommand {
    virtual void initialize(char* param);
    virtual void execute();
    virtual int isEnd();
};

bool cmdCheckMeisanhinCount(void* param);
bool cmdCheckMuseumLevel(void* param);
bool cmdCheckMeisanCount(void* param);
bool cmdCheckSpecialMuseum(void* param);
bool cmdCheckMeisanhin(void* param);
bool cmdCheckPenaltyPoint(void* param);
bool cmdStartSurechigaiParty(void* param);
bool cmdIsCompleteMeisanhin(void* param);
bool cmdCheckLevel3Meisanhin(void* param);
bool cmdLevelUpLocket(void* param);
bool cmdUpdateMuseumLevel(void* param);

extern SetMeisanhinItem gSetMeisanhinItem;
