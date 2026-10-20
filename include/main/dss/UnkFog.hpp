#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

extern int data_020f3e30;                       // fog enabled
extern dss::Fix32 data_020f3e34[2];
extern int data_020f3e3c[2];                    // fog offset of each screen
extern unsigned int data_020f3e44[2][8];        // fog table of each screen

void initFog();                        // init
void setFogOffset(int side, int offset);    // fog offset
void setFogRate(int side, dss::Fix32 rate);   // fog rate
void setFogColor(int r, int g, int b);     // fog color
void setFogEnable(int enable);              // fog enable
void updateFog();                        // update
