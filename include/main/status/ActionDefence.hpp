#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/leveldata/ActionParam.hpp"

namespace status{
    struct ActionDefence {
        int disable_;                       // 0x00
        CharacterType characterType_;       // 0x04
        unsigned char mera_;                // 0x08
        unsigned char gira_;                // 0x09
        unsigned char io_;                  // 0x0A
        unsigned char hyado_;               // 0x0B
        unsigned char bagi_;                // 0x0C
        unsigned char dein_;                // 0x0D
        unsigned char zaki_;                // 0x0E
        unsigned char megante_;             // 0x0F
        unsigned char nifram_;              // 0x10
        unsigned char manusa_;              // 0x11
        unsigned char medapani_;            // 0x12
        unsigned char rariho_;              // 0x13
        unsigned char rarihoma_;            // 0x14
        unsigned char mahotone_;            // 0x15
        unsigned char mahotora_;            // 0x16
        unsigned char rukani_;              // 0x17
        unsigned char rukanan_;             // 0x18
        unsigned char sukara_;              // 0x19
        unsigned char fire_;                // 0x1A
        unsigned char blizzard_;            // 0x1B
        unsigned char poison_;              // 0x1C
        unsigned char venom_;               // 0x1D
        unsigned char spazz_;               // 0x1E
        unsigned char rest_;                // 0x1F
        unsigned char all_;                 // 0x20
        unsigned char half_;                // 0x21
        unsigned char success_1_4_;         // 0x22
        unsigned char success_1_6_;         // 0x23
        unsigned char success_1_8_;         // 0x24
        unsigned char success_3_4_;         // 0x25
        unsigned char success_3_8_;         // 0x26
        unsigned char success_5_8_;         // 0x27
        unsigned char embrace_;             // 0x28

        ActionDefence();
        ~ActionDefence();
        void setDisable(bool flag);
        void setup(unsigned short index, CharacterType type);
        void setupPlayer(unsigned short index);
        void setupMonster(unsigned short index);
        int getEffect(dq5::level::ActionParam::DEFENCETYPE type, unsigned char value);
        int calc(dq5::level::ActionParam::DEFENCE kind, dq5::level::ActionParam::DEFENCETYPE type, int actionIndex);
        int getEffectAI(dq5::level::ActionParam::DEFENCETYPE type, unsigned char value);
        int calcAI(dq5::level::ActionParam::DEFENCE kind, dq5::level::ActionParam::DEFENCETYPE type, int actionIndex);
        int getEffectValue(int actionIndex);
        int getEffectValueAI(int actionIndex);
        unsigned char getZaki();
        int getMedapani();
        int getRariho();
        int getVenom();
        void setNifram(unsigned char nif);
    };
}
