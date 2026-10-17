#pragma once
#include <globaldefs.h>

// Slime touch mini game (ov002)
struct ST_ARG_SL_TOUCH {
    int player;                                 // 0x00
    int dbStage;                                // 0x04
    int dbScore;                                // 0x08
    int score;                                  // 0x0C
    int stage;                                  // 0x10
    int gameClear;                              // 0x14
    int item[17];                               // 0x18
};

void SlimeTouchInit(void* work, unsigned int size, ST_ARG_SL_TOUCH* arg);
void SlimeTouchDraw();
void SlimeTouchExec();
void SlimeTouchTerm();
int SlimeTouchResult(ST_ARG_SL_TOUCH* arg);
