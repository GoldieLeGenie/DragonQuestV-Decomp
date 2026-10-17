#pragma once
#include <globaldefs.h>
#include "GameInfo.hpp"
#include "main/status/BaseHaveItem.hpp"
#include "main/status/ItemData.hpp"

namespace status {
    struct HaveItem : BaseHaveItem {
        static const int ITEM_MAX = 12;
        ItemData itemArray_[ITEM_MAX];
        static int sortEnable_;     // data_02093ec8
        HaveItem();
        ~HaveItem();
        void setup(int index);
        void cleanup(int index);
        virtual void clear();
        virtual int add(int itemIndex);
        virtual bool del(int ctrlId);
        virtual void sortEquipment();
        static void setSortEnable(bool flag);
        int getEquipmentItem(ItemType type, int index);
        bool isEquipmentInAllItem(int itemIndex);
        bool isSpace();
        bool isSpell();
    };
}
