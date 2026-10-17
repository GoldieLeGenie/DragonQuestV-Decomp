#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/dss/DssUtils.hpp"

namespace dq5 {
    enum DAY_NIGHT {
        DAY_NIGHT_NONE = 0,
        DAY_NIGHT_DAY = 1,
        DAY_NIGHT_NIGHT = 2,
    };
}

namespace cmn {
    struct WorldLocation {
        static void calcWorldPos(fx32& x, fx32& y);
        static dss::Fix32Vector3 calcPaletteRate(int prev, int next, dss::Fix32 ratio);
        static dss::Fix32Vector3 calcPaletteRate(int wtime);
        static dss::Fix32Vector3 calcDarkPaletteRate();
        static void setCurrentTimeZone();
        static TIME_ZONE getCurrentTimeZone();
        static dq5::DAY_NIGHT getCurrentDayNight();
        static bool isVehicleExist(int vehicle);
        static int getDaytime();
        static int getEvening();
        static int getNight();
        static int getMorning();
        static int getMaxTime();
    };
}
