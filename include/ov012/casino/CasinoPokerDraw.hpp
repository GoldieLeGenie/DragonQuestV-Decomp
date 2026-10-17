#pragma once
#include <globaldefs.h>
#include "main/data/DataObject.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkTextureObject.hpp"
#include "ov012/casino/PokerCard.hpp"

namespace casino {
    struct CasinoPokerDraw {
        static const int MAX_CARD_TYPE = 6;
        static const int MAX_CARD_INSTANCE = 5;

        dss::Fix32 cardDistance_;                       // 0x000
        dss::Fix32 cardDepth_;                          // 0x004
        dss::Fix32 cardSpace_;                          // 0x008
        dss::Fix32 cardScale_;                          // 0x00C
        dss::Fix32Vector3 defaultPos[MAX_CARD_INSTANCE];    // 0x010
        DataObject cardObject[MAX_CARD_TYPE];           // 0x04C
        UnkTextureObject* cardTexture_[MAX_CARD_TYPE];  // 0x0AC
        PokerCard card[MAX_CARD_INSTANCE];              // 0x0C4
        unsigned char alpha_;                           // 0xC54

        CasinoPokerDraw();
        ~CasinoPokerDraw();
        static CasinoPokerDraw* getSingleton();
        void initialize();
        void setPoolPosition();
        void setHighLowPosition();
        void terminate();
        void draw();
        void setCardReverse(int cardIndex);
        void setCardTexture(int cardIndex, int type, int number);
        void setBackCardTexture();
        void setEffectCardTexture();
        void setCardPosition(int cardIndex, dss::Fix32Vector3 pos);
        dss::Fix32Vector3 getCardPosition(int cardIndex);
        dss::Fix32 getDistance();
        dss::Fix32 getSpace();
        void setCardAngle(int cardIndex, unsigned short angle);
        void setEffect(int cardIndex);
        void setDisplay(int cardIndex, bool flag);
        void setAlpha(int cardIndex, unsigned char alpha);
        unsigned char getAlpha();
    };
}
