#pragma once
#include <globaldefs.h>

// window parts of the casino and adventure log menus drawn from menu parts lists
void drawFightStadiumLayout(int flag);                            // monster list title
void drawFightStadiumPanels(int flag);                            // bet window title
void drawMessageColumn(int* message, int count, int x, int y);   // command list
void drawFightStadiumEntry(int monster, int diameter, int index, int order);    // monster list line
void drawFightStadiumCursor(int index);                           // monster list cursor
void drawFightStadiumBetDigits(int coin, int x, int y, int flag);    // coins window
void drawCenteredMessage(int* message, int x, int y, int w, int h);    // window title
void drawJournalSlot(int index, const char* name, int clear, int level, int town, int time, int x, int flag);  // adventure log line
void drawResumeSlot(const char* name, int clear, int level, int time);    // resume data
void drawNameEditCharTable(int* text, int flag);                 // name entry keyboard lines
void drawNameEditField(int language, unsigned int* text, int count, int max, int blink, int type);  // name entry chars
void drawNameEditCommentField(unsigned int* text, int count);      // name entry message chars
