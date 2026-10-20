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

void setupMenuDisplays();                        // setup all menu displays
void disableMenuDisplays();                        // disable all menu displays
void updateMenuDisplays();
void executeMenuDisplays();
void drawMenuDisplays();
void moveMenuDisplays();                        // move all menu displays
void resetMenuDisplays();
void initMenuBg();
void updateMenuBg();
void executeMenuBg();
void transferMenuBg();
