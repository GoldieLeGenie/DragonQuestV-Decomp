#pragma once
#include <globaldefs.h>
#include "main/status/BaseHaveItem.hpp"
#include "main/status/ItemData.hpp"

namespace status {
    struct HaveItem;
}

namespace status{
    struct HaveItemSack : BaseHaveItem {
        enum SortType {
            Kind = 0x0,
            Name = 0x1,
            Same = 0x2,
        };
        SortType sortType_;         // 0x0C
        ItemData itemArray_[263];   // 0x10
        char name_[26];             // 0x42C
        int cursedName_;            // 0x448
        HaveItemSack();
        ~HaveItemSack();
        void setNameString(const char* name);
        void setCursedName(int flag);
        int getCursedName();
        int add(int itemIndex, int count);
        virtual int add(int itemIndex);
        virtual bool del(int ctrlId);
        void execThrow(int index);
        void sortOutSack(SortType type);
        void sortOutItem(HaveItem& haveItem);
        void sortOutItemOne(HaveItem& haveItem);
    };
}
