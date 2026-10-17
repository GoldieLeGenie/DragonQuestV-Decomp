#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace cmn
{
    struct MembaerDamage {
        int type;                               // 0x00
        int counter;                            // 0x04
        int frame;                              // 0x08
    };

    struct CommonWalkDamage {
        static const int PARTY_DAMAGE_COUNT = 4;

        // vtable                               // 0x00
        int seCounter_;                         // 0x04
        int nextSe_;                            // 0x08
        int nextSeType_;                        // 0x0C
        int nextWatSe_;                         // 0x10
        int watCounter_;                        // 0x14

        static int topStride_;
        static int memberDamage_;
        static int encountFlag_;
        static int damageFlag_;
        static int effectFlag_;
        static int walkCount_;
        static int partyStride_;
        static MembaerDamage partyDamage_[PARTY_DAMAGE_COUNT];
        static char damage_[82];

        void setup();
        void clear();
        void setDamageFlag(bool flag);
        void setEffectFlag(bool flag);
        void setCounter(int count);
        bool checkWalkStride();
        int getDamageStride(int type);
        void checkWalk(dss::Fix32Vector3& position, dss::Fix32Vector3& prevPosition);
        virtual bool checkBarrier() = 0;
        virtual bool checkPoison() = 0;
        virtual bool checkYogan();
        virtual bool checkPuddle();
        virtual void setPartyMemberColor(int playerIndex, int type) = 0;
        virtual void setPuddleEffect(int index);
        bool isPlaySe();
        void setNextSe(int type);
        void resetMemberColor();
    };
} // namespace cmn
