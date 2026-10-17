#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"

namespace status {
    struct HaveItem;

    struct HaveEquipment {
        static const int EQUIP_NONE = 0;

        int playerIndex_;
        int calcNoEquipmentItemIndex_;
        int calcEquipmentItemIndex_;
        unsigned char strength_;
        unsigned char agility_;
        unsigned char protection_;
        unsigned char wisdom_;
        unsigned char luck_;
        unsigned short hp_;
        unsigned short mp_;
        unsigned short attack_;
        unsigned short defence_;
        HaveItem* haveItem_;

        HaveEquipment();
        ~HaveEquipment();
        void setup(HaveItem* haveItem);
        void clear();
        void setEquipment(ItemType type, int itemIndex);
        void resetEquipment(ItemType type);
        void resetEquipment(int itemIndex);
        int getEquipment(ItemType type, int index) const;
        bool isEquipment(int itemIndex) const;
        void calcEffect();
        void calcEffect(int itemIndex, ItemType type);
        void calcEquipment(int itemIndex);
        unsigned short getAttack();
        unsigned short getDefence();
        unsigned char getStrength();
        unsigned char getAgility();
        unsigned char getWisdom();
        unsigned char getLuck();
    };
}
