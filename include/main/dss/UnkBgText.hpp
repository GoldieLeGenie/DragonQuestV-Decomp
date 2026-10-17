#pragma once
#include <globaldefs.h>
#include "main/dss/UnkBgBuffer.hpp"
#include "main/dss/UnkFont.hpp"

// text drawing state of the BG text engine
struct UnkBgText {
    int size_;                                  // 0x00 font size (12 or 10)
    UnkFont font12_;                            // 0x04
    UnkFont font10_;                            // 0x14
    UnkFont subFont12_;                         // 0x24 latin chars
    UnkFont subFont10_;                         // 0x34 latin chars
    unsigned char charWidths_[0x100];           // 0x044 widths of the last text
    unsigned short charCodes_[0x100];           // 0x144 chars of the last text
    int count_;                                 // 0x344 char count of the last text
    int width_;                                 // 0x348 width of the last text
    int height_;                                // 0x34C height of the last text
    UnkFont* font_;                             // 0x350
    UnkFont* subFont_;                          // 0x354
    int lineHeight_;                            // 0x358
    int mode_;                                  // 0x35C full-width digits glyphs (1 or 2)
};

extern UnkBgText data_021011f0;

void unkfunc_0204df4c();                        // init
void unkfunc_0204df60(void* data, void* subData);   // load the 12 dots fonts
void unkfunc_0204df84(void* data, void* subData);   // load the 10 dots fonts
int unkfunc_0204dfa8(UnkCharBuffer* buffer, int x, int y, int color, const char* text);   // draw a text (NULL: measure)
int unkfunc_0204dfbc(UnkCharBuffer* buffer, int x, int y, int color, const char* text, int wrap);
int unkfunc_0204e1a0(UnkG2dCanvas* canvas, int x, int y, int color, unsigned short c);    // draw a char (NULL: width)
void unkfunc_0204e478(int size);                // set the font size
int unkfunc_0204e4c8(int size);                 // line height
int unkfunc_0204e4dc(unsigned char* widths, int max);   // char widths of the last text
int unkfunc_0204e540();                         // width of the last text
int unkfunc_0204e50c(unsigned short* codes, int size);  // char codes of the last text

extern "C" void func_0204e54c(int mode);           // set the full-width digits glyphs mode
