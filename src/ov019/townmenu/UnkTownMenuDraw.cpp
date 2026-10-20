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

THUMB void drawRootMenuScreen(int messageOpen)
{
    if (messageOpen == 0) {
        drawRootMenuCommands(-1, -1);
        drawRootMenuButtonFrames(0, 0, 1);
    }
    drawPartyStatusWindows();
    drawMoneyWindow(-1, -1, 0);
}

THUMB void drawItemCharaSelectScreen(int messageOpen)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    if (messageOpen == 0) {
        drawItemMenuHeader(activeChara, 0, 1, 0);
        drawChooseCharaPrompt(1);
        drawCharaSelectWindow(1, 0);
    }
    drawPartyStatusWindows();
    if (messageOpen == 0) {
        drawCharaItemList(activeChara, 0);
        drawMenuFrame(0, 0x50, 0x100, 0x70, -1);
    }
}

THUMB void drawItemSelectScreen(int messageOpen, int page)
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
        drawItemMenuHeader(activeChara, 0, 1, 0);
        drawItemListPage(activeChara, page, 0);
        drawMenuFrame(0, 0, 0x100, 0xa0, 0x70);
        drawMenuDescription(itemID, 0, 0);
        if (TownMenuPlayerControl::getSingleton()->activeFukuro_ != 0) {
            if (MenuStatusInfo::getFukuroItemCount() > 6) {
                drawPageIndicator(0xb8, MenuStatusInfo::getFukuroMaxPage() - 1, page, 1);
            }
        } else if (MenuStatusInfo::getPlayerItemCount(activeChara) > 6) {
            drawPageIndicator(0xd0, 1, page, 0);
        }
    }
    drawPartyStatusWindows();
    drawMenuFrame(0, 0x78, 0xb0, 0x48, 0x90);
    switch (status::UseItem::getEquipItemType(itemID)) {
        case ITEM_WEAPON:
        case ITEM_ARMOR:
        case ITEM_SHIELD:
        case ITEM_HELMET:
        case ITEM_ACCESSORY:
            drawEquipCompareWindow(activeChara, itemID, 0, 0, 0, 0);
            break;
        case ITEM_OTHER:
            break;
        default:
            if (activeFukuro == 0 && menu::TownMenuItemUseManager::isEquipSpecialItem(itemID) == true) {
                drawEquipCompareWindow(activeChara, itemID, 0, 0, 0, 0);
            } else {
                drawItemUsageInfo(itemID);
            }
            break;
    }
}

THUMB void drawItemCommandScreen(int messageOpen, int a1, int itemID, int page)
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
        drawItemMenuHeader(activeChara, 0, 1, 0);
        drawItemUseCommands(commandFlag);
        drawMenuFrame(0, 0, 0x100, 0xa0, 0x68);
        drawItemListPage(activeChara, page, 0);
        drawTownCommandCursor(x, y + 4);
    }
    drawPartyStatusWindows();
    if (messageOpen == 0 && a1 == 0) {
        drawMenuFrame(0, 0x78, 0xb0, 0x48, 0x90);
        switch (status::UseItem::getEquipItemType(itemID)) {
            case ITEM_WEAPON:
            case ITEM_ARMOR:
            case ITEM_SHIELD:
            case ITEM_HELMET:
            case ITEM_ACCESSORY:
                drawEquipCompareWindow(activeChara, itemID, 0, 0, 0, 0);
                return;
            default:
                drawItemUsageInfo(itemID);
                break;
        }
    }
}

THUMB void drawItemUseTargetScreen(int messageOpen, int itemID, int page)
{
    if (messageOpen == 0) {
        drawItemMenuHeader(TownMenuPlayerControl::getSingleton()->targetChara_, 0, 1, 1);
        drawMenuFrame(0, 0, 0x100, 0xa0, -1);
        drawPartyHpMpListBattle(page);
        MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    }
    drawPartyStatusWindows();
    if (messageOpen == 0) {
        drawItemUsageInfo(itemID);
        drawMenuFrame(0, 0x78, 0xb0, 0x48, 0x90);
    }
}

THUMB void drawItemTargetCharaScreen(int messageOpen)
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
        drawItemMenuHeader(activeChara, 0, 0, 0);
        drawMenuFrame(0x88, 0xa0, 0x40, 0x20, -1);
        drawTargetCharaNameBar(targetChara);
        drawItemTargetInfo(targetChara, itemID, 0);
        drawCharaSelectWindow(1, 0);
        drawMenuFrame(0, 0, 0x100, 0x48, 0x28);
    }
    drawCharaItemList(targetChara, 1);
    drawMenuFrame(0, 0x50, 0x100, 0x70, -1);
    drawPartyStatusWindows();
}

THUMB void drawItemTargetItemScreen(int messageOpen)
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
        drawItemMenuHeader(activeChara, 0, 0, 0);
        drawMenuFrame(0x88, 0xa0, 0x40, 0x20, -1);
        drawTargetCharaNameBar(targetChara);
        drawMenuFrame(0, 0, 0x100, 0xa0, 0x70);
        drawItemListPage(targetChara, targetItemPage, 1);
        drawMenuDescription(0, 0, 1);
        if (MenuStatusInfo::getPlayerItemCount(targetChara) + 1 > 6) {
            drawPageIndicator(0xd0, 1, TownMenuPlayerControl::getSingleton()->targetItemPage_, 0);
        }
    }
    drawItemTargetInfo(targetChara, itemID, 1);
    drawMenuFrame(0, 8, 0x100, 0x48, 0x30);
    drawCharaItemList(targetChara, 1);
    drawMenuFrame(0, 0x50, 0x100, 0x70, -1);
}

THUMB void drawMagicCasterSelectScreen(int messageOpen)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int mp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::NOWMP, false);
    int maxMp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::MAXMP, false);
    if (messageOpen == 0) {
        drawMagicMenuHeader(activeChara);
        drawCharaSelectWindow(0, 0);
        drawCasterMpBar(activeChara, maxMp, mp);
        drawChooseCharaPrompt(0);
        drawTownSpellList(activeChara);
    }
    drawPartyStatusWindows();
}

THUMB void drawMagicSpellSelectScreen(int messageOpen)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int magicID = MenuStatusInfo::getPlayerActionID(activeChara, TownMenuPlayerControl::getSingleton()->activeMagic_, MenuStatusInfo::USE_TOWN);
    int mp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::NOWMP, false);
    int useMp = status::UseAction::getUseMp(magicID);
    if (messageOpen == 0) {
        drawMagicMenuHeader(activeChara);
        drawCasterMpBar(activeChara, mp, useMp);
        drawFieldSpellList(activeChara);
        drawMenuDescription(magicID, 1, 0);
        drawMenuFrame(0, 0, 0x100, 0xa0, 0x70);
        drawSpellOrTownSelectPrompt(0);
    }
    drawPartyStatusWindows();
}

THUMB void drawWarpTownSelectScreen(int messageOpen, int page)
{
    if (messageOpen == 0) {
        int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
        int mp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::NOWMP, false);
        int useMp = status::UseAction::getUseMp(0x81);
        drawRootMenuCommands(1, -1);
        drawRootMenuButtonFrames(0x40, 0xa0, 0);
        drawCasterMpBar(activeChara, mp, useMp);
        drawMenuFrame(0, 0xa0, 0x40, 0x20, -1);
        drawActiveCharaNameBar(activeChara, 0, 0, 0);
        drawMenuFrame(0, 0, 0x100, 0xa0, 0x70);
        drawRuraTownList(page);
        drawSpellOrTownSelectPrompt(1);
    }
    drawPartyStatusWindows();
}

THUMB void drawMagicTargetSelectScreen(int messageOpen, int page)
{
    if (messageOpen == 0) {
        int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
        int magicID = MenuStatusInfo::getPlayerActionID(activeChara, TownMenuPlayerControl::getSingleton()->activeMagic_, MenuStatusInfo::USE_TOWN);
        int mp = MenuDataCommon::getStatus(activeChara, MenuDataCommon::NOWMP, false);
        int useMp = status::UseAction::getUseMp(magicID);
        drawMagicMenuHeader(activeChara);
        drawCasterMpBar(activeChara, mp, useMp);
        drawMenuFrame(0, 0, 0x100, 0xa0, -1);
        drawPartyHpMpList(page);
    }
    drawPartyStatusWindows();
}

THUMB void drawStatusMainPage(int page)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    drawStatusMenuHeader(activeChara, page);
    drawCharaDetailWindow(activeChara, 1, 0);
    drawCharaAbilityWindow(activeChara, 0);
    drawCharaEquipWindow(activeChara, 0);
}

THUMB void drawStatusSpellPage(int page)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    drawStatusMenuHeader(activeChara, page);
    drawCharaSpellWindow(activeChara, 0);
    drawCharaSpellWindow(activeChara, 1);
}

THUMB void drawStatusPartySummaryScreen(int chara, int flag, int page)
{
    drawStatusMenuHeader(chara, page);
    if (flag == 1) {
        drawPartyHpMpWindows(0);
    } else {
        drawPartyAttackDefenceWindows(0);
    }
}

THUMB void drawStatusMoneyScreen(int page)
{
    drawStatusMenuHeader(-2, page);
    drawMoneyTimeWindow();
}

THUMB void drawOperationRootScreen(int messageOpen)
{
    if (messageOpen == 0) {
        drawRootMenuCommands(5, -1);
        drawRootMenuButtonFrames(0x40, 0xa0, 0);
        drawOperationCommandList();
    }
    drawPartyStatusWindows();
}

THUMB void drawSortItemScreen(int messageOpen, int mode)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (messageOpen == 0) {
        drawRootMenuCommands(5, 0);
        if (mode == 1) {
            drawOperationTitle(2);
            drawRootMenuButtonFrames(0, 0xa0, 0);
            drawMenuFrame(0x98, 0xa0, 0x40, 0x20, -1);
            if (activeChara == count) {
                drawActiveCharaNameBar(-2, 1, 0, 0x10);
            } else {
                drawActiveCharaNameBar(activeChara, 1, 0, 0x10);
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
            drawPartyOrderIcons(list, 2);
        } else {
            drawOperationTitle(3);
            drawRootMenuButtonFrames(0, 0xa0, 0);
            drawSortSackOptions();
        }
    }
    drawPartyStatusWindows();
    if (activeChara != count && mode == 1) {
        drawCharaItemList(activeChara, 0);
        drawMenuFrame(0, 0x50, 0x100, 0x70, -1);
    }
}

THUMB void drawTacticsScreen(char* playerList, int chara)
{
    drawRootMenuCommands(5, 0);
    drawOperationTitle(1);
    drawRootMenuButtonFrames(0, 0xa0, 0);
    drawMenuFrame(0x98, 0xa0, 0x40, 0x20, -1);
    drawActiveCharaNameBar(chara, 1, 0, 0x10);
    drawPartyOrderIcons(playerList, -1);
    drawPartyTacticsList(playerList);
}

THUMB void drawTacticsSelectScreen(char* playerList, int chara, int active)
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
    drawTacticsOptions();
    drawMenuFrame(0x10, 0, 0xd0, 0x48, -1);
    drawTownCommandCursor(x, y);
    drawTacticsScreen(playerList, chara);
}

THUMB void drawShiftPartyScreen(char* allocation, char* list, int active, int count)
{
    drawShiftPartyIconList(allocation, list, count);
    drawMenuFrame(0, 0x68, 0xe0, 0x58, -1);
    drawShiftPartyFrontSlots(allocation);
    drawMenuFrame(0, 0, 0x90, 0x68, -1);
    if (list[active] != -1) {
        drawCharaStatusWindow(list[active], 0);
        if (MenuStatusInfo::isCarriageEnable()) {
            drawCharaSpellWindow(list[active], 1);
            drawMenuFrame(0, 0, 0x100, 0xc0, 0x28);
            return;
        }
        drawPartyStatusWindows();
        return;
    }
    unkfunc_02172804();
    drawPartyStatusWindows();
}

THUMB void drawEquipCharaSelectScreen(int messageOpen)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    if (messageOpen == 0) {
        drawEquipMenuHeader(activeChara);
        drawCharaSelectWindow(0, 1);
    }
    drawCharaEquipWindow(activeChara, 1);
}

THUMB void drawEquipScreen(short* itemPosList, int itemCount, int itemType, int itemListActive)
{
    int activeChara = TownMenuPlayerControl::getSingleton()->activeChara_;
    int page = TownMenuPlayerControl::getSingleton()->activeItemPage_;
    int activeItem = TownMenuPlayerControl::getSingleton()->activeItem_;
    drawEquipMenuHeader(activeChara);
    drawEquipItemList(activeChara, itemPosList, itemCount, page);
    if (itemCount > 6) {
        drawPageIndicatorWide(0x50, (itemCount - 1) / 6, page);
    }
    drawEquipListCaption(itemType);
    drawMenuFrame(0, 0, 0x100, 0xa0, -1);
    if (activeItem == -1) {
        drawEquipItemInfo(activeChara, -1, itemType, itemListActive);
    } else {
        int index = activeItem;
        index += page * 6;
        drawEquipItemInfo(activeChara, itemPosList[index], itemType, itemListActive);
    }
    drawMenuFrame(0, 0x78, 0x68, 0x48, 0x90);
    drawCharaEquipWindow(activeChara, 1);
}

THUMB void drawTownShopScreen(int type)
{
    drawTownShopGoods(type);
}

THUMB void drawItemMenuHeader(int chara, int a, int b, int c)
{
    drawRootMenuCommands(s_pairs_0217ddb8[0].first, s_pairs_0217ddb8[0].second);
    drawRootMenuButtonFrames(0x40, 0xa0, a);
    if (b != 0) {
        drawMenuFrame(0x88, 0xa0, 0x40, 0x20, -1);
    } else {
        drawMenuFrame(0, 0xa0, 0x40, 0x20, -1);
    }
    drawActiveCharaNameBar(chara, b, c, 0);
}

THUMB void drawMagicMenuHeader(int chara)
{
    drawRootMenuCommands(s_pairs_0217ddb8[1].first, s_pairs_0217ddb8[1].second);
    drawRootMenuButtonFrames(0x40, 0xa0, 0);
    drawMenuFrame(0, 0xa0, 0x40, 0x20, -1);
    drawActiveCharaNameBar(chara, 0, 0, 0);
}

THUMB void drawStatusMenuHeader(int chara, int page)
{
    drawRootMenuCommands(4, -1);
    drawRootMenuButtonFrames(0x40, 0xa0, 0);
    drawMenuFrame(0x88, 0xa0, 0x40, 0x20, -1);
    drawActiveCharaNameBar(chara, 1, 0, 0);
    drawStatusPartyIcons(page);
}

THUMB void drawEquipMenuHeader(int chara)
{
    drawRootMenuCommands(5, 0);
    drawRootMenuButtonFrames(0, 0xa0, 0);
    drawOperationTitle(0);
    drawMenuFrame(0x98, 0xa0, 0x40, 0x20, -1);
    drawActiveCharaNameBar(chara, 1, 0, 0x10);
}

THUMB void drawCharaSelectWindow(int a, int b)
{
    int count;
    if (a == 1) {
        count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) + 1;
    } else {
        count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    }
    drawPartyIconRow(a, b);
    if (count < 5) {
        drawMenuFrame(0, 0x70, 0xb8, 0x30, -1);
    } else if (count == 5) {
        drawMenuFrame(0, 0x70, 0xe0, 0x30, -1);
    } else {
        drawMenuFrame(0, 0x48, 0xe0, 0x58, -1);
    }
}

THUMB void drawStatusPartyIcons(int page)
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    if (page == 0) {
        if (count > 4) {
            count = 5;
            drawPageIndicator(0xd0, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) / count, page, 0);
        }
        for (int i = 0; i < count; i++) {
            drawPartyMemberIcon(i, i * 0x28 + 0x10, 0x70);
        }
        int n = 0;
        for (int i = 0; i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT); i++) {
            if (!MenuStatusInfo::isPlayerType(i, MenuStatusInfo::TYPE_NORMAL_NPC)) {
                drawCarriageOrderNumber(i + 1, n * 0x28 + 8, 0x78, i);
                n++;
            }
        }
        if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) < 4) {
            int x = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) * 0x28 + 0x10;
            drawPartyMemberIcon(-2, x, 0x70);
            drawMenuFrame(0, 0x70, 0xb8, 0x30, -1);
            return;
        }
        if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) == 4) {
            drawPartyMemberIcon(-2, 0xb0, 0x70);
            drawMenuFrame(0, 0x70, 0xe0, 0x30, -1);
            return;
        }
        drawMenuFrame(0, 0x70, 0x100, 0x30, -1);
        return;
    }
    if (page == 1) {
        if (count > 10) {
            count = 10;
        }
        for (int i = 5; i < count; i++) {
            drawPartyMemberIcon(i, (i - page * 5) * 0x28 + 0x10, 0x70);
        }
        if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) < 10) {
            int x = (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) - 5) * 0x28 + 0x10;
            drawPartyMemberIcon(-2, x, 0x70);
        }
    } else {
        drawPartyMemberIcon(-2, 0x10, 0x70);
    }
    drawPageIndicator(0xd0, MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) / 5, page, 0);
    drawMenuFrame(0, 0x70, 0x100, 0x30, -1);
}

THUMB void drawCharaItemList(int chara, int flag)
{
    if ((flag != 0 && TownMenuPlayerControl::getSingleton()->targetFukuro_ != 0) || (flag == 0 && TownMenuPlayerControl::getSingleton()->activeFukuro_ != 0)) {
        drawBagItemNameList();
    } else {
        drawCharaItemNameList(chara);
    }
}

THUMB void drawItemListPage(int chara, int page, int flag)
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
            drawBagItemSlot(itemID, index, (i % 2 + 1) * 16 + (i % 2) * 0x68 + 4, (i / 2) * 8 + (i / 2) * 0x18 + 4);
        }
    } else {
        int count = MenuStatusInfo::getPlayerItemCount(chara) - page * 6;
        if (count > 6) {
            count = 6;
        }
        for (int i = 0; i < count; i++) {
            if (page == 0) {
                int itemID = MenuStatusInfo::getPlayerItemID(chara, i);
                drawItemSlot(itemID, (i % 2 + 1) * 16 + (i % 2) * 0x68 + 4, (i / 2) * 8 + (i / 2) * 0x18 + 4);
                if (MenuStatusInfo::isPlayerEquipItemIndex(chara, i) == true) {
                    drawItemEquippedMark(i);
                }
            } else {
                int itemID = MenuStatusInfo::getPlayerItemID(chara, i + 6);
                drawItemSlot(itemID, (i % 2 + 1) * 16 + (i % 2) * 0x68 + 4, (i / 2) * 8 + (i / 2) * 0x18 + 4);
                if (MenuStatusInfo::isPlayerEquipItemIndex(chara, i + page * 6) == true) {
                    drawItemEquippedMark(i);
                }
            }
        }
        if (!gTownMenu_MESSAGE.isOpen() && flag != 0 && count < 6) {
            drawItemSlot(-1, (count % 2 + 1) * 16 + (count % 2) * 0x68 + 4, (count / 2) * 8 + (count / 2) * 0x18 + 4);
        }
    }
}

THUMB void drawPartyHpMpList(int page)
{
    int i;
    int end = (page + 1) * 4;
    if (end >= MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        end = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    }
    for (i = page * 4; i < end; i++) {
        drawCharaSummaryPanel(i, i - page * 4, page);
    }
    if (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) > 4) {
        drawPageIndicatorWide(0x50, (MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL) - 1) / 4, page);
    }
}

THUMB void drawPartyHpMpListBattle(int page)
{
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    drawPartyHpMpList(page);
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
}

THUMB void drawFieldSpellList(int chara)
{
    int count = MenuStatusInfo::getPlayerActionCount(chara, MenuStatusInfo::USE_TOWN);
    int n = 0;
    for (int i = 0; i < count; i++) {
        int magicID = MenuStatusInfo::getPlayerActionID(chara, i);
        if (MenuStatusInfo::isPlayerActionUseType(magicID, MenuStatusInfo::USE_TOWN) == true) {
            int word = MenuStatusInfo::getWordDBIndex(magicID);
            drawSpellName((n % 2) * 0x78 + 4, (n / 2) * 16 + 0xe + (n / 2) * 8, word + 0x70000000, chara);
            n++;
        }
    }
}

THUMB void drawOperationCommandList()
{
    int text[8] = {(int)0xe000015e, (int)0xe000015f, (int)0xe0000160, (int)0xe0000161, (int)0xe0000162, (int)0xe0000163, (int)0xe00001b5, (int)0xe0000165};
    for (int i = 0; i < 8; i++) {
        drawCommandLabel((i % 2) * 0x50 + 0x20 + (i % 2) * 16, (i / 2) * 16 + 0x3c + (i / 2) * 8, text[i]);
    }
    drawMenuFrame(0x10, 0x30, 0xd0, 0x70, -1);
}

THUMB void drawSortSackOptions()
{
    UnkTownMenuDrawPair text = s_pairs_0217ddb8[2];
    drawCommandLabel(0x10, 0x88, text.first);
    drawCommandLabel(0x70, 0x88, text.second);
    drawMenuFrame(0, 0x80, 0xd0, 0x20, -1);
}

THUMB void drawPartyOrderIcons(char* list, int mode)
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
        drawMenuFrame(0, 0x70, 0xe0, 0x30, -1);
    } else {
        drawMenuFrame(0, 0x48, 0xe0, 0x58, -1);
    }
    char* p;
    for (; (p = &list[i], list[i] != -1) && i < 5; i++) {
        drawPartyMemberIcon(list[i], i * 0x20 + 0x10 + i * 8, y);
    }
    int n = 0;
    y += 8;
    for (int j = 0; j < outCount; j++) {
        if ((mode == 2 || MenuStatusInfo::getPlayerIndex(j) != 1) && MenuStatusInfo::isPlayerType(j, MenuStatusInfo::TYPE_PLAYER)) {
            int x = n * 0x20 + 0x10 + n * 8;
            drawCarriageOrderNumber(j + 1, x - 8, y, list[n]);
            n++;
        }
    }
    if (*p == -1 || i < 5) {
        int x = i * 0x20 + 0x10 + i * 8;
        if (i == 5) {
            x = 0x10;
        }
        drawPartyMemberIcon(-2, x, 0x70);
        return;
    }
    for (; list[i] != -1 && i < 9; i++) {
        drawPartyMemberIcon(list[i], (i - 5) * 0x20 + 0x10 + (i - 5) * 8, 0x70);
    }
    drawPartyMemberIcon(-2, (i - 5) * 0x20 + 0x10 + (i - 5) * 8, 0x70);
}

THUMB void drawPartyTacticsList(char* list)
{
    int i = 0;
    drawMenuHeaderText(i, 0xe, 0xe00001aa);
    if (list[i] != -1) {
        int y = 0x30;
        do {
            drawCharaTacticsRow(list[i], 0, y);
            i++;
            y += 0x10;
        } while (list[i] != -1);
    }
    drawMenuFrame(0, 0, 0x100, 0xc0, 0x20);
}

THUMB void drawEquipItemList(int chara, short* itemPosList, int itemCount, int page)
{
    if (page == 0) {
        itemCount = dss::clamp<int>(0, itemCount, 6);
        for (int i = 0; i < itemCount; i++) {
            int itemID = MenuStatusInfo::getPlayerItemID(chara, itemPosList[i]);
            drawItemSlot(itemID, (i % 2 + 1) * 16 + 4 + (i % 2) * 0x68, (i / 2) * 8 + (i / 2) * 0x18 + 4);
            if (MenuStatusInfo::isPlayerEquipItemIndex(chara, itemPosList[i]) == true) {
                drawItemEquippedMark(i);
            }
        }
    } else {
        for (int i = 6; i < itemCount; i++) {
            int itemID = MenuStatusInfo::getPlayerItemID(chara, itemPosList[i]);
            drawItemSlot(itemID, ((i - 6) % 2 + 1) * 16 + 4 + ((i - 6) % 2) * 0x68, ((i - 6) / 2) * 8 + ((i - 6) / 2) * 0x18 + 4);
            if (MenuStatusInfo::isPlayerEquipItemIndex(chara, itemPosList[i]) == true) {
                drawItemEquippedMark(i - 6);
            }
        }
    }
}

THUMB void drawEquipItemInfo(int chara, int activeItem, int itemType, int itemListActive)
{
    if (itemType == -1) {
        return;
    }
    if (activeItem == -1) {
        drawEquipCompareWindow(chara, -1, itemType, 0, 1, itemListActive);
        return;
    }
    drawEquipCompareWindow(chara, MenuStatusInfo::getPlayerItemID(chara, activeItem), itemType, 0, 1, itemListActive);
}

THUMB void drawSettingScreen()
{
    drawSettingScreenLabels();
    drawRootMenuCommands(5, -1);
    drawRootMenuButtonFrames(0x40, 0xa0, 0);
    drawPartyStatusWindows();
    drawMoneyWindow(-1, -1, 0);
}
