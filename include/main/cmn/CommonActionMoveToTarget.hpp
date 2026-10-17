#pragma once
#include <globaldefs.h>
#include "main/cmn/ActionBase.hpp"
#include "main/cmn/PlayerManager.hpp"
#include "main/dss/DssUtils.hpp"

namespace cmn
{
    struct CommonActionMoveToTarget : ActionBase {
        enum MOVE_TYPE {
            MOVE_TO_TARGET = 0,
            MOVE_TO_FIRST = 1,
            MOVE_END = 2,
        };

        PlayerManager* playerManager_;          // 0x04
        dss::Fix32Vector3 target_;              // 0x08
        dss::Fix32Vector3 startPos_;            // 0x14
        dss::Fix32Vector3 nowPos_;              // 0x20
        dss::Fix32Vector3 moveVec_;             // 0x2C
        dss::Fix32 speed_;                      // 0x38
        int moveType_;                          // 0x3C
        int drawType_;                          // 0x40
        int nextAction_;                        // 0x44
        int partyMoveFlag_;                     // 0x48
        MOVE_TYPE moveMode_;                    // 0x4C
        int eraseFlag_;                         // 0x50
        int count_;                             // 0x54

        virtual int setup();
        virtual void execute();
        virtual int update();
        void setAction(dss::Fix32Vector3& start, dss::Fix32Vector3& target, dss::Fix32 speed, int moveType, int drawType, int nextAction);
        int getNextAction();
        void drawAllExec();
        void drawEraseExec(int start);
    };

    extern CommonActionMoveToTarget gMoveToTarget;
} // namespace cmn
