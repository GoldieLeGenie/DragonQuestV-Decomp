#pragma once
#include <globaldefs.h>

namespace status {
    struct BaseStatus {
        int exp_;
        unsigned short strength_;
        unsigned short protection_;
        unsigned short hp_;
        unsigned short hpMax_;
        unsigned short mp_;
        unsigned short mpMax_;
        unsigned char agility_;
        unsigned char wisdom_;
        unsigned char luck_;
        unsigned char level_;
        BaseStatus();
        ~BaseStatus();
        void clear();
        void setStrength(unsigned char strength);
        void addStrength(char value);
        void setAgility(unsigned char agility);
        void addAgility(char value);
        void setProtection(unsigned char protection);
        void addProtection(char value);
        void setWisdom(unsigned char wisdom);
        void addWisdom(char value);
        void setLuck(unsigned char luck);
        void addLuck(unsigned char value);
        void setHp(unsigned short hp);
        void setHpMax(unsigned short hpMax);
        void addHpMax(char value);
        void setMp(unsigned short mp);
        void setMpMax(unsigned short mpMax);
        void addMpMax(char value);
    };
}
