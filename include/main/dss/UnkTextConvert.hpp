#pragma once
#include <globaldefs.h>
#include "main/dss/UnkUtf8Iterator.hpp"

extern unsigned short data_02099e40[2][21];     // normal kana, small kana
extern unsigned short data_02099e94[2][52];     // upper case, lower case
extern unsigned short data_02099f64[2][85];     // katakana, hiragana
extern unsigned short data_0209a0b8[2][96];     // full width, ASCII
extern unsigned char data_020f679c[0x800];

void unkfunc_0204acc4(unsigned short* table81, int size81, unsigned short* tableE0, int sizeE0);
int unkfunc_0204ace4(char* dst, int size, const char* src);                                     // UTF-16 -> UTF-8
unsigned short unkfunc_0204ad44(unsigned short c);                                              // Unicode -> Shift-JIS
int unkfunc_0204adb8(char* dst, unsigned int size, const char* src);                            // UTF-8 -> Shift-JIS
int unkfunc_0204ae2c(char* dst, int size, const char* src);                                     // Shift-JIS -> UTF-8
int unkfunc_0204aeb4(unsigned short* from, unsigned short* to, int c);                          // to[i] -> from[i]
int unkfunc_0204aed0(unsigned short* from, unsigned short* to, char* dst, int size, const char* src);
int unkfunc_0204af38(unsigned short* from, unsigned short* to, char* dst, int size, const char* src, int count);
char* unkfunc_0204afa8(const char* src);                                                        // UTF-8 -> Shift-JIS work buffer
