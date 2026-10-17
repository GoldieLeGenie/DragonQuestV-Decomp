#include "main/status/ShopList.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/leveldata/ShopData1.hpp"
#include "main/leveldata/ShopData2.hpp"
#include "main/leveldata/ShopData3.hpp"
#include "main/leveldata/ShopDataSugoroku.hpp"

inline unsigned long dq5::level::ShopData1::getPrice()
{
    return price;
}

inline unsigned short dq5::level::ShopData1::getItem()
{
    return item;
}

inline unsigned long dq5::level::ShopData2::getPrice()
{
    return price;
}

inline unsigned short dq5::level::ShopData2::getItem()
{
    return item;
}

inline unsigned long dq5::level::ShopData3::getPrice()
{
    return price;
}

inline unsigned short dq5::level::ShopData3::getItem()
{
    return item;
}

inline unsigned long dq5::level::ShopDataSugoroku::getPrice()
{
    return price;
}

inline unsigned short dq5::level::ShopDataSugoroku::getItem()
{
    return item;
}

inline void status::ShopList::setSection(int section)
{
    section_ = section;
}

inline dq5::level::ShopData1* dq5::level::ShopData1::getRecord(int index)
{
    return (ShopData1*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::ShopData2* dq5::level::ShopData2::getRecord(int index)
{
    return (ShopData2*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::ShopData3* dq5::level::ShopData3::getRecord(int index)
{
    return (ShopData3*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::ShopDataSugoroku* dq5::level::ShopDataSugoroku::getRecord(int index)
{
    return (ShopDataSugoroku*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int status::StageAttribute::getShopDataIndex() { return shopDataIndex_; }

status::ShopList status::g_Shop;
int status::ShopList::section_;

THUMB status::ShopList::ShopList()
{
}

THUMB status::ShopList::~ShopList()
{
}

THUMB void status::ShopList::initialize()
{
    setSection(SECTION_FIRST);
}

THUMB int status::ShopList::getAreaOffset(int area)
{
    return area * SHOP_DATA_OFFSET;
}

THUMB int status::ShopList::getDataIndex(int shop) const
{
    int index = getAreaOffset(g_StageAttribute.getShopDataIndex());
    switch (shop) {
    case SHOP_HOTEL:
        index += HOTEL_OFFSET;
        break;
    case SHOP_CHURCH:
        index += CHURCH_OFFSET;
        break;
    case SHOP_WEAPON:
        index += WEAPON_SHOP_OFFSET;
        break;
    case SHOP_PROTECTOR:
        index += PROTECTOR_SHOP_OFFSET;
        break;
    case SHOP_ITEM:
        index += ITEM_SHOP_OFFSET;
        break;
    case SHOP_YOROZU:
        index += YOROZU_SHOP_OFFSET;
        break;
    case SHOP_CASINO:
        index += CASINO_SHOP_OFFSET;
        break;
    case SHOP_HOTEL_SECOND:
        index += SECOND_SHOP_OFFSET + HOTEL_OFFSET;
        break;
    case SHOP_CHURCH_SECOND:
        index += SECOND_SHOP_OFFSET + CHURCH_OFFSET;
        break;
    case SHOP_WEAPON_SECOND:
        index += SECOND_SHOP_OFFSET + WEAPON_SHOP_OFFSET;
        break;
    case SHOP_PROTECTOR_SECOND:
        index += SECOND_SHOP_OFFSET + PROTECTOR_SHOP_OFFSET;
        break;
    case SHOP_ITEM_SECOND:
        index += SECOND_SHOP_OFFSET + ITEM_SHOP_OFFSET;
        break;
    case SHOP_YOROZU_SECOND:
        index += SECOND_SHOP_OFFSET + YOROZU_SHOP_OFFSET;
        break;
    case SHOP_CASINO_SECOND:
        index += SECOND_SHOP_OFFSET + CASINO_SHOP_OFFSET;
        break;
    }
    return index;
}

THUMB int status::ShopList::getShopCount(int shop) const
{
    int count = 0;
    int dataIndex = getDataIndex(shop);
    int max;
    switch (shop) {
    case SHOP_WEAPON:
        max = WEAPON_COUNT;
        break;
    case SHOP_WEAPON_SECOND:
        max = WEAPON_COUNT;
        break;
    case SHOP_PROTECTOR:
        max = PROTECTOR_COUNT;
        break;
    case SHOP_PROTECTOR_SECOND:
        max = PROTECTOR_COUNT;
        break;
    case SHOP_ITEM:
        max = ITEM_COUNT;
        break;
    case SHOP_ITEM_SECOND:
        max = ITEM_COUNT;
        break;
    case SHOP_YOROZU:
    case SHOP_CASINO:
    case SHOP_YOROZU_SECOND:
    case SHOP_CASINO_SECOND:
        max = YOROZU_COUNT;
        break;
    }
    switch (section_) {
    case SECTION_FIRST:
        for (int i = 0; i < max; i++) {
            if (dq5::level::ShopData1::getRecord(dataIndex + i)->getItem() != 0) {
                count++;
            }
        }
        break;
    case SECTION_SECOND:
        for (int i = 0; i < max; i++) {
            if (dq5::level::ShopData2::getRecord(dataIndex + i)->getItem() != 0) {
                count++;
            }
        }
        break;
    case SECTION_THIRD:
        for (int i = 0; i < max; i++) {
            if (dq5::level::ShopData3::getRecord(dataIndex + i)->getItem() != 0) {
                count++;
            }
        }
        break;
    default:
        for (int i = 0; i < max; i++) {
            if (dq5::level::ShopDataSugoroku::getRecord(dataIndex + i)->getItem() != 0) {
                count++;
            }
        }
        break;
    }
    return count;
}

THUMB int status::ShopList::getShopItem(int shop, int index) const
{
    int dataIndex = getDataIndex(shop);
    switch (section_) {
    case SECTION_FIRST:
        return dq5::level::ShopData1::getRecord(dataIndex + index)->getItem();
    case SECTION_SECOND:
        return dq5::level::ShopData2::getRecord(dataIndex + index)->getItem();
    case SECTION_THIRD:
        return dq5::level::ShopData3::getRecord(dataIndex + index)->getItem();
    default:
        return dq5::level::ShopDataSugoroku::getRecord(dataIndex + index)->getItem();
    }
}

THUMB int status::ShopList::getHotelPrice(bool second) const
{
    int dataIndex;
    if (second == false) {
        dataIndex = getDataIndex(SHOP_HOTEL);
    }
    else {
        dataIndex = getDataIndex(SHOP_HOTEL_SECOND);
    }
    switch (section_) {
    case SECTION_FIRST:
        return dq5::level::ShopData1::getRecord(dataIndex)->getPrice();
    case SECTION_SECOND:
        return dq5::level::ShopData2::getRecord(dataIndex)->getPrice();
    case SECTION_THIRD:
        return dq5::level::ShopData3::getRecord(dataIndex)->getPrice();
    default:
        return dq5::level::ShopDataSugoroku::getRecord(dataIndex)->getPrice();
    }
}

THUMB status::ShopList::ChurchType status::ShopList::getChurchType(bool second) const
{
    int dataIndex;
    int type;
    if (second == false) {
        dataIndex = getDataIndex(SHOP_CHURCH);
    }
    else {
        dataIndex = getDataIndex(SHOP_CHURCH_SECOND);
    }
    switch (section_) {
    case SECTION_FIRST:
        type = dq5::level::ShopData1::getRecord(dataIndex)->getPrice();
        break;
    case SECTION_SECOND:
        type = dq5::level::ShopData2::getRecord(dataIndex)->getPrice();
        break;
    case SECTION_THIRD:
        type = dq5::level::ShopData3::getRecord(dataIndex)->getPrice();
        break;
    default:
        type = dq5::level::ShopDataSugoroku::getRecord(dataIndex)->getPrice();
        break;
    }
    switch (type) {
    case 0:
        return NoExist;
    case 1:
        return Exist;
    case 2:
        return NoPray;
    default:
        return Exist;
    }
}
