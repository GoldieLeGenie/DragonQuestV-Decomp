#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace ceremony {
    // Settings of the opening/ending ceremony set by the scripts
    struct CeremonySetting {
        int opening_;                           // 0x00
        int staffrollIndex_;                    // 0x04
        int nextActMap_;                        // 0x08
        dss::Fix32Vector3 nextActPosition_;     // 0x0C

        CeremonySetting();
        ~CeremonySetting();
        static CeremonySetting* getSingleton();
        void setOpening(int index);
        void setStaffrollIndex(int index);
        int getNextActMap();
        void setNextActMap(int index);
        void setNextActPos(dss::Fix32Vector3& pos);
        dss::Fix32Vector3& getNextActPos();
    };
}
