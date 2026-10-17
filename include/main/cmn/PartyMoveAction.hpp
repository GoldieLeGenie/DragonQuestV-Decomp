#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace cmn
{
    struct PartyData {
        dss::Fix32Vector3 position;             // 0x00
        dss::Fix32Vector3 prevPosition;         // 0x0C
        dss::Fix32 maxDist;                     // 0x18
        dss::Fix32 orgDist;                     // 0x1C
        short direction;                        // 0x20
        short prevDirection;                    // 0x22
        short state;                            // 0x24
        dss::Fix32 front;                       // 0x28
        dss::Fix32 back;                        // 0x2C
        dss::Fix32 right;                       // 0x30
        dss::Fix32 left;                        // 0x34
    };

    struct PartyMoveAction {
        enum PARTY_ACTION_STATE {
            MOVE_NORMAL = 0,
            MOVE_BASHA = 1,
            MOVE_TO_FIRST = 2,
            MOVE_TO_FORMATION = 3,
            SET_FORMATION = 4,
            MOVE_TO_PARALLEL = 5,
            MOVE_MEMBER_JUMP = 6,
        };

        // vtable                               // 0x00
        dss::Fix32Vector3 moveVec_;             // 0x04
        dss::Fix32Vector3 target_;              // 0x10
        int moveCounter_;                       // 0x1C
        int endMoveFrame_;                      // 0x20
        int formation_;                         // 0x24
        short formationDir_;                    // 0x28

        static const int MOVE_ARRAY_MAX = 180;
        static const int PARTY_MEMBER_MAX = 8;

        static dss::Fix32 memberSpeed_;
        static PARTY_ACTION_STATE state_;
        static dss::Fix32Vector3 posArray_[MOVE_ARRAY_MAX];
        static dss::Fix32 distArray_[MOVE_ARRAY_MAX];
        static short dirArray_[MOVE_ARRAY_MAX];
        static PartyData partyData_[PARTY_MEMBER_MAX];
        static int top_;
        static int arrayCount_;
        static int countPartyArray_;
        static int countRFix_;
        static int countLFix_;
        static dss::Fix32Vector3 bashaLPos_;
        static short bashaLIdx_;
        static dss::Fix32Vector3 bashaRPos_;
        static short bashaRIdx_;
        static short prevDirIdx_;

        PartyMoveAction();
        void initialize();
        void setNextArray(dss::Fix32Vector3& pos, short& dir);
        void moveNormalUpdate();
        void moveToFirstUpdate();
        void setAllMemberPos(dss::Fix32Vector3& pos, short dir);
        void trajectoryClear();
        void setDistance(int index);
        void setPartyState(PARTY_ACTION_STATE state);
        PARTY_ACTION_STATE getPartyState();
        void setSpeed(dss::Fix32 speed);
        dss::Fix32 getDistance(int index, int type);
        void setCharaDistance(int index, dss::Fix32 front, dss::Fix32 back, dss::Fix32 right, dss::Fix32 left);
        void setParallelMove(dss::Fix32Vector3& pos, int frame);
        void moveParallelUpdate();
        void setMemberPrevPos(int no, dss::Fix32Vector3& pos);
        const dss::Fix32Vector3& getMemberPrevPos(int no);
        void setMemberPrevDir(int no, short idx);
        virtual int getMemberCount() = 0;
        virtual void execute() = 0;
        virtual inline void setMemberPos(int index, dss::Fix32Vector3& position);
        virtual const dss::Fix32Vector3& getMemberPos(int index);
        virtual inline void setMemberDir(int index, short dir);
        virtual short getMemberDir(int index);
        void setMemberState(int no, short state);
        void removeMemberState(int no, short state);
    };
} // namespace cmn
