#pragma once
#include <globaldefs.h>
#include "main/cmn/CommonEffect.hpp"

namespace btl {
    struct BattleEffectGroup {
        static const int FIRST = 0;
        static const int SECOND = 1;
        static const int MAX_EFFECT = 2;
        static const int FLAG_FIRST_DRAW = 0x1;
        static const int FLAG_SECOND_DRAW = 0x2;

        dss::BitFlag<unsigned char> flag_;          // 0x000
        dss::BitFlag<unsigned char> state_;         // 0x001
        int regist_;                                // 0x004
        cmn::CommonEffectFlat effectFlat_;          // 0x008
        cmn::CommonEffectCubic effectCubic_;        // 0x0D8
        cmn::CommonEffectSimple* effectSimple_[MAX_EFFECT]; // 0x3EC

        BattleEffectGroup();
        ~BattleEffectGroup();
        void init();
        void draw();
        void extraDraw();
        void start();
        void addEffect(cmn::CommonEffectData* data, bool flag);
        void cleanup(bool flag);
        void setScale(dss::Fix32 scale);
        void setDisplayType(int type, int index);
        void setPosition(dss::Fix32Vector3& position);
        bool isEnable();
        bool isEnd();
    };
}
