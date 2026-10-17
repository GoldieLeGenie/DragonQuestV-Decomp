#pragma once
#include <globaldefs.h>

extern void* data_02101550[5];                  // system text resources (character, font, palettes)

void unkfunc_0204e654(void* res0, void* res1, void* res2, void* res3, void* res4);    // set the resources
void* unkfunc_0204e698(int index);              // character resource
void* unkfunc_0204e6a4(int index);              // palette resource
void unkfunc_0204e6b0(int type, int screen1, int screen2);  // transfer the characters
void unkfunc_0204e74c(int type, int screen1, int screen2);  // transfer the palettes
