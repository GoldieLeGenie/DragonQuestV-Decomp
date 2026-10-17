#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/script/sys/ScriptEngine.hpp"

struct ScriptSystem {
    int flag_;                                  // 0x00000
    int chapter_;                               // 0x00004
    DataObject dataObject_;                     // 0x00008
    ScriptEngine scriptEngine_;                 // 0x00018
    int executeEnable_;                         // 0x1F5BC
    int enable_;                                // 0x1F5C0

    ScriptSystem();
    ~ScriptSystem();
    static ScriptSystem* getSingleton();
    void setup(char* fname);
    void setup();
    void cleanup();
    void initialize(int chapter, const char* filename);
    void terminate();
    void execute();
    bool isEnable();
    void setEnableExecute(bool flag);
};
