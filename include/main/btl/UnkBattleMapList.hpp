#pragma once
#include <globaldefs.h>
#include "main/dss/CsvData.hpp"

// Group/map list of "data/btlmap/_list.txt" used by the battle menu part
struct UnkBattleMapList : CsvData {
    int group_;                                 // 0x20  first row of the current group
    int map_;                                   // 0x24  row in the group
    int unk_28;                                 // 0x28
    int loaded_;                                // 0x2C

    UnkBattleMapList();
    ~UnkBattleMapList();
    void unkfunc_0206da18(const char* filename);    // load
    int unkfunc_0206da30();                         // loaded
    char* unkfunc_0206da34();                       // group name
    void unkfunc_0206da44();                        // next group
    void unkfunc_0206dac4();                        // previous group
    char* unkfunc_0206db60();                       // map name
    void unkfunc_0206db74();                        // next map
    void unkfunc_0206dbdc();                        // previous map
};

extern UnkBattleMapList data_0209ce6c;
