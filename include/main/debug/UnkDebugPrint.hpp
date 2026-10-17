#pragma once
#include <globaldefs.h>
#include <stdarg.h>

extern int data_020f3258;                       // wireless role mode
extern int data_020f325c;                       // console print enable
extern int data_020f3260;

void unkfunc_02043430(const char* title);       // clear the console and print a title
void unkfunc_0204348c(int x, int y, const char* str);
void unkfunc_020434c8(int x, int y, const char* fmt, ...);  // control characters printed as spaces

extern "C" {
    int func_020873dc(char* dst, int size, const char* fmt, va_list args);  /* OS_VSNPrintf */
}
