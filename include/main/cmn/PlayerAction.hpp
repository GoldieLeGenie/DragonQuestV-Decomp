#pragma once
#include <globaldefs.h>

namespace cmn
{
    struct PlayerAction {
        // vtable                               // 0x00
        int padInput_;                          // 0x04
        int dirInput_;                          // 0x08

        PlayerAction();
        ~PlayerAction();
        virtual void unkfunc_02014160();
        virtual void unkfunc_02014164();
        virtual void execMove() = 0;
        virtual void execCollision() = 0;
        void inputPad(int dir);
        void inputClear();
        int getPadInput();
        int getDirInput();
    };
} // namespace cmn
