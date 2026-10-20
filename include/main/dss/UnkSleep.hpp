#pragma once
#include <globaldefs.h>
#include "nitro/pm.hpp"

extern int data_020fd15c;                       // sleep when the lid is closed
extern int data_020fd160;
extern int data_020fd164;                       // LCD request (1: off, 2: on)
extern UnkPmSleepCallback data_020fd168;
extern UnkPmSleepCallback data_020fd174;

void initSleep();                        // init
void updateSleep();                        // update (sleep, LCD power)
void setSleepEnabled(int enable);              // lid-close sleep enable
int isSleepEnabled();
void onPreSleep(void* arg);               // pre-sleep callback
void onPostSleep(void* arg);               // post-sleep callback
