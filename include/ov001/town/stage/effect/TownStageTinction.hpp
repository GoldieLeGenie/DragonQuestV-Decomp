#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/data/DataObject.hpp"

namespace twn {
    struct TownStageTinction {
        int correctTime_;                           // 0x00
        dss::Fix32Vector3 rate_;                    // 0x04
        int nextIndex_;                             // 0x10
        DataObject stageData_;                      // 0x14

        TownStageTinction();
        ~TownStageTinction();
        void cleanup();
        void loadStage();
        void setFloorfog(int index);
        void setTimezone(int index);
        dss::Fix32Vector3 getDefaultPaletteRate();
        void setBackcolor(int index);
        void setRGBRate(dss::Fix32Vector3& rate, int realTime);
        int getCurrentBackColor();
        void setNextBackColor(int index);
        int getNextBackColor();
        dss::Fix32Vector3& getPaletteRate();
    };
}
