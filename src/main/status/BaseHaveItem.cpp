#include "main/status/BaseHaveItem.hpp"
#include "main/status/UseItem.hpp"

inline void status::BaseHaveItem::sortEquipment()
{
}

THUMB status::BaseHaveItem::BaseHaveItem()
{
}

THUMB status::BaseHaveItem::~BaseHaveItem()
{
}

THUMB void status::BaseHaveItem::operator=(BaseHaveItem& rhs)
{
    for (int i = 0; i < itemMax_; i++) {
        item_[i] = rhs.getItemData(i);
    }
}

THUMB void status::BaseHaveItem::clear()
{
    for (int i = 0; i < itemMax_; i++) {
        item_[i].clear();
    }
}

THUMB int status::BaseHaveItem::add(int itemIndex)
{
    return addOne(itemIndex);
}

THUMB bool status::BaseHaveItem::del(int ctrlId)
{
    return delOne(ctrlId);
}

THUMB int status::BaseHaveItem::addOne(int itemIndex)
{
    if (itemIndex == 0) {
        return ITEM_NONE;
    }
    int index = 0;
    for (int i = 0; i < itemMax_; i++) {
        if (item_[i].index_ == 0) {
            item_[i].index_ = itemIndex;
            item_[i].count_ = 1;
            index = i;
            break;
        }
    }
    return index;
}

THUMB int status::BaseHaveItem::addNum(int itemIndex, int count)
{
    int index = 0;
    for (int i = 0; i < itemMax_; i++) {
        if (item_[i].index_ == itemIndex) {
            item_[i].index_ = itemIndex;
            item_[i].count_ += (unsigned char)count;
            index = i;
            break;
        }
        if (item_[i].index_ == 0) {
            item_[i].index_ = itemIndex;
            item_[i].count_ = count;
            index = i;
            break;
        }
    }
    return index;
}

THUMB bool status::BaseHaveItem::delOne(int ctrlId)
{
    item_[ctrlId].clear();
    sort();
    return true;
}

THUMB bool status::BaseHaveItem::delNum(int ctrlId)
{
    if (item_[ctrlId].count_ == 0) {
        return false;
    }
    item_[ctrlId].count_--;
    if (item_[ctrlId].count_ == 0) {
        item_[ctrlId].index_ = 0;
        sort();
    }
    return true;
}

THUMB void status::BaseHaveItem::sort()
{
    ItemData itemTemp_[263];
    for (int i = 0; i < itemMax_; i++) {
        itemTemp_[i].clear();
    }
    int idx = 0;
    for (int i = 0; i < itemMax_; i++) {
        if (item_[i].index_ != 0) {
            itemTemp_[idx] = item_[i];
            idx++;
        }
    }
    BaseHaveItem::clear();
    for (int i = 0; i < itemMax_; i++) {
        item_[i] = itemTemp_[i];
    }
}

THUMB int status::BaseHaveItem::getCount() const
{
    int count = 0;
    for (int i = 0; i < itemMax_; i++) {
        if (item_[i].index_ != 0) {
            count++;
        }
    }
    return count;
}

THUMB int status::BaseHaveItem::getMaxCount() const
{
    return itemMax_;
}

THUMB int status::BaseHaveItem::getItem(int index) const
{
    return item_[index].index_;
}

THUMB int status::BaseHaveItem::getItemSortIndex(int itemIndex) const
{
    int index = ITEM_NONE;
    for (int i = 0; i < itemMax_; i++) {
        if (itemIndex == item_[i].index_) {
            index = i;
            break;
        }
    }
    return index;
}

THUMB status::ItemData& status::BaseHaveItem::getItemData(int index)
{
    return item_[index];
}

THUMB int status::BaseHaveItem::getItemCount(int index) const
{
    return item_[index].count_;
}

THUMB bool status::BaseHaveItem::isItem(int itemIndex) const
{
    for (int i = 0; i < itemMax_; i++) {
        if (itemIndex == item_[i].index_) {
            return true;
        }
    }
    return false;
}

THUMB int status::BaseHaveItem::getItemMax()
{
    return itemMax_;
}

THUMB void status::BaseHaveItem::setEquipment(int index)
{
    if (index != ITEM_NONE) {
        item_[index].setEquipment(true);
        setSpell(index, true);
        sortEquipment();
    }
}

THUMB void status::BaseHaveItem::resetEquipment(int index)
{
    item_[index].setEquipment(false);
    sortEquipment();
}

THUMB void status::BaseHaveItem::resetEquipmentWithItemIndex(int itemIndex)
{
    for (int i = 0; i < getCount(); i++) {
        if (item_[i].isEquipment() && itemIndex == item_[i].index_) {
            resetEquipment(i);
            return;
        }
    }
}

THUMB bool status::BaseHaveItem::isEquipment(int index) const
{
    return item_[index].isEquipment();
}

THUMB void status::BaseHaveItem::setSpell(int index, bool flag)
{
    if (UseItem::isCurse(item_[index].index_)) {
        item_[index].setSpell(flag);
    }
}
