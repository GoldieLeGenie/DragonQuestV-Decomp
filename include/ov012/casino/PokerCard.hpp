#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"
#include "main/dss/PolygonObject.hpp"

namespace casino {
    // card face drawn with a rotation around the vertical axis
    struct PokerCardPolygon : PolygonObject {
        virtual void draw();

        unsigned short angle_;                  // 0x84

        PokerCardPolygon();
        ~PokerCardPolygon();
    };

    struct PokerCard {
        static const int MAX_FRAME = 30;

        PokerCardPolygon m_front_polygon;               // 0x000 front
        PokerCardPolygon m_back_polygon;               // 0x088 back
        PokerCardPolygon m_shine_polygon;               // 0x110 effect
        PokerCardPolygon m_glow_polygon;               // 0x198 effect base
        dss::Flag m_ctrl;                       // 0x220
        int m_effect_frame;                     // 0x224
        int m_shine_scroll_speed;                            // 0x228 effect scroll speed
        int m_effect_enable;                    // 0x22C
        UnkBillboardTexCoord m_shine_tex_coord;           // 0x230 effect texture coordinates

        PokerCard();
        ~PokerCard();
        void setup();
        void setScale(dss::Fix32 scale);
        void setVertex(const UnkPolygonVertex* vertex);
        void setPosition(dss::Fix32Vector3& pos);
        dss::Fix32Vector3 getPosition();
        void setAngle(int angle);
        void setFrontTexCoord(const UnkBillboardTexCoord* texCoord);
        void setBackTexCoord(const UnkBillboardTexCoord* texCoord);
        void setShineTexCoord(const UnkBillboardTexCoord* texCoord);
        void setGlowTexCoord(const UnkBillboardTexCoord* texCoord);
        void setFrontTexture(void* texture);
        void setBackTexture(void* texture);
        void setShineTexture(void* texture);
        void setGlowTexture(void* texture);
        void draw();
        void setEffect();
        void setVisible(bool enable);
        void setAlpha(unsigned char alpha);
    };
}
