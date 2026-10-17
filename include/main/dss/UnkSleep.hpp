#pragma once
#include <globaldefs.h>
#include "nitro/pm.hpp"

extern int data_020fd15c;                       // sleep when the lid is closed
extern int data_020fd160;
extern int data_020fd164;                       // LCD request (1: off, 2: on)
extern UnkPmSleepCallback data_020fd168;
extern UnkPmSleepCallback data_020fd174;

void unkfunc_0204bf48();                        // init
void unkfunc_0204bfa4();                        // update (sleep, LCD power)
void unkfunc_0204c08c(int enable);              // lid-close sleep enable
int unkfunc_02089568();
void unkfunc_02089578(void* arg);               // pre-sleep callback
void unkfunc_0208957c(void* arg);               // post-sleep callback
