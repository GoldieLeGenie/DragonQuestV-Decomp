#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/CharacterStatus.hpp"

namespace status {
    struct PlayerStatus : CharacterStatus {
        static const int WALK_COUNT = 16;

        short index_;                                   // 0x508
        short characterIndex_;                          // 0x50A
        short walkCount_;                               // 0x50C
        short walkCountBarrier_;                        // 0x50E
        short walkCountPoison_;                         // 0x510
        short walkCountVenom_;                          // 0x512
        short walkCountLuckHat_;                        // 0x514
        short walkCountLifeRing_;                       // 0x516
        short walkCountCurse4_;                         // 0x518
        short walkCountCurse5_;                         // 0x51A

        PlayerStatus();
        ~PlayerStatus();
        void setup(int index);
        short getIndex();
        void cleanup();
        void levelup(int level);
        void setBestCondition();
        bool walkDamage(StageDamage damage);
        bool walkNormal();
        void walkEnvioronment();
        void setWalkDamage(int dmg);
        void clearWalkDamage(bool flag);
        bool setWalkEffectPoison();
        bool setWalkEffectVenom();
        void setWalkEffectLuckHat();
        void setWalkEffectLifeRing();
        bool setWalkEffectCurse4();
        bool setWalkEffectCurse5();
        void execStartOfRound();
        void execOfRound();
        bool isAlive() const;
        int getPlayerIndex();
        int getPlayerKindIndex();
        int getCharaIndex();
        virtual void print();
        virtual void printAction();
    };
}
