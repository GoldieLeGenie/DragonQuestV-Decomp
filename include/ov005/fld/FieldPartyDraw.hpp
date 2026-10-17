#pragma once
#include <globaldefs.h>
#include "main/object/SpriteCharacter.hpp"

namespace fld
{
    struct FieldPartyDraw {
        static const int PARTY_DRAW_MAX = 8;

        static const unsigned short colorDoku;
        static const unsigned short colorBarrier;

        SpriteCharacter partyCharacter_[PARTY_DRAW_MAX];   // 0x000
        int count_;                                     // 0x6E0
        int countReal_;                                 // 0x6E4
        int backupCount_;                               // 0x6E8
        int carpet_;                                    // 0x6EC
        int valueY_[PARTY_DRAW_MAX];                    // 0x6F0
        short charaIndex_[PARTY_DRAW_MAX];              // 0x710

        FieldPartyDraw();
        ~FieldPartyDraw();
        void setup();
        void cleanup();
        void draw();
        void reload();
        void setPosition(int index, dss::Vector2<int> pos);
        void setRotate(int index, unsigned int dirIdx);
        void setDrawNone();
        void setDrawPartyOne();
        void resetDrawCount();
        void setShadowFlag(int index, int flag);
        void setDepth(int index, int value);
        void setMemberColor(int index, unsigned short color);
        unsigned short colorDokuParty();
        unsigned short colorBarrierParty();
        void setupChara(int index, int charaNo);
        void changePlayerPose(int charaId, int charaIndex);
    };
} // namespace fld
