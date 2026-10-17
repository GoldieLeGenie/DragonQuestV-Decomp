#include "main/status/HaveItem.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/UseItem.hpp"

inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index)
{
    return playerData_[index];
}

inline status::HaveItem& status::PlayerData::getHaveItem()
{
    return haveItem_;
}

inline void status::PlayerData::setHaveItem(HaveItem& item)
{
    haveItem_ = item;
}

int status::HaveItem::sortEnable_ = 1;

THUMB status::HaveItem::HaveItem()
{
    item_ = itemArray_;
    itemMax_ = ITEM_MAX;
    clear();
}

THUMB status::HaveItem::~HaveItem()
{
}

THUMB void status::HaveItem::setup(int index)
{
    clear();
    PlayerData& playerData = PlayerDataAll::getPlayerData(index);
    *this = playerData.getHaveItem();
}

THUMB void status::HaveItem::cleanup(int index)
{
    PlayerData& playerData = PlayerDataAll::getPlayerData(index);
    playerData.setHaveItem(*this);
}

THUMB void status::HaveItem::clear()
{
    BaseHaveItem::clear();
}

THUMB int status::HaveItem::add(int itemIndex)
{
    return addOne(itemIndex);
}

THUMB bool status::HaveItem::del(int ctrlId)
{
    bool ret = delOne(ctrlId);
    sortEquipment();
    return ret;
}

THUMB void status::HaveItem::sortEquipment()
{
    if (sortEnable_ == 0) {
        return;
    }

    ItemData itemTemp[ITEM_MAX];
    for (int i = 0; i < ITEM_MAX; i++) {
        itemTemp[i].index_ = 0;
    }

    int tempIndex = 0;
    for (int i = 0; i < ITEM_MAX; i++) {
        if (item_[i].index_ != 0 && item_[i].isEquipment() && UseItem::getEquipItemType(item_[i].index_) == ITEM_WEAPON) {
            itemTemp[tempIndex++] = item_[i];
            item_[i].index_ = 0;
        }
    }
    for (int i = 0; i < ITEM_MAX; i++) {
        if (item_[i].index_ != 0 && item_[i].isEquipment() && UseItem::getEquipItemType(item_[i].index_) == ITEM_ARMOR) {
            itemTemp[tempIndex++] = item_[i];
            item_[i].index_ = 0;
        }
    }
    for (int i = 0; i < ITEM_MAX; i++) {
        if (item_[i].index_ != 0 && item_[i].isEquipment() && UseItem::getEquipItemType(item_[i].index_) == ITEM_SHIELD) {
            itemTemp[tempIndex++] = item_[i];
            item_[i].index_ = 0;
        }
    }
    for (int i = 0; i < ITEM_MAX; i++) {
        if (item_[i].index_ != 0 && item_[i].isEquipment() && UseItem::getEquipItemType(item_[i].index_) == ITEM_HELMET) {
            itemTemp[tempIndex++] = item_[i];
            item_[i].index_ = 0;
        }
    }
    for (int i = 0; i < ITEM_MAX; i++) {
        if (item_[i].index_ != 0 && item_[i].isEquipment() && UseItem::getEquipItemType(item_[i].index_) == ITEM_ACCESSORY) {
            itemTemp[tempIndex++] = item_[i];
            item_[i].index_ = 0;
        }
    }
    for (int i = 0; i < ITEM_MAX; i++) {
        if (item_[i].index_ != 0) {
            itemTemp[tempIndex++] = item_[i];
            item_[i].index_ = 0;
        }
    }
    for (int i = 0; i < ITEM_MAX; i++) {
        if (itemTemp[i].index_ != 0) {
            item_[i] = itemTemp[i];
        }
    }
}

THUMB int status::HaveItem::getEquipmentItem(ItemType type, int index)
{
    int equipCount = 0;
    int count = getCount();
    for (int i = 0; i < count; i++) {
        if (isEquipment(i)) {
            int itemIndex = getItem(i);
            if (type == UseItem::getEquipItemType(itemIndex)) {
                if (equipCount == index) {
                    return itemIndex;
                }
                equipCount++;
            }
        }
    }
    return 0;
}

THUMB bool status::HaveItem::isEquipmentInAllItem(int itemIndex)
{
    int count = getCount();
    for (int i = 0; i < count; i++) {
        if (isEquipment(i) && itemIndex == getItem(i)) {
            return true;
        }
    }
    return false;
}

THUMB bool status::HaveItem::isSpace()
{
    if (getCount() < ITEM_MAX) {
        return true;
    }
    return false;
}

THUMB bool status::HaveItem::isSpell()
{
    for (int i = 0; i < itemMax_; i++) {
        if (item_[i].isSpell()) {
            return true;
        }
    }
    return false;
}
