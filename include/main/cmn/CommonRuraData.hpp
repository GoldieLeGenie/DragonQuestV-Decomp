#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace cmn {
    struct CommonRuraData {
        static const int maxRuraFlag = 21;

        static CommonRuraData& getSingleton();
        CommonRuraData();
        ~CommonRuraData();
        void initialize();
        void terminate();
        bool isEnableRura(int index);
        int getRuraCount();
        dss::Fix32Vector3 getShipTownPos(int index);
        dss::Fix32Vector3 getPlayerTownPos(int index);
    };
}
