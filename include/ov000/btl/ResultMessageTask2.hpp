#pragma once
#include <globaldefs.h>
#include "main/task/BaseTask.hpp"

namespace status {
    struct UseActionParam;
}

namespace btl {
    struct ResultMessageTask2 : BaseTask {
        int message_;                               // 0x08
        int wait_;                                  // 0x0C
        int counter_;                               // 0x10

        static status::UseActionParam* useActionParam_;

        static void setup(status::UseActionParam* useActionParam);
        virtual void initialize();
        virtual void terminate();
        virtual void execute();
        virtual int isEnd();
    };
}
