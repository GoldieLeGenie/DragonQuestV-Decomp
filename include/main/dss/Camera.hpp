#pragma once
#include "main/dss/DssUtils.hpp"
#include "nitro/g3.hpp"
#include "nnsys/g3d.hpp"

namespace dss {
    struct UnkCameraPerspective {
        unsigned int m_fovySin;                 // 0x00
        unsigned int m_fovyCos;                 // 0x04
        int m_aspect;                           // 0x08
        int m_near;                             // 0x0C
        int m_far;                              // 0x10
    };

    struct Camera {
        // vtable                               // 0x00
        Vector3<short> m_angle;                 // 0x04
        Fix32Vector3 m_target_pos;              // 0x0C
        Fix32Vector3 m_pos;                     // 0x18
        Fix32Vector3 m_direction;               // 0x24
        Fix32Vector3 m_up;                      // 0x30
        Fix32Vector3 m_lookDir;                    // 0x3C normalized target - position
        Fix32 m_distance;                       // 0x48
        Fix32 m_distanceSq;                     // 0x4C
        int m_fov2;                             // 0x50
        Fix32 m_scaleW;                         // 0x54
        UnkCameraPerspective m_perspective;     // 0x58
        int m_noUpdate;                             // 0x6C

        Camera();
        virtual void update();
        virtual void calcPosition();
        void setup();
        void calcLookDirection();
        void applyCamera();
        void setPosition(const Fix32Vector3& pos);
        Fix32Vector3& getPosition();
        void setTarget(const Fix32Vector3& target);
        Fix32Vector3& getTarget();
        void setAngle(const Vector3<short>& angle);
        Vector3<short>& getAngle();
        void setDistance(const Fix32& distance);
        Fix32& getDistance();
        Fix32& getDistanceSq();
        Fix32Vector3& getDirection();
        void setFOV(unsigned int sin, unsigned int cos);
        void setFOV2(int fovy);
        int getFOV2();
        void setScaleW(Fix32 scaleW);
        void setNear(int value);
        void setFar(int value);
    };
}

namespace dss {
    // Cameras of the two screens (main 0x02051bd4)
    struct UnkDualCameraBase {
        // vtable                               // 0x000
        Camera m_camera0;                         // 0x004
        Camera m_camera1;                         // 0x074
        int m_cameraNo;                            // 0x0E4 current screen camera

        UnkDualCameraBase();
        virtual void update();
        virtual void calcPosition();
        void updateCameraNo();
        void applyCamera();                // update, calc and apply the cameras
        void applyG3d();                // apply the camera of the current screen
        void setTarget(const Fix32Vector3& target, int screen);
    };

    struct UnkDualCamera : UnkDualCameraBase {
        int unk_0e8;                            // 0x0E8
        int unk_0ec;                            // 0x0EC
        Fix32 m_offset;                          // 0x0F0 offset
        short m_dirOffset;                          // 0x0F4 direction offset
        Vector3<short> unk_0f6;                 // 0x0F6
        Vector3<short> unk_0fc;                 // 0x0FC
        unsigned char unk_102[0x108 - 0x102];   // 0x102
        int m_pursue;                           // 0x108

        UnkDualCamera();
        virtual void update();
        virtual void calcPosition();
        void setup();
        void setDistance(Fix32 distance);
        void setAngle(Vector3<short> angle);
        void setRotXYZ(Vector3<short> angle);
        void setOffset(Fix32 offset);
        void setFOV2(int fovy);
        void setScaleW(Fix32 scaleW);
    };
}

// dss::Camera subclass whose target follows position + angle (main 0x02051ffc); idk the real name yet
struct UnkCamera : dss::Camera {
    UnkCamera();
    virtual void update();
    virtual void calcPosition();
};

extern short data_02099a3c[4];
extern int data_02099a44[40][2];
