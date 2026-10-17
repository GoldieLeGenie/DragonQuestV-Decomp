#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace cmn
{
    struct MoveBase {
        dss::Fix32Vector3 targetPos_;           // 0x00
        dss::Fix32Vector3 startPos_;            // 0x0C
        dss::Fix32Vector3 moveVec_;             // 0x18
        dss::Vector3<short> targetDirIdx_;      // 0x24
        dss::Vector3<short> startDirIdx_;       // 0x2A
        dss::Vector3<int> rotIdx_;              // 0x30
        int moveType_;                          // 0x3C
        short endMoveFrame_;                    // 0x40
        short endRotFrame_;                     // 0x42
        short moveCounter_;                     // 0x44
        short rotCounter_;                      // 0x46
        short dampFrame_;                       // 0x48
        short ampFrame_;                        // 0x4A
        dss::BitFlag<unsigned short> actionFlag_; // 0x4C

        static const dss::Fix32 grav;

        void setup();
        void execMove(dss::Fix32Vector3& pos);
        void execRot(dss::Vector3<short>& rot);
        bool moveUpdate();
        bool rotUpdate();
        bool isEnd();
        void setActionMove(dss::Fix32Vector3& start, dss::Fix32Vector3& target);
        void setActionRot(dss::Vector3<short>& start, dss::Vector3<short>& target);
        void setMoveSpeed(dss::Fix32 speed);
        void setMoveFrame(int frame);
        void setRotFrame(int frame, int type);
        short setRot(short rot, int frame, int type);
        void simpleMove(dss::Fix32Vector3& pos);
        void simpleRot(dss::Vector3<short>& rot);
        void setSimpleRot(dss::Vector3<short>& start, dss::Vector3<short>& add, int frame);
        void setRotSpeedY(short speed);
        bool simpleMoveUpdate();
        bool simpleRotUpdata();
        void setVibMotion(dss::Fix32Vector3& start, dss::Fix32Vector3& target, int amp, int damp, int frame);
        void moveVibMotion(dss::Fix32Vector3& pos);
        bool updateVibMotion();
        void setRandomShake(dss::Fix32Vector3& start, dss::Fix32Vector3& target, int count);
        void shakeExecute(dss::Fix32Vector3& pos);
        bool updateShake();
        dss::Fix32Vector3 getShakeVec(int index);
        void setJumpMove(dss::Fix32Vector3& start, dss::Fix32Vector3& target, int frame);
        void jumpExecute(dss::Fix32Vector3& pos);
        bool updateJump();
        void setAddMove(dss::Fix32Vector3& start, dss::Fix32Vector3& target, int frame);
        void moveAddExecute(dss::Fix32Vector3& pos);
        bool updateMoveAdd();
        void dirMoveExec(dss::Fix32Vector3& pos);
        bool updateDirMove();
        void setDirMove(dss::Fix32 value, int dir, dss::Fix32 speed);
        void setMoveLock(bool flag);
        void execWait();
        bool updateWait();
        dss::Vector3<short> getRotIdx();
        void setRough(bool flag);
    };

    struct MoveAction : MoveBase {
        unsigned char recActionNo_;             // 0x4E
        unsigned char recStep_;                 // 0x4F
        unsigned char recFlowType_;             // 0x50
        unsigned char recLoopType_;             // 0x51
        unsigned short recFrame_;               // 0x52

        void setup();
    };
} // namespace cmn
