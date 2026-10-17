#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_ROOT.hpp"
#include "ov027/leveldata/MedalPrize.hpp"
#include "main/global/Global.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/status/ShopList.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/UseItem.hpp"

using menu::MenuStatusInfo;

inline dq5::level::MedalPrize* dq5::level::MedalPrize::getRecord(int index)
{
    return (MedalPrize*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned short dq5::level::MedalPrize::getItem()
{
    return item;
}

inline unsigned char dq5::level::MedalPrize::getMedal()
{
    return medal;
}

THUMB MaterielMenu_SHOP_MANAGER* MaterielMenu_SHOP_MANAGER::getSingleton()
{
    static MaterielMenu_SHOP_MANAGER shopManager;
    return &shopManager;
}

THUMB void MaterielMenu_SHOP_MANAGER::initialize()
{
    for (int i = 0; i < 6; i++) {
        item_[i] = 0;
        itemPrice_[i] = 0;
        itemQuantity_[i] = 0;
    }
    shopType_ = SHOP_TYPE_NONE;
    shopAction_ = 0;
    sellQuantity_ = 0;
}

THUMB void MaterielMenu_SHOP_MANAGER::openShopMenu(int type)
{
    setShopType(type);
    gMaterielMenu_SHOP_ROOT.open();
}

THUMB void MaterielMenu_SHOP_MANAGER::initializeShopItem()
{
    if (shopType_ == SHOP_TYPE_MEDAL_KING) {
        dq5::level::MedalPrize::setup();
        sellItemCount_ = 6;
        for (int i = 0; i < 6; i++) {
            item_[i] = dq5::level::MedalPrize::getRecord(i + 1)->getItem();
            itemPrice_[i] = dq5::level::MedalPrize::getRecord(i + 1)->getMedal();
            itemQuantity_[i] = 1;
        }
        dq5::level::MedalPrize::cleanup();
        return;
    }
    int goldCard = status::g_Story.isGoldCard();
    sellItemCount_ = status::g_Shop.getShopCount(getShopListType());
    for (int i = 0; i < sellItemCount_; i++) {
        item_[i] = status::g_Shop.getShopItem(getShopListType(), i);
        if (shopType_ == SHOP_TYPE_GIFT || shopType_ == SHOP_TYPE_GIFT_SECOND) {
            itemPrice_[i] = status::UseItem::getCasino(item_[i]);
        }
        else {
            itemPrice_[i] = status::UseItem::getBuyPrice(item_[i]);
            if (goldCard == 1) {
                itemPrice_[i] = itemPrice_[i] * 8 / 10;
            }
        }
        itemQuantity_[i] = 1;
    }
    if (status::g_Story.chapter_ == dq5::CHAPTER_YOUNENKI && g_Global.areaNo_ == 10 && shopType_ == SHOP_TYPE_ITEM) {
        itemPrice_[0] = 6;
        itemPrice_[1] = 8;
    }
}

THUMB void MaterielMenu_SHOP_MANAGER::setShopType(int type)
{
    shopType_ = type;
    initializeShopItem();
}

THUMB int MaterielMenu_SHOP_MANAGER::getShopType()
{
    return shopType_;
}

THUMB void MaterielMenu_SHOP_MANAGER::setShopAction(char action)
{
    shopAction_ = action;
}

THUMB int MaterielMenu_SHOP_MANAGER::getShopAction()
{
    return shopAction_;
}

THUMB int MaterielMenu_SHOP_MANAGER::getItem(int index)
{
    return item_[index];
}

THUMB int MaterielMenu_SHOP_MANAGER::getItemPrice(int index)
{
    return itemPrice_[index];
}

THUMB int MaterielMenu_SHOP_MANAGER::getItemPriceSum(int index)
{
    return itemPrice_[index] * itemQuantity_[index];
}

THUMB int MaterielMenu_SHOP_MANAGER::getItemQuantity(int index)
{
    return itemQuantity_[index];
}

THUMB int MaterielMenu_SHOP_MANAGER::getSellItemCount()
{
    return sellItemCount_;
}

THUMB int MaterielMenu_SHOP_MANAGER::getMinimumPrice()
{
    int price = itemPrice_[0];
    for (int i = 0; i < sellItemCount_; i++) {
        if (price > itemPrice_[i]) {
            price = itemPrice_[i];
        }
    }
    return price;
}

THUMB void MaterielMenu_SHOP_MANAGER::setSellQuantity(int quantity)
{
    sellQuantity_ = quantity;
}

THUMB int MaterielMenu_SHOP_MANAGER::getSellQuantity()
{
    return sellQuantity_;
}

THUMB bool MaterielMenu_SHOP_MANAGER::buyItem(int index, int activeChara)
{
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    payOut(index);
    if (activeChara == partyCount) {
        MenuStatusInfo::addFukuroItem(item_[index], itemQuantity_[index]);
        return true;
    }
    if (activeChara < partyCount) {
        for (int i = 0; i < itemQuantity_[index]; i++) {
            if (MenuStatusInfo::getPlayerItemCount(activeChara) == 12) {
                itemQuantity_[index] -= i;
                MenuStatusInfo::addFukuroItem(item_[index], itemQuantity_[index]);
                itemQuantity_[index] = 1;
                return false;
            }
            MenuStatusInfo::addPlayerItem(activeChara, item_[index]);
        }
        itemQuantity_[index] = 1;
        return true;
    }
    return false;
}

THUMB bool MaterielMenu_SHOP_MANAGER::sellItem(int activeItem, int activeChara, int page)
{
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    int itemID;
    if (activeChara == partyCount) {
        itemID = MenuStatusInfo::getFukuroItemID(activeItem, page);
    }
    else {
        itemID = MenuStatusInfo::getPlayerItemID(activeChara, activeItem + page * 6);
    }
    int price = status::UseItem::getSellPrice(itemID);
    if (activeChara == partyCount) {
        if (sellOut(price)) {
            for (int i = 0; i < sellQuantity_; i++) {
                MenuStatusInfo::throwFukuroItem(activeItem, page);
            }
            return true;
        }
    }
    else if (sellOut(price)) {
        for (int i = 0; i < sellQuantity_; i++) {
            MenuStatusInfo::throwPlayerItem(activeChara, activeItem + page * 6);
        }
        return true;
    }
    return false;
}

THUMB void MaterielMenu_SHOP_MANAGER::resetItemQuantity()
{
    for (int i = 0; i < sellItemCount_; i++) {
        itemQuantity_[i] = 1;
    }
}

THUMB void MaterielMenu_SHOP_MANAGER::addItem(int index)
{
    itemQuantity_[index]++;
    if (itemQuantity_[index] > 9) {
        itemQuantity_[index] = 1;
    }
}

THUMB void MaterielMenu_SHOP_MANAGER::subItem(int index)
{
    itemQuantity_[index]--;
    if (itemQuantity_[index] < 1) {
        itemQuantity_[index] = 9;
    }
}

THUMB void MaterielMenu_SHOP_MANAGER::setItemQuantity(int index, int quantity)
{
    itemQuantity_[index] = quantity;
}

THUMB bool MaterielMenu_SHOP_MANAGER::sellOK()
{
    if (MenuStatusInfo::getGold() == 999999) {
        return false;
    }
    int count = 0;
    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
        int itemCount = MenuStatusInfo::getPlayerItemCount(i);
        if (itemCount != 0) {
            for (int j = 0; j < itemCount; j++) {
                if (status::UseItem::getSellType(MenuStatusInfo::getPlayerItemID(i, j)) == status::UseItem::SELL_NG) {
                    count++;
                }
            }
            if (itemCount != count) {
                return true;
            }
        }
    }
    int itemCount = MenuStatusInfo::getFukuroItemCount();
    if (itemCount != 0) {
        for (int j = 0; j < itemCount; j++) {
            if (status::UseItem::getSellType(MenuStatusInfo::getFukuroItemID(j, 0)) == status::UseItem::SELL_NG) {
                count++;
            }
        }
        if (itemCount != count) {
            return true;
        }
    }
    return false;
}

THUMB int MaterielMenu_SHOP_MANAGER::getShopListType()
{
    int type = 0;
    switch (shopType_) {
        case SHOP_TYPE_WEAPON:
            type = 2;
            break;
        case SHOP_TYPE_PROTECTOR:
            type = 3;
            break;
        case SHOP_TYPE_YOROZU:
            type = 5;
            break;
        case SHOP_TYPE_ITEM:
            type = 4;
            break;
        case SHOP_TYPE_GIFT:
            type = 6;
            break;
        case SHOP_TYPE_WEAPON_SECOND:
            type = 9;
            break;
        case SHOP_TYPE_PROTECTOR_SECOND:
            type = 10;
            break;
        case SHOP_TYPE_YOROZU_SECOND:
            type = 11;
            break;
        case SHOP_TYPE_ITEM_SECOND:
            type = 12;
            break;
        case SHOP_TYPE_GIFT_SECOND:
            type = 13;
            break;
        case SHOP_TYPE_SUGOROKU:
            type = 5;
            break;
    }
    return type;
}

THUMB void MaterielMenu_SHOP_MANAGER::payOut(int index)
{
    int gold = MenuStatusInfo::getGold() - itemPrice_[index] * itemQuantity_[index];
    if (gold < 0) {
        gold = 0;
    }
    MenuStatusInfo::setGold(gold);
}

THUMB bool MaterielMenu_SHOP_MANAGER::sellOut(int price)
{
    unsigned int gold = MenuStatusInfo::getGold();
    gold += price * sellQuantity_;
    if (gold > 999999) {
        return false;
    }
    MenuStatusInfo::setGold(gold);
    return true;
}
