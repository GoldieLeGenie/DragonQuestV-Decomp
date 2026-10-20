#pragma once
#include <globaldefs.h>
#include "main/dss/Camera.hpp"
#include "ov000/btl/BattleCameraHoming.hpp"

namespace btl {
    struct BattleCamera {
        static const int CAMERA_NAME_SIZE = 16;

        UnkCamera normalCamera_;                    // 0x000
        UnkCamera iniCamera_;                          // 0x070
        dss::Fix32Vector3 initposition_;            // 0x0E0
        int enable_;                                // 0x0EC
        int unk_0f0;                                // 0x0F0
        int unk_0f4;                                // 0x0F4
        char file_[CAMERA_NAME_SIZE];               // 0x0F8
        char file2_[CAMERA_NAME_SIZE];              // 0x108
        BattleCameraHoming homing_;                 // 0x118

        BattleCamera();
        ~BattleCamera();
        static BattleCamera* getSingleton();
        void initialize();
        void terminate();
        void reset();
        void executeForMap();
        void draw();
        void initCamera(int wait);
        void setCameraAnimation(unsigned short camera1, unsigned short camera2, unsigned short wait);
        void setHomingTarget(int drawCtrlId);
        void setRotateTime(int time);
        void setWaitTime(int time);
        void setHomingStart();
        dss::Camera* getCamera();
    };
}
