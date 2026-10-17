#pragma once
#include <globaldefs.h>
#include "ov001/town/character/TownCharacterBase.hpp"
#include "main/object/ModelObject.hpp"

namespace twn {
    struct TownMotionlessDraw : TownCharacterBase {
        UnkStaticModelObject motionless_;       // 0x15C
        short dirIdx_;                          // 0x334
        dss::Vector3<short> modelIdx3d_;        // 0x336
        int display_;                           // 0x33C
        int defaultIndex_;                      // 0x340
        dss::Fix32 basePalletRate_;             // 0x344

        TownMotionlessDraw();
        ~TownMotionlessDraw();
        virtual void setup(TOWN_CHARACTER& chara);
        virtual void cleanup();
        void readData();
        virtual void execute();
        virtual void draw();
        virtual void setDisplay(int flag);
        virtual int isDisplay();
        virtual void changePose(int set);
        virtual void restorePose();
        virtual void requestReload();
        virtual void setScale(dss::Fix32 scale);
        virtual void setPosition(dss::Fix32Vector3& target);
        virtual void setRotation(dss::Vector3<short>& rot);
        dss::Fix32Vector3 getPosition();
        virtual void setAnimation(int flag);
        virtual void setPaletteRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b);
        virtual void setPaletteRate(unsigned char r, unsigned char g, unsigned char b, dss::Fix32 rate);
        virtual void setDir(int dir);
        virtual void setPalletRate(dss::Fix32 rate);
        virtual int getDir();
    };
}
