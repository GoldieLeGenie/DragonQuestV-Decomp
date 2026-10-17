#pragma once
#include "globaldefs.h"
#include "main/script/sys/ScriptParam.hpp"

struct ScriptCommand {
    ScriptCommand();
    ~ScriptCommand();
    virtual void initialize(char* param) = 0;
    virtual void execute();
    virtual void terminate();
    virtual int isEnd() = 0;
    bool exec(CommandParameter* param);
};

int StartFunction(void* startParam);
void initializeScriptObjectEnble();
void setScriptObjectEnable(int index, bool flag);
int isScriptObjectEnble(int index);
int getObjectCount();
void initializeScriptObjectCtrl();
void setScriptObjectCtrl(int index, int ctrl);
int getScriptObjectCtrl(int index);
int getScriptObjectIndex(int ctrl);
void setPlacementCtrlId(int ctrl);
int getPlacementCtrlId();
int getPlacementCtrlId(int index);
int getPlacementIndex(int ctrl);

extern int scriptObjectEnable[48];
extern int objectCount;
extern int scriptObjectCtrl[48];
extern int ctrlId_;
