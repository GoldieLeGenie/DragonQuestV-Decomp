#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/Camera.hpp"
#include "main/cmn/MoveBase.hpp"

struct TownCamera {
    enum {
        MOVE_NONE = 0,
        MOVE_SIMPLE = 1,
        MOVE_VIBMOTION = 2,
        MOVE_RANDOM = 3,
        MOVE_RESET = 4,
        MOVE_TARGET_CHARA = 5,
        MOVE_TARGET_PLAYER = 6,
        MOVE_AREA = 7,
        MOVE_END = 8,
    };

    dss::UnkDualCamera camera_;                 // 0x000
    dss::Fix32 limitL;                          // 0x10C
    dss::Fix32 limitR;                          // 0x110
    int flagRotateL;                            // 0x114
    int flagRotateR;                            // 0x118
    int cameraLock_;                            // 0x11C
    int povLock_;                               // 0x120
    int isPovMove_;                             // 0x124
    int effect_;                                // 0x128
    int remote_;                                // 0x12C
    dss::Fix32Vector3 savePos_;                 // 0x130
    dss::Vector3<short> saveAngle_;             // 0x13C
    int saveFlag_;                              // 0x144
    cmn::MoveBase cameraMove_;                  // 0x148
    cmn::MoveBase povMove_;                     // 0x198
    cmn::MoveBase effecter_;                    // 0x1E8
    int changeDistance_;                        // 0x238
    dss::Fix32 distance_;                       // 0x23C
    dss::Fix32 addDistance_;                    // 0x240
    dss::Fix32 endDistance_;                    // 0x244
    dss::Fix32 startDistance_;                  // 0x248
    dss::Fix32Vector3 povOffset_;               // 0x24C
    int counter_;                               // 0x258
    int frame_;                                 // 0x25C
    int targetChara_;                           // 0x260
    int changeAngle_;                           // 0x264
    int changeDefaultAngleFlag_;                // 0x268
    dss::Vector3<short> changeDefaultAngle_;    // 0x26C
    dss::Vector3<short> preAngle_;              // 0x272
    int notEqualPreAngle_;                      // 0x278
    int endCameraReset_;                        // 0x27C
    dss::Fix32Vector3 target_;                  // 0x280
    dss::Fix32Vector3 minPos_;                  // 0x28C
    dss::Fix32Vector3 maxPos_;                  // 0x298

    TownCamera();
    ~TownCamera();
    static TownCamera* getSingleton();
    void initialize();
    void terminate();
    void execute();
    void gazeMove();
    void angleRot();
    void changeDistance();
    void effectAction();
    void viewMove();
    void lockUpdate();
    void draw();
    bool setAngleNorth(short& retAngle);
    bool rotateL();
    bool rotateR();
    void setLimitL(dss::Fix32 left);
    void setLimitR(dss::Fix32 right);
    void resetAngle();
    void store();
    void restore();
    bool isLimitRotate();
    bool isEndPovMove();
    void setMoveTo(dss::Fix32Vector3& target, int frame, bool absFlag);
    void setRotTo(dss::Vector3<short>& angle, int frame, bool absFlag);
    void resetCameraMove(int frame);
    void setShake(int type, int count);
    void setChangeDistance(int frame, dss::Fix32 end);
    void resetDistance(int frame);
    bool isEndChangeDistance();
    void setPovMove(dss::Fix32Vector3 target, int frame, int flag);
    void unkfunc_021403a0(dss::Vector3<short>& angle, dss::Fix32Vector3& pos, dss::Fix32Vector3& target);
    void setTargetPlayer(int flag);
    void setMoveTargetPlayer(int frame);
    void setMoveTragetChara(int index);
    void setCameraLock(int flag);
    int isRotateL();
    int isRotateR();
    void setEndCameraReset(bool flag);
    void angleCalc();
    void setLockPov(int flag);
    void setDefaultAngle(dss::Vector3<short>& angle);
    void checkArea();
    void setArea(dss::Fix32Vector3& pos1, dss::Fix32Vector3& pos2);
    void setCameraAreaMove(bool flag);
    void setPrevChange(bool flag);
    void setAreaTarget(dss::Fix32Vector3& pos);
    bool isEndMotion();
    void setCameraRemote(int mode);
};
