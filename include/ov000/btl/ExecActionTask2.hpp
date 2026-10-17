#pragma once
#include <globaldefs.h>
#include "main/task/BaseTask.hpp"

namespace status {
    struct UseActionParam;
}

namespace btl {
    struct ExecActionTask2 : BaseTask {
        static status::UseActionParam* useActionParam_;

        static void setup(status::UseActionParam* useActionParam);

        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual int isEnd();
    };

    struct ExecActionTask3 : ExecActionTask2 {
        int execute_;                               // 0x08

        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual int isEnd();
    };
}
