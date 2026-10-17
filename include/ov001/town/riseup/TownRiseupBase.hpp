#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/Camera.hpp"

namespace twn {
    struct TownRiseupBase {
        enum {
            RISEUP_BILLBOARD_ITEM = 0,
            RISEUP_SPRITE_ANIM = 1,
            RISEUP_MODEL_ANIM = 2,
            RISEUP_BILLBOARD_SCRIPT = 3,
            RISEUP_SPRITE_MEDAL = 4,
            RISEUP_BILLBOARD_EXHIBIT = 5,
            RISEUP_BILLBOARD_NUMBER = 6,
        };

        struct RiseupParam {
            int maxHigh_;                           // 0x00
            int velocity_;                          // 0x04
            int startWait_;                         // 0x08
            int endWait_;                           // 0x0C
            int sound_;                             // 0x10
            int fadein_;                            // 0x14
            int fadeout_;                           // 0x18
        };

        // vtable                                   // 0x00
        int index_;                                 // 0x04
        dss::Fix32Vector3 position_;                // 0x08
        int enable_;                                // 0x14

        static dss::Camera* camera_;
        static dss::Fix32 near_scale;
        static RiseupParam defaultParam[4];

        TownRiseupBase();
        static void setCamera(dss::Camera* camera);
        static dss::Camera* getCamera();
        void calcNearPos(dss::Fix32Vector3& pos, dss::Fix32 scale);
        ~TownRiseupBase();
        virtual void execute();
        virtual void draw() = 0;
        virtual int getType() = 0;
        virtual int getResorceType() = 0;
        virtual void setup(int index);
        virtual void setType(int type);
        virtual void setupNear(int flag);
        virtual void setupNear2(int type);
        virtual void cleanup();
        virtual void setPosition(dss::Fix32Vector3 pos);
        virtual void setScriptData(dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame, int type);
        virtual void setScriptFade(dss::Fix32Vector3 pos, int frame, int flag);
        virtual void setEndFrame(int frame);
        virtual void setStartFrame(int frame);
        virtual bool isFinish();
        virtual void setResource(void* data) = 0;
        virtual void setExhibitIcon(int icon);
    };
}
