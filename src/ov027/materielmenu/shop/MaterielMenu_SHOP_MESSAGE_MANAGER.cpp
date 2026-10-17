#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "ov027/leveldata/ShopMessage.hpp"

inline dq5::level::ShopMessage* dq5::level::ShopMessage::getRecord(int index)
{
    return (ShopMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::ShopMessage::getMessage1()
{
    return message1;
}

inline unsigned long dq5::level::ShopMessage::getMessage2()
{
    return message2;
}

inline unsigned long dq5::level::ShopMessage::getMessage3()
{
    return message3;
}

inline unsigned long dq5::level::ShopMessage::getMessage4()
{
    return message4;
}

THUMB MaterielMenu_SHOP_MESSAGE_MANAGER* MaterielMenu_SHOP_MESSAGE_MANAGER::getSingleton()
{
    static MaterielMenu_SHOP_MESSAGE_MANAGER messageManager;
    return &messageManager;
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::idle()
{
    switch (MaterielMenu_SHOP_MANAGER::getSingleton()->getShopType()) {
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_WEAPON:
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_PROTECTOR:
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_ITEM:
            shopType_ = MaterielMenu_SHOP_MANAGER::getSingleton()->getShopType();
            break;
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_WEAPON_SECOND:
            shopType_ = MaterielMenu_SHOP_MANAGER::SHOP_TYPE_WEAPON;
            break;
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_PROTECTOR_SECOND:
            shopType_ = MaterielMenu_SHOP_MANAGER::SHOP_TYPE_PROTECTOR;
            break;
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_ITEM_SECOND:
            shopType_ = MaterielMenu_SHOP_MANAGER::SHOP_TYPE_ITEM;
            break;
        default:
            shopType_ = MaterielMenu_SHOP_MANAGER::SHOP_TYPE_SUGOROKU;
            break;
    }
    return getMessageNo(1);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::buy()
{
    return getMessageNo(2);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::sell()
{
    return getMessageNo(0x16);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::yameru()
{
    return getMessageNo(0x25);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::cancel()
{
    return getMessageNo(0x24);
}

THUMB void MaterielMenu_SHOP_MESSAGE_MANAGER::noMoney(int* mes)
{
    mes[0] = getMessageNo(3);
    mes[1] = getMessageNo(0x24);
}

THUMB void MaterielMenu_SHOP_MESSAGE_MANAGER::buyItem(int plural, bool battleUse, int* mes)
{
    int buy = getMessageNo(4);
    int buyPlural = getMessageNo(5);
    int use = getMessageNo(6);
    int ask = getMessageNo(7);
    if (plural && battleUse) {
        mes[0] = buyPlural;
        mes[1] = use;
        mes[2] = ask;
        return;
    }
    if (battleUse) {
        mes[0] = buy;
        mes[1] = use;
        mes[2] = ask;
        return;
    }
    if (plural) {
        mes[0] = buyPlural;
        mes[1] = ask;
        return;
    }
    mes[0] = buy;
    mes[1] = ask;
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::haveItemMax()
{
    return getMessageNo(9);
}

THUMB void MaterielMenu_SHOP_MESSAGE_MANAGER::buyToSack(bool haveMoney, int* mes)
{
    mes[0] = getMessageNo(8);
    if (haveMoney) {
        mes[1] = getMessageNo(0x15);
        return;
    }
    mes[1] = getMessageNo(0x24);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::getItem(bool isBasha, bool isDeath)
{
    if (isBasha) {
        return getMessageNo(0x13);
    }
    if (isDeath) {
        return getMessageNo(0x12);
    }
    return getMessageNo(0x11);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::checkMoney(int overItem, int haveNoMoney, int* mes)
{
    int count = 1;
    int over = getMessageNo(0x14);
    int other = getMessageNo(0x15);
    int cancel = getMessageNo(0x24);
    if (overItem && haveNoMoney) {
        mes[0] = over;
        mes[1] = cancel;
        count = 2;
    }
    else if (overItem) {
        mes[0] = over;
        mes[1] = other;
        count = 2;
    }
    else if (haveNoMoney) {
        mes[0] = cancel;
    }
    else {
        mes[0] = other;
    }
    return count;
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::haveOther()
{
    return getMessageNo(0xc);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::haveWhose()
{
    return getMessageNo(7);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::haveSomething()
{
    return getMessageNo(0xb);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::sortEnd()
{
    return getMessageNo(0xa);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::checkEquip(bool equip)
{
    if (equip) {
        return getMessageNo(0xd);
    }
    return getMessageNo(0x10);
}

THUMB void MaterielMenu_SHOP_MESSAGE_MANAGER::equipItem(int* mes)
{
    mes[0] = getMessageNo(0xe);
    mes[1] = getMessageNo(0xf);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::portSelmi()
{
    return getMessageNo(0x26);
}

THUMB void MaterielMenu_SHOP_MESSAGE_MANAGER::haveNoItem(bool fukuro, int* mes)
{
    if (fukuro) {
        mes[0] = getMessageNo(0x18);
    }
    else {
        mes[0] = getMessageNo(0x17);
    }
    mes[1] = getMessageNo(0x24);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::sellOK()
{
    return getMessageNo(0x1c);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::sellHowMany()
{
    return getMessageNo(0x1d);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::sellPluralSellOK()
{
    return getMessageNo(0x1e);
}

THUMB void MaterielMenu_SHOP_MESSAGE_MANAGER::sellNG(bool sellYet, int* mes)
{
    mes[0] = getMessageNo(0x19);
    mes[1] = getMessageNo(0x1a);
    if (sellYet) {
        mes[2] = getMessageNo(0x24);
        return;
    }
    mes[2] = getMessageNo(0x23);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::sellDifficult()
{
    return getMessageNo(0x1b);
}

THUMB void MaterielMenu_SHOP_MESSAGE_MANAGER::celectNo(bool sellYet, int* mes)
{
    mes[0] = getMessageNo(0x1f);
    if (sellYet) {
        mes[1] = getMessageNo(0x24);
        return;
    }
    mes[1] = getMessageNo(0x23);
}

THUMB void MaterielMenu_SHOP_MESSAGE_MANAGER::sellEnd(bool sellYet, int* mes)
{
    mes[0] = getMessageNo(0x22);
    if (sellYet) {
        mes[1] = getMessageNo(0x24);
        return;
    }
    mes[1] = getMessageNo(0x23);
}

THUMB void MaterielMenu_SHOP_MESSAGE_MANAGER::overMoney(int* mes)
{
    mes[0] = getMessageNo(0x20);
    mes[1] = getMessageNo(0x21);
    mes[2] = getMessageNo(0x24);
}

THUMB int MaterielMenu_SHOP_MESSAGE_MANAGER::getMessageNo(int index)
{
    int mes = 0;
    dq5::level::ShopMessage* record = dq5::level::ShopMessage::getRecord(index);
    switch (shopType_) {
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_WEAPON:
            mes = record->getMessage2();
            break;
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_PROTECTOR:
            mes = record->getMessage3();
            break;
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_ITEM:
            mes = record->getMessage1();
            break;
        case MaterielMenu_SHOP_MANAGER::SHOP_TYPE_SUGOROKU:
            mes = record->getMessage4();
            break;
    }
    return mes;
}
