#pragma once
#include <globaldefs.h>

// Build date and time of the game
struct UnkBuildDate {
    const char* date_;                          // 0x00 "Mmm dd yyyy"
    char time_[0x10];                           // 0x04 "hh:mm:ss"
    char dateString_[0x10];                     // 0x14

    UnkBuildDate();
};
