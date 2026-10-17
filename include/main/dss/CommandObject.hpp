#pragma once
#include <globaldefs.h>

namespace args {
    struct CommandObject {
        CommandObject();
        ~CommandObject();
        virtual int isExec() = 0;
        virtual int isEnd() = 0;
        virtual void exec() = 0;
    };

    struct CommandObjectManager {
        static const int COMMAND_OBJECT_MAX = 64;

        CommandObject* commandObject_[COMMAND_OBJECT_MAX]; // 0x000
        int state_;                                     // 0x100

        CommandObjectManager();
        ~CommandObjectManager();
        void initialize();
        void enRegister(CommandObject& object, int priority);
        void execute();
        void setCommandState(int state);
    };
}
