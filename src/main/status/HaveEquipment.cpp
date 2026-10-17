#include "main/status/HaveEquipment.hpp"
#include "main/status/HaveItem.hpp"
#include "main/status/UseItem.hpp"
#include "main/dss/DssUtils.hpp"


THUMB status::HaveEquipment::HaveEquipment()
{
    strength_ = 0;
    agility_ = 0;
    protection_ = 0;
    wisdom_ = 0;
    luck_ = 0;
    attack_ = 0;
    defence_ = 0;
}

THUMB status::HaveEquipment::~HaveEquipment()
{
}

THUMB void status::HaveEquipment::setup(HaveItem* haveItem)
{
    haveItem_ = haveItem;
    calcNoEquipmentItemIndex_ = EQUIP_NONE;
    calcEquipmentItemIndex_ = EQUIP_NONE;
}

THUMB void status::HaveEquipment::clear()
{
    strength_ = 0;
    agility_ = 0;
    protection_ = 0;
    wisdom_ = 0;
    luck_ = 0;
    attack_ = 0;
    defence_ = 0;
}

THUMB void status::HaveEquipment::setEquipment(ItemType type, int itemIndex)
{
}

THUMB void status::HaveEquipment::resetEquipment(ItemType type)
{
}

THUMB void status::HaveEquipment::resetEquipment(int itemIndex)
{
}

THUMB int status::HaveEquipment::getEquipment(ItemType type, int index) const
{
    return haveItem_->getEquipmentItem(type, index);
}

THUMB bool status::HaveEquipment::isEquipment(int itemIndex) const
{
    return haveItem_->isEquipmentInAllItem(itemIndex);
}

THUMB void status::HaveEquipment::calcEffect()
{
    int itemIndex;

    strength_ = 0;
    agility_ = 0;
    wisdom_ = 0;
    luck_ = 0;
    attack_ = 0;
    defence_ = 0;

    itemIndex = haveItem_->getEquipmentItem(ITEM_WEAPON, 0);
    calcEffect(itemIndex, ITEM_WEAPON);
    itemIndex = haveItem_->getEquipmentItem(ITEM_ARMOR, 0);
    calcEffect(itemIndex, ITEM_ARMOR);
    itemIndex = haveItem_->getEquipmentItem(ITEM_SHIELD, 0);
    calcEffect(itemIndex, ITEM_SHIELD);
    itemIndex = haveItem_->getEquipmentItem(ITEM_HELMET, 0);
    calcEffect(itemIndex, ITEM_HELMET);
    itemIndex = haveItem_->getEquipmentItem(ITEM_ACCESSORY, 0);
    calcEffect(itemIndex, ITEM_ACCESSORY);
    itemIndex = haveItem_->getEquipmentItem(ITEM_ACCESSORY, 1);
    calcEffect(itemIndex, ITEM_ACCESSORY);
    itemIndex = haveItem_->getEquipmentItem(ITEM_ACCESSORY, 2);
    calcEffect(itemIndex, ITEM_ACCESSORY);
    itemIndex = haveItem_->getEquipmentItem(ITEM_ACCESSORY, 3);
    calcEffect(itemIndex, ITEM_ACCESSORY);
    itemIndex = haveItem_->getEquipmentItem(ITEM_ACCESSORY, 4);
    calcEffect(itemIndex, ITEM_ACCESSORY);
    itemIndex = haveItem_->getEquipmentItem(ITEM_ACCESSORY, 5);
    calcEffect(itemIndex, ITEM_ACCESSORY);
    itemIndex = haveItem_->getEquipmentItem(ITEM_ACCESSORY, 6);
    calcEffect(itemIndex, ITEM_ACCESSORY);
}

THUMB void status::HaveEquipment::calcEffect(int itemIndex, ItemType type)
{
    if (calcNoEquipmentItemIndex_ != EQUIP_NONE && calcNoEquipmentItemIndex_ == itemIndex) {
        calcNoEquipmentItemIndex_ = EQUIP_NONE;
        return;
    }
    if (calcEquipmentItemIndex_ != EQUIP_NONE) {
        if (UseItem::getEquipItemType(itemIndex) == UseItem::getEquipItemType(calcEquipmentItemIndex_)) {
            itemIndex = calcEquipmentItemIndex_;
            calcEquipmentItemIndex_ = EQUIP_NONE;
        }
        if (itemIndex == EQUIP_NONE && type == UseItem::getEquipItemType(calcEquipmentItemIndex_)) {
            itemIndex = calcEquipmentItemIndex_;
            calcEquipmentItemIndex_ = EQUIP_NONE;
        }
    }
    if (itemIndex != EQUIP_NONE) {
        EquipType equipType = UseItem::getEquipType(itemIndex);
        int value = UseItem::getEquipValue(itemIndex);

        switch (equipType) {
        case Strength:
            strength_ += value;
            break;
        case Agility:
            if (dss::abs<int>(value) != 10000) {
                agility_ += value;
            }
            break;
        case Wisdom:
            wisdom_ += value;
            break;
        case Luck:
            luck_ += value;
            break;
        case Attack:
            attack_ += value;
            break;
        case Defence:
            defence_ += value;
            break;
        }
    }
}
