#pragma once
#include <globaldefs.h>

// Game region of the build (sets the game code)
struct UnkLanguage {
    UnkLanguage();
};

void unkfunc_020464f8();                        // set the game code of the region
int unkfunc_020464e8();                         // game region (1: JP, 2: NA, 3: EU)
int unkfunc_020465a0();                         // region code

extern const char* data_02099a10;               // game code
