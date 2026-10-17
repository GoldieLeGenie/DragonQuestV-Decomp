#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/cmn/CommonEffectResource.hpp"
#include "ov001/town/riseup/TownRiseupStorage.hpp"
#include "ov001/town/riseup/BillbordItemResource.hpp"

namespace twn {
    struct TownRiseupManager {
        static const int RISEUP_MAX = 32;
        static const int SMALL_MEDAL_EFFECT = 0x38c;

        TownRiseupStorage riseupStorage_;               // 0x0000
        BillbordItemResource riseupResourece_;          // 0x17C4
        cmn::CommonEffectResource effectResourece_;     // 0x38D0
        TownRiseupBase* riseup_[RISEUP_MAX];            // 0x4140

        static int riseupCounter_;

        TownRiseupManager();
        ~TownRiseupManager();
        static TownRiseupManager& getSingleton();
        void initialize();
        void terminate();
        int setup(int index, dss::Fix32Vector3 position);
        int setupMedal(dss::Fix32Vector3 position);
        int setupSprite(int index, dss::Fix32Vector3 position, int near, int startFrame);
        int setupSprite2(int index, dss::Fix32Vector3 position, int near, int startFrame);
        int setupScript(int index, dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame);
        int setupSpriteMove(int index, dss::Fix32Vector3 start, dss::Fix32Vector3 end, int frame, int type);
        int setupModel(int index, dss::Fix32Vector3 position);
        int setupSpriteFade(int index, dss::Fix32Vector3 position, int frame, int flag);
        int setupExhibitIcon(int icon, dss::Fix32Vector3 position);
        void setFadeIn(int index, int frame);
        void setFadeOut(int index, int frame);
        void setPosition(int index, dss::Fix32Vector3 position);
        void cleanup(int index);
        void draw();
        void execute();
        bool isFinish(int index);
        bool isEnable(int index);
        int getSpriteNum();
    };
}
