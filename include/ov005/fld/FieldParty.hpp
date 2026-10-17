#pragma once
#include <globaldefs.h>
#include "main/cmn/PartyMoveAction.hpp"
#include "main/dss/DssUtils.hpp"

namespace dq5
{
    enum TYPE_DIR4 {
        TYPE_DIR4_UP = 0,
        TYPE_DIR4_RIGHT = 1,
        TYPE_DIR4_DOWN = 2,
        TYPE_DIR4_LEFT = 3,
    };
} // namespace dq5

namespace fld
{
    struct FieldParty : cmn::PartyMoveAction {
        static const int COUNT_MAX = 20;

        int flagBashaArray_;                    // 0x2C
        int flagMoveToFirst_;                   // 0x30
        int LRreset_;                           // 0x34

        FieldParty();
        ~FieldParty();
        void setup();
        void cleanup();
        virtual void execute();
        virtual int getMemberCount();
        bool isBashaEnable();
        void setBashaArray(bool flag);
        virtual const dss::Fix32Vector3& getMemberPos(int index);
        virtual void setMemberPos(int index, dss::Fix32Vector3& pos);
        virtual short getMemberDir(int index);
        virtual void setMemberDir(int index, short idx);
        void moveAllPlayerToFirst();
        void setAllPlayerAtFirst();
        void getSidePos(dq5::TYPE_DIR4 side, dss::Fix32Vector3& nowPos, dss::Fix32Vector3* nextPos, short* retIdx);
        void collisionSide(dq5::TYPE_DIR4 side, dss::Fix32Vector3* nextPos, short dirIdx);
        void fixSidePos(dq5::TYPE_DIR4 side, int fix);
        void resetBashaCount();
        void resetLRMove(bool flag);
        void setFormation(dss::Fix32Vector3& dirVec, short dirIdx);
        void moveBashaUpdate();
    };
} // namespace fld
