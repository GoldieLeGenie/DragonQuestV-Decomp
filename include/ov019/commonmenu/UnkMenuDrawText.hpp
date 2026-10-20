#pragma once
#include <globaldefs.h>

// text ids and table lookups used by the town and materiel menu windows
int getItemCommandText(int index);
int getMenuCommandText(int type, int index);
void getHighLowCommandText(int* text, int flag);
void getChurchCommandText(int* text, int flag);
int getTagModeRootText(int index);
char getMeisanhinRecordIndex(int index);
