#pragma ipa file
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov019/materielmenu/MaterielMenu_WINDOW_MANAGER.hpp"
#include "ov019/commonmenu/UnkMenuDrawText.hpp"
#include "ov019/materielmenu/meisanhin/MaterielMenuMeisanhinUtil.hpp"
#include "ov012/casino/PokerManager.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "main/menu/MenuDataCommon.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/RaceData.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/leveldata/MeisanhinData.hpp"
#include "main/leveldata/SurechigaiData.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/UseItem.hpp"
#include "main/town/TownSugorokuInfo.hpp"
#include "main/dss/UnkUtf8Iterator.hpp"

using menu::MaterielMenuPlayerControl;
using menu::MenuDataCommon;
using menu::MenuStatusInfo;

#define PARTS_END {0xff, 0x00, 0x0000, 0, 0x00, 0x00, 0x00, 0x00}

extern UnkMenuParts s_parts_0218032c[];
extern UnkMenuParts s_parts_021803f0[];
extern UnkMenuParts s_parts_02180498[];
extern UnkMenuParts s_parts_02180508[];
extern UnkMenuParts s_parts_0218055c[];
extern UnkMenuParts s_parts_02180578[];
extern UnkMenuParts s_parts_021805b0[];
extern UnkMenuParts s_parts_021806c8[];
extern UnkMenuParts s_parts_021806e4[];
extern UnkMenuParts s_parts_02180700[];
extern UnkMenuParts s_parts_02180738[];
extern UnkMenuParts s_parts_02180770[];
extern UnkMenuParts s_parts_021807c4[];
extern UnkMenuParts s_parts_021807fc[];
extern UnkMenuParts s_parts_02180826[];
extern UnkMenuParts s_parts_02180850[];
extern UnkMenuParts s_parts_02180922[];
extern UnkMenuParts s_parts_02180a1e[];
extern UnkMenuParts s_parts_02180a72[];
extern UnkMenuParts s_parts_02180ac6[];
extern UnkMenuParts s_parts_02180af0[];
extern UnkMenuParts s_parts_02180b6e[];
extern UnkMenuParts s_parts_02180bfa[];
extern UnkMenuParts s_parts_02180cda[];
extern UnkMenuParts s_parts_02180d4a[];
extern UnkMenuParts s_parts_02180d82[];
extern UnkMenuParts s_parts_02180dba[];
extern UnkMenuParts s_parts_02180df2[];
extern UnkMenuParts s_parts_02180e62[];
extern UnkMenuParts s_parts_02181030[];
extern UnkMenuParts s_parts_02181076[];
extern UnkMenuParts s_parts_021810bc[];
extern UnkMenuParts s_parts_02181148[];
extern UnkMenuParts s_parts_02181228[];
extern UnkMenuParts s_parts_021813cc[];
extern UnkMenuParts s_parts_0218151c[];
extern UnkMenuParts s_parts_0218157e[];
extern UnkMenuParts s_parts_02181650[];
extern UnkMenuParts s_parts_02181b9e[];

inline dq5::level::SurechigaiData* dq5::level::SurechigaiData::getRecord(int index) { return (SurechigaiData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline dq5::level::MeisanhinData* dq5::level::MeisanhinData::getRecord(int index) { return (MeisanhinData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }
inline char dq5::level::MeisanhinData::getPoint1() { return byte_1 & 1; }
inline char dq5::level::MeisanhinData::getPoint2() { return (byte_1 & 2) >> 1; }
inline status::MuseumItemStatus& status::MuseumStatus::getMuseumItemStatus(int index) { return museumitem_[index]; }
inline dq5::level::MeisanhinData* status::MuseumItemStatus::getMeisanhinData() { return &meisan_; }
inline status::TaishiBase& status::MuseumStatus::getPlayerTaishi() { return playerTaishi_; }
inline status::TaishiBase& status::MuseumStatus::getOthersTaishi(int index) { return othersTaishi_[index]; }
inline char* status::TaishiBase::getTaishiName() { return taishiName_; }
inline char* status::TaishiBase::getTaishiMessage() { return message_; }

static UnkMenuParts s_parts_0218063c[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x98, 0x54, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_021812d0[] = {
    {0x0c, 0xf4, 0x0000, 0, 0x04, 0x00, 0x18, 0x18},
    {0x0c, 0xf4, 0x0000, 1, 0x4c, 0x00, 0x18, 0x18},
    {0x0f, 0x0a, (short)0xf000, 2, 0x20, 0x08, 0x0a, 0x10},
    {0x0d, 0x0a, (short)0xf000, 3, 0x30, 0x08, 0x0a, 0x10},
    {0x0f, 0x0a, (short)0xf000, 4, 0x40, 0x08, 0x0a, 0x10},
    PARTS_END,
};

THUMB int getPokerHandText(int index)
{
    int text = 0;
    switch (index) {
        case 11:
            text = (int)0xe0000361;
            break;
        case 10:
            text = (int)0xe0000362;
            break;
        case 9:
            text = (int)0xe0000363;
            break;
        case 8:
            text = (int)0xe0000364;
            break;
        case 7:
            text = (int)0xe0000365;
            break;
        case 6:
            text = (int)0xe0000366;
            break;
        case 5:
            text = (int)0xe0000367;
            break;
        case 4:
            text = (int)0xe0000368;
            break;
        case 3:
            text = (int)0xe0000369;
            break;
        case 2:
            text = (int)0xe000036a;
            break;
    }
    return text;
}

THUMB void drawShopRootCommands(int type, int flag)
{
    int param = 0;
    int color = 0;
    if (flag == 1) {
        color = 3;
    }
    for (int i = 0; i < 3; i++) {
        param = getMenuCommandText(type, i);
        drawMenuParts(s_parts_02180508, &param, 0xa4, i * 16 + 8 + i * 8, data_02094dd4[color]);
    }
    drawMenuFrame(0x98, 0, 0x68, 0x50, -1);
}

THUMB void drawShopEquipCompare()
{
    setMenuDrawOffset(0, 0);
    int param[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        param[i] = 0;
    }
    UnkMenuParts* parts = 0;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < count; i++) {
        switch (getShopEquipCompare(i, param, -1)) {
            case 0:
                parts = s_parts_02180a1e;
                break;
            case 1:
                parts = s_parts_021810bc;
                break;
            case 2:
                parts = s_parts_02180d82;
                break;
        }
        drawMenuParts(parts, param, (i % 2) << 7, ((i / 2) << 4) + 0x28, data_02094dd4[0]);
    }
    drawShopItemHeader(-1);
    drawMenuFrame(0, 0, 0x100, 0x90, 0x20);
    drawMenuFrame(0, 0x90, 0x100, 0x30, -1);
}

THUMB void drawShopHeldCounts()
{
    setMenuDrawOffset(0, 0);
    int param[3] = {0, 0, 0};
    for (int j = 0; j < 3; j++) {
        param[j] = 0;
    }
    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
        UnkMenuParts* parts;
        if (getShopHeldCount(i, param, -1)) {
            parts = s_parts_02180dba;
        } else {
            parts = s_parts_02180ac6;
        }
        drawMenuParts(parts, param, (i % 2) << 7, ((i / 2) << 4) + 0x28, data_02094dd4[0]);
    }
    drawShopItemHeader(-1);
    drawMenuFrame(0, 0, 0x100, 0x90, 0x20);
    drawMenuFrame(0, 0x90, 0x100, 0x30, -1);
}

THUMB void drawShopSackCount(int itemID)
{
    setMenuDrawOffset(0, 0);
    UnkMenuParts* parts = s_parts_02180df2;
    int have = MenuStatusInfo::isFukuroHaveItem(itemID);
    int param[3] = {0x5000024e, (int)"\xff\xfe\xa9\x24", have};
    if (have == 0) {
        param[1] = (int)0xe00000e4;
        parts = s_parts_02180af0;
    }
    drawMenuPartsColored(parts, param, data_02094dd4[0]);
}

THUMB void drawShopItemKind()
{
    MaterielMenuPlayerControl* control = MaterielMenuPlayerControl::getSingleton();
    int itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(control->activeItem_);
    int param[2] = {0, (int)0xe0000066};
    param[0] = itemID;
    if (status::UseItem::getEquipItemType(itemID) <= ITEM_ACCESSORY) {
        param[1] = MenuDataCommon::getEquipKind(status::UseItem::getEquipItemType(itemID));
    }
    drawMenuPartsColored(s_parts_02180a72, param, data_02094dd4[0]);
    drawMenuFrame(0, 0xa0, 0x88, 0x20, -1);
}

static UnkMenuParts s_parts_02180976[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x10, 0x20, 0x18},
    {0x0c, 0xf1, 0x0000, 0, 0x00, 0x00, 0x20, 0x20},
    PARTS_END,
};

THUMB void drawShopBuyList(int flag)
{
    UnkMenuParts partsA[] = {
        {0x0d, 0x08, (short)0xf000, 0, 0x0a, 0x02, 0x80, 0x0c},
        {0x0d, 0x08, (short)0xf000, 1, 0x9c, 0x02, 0x08, 0x0c},
        {0x0f, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x08, 0x0c},
        {0x0f, 0x0a, (short)0xf000, 3, 0xa8, 0x02, 0x38, 0x0c},
        {0x0d, 0x0b, (short)0xf000, 4, 0x00, 0x00, 0x08, 0x0c},
        PARTS_END,
    };
    UnkMenuParts partsB[] = {
        {0x0d, 0x08, (short)0xf000, 0, 0x0a, 0x02, 0x80, 0x0c},
        {0x0f, 0x0a, (short)0xf000, 1, 0xa8, 0x02, 0x38, 0x0c},
        PARTS_END,
    };
    int param[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        param[i] = 0;
    }
    int count = MaterielMenu_SHOP_MANAGER::getSingleton()->getSellItemCount();
    for (int i = 0; i < count; i++) {
        UnkMenuParts* parts;
        if (flag == 0) {
            param[0] = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(i) + 0x40000000;
            param[1] = (int)"\xff\xfe\xa9\x24";
            param[2] = MaterielMenu_SHOP_MANAGER::getSingleton()->getItemQuantity(i);
            param[3] = MaterielMenu_SHOP_MANAGER::getSingleton()->getItemPriceSum(i);
            param[4] = (int)0xe0000071;
            parts = partsA;
        } else {
            param[0] = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(i) + 0x40000000;
            param[1] = MaterielMenu_SHOP_MANAGER::getSingleton()->getItemPriceSum(i);
            parts = partsB;
        }
        drawMenuParts(parts, param, 0xc, i * 16 + 0xc + i * 8, data_02094dd4[0]);
    }
    drawMenuFrame(0, 0, 0x100, 0xa0, -1);
}

static UnkMenuParts s_parts_02180e9a[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x14, 0x00, 0x60, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0x88, 0x00, 0x30, 0x10},
    {0x0d, 0x0a, (short)0xf000, 2, 0x98, 0x00, 0x30, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_021804d0[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x02, 0x68, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02181378[] = {
    {0x0c, 0xf4, 0x0000, 0, 0xa8, 0x30, 0x18, 0x18},
    {0x0f, 0x0a, (short)0xf000, 1, 0xc8, 0x3a, 0x08, 0x0c},
    {0x0d, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x78, 0x0c},
    {0x0f, 0x0a, (short)0xf000, 3, 0xd8, 0x3a, 0x08, 0x0c},
    {0x0c, 0xf4, 0x0000, 4, 0xe0, 0x30, 0x18, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_021809a0[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x10, 0x20, 0x18},
    {0x0c, 0xf0, 0x0000, 0, 0x00, 0x00, 0x20, 0x20},
    PARTS_END,
};

UnkMenuParts s_parts_02180508[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x02, 0x54, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_021804ec[] = {
    {0x0e, 0x08, (short)0xf000, 0, 0x08, 0x98, 0xf0, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_021809ca[] = {
    {0x14, 0xc2, 0x0000, 0, 0x04, 0x0e, 0x20, 0x18},
    {0x0c, 0xf1, 0x0000, 0, 0x00, 0x00, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_021809f4[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x00, 0x68, 0x68},
    {0x16, 0x00, (short)0xf000, 0, 0x00, 0x18, 0x68, 0x00},
    PARTS_END,
};

static UnkMenuParts s_parts_021806ac[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0xa2, 0x04, 0x58, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0218118e[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0xd0, 0x78, 0x10, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0xe0, 0x78, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0xe8, 0x78, 0x10, 0x0a},
    {0x0c, 0xf4, 0x0000, 3, 0xe0, 0x84, 0x18, 0x18},
    PARTS_END,
};

UnkMenuParts s_parts_02180a1e[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x30, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x50, 0x00, 0x48, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180a48[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x46, 0x0a, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 1, 0x44, 0x0a, 0x18, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180428[] = {
    {0x0d, 0x0a, (short)0xf000, 0, 0x98, 0x98, 0x50, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02181420[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x14, 0x00, 0x60, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0x88, 0x00, 0x30, 0x10},
    {0x0d, 0x0a, (short)0xf000, 2, 0x98, 0x00, 0x30, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0xd8, 0x00, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 4, 0xe0, 0x00, 0x18, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02181ab0[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x08, 0x6a, 0x88, 0x10},
    {0x0d, 0x09, (short)0xf000, 1, 0x08, 0x80, 0x88, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x20, 0x8c, 0x30, 0x10},
    {0x0d, 0x0a, (short)0xf000, 3, 0x50, 0x8c, 0x08, 0x10},
    {0x0d, 0x0b, (short)0xf000, 4, 0x00, 0x00, 0x20, 0x10},
    {0x0d, 0x08, (short)0xf000, 5, 0x20, 0x97, 0x30, 0x10},
    {0x0d, 0x0a, (short)0xf000, 6, 0x50, 0x97, 0x08, 0x10},
    {0x0f, 0x0b, (short)0xf000, 7, 0x00, 0x00, 0x20, 0x10},
    {0x0d, 0x08, (short)0xf000, 8, 0x20, 0xa2, 0x18, 0x10},
    {0x0f, 0x0a, (short)0xf000, 9, 0x38, 0xa2, 0x20, 0x10},
    {0x0d, 0x0b, (short)0xf000, 10, 0x00, 0x00, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 11, 0x58, 0xa2, 0x20, 0x10},
    {0x0d, 0x08, (short)0xf000, 12, 0x20, 0xae, 0x18, 0x10},
    {0x0f, 0x0a, (short)0xf000, 13, 0x38, 0xae, 0x20, 0x10},
    {0x0d, 0x0b, (short)0xf000, 14, 0x00, 0x00, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 15, 0x58, 0xae, 0x20, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_021816ce[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x08, 0x0a, 0x30, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x38, 0x0a, 0x28, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0x0c, 0x24, 0x18, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 3, 0x1c, 0x24, 0x20, 0x0a},
    {0x0d, 0x08, (short)0xf000, 8, 0x3c, 0x24, 0x0a, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 4, 0x3c, 0x24, 0x20, 0x0a},
    {0x0d, 0x08, (short)0xf000, 5, 0x0c, 0x34, 0x18, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 6, 0x1c, 0x34, 0x20, 0x0a},
    {0x0d, 0x08, (short)0xf000, 8, 0x3c, 0x34, 0x0a, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 7, 0x3c, 0x34, 0x20, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180594[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x9c, 0xf0, 0x18},
    PARTS_END,
};

UnkMenuParts s_parts_02180ac6[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x30, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x38, 0x00, 0x48, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02181474[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0xcc, 0x78, 0x10, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0xdc, 0x78, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0xe4, 0x78, 0x10, 0x0a},
    {0x0c, 0xf4, 0x0000, 3, 0xc0, 0x84, 0x18, 0x18},
    {0x0c, 0xf4, 0x0000, 4, 0xe0, 0x84, 0x18, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_021815e0[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x80, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x0c, 0x1a, 0x10, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x18, 0x1a, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x32, 0x80, 0x10},
    {0x0d, 0x0a, (short)0xf000, 4, 0xc8, 0x32, 0x0c, 0x10},
    {0x0f, 0x0a, (short)0xf000, 5, 0xb0, 0x32, 0x44, 0x10},
    {0x0c, 0xf0, 0x0000, 6, 0xd8, 0x04, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_02180f0a[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x08, 0x68, 0x18},
    {0x0e, 0x08, (short)0xf000, 0, 0x04, 0x08, 0x40, 0x18},
    {0x0c, 0xf0, 0x0000, 1, 0x48, 0x00, 0x20, 0x20},
    PARTS_END,
};

THUMB void drawCharaItemNames()
{
    int count;
    int partyCount;
    UnkMenuParts* parts;
    int x;
    setMenuDrawOffset(0, 0);
    UnkMenuParts partsA[] = {
        {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x68, 0x10},
        PARTS_END,
    };
    UnkMenuParts partsB[] = {
        {0x0d, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x08, 0x10},
        {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x00, 0x68, 0x10},
        PARTS_END,
    };
    int param[2] = {0, 0};
    for (int i = 0; i < 2; i++) {
        param[i] = 0;
    }
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (chara == partyCount) {
        count = MenuStatusInfo::getFukuroItemCount();
        if (count > 12) {
            count = 12;
        }
    } else {
        count = MenuStatusInfo::getPlayerItemCount(chara);
    }
    for (int i = 0; i < count; i++) {
        x = (i % 2) * 0x70 + 0xc;
        int y = ((i / 2) << 4) + 0x58;
        if (chara == partyCount) {
            int itemID = MenuStatusInfo::getFukuroItemID(i, 0);
            parts = partsA;
            param[0] = itemID + 0x40000000;
        } else {
            int item = MenuStatusInfo::getPlayerItemID(chara, i);
            if (MenuStatusInfo::isPlayerEquipItemIndex(chara, i) == true) {
                parts = partsB;
                param[0] = (int)0xe000003c;
                param[1] = item + 0x40000000;
            } else {
                parts = partsA;
                param[0] = item + 0x40000000;
            }
        }
        drawMenuParts(parts, param, x, y, data_02094dd4[0]);
    }
    drawMenuFrame(0, 0x50, 0x100, 0x70, -1);
}

static UnkMenuParts s_parts_02180754[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x00, 0x100, 0x50},
    PARTS_END,
};

static UnkMenuParts s_parts_021814c8[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x58, 0xa0, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x70, 0xa0, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0x08, 0x80, 0x1c, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 3, 0x28, 0x80, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 4, 0x30, 0x80, 0x1c, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180b1a[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x0c, 0x20, 0x18},
    {0x0c, 0xf1, 0x0000, 0, 0x00, 0x00, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_021807a8[] = {
    {0x0d, 0x08, (short)0xf100, 0, 0x00, 0x00, 0x50, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180b44[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x14, 0x00, 0x60, 0x10},
    {0x0d, 0x0a, (short)0xf000, 1, 0x80, 0x00, 0x48, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02180f7a[] = {
    {0x0d, 0x08, (short)0xf100, 0, 0x0c, 0x08, 0x38, 0x0a},
    {0x0f, 0x0a, (short)0xf100, 1, 0x08, 0x14, 0x3c, 0x0a},
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x00, 0x50, 0x28},
    PARTS_END,
};

static UnkMenuParts s_parts_02180b98[] = {
    {0x0f, 0x08, (short)0xf000, 1, 0x10, 0x0a, 0x60, 0x10},
    {0x0d, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x60, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02180fb2[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x58, 0xa0, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x70, 0xa0, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0x08, 0x80, 0xa0, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_021818fe[] = {
    {0x0c, 0xf0, 0x0000, 0, 0x58, 0x08, 0x20, 0x20},
    {0x0d, 0x08, (short)0xf000, 1, 0x28, 0x30, 0x30, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x48, 0x30, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x54, 0x30, 0x68, 0x10},
    {0x0d, 0x08, (short)0xf000, 4, 0x28, 0x40, 0x30, 0x10},
    {0x0d, 0x08, (short)0xf000, 5, 0x48, 0x40, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 6, 0x54, 0x40, 0x68, 0x10},
    {0x0d, 0x08, (short)0xf000, 7, 0x28, 0x50, 0x30, 0x10},
    {0x0d, 0x08, (short)0xf000, 8, 0x48, 0x50, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 9, 0x54, 0x50, 0x68, 0x10},
    {0x0d, 0x08, (short)0xf000, 10, 0x28, 0x60, 0x2c, 0x10},
    {0x0d, 0x08, (short)0xf000, 11, 0x48, 0x60, 0x08, 0x10},
    {0x0f, 0x08, (short)0xf000, 12, 0x54, 0x60, 0x40, 0x10},
    {0x0d, 0x0b, (short)0xf000, 13, 0x00, 0x00, 0x08, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02180fea[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x58, 0xa0, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x70, 0xa0, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 2, 0x28, 0x80, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 3, 0x30, 0x80, 0x1c, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180444[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x78, 0x08, 0x10, 0x10},
    PARTS_END,
};

THUMB void drawShopGiveCompare(int itemID)
{
    UnkMenuParts* parts = 0;
    int param[8] = {-1};
    for (int i = 0; i < 8; i++) {
        param[i] = -1;
    }
    int values[5] = {-1};
    for (int i = 0; i < 5; i++) {
        values[i] = -1;
    }
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    int item = MaterielMenuPlayerControl::getSingleton()->activeItem_;
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    if (itemID == 0) {
        itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(item);
    }
    param[0] = itemID + 0x40000000;
    param[1] = (int)"\xff\xfe\xaf\x24";
    if (chara == partyCount) {
        param[2] = 0x5000024e;
    } else {
        param[2] = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
    }
    if (status::UseItem::getEquipItemType(itemID) <= ITEM_ACCESSORY && chara != partyCount) {
        param[3] = MenuDataCommon::getItemTypeMessageNo(itemID);
        switch (getShopEquipCompare(chara, values, -1)) {
            case 0:
                parts = s_parts_021813cc;
                param[3] = values[1];
                param[4] = itemID;
                break;
            case 1:
                parts = s_parts_02181650;
                param[4] = values[1];
                param[5] = values[2];
                param[6] = values[3];
                param[7] = itemID;
                break;
            case 2:
                parts = s_parts_021815e0;
                param[4] = values[1];
                param[5] = values[2];
                param[6] = itemID;
                break;
        }
    } else {
        parts = s_parts_021813cc;
        if (chara == partyCount) {
            if (MenuStatusInfo::isFukuroHaveItem(itemID)) {
                param[3] = (int)0xe00000e3;
            } else {
                param[3] = (int)0xe00000e4;
            }
        } else {
            if (MenuStatusInfo::isPlayerHaveItem(chara, itemID) == true) {
                param[3] = (int)0xe00000e1;
            } else {
                param[3] = (int)0xe00000e2;
            }
        }
        param[4] = itemID;
    }
    drawMenuPartsColored(parts, param, data_02094dd4[0]);
    drawMenuFrame(0, 0, 0x100, 0x48, 0x28);
}

static UnkMenuParts s_parts_021803b8[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x78, 0x38, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02180bc2[] = {
    {0x0f, 0x0a, (short)0xf100, 0, 0x18, 0x00, 0x18, 0x0a},
    {0x0f, 0x0a, (short)0xf100, 1, 0x66, 0x00, 0x18, 0x0a},
    {0x0f, 0x0a, (short)0xf100, 2, 0x98, 0x00, 0x40, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180540[] = {
    {0x0c, 0xf0, 0x0000, 0, 0x00, 0x00, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_02180310[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x14, 0x1a, 0x54, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_021802f4[] = {
    {0x15, 0xb6, 0x0000, 0, 0x80, 0x12, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_parts_02180524[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x02, 0x50, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02180348[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x0c, 0x90, 0x10},
    PARTS_END,
};

THUMB void drawPartyIcons(int y, int flag)
{
    int param = 0;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < count; i++) {
        drawCharaIconWithCondition(i, ((i % 5) << 5) + 0x10 + ((i % 5) << 3), (i / 5) * 0x28 + 0x48 - y);
    }
    if (flag == 1) {
        MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
        int n = 0;
        for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT); i++) {
            int x = ((n % 5) << 5) + 0xc + ((n % 5) << 3);
            if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_PLAYER) == true) {
                param = i + 1;
                drawMenuParts(s_parts_021806c8, &param, x, 0x50 - y, data_02094dd4[getActorConditionColor(i)]);
                n++;
            }
        }
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    } else {
        for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT); i++) {
            int m = i % 5;
            param = i + 1;
            drawMenuParts(s_parts_021806c8, &param, (m << 5) + 0xc + (m << 3), 0x50 - y, data_02094dd4[getActorConditionColor(i)]);
        }
    }
    if (y == 0) {
        drawCharaIconWithCondition(-1, ((count % 5) << 5) + 0x10 + ((count % 5) << 3), (count / 5) * 0x28 + 0x48);
    }
    drawMenuFrame(0, 0x48 - y, 0xe0, 0x58, -1);
}

THUMB void drawSellPriceList()
{
    setMenuDrawOffset(0, 0);
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    int param[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        param[i] = 0;
    }
    if (chara == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        int count = MenuStatusInfo::getFukuroItemCount();
        if (count > 12) {
            count = 12;
        }
        for (int i = 0; i < count; i++) {
            UnkMenuParts* parts;
            if (getSellListRow(param, chara, i) == 0) {
                parts = s_parts_02180b44;
            } else {
                parts = s_parts_02181420;
            }
            drawMenuParts(parts, param, 0, i * 14 + 0xc, data_02094dd4[0]);
        }
    } else {
        int count = MenuStatusInfo::getPlayerItemCount(chara);
        for (int i = 0; i < count; i++) {
            UnkMenuParts* parts;
            if (getSellListRow(param, chara, i) == 0) {
                parts = s_parts_02180b44;
            } else {
                parts = s_parts_02180e9a;
            }
            drawMenuParts(parts, param, 0, i * 14 + 0xc, data_02094dd4[0]);
            if (MenuStatusInfo::isPlayerEquipItemIndex(chara, i) == true) {
                int equip = (int)0xe000003c;
                drawMenuParts(s_parts_02180578, &equip, 0, i * 14 + 0xc, data_02094dd4[0]);
            }
        }
    }
    drawMenuFrame(0, 0, 0x100, 0xc0, -1);
}

THUMB void drawItemPage(int fukuro)
{
    int page = MaterielMenuPlayerControl::getSingleton()->activeItemPage_;
    int param[2] = {0, 0};
    for (int i = 0; i < 2; i++) {
        param[i] = 0;
    }
    int end = (page + 1) * 6;
    if (fukuro == 1) {
        int n = 0;
        int count = MenuStatusInfo::getFukuroItemCount();
        if (end > count) {
            end = count;
        }
        for (int i = page * 6; i < end; i++) {
            int itemID = MenuStatusInfo::getFukuroItemID(i, 0);
            int x = (n % 2) * 0x78 + 0x14;
            int y = (n / 2) << 5;
            param[0] = itemID + 0x40000000;
            param[1] = itemID;
            drawMenuParts(s_parts_02180f0a, param, x, y + 4, data_02094dd4[0]);
            if (MenuStatusInfo::getFukuroItemCount(i) > 1) {
                int quantity = MenuStatusInfo::getFukuroItemCount(i);
                if (quantity > 99) {
                    quantity = 99;
                }
                drawMenuParts(s_parts_02180700, &quantity, x, y + 4, data_02094dd4[0]);
            }
            n++;
        }
    } else {
        int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
        int n = 0;
        int count = MenuStatusInfo::getPlayerItemCount(chara);
        if (end > count) {
            end = count;
        }
        for (int i = page * 6; i < end; i++) {
            int itemID = MenuStatusInfo::getPlayerItemID(chara, i);
            int x = (n % 2) * 0x78 + 0x14;
            int y = (n / 2) << 5;
            param[0] = itemID + 0x40000000;
            param[1] = itemID;
            drawMenuParts(s_parts_02180f0a, param, x, y + 4, data_02094dd4[0]);
            if (MenuStatusInfo::isPlayerEquipItemIndex(chara, i) == true) {
                int equip = (int)0xe000003c;
                drawMenuParts(s_parts_02180738, &equip, x, y + 4, data_02094dd4[0]);
            }
            n++;
        }
    }
    drawMenuFrame(0, 0, 0x100, 0xa0, 0x70);
}

THUMB void drawSellPrice(int fukuro)
{
    int param[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        param[i] = 0;
    }
    UnkMenuParts* parts;
    MaterielMenuPlayerControl* control = MaterielMenuPlayerControl::getSingleton();
    int base;
    int item = control->activeItem_;
    base = control->activeItemPage_ * 6;
    if (fukuro == 1) {
        int itemID = MenuStatusInfo::getFukuroItemID(item + base, 0);
        if (status::UseItem::getSellType(itemID) == 1) {
            param[0] = (int)0xe0000231;
            parts = s_parts_021807c4;
        } else {
            parts = s_parts_02181148;
            param[0] = status::UseItem::getSellPrice(itemID);
            param[1] = (int)0xe0000071;
            param[2] = (int)"\xff\xfe\xa9\x24";
            param[3] = MenuStatusInfo::getFukuroItemCount(item + base);
            if (param[3] > 99) {
                param[3] = 99;
            }
        }
    } else {
        int itemID = MenuStatusInfo::getPlayerItemID(MaterielMenuPlayerControl::getSingleton()->activeChara_, item + base);
        if (status::UseItem::getSellType(itemID) == 1) {
            param[0] = (int)0xe0000231;
            parts = s_parts_021807c4;
        } else {
            parts = s_parts_02180b6e;
            param[0] = status::UseItem::getSellPrice(itemID);
            param[1] = (int)0xe0000071;
        }
    }
    drawMenuPartsColored(parts, param, data_02094dd4[0]);
}

THUMB void drawItemPageNumber(int fukuro)
{
    UnkMenuParts* parts = s_parts_02181474;
    int param[5] = {MaterielMenuPlayerControl::getSingleton()->activeItemPage_ + 1, (int)"\xff\xfe\xa7\x24", (MenuStatusInfo::getFukuroItemCount() - 1) / 6 + 1, 0xc, 0xd};
    if (fukuro == 1) {
        if (MenuStatusInfo::getFukuroItemCount() <= 6) {
            return;
        }
    } else {
        int count = MenuStatusInfo::getPlayerItemCount(MaterielMenuPlayerControl::getSingleton()->activeChara_);
        if (count <= 6) {
            return;
        }
        param[0] = MaterielMenuPlayerControl::getSingleton()->activeItemPage_ + 1;
        param[2] = count / 6 + 1;
        if (count == 12) {
            param[2] = 2;
        }
    }
    drawMenuPartsColored(parts, param, data_02094dd4[0]);
}

static UnkMenuParts s_parts_02180364[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x78, 0x08, 0x28, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02180380[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x88, 0x1a, 0x38, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_021810bc[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x30, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 1, 0x30, 0x00, 0x20, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 2, 0x50, 0x00, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 3, 0x58, 0x00, 0x20, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_021811d4[] = {
    {0x0c, 0xf4, 0x0000, 0, 0x50, 0x98, 0x18, 0x18},
    {0x0f, 0x0a, (short)0xf000, 1, 0x64, 0xa4, 0x10, 0x10},
    {0x0d, 0x0a, (short)0xf000, 2, 0x78, 0xa4, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 3, 0x7e, 0xa4, 0x10, 0x10},
    {0x0c, 0xf4, 0x0000, 4, 0x88, 0x98, 0x18, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_021804b4[] = {
    {0x0d, 0x09, (short)0xf100, 0, 0x29, 0xaa, 0x50, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02180c32[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x0c, 0x68, 0x18},
    {0x0e, 0x08, (short)0xf000, 0, 0x0c, 0x0c, 0x40, 0x18},
    {0x0c, 0xf0, 0x0000, 1, 0x44, 0x00, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_02181102[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x00, 0x00, 0x10, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 2, 0x18, 0x00, 0x10, 0x10},
    {0x0c, 0xf4, 0x0000, 3, 0x10, 0x08, 0x18, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_02180a9c[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x46, 0x0a, 0x10, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 1, 0x44, 0x0a, 0x18, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180674[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x98, 0x98, 0x50, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180c6a[] = {
    {0x0e, 0x08, (short)0xf000, 0, 0x14, 0x06, 0x90, 0x18},
    {0x0e, 0x08, (short)0xf000, 1, 0xb0, 0x06, 0x10, 0x18},
    {0x0e, 0x08, (short)0xf000, 2, 0xc0, 0x06, 0x38, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_02180690[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x10, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180738[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x48, 0x18, 0x0e, 0x0e},
    PARTS_END,
};

static UnkMenuParts s_parts_02180ca2[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x50, 0xa6, 0x30, 0x08},
    {0x07, 0x00, (short)0xf000, 17, 0x50, 0xa0, 0x30, 0x08},
    {0x11, 0x00, 0x0000, 1, 0x48, 0xb0, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_parts_0218087a[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x88, 0x08, 0x40, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0xc0, 0x08, 0x38, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0218040c[] = {
    {0x0e, 0x08, (short)0xf000, 0, 0x08, 0x78, 0xf0, 0x1c},
    PARTS_END,
};

static UnkMenuParts s_parts_02180d12[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x90, 0xa6, 0x30, 0x08},
    {0x07, 0x00, (short)0xf000, 17, 0x90, 0xa0, 0x30, 0x08},
    {0x11, 0x00, 0x0000, 1, 0x88, 0xb0, 0x00, 0x00},
    PARTS_END,
};

THUMB void drawItemDetail(int itemID, int flag)
{
    UnkMenuParts* parts = s_parts_021807fc;
    setMenuDrawOffset(0, 0);
    int param[5] = {-1};
    for (int i = 0; i < 5; i++) {
        param[i] = -1;
    }
    MaterielMenuPlayerControl* control = MaterielMenuPlayerControl::getSingleton();
    int base;
    int item = control->activeItem_;
    base = control->activeItemPage_ * 6;
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    unsigned int mode = MenuStatusInfo::getMode();
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    MenuStatusInfo::setMode(mode);
    if (itemID == -1) {
        if (chara == partyCount) {
            itemID = MenuStatusInfo::getFukuroItemID(item + base, 0);
        } else {
            int activeChara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
            int values[4] = {-1};
            for (int i = 0; i < 4; i++) {
                values[i] = -1;
            }
            itemID = MenuStatusInfo::getPlayerItemID(activeChara, item + base);
            switch (getShopEquipCompare(activeChara, values, itemID)) {
                case 0:
                    parts = s_parts_02180fb2;
                    param[2] = values[1];
                    break;
                case 1:
                    parts = s_parts_021814c8;
                    param[2] = values[1];
                    param[3] = values[2];
                    param[4] = values[3];
                    break;
                case 2:
                    parts = s_parts_02180fea;
                    param[2] = values[1];
                    param[3] = values[2];
                    break;
            }
        }
    }
    if (status::UseItem::getEquipItemType(itemID) <= ITEM_ACCESSORY) {
        param[0] = MenuDataCommon::getEquipKind(status::UseItem::getEquipItemType(itemID));
        param[1] = MenuDataCommon::getItemMessageNo(itemID);
    } else {
        parts = s_parts_021807fc;
        param[0] = MenuDataCommon::getItemTypeMessageNo(itemID);
        param[1] = MenuDataCommon::getItemMessageNo(itemID);
    }
    if (flag == 1) {
        drawMenuParts(parts, param, 0, 0x28, data_02094dd4[0]);
        drawMenuFrame(0, 0x78, 0x100, 0x48, 0x90);
        return;
    }
    int message = status::UseItem::getMenuMessage(itemID) + 0x20000000;
    drawMenuPartsColored(parts, param, data_02094dd4[0]);
    drawMenuPartsColored(s_parts_021804ec, &message, data_02094dd4[0]);
    drawMenuFrame(0, 0x50, 0x100, 0x70, 0x68);
    drawMenuFrameLine(0, 0x90, 0x100);
}

static UnkMenuParts s_parts_021808a4[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x88, 0x1a, 0x38, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0xc0, 0x1a, 0x38, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02181148[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x14, 0x80, 0x30, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 1, 0x28, 0x80, 0x28, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0x60, 0x80, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 3, 0x60, 0x80, 0x20, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_021808ce[] = {
    {0x14, 0xc0, 0x0000, -1, 0x04, 0x00, 0x21, 0x10},
    {0x0d, 0x09, (short)0xf000, 0, 0x00, 0x02, 0x29, 0x10},
    PARTS_END,
};

THUMB void drawSellQuantity(int value)
{
    int param[2] = {(int)"\xff\xfe\xa9\x24", 0};
    param[1] = value;
    drawMenuPartsColored(s_parts_02180826, param, data_02094dd4[0]);
    drawMenuFrame(0x98, 0x50, 0x68, 0x28, -1);
}

static UnkMenuParts s_parts_021808f8[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x04, 0x21, 0x10},
    {0x0d, 0x09, (short)0xf000, 0, 0x00, 0x06, 0x20, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02180460[] = {
    {0x0f, 0x09, (short)0xf000, 0, 0xb0, 0x0a, 0x10, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_parts_02180e2a[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x48, 0x00, 0x20, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x6a, 0x00, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x74, 0x00, 0x78, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0218127c[] = {
    {0x0c, 0xf4, 0x0000, 0, 0xa8, 0x30, 0x18, 0x18},
    {0x0f, 0x0a, (short)0xf000, 1, 0xc8, 0x3a, 0x08, 0x0c},
    {0x0d, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x78, 0x0c},
    {0x0f, 0x0a, (short)0xf000, 3, 0xd8, 0x3a, 0x08, 0x0c},
    {0x0c, 0xf4, 0x0000, 4, 0xe0, 0x30, 0x18, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_021805cc[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x14, 0x02, 0x70, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_0218047c[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x0a, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180604[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x02, 0x68, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_021819d0[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x08, 0x0e, 0xf0, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x1c, 0x38, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x68, 0x38, 0x08, 0x10},
    {0x0f, 0x08, (short)0xf000, 3, 0x78, 0x38, 0x10, 0x10},
    {0x0d, 0x08, (short)0xf000, 4, 0x1c, 0x50, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 5, 0x68, 0x50, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 6, 0x1c, 0x60, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 7, 0x68, 0x60, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 8, 0x1c, 0x70, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 9, 0x68, 0x70, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 10, 0x1c, 0x88, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 11, 0x38, 0x88, 0x08, 0x10},
    {0x19, 0x08, (short)0xf000, 12, 0x40, 0x88, 0xb8, 0x40},
    {0x0c, 0xf0, 0x0000, 13, 0xa8, 0x28, 0x20, 0x20},
    {0x14, 0xc0, 0x0000, -1, 0xac, 0x38, 0x20, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_0218094c[] = {
    {0x0d, 0x0a, (short)0xf000, 1, 0x58, 0x9e, 0x28, 0x0c},
    {0x0f, 0x0b, (short)0xf000, 0, 0x04, 0x00, 0x10, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_parts_02181324[] = {
    {0x0c, 0xf4, 0x0000, 0, 0x58, 0xa4, 0x18, 0x18},
    {0x0f, 0x0a, (short)0xf000, 1, 0x74, 0xa8, 0x08, 0x0c},
    {0x0d, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x78, 0x0c},
    {0x0f, 0x0a, (short)0xf000, 3, 0x84, 0xa8, 0x08, 0x0c},
    {0x0c, 0xf4, 0x0000, 4, 0x90, 0xa4, 0x18, 0x18},
    PARTS_END,
};

static UnkMenuParts s_parts_02180658[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x10, 0x60, 0x10},
    PARTS_END,
};

THUMB void drawPokerPayoutTable()
{
    setMenuDrawOffset(0, 0);
    int rate[10] = {1, 1, 2, 4, 5, 10, 20, 50, 100, 500};
    int text[10] = {
        (int)0xe000036a, (int)0xe0000369, (int)0xe0000368, (int)0xe0000367, (int)0xe0000366,
        (int)0xe0000365, (int)0xe0000364, (int)0xe0000363, (int)0xe0000362, (int)0xe0000361,
    };
    int param[2] = {2, 0};
    int hand = casino::PokerManager::getSingleton()->winningCombination_ - 2;
    int bet = casino::PokerManager::getSingleton()->betCoin_;
    if (bet == 0) {
        bet = 1;
    }
    for (int i = 9; i >= 0; i--) {
        param[0] = text[i];
        param[1] = rate[i] * bet;
        if (i == hand) {
            drawMenuParts(s_parts_02180850, param, 0, 0xa4 - i * 16, data_02094dd4[5]);
        } else {
            drawMenuParts(s_parts_02180850, param, 0, 0xa4 - i * 16, data_02094dd4[0]);
        }
    }
    drawMenuFrame(0, 0, 0x100, 0xc0, -1);
}

THUMB void drawPokerCoinsAndBet(int coin, int bet, int flag, int type)
{
    int param[2] = {(int)0xe0000140, 0};
    int color = 0;
    param[1] = coin;
    drawMenuPartsColored(s_parts_0218087a, param, data_02094dd4[0]);
    param[1] = bet;
    if (flag == 1) {
        param[0] = (int)0xe0000355;
        color = 5;
    } else {
        param[0] = (int)0xe0000354;
    }
    drawMenuPartsColored(type == 1 ? s_parts_02180380 : s_parts_021808a4, param, data_02094dd4[color]);
    drawMenuFrame(0x80, 0, 0x80, 0x30, -1);
}

static UnkMenuParts s_parts_0218071c[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x00, 0x100, 0x60},
    PARTS_END,
};

THUMB void drawHighLowCommands(int flag)
{
    int param[2] = {-1};
    for (int i = 0; i < 2; i++) {
        param[i] = -1;
    }
    getHighLowCommandText(param, flag);
    drawMenuPartsColored(s_parts_02181030, param, data_02094dd4[0]);
}

static UnkMenuParts s_parts_02180ed2[] = {
    {0x0d, 0x0a, (short)0xf000, 0, 0x08, 0x0a, 0x18, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0x28, 0x0a, 0x18, 0x10},
    {0x0d, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x18, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180700[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x50, 0x18, 0x18, 0x08},
    PARTS_END,
};

THUMB void drawPokerHoldLabels(int* flags)
{
    int x[5] = {0, 0x30, 0x60, 0x90, 0xc0};
    int param = 0;
    for (int i = 0; i < 5; i++) {
        param = (int)0xe000035c;
        if (flags[i] == 1) {
            param = (int)0xe000035d;
        }
        drawMenuParts(s_parts_021808ce, &param, x[i] + 0xb, 0x7a, data_02094dd4[0]);
    }
    param = (int)0xe000035e;
    drawMenuParts(s_parts_021808f8, &param, 0x6f, 0x8c, data_02094dd4[0]);
}

static UnkMenuParts s_parts_021805e8[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x00, 0x0c, 0xf0, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180578[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x0c, 0x00, 0x08, 0x10},
    PARTS_END,
};

THUMB void drawMonsterBookPage()
{
    int param[2] = {-1};
    for (int i = 0; i < 2; i++) {
        param[i] = -1;
    }
    int page = MaterielMenuPlayerControl::getSingleton()->activeItemPage_;
    int count = 0xca - page * 16;
    int base = page * 16;
    count = dss::clamp<int>(1, count, 16);
    for (int i = 0; i < count; i++) {
        if (status::g_BattleResult.isMonsterEncount(i + page * 16u) == true) {
            param[0] = status::g_BattleResult.getMonsterIndex(base + i) + 0x60000000;
        } else {
            param[0] = (int)0xe0000321;
        }
        drawMenuParts(s_parts_02180498, param, (i % 2) * 0x70 + 0x20, (i / 2) * 12 + (i / 2) * 4 + 0xd, data_02094dd4[4]);
    }
    param[0] = page + 1;
    param[1] = (int)0xe0000320;
    if (status::g_Game.language_ == Japanese) {
        drawMenuPartsColored(s_parts_02180922, param, data_02094dd4[4]);
    } else {
        drawMenuPartsColored(s_parts_0218094c, param, data_02094dd4[4]);
    }
}

static UnkMenuParts s_parts_0218039c[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x90, 0xaa, 0x30, 0x08},
    PARTS_END,
};

static UnkMenuParts s_parts_02180f42[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x38, 0xb0, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x10, 0x48, 0xb0, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x10, 0x58, 0xb0, 0x10},
    PARTS_END,
};

THUMB void drawMonsterBookDetail(int index)
{
    int count = status::g_BattleResult.result_[index].monsterCount_;
    int item = status::g_BattleResult.getMonsterItemIndex(index);
    int friendly = status::g_BattleResult.getMonsterFriendly(index);
    int level = status::g_BattleResult.result_[index].level_;
    int text[4] = {(int)0xe0000325, (int)0xe0000326, (int)0xe0000327, (int)0xe0000328};
    int param[19] = {
        0, 0, (int)0xe000032d, 0, (int)0xe000032e, 0, (int)0xe000032f, 0, (int)0xe0000330, 0,
        (int)0xe0000331, 0, (int)0xe0000332, 0, (int)0xe0000321, (int)0xe0000334, (int)0xe0000118, 0, (int)"\xff\xfe\xa8\x24",
    };
    param[0] = index + 1;
    param[1] = status::g_BattleResult.getMonsterIndex(index) + 0x60000000;
    param[3] = count;
    param[5] = status::g_BattleResult.getMonsterExp(index);
    param[7] = status::g_BattleResult.getMonsterTotalExp(index);
    param[9] = status::g_BattleResult.getMonsterGold(index);
    param[11] = status::g_BattleResult.getMonsterTotalGold(index);
    param[13] = status::g_BattleResult.result_[index].itemCount_;
    param[17] = text[friendly];
    if (item == 0) {
        param[14] = (int)"NASHI";
    } else if (item != -1) {
        param[14] = item + 0x40000000;
    }
    drawMenuPartsColored(s_parts_02181b9e, param, data_02094dd4[4]);
    if (level == 0) {
        level = (int)"@\x81\\";
        drawMenuPartsColored(s_parts_02180428, &level, data_02094dd4[4]);
    } else {
        drawMenuPartsColored(s_parts_02180674, &level, data_02094dd4[4]);
    }
}

THUMB void drawChurchCommands()
{
    int count = MaterielMenuPlayerControl::getSingleton()->churchCommandNum_;
    int text[6];
    int flag = 0;
    if (count != 6) {
        flag = 1;
    }
    getChurchCommandText(text, flag);
    for (int i = 0; i < count; i++) {
        drawMenuParts(s_parts_021803f0, &text[i], (i % 2) * 0x60 + 0x44, (i / 2) * 0x18 + 0xc, data_02094dd4[0]);
    }
    drawMenuFrame(0x30, 0, 0xd0, 0x58, -1);
}

THUMB void drawBankDigits(int value, int flag)
{
    int y = 0;
    int digit = 0;
    int div = 100000;
    if (flag == 1) {
        y = 0x50;
    }
    for (int i = 0; i < 6; i++) {
        digit = value / div;
        if (flag == 0 && i == 0) {
            value = value % div;
            div = div / 10;
        } else {
            drawMenuParts(s_parts_02180460, &digit, i * 10 + 5, y, data_02094dd4[0]);
            value = value % div;
            div = div / 10;
        }
    }
    drawMenuFrame(0xa8, y, 0x58, 0x20, -1);
}

THUMB void drawActiveCharaHp(int flag)
{
    int param[2] = {0, 0};
    for (int i = 0; i < 2; i++) {
        param[i] = 0;
    }
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    if (chara == -2 || chara == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        if (chara == -2) {
            param[0] = 0x5000024d;
        } else {
            param[0] = 0x5000024e;
        }
        drawMenuFrame(0x48, 0xa0, 0x40, 0x20, -1);
        drawMenuPartsColored(s_parts_0218032c, param, data_02094dd4[0]);
        return;
    }
    int hp = MenuDataCommon::getStatus(chara, MenuDataCommon::NOWHP, false);
    int maxHp = MenuDataCommon::getStatus(chara, MenuDataCommon::MAXHP, false);
    param[0] = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
    param[1] = hp * 100 / maxHp;
    if (param[1] <= 0 && hp > 0) {
        param[1] = 1;
    }
    UnkMenuParts* parts;
    if (flag == 1) {
        parts = s_parts_02180cda;
        drawMenuFrame(0, 0, 0x40, 0x20, -1);
    } else {
        parts = s_parts_02180ca2;
        drawMenuFrame(0x48, 0xa0, 0x40, 0x20, -1);
    }
    drawMenuPartsColored(parts, param, data_02094dd4[getActorConditionColor(chara)]);
}

THUMB void drawMemberCommandHeader(int type, int monster)
{
    int param[2] = {0, 0};
    for (int i = 0; i < 2; i++) {
        param[i] = 0;
    }
    if (type == 10) {
        param[0] = getMenuCommandText(2, 6);
    } else if (type < 6) {
        param[0] = getMenuCommandText(2, type);
    } else {
        param[0] = getMenuCommandText(3, type - 6);
    }
    drawMenuPartsPlain(s_parts_021804b4, param);
    drawMenuFrame(0x18, 0xa0, 0x70, 0x20, -1);
    drawCommandCursor(0x18, 0xb0);
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    int color = 0;
    UnkMenuParts* parts;
    if (chara == -1) {
        param[0] = 0x5000024e;
        parts = s_parts_0218039c;
    } else {
        parts = s_parts_02180d12;
        if (chara == 999) {
            param[0] = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(monster) + 0x50000000;
            param[1] = 100;
        } else {
            int hp = MenuDataCommon::getStatus(chara, MenuDataCommon::NOWHP, false);
            int maxHp = MenuDataCommon::getStatus(chara, MenuDataCommon::MAXHP, false);
            param[0] = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
            param[1] = hp * 100 / maxHp;
            if (param[1] <= 0 && hp > 0) {
                param[1] = 1;
            }
            color = getActorConditionColor(chara);
        }
    }
    drawMenuFrame(0x88, 0xa0, 0x40, 0x20, -1);
    drawMenuPartsColored(parts, param, data_02094dd4[color]);
}

THUMB void drawCommandCursor(int x, int y)
{
    drawMenuPartsAt(s_parts_0218055c, 0, x, y);
}

THUMB void drawCharaIconFrame(int chara, int y)
{
    int icon = 0x5d;
    if (chara != -1) {
        icon = MenuStatusInfo::getPlayerIconIndex(chara);
    }
    drawMenuPartsAt(s_parts_02180976, &icon, 0xc, y);
    drawMenuFrame(0, y, 0x38, 0x30, -1);
}

THUMB void drawNameEditIcon(int icon, int y)
{
    int param = icon;
    drawMenuPartsAt(s_parts_021809a0, &param, 0xc, y);
    drawMenuFrame(0, y, 0x38, 0x30, -1);
}

THUMB void drawCharaHpPercent(int chara, int x, int y)
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    int hpMax;
    int playerIndex = info.haveStatus_.playerIndex_;
    hpMax = info.getHpMax();
    int param[2] = {0, 0};
    for (int i = 0; i < 2; i++) {
        param[i] = 0;
    }
    param[0] = playerIndex + 0x50000000;
    param[1] = info.getHp() * 100 / hpMax;
    if (param[1] <= 0 && info.getHp() > 0) {
        param[1] = 1;
    }
    if (info.getHp() > hpMax / 4 - 1 && param[1] < 26) {
        param[1] = 26;
    }
    drawMenuParts(s_parts_02181076, param, x, y, data_02094dd4[getActorConditionColor(chara)]);
}

THUMB void unkfunc_0217a578(int icon, int x, int y)
{
    drawMenuPartsAt(s_parts_021809ca, &icon, x, y);
}

THUMB void drawCharaConditionMarks(int chara, int x, int y)
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    int param[3] = {0, (int)" ", (int)" "};
    int curse = 0;
    param[0] = chara + 1;
    int count = info.haveItem_.getMaxCount();
    for (int i = 0; i < count; i++) {
        if (info.haveItem_.isEquipment(i) == true && status::UseItem::isCurse(info.haveItem_.getItem(i))) {
            curse = 1;
        }
    }
    if (info.isDeath()) {
        param[1] = (int)0xe0000037;
    } else {
        if (info.statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU) || info.statusChange_.isEnable(dq5::level::ActionParam::ACTIONTYPE_MOUDOKU)) {
            param[1] = (int)0xe0000038;
        }
        if (info.isSpell() || curse) {
            param[2] = (int)0xe0000039;
        }
    }
    drawMenuParts(s_parts_02180d4a, param, x, y, data_02094dd4[getActorConditionColor(chara)]);
}

UnkMenuParts s_parts_02181650[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x80, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x0c, 0x1a, 0x10, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x18, 0x1a, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x32, 0x80, 0x10},
    {0x0f, 0x0a, (short)0xf000, 4, 0xa8, 0x32, 0x1c, 0x10},
    {0x0d, 0x0a, (short)0xf000, 5, 0xc8, 0x32, 0x0c, 0x10},
    {0x0f, 0x0a, (short)0xf000, 6, 0xb0, 0x32, 0x44, 0x10},
    {0x0c, 0xf0, 0x0000, 7, 0xd8, 0x04, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_parts_021803d4[] = {
    {0x14, 0xc0, 0x0000, -1, 0x00, 0x10, 0x20, 0x18},
    PARTS_END,
};

THUMB void drawCharaStatusPanel(int chara, int x, int y)
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    int color = getActorConditionColor(chara);
    drawMenuPartsAt(s_parts_021809f4, 0, x, y);
    int level[2] = {(int)"\xff\xfe\xa8\x24", 0};
    level[1] = info.haveStatus_.level_;
    int param[9] = {0, (int)0xe0000016, (int)0xe0000014, 0, 0, (int)0xe0000015, 0, 0, (int)"\xff\xfe\xa7\x24"};
    param[0] = info.haveStatus_.playerIndex_ + 0x50000000;
    param[3] = info.getHp();
    param[4] = info.getHpMax();
    param[6] = info.getMp();
    param[7] = info.getMpMax();
    int status[5] = {(int)0xe0000019, 0, (int)0xe000001a, 0, (int)"\xff\xfe\xa8\x24"};
    status[1] = info.getAttack(0);
    status[3] = info.getDefence(0);
    drawMenuParts(s_parts_02180a48, level, x, y, data_02094dd4[color]);
    drawMenuParts(s_parts_021816ce, param, x, y, data_02094dd4[color]);
    drawMenuParts(s_parts_0218151c, status, x, y, data_02094dd4[color]);
}

static UnkMenuParts s_parts_0218182c[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x08, 0x0e, 0xf0, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x20, 0x38, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x68, 0x38, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x20, 0x50, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 4, 0x68, 0x50, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 5, 0x20, 0x60, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 6, 0x68, 0x60, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 7, 0x20, 0x70, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 8, 0x68, 0x70, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 9, 0x20, 0x90, 0x48, 0x10},
    {0x0d, 0x08, (short)0xf000, 10, 0x38, 0x90, 0x08, 0x10},
    {0x19, 0x08, (short)0xf000, 11, 0x40, 0x90, 0xb8, 0x40},
    {0x0c, 0xf0, 0x0000, 12, 0xa8, 0x28, 0x20, 0x20},
    {0x14, 0xc0, 0x0000, -1, 0xac, 0x38, 0x20, 0x18},
    PARTS_END,
};

THUMB void drawRaceOddsEntry(int first, int second, int value, int count, int x, int y, int flag)
{
    int param[6] = {(int)"@\x81\\", 0, (int)"@\x81" "D", 0, (int)"\xff\xfe\xa9\x24", 0};
    param[1] = value / 10;
    param[3] = value % 10;
    param[5] = count;
    if (flag) {
        drawMenuParts(s_parts_0218157e, param, x, y, 0xb);
    } else {
        drawMenuParts(s_parts_0218157e, param, x, y, data_02094dd4[0]);
    }
    drawRaceSlimeNumber(first, x, y, flag);
    x += 0x16;
    drawRaceSlimeNumber(second, x, y, flag);
}

static UnkMenuParts s_parts_02181768[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x80, 0x58, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x40, 0x80, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x48, 0x80, 0x70, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x8d, 0x58, 0x10},
    {0x0d, 0x08, (short)0xf000, 4, 0x40, 0x8d, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 5, 0x48, 0x8d, 0x70, 0x10},
    {0x0d, 0x08, (short)0xf000, 6, 0x08, 0x9b, 0x58, 0x10},
    {0x0d, 0x08, (short)0xf000, 7, 0x40, 0x9b, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 8, 0x48, 0x9b, 0x70, 0x10},
    {0x0d, 0x08, (short)0xf000, 9, 0x08, 0xa8, 0x58, 0x10},
    {0x0d, 0x08, (short)0xf000, 10, 0x40, 0xa8, 0x08, 0x10},
    {0x0f, 0x08, (short)0xf000, 11, 0x48, 0xa8, 0x70, 0x10},
    {0x0d, 0x0b, (short)0xf000, 12, 0x00, 0x00, 0x08, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180826[] = {
    {0x0d, 0x0a, (short)0xf000, 0, 0xc0, 0x5e, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0xc8, 0x5e, 0x18, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_021807e0[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x08, 0x10, 0xb0, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_021803f0[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x02, 0x50, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180d4a[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x00, 0x08, 0x0a, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x1c, 0x08, 0x0a, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0x1c, 0x13, 0x0a, 0x0a},
    PARTS_END,
};

UnkMenuParts s_parts_02180d82[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x30, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 1, 0x50, 0x00, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0x58, 0x00, 0x20, 0x0a},
    PARTS_END,
};

UnkMenuParts s_parts_02180df2[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x7c, 0x30, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 1, 0x50, 0x7c, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0x58, 0x7c, 0x20, 0x0a},
    PARTS_END,
};

THUMB void drawRaceSlimeNumber(int value, int x, int y, int flag)
{
    if (flag) {
        drawMenuParts(s_parts_0218047c, &value, x, y, 0xb);
        return;
    }
    switch (value) {
        case 1:
            drawMenuParts(s_parts_0218047c, &value, x, y, 5);
            break;
        case 2:
            drawMenuParts(s_parts_0218047c, &value, x, y, 6);
            break;
        case 3:
            drawMenuParts(s_parts_0218047c, &value, x, y, 7);
            break;
        case 4:
            drawMenuParts(s_parts_0218047c, &value, x, y, 8);
            break;
        case 5:
            drawMenuParts(s_parts_0218047c, &value, x, y, 9);
            break;
        case 6:
            drawMenuParts(s_parts_0218047c, &value, x, y, 10);
            break;
    }
}

THUMB void drawRaceOddsTable(int mode, int x, int y, int flag)
{
    UnkMenuParts* parts = s_parts_02180754;
    if (mode == 6) {
        parts = s_parts_0218071c;
    }
    drawMenuParts(parts, 0, x, y, 1);
    int index = 0;
    int lastY = 0;
    int offsetX = 0x10;
    int column = 6;
    int count = 5;
    int offsetY = 8;
    if (mode == 6) {
        column = 8;
        count = 6;
    }
    for (int i = 1; i < count; i++) {
        for (int j = i + 1; j <= count; j++) {
            int selected;
            if (index == g_RaceData.winningNum_ && g_RaceData.result_ != 0xff) {
                selected = 1;
            } else {
                selected = 0;
            }
            drawRaceOddsEntry(i, j, g_RaceData.oddsData_[index].odds, g_RaceData.oddsData_[index].coin, offsetX + x, offsetY + y, selected);
            index++;
            offsetY += 10;
            if (index == column) {
                lastY = offsetY;
                lastY -= 10;
                offsetY = 8;
                offsetX += 0x78;
            }
        }
    }
    if (flag) {
        int text = (int)0xe0000384;
        drawMenuParts(s_parts_021807a8, &text, offsetX + x, lastY + y, 1);
    }
}

THUMB void drawRaceCoinValue(int value, int x, int y)
{
    int param[2] = {(int)0xe0000352, 0};
    param[1] = value;
    drawMenuParts(s_parts_02180f7a, param, x, y, 1);
}

UnkMenuParts s_parts_0218032c[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x50, 0xaa, 0x30, 0x08},
    PARTS_END,
};

UnkMenuParts s_parts_02181b9e[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x08, 0x18, 0x28, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x38, 0x18, 0x68, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0x98, 0x18, 0x50, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 3, 0x98, 0x18, 0x50, 0x0a},
    {0x0d, 0x08, (short)0xf000, 4, 0x98, 0x28, 0x38, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 5, 0x98, 0x28, 0x50, 0x0a},
    {0x0d, 0x08, (short)0xf000, 6, 0x98, 0x38, 0x50, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 7, 0x98, 0x38, 0x50, 0x0a},
    {0x0d, 0x08, (short)0xf000, 8, 0x98, 0x48, 0x50, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 9, 0x98, 0x48, 0x50, 0x0a},
    {0x0d, 0x08, (short)0xf000, 10, 0x98, 0x58, 0x50, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 11, 0x98, 0x58, 0x50, 0x0a},
    {0x0d, 0x08, (short)0xf000, 12, 0x98, 0x68, 0x50, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 13, 0x98, 0x68, 0x50, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 14, 0x78, 0x78, 0x70, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 15, 0x88, 0x88, 0x60, 0x0a},
    {0x0d, 0x08, (short)0xf000, 16, 0xa8, 0x98, 0x40, 0x0a},
    {0x0d, 0x08, (short)0xf000, 17, 0x18, 0x28, 0x68, 0x0a},
    {0x0d, 0x08, (short)0xf000, 18, 0x30, 0x18, 0x68, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02180620[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x3e, 0x80, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180922[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x64, 0x9e, 0x10, 0x0c},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x28, 0x0c},
    PARTS_END,
};

THUMB void drawSlimeTouchRankEntry(int first, int second, int third, int x, int y)
{
    int param[3] = {first, third, second};
    drawMenuParts(s_parts_02180bc2, param, x, y, 1);
}

THUMB void drawTagModeRootMenu()
{
    drawMenuPartsColored(s_parts_021802f4, 0, data_02094dd4[0]);
    for (int i = 0; i < 5; i++) {
        int text = getTagModeRootText(i);
        drawMenuParts(s_parts_021805cc, &text, 0, i * 16 + 0xc + i * 4, data_02094dd4[0]);
    }
    drawMenuFrame(0, 0, 0x90, 0x78, -1);
}

THUMB void drawTagModeIconGrid(int type, int value)
{
    int count = 12;
    if (type == 5) {
        count = 4;
    }
    for (int i = 0; i < count; i++) {
        int index = type * 12 + i;
        int cgicon = dq5::level::SurechigaiData::getRecord(index + 1)->cgicon;
        int x = (i % 6) * 0x28 + 0xc;
        int y = (i / 6) * 0x28 + 0x20;
        if (status::g_MuseumStatus.selectTaishiFlag_[index] == 1) {
            drawMenuParts(s_parts_02180540, &cgicon, x, y, data_02094dd4[0]);
        }
        drawMenuParts(s_parts_021803d4, 0, x, y, data_02094dd4[0]);
    }
    int text = (int)0xe00003c0;
    drawMenuPartsColored(s_parts_02180348, &text, data_02094dd4[0]);
    int param[5] = {0xc, 0, (int)"\xff\xfe\xa7\x24", 0, 0xd};
    param[1] = type + 1;
    param[3] = value;
    drawMenuPartsColored(s_parts_02181228, param, data_02094dd4[0]);
    drawMenuFrame(0, 0, 0x100, 0x78, 0x20);
}

static UnkMenuParts s_parts_0218078c[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x20, 0x00, 0x0e, 0x0a},
    PARTS_END,
};

THUMB void drawTagModeTenantList(int page, int value, int flag)
{
    int rest = status::g_MuseumStatus.getTaishiCount() - page * 8;
    int count = dss::clamp<int>(0, rest, 8);
    for (int i = 0; i < count; i++) {
        int name = (int)status::g_MuseumStatus.getOthersTaishi(i + page * 8).getTaishiName();
        drawMenuParts(s_parts_021804d0, &name, (i % 2) * 0x78 + 0x10, (i / 2) * 0x18 + 0x5c, data_02094dd4[0]);
    }
    int param[3] = {(int)0xe00003b8, (int)0xe00003bb, (int)"\xff\xfe\xac\x24"};
    if (flag == 1) {
        param[0] = (int)0xe00003b9;
    }
    drawMenuPartsColored(s_parts_02180bfa, param, data_02094dd4[0]);
    if (status::g_MuseumStatus.getTaishiCount() > 8) {
        int pageParam[5] = {0xc, 0, (int)"\xff\xfe\xa7\x24", 0, 0xd};
        pageParam[1] = page + 1;
        pageParam[3] = value;
        drawMenuPartsColored(s_parts_0218127c, pageParam, data_02094dd4[0]);
    }
    drawMenuFrame(0, 0x30, 0x100, 0x90, 0x50);
    drawMenuFrame(0x38, 0x10, 0x58, 0x20, -1);
}

UnkMenuParts s_parts_021807c4[] = {
    {0x0d, 0x0a, (short)0xf000, 0, 0x08, 0x80, 0x48, 0x0a},
    PARTS_END,
};

THUMB void drawTagModeProfile(int index, int mode)
{
    if (mode == 0 && status::g_MuseumStatus.getTaishiCount() == 0) {
        return;
    }
    setMenuDrawOffset(0, 0);
    status::TaishiBase* taishi;
    if (mode == 1) {
        taishi = &status::g_MuseumStatus.getPlayerTaishi();
    } else {
        taishi = &status::g_MuseumStatus.getOthersTaishi(index);
    }
    int param[13] = {
        (int)0xe00003c5, (int)"\xff\xfe\xa8\x24", 0, (int)0xe00003c6, (int)"\xff\xfe\xa8\x24", 0,
        (int)0xe00003c7, (int)"\xff\xfe\xa8\x24", 0, (int)0xe00003c8, (int)"\xff\xfe\xa8\x24", 0, (int)0xe0000071,
    };
    param[2] = (int)taishi->taishiName_;
    param[5] = taishi->production_ + (int)0xc0000320;
    param[8] = (int)taishi->producer_;
    param[11] = taishi->price_;
    drawMenuPartsColored(s_parts_02181768, param, data_02094dd4[0]);
    drawMenuFrame(0, 0x70, 0xc0, 0x50, -1);
}

UnkMenuParts s_parts_02180af0[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x7c, 0x30, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x40, 0x7c, 0x48, 0x0a},
    PARTS_END,
};

THUMB void drawTagModeTenantDetail(int index, int mode, int flag)
{
    int x = 0;
    if (flag == 1) {
        x = 0x18;
    }
    status::TaishiBase* taishi;
    if (mode == 1) {
        taishi = &status::g_MuseumStatus.getPlayerTaishi();
    } else {
        taishi = &status::g_MuseumStatus.getOthersTaishi(index);
    }
    int param[14] = {
        0, (int)0xe00003c5, (int)"\xff\xfe\xa8\x24", 0, (int)0xe00003c6, (int)"\xff\xfe\xa8\x24", 0,
        (int)0xe00003c7, (int)"\xff\xfe\xa8\x24", 0, (int)0xe00003c8, (int)"\xff\xfe\xa8\x24", 0, (int)0xe0000071,
    };
    param[0] = dq5::level::SurechigaiData::getRecord(taishi->objectId_)->cgicon;
    param[3] = (int)taishi->getTaishiName();
    param[6] = taishi->production_ + (int)0xc0000320;
    param[9] = (int)taishi->producer_;
    param[12] = taishi->price_;
    drawMenuParts(s_parts_021818fe, param, x, 0, data_02094dd4[0]);
    x += 0x18;
    drawMenuFrame(x, 0, 0xa8, 0x78, 0x28);
}

THUMB void drawTagModeProductionList(int page)
{
    drawTagModeName((int)status::g_MuseumStatus.getPlayerTaishi().getTaishiName(), 1);
    int count = 0x40 - page * 8;
    count = dss::clamp<int>(0, count, 8);
    for (int i = 0; i < count; i++) {
        int text = i + (int)0xc0000321 + page * 8;
        drawMenuParts(s_parts_02180604, &text, (i % 2) * 0x78 + 0x10, (i / 2) * 0x18 + 0x5c, data_02094dd4[0]);
    }
    int title = (int)0xe00003c2;
    drawMenuPartsColored(s_parts_02180620, &title, data_02094dd4[0]);
    int param[5] = {0xc, 0, (int)"\xff\xfe\xa7\x24", 8, 0xd};
    param[1] = page + 1;
    drawMenuPartsColored(s_parts_02181378, param, data_02094dd4[0]);
    drawMenuFrame(0, 0x30, 0x100, 0x90, 0x50);
}

THUMB void drawTagModePriceInput(int value)
{
    int param[3] = {(int)0xe00003c6, (int)"\xff\xfe\xa8\x24", 0};
    param[2] = status::g_MuseumStatus.getPlayerTaishi().production_ + (int)0xc0000320;
    drawMenuPartsColored(s_parts_02180e62, param, data_02094dd4[0]);
    drawTagModeName((int)status::g_MuseumStatus.getPlayerTaishi().getTaishiName(), 0);
    int div = 100000;
    for (int i = 0; i < 6; i++) {
        param[0] = value / div;
        drawMenuParts(s_parts_021805b0, param, i * 10 + 5, 0, data_02094dd4[0]);
        value = value % div;
        div = div / 10;
    }
    param[0] = (int)0xe0000071;
    drawMenuPartsColored(s_parts_0218063c, param, data_02094dd4[0]);
    param[0] = (int)0xe00003c3;
    drawMenuPartsColored(s_parts_021806e4, param, data_02094dd4[0]);
    drawMenuFrame(0, 0x30, 0x100, 0x48, 0x48);
}

UnkMenuParts s_parts_0218055c[] = {
    {0x15, 0xb5, 0x0000, 0, 0x00, 0x00, 0x00, 0x00},
    PARTS_END,
};

THUMB void drawTagModeComment()
{
    char line1[0x40];
    char line2[0x40];
    char line3[0x40];
    splitCommentLines(line1, line2, line3, status::g_MuseumStatus.getPlayerTaishi().getTaishiMessage());
    int param[3] = {(int)line1, (int)line2, (int)line3};
    drawMenuPartsColored(s_parts_02180f42, param, data_02094dd4[0]);
    param[0] = (int)0xe00003c9;
    drawMenuPartsColored(s_parts_021807e0, param, data_02094dd4[0]);
    drawMenuFrame(0, 8, 0xc0, 0x70, 0x20);
}

THUMB void drawMeisanhinList(int mode)
{
    int param[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        param[i] = 0;
    }
    int page = MaterielMenuPlayerControl::getSingleton()->activeItemPage_;
    int count = 0x1c - page * 16;
    count = dss::clamp<int>(1, count, 16);
    for (int i = 0; i < count; i++) {
        dq5::level::MeisanhinData* data = dq5::level::MeisanhinData::getRecord(getMeisanhinRecordIndex(i + page * 16));
        int item = data->itemid;
        param[0] = item + 0x40000000;
        if ((mode == 0 && data->getPoint1() == 1) || (mode == 1 && data->getPoint2() == 1)) {
            if (item == 0xf7 || item == 0xfa) {
                if (!g_AreaFlag.check(0x226) && !g_AreaFlag.check(getMeisanhinFlagNo(item))) {
                    param[0] = (int)0xe0000321;
                }
            } else {
                if (!g_AreaFlag.check(getMeisanhinFlagNo(item))) {
                    param[0] = (int)0xe0000321;
                }
            }
        }
        drawMenuParts(s_parts_02180658, param, (i % 2) * 0x70 + 0x18, (i / 2) * 12 + (i / 2) * 4 + 0xd, data_02094dd4[0]);
    }
    param[0] = 0xc;
    param[1] = page + 1;
    param[2] = (int)"\xff\xfe\xa7\x24";
    param[3] = 2;
    param[4] = 0xd;
    drawMenuPartsColored(s_parts_021811d4, param, data_02094dd4[0]);
    drawMenuFrame(0, 0, 0x100, 0xc0, -1);
}

THUMB void drawMeisanhinDetail()
{
    dq5::level::MeisanhinData* data = dq5::level::MeisanhinData::getRecord(getMeisanhinRecordIndex(MaterielMenuPlayerControl::getSingleton()->activeItem_));
    int level = data->point3;
    int point4 = data->point4;
    int point5 = data->point5;
    int point6 = data->point6;
    int star = (int)"\xff\xfe\xb9\x24";
    int item = data->itemid;
    int param[13] = {
        0, (int)0xe00003a4, (int)"\xff\xfe\xa8\x24", (int)0xe00003a6, (int)"\xff\xfe\xa8\x24", (int)0xe00003a7, (int)"\xff\xfe\xa8\x24",
        (int)0xe00003a8, (int)"\xff\xfe\xa8\x24", (int)0xe00003a9, (int)"\xff\xfe\xa8\x24", 0, 0,
    };
    param[0] = item + 0x40000000;
    param[11] = data->message1;
    param[12] = item;
    if (item == 0xdc && g_AreaFlag.check(getMeisanhinFlagNo(0xdd)) == true) {
        param[11] = data->message2;
    }
    int known = 1;
    if (!g_AreaFlag.check(getMeisanhinFlagNo(item))) {
        param[12] = 0x14f;
        if (data->getPoint1() == 1) {
            if (item == 0xf7 || item == 0xfa) {
                if (!g_AreaFlag.check(0x226) && !g_AreaFlag.check(getMeisanhinFlagNo(item))) {
                    known = 0;
                }
            } else {
                if (!g_AreaFlag.check(getMeisanhinFlagNo(item))) {
                    known = 0;
                }
            }
        }
    }
    if (known == 1) {
        drawMenuPartsColored(s_parts_021803b8, &level, data_02094dd4[0]);
        for (int i = 0; i < point4; i++) {
            drawMenuParts(s_parts_02180364, &star, i * 8 + i * 2, 0x48, data_02094dd4[0]);
        }
        for (int i = 0; i < point5; i++) {
            drawMenuParts(s_parts_02180364, &star, i * 8 + i * 2, 0x58, data_02094dd4[0]);
        }
        for (int i = 0; i < point6; i++) {
            drawMenuParts(s_parts_02180364, &star, i * 8 + i * 2, 0x68, data_02094dd4[0]);
        }
    } else {
        param[0] = (int)0xe0000321;
        param[11] = (int)0xe0000321;
        level = (int)0xe0000321;
        star = (int)0xe0000321;
        drawMenuParts(s_parts_02180364, &level, 0, 0x30, data_02094dd4[0]);
        drawMenuParts(s_parts_02180364, &star, 0, 0x48, data_02094dd4[0]);
        drawMenuParts(s_parts_02180364, &star, 0, 0x58, data_02094dd4[0]);
        drawMenuParts(s_parts_02180364, &star, 0, 0x68, data_02094dd4[0]);
    }
    drawMenuPartsColored(s_parts_0218182c, param, data_02094dd4[0]);
    drawMenuFrame(0, 0, 0x100, 0xc0, 0x20);
}

THUMB void drawMuseumItemDetail(int index)
{
    dq5::level::MeisanhinData* data = status::g_MuseumStatus.getMuseumItemStatus(index).getMeisanhinData();
    int param[14] = {
        0, (int)0xe00003a4, (int)"\xff\xfe\xa8\x24", 0, (int)0xe00003a6, (int)"\xff\xfe\xa8\x24", (int)0xe00003a7,
        (int)"\xff\xfe\xa8\x24", (int)0xe00003a8, (int)"\xff\xfe\xa8\x24", (int)0xe00003a9, (int)"\xff\xfe\xa8\x24", 0, 0,
    };
    param[0] = data->itemid + 0x40000000;
    param[13] = data->itemid;
    param[3] = data->point3;
    param[12] = data->message1;
    drawMenuPartsColored(s_parts_021819d0, param, data_02094dd4[0]);
    int point4 = data->point4;
    int point5 = data->point5;
    int point6 = data->point6;
    int star = (int)"\xff\xfe\xb9\x24";
    for (int i = 0; i < point4; i++) {
        drawMenuParts(s_parts_02180444, &star, i * 8 + i * 2, 0x48, data_02094dd4[0]);
    }
    for (int i = 0; i < point5; i++) {
        drawMenuParts(s_parts_02180444, &star, i * 8 + i * 2, 0x58, data_02094dd4[0]);
    }
    for (int i = 0; i < point6; i++) {
        drawMenuParts(s_parts_02180444, &star, i * 8 + i * 2, 0x68, data_02094dd4[0]);
    }
    drawMenuFrame(0, 0, 0x100, 0xc0, 0x20);
}

THUMB void drawShopItemHeader(int itemID)
{
    setMenuDrawOffset(0, 0);
    int param = 0;
    int item = MaterielMenuPlayerControl::getSingleton()->activeItem_;
    if (itemID == -1) {
        itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(item);
    }
    if (status::UseItem::getEquipItemType(itemID) <= ITEM_ACCESSORY) {
        param = MenuDataCommon::getItemMessageNo(itemID);
    } else {
        param = MenuDataCommon::getItemTypeMessageNo(itemID);
    }
    drawMenuPartsColored(s_parts_021805e8, &param, data_02094dd4[0]);
    param = status::UseItem::getMenuMessage(itemID) + 0x20000000;
    drawMenuPartsColored(s_parts_02180594, &param, data_02094dd4[0]);
}

THUMB int getShopEquipCompare(int chara, int* values, int itemID)
{
    int result = 1;
    values[0] = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
    if (itemID == -1) {
        MaterielMenuPlayerControl* control = MaterielMenuPlayerControl::getSingleton();
        itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(control->activeItem_);
    }
    bool equipped = MenuStatusInfo::isPlayerEquipItem(chara, itemID);
    if (!MenuStatusInfo::isPlayerEquipEnable(chara, itemID)) {
        values[1] = (int)0xe00000de;
        result = 0;
    } else {
        values[2] = (int)"\xff\xfe\xaf\x24";
        switch (status::UseItem::getEquipType(itemID)) {
            case Strength:
                if (equipped == true) {
                    values[1] = (int)0xe000003c;
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::STRENGTH, false);
                    result = 2;
                } else {
                    values[1] = MenuDataCommon::getStatus(chara, MenuDataCommon::STRENGTH, false);
                    values[3] = MenuStatusInfo::getHaveStatusInfo(chara).getChangeStrength(itemID);
                }
                break;
            case Attack:
                if (equipped == true) {
                    values[1] = (int)0xe000003c;
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::ATTACK, false);
                    result = 2;
                } else {
                    values[1] = MenuDataCommon::getStatus(chara, MenuDataCommon::ATTACK, false);
                    values[3] = MenuStatusInfo::getHaveStatusInfo(chara).getChangeAttack(itemID);
                }
                break;
            case Defence:
                if (equipped == true) {
                    values[1] = (int)0xe000003c;
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::DEFENCE, false);
                    result = 2;
                } else {
                    values[1] = MenuDataCommon::getStatus(chara, MenuDataCommon::DEFENCE, false);
                    values[3] = MenuStatusInfo::getHaveStatusInfo(chara).getChangeDefence(itemID);
                }
                break;
            case Agility:
                if (equipped == true) {
                    values[1] = (int)0xe000003c;
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::AGILITY, false);
                    result = 2;
                } else {
                    values[1] = MenuDataCommon::getStatus(chara, MenuDataCommon::AGILITY, false);
                    values[3] = MenuStatusInfo::getHaveStatusInfo(chara).getChangeAgility(itemID);
                }
                break;
            case Wisdom:
                if (equipped == true) {
                    values[1] = (int)0xe000003c;
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::WISDOM, false);
                    result = 2;
                } else {
                    values[1] = MenuDataCommon::getStatus(chara, MenuDataCommon::WISDOM, false);
                    values[3] = MenuStatusInfo::getHaveStatusInfo(chara).getChangeWisdom(itemID);
                }
                break;
            case Luck:
                if (equipped == true) {
                    values[1] = (int)0xe000003c;
                    values[2] = MenuDataCommon::getStatus(chara, MenuDataCommon::LUCK, false);
                    result = 2;
                } else {
                    values[1] = MenuDataCommon::getStatus(chara, MenuDataCommon::LUCK, false);
                    values[3] = MenuStatusInfo::getHaveStatusInfo(chara).getChangeLuck(itemID);
                }
                break;
        }
    }
    return result;
}

THUMB int getShopHeldCount(int chara, int* values, int itemID)
{
    values[0] = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
    int count = 0;
    int item = MaterielMenuPlayerControl::getSingleton()->activeItem_;
    if (itemID == -1) {
        itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(item);
    }
    for (int i = 0; i < MenuStatusInfo::getPlayerItemCount(chara); i++) {
        if (itemID == MenuStatusInfo::getPlayerItemID(chara, i)) {
            count++;
        }
    }
    if (count > 0) {
        values[1] = (int)"\xff\xfe\xa9\x24";
        values[2] = count;
        return 1;
    }
    values[1] = (int)0xe00000e2;
    return 0;
}

THUMB int getSellListRow(int* param, int chara, int index)
{
    int result = 1;
    if (chara == MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        param[0] = MenuStatusInfo::getFukuroItemID(index, 0) + 0x40000000;
        if (status::UseItem::getSellType(MenuStatusInfo::getFukuroItemID(index, 0)) == 1) {
            param[1] = (int)0xe0000231;
            result = 0;
            param[2] = param[3] = param[4] = 0;
        } else {
            param[1] = status::UseItem::getSellPrice(MenuStatusInfo::getFukuroItemID(index, 0));
            param[2] = (int)0xe0000071;
            param[3] = (int)"\xff\xfe\xa9\x24";
            param[4] = MenuStatusInfo::getFukuroItemCount(index);
        }
    } else {
        param[0] = MenuStatusInfo::getPlayerItemID(chara, index) + 0x40000000;
        if (status::UseItem::getSellType(MenuStatusInfo::getPlayerItemID(chara, index)) == 1) {
            param[1] = (int)0xe0000231;
            result = 0;
            param[2] = param[3] = param[4] = 0;
        } else {
            param[1] = status::UseItem::getSellPrice(MenuStatusInfo::getPlayerItemID(chara, index));
            param[2] = (int)0xe0000071;
            param[3] = param[4] = 0;
        }
    }
    return result;
}

THUMB void drawTagModeName(int value, int flag)
{
    if (flag == 1) {
        int name = value;
        drawMenuParts(s_parts_02180770, &name, 0, 0x18, data_02094dd4[0]);
        drawMenuFrame(0x38, 0x10, 0xa0, 0x20, -1);
    } else {
        int param[3] = {(int)0xe00003c5, (int)"\xff\xfe\xa8\x24", 0};
        param[2] = value;
        drawMenuParts(s_parts_02180e2a, param, 0, 0xa, data_02094dd4[0]);
        drawMenuFrame(0x38, 0, 0xa8, 0x30, -1);
    }
}

UnkMenuParts s_parts_021807fc[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x58, 0xa0, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x70, 0xa0, 0x18},
    PARTS_END,
};

UnkMenuParts s_parts_02180cda[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x06, 0x30, 0x08},
    {0x07, 0x00, (short)0xf000, 17, 0x08, 0x00, 0x30, 0x08},
    {0x11, 0x00, 0x0000, 1, 0x00, 0x10, 0x00, 0x00},
    PARTS_END,
};

UnkMenuParts s_parts_02180dba[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x30, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 1, 0x50, 0x00, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0x58, 0x00, 0x20, 0x0a},
    PARTS_END,
};

UnkMenuParts s_parts_02181228[] = {
    {0x0c, 0xf4, 0x0000, 0, 0xb0, 0x00, 0x18, 0x18},
    {0x0f, 0x0a, (short)0xf000, 1, 0xca, 0x0e, 0x08, 0x0c},
    {0x0d, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x78, 0x0c},
    {0x0f, 0x0a, (short)0xf000, 3, 0xda, 0x0e, 0x08, 0x0c},
    {0x0c, 0xf4, 0x0000, 4, 0xe0, 0x00, 0x18, 0x18},
    PARTS_END,
};

UnkMenuParts s_parts_021805b0[] = {
    {0x0f, 0x09, (short)0xf000, 0, 0x58, 0x54, 0x10, 0x10},
    PARTS_END,
};

THUMB void splitCommentLines(char* line1, char* line2, char* line3, char* message)
{
    UnkUtf8Iterator src;
    src.setText(message);
    UnkUtf8Iterator dst1;
    dst1.initBuffer(line1, 0x400);
    UnkUtf8Iterator dst2;
    dst2.initBuffer(line2, 0x400);
    UnkUtf8Iterator dst3;
    dst3.initBuffer(line3, 0x400);
    for (int i = 0; ; i++) {
        unsigned short c = src.getChar();
        src.nextChar();
        if (c == 0) {
            break;
        }
        dst1.putChar(c);
        if (i == 14) {
            break;
        }
    }
    for (int i = 0; ; i++) {
        unsigned short c = src.getChar();
        src.nextChar();
        if (c == 0) {
            break;
        }
        dst2.putChar(c);
        if (i == 14) {
            break;
        }
    }
    for (int i = 0; ; i++) {
        unsigned short c = src.getChar();
        src.nextChar();
        if (c == 0) {
            break;
        }
        dst3.putChar(c);
        if (i == 14) {
            break;
        }
    }
}

THUMB void drawSugorokuRootMenu()
{
    int param[3] = {(int)0xe0000375, 0, (int)0xe0000376};
    param[1] = twn::g_SugorokuInfo.diceCount_;
    int text[4] = {(int)0xe0000370, (int)0xe0000371, (int)0xe0000372, (int)0xe0000373};
    if (status::g_Game.language_ == Japanese) {
        drawMenuPartsColored(s_parts_02180ed2, param, data_02094dd4[0]);
    } else {
        drawMenuPartsColored(s_parts_02180b98, param, data_02094dd4[0]);
    }
    for (int i = 0; i < 4; i++) {
        drawMenuParts(s_parts_02180310, &text[i], 0, i * 16 + 8 + i * 8, data_02094dd4[0]);
    }
    drawMenuFrame(0, 0, 0x68, 0x80, 0x18);
}

UnkMenuParts s_parts_021813cc[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x80, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x0c, 0x1a, 0x10, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x18, 0x1a, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x32, 0x80, 0x10},
    {0x0c, 0xf0, 0x0000, 4, 0xd8, 0x04, 0x20, 0x20},
    PARTS_END,
};

UnkMenuParts s_parts_021806e4[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x08, 0x3a, 0xf0, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180770[] = {
    {0x0d, 0x05, (short)0xf000, 0, 0x38, 0x00, 0xa0, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180b6e[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x14, 0x80, 0x30, 0x0a},
    {0x0d, 0x0a, (short)0xf000, 1, 0x28, 0x80, 0x28, 0x0a},
    PARTS_END,
};

UnkMenuParts s_parts_02181030[] = {
    {0x14, 0xc0, 0x0000, -1, 0x70, 0x90, 0x20, 0x10},
    {0x14, 0xc0, 0x0000, -1, 0x70, 0xa8, 0x20, 0x10},
    {0x0d, 0x09, (short)0xf000, 0, 0x70, 0x92, 0x20, 0x10},
    {0x0d, 0x09, (short)0xf000, 1, 0x70, 0xaa, 0x20, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180bfa[] = {
    {0x0e, 0x08, (short)0xf000, 0, 0x10, 0x36, 0x80, 0x10},
    {0x0e, 0x08, (short)0xf000, 1, 0x40, 0x14, 0x38, 0x18},
    {0x0e, 0x08, (short)0xf000, 2, 0x78, 0x14, 0x10, 0x18},
    PARTS_END,
};

UnkMenuParts s_parts_02180850[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x00, 0x98, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0xa0, 0x00, 0x58, 0x10},
    PARTS_END,
};

THUMB void unkfunc_0217b9c4()
{
    MaterielMenuPlayerControl* control = MaterielMenuPlayerControl::getSingleton();
    int message = status::UseItem::getMenuMessage(MenuStatusInfo::getPlayerItemID(0, control->activeItem_ + control->activeItemPage_ * 6)) + 0x20000000;
    drawMenuPartsColored(s_parts_0218040c, &message, data_02094dd4[0]);
}

THUMB void drawJisanRootCommands()
{
    MaterielMenuPlayerControl::getSingleton();
    for (int i = 0; i < 6; i++) {
        int text = getMenuCommandText(2, i);
        drawMenuParts(s_parts_02180524, &text, (i % 2) * 0x60 + 0x44, (i / 2) * 0x18 + 0xc, data_02094dd4[0]);
    }
    drawMenuFrame(0x30, 0, 0xd0, 0x58, -1);
}

THUMB void drawMemberIconList(int page, int maxPage, int monster)
{
    int total;
    int script = MaterielMenu_WINDOW_MANAGER::getSingleton()->editMessageForScript_;
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    int count = partyCount;
    int list[8] = {-1};
    for (int i = 0; i < 8; i++) {
        list[i] = -1;
    }
    if (script == 1) {
        count = 0;
        if (monster != 0) {
            list[0] = 999;
            count = 1;
        }
        for (int i = 0; i < partyCount; i++) {
            if (MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
                list[count] = i;
                count++;
            }
        }
    }
    total = count;
    if (page == maxPage) {
        count -= page * 5;
    } else if (count > 5) {
        count = 5;
    }
    int drawCount = dss::clamp<int>(0, count, 5);
    for (int i = 0; i < drawCount; i++) {
        int index = i + page * 5;
        if (script == 1) {
            if (list[index] == 999) {
                drawCharaIcon(status::PlayerDataAll::playerData_[status::PlayerDataAll::getCtrlFromFriendMonsterIndex(monster)].getIconIndex(), i * 0x28 + 0x10, 0x70);
            } else {
                drawCharaIconWithCondition(list[index], i * 0x28 + 0x10, 0x70);
            }
        } else {
            drawCharaIconWithCondition(index, i * 0x28 + 0x10, 0x70);
        }
    }
    if (status::g_Menu.drawFlag_ == 0 && page == 0) {
        int carriage = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
        int number = 0;
        if (script == 1) {
            for (int i = 0; i < total; i++) {
                if (list[i] < carriage) {
                    number = list[i] + 1;
                    drawMenuParts(s_parts_02180690, &number, i * 0x28 + 0x10, 0x78, data_02094dd4[getActorConditionColor(list[i])]);
                }
            }
        } else {
            for (int i = 0; i < carriage; i++) {
                number = i + 1;
                drawMenuParts(s_parts_02180690, &number, i * 0x28 + 0x10, 0x78, data_02094dd4[getActorConditionColor(i)]);
            }
        }
    }
    if (maxPage > 0) {
        int param[5] = {0, (int)"\xff\xfe\xa7\x24", 0, 0xd, 0};
        param[0] = page + 1;
        param[2] = maxPage + 1;
        drawMenuParts(s_parts_02181102, param, 0xd0, 0x78, data_02094dd4[0]);
    }
    drawMenuFrame(0, 0x70, 0x100, 0x30, -1);
}

THUMB void drawMemberIconGrid(int page, int maxPage, short* list, int total)
{
    int count = total - page * 12;
    count = dss::clamp<int>(0, count, 12);
    for (int i = 0; i < count; i++) {
        int index = i + page * 12;
        int x = (i % 6) * 0x28 + 8;
        int y = (i / 6) * 0x28 + 0x20;
        if (list[index] == -1) {
            drawCharaIconWithCondition(-1, x, y);
        } else {
            drawCharaIconWithCondition(list[index], x, y);
        }
    }
    if (maxPage > 0) {
        int param[5] = {0xc, 0xd, 0, (int)"\xff\xfe\xa7\x24", 0};
        param[2] = page + 1;
        param[4] = maxPage + 1;
        drawMenuParts(s_parts_021812d0, param, 0x48, 0x80, data_02094dd4[0]);
    }
    drawMenuFrame(0, 0x20, 0x100, 0x80, -1);
}

UnkMenuParts s_parts_021806c8[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x00, 0x00, 0x10, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_0218157e[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x0a, 0x00, 0x0a, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 1, 0x18, 0x00, 0x20, 0x0a},
    {0x0d, 0x0b, (short)0xf000, 2, 0x00, 0x00, 0x0a, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 3, 0x02, 0x00, 0x0a, 0x0a},
    {0x0d, 0x08, (short)0xf000, 4, 0x48, 0x00, 0x0a, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 5, 0x48, 0x00, 0x18, 0x0a},
    PARTS_END,
};

THUMB void drawActiveCharaProfile()
{
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    if (chara == -1) {
        return;
    }
    setMenuDrawOffset(0, 0);
    int sex = MenuStatusInfo::getPlayerSex(chara);
    int param[16] = {
        0, 0, (int)0xe0000113, (int)"\xff\xfe\xa8\x24", (int)0xe0000321, (int)0xe0000016, (int)"\xff\xfe\xa8\x24", 0,
        (int)0xe0000014, 0, (int)"\xff\xfe\xa7\x24", 0, (int)0xe0000015, 0, (int)"\xff\xfe\xa7\x24", 0,
    };
    param[0] = MenuStatusInfo::getPlayerIndex(chara) + 0x50000000;
    param[1] = MenuDataCommon::getPlayerJob(chara);
    param[7] = MenuDataCommon::getStatus(chara, MenuDataCommon::LEVEL, false);
    param[9] = MenuDataCommon::getStatus(chara, MenuDataCommon::NOWHP, false);
    param[11] = MenuDataCommon::getStatus(chara, MenuDataCommon::MAXHP, false);
    param[13] = MenuDataCommon::getStatus(chara, MenuDataCommon::NOWMP, false);
    param[15] = MenuDataCommon::getStatus(chara, MenuDataCommon::MAXMP, false);
    if (sex == 0x114) {
        param[4] = (int)0xe0000114;
    }
    if (sex == 0x115) {
        param[4] = (int)0xe0000115;
    }
    drawMenuPartsColored(s_parts_02181ab0, param, data_02094dd4[getActorConditionColor(chara)]);
    drawMenuFrame(0, 0x60, 0x98, 0x60, 0x78);
}

UnkMenuParts s_parts_02180498[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x10, 0x58, 0x0c},
    PARTS_END,
};

UnkMenuParts s_parts_02180e62[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x48, 0x1c, 0x20, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x6a, 0x1c, 0x08, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x74, 0x1c, 0x78, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02180a72[] = {
    {0x0c, 0xf0, 0x0000, 0, 0x00, 0xa0, 0x20, 0x20},
    {0x0d, 0x08, (short)0xf000, 1, 0x28, 0xaa, 0x50, 0x10},
    PARTS_END,
};

UnkMenuParts s_parts_02181076[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x00, 0x40, 0x20},
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x06, 0x30, 0x10},
    {0x07, 0x00, (short)0xf000, 17, 0x08, 0x00, 0x30, 0x08},
    {0x11, 0x00, 0x0000, 1, 0x00, 0x10, 0x00, 0x00},
    PARTS_END,
};

UnkMenuParts s_parts_0218151c[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x0a, 0x44, 0x38, 0x0a},
    {0x0d, 0x08, (short)0xf000, 4, 0x3c, 0x44, 0x0a, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x1a, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0x0a, 0x54, 0x38, 0x0a},
    {0x0d, 0x08, (short)0xf000, 4, 0x3c, 0x54, 0x0a, 0x0a},
    {0x0f, 0x0b, (short)0xf000, 3, 0x00, 0x00, 0x1a, 0x0a},
    PARTS_END,
};

THUMB void drawLuidaRootCommands()
{
    int text = 0;
    for (int i = 0; i < 4; i++) {
        text = getMenuCommandText(3, i);
        drawMenuParts(s_parts_021806ac, &text, 0, i * 16 + 8 + i * 8, data_02094dd4[0]);
    }
    drawMenuFrame(0x90, 0, 0x70, 0x70, -1);
}

// not in the ROM (dead-stripped), keeps the unused parts lists of this file and its const local
THUMB void unkfunc_unused_0218078c()
{
    const int unk = 0;
    drawMenuPartsPlain(s_parts_0218078c, 0);
    drawMenuPartsPlain(s_parts_02180a9c, 0);
    drawMenuPartsPlain(s_parts_02180b1a, 0);
    drawMenuPartsPlain(s_parts_02180c32, 0);
    drawMenuPartsPlain(s_parts_02180c6a, 0);
    drawMenuPartsPlain(s_parts_0218118e, 0);
    drawMenuPartsPlain(s_parts_02181324, 0);
}
