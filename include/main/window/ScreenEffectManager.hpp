#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/Camera.hpp"

namespace window {
    // camera of the screen effects
    struct UnkScreenEffectCamera {
        dss::Camera camera_;                    // 0x00

        UnkScreenEffectCamera();
        ~UnkScreenEffectCamera();
        static UnkScreenEffectCamera* unkfunc_02028cc4();   // the instance
        void unkfunc_02028d00();                // setup
        void unkfunc_02028d40();
        void unkfunc_02028d44();                // apply
    };

    // one panel of the screen effects (position, 4 vertices, 4 texture coordinates)
    struct UnkScreenEffectPanel {
        fx32 x;                                 // 0x00
        fx32 y;                                 // 0x04
        fx32 z;                                 // 0x08
        fx16 vertex[4][3];                      // 0x0C
        fx32 texCoord[4][2];                    // 0x24
    };

    // base of the screen effects of ScreenEffectManager
    struct UnkScreenEffect {
        enum {
            FLAG_SETUP = 1,
            FLAG_ACTIVE = 2,
            FLAG_READY = 4,
        };

        virtual void setup();
        virtual void draw();
        virtual bool isEnd();

        unsigned char alpha_;                   // 0x04
        dss::Fix32 unk_08;                      // 0x08
        int unk_0c;                             // 0x0C
        int unk_10;                             // 0x10
        int unk_14;                             // 0x14
        int unk_18;                             // 0x18
        unsigned char flag_;                    // 0x1C FLAG_xxx

        UnkScreenEffect();
        ~UnkScreenEffect();
        bool unkfunc_020284cc();                // builds the panels, false while waiting
        void terminate();
        void execute();
        void unkfunc_020287e8(int polygonId);   // polygon attributes
        bool isActive();
        bool isSetup();
        bool isReady();
    };

    // rura/riremito effect
    struct UnkRiremitoEffect : UnkScreenEffect {
        int unk_20;                             // 0x20
        int angle_;                             // 0x24
        int unk_28;                             // 0x28
        int unk_2c;                             // 0x2C
        int unk_30[8];                          // 0x30
        int counter_;                           // 0x50
        int unk_54;                             // 0x54
        int unk_58;                             // 0x58
        int unk_5c;                             // 0x5C

        void setup();
        void draw();
        bool isEnd();
        void unkfunc_020289e4();                // draws the panels
    };

    // ranaruta day/night switch effect
    struct ScreenEffectRanaruta : UnkScreenEffect {
        int unk_20;                             // 0x20
        int counter_;                           // 0x24
        int waveSpeed_;                         // 0x28
        int waveHeight_;                        // 0x2C
        int unk_30[9];                          // 0x30
        short wavePanel_[10];                   // 0x54
        int morningFlag_;                       // 0x68

        void setup();
        void draw();
        bool isEnd();
        void unkfunc_020290c8(int index, int vertex, short z);  // moves a vertex shared by 4 panels
    };

    // tabi (travel door) effect
    struct ScreenEffectTravelDoor : UnkScreenEffect {
        int travelBack_;                        // 0x20
        int counter_;                           // 0x24
        int angle_;                             // 0x28
        int speed_;                             // 0x2C

        void setup();
        void draw();
        bool isEnd();
        void unkfunc_02029ba4(int travelBack);
    };

    // battle start effect
    struct ScreenEffectBattle : UnkScreenEffect {
        int counter_;                           // 0x20
        int unk_24;                             // 0x24
        int unk_28;                             // 0x28
        int unk_2c;                             // 0x2C
        int unk_30;                             // 0x30
        int unk_34;                             // 0x34

        void setup();
        void draw();
        bool isEnd();
        void unkfunc_02029588(short x, short y, short index, short* sin, short* cos);
    };

    // Screen effects played back on the map screens (cure floor, rura, battle start...)
    struct ScreenEffectManager {
        enum PLAY_BACK_EFFECT {
            PLAY_BACK_NONE = 0,
            PLAY_BACK_CURE_FLOOR = 1,
            PLAY_BACK_RURA = 2,
            PLAY_BACK_TABI = 3,
            PLAY_BACK_BATTLE = 4,
            PLAY_BACK_RANARUTA = 5,
            PLAY_BACK_RIREMITO = 6,
            PLAY_TEST_EFFECT = 7,
        };

        PLAY_BACK_EFFECT effectMode_;           // 0x00
        int soundCounter_;                      // 0x04
        int fade_;                              // 0x08
        int setupFlag_;                         // 0x0C
        int oldFlag_;                           // 0x10
        UnkScreenEffect* effect_;               // 0x14
        UnkScreenEffect unk_18;                 // 0x18
        ScreenEffectRanaruta ranarutaEffect_; // 0x38
        UnkRiremitoEffect riremitoEffect_;      // 0xA4
        ScreenEffectTravelDoor tabiEffect_;              // 0x104
        ScreenEffectBattle battleEffect_;          // 0x134

        static int travelFlag_;

        void initialize();
        void execute();
        void draw();
        void terminate();
        bool isActiveSetup();
        bool isEnd();
        bool isSetup();
        void cleanUp();
        void effectStart(PLAY_BACK_EFFECT effect);
        bool isActivate();
        void cureFloorSetup();
        void cureFloorUpdate();
    };

    extern ScreenEffectManager gScreenEffect;
}

extern window::UnkScreenEffectPanel* data_020c32a0;
