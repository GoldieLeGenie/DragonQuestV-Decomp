#pragma ipa file
#include "main/status/HaveItemSack.hpp"
#include "main/status/HaveItem.hpp"
#include "main/status/UseItem.hpp"
#include "main/dss/DssUtils.hpp"

inline void status::BaseHaveItem::sortEquipment()
{
}

THUMB status::HaveItemSack::HaveItemSack() : sortType_(Kind)
{
    item_ = itemArray_;
    itemMax_ = 263;
    clear();
    setNameString("----");
}

THUMB status::HaveItemSack::~HaveItemSack()
{
}

THUMB void status::HaveItemSack::setNameString(const char* name)
{
    dss::strcpy(name_, name);
}

THUMB int status::HaveItemSack::add(int itemIndex, int count)
{
    int index = getItemSortIndex(itemIndex);
    if (getItemCount(index) + count <= 99) {
        return addNum(itemIndex, count);
    }
    int cnt = 99 - getItemCount(index);
    return addNum(itemIndex, cnt);
}

THUMB int status::HaveItemSack::add(int itemIndex)
{
    return add(itemIndex, 1);
}

THUMB bool status::HaveItemSack::del(int ctrlId)
{
    return delNum(ctrlId);
}

THUMB void status::HaveItemSack::execThrow(int index)
{
    del(index);
}

THUMB void status::HaveItemSack::sortOutSack(SortType type)
{
    if (type == Same) {
        type = sortType_;
    } else {
        sortType_ = type;
    }
    ItemData itemTemp[263];
    for (int i = 0; i < itemMax_; i++) {
        itemTemp[i].clear();
    }
    int idx = 0;
    int sortIndex;
    for (int j = 0; j < itemMax_; j++) {
        sortIndex = j + 1;
        for (int i = 0; i < itemMax_; i++) {
            if (item_[i].index_ != 0) {
                if (type == Kind) {
                    if (sortIndex == UseItem::getTypeSortIndex(item_[i].index_)) {
                        itemTemp[idx++] = item_[i];
                        item_[i].index_ = 0;
                        break;
                    }
                } else if (type == Name) {
                    if (sortIndex == UseItem::getNameSortIndex(item_[i].index_)) {
                        itemTemp[idx++] = item_[i];
                        item_[i].index_ = 0;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < itemMax_; i++) {
        if (itemTemp[i].index_ != 0) {
            item_[i] = itemTemp[i];
        }
    }
}

THUMB void status::HaveItemSack::sortOutItem(HaveItem& haveItem)
{
    for (int i = 0; i < haveItem.getMaxCount(); i++) {
        sortOutItemOne(haveItem);
    }
}

THUMB void status::HaveItemSack::sortOutItemOne(HaveItem& haveItem)
{
    for (int i = 0; i < haveItem.getCount(); i++) {
        if (!haveItem.isEquipment(i) && UseItem::isOrder(haveItem.getItem(i))) {
            add(haveItem.getItem(i));
            haveItem.del(i);
            return;
        }
    }
}
