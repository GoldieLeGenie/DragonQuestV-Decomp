#pragma ipa file
#include "main/status/UseItem.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseActionFlag.hpp"
#include "main/status/UseActionParam.hpp"
#include "main/status/CharacterStatus.hpp"
#include "main/status/HaveStatusInfo.hpp"
#include "main/status/HaveItemSack.hpp"
#include "main/status/GameStatus.hpp"
#include "main/leveldata/AppriseItem.hpp"

inline unsigned long dq5::level::ItemData::getCasino()
{
    return casino;
}

inline unsigned long dq5::level::ItemData::getMenuMes()
{
    return menuMes;
}

inline unsigned long dq5::level::ItemData::getMeisanhinMsg()
{
    return MeisanhinMsg;
}

inline unsigned long dq5::level::ItemData::getCommentMsg()
{
    return CommentMsg;
}

inline unsigned short dq5::level::ItemData::getBuyPrice()
{
    return BuyPrice;
}

inline unsigned short dq5::level::ItemData::getSellPrice()
{
    return SellPrice;
}

inline unsigned short dq5::level::ItemData::getEffect()
{
    return effect;
}

inline unsigned short dq5::level::ItemData::getAction()
{
    return action;
}

inline unsigned short dq5::level::ItemData::getBattleAction()
{
    return battleAction;
}

inline unsigned short dq5::level::ItemData::getTypeSort()
{
    return typeSort;
}

inline unsigned char dq5::level::ItemData::getEquipType()
{
    return equipType;
}

inline unsigned char dq5::level::ItemData::getCommentID()
{
    return CommentID;
}

inline unsigned char dq5::level::ItemData::getCommentType()
{
    return CommentType;
}

inline unsigned char dq5::level::ItemData::getType()
{
    return type;
}

inline char dq5::level::ItemData::getProtagonist()
{
    return byte_1 & 0x1;
}

inline char dq5::level::ItemData::getBianca()
{
    return (byte_1 & 0x2) >> 1;
}

inline char dq5::level::ItemData::getHenry()
{
    return (byte_1 & 0x4) >> 2;
}

inline char dq5::level::ItemData::getFlora()
{
    return (byte_1 & 0x8) >> 3;
}

inline char dq5::level::ItemData::getDevora()
{
    return (byte_1 & 0x10) >> 4;
}

inline char dq5::level::ItemData::getSancho()
{
    return (byte_1 & 0x20) >> 5;
}

inline char dq5::level::ItemData::getPipin()
{
    return (byte_1 & 0x40) >> 6;
}

inline char dq5::level::ItemData::getSon()
{
    return (byte_1 & 0x80) >> 7;
}

inline char dq5::level::ItemData::getDaughter()
{
    return byte_2 & 0x1;
}

inline char dq5::level::ItemData::getMonster1()
{
    return (byte_2 & 0x2) >> 1;
}

inline char dq5::level::ItemData::getMonster2()
{
    return (byte_2 & 0x4) >> 2;
}

inline char dq5::level::ItemData::getMonster3()
{
    return (byte_2 & 0x8) >> 3;
}

inline char dq5::level::ItemData::getMonster4()
{
    return (byte_2 & 0x10) >> 4;
}

inline char dq5::level::ItemData::getMonster5()
{
    return (byte_2 & 0x20) >> 5;
}

inline char dq5::level::ItemData::getMonster6()
{
    return (byte_2 & 0x40) >> 6;
}

inline char dq5::level::ItemData::getMonster7()
{
    return (byte_2 & 0x80) >> 7;
}

inline char dq5::level::ItemData::getMonster8()
{
    return byte_3 & 0x1;
}

inline char dq5::level::ItemData::getMonster9()
{
    return (byte_3 & 0x2) >> 1;
}

inline char dq5::level::ItemData::getMonster10()
{
    return (byte_3 & 0x4) >> 2;
}

inline char dq5::level::ItemData::getMonster11()
{
    return (byte_3 & 0x8) >> 3;
}

inline char dq5::level::ItemData::getMonster12()
{
    return (byte_3 & 0x10) >> 4;
}

inline char dq5::level::ItemData::getMonster13()
{
    return (byte_3 & 0x20) >> 5;
}

inline char dq5::level::ItemData::getMonster14()
{
    return (byte_3 & 0x40) >> 6;
}

inline char dq5::level::ItemData::getMonster15()
{
    return (byte_3 & 0x80) >> 7;
}

inline char dq5::level::ItemData::getMonster16()
{
    return byte_4 & 0x1;
}

inline char dq5::level::ItemData::getLost()
{
    return (byte_4 & 0x2) >> 1;
}

inline char dq5::level::ItemData::getCurse()
{
    return (byte_4 & 0x4) >> 2;
}

inline char dq5::level::ItemData::getSell()
{
    return (byte_4 & 0x30) >> 4;
}

inline char dq5::level::ItemData::getThrow()
{
    return (byte_4 & 0xC0) >> 6;
}

inline char dq5::level::ItemData::getOrderby()
{
    return byte_5 & 0x3;
}

inline char dq5::level::ItemData::getChange()
{
    return (byte_5 & 0x1C) >> 2;
}

inline dq5::level::ItemData* dq5::level::ItemData::getRecord(int index)
{
    return (ItemData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned long dq5::level::AppriseItem::getMessage1()
{
    return message1;
}

inline unsigned long dq5::level::AppriseItem::getMessage2()
{
    return message2;
}

inline unsigned long dq5::level::AppriseItem::getMessage3()
{
    return message3;
}

inline unsigned long dq5::level::AppriseItem::getMessage4()
{
    return message4;
}

inline unsigned long dq5::level::AppriseItem::getMessage5()
{
    return message5;
}

inline unsigned long dq5::level::AppriseItem::getMessage6()
{
    return message6;
}

inline unsigned long dq5::level::AppriseItem::getMessage7()
{
    return message7;
}

inline unsigned long dq5::level::AppriseItem::getMessage8()
{
    return message8;
}

inline unsigned long dq5::level::AppriseItem::getMessage9()
{
    return message9;
}

inline dq5::level::AppriseItem* dq5::level::AppriseItem::getRecord(int index)
{
    return (AppriseItem*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline status::BaseItem::BaseItem()
{
    available_ = false;
}

static unsigned short es_tbl[264] = {
    0, 205, 143, 148, 147, 176, 88, 86, 87, 136, 124, 122,
    123, 125, 133, 82, 131, 137, 130, 207, 180, 215, 98, 179,
    127, 129, 134, 126, 128, 132, 44, 41, 37, 39, 38, 35,
    45, 42, 40, 43, 36, 182, 8, 177, 178, 142, 141, 140,
    96, 144, 206, 5, 192, 63, 64, 65, 163, 161, 171, 160,
    162, 172, 157, 159, 158, 46, 29, 10, 258, 212, 74, 257,
    99, 21, 156, 253, 193, 70, 251, 75, 94, 250, 166, 20,
    194, 165, 23, 243, 18, 76, 249, 66, 242, 173, 95, 195,
    24, 201, 33, 254, 93, 244, 19, 256, 245, 30, 67, 26,
    28, 170, 32, 27, 252, 22, 25, 174, 31, 113, 230, 106,
    108, 105, 109, 118, 107, 114, 119, 117, 112, 110, 111, 115,
    116, 120, 145, 146, 240, 89, 84, 77, 236, 79, 226, 83,
    239, 259, 248, 225, 91, 100, 261, 260, 92, 262, 164, 61,
    60, 85, 12, 11, 14, 203, 202, 2, 6, 150, 211, 62,
    13, 3, 57, 198, 220, 222, 219, 223, 224, 221, 52, 53,
    191, 51, 58, 241, 190, 104, 73, 200, 229, 81, 7, 238,
    218, 135, 16, 149, 233, 153, 97, 139, 34, 186, 187, 189,
    121, 188, 167, 168, 169, 184, 175, 78, 197, 4, 263, 9,
    235, 232, 47, 154, 155, 90, 208, 68, 69, 152, 228, 49,
    151, 234, 54, 55, 56, 216, 214, 183, 181, 50, 185, 217,
    209, 210, 204, 15, 103, 48, 237, 59, 71, 72, 80, 138,
    1, 231, 102, 213, 101, 17, 247, 246, 255, 227, 199, 196,
};
static unsigned short fr_tbl[264] = {
    0, 31, 197, 167, 166, 133, 103, 102, 104, 219, 118, 121,
    126, 120, 129, 117, 125, 179, 122, 109, 141, 177, 140, 124,
    123, 127, 178, 130, 119, 128, 39, 30, 32, 33, 37, 29,
    40, 36, 34, 35, 38, 187, 196, 193, 194, 162, 163, 161,
    100, 224, 225, 3, 110, 46, 47, 48, 146, 144, 139, 143,
    145, 142, 181, 183, 182, 159, 19, 164, 262, 165, 76, 254,
    247, 13, 175, 234, 18, 74, 232, 75, 97, 96, 151, 12,
    221, 185, 14, 191, 17, 78, 190, 72, 1, 230, 106, 220,
    105, 229, 108, 231, 107, 189, 11, 235, 192, 20, 73, 21,
    15, 43, 24, 22, 233, 16, 25, 188, 23, 59, 101, 52,
    57, 51, 53, 63, 60, 61, 55, 54, 56, 58, 50, 65,
    62, 64, 82, 86, 81, 41, 112, 77, 256, 169, 168, 195,
    88, 170, 263, 87, 94, 257, 158, 83, 99, 171, 239, 69,
    70, 5, 9, 8, 7, 173, 172, 137, 4, 134, 238, 49,
    27, 136, 241, 218, 153, 157, 152, 155, 156, 154, 258, 259,
    180, 203, 114, 135, 215, 138, 93, 42, 248, 85, 249, 260,
    89, 202, 261, 200, 251, 115, 95, 160, 26, 204, 205, 208,
    66, 209, 90, 91, 92, 201, 80, 184, 216, 150, 243, 210,
    255, 250, 222, 244, 245, 98, 68, 44, 45, 246, 71, 28,
    131, 252, 147, 148, 149, 242, 237, 199, 198, 67, 174, 228,
    226, 227, 223, 6, 207, 132, 116, 10, 212, 213, 84, 211,
    176, 79, 186, 253, 113, 240, 2, 111, 236, 206, 217, 214,
};
static unsigned short jp_tbl[264] = {
    0, 187, 76, 4, 175, 61, 5, 169, 32, 150, 149, 165,
    170, 176, 96, 174, 216, 179, 250, 72, 113, 251, 156, 230,
    240, 43, 198, 142, 84, 235, 86, 35, 135, 3, 148, 217,
    259, 95, 211, 196, 158, 25, 24, 12, 213, 136, 207, 1,
    62, 202, 152, 154, 51, 190, 243, 208, 10, 125, 239, 171,
    63, 168, 120, 255, 130, 185, 81, 122, 163, 160, 131, 123,
    44, 42, 38, 45, 14, 94, 40, 66, 60, 27, 98, 101,
    137, 16, 138, 227, 172, 37, 246, 262, 194, 215, 114, 59,
    91, 110, 199, 183, 159, 68, 244, 228, 116, 221, 88, 139,
    209, 146, 92, 232, 201, 214, 144, 22, 238, 178, 28, 39,
    13, 100, 134, 212, 157, 189, 115, 206, 126, 23, 225, 141,
    182, 236, 41, 161, 48, 33, 203, 65, 53, 132, 89, 133,
    36, 79, 87, 83, 129, 20, 64, 140, 119, 237, 181, 204,
    233, 17, 210, 229, 8, 245, 153, 99, 50, 108, 105, 224,
    9, 220, 162, 67, 127, 223, 97, 34, 7, 192, 93, 191,
    249, 222, 173, 188, 195, 18, 145, 6, 121, 11, 219, 143,
    112, 254, 117, 180, 261, 19, 253, 197, 104, 258, 257, 73,
    184, 155, 256, 218, 77, 124, 193, 177, 82, 102, 103, 2,
    58, 54, 57, 55, 56, 263, 78, 46, 47, 49, 31, 205,
    75, 260, 70, 71, 69, 186, 80, 234, 26, 128, 242, 147,
    106, 107, 252, 52, 15, 164, 167, 166, 29, 30, 248, 226,
    109, 74, 241, 21, 247, 151, 85, 118, 90, 200, 231, 111,
};
static unsigned short it_tbl[264] = {
    0, 47, 80, 40, 39, 113, 263, 262, 261, 182, 229, 134,
    223, 230, 133, 232, 225, 114, 227, 238, 15, 12, 14, 231,
    222, 224, 228, 233, 195, 226, 51, 49, 41, 45, 103, 44,
    50, 42, 48, 46, 153, 143, 148, 149, 150, 37, 38, 36,
    173, 81, 115, 183, 166, 55, 56, 57, 123, 122, 154, 121,
    124, 118, 136, 137, 135, 43, 24, 1, 8, 247, 144, 2,
    129, 30, 132, 256, 22, 58, 4, 145, 93, 91, 219, 27,
    86, 140, 28, 253, 21, 131, 255, 90, 126, 146, 94, 84,
    92, 180, 85, 7, 25, 254, 23, 252, 3, 32, 64, 181,
    31, 54, 34, 33, 257, 29, 35, 167, 26, 201, 82, 207,
    196, 205, 206, 209, 198, 202, 203, 208, 199, 204, 197, 211,
    210, 200, 71, 68, 108, 130, 116, 72, 100, 105, 67, 151,
    70, 106, 251, 69, 99, 101, 128, 109, 88, 107, 117, 59,
    60, 79, 19, 16, 18, 110, 111, 10, 13, 119, 189, 62,
    17, 9, 161, 176, 213, 214, 217, 215, 216, 212, 52, 53,
    141, 159, 120, 160, 177, 104, 65, 102, 240, 61, 241, 66,
    239, 235, 245, 186, 112, 237, 87, 185, 11, 163, 164, 127,
    218, 96, 76, 77, 75, 158, 147, 138, 193, 179, 260, 97,
    243, 242, 250, 220, 221, 89, 184, 73, 74, 236, 78, 162,
    234, 98, 168, 169, 170, 191, 188, 155, 152, 63, 194, 192,
    258, 259, 174, 20, 95, 125, 142, 187, 156, 157, 246, 171,
    172, 244, 139, 6, 83, 190, 248, 249, 5, 165, 178, 175,
};
static unsigned short en_tbl[264] = {
    0, 39, 152, 226, 9, 25, 227, 224, 155, 16, 36, 184,
    223, 158, 196, 23, 56, 64, 212, 102, 262, 61, 55, 134,
    48, 144, 13, 258, 95, 140, 222, 153, 110, 121, 220, 219,
    216, 225, 131, 221, 52, 79, 213, 246, 93, 105, 66, 35,
    159, 20, 163, 164, 65, 17, 58, 70, 236, 26, 149, 218,
    87, 67, 7, 103, 43, 85, 174, 171, 161, 195, 90, 247,
    201, 115, 118, 204, 185, 18, 116, 76, 24, 40, 215, 19,
    106, 176, 104, 34, 75, 242, 175, 114, 80, 120, 261, 205,
    206, 167, 14, 198, 49, 181, 217, 72, 41, 127, 202, 45,
    68, 3, 180, 145, 170, 94, 255, 156, 137, 179, 165, 119,
    186, 21, 109, 129, 51, 233, 42, 69, 166, 154, 207, 257,
    199, 139, 117, 162, 92, 197, 89, 77, 211, 107, 240, 108,
    97, 88, 248, 91, 235, 83, 86, 256, 229, 138, 10, 141,
    111, 59, 31, 33, 32, 136, 5, 98, 29, 252, 251, 148,
    168, 130, 150, 182, 193, 192, 189, 194, 190, 191, 231, 239,
    151, 147, 177, 160, 173, 60, 28, 47, 245, 113, 73, 259,
    232, 172, 241, 96, 124, 178, 62, 84, 6, 54, 53, 82,
    81, 50, 112, 128, 244, 143, 1, 157, 228, 249, 250, 260,
    210, 209, 208, 237, 238, 37, 15, 132, 133, 38, 214, 200,
    234, 263, 99, 100, 101, 187, 44, 30, 135, 8, 146, 122,
    253, 254, 63, 4, 188, 74, 243, 78, 125, 126, 22, 27,
    230, 123, 11, 169, 57, 183, 2, 46, 203, 71, 142, 12,
};
static unsigned short de_tbl[264] = {
    0, 263, 35, 224, 100, 104, 225, 215, 149, 107, 117, 168,
    214, 186, 176, 13, 235, 55, 198, 46, 260, 60, 31, 131,
    261, 244, 71, 255, 93, 138, 212, 36, 45, 9, 79, 210,
    200, 226, 129, 211, 32, 158, 38, 114, 85, 40, 63, 108,
    171, 17, 75, 76, 56, 21, 106, 64, 27, 103, 144, 216,
    81, 240, 4, 8, 24, 119, 166, 127, 37, 199, 86, 157,
    190, 121, 124, 189, 184, 118, 123, 150, 102, 230, 177, 16,
    41, 165, 43, 130, 162, 173, 163, 206, 105, 237, 259, 191,
    195, 155, 12, 175, 29, 164, 213, 68, 33, 251, 187, 170,
    65, 51, 88, 203, 154, 167, 254, 111, 136, 172, 234, 125,
    185, 18, 44, 252, 30, 227, 34, 66, 113, 148, 196, 258,
    174, 137, 122, 207, 94, 146, 83, 61, 197, 39, 262, 42,
    90, 84, 14, 58, 25, 78, 82, 257, 201, 135, 5, 139,
    99, 47, 159, 161, 160, 89, 74, 241, 23, 246, 249, 141,
    73, 253, 145, 221, 217, 3, 69, 242, 120, 128, 229, 233,
    147, 143, 62, 50, 219, 48, 91, 220, 115, 109, 67, 256,
    70, 202, 54, 72, 208, 110, 49, 80, 2, 156, 126, 77,
    239, 28, 231, 250, 238, 140, 1, 15, 218, 222, 223, 180,
    192, 193, 194, 52, 53, 116, 11, 204, 205, 179, 178, 20,
    182, 209, 95, 96, 97, 7, 245, 181, 132, 22, 142, 92,
    247, 248, 59, 152, 57, 243, 232, 183, 133, 134, 101, 151,
    228, 236, 19, 153, 112, 169, 87, 26, 188, 10, 98, 6,
};

THUMB void status::UseItem::setItemRecord(int index)
{
    itemData2_ = dq5::level::ItemData::getRecord(index);
}

THUMB void status::UseItem::initialize()
{
}

THUMB ItemType status::UseItem::getItemType(int itemIndex)
{
    setItemRecord(itemIndex);
    switch (itemData2_->getType()) {
        case 1:
            return ITEM_WEAPON;
        case 2:
            return ITEM_ARMOR;
        case 4:
            return ITEM_SHIELD;
        case 3:
            return ITEM_HELMET;
        case 5:
            return ITEM_ACCESSORY;
        case 6:
            return ITEM_ITEM;
        case 7:
            return ITEM_KEY;
        case 8:
            return ITEM_SPECIALTY;
        case 10:
            return ITEM_OTHER;
        case 9:
            return ITEM_IMPORTANT;
        case 11:
            return ITEM_DEBUG;
    }
    return ITEM_OTHER;
}

THUMB ItemType status::UseItem::getEquipItemType(int itemIndex)
{
    setItemRecord(itemIndex);
    switch (itemData2_->getEquipType()) {
        case 1:
            return ITEM_WEAPON;
        case 2:
            return ITEM_ARMOR;
        case 4:
            return ITEM_SHIELD;
        case 3:
            return ITEM_HELMET;
        case 5:
            return ITEM_ACCESSORY;
        case 6:
            return ITEM_ITEM;
        case 7:
            return ITEM_KEY;
        case 8:
            return ITEM_SPECIALTY;
        case 10:
            return ITEM_OTHER;
        case 9:
            return ITEM_IMPORTANT;
        case 11:
            return ITEM_DEBUG;
    }
    return ITEM_OTHER;
}

THUMB status::UseItem::ThrowType status::UseItem::getThrowType(int itemIndex)
{
    setItemRecord(itemIndex);
    switch (itemData2_->getThrow()) {
        case 0:
            return THROW_NG;
        case 1:
            return THROW_OK;
        case 2:
            return THROW_DIFFICULT;
    }
    return THROW_NG;
}

THUMB status::UseItem::SellType status::UseItem::getSellType(int itemIndex)
{
    setItemRecord(itemIndex);
    switch (itemData2_->getSell()) {
        case 0:
            return SELL_NG;
        case 1:
            return SELL_OK;
        case 2:
            return SELL_DIFFICULT;
    }
    return SELL_NG;
}

THUMB bool status::UseItem::isCurse(int itemIndex)
{
    setItemRecord(itemIndex);
    if (itemData2_->getCurse()) {
        return true;
    }
    return false;
}

THUMB bool status::UseItem::isLost(int itemIndex)
{
    setItemRecord(itemIndex);
    switch (itemData2_->getLost()) {
        case 0:
            return false;
        case 1:
            return true;
    }
    return true;
}

THUMB bool status::UseItem::isOrder(int itemIndex)
{
    setItemRecord(itemIndex);
    if (itemData2_->getOrderby()) {
        return true;
    }
    return false;
}

THUMB int status::UseItem::getEffect(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getEffect();
}

THUMB int status::UseItem::getSellPrice(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getSellPrice();
}

THUMB int status::UseItem::getBuyPrice(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getBuyPrice();
}

THUMB int status::UseItem::isEquipEnable(int equipAttrIndex, int itemIndex, int sex)
{
    if (allEquipment_) {
        return true;
    }
    setItemRecord(itemIndex);
    switch (equipAttrIndex) {
        case 1:
            if (itemData2_->getProtagonist()) {
                return true;
            }
            break;
        case 2:
            if (itemData2_->getBianca()) {
                return true;
            }
            break;
        case 3:
            if (itemData2_->getHenry()) {
                return true;
            }
            break;
        case 4:
            if (itemData2_->getFlora()) {
                return true;
            }
            break;
        case 5:
            if (itemData2_->getDevora()) {
                return true;
            }
            break;
        case 6:
            if (itemData2_->getSancho()) {
                return true;
            }
            break;
        case 7:
            if (itemData2_->getPipin()) {
                return true;
            }
            break;
        case 8:
            if (itemData2_->getSon()) {
                return true;
            }
            break;
        case 9:
            if (itemData2_->getDaughter()) {
                return true;
            }
            break;
        case 10:
            if (itemData2_->getMonster1()) {
                return true;
            }
            break;
        case 11:
            if (itemData2_->getMonster2()) {
                return true;
            }
            break;
        case 12:
            if (itemData2_->getMonster3()) {
                return true;
            }
            break;
        case 13:
            if (itemData2_->getMonster4()) {
                return true;
            }
            break;
        case 14:
            if (itemData2_->getMonster5()) {
                return true;
            }
            break;
        case 15:
            if (itemData2_->getMonster6()) {
                return true;
            }
            break;
        case 16:
            if (itemData2_->getMonster7()) {
                return true;
            }
            break;
        case 17:
            if (itemData2_->getMonster8()) {
                return true;
            }
            break;
        case 18:
            if (itemData2_->getMonster9()) {
                return true;
            }
            break;
        case 19:
            if (itemData2_->getMonster10()) {
                return true;
            }
            break;
        case 20:
            if (itemData2_->getMonster11()) {
                return true;
            }
            break;
        case 21:
            if (itemData2_->getMonster12()) {
                return true;
            }
            break;
        case 22:
            if (itemData2_->getMonster13()) {
                return true;
            }
            break;
        case 23:
            if (itemData2_->getMonster14()) {
                return true;
            }
            break;
        case 24:
            if (itemData2_->getMonster15()) {
                return true;
            }
            break;
        case 25:
            if (itemData2_->getMonster16()) {
                return true;
            }
            break;
    }
    return false;
}

THUMB EquipType status::UseItem::getEquipType(int itemIndex)
{
    setItemRecord(itemIndex);
    switch (itemData2_->getChange()) {
        case 3:
            return Strength;
        case 4:
            return Agility;
        case 5:
            return Wisdom;
        case 6:
            return Luck;
        case 1:
            return Attack;
        case 2:
            return Defence;
    }
    return Attack;
}

THUMB int status::UseItem::getEquipValue(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getEffect();
}

THUMB status::BaseItem& status::UseItem::getItem(int itemIndex)
{
    if (itemIndex == 0x6f) {
        static ExtraItemYakusou yakusou;
        return yakusou;
    }
    if (itemIndex == 0x70) {
        static ExtraItemDokukesisou dokukesisou;
        return dokukesisou;
    }
    static BaseItem item;
    return item;
}

THUMB status::UseItem::UseType status::UseItem::getUseType(int itemIndex)
{
    switch (UseAction::getUseType(getUseAction(itemIndex))) {
        case UseAction::Myself:
            return Myself;
        case UseAction::Friend:
            return Friend;
        case UseAction::Enemy:
            return Enemy;
        case UseAction::Both:
            return Both;
        case UseAction::None:
            return None;
    }
    return None;
}

THUMB status::UseItem::UseArea status::UseItem::getUseArea(int itemIndex)
{
    switch (UseAction::getUseArea(getUseAction(itemIndex))) {
        case UseAction::Zero:
            return Zero;
        case UseAction::One:
            return One;
        case UseAction::Group:
            return Group;
        case UseAction::All:
            return All;
        case UseAction::Horse:
            return Horse;
        case UseAction::UsuallyHorse:
            return UsuallyHorse;
        case UseAction::BattleHorse:
            return BattleHorse;
    }
    return Zero;
}

THUMB int status::UseItem::getUseAction(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getAction();
}

THUMB int status::UseItem::getBattleUseAction(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getBattleAction();
}

THUMB int status::UseItem::getMenuMessage(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getMenuMes();
}

THUMB bool status::UseItem::isBattleUse(int itemIndex)
{
    if (getBattleUseAction(itemIndex) == 0xdb) {
        return false;
    }
    if (getBattleUseAction(itemIndex) == 0xdc) {
        return false;
    }
    return true;
}

THUMB int status::UseItem::getTypeSortIndex(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getTypeSort();
}

THUMB int status::UseItem::getNameSortIndex(int itemIndex)
{
    setItemRecord(itemIndex);
    unsigned short* table = jp_tbl;
    Language language = g_Game.language_;
    if (language == Japanese) {
        table = jp_tbl;
    }
    if (language == English) {
        table = en_tbl;
    }
    if (language == French) {
        table = fr_tbl;
    }
    if (language == German) {
        table = de_tbl;
    }
    if (language == Italian) {
        table = it_tbl;
    }
    if (language == Spanish) {
        table = es_tbl;
    }
    return table[itemIndex];
}

THUMB int status::UseItem::getCommentType(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getCommentType();
}

THUMB int status::UseItem::getCommentKindIndex(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getCommentID();
}

THUMB int status::UseItem::getCommentMessage(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getCommentMsg();
}

THUMB int status::UseItem::getCasino(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getCasino();
}

THUMB int status::UseItem::getStopMessage(int itemIndex)
{
    setItemRecord(itemIndex);
    return itemData2_->getMeisanhinMsg();
}

THUMB void status::UseItem::execUse(UseActionParam& useActionParam)
{
    int sortIndex = useActionParam.itemSortIndex_;
    if (useActionParam.actorHaveItemSack_) {
        itemIndex_ = useActionParam.actorHaveItemSack_->getItem(sortIndex);
    } else if (useActionParam.actorCharacterStatus_) {
        itemIndex_ = useActionParam.actorCharacterStatus_->haveStatusInfo_.haveItem_.getItem(sortIndex);
        useActionParam.itemIndex_ = itemIndex_;
    }
    actionIndex_ = getUseAction(itemIndex_);
    useActionParam.setActionIndex(actionIndex_);
    UseAction::execUse(useActionParam);
    if (useActionParam.result_) {
        if (isLost(itemIndex_)) {
            if (useActionParam.actorHaveItemSack_) {
                itemIndex_ = useActionParam.actorHaveItemSack_->del(sortIndex);
            } else if (useActionParam.actorCharacterStatus_) {
                useActionParam.actorCharacterStatus_->haveStatusInfo_.haveItem_.del(sortIndex);
            }
        }
        if (UseActionFlag::isBreakPrayRing()) {
            UseActionFlag::setBreakPrayRing(false);
            if (useActionParam.actorHaveItemSack_) {
                itemIndex_ = useActionParam.actorHaveItemSack_->del(sortIndex);
            } else if (useActionParam.actorCharacterStatus_) {
                useActionParam.actorCharacterStatus_->haveStatusInfo_.haveItem_.del(sortIndex);
            }
        }
    }
}

THUMB void status::UseItem::give(BaseHaveItem& srcHaveItem, int index, BaseHaveItem& desHaveItem)
{
    if (desHaveItem.getCount() == desHaveItem.getItemMax()) {
        if (desHaveItem.getItemMax() != 99) {
            int itemIndex = desHaveItem.getItem(desHaveItem.getCount() - 1);
            desHaveItem.del(desHaveItem.getCount() - 1);
            desHaveItem.add(srcHaveItem.getItem(index));
            srcHaveItem.del(index);
            srcHaveItem.add(itemIndex);
        }
    } else {
        desHaveItem.add(srcHaveItem.getItem(index));
        srcHaveItem.del(index);
    }
}

THUMB void status::UseItem::give2(HaveStatusInfo& srcHaveStatusInfo, int srcIndex, HaveItemSack& desHaveItemSack, int desIndex)
{
    int itemIndex = 0;
    if (desIndex == -1) {
        if (srcHaveStatusInfo.haveItem_.isEquipment(srcIndex)) {
            itemIndex = srcHaveStatusInfo.haveItem_.getItem(srcIndex);
        }
        give(srcHaveStatusInfo.haveItem_, srcIndex, desHaveItemSack);
        srcHaveStatusInfo.haveEquipment_.resetEquipment(itemIndex);
    } else {
        if (srcHaveStatusInfo.haveItem_.isEquipment(srcIndex)) {
            srcHaveStatusInfo.resetEquipment(srcIndex);
        }
        ItemData& srcItemData = srcHaveStatusInfo.haveItem_.itemArray_[srcIndex];
        int itemIndex = desHaveItemSack.getItem(desIndex);
        desHaveItemSack.add(srcItemData.index_);
        desHaveItemSack.del(desIndex);
        srcItemData.index_ = (unsigned char)itemIndex;
    }
}

THUMB void status::UseItem::give2(HaveItemSack& srcHaveItemSack, int srcIndex, HaveStatusInfo& desHaveStatusInfo, int desIndex)
{
    if (desIndex == -1) {
        give(srcHaveItemSack, srcIndex, desHaveStatusInfo.haveItem_);
    } else {
        int desItemIndex = 0;
        if (desHaveStatusInfo.haveItem_.isEquipment(desIndex)) {
            desItemIndex = desHaveStatusInfo.haveItem_.getItem(desIndex);
        }
        desHaveStatusInfo.haveEquipment_.resetEquipment(desItemIndex);
        ItemData& srcItemData = srcHaveItemSack.getItemData(srcIndex);
        ItemData& desItemData = desHaveStatusInfo.haveItem_.itemArray_[desIndex];
        unsigned short index = desItemData.index_;
        desItemData.index_ = srcItemData.index_;
        desItemData.setEquipment(false);
        srcHaveItemSack.del(srcIndex);
        srcHaveItemSack.add(index);
    }
}

THUMB void status::UseItem::give2(HaveStatusInfo& srcHaveStatusInfo, int srcIndex, HaveStatusInfo& desHaveStatusInfo, int desIndex)
{
    int srcItemIndex = 0;
    if (desIndex == -1) {
        if (srcHaveStatusInfo.haveItem_.isEquipment(srcIndex)) {
            srcItemIndex = srcHaveStatusInfo.haveItem_.getItem(srcIndex);
        }
        give(srcHaveStatusInfo.haveItem_, srcIndex, desHaveStatusInfo.haveItem_);
        srcHaveStatusInfo.haveEquipment_.resetEquipment(srcItemIndex);
    } else {
        if (srcHaveStatusInfo.haveItem_.isEquipment(srcIndex)) {
            srcHaveStatusInfo.haveEquipment_.resetEquipment(srcHaveStatusInfo.haveItem_.getItem(srcIndex));
        }
        if (desHaveStatusInfo.haveItem_.isEquipment(desIndex)) {
            desHaveStatusInfo.haveEquipment_.resetEquipment(desHaveStatusInfo.haveItem_.getItem(desIndex));
        }
        ItemData& srcItemData = srcHaveStatusInfo.haveItem_.itemArray_[srcIndex];
        ItemData& desItemData = desHaveStatusInfo.haveItem_.itemArray_[desIndex];
        srcItemData.setEquipment(false);
        desItemData.setEquipment(false);
        unsigned short index = srcItemData.index_;
        srcItemData.index_ = desItemData.index_;
        desItemData.index_ = index;
        srcHaveStatusInfo.haveItem_.sortEquipment();
        desHaveStatusInfo.haveItem_.sortEquipment();
    }
}

THUMB int status::UseItem::getJudgeMessage(int itemIndex, int index)
{
    dq5::level::AppriseItem* appriseItem = dq5::level::AppriseItem::getRecord(itemIndex);
    switch (index) {
        case 0:
            return appriseItem->getMessage1();
        case 1:
            return appriseItem->getMessage2();
        case 2:
            return appriseItem->getMessage3();
        case 3:
            return appriseItem->getMessage4();
        case 4:
            return appriseItem->getMessage5();
        case 5:
            return appriseItem->getMessage6();
        case 6:
            return appriseItem->getMessage7();
        case 7:
            return appriseItem->getMessage8();
        case 8:
            return appriseItem->getMessage9();
    }
    return 0;
}

int status::UseItem::itemIndex_;
int status::UseItem::actionIndex_;
dq5::level::ItemData* status::UseItem::itemData2_;
int status::UseItem::allEquipment_;
