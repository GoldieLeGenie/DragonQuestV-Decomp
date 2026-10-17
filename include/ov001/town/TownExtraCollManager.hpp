#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace twn
{
    struct TownExtraCollManager {
        static TownExtraCollManager& getSingleton();
        void setup();
        void addSleepChara(int index);
        void addCharacterColl(int index, int type);
        void resetCharaColl(int index, int type);
        void setCheckArea(dss::Fix32 minX, dss::Fix32 maxX, dss::Fix32 minZ, dss::Fix32 maxZ);
    };
} // namespace twn
