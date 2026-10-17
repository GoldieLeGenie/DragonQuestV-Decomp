#pragma once
#include <globaldefs.h>
#include "main/cmn/CommonWalkDamage.hpp"
#include "main/dss/DssUtils.hpp"

namespace fld
{
    struct FieldPlayerDoku : cmn::CommonWalkDamage {
        int blockAttr_;                         // 0x18

        static FieldPlayerDoku& getSingleton();
        void setup();
        virtual bool checkBarrier();
        virtual bool checkPoison();
        virtual void setPartyMemberColor(int index, int type);
        void checkDokuDamage(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos);
        void setBlockAttr(int blockAttr);
    };
} // namespace fld
