#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/data/DataObject.hpp"

namespace btl {
    struct CameraControl {
        struct SeqCameraControl {
            int frame;                              // 0x00
            dss::Fix32Vector3 pos;                  // 0x04
            dss::Fix32Vector3 pos_a;                // 0x10
            dss::Fix32Vector3 ang;                  // 0x1C
            dss::Fix32Vector3 ang_a;                // 0x28
            dss::Fix32Vector3 posEnd;               // 0x34
            dss::Fix32Vector3 angEnd;               // 0x40
        };
        DataObject data_;                           // 0x00
        dss::Fix32Vector3 iniPosition_;             // 0x10
        dss::Vector3<short> iniAngle_;              // 0x1C
        unsigned int maxSeqPhase_;                  // 0x24
        unsigned int seqPhase_;                     // 0x28
        short dt_;                                  // 0x2C
        short waitCounter_;                         // 0x2E
        SeqCameraControl* seqData_;                 // 0x30
        char camera_name[128];                      // 0x34
        int wait_;                                  // 0xB4

        CameraControl();
        ~CameraControl();
        void terminate();
        void initCameraControl(dss::Fix32Vector3 position, dss::Vector3<short> angle);
        void readCameraData(const char* fname, bool flag);
        bool isEnable();
        bool calc(dss::Fix32Vector3& arg_position, dss::Vector3<short>& arg_angle);
        bool moveCamera(dss::Fix32Vector3& arg_position, dss::Vector3<short>& arg_angle);
        dss::Fix32Vector3& getInitPosition();
        dss::Vector3<short>& getInitAngle();
    };
}
