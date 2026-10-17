#pragma once
#include <globaldefs.h>

// adventure log line shown by the load and save menus
struct UnkDiaryInfo {
    const char* name_;                          // 0x00
    int clear_;                                 // 0x04
    int level_;                                 // 0x08
    int town_;                                  // 0x0C
    int time_;                                  // 0x10
    int savetype_;                              // 0x14
};
