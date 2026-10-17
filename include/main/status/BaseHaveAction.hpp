#pragma once
#include <globaldefs.h>

namespace status {
    struct BaseHaveAction {
        static const int FLAG_TYPE_A = 0x1;
        static const int FLAG_TYPE_B = 0x2;
        static const int FLAG_REMEMBER = 0x4;
        static const int FLAG_REMEMBERING = 0x8;

        unsigned short battleAction_;           // 0x0
        unsigned short usuallyAction_;          // 0x2
        unsigned char actionLevel_;             // 0x4
        unsigned char actionFlag_;              // 0x5

        BaseHaveAction();
        ~BaseHaveAction();
        void clear();
        void setup(int battleAction, int usuallyAction, int level, int flag);
        bool isEnable();
        void add(int battleAction, int usuallyAction);
        void del();
        int getAction();
        int getUsuallyAction();
        void remember();
        bool isRemember();
        void remembering();
        bool isRemembering();
        void clearRemembering();
        void learnTypeA(int level, int wisdom);
        void learnTypeB(int level, int wisdom);
    };
}
