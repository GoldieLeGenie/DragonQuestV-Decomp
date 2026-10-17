#pragma once
#include <globaldefs.h>

namespace dq5 {
namespace level {
    struct LevelDataUtility {
        LevelDataUtility();
        ~LevelDataUtility();
        int searchShopDataIndex(int area, int section);
        int searchMapCorrectIndex(int floorIndex);
        int searchFurnDataIndex(int floorIndex);
        int getCharaParamIndex(int index);
        int getSoratobuIndex();
        int getKimeraIndex(int map);
        int getRuraIndex(int flag);
        int getOverviewFloor(int mapId);
        int getOverviewArea(int areaId);
        int getMapNameIdByName(const char* name);
        const char* getMapNameById(int no);
        int getAreaNoByMapId(int id);
        int getFloorDataIndex();
    };

    extern LevelDataUtility g_LevelDataUtility;
}
}
