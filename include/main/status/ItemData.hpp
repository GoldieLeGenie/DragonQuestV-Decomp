#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace status {
    struct ItemData {
        static const unsigned char FLAG_EQUIP = 0x1;
        static const unsigned char FLAG_SPELL = 0x2;

        unsigned short index_;
        unsigned char count_;
        dss::UnkBitFlagUchar flag_;
        ItemData();
        ~ItemData();
        void clear();
        void setEquipment(bool flag);
        bool isEquipment();
        void setSpell(bool flag);
        bool isSpell();
    };
}
