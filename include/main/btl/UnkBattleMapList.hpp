#pragma once
#include <globaldefs.h>
#include "main/dss/CsvData.hpp"

// Group/map list of "data/btlmap/_list.txt" used by the battle menu part
struct UnkBattleMapList : CsvData {
    int group_;                                 // 0x20  first row of the current group
    int map_;                                   // 0x24  row in the group
    int mapIndex_;                                 // 0x28
    int loaded_;                                // 0x2C

    UnkBattleMapList();
    ~UnkBattleMapList();
    void unkfunc_0206da18(const char* filename);    // load
    int isLoaded();                         // loaded
    char* getGroupName();                       // group name
    void nextGroup();                        // next group
    void prevGroup();                        // previous group
    char* getMapName();                       // map name
    void nextMap();                        // next map
    void prevMap();                        // previous map
};

extern UnkBattleMapList data_0209ce6c;
