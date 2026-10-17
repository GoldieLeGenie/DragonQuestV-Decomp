#pragma once
#include <globaldefs.h>
#include "main/dss/Tree.hpp"

struct ScriptTree : public dss::Tree<unsigned char, 160> {
    static bool (*executeFunction_)(int);
    static bool (*checkStatusFunction_)();
    static void (*clearStatusFunction_)(int);
    static int (*getScriptCommandTypeFunction_)(int);
    static bool (*getScriptCommandClearFlag_)(int);
    static bool (*displayFunction_)(int);

    ScriptTree();
    ~ScriptTree();
    static void setExecuteFunction(bool (*fc)(int));
    static void setCheckStatusFunction(bool (*fc)());
    static void setClearStatusFunction(void (*fc)(int));
    static void setGetScriptCommandTypeFunction(int (*fc)(int));
    static void setGetScriptCommandClearFlag(bool (*fc)(int));
    static void setDisplayFunction(bool (*fc)(int));
    void recursiveTree();
    virtual void display();
    void recursiveDisplay();
};
