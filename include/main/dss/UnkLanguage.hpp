#pragma once
#include <globaldefs.h>

// Game region of the build (sets the game code)
struct UnkLanguage {
    UnkLanguage();
};

void setRegionGameCode();                        // set the game code of the region
int getGameRegion();                         // game region (1: JP, 2: NA, 3: EU)
int getGgid();                         // region code

extern const char* data_02099a10;               // game code
