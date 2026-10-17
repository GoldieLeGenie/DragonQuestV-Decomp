#pragma ipa file
#include "ov019/townmenu/UnkTownMenuDraw.hpp"
#include "ov019/townmenu/UnkTownMenuDrawParts.hpp"
#include "ov019/townmenu/TownMenuPlayerControl.hpp"
#include "ov019/townmenu/town_item/TownMenuItemUseManager.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/menu/MenuDataCommon.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseItem.hpp"

using menu::MenuDataCommon;
using menu::MenuStatusInfo;
using menu::TownMenuPlayerControl;

inline short TownMenuPlayerControl::getActiveItem()
{
    return activeItem_;
}

inline char TownMenuPlayerControl::getActiveItemPage()
{
    return activeItemPage_;
}

static const UnkTownMenuDrawPair s_pairs_0217ddb8[3] = {{2, -1}, {1, -1}, {(int)0xe00001ae, (int)0xe00001af}};

THUMB void unkfunc_02172ef0(int messageOpen)
{
    if (messageOpen == 0) {
        unkfunc_021715fc(-1, -1);
        unkfunc_021715b4(0, 0, 1);
    }
    unkfunc_0201b158();
    unkfunc_0201b1cc(-1, -1, 0);
}

THUMB void unkfunc_02172f1c(int messageOpen)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    if (messageOpen == 0) {
        unkfunc_02173948(activeChara, 0, 1, 0);
        unkfunc_021729dc(1);
        unkfunc_02173a58(1, 0);
    }
    unkfunc_0201b158();
    if (messageOpen == 0) {
        unkfunc_02173c50(activeChara, 0);
        unkfunc_0201b0f8(0, 0x50, 0x100, 0x70, -1);
    }
}

THUMB void unkfunc_02172f6c(int messageOpen, int page)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int activeItem = TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll();
    int activeFukuro = TownMenuPlayerControl::getSingleton()->activeFukuro_;
    int itemID;
    if (activeFukuro == 1) {
        itemID = MenuStatusInfo::getFukuroItemID(activeItem, 0);
    } else {
        itemID = MenuStatusInfo::getPlayerItemID(activeChara, activeItem);
    }
    if (messageOpen == 0) {
        unkfunc_02173948(activeChara, 0, 1, 0);
        unkfunc_02173c80(activeChara, page, 0);
        unkfunc_0201b0f8(0, 0, 0x100, 0xa0, 0x70);
        unkfunc_02171b70(itemID, 0, 0);
        if (TownMenuPlayerControl::getSingleton()->activeFukuro_ != 0) {
            if (MenuStatusInfo::getFukuroItemCount() > 6) {
                unkfunc_02171ad4(0xb8, MenuStatusInfo::getFukuroMaxPage() - 1, page, 1);
            }
        } else if (MenuStatusInfo::getPlayerItemCount(activeChara) > 6) {
            unkfunc_02171ad4(0xd0, 1, page, 0);
        }
    }
    unkfunc_0201b158();
    unkfunc_0201b0f8(0, 0x78, 0xb0, 0x48, 0x90);
    switch (status::UseItem::getEquipItemType(itemID)) {
        case ITEM_WEAPON:
        case ITEM_ARMOR:
        case ITEM_SHIELD:
        case ITEM_HELMET:
        case ITEM_ACCESSORY:
            unkfunc_02171c0c(activeChara, itemID, 0, 0, 0, 0);
            break;
        case ITEM_OTHER:
            break;
        default:
            if (activeFukuro == 0 && menu::TownMenuItemUseManager::isEquipSpecialItem(itemID) == true) {
                unkfunc_02171c0c(activeChara, itemID, 0, 0, 0, 0);
            } else {
                unkfunc_02171bd4(itemID);
            }
            break;
    }
}

THUMB void unkfunc_02173098(int messageOpen, int a1, int itemID, int page)
{
    int x;
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    if (messageOpen == 0 && a1 == 0) {
        x = (TownMenuPlayerControl::getSingleton()->activeItem_ % 2) * 0x78 + 0x14;
        int y = (TownMenuPlayerControl::getSingleton()->activeItem_ / 2) * 0x20 + 0x14;
        int commandFlag = MenuStatusInfo::getPlayerItemCommandFlag(activeChara, TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll());
        if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
            commandFlag = MenuStatusInfo::getFukuroItemCommandFlag();
        }
        unkfunc_02173948(activeChara, 0, 1, 0);
        unkfunc_02171d90(commandFlag);
        unkfunc_0201b0f8(0, 0, 0x100, 0xa0, 0x68);
        unkfunc_02173c80(activeChara, page, 0);
        unkfunc_0217283c(x, y + 4);
    }
    unkfunc_0201b158();
    if (messageOpen == 0 && a1 == 0) {
        unkfunc_0201b0f8(0, 0x78, 0xb0, 0x48, 0x90);
        switch (status::UseItem::getEquipItemType(itemID)) {
            case ITEM_WEAPON:
            case ITEM_ARMOR:
            case ITEM_SHIELD:
            case ITEM_HELMET:
            case ITEM_ACCESSORY:
                unkfunc_02171c0c(activeChara, itemID, 0, 0, 0, 0);
                return;
            default:
                unkfunc_02171bd4(itemID);
                break;
        }
    }
}

THUMB void unkfunc_02173194(int messageOpen, int itemID, int page)
{
    if (messageOpen == 0) {
        unkfunc_02173948(TownMenuPlayerControl::getSingleton()->targetChara_, 0, 1, 1);
        unkfunc_0201b0f8(0, 0, 0x100, 0xa0, -1);
        unkfunc_02173e7c(page);
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    }
    unkfunc_0201b158();
    if (messageOpen == 0) {
        unkfunc_02171bd4(itemID);
        unkfunc_0201b0f8(0, 0x78, 0xb0, 0x48, 0x90);
    }
}

THUMB void unkfunc_021731f8(int messageOpen)
{
    short itemID;
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int targetChara = TownMenuPlayerControl::getSingleton()->targetChara_;
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 1) {
        int activeItem = TownMenuPlayerControl::getSingleton()->getActiveItem();
        itemID = MenuStatusInfo::getFukuroItemID(activeItem, TownMenuPlayerControl::getSingleton()->getActiveItemPage());
    } else {
        itemID = MenuStatusInfo::getPlayerItemID(activeChara, TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll());
    }
    if (messageOpen == 0) {
        unkfunc_02173948(activeChara, 0, 0, 0);
        unkfunc_0201b0f8(0x88, 0xa0, 0x40, 0x20, -1);
        unkfunc_02171914(targetChara);
        unkfunc_02172850(targetChara, itemID, 0);
        unkfunc_02173a58(1, 0);
        unkfunc_0201b0f8(0, 0, 0x100, 0x48, 0x28);
    }
    unkfunc_02173c50(targetChara, 1);
    unkfunc_0201b0f8(0, 0x50, 0x100, 0x70, -1);
    unkfunc_0201b158();
}

THUMB void unkfunc_021732b0(int messageOpen)
{
    short itemID;
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int targetChara = TownMenuPlayerControl::getSingleton()->targetChara_;
    int targetItemPage = TownMenuPlayerControl::getSingleton()->targetItemPage_;
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_) {
        int activeItem = TownMenuPlayerControl::getSingleton()->getActiveItem();
        itemID = MenuStatusInfo::getFukuroItemID(activeItem, TownMenuPlayerControl::getSingleton()->getActiveItemPage());
    } else {
        itemID = MenuStatusInfo::getPlayerItemID(activeChara, TownMenuPlayerControl::getSingleton()->getActiveItemIndexToAll());
    }
    if (messageOpen == 0) {
        unkfunc_02173948(activeChara, 0, 0, 0);
        unkfunc_0201b0f8(0x88, 0xa0, 0x40, 0x20, -1);
        unkfunc_02171914(targetChara);
        unkfunc_0201b0f8(0, 0, 0x100, 0xa0, 0x70);
        unkfunc_02173c80(targetChara, targetItemPage, 1);
        unkfunc_02171b70(0, 0, 1);
        if (MenuStatusInfo::getPlayerItemCount(targetChara) + 1 > 6) {
            unkfunc_02171ad4(0xd0, 1, TownMenuPlayerControl::getSingleton()->targetItemPage_, 0);
        }
    }
    unkfunc_02172850(targetChara, itemID, 1);
    unkfunc_0201b0f8(0, 8, 0x100, 0x48, 0x30);
    unkfunc_02173c50(targetChara, 1);
    unkfunc_0201b0f8(0, 0x50, 0x100, 0x70, -1);
}

THUMB void unkfunc_021733b0(int messageOpen)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int mp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::NOWMP, false);
    int maxMp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::MAXMP, false);
    if (messageOpen == 0) {
        unkfunc_0217399c(activeChara);
        unkfunc_02173a58(0, 0);
        unkfunc_021721d4(activeChara, maxMp, mp);
        unkfunc_021729dc(0);
        unkfunc_02172228(activeChara);
    }
    unkfunc_0201b158();
}

THUMB void unkfunc_02173400(int messageOpen)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int magicID = MenuStatusInfo::getPlayerActionID(activeChara, TownMenuPlayerControl::getSingleton()->activeMagic_, MenuStatusInfo::USE_TOWN);
    int mp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::NOWMP, false);
    int useMp = status::UseAction::getUseMp(magicID);
    if (messageOpen == 0) {
        unkfunc_0217399c(activeChara);
        unkfunc_021721d4(activeChara, mp, useMp);
        unkfunc_02173e94(activeChara);
        unkfunc_02171b70(magicID, 1, 0);
        unkfunc_0201b0f8(0, 0, 0x100, 0xa0, 0x70);
        unkfunc_02172a60(0);
    }
    unkfunc_0201b158();
}

THUMB void unkfunc_02173478(int messageOpen, int page)
{
    if (messageOpen == 0) {
        int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
        int mp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::NOWMP, false);
        int useMp = status::UseAction::getUseMp(0x81);
        unkfunc_021715fc(1, -1);
        unkfunc_021715b4(0x40, 0xa0, 0);
        unkfunc_021721d4(activeChara, mp, useMp);
        unkfunc_0201b0f8(0, 0xa0, 0x40, 0x20, -1);
        unkfunc_02171820(activeChara, 0, 0, 0);
        unkfunc_0201b0f8(0, 0, 0x100, 0xa0, 0x70);
        unkfunc_021722d8(page);
        unkfunc_02172a60(1);
    }
    unkfunc_0201b158();
}

THUMB void unkfunc_021734f8(int messageOpen, int page)
{
    if (messageOpen == 0) {
        int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
        int magicID = MenuStatusInfo::getPlayerActionID(activeChara, TownMenuPlayerControl::getSingleton()->activeMagic_, MenuStatusInfo::USE_TOWN);
        int mp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::NOWMP, false);
        int useMp = status::UseAction::getUseMp(magicID);
        unkfunc_0217399c(activeChara);
        unkfunc_021721d4(activeChara, mp, useMp);
        unkfunc_0201b0f8(0, 0, 0x100, 0xa0, -1);
        unkfunc_02173e24(page);
    }
    unkfunc_0201b158();
}

THUMB void unkfunc_02173560(int page)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    unkfunc_021739d8(activeChara, page);
    unkfunc_0201b4d4(activeChara, 1, 0);
    unkfunc_0201b6b4(activeChara, 0);
    unkfunc_0201b7dc(activeChara, 0);
}

THUMB void unkfunc_02173590(int page)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    unkfunc_021739d8(activeChara, page);
    unkfunc_0201ba48(activeChara, 0);
    unkfunc_0201ba48(activeChara, 1);
}

THUMB void unkfunc_021735b8(int chara, int flag, int page)
{
    unkfunc_021739d8(chara, page);
    if (flag == 1) {
        unkfunc_0201bcc8(0);
    } else {
        unkfunc_0201be24(0);
    }
}

THUMB void unkfunc_021735d8(int page)
{
    unkfunc_021739d8(-2, page);
    unkfunc_0201bbb4();
}

THUMB void unkfunc_021735ec(int messageOpen)
{
    if (messageOpen == 0) {
        unkfunc_021715fc(5, -1);
        unkfunc_021715b4(0x40, 0xa0, 0);
        unkfunc_02173efc();
    }
    unkfunc_0201b158();
}

THUMB void unkfunc_02173610(int messageOpen, int mode)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (messageOpen == 0) {
        unkfunc_021715fc(5, 0);
        if (mode == 1) {
            unkfunc_0217269c(2);
            unkfunc_021715b4(0, 0xa0, 0);
            unkfunc_0201b0f8(0x98, 0xa0, 0x40, 0x20, -1);
            if (activeChara == count) {
                unkfunc_02171820(-2, 1, 0, 0x10);
            } else {
                unkfunc_02171820(activeChara, 1, 0, 0x10);
            }
            char list[10] = {0};
            for (int i = 0; i < 10; i++) {
                list[i] = 0;
            }
            char n = 0;
            for (char i = 0; i < count; i++) {
                if (!MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_BATTLE_NPC)) {
                    list[n] = i;
                    n++;
                }
            }
            list[n] = -1;
            unkfunc_02173fa4(list, 2);
        } else {
            unkfunc_0217269c(3);
            unkfunc_021715b4(0, 0xa0, 0);
            unkfunc_02173f68();
        }
    }
    unkfunc_0201b158();
    if (activeChara != count && mode == 1) {
        unkfunc_02173c50(activeChara, 0);
        unkfunc_0201b0f8(0, 0x50, 0x100, 0x70, -1);
    }
}

THUMB void unkfunc_02173720(char* playerList, int chara)
{
    unkfunc_021715fc(5, 0);
    unkfunc_0217269c(1);
    unkfunc_021715b4(0, 0xa0, 0);
    unkfunc_0201b0f8(0x98, 0xa0, 0x40, 0x20, -1);
    unkfunc_02171820(chara, 1, 0, 0x10);
    unkfunc_02173fa4(playerList, -1);
    unkfunc_02174124(playerList);
}

THUMB void unkfunc_02173770(char* playerList, int chara, int active)
{
    int x = (active % 5) * 0x28 + 0x14;
    int y = (active / 5) * 0x28 + 0x64;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (MenuStatusInfo::getPlayerSortIndex(1) != -1) {
        count--;
    }
    if (count < 5) {
        y = 0x8c;
    }
    unkfunc_02172498();
    unkfunc_0201b0f8(0x10, 0, 0xd0, 0x48, -1);
    unkfunc_0217283c(x, y);
    unkfunc_02173720(playerList, chara);
}

THUMB void unkfunc_021737e4(char* allocation, char* list, int active, int count)
{
    unkfunc_021724f4(allocation, list, count);
    unkfunc_0201b0f8(0, 0x68, 0xe0, 0x58, -1);
    unkfunc_021725bc(allocation);
    unkfunc_0201b0f8(0, 0, 0x90, 0x68, -1);
    if (list[active] != -1) {
        unkfunc_0201b2a8(list[active], 0);
        if (MenuStatusInfo::isCarriageEnable()) {
            unkfunc_0201ba48(list[active], 1);
            unkfunc_0201b0f8(0, 0, 0x100, 0xc0, 0x28);
            return;
        }
        unkfunc_0201b158();
        return;
    }
    unkfunc_02172804();
    unkfunc_0201b158();
}

THUMB void unkfunc_0217386c(int messageOpen)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    if (messageOpen == 0) {
        unkfunc_02173a18(activeChara);
        unkfunc_02173a58(0, 1);
    }
    unkfunc_0201b7dc(activeChara, 1);
}

THUMB void unkfunc_02173894(short* itemPosList, int itemCount, int itemType, int itemListActive)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int page = TownMenuPlayerControl::getSingleton()->activeItemPage_;
    int activeItem = TownMenuPlayerControl::getSingleton()->activeItem_;
    unkfunc_02173a18(activeChara);
    unkfunc_02174170(activeChara, itemPosList, itemCount, page);
    if (itemCount > 6) {
        unkfunc_02171b28(0x50, (itemCount - 1) / 6, page);
    }
    unkfunc_021726d0(itemType);
    unkfunc_0201b0f8(0, 0, 0x100, 0xa0, -1);
    if (activeItem == -1) {
        unkfunc_02174248(activeChara, -1, itemType, itemListActive);
    } else {
        int index = activeItem;
        index += page * 6;
        unkfunc_02174248(activeChara, itemPosList[index], itemType, itemListActive);
    }
    unkfunc_0201b0f8(0, 0x78, 0x68, 0x48, 0x90);
    unkfunc_0201b7dc(activeChara, 1);
}

THUMB void unkfunc_02173940(int type)
{
    unkfunc_02172ad0(type);
}

THUMB void unkfunc_02173948(int chara, int a, int b, int c)
{
    unkfunc_021715fc(s_pairs_0217ddb8[0].first, s_pairs_0217ddb8[0].second);
    unkfunc_021715b4(0x40, 0xa0, a);
    if (b != 0) {
        unkfunc_0201b0f8(0x88, 0xa0, 0x40, 0x20, -1);
    } else {
        unkfunc_0201b0f8(0, 0xa0, 0x40, 0x20, -1);
    }
    unkfunc_02171820(chara, b, c, 0);
}

THUMB void unkfunc_0217399c(int chara)
{
    unkfunc_021715fc(s_pairs_0217ddb8[1].first, s_pairs_0217ddb8[1].second);
    unkfunc_021715b4(0x40, 0xa0, 0);
    unkfunc_0201b0f8(0, 0xa0, 0x40, 0x20, -1);
    unkfunc_02171820(chara, 0, 0, 0);
}

THUMB void unkfunc_021739d8(int chara, int page)
{
    unkfunc_021715fc(4, -1);
    unkfunc_021715b4(0x40, 0xa0, 0);
    unkfunc_0201b0f8(0x88, 0xa0, 0x40, 0x20, -1);
    unkfunc_02171820(chara, 1, 0, 0);
    unkfunc_02173ac8(page);
}

THUMB void unkfunc_02173a18(int chara)
{
    unkfunc_021715fc(5, 0);
    unkfunc_021715b4(0, 0xa0, 0);
    unkfunc_0217269c(0);
    unkfunc_0201b0f8(0x98, 0xa0, 0x40, 0x20, -1);
    unkfunc_02171820(chara, 1, 0, 0x10);
}

THUMB void unkfunc_02173a58(int a, int b)
{
    int count;
    if (a == 1) {
        count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1;
    } else {
        count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    }
    unkfunc_02171eb4(a, b);
    if (count < 5) {
        unkfunc_0201b0f8(0, 0x70, 0xb8, 0x30, -1);
    } else if (count == 5) {
        unkfunc_0201b0f8(0, 0x70, 0xe0, 0x30, -1);
    } else {
        unkfunc_0201b0f8(0, 0x48, 0xe0, 0x58, -1);
    }
}

THUMB void unkfunc_02173ac8(int page)
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (page == 0) {
        if (count > 4) {
            count = 5;
            unkfunc_02171ad4(0xd0, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) / count, page, 0);
        }
        for (int i = 0; i < count; i++) {
            unkfunc_021716f0(i, i * 0x28 + 0x10, 0x70);
        }
        int n = 0;
        for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT); i++) {
            if (!MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_NORMAL_NPC)) {
                unkfunc_02172390(i + 1, n * 0x28 + 8, 0x78, i);
                n++;
            }
        }
        if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) < 4) {
            int x = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) * 0x28 + 0x10;
            unkfunc_021716f0(-2, x, 0x70);
            unkfunc_0201b0f8(0, 0x70, 0xb8, 0x30, -1);
            return;
        }
        if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) == 4) {
            unkfunc_021716f0(-2, 0xb0, 0x70);
            unkfunc_0201b0f8(0, 0x70, 0xe0, 0x30, -1);
            return;
        }
        unkfunc_0201b0f8(0, 0x70, 0x100, 0x30, -1);
        return;
    }
    if (page == 1) {
        if (count > 10) {
            count = 10;
        }
        for (int i = 5; i < count; i++) {
            unkfunc_021716f0(i, (i - page * 5) * 0x28 + 0x10, 0x70);
        }
        if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) < 10) {
            int x = (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) - 5) * 0x28 + 0x10;
            unkfunc_021716f0(-2, x, 0x70);
        }
    } else {
        unkfunc_021716f0(-2, 0x10, 0x70);
    }
    unkfunc_02171ad4(0xd0, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) / 5, page, 0);
    unkfunc_0201b0f8(0, 0x70, 0x100, 0x30, -1);
}

THUMB void unkfunc_02173c50(int chara, int flag)
{
    if ((flag != 0 && TownMenuPlayerControl::getSingleton()->targetFukuro_ != 0) || (flag == 0 && TownMenuPlayerControl::getSingleton()->activeFukuro_ != 0)) {
        unkfunc_0217178c();
    } else {
        unkfunc_021716f8(chara);
    }
}

THUMB void unkfunc_02173c80(int chara, int page, int flag)
{
    TownMenuPlayerControl::getSingleton();
    if (TownMenuPlayerControl::getSingleton()->activeFukuro_ == 0) {
        TownMenuPlayerControl::getSingleton();
    }
    if ((flag != 0 && TownMenuPlayerControl::getSingleton()->targetFukuro_ != 0) || (flag == 0 && TownMenuPlayerControl::getSingleton()->activeFukuro_ != 0)) {
        int count = MenuStatusInfo::getFukuroItemCountInPage(page);
        for (int i = 0; i < count; i++) {
            int itemID = MenuStatusInfo::getFukuroItemID(i, page);
            int index = MenuStatusInfo::getFukuroItemIndexToAll(i, page);
            unkfunc_02171a30(itemID, index, (i % 2 + 1) * 16 + (i % 2) * 0x68 + 4, (i / 2) * 8 + (i / 2) * 0x18 + 4);
        }
    } else {
        int count = MenuStatusInfo::getPlayerItemCount(chara) - page * 6;
        if (count > 6) {
            count = 6;
        }
        for (int i = 0; i < count; i++) {
            if (page == 0) {
                int itemID = MenuStatusInfo::getPlayerItemID(chara, i);
                unkfunc_021719e0(itemID, (i % 2 + 1) * 16 + (i % 2) * 0x68 + 4, (i / 2) * 8 + (i / 2) * 0x18 + 4);
                if (MenuStatusInfo::isPlayerEquipItemIndex(chara, i) == true) {
                    unkfunc_02171a88(i);
                }
            } else {
                int itemID = MenuStatusInfo::getPlayerItemID(chara, i + 6);
                unkfunc_021719e0(itemID, (i % 2 + 1) * 16 + (i % 2) * 0x68 + 4, (i / 2) * 8 + (i / 2) * 0x18 + 4);
                if (MenuStatusInfo::isPlayerEquipItemIndex(chara, i + page * 6) == true) {
                    unkfunc_02171a88(i);
                }
            }
        }
        if (!gTownMenu_MESSAGE.isOpen() && flag != 0 && count < 6) {
            unkfunc_021719e0(-1, (count % 2 + 1) * 16 + (count % 2) * 0x68 + 4, (count / 2) * 8 + (count / 2) * 0x18 + 4);
        }
    }
}

THUMB void unkfunc_02173e24(int page)
{
    int i;
    int end = (page + 1) * 4;
    if (end >= MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        end = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    }
    for (i = page * 4; i < end; i++) {
        unkfunc_02172094(i, i - page * 4, page);
    }
    if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) > 4) {
        unkfunc_02171b28(0x50, (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) - 1) / 4, page);
    }
}

THUMB void unkfunc_02173e7c(int page)
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    unkfunc_02173e24(page);
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
}

THUMB void unkfunc_02173e94(int chara)
{
    int count = MenuStatusInfo::getPlayerActionCount(chara, MenuStatusInfo::USE_TOWN);
    int n = 0;
    for (int i = 0; i < count; i++) {
        int magicID = MenuStatusInfo::getPlayerActionID(chara, i);
        if (MenuStatusInfo::isPlayerActionUseType(magicID, MenuStatusInfo::USE_TOWN) == true) {
            int word = MenuStatusInfo::getWordDBIndex(magicID);
            unkfunc_021722a8((n % 2) * 0x78 + 4, (n / 2) * 16 + 0xe + (n / 2) * 8, word + 0x70000000, chara);
            n++;
        }
    }
}

THUMB void unkfunc_02173efc()
{
    int text[8] = {(int)0xe000015e, (int)0xe000015f, (int)0xe0000160, (int)0xe0000161, (int)0xe0000162, (int)0xe0000163, (int)0xe00001b5, (int)0xe0000165};
    for (int i = 0; i < 8; i++) {
        unkfunc_02172414((i % 2) * 0x50 + 0x20 + (i % 2) * 16, (i / 2) * 16 + 0x3c + (i / 2) * 8, text[i]);
    }
    unkfunc_0201b0f8(0x10, 0x30, 0xd0, 0x70, -1);
}

THUMB void unkfunc_02173f68()
{
    UnkTownMenuDrawPair text = s_pairs_0217ddb8[2];
    unkfunc_02172414(0x10, 0x88, text.first);
    unkfunc_02172414(0x70, 0x88, text.second);
    unkfunc_0201b0f8(0, 0x80, 0xd0, 0x20, -1);
}

THUMB void unkfunc_02173fa4(char* list, int mode)
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int outCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (mode != 2 && MenuStatusInfo::getPlayerSortIndex(1) != -1) {
        count--;
    }
    for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL); i++) {
        if (!MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_PLAYER)) {
            count--;
        }
    }
    int y = 0x48;
    int i = 0;
    if (count < 5) {
        y = 0x70;
    }
    if (count < 5) {
        unkfunc_0201b0f8(0, 0x70, 0xe0, 0x30, -1);
    } else {
        unkfunc_0201b0f8(0, 0x48, 0xe0, 0x58, -1);
    }
    char* p;
    for (; (p = &list[i], list[i] != -1) && i < 5; i++) {
        unkfunc_021716f0(list[i], i * 0x20 + 0x10 + i * 8, y);
    }
    int n = 0;
    y += 8;
    for (int j = 0; j < outCount; j++) {
        if ((mode == 2 || MenuStatusInfo::getPlayerIndex(j) != 1) && MenuStatusInfo::isPlayerType(j, MenuStatusInfo::TYPE_PLAYER)) {
            int x = n * 0x20 + 0x10 + n * 8;
            unkfunc_02172390(j + 1, x - 8, y, list[n]);
            n++;
        }
    }
    if (*p == -1 || i < 5) {
        int x = i * 0x20 + 0x10 + i * 8;
        if (i == 5) {
            x = 0x10;
        }
        unkfunc_021716f0(-2, x, 0x70);
        return;
    }
    for (; list[i] != -1 && i < 9; i++) {
        unkfunc_021716f0(list[i], (i - 5) * 0x20 + 0x10 + (i - 5) * 8, 0x70);
    }
    unkfunc_021716f0(-2, (i - 5) * 0x20 + 0x10 + (i - 5) * 8, 0x70);
}

THUMB void unkfunc_02174124(char* list)
{
    int i = 0;
    unkfunc_021723e0(i, 0xe, 0xe00001aa);
    if (list[i] != -1) {
        int y = 0x30;
        do {
            unkfunc_0217243c(list[i], 0, y);
            i++;
            y += 0x10;
        } while (list[i] != -1);
    }
    unkfunc_0201b0f8(0, 0, 0x100, 0xc0, 0x20);
}

THUMB void unkfunc_02174170(int chara, short* itemPosList, int itemCount, int page)
{
    if (page == 0) {
        itemCount = dss::clamp<int>(0, itemCount, 6);
        for (int i = 0; i < itemCount; i++) {
            int itemID = MenuStatusInfo::getPlayerItemID(chara, itemPosList[i]);
            unkfunc_021719e0(itemID, (i % 2 + 1) * 16 + 4 + (i % 2) * 0x68, (i / 2) * 8 + (i / 2) * 0x18 + 4);
            if (MenuStatusInfo::isPlayerEquipItemIndex(chara, itemPosList[i]) == true) {
                unkfunc_02171a88(i);
            }
        }
    } else {
        for (int i = 6; i < itemCount; i++) {
            int itemID = MenuStatusInfo::getPlayerItemID(chara, itemPosList[i]);
            unkfunc_021719e0(itemID, ((i - 6) % 2 + 1) * 16 + 4 + ((i - 6) % 2) * 0x68, ((i - 6) / 2) * 8 + ((i - 6) / 2) * 0x18 + 4);
            if (MenuStatusInfo::isPlayerEquipItemIndex(chara, itemPosList[i]) == true) {
                unkfunc_02171a88(i - 6);
            }
        }
    }
}

THUMB void unkfunc_02174248(int chara, int activeItem, int itemType, int itemListActive)
{
    if (itemType == -1) {
        return;
    }
    if (activeItem == -1) {
        unkfunc_02171c0c(chara, -1, itemType, 0, 1, itemListActive);
        return;
    }
    unkfunc_02171c0c(chara, MenuStatusInfo::getPlayerItemID(chara, activeItem), itemType, 0, 1, itemListActive);
}

THUMB void unkfunc_0217428c()
{
    unkfunc_02172728();
    unkfunc_021715fc(5, -1);
    unkfunc_021715b4(0x40, 0xa0, 0);
    unkfunc_0201b158();
    unkfunc_0201b1cc(-1, -1, 0);
}
