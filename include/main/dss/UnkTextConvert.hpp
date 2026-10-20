#pragma once
#include <globaldefs.h>
#include "main/dss/UnkUtf8Iterator.hpp"

extern unsigned short data_02099e40[2][21];     // normal kana, small kana
extern unsigned short data_02099e94[2][52];     // upper case, lower case
extern unsigned short data_02099f64[2][85];     // katakana, hiragana
extern unsigned short data_0209a0b8[2][96];     // full width, ASCII
extern unsigned char data_020f679c[0x800];

void initSjisTables(unsigned short* table81, int size81, unsigned short* tableE0, int sizeE0);
int convertUtf16ToUtf8(char* dst, int size, const char* src);                                     // UTF-16 -> UTF-8
unsigned short unicodeToSjis(unsigned short c);                                              // Unicode -> Shift-JIS
int convertUtf8ToSjis(char* dst, unsigned int size, const char* src);                            // UTF-8 -> Shift-JIS
int convertSjisToUtf8(char* dst, int size, const char* src);                                     // Shift-JIS -> UTF-8
int translateChar(unsigned short* from, unsigned short* to, int c);                          // to[i] -> from[i]
int translateText(unsigned short* from, unsigned short* to, char* dst, int size, const char* src);
int translateTextPrefix(unsigned short* from, unsigned short* to, char* dst, int size, const char* src, int count);
char* convertUtf8ToSjisWork(const char* src);                                                        // UTF-8 -> Shift-JIS work buffer
