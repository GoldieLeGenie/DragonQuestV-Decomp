#pragma once
#include "globaldefs.h"
#include "GameInfo.hpp"

struct MessageWindow;

void ui_MsgSystemInit();
void ui_MsgSetup(eMessageWindow type, int lang);
void ui_MsgAdd(int strNo);
int ui_MsgAddSerial(int no);
void ui_MsgAdd(const char* str);
void ui_MsgAddWaitTrigger();
void ui_MsgAddWait();
void unkfunc_0206264c();
void ui_MsgSetYesNoCursor(int cursor);
void ui_MsgSndSet(int no);
void ui_MsgSndSet(int* pms);
int ui_MsgSndGet();
void unkfunc_0206266c(int strNo);
void ui_MsgOpenIfFirst();
int unkfunc_02062748(int no);
void unkfunc_020627f8(char* dst, const char* src, int width, int lines, int font);  // auto return

extern MessageWindow* s_draw;
extern int s_msgCount;
