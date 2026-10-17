#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

extern int data_020f3e30;                       // fog enabled
extern dss::Fix32 data_020f3e34[2];
extern int data_020f3e3c[2];                    // fog offset of each screen
extern unsigned int data_020f3e44[2][8];        // fog table of each screen

void unkfunc_02046ab0();                        // init
void unkfunc_02046b28(int side, int offset);    // fog offset
void unkfunc_02046b34(int side, dss::Fix32 rate);   // fog rate
void unkfunc_02046ba8(int r, int g, int b);     // fog color
void unkfunc_02046bc4(int enable);              // fog enable
void unkfunc_02046be0();                        // update
