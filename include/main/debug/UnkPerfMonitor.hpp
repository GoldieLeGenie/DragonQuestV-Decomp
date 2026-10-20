#pragma once
#include <globaldefs.h>

// map + measured value
struct UnkPerfRecord {
    int mapId_;                                 // 0x00
    int value_;                                 // 0x04

    UnkPerfRecord();
    void clear();
    void set(int mapId, int value);
    int getMapId();
    int getValue();
};

void keepLowestPerfRecord(UnkPerfRecord* records, int count, int mapId, int value);  // keep the smallest values
void keepHighestPerfRecord(UnkPerfRecord* records, int count, int mapId, int value);  // keep the largest values
void sortPerfRecordsDescending(UnkPerfRecord* records, int count);  // sort, largest first
void sortPerfRecordsAscending(UnkPerfRecord* records, int count);  // sort, smallest first
void printPerfRecord(UnkPerfRecord* record, const char* label);  // print

// worst frame times and lowest free memory of each map
struct UnkPerfMonitor {
    int done_;                                  // 0x00
    int active_;                                // 0x04
    int wait_;                                  // 0x08 frames before measuring
    int drawTick0_;                             // 0x0C odd frames
    int collisionTick0_;                        // 0x10
    int drawTick1_;                             // 0x14 even frames
    int collisionTick1_;                        // 0x18
    int freeHeap_;                              // 0x1C KB
    int freeVram_;                              // 0x20 KB
    UnkPerfRecord draw0_[16];                   // 0x24
    UnkPerfRecord draw1_[16];                   // 0xA4
    UnkPerfRecord collision0_[16];              // 0x124
    UnkPerfRecord collision1_[16];              // 0x1A4
    UnkPerfRecord heap_[16];                    // 0x224
    UnkPerfRecord vram_[16];                    // 0x2A4

    void initialize();
    void update();
    void start();
    void stop();
    void finish();
    void measure();
};
