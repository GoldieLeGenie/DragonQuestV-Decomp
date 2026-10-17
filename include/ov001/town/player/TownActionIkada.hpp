#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"

namespace twn {
    struct TownActionIkada : cmn::ActionBase {
        enum {
            SCRIPT_NONE = 0,
            SCRIPT_GET_ON = 1,
            SCRIPT_GET_OFF = 2,
        };

        int ikadaObjectId_;                         // 0x04
        int ctrSurfaceId_;                          // 0x08
        int ctrSurfacePoly_;                        // 0x0C
        int counter_;                               // 0x10
        dss::Fix32Vector3 ikadaPosition_;           // 0x14
        dss::Fix32Vector3 scriptTarget_;            // 0x20
        int moveMode_;                              // 0x2C
        int script_;                                // 0x30

        virtual int setup();
        virtual void execute();
        virtual int update();
        int startCheck();
        void setIkadaPosition(dss::Fix32Vector3& pos);
        void setIkadaDataByScript(int nameId, dss::Fix32Vector3& pos);
        static void setScriptMove(int type);
        static int getScriptMove();
        static void setScriptTarget(dss::Fix32Vector3& pos);
        void ikadaMove();
    };
}
