#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionWalk : cmn::ActionBase {
        int collActionFlag_;                        // 0x04
        int searchObjectId_;                        // 0x08
        int searchPolyNo_;                          // 0x0C
        int floorMapUid_;                           // 0x10
        int prevFloorMapUid_;                       // 0x14
        int floorSurfaceId_;                        // 0x18
        int prevFloorSurfaceId_;                    // 0x1C
        dss::Fix32Vector3 searchObjectPos_;         // 0x20
        int searchObjectSide_;                      // 0x2C
        int ctrSurfaceId_;                          // 0x30
        int idoSurfaceid_;                          // 0x34
        int collId_;                                // 0x38
        int prevCollId_;                            // 0x3C
        int sekaijyuSurfaceId_;                     // 0x40
        int cureFloor_;                             // 0x44
        int moveFlag_;                              // 0x48
        int prevSurface_;                           // 0x4C

        virtual int setup();
        virtual void execute();
        virtual int update();
        static void setSearchObjectId(int id);
        static int getFloorMapUid();
        static int getPrevFloorMapUid();
        static int getCollId();
        static int getPrevCollId();
        static void setPrevSurfaceId(int id);
        static int getPrevSurfaceId();
        void clearActionInfo();
        int getMapUid();
        bool isIdoMonster(int mapUid);
    };
}
