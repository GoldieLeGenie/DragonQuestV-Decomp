#pragma once
#include <globaldefs.h>
#include "main/dss/Billboard.hpp"
#include "main/dss/Camera.hpp"

namespace cmn
{
    struct CommonParticle : Billboard {
        int frame;                              // 0xB4
        int anim;                               // 0xB8
        int pattern;                            // 0xBC
        dss::Fix32Vector3 velocity;             // 0xC0
        unsigned char unk_cc[0x4];              // 0xCC
        int phase;                              // 0xD0

        CommonParticle();
        ~CommonParticle();
        void unkfunc_0204500c();                // texture coordinates, vertex, texture, fade in
        void unkfunc_020451f8();                // random animation start
        void execute();
        void updateAnimation();                // animation
        void updateAlpha();                // alpha (fade in/out)
        void loopBack(dss::Camera* camera);
        bool isInView(dss::Camera* camera);    // in the camera view
        void unkfunc_020455ec();
        bool isDelete();
    };

    struct CommonParticleEmitter {
        dss::UnkDualCamera* unk_00;             // 0x00 camera
        int enable_;                            // 0x04
        int stop_;                              // 0x08
        int count_;                             // 0x0C
        dss::Fix32 minScale_;                   // 0x10
        dss::Fix32 maxScale_;                   // 0x14
        dss::Fix32 offset_;                     // 0x18
        dss::Fix32Vector3 baseVelocity_;        // 0x1C
        dss::Fix32Vector3 offsetVelocity_;      // 0x28
        CommonParticle* particle_;              // 0x34
        unsigned char unk_38[0x620];            // 0x38

        CommonParticleEmitter();
        ~CommonParticleEmitter();
        static CommonParticleEmitter* getSingleton();
        void initialize();
        void terminate();
        void setup(int index);
        void setupParameter(int type);
        void setupParticle(int index);
        void draw();
        void execute();
        void pause(bool flag);
        int isEnable();
        void cleanup();
        void setCount(int count);
    };
} // namespace cmn
