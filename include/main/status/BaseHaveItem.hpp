#pragma once
#include <globaldefs.h>
#include "main/status/ItemData.hpp"

namespace status{
    struct BaseHaveItem {
        static const int ITEM_NONE = -1;
        status::ItemData* item_;
        int itemMax_;
        BaseHaveItem();
        ~BaseHaveItem();
        void operator=(BaseHaveItem& rhs);
        virtual void clear();
        virtual int add(int itemIndex);
        virtual bool del(int ctrlId);
        int addOne(int itemIndex);
        int addNum(int itemIndex, int count);
        bool delOne(int ctrlId);
        bool delNum(int ctrlId);
        void sort();
        int getCount() const;
        int getMaxCount() const;
        int getItem(int index) const;
        int getItemSortIndex(int itemIndex) const;
        status::ItemData& getItemData(int index);
        int getItemCount(int index) const;
        bool isItem(int itemIndex) const;
        int getItemMax();
        void setEquipment(int index);
        void resetEquipment(int index);
        void resetEquipmentWithItemIndex(int itemIndex);
        bool isEquipment(int index) const;
        virtual void sortEquipment();
        void setSpell(int index, bool flag);
    };
}
