#pragma once
#include "globaldefs.h"
#include "GameInfo.hpp"

struct UnkMessageWindow;

void ui_MsgSystemInit();
void ui_MsgSetup(eMessageWindow type, int lang);
void ui_MsgAdd(int strNo);
int ui_MsgAddSerial(int no);
void ui_MsgAdd(const char* str);
void unkfunc_02062624();
void ui_MsgAddWait();
void unkfunc_0206264c();
void unkfunc_0206265c(int cursor);
void ui_MsgSndSet(int no);
void ui_MsgSndSet(int* pms);
int ui_MsgSndGet();
void unkfunc_0206266c(int strNo);
void unkfunc_02062720();
int unkfunc_02062748(int no);
void unkfunc_020627f8(char* dst, const char* src, int width, int lines, int font);  // auto return

extern UnkMessageWindow* s_draw;
extern int s_msgCount;
