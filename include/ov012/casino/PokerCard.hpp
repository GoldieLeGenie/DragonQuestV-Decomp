#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkPolygonObject.hpp"

namespace casino {
    // card face drawn with a rotation around the vertical axis
    struct PokerCardPolygon : UnkPolygonObject {
        virtual void draw();

        unsigned short angle_;                  // 0x84

        PokerCardPolygon();
        ~PokerCardPolygon();
    };

    struct PokerCard {
        static const int MAX_FRAME = 30;

        PokerCardPolygon unk_000;               // 0x000 front
        PokerCardPolygon unk_088;               // 0x088 back
        PokerCardPolygon unk_110;               // 0x110 effect
        PokerCardPolygon unk_198;               // 0x198 effect base
        dss::Flag m_ctrl;                       // 0x220
        int m_effect_frame;                     // 0x224
        int unk_228;                            // 0x228 effect scroll speed
        int m_effect_enable;                    // 0x22C
        UnkBillboardTexCoord unk_230;           // 0x230 effect texture coordinates

        PokerCard();
        ~PokerCard();
        void setup();
        void unkfunc_021282f0(dss::Fix32 scale);
        void unkfunc_02128350(const UnkPolygonVertex* vertex);
        void setPosition(dss::Fix32Vector3& pos);
        dss::Fix32Vector3 getPosition();
        void setAngle(int angle);
        void unkfunc_02128400(const UnkBillboardTexCoord* texCoord);
        void unkfunc_02128408(const UnkBillboardTexCoord* texCoord);
        void unkfunc_02128414(const UnkBillboardTexCoord* texCoord);
        void unkfunc_021284a0(const UnkBillboardTexCoord* texCoord);
        void unkfunc_021284b0(void* texture);
        void unkfunc_021284b4(void* texture);
        void unkfunc_021284bc(void* texture);
        void unkfunc_021284c4(void* texture);
        void draw();
        void setEffect();
        void unkfunc_02128688(bool enable);
        void setAlpha(unsigned char alpha);
    };
}
