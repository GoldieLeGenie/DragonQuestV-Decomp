#pragma once
#include <globaldefs.h>
#include "main/task/BaseTask.hpp"

namespace status {
    struct UseActionParam;
}

namespace btl {
    struct AfterMessageTask2 : BaseTask {
        int message_;                               // 0x08

        static status::UseActionParam* useActionParam_;

        static void setup(status::UseActionParam* useActionParam);
        void cleanup();
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual int isEnd();
    };
}
