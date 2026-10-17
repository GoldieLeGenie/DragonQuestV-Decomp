#pragma once
#include <globaldefs.h>

// Menu system hooks called by the game part base (0x0203ed64...)
void unkfunc_02052440();                        // start
void unkfunc_02052450();                        // end
void unkfunc_02052464();                        // execute

extern "C" {
    void func_020624a8(void);                   // load menu graphics
    void func_020624b0(void);                   // init
    void func_020624bc(void);                   // start
    void func_020624c8(void);                   // end
    void func_020624cc(void);
    void func_020624d8(void);                   // execute
    void func_020624e8(void);                   // draw
}

void unkfunc_02063c00();                        // setup all menu displays
void unkfunc_02063cdc();                        // disable all menu displays
void unkfunc_02063d94();
void unkfunc_02063e98();
void unkfunc_02063f9c();
void unkfunc_020640b8();                        // move all menu displays
void unkfunc_02064154();
void unkfunc_02063414();
void unkfunc_0206343c();
void unkfunc_02063440();
void unkfunc_02063450();
