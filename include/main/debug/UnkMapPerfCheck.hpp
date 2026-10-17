#pragma once
#include <globaldefs.h>
#include "main/debug/UnkDebugTask.hpp"
#include "main/debug/UnkPerfMonitor.hpp"

// Starts every town map in turn and records its frame times and free memory
struct UnkMapPerfCheck : UnkDebugTask {
    int waitFrame_;                             // 0x10 frames measured per map
    int startFloor_;                            // 0x14
    int endFloor_;                              // 0x18
    int unk_1c;                                 // 0x1C
    int chapterType_;                           // 0x20
    int timeZoneType_;                          // 0x24
    int turnCheck_;                             // 0x28
    int chapterMask_;                           // 0x2C
    int timeZoneMask_;                          // 0x30
    int floor_;                                 // 0x34
    int chapter_;                               // 0x38
    int timeZone_;                              // 0x3C
    UnkPerfMonitor perf_;                       // 0x40

    UnkMapPerfCheck();
    virtual void vf04();
    virtual void vf08();
    virtual void vf0c();
    virtual void vf10();
    void startFloor();
    void nextFloor();
    void searchFloor();
    bool isCheckFloor();
    int getChapterMask(int type);
    int getTimeZoneMask(int type);
    bool isSkipFloor(int floorIndex);
};

extern UnkMapPerfCheck data_020d8800;
