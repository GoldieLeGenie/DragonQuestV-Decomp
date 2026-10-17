#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/script/sys/ScriptTree.hpp"

// one command of a script tree
struct CommandParameter {
    static const unsigned int FLAG_TYPE_A = 0x0;
    static const unsigned int FLAG_TYPE_B = 0x1;
    static const unsigned int FLAG_INITIALIZED = 0x10;
    static const unsigned int FLAG_TERMINATED = 0x40;

    unsigned short command_;                    // 0x00
    unsigned char flag_;                        // 0x02
    unsigned char reserved_;                    // 0x03
    char param_[4];                             // 0x04

    int getCommandIndex();
    bool isTypeA();
    bool isTypeB();
    void setInitialized();
    bool isInitialized();
    void setTerminated();
    bool isTerminated();
    char* getParam();
};

struct ScriptParam {
    DataObject dataObject_;                     // 0x000
    ScriptTree scriptTree_;                     // 0x010
    int count_;                                 // 0x2A4
    char* tree_;                                // 0x2A8
    int* offset_;                               // 0x2AC
    unsigned char* command_;                    // 0x2B0

    ScriptParam();
    ~ScriptParam();
    void setup(void* addr);
    void setup();
    void cleanup();
    void execute();
    static void setExecuteCommandFunction(bool (*fc)(void*));
    bool execScriptCommand(int cmdIndex);
    bool checkScriptCommandStatus();
    void clearScriptCommandStatus(int cmdIndex);
    int getScriptCommandType(int cmdIndex);
    bool getScriptCommandClearFlag(int cmdIndex);

    static bool (*executeCommandFunction_)(void*);
};
