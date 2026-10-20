#pragma ipa file
#include "ov019/materielmenu/UnkMaterielMenuWindowDraw.hpp"
#include "ov019/materielmenu/UnkMaterielMenuDrawParts.hpp"
#include "ov019/materielmenu/MaterielMenuPlayerControl.hpp"
#include "ov027/materielmenu/shop/MaterielMenu_SHOP_MANAGER.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/TownMenu_MESSAGE.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/status/TouchData.hpp"
#include "main/status/UseItem.hpp"

using menu::MaterielMenuPlayerControl;
using menu::MenuStatusInfo;

#define PARTS_END {0xff, 0x00, 0x0000, 0, 0x00, 0x00, 0x00, 0x00}

static UnkMenuParts s_parts_02181d86[] = {
    {0x01, 0x00, (short)0xf000, 0, 0xb8, 0x00, 0x48, 0x30},
    {0x0d, 0x08, (short)0xf000, 0, 0xc0, 0x0a, 0x38, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0xc0, 0x1a, 0x38, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_parts_02181d5c[] = {
    {0x01, 0x00, (short)0xf000, 0, 0xb8, 0x00, 0x48, 0x30},
    {0x0d, 0x08, (short)0xf000, 0, 0xc0, 0x0a, 0x38, 0x10},
    PARTS_END,
};

static UnkMenuParts s_parts_02181cec[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x48, 0x68, 0x30},
    PARTS_END,
};

static UnkMenuParts s_parts_02181d08[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x48, 0x40, 0x30},
    PARTS_END,
};

static UnkMenuParts s_parts_02181d24[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x48, 0xb8, 0x30},
    PARTS_END,
};

static UnkMenuParts s_parts_02181d40[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x48, 0x90, 0x30},
    PARTS_END,
};

static UnkMenuParts s_parts_02181f46[] = {
    {0x0d, 0x09, (short)0xf100, 0, 0x58, 0x0b, 0x48, 0x0a},
    {0x0d, 0x0b, (short)0xf100, 1, 0x00, 0x00, 0x10, 0x0a},
    {0x01, 0x00, (short)0xf000, 0, 0x50, 0x00, 0x60, 0x20},
    {0x0d, 0x08, (short)0xf100, 2, 0x0c, 0xa0, 0xe4, 0x14},
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x98, 0x100, 0x28},
    PARTS_END,
};

static UnkMenuParts s_parts_02181dbe[] = {
    {0x0d, 0x09, (short)0xf100, 0, 0x40, 0x50, 0x80, 0x10},
    {0x0d, 0x09, (short)0xf100, 1, 0x40, 0x5c, 0x80, 0x0c},
    {0x01, 0x00, (short)0xf000, 0, 0x38, 0x48, 0x90, 0x28},
    PARTS_END,
};

static UnkMenuParts s_parts_02181df6[] = {
    {0x0d, 0x08, (short)0xf100, 0, 0x10, 0x08, 0x90, 0x0a},
    {0x0d, 0x08, (short)0xf100, 1, 0x10, 0x17, 0x90, 0x0a},
    {0x0d, 0x08, (short)0xf100, 2, 0x10, 0x26, 0x90, 0x0a},
    {0x0d, 0x08, (short)0xf100, 3, 0x10, 0x35, 0x90, 0x0a},
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x00, 0xb0, 0x48},
    PARTS_END,
};

static UnkMenuParts s_parts_02181e4a[] = {
    {0x0d, 0x09, (short)0xf100, 0, 0x58, 0x2e, 0x48, 0x0c},
    {0x0d, 0x0b, (short)0xf100, 1, 0x00, 0x00, 0x10, 0x0c},
    {0x0d, 0x08, (short)0xf100, 2, 0x10, 0x50, 0xd0, 0x20},
    {0x01, 0x00, (short)0xf000, 0, 0x50, 0x20, 0x60, 0x28},
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x48, 0x100, 0x28},
    PARTS_END,
};

static UnkMenuParts s_parts_02181e9e[] = {
    {0x0d, 0x08, (short)0xf100, 0, 0x1c, 0x10, 0x28, 0x0a},
    {0x0d, 0x08, (short)0xf100, 1, 0x64, 0x10, 0x30, 0x0a},
    {0x0d, 0x0a, (short)0xf100, 2, 0xb0, 0x10, 0x28, 0x0a},
    {0x01, 0x00, (short)0xf000, 0, 0x10, 0x08, 0xe0, 0xb0},
    {0x16, 0x00, (short)0xf000, 0, 0x10, 0x20, 0xe0, 0x00},
    PARTS_END,
};

static UnkMenuParts s_parts_02181ef2[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x00, 0xb0, 0x48},
    {0x0d, 0x08, (short)0xf000, 0, 0x14, 0x08, 0x94, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x14, 0x17, 0x94, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0x14, 0x26, 0x94, 0x0a},
    {0x0d, 0x08, (short)0xf000, 3, 0x14, 0x35, 0x94, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_parts_02181f9a[] = {
    {0x01, 0x00, (short)0xf000, 0, 0xb0, 0x78, 0x50, 0x20},
    {0x01, 0x00, (short)0xf000, 0, 0xb0, 0x98, 0x50, 0x28},
    {0x0d, 0x08, (short)0xf000, 0, 0xec, 0x82, 0x0c, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 1, 0xb8, 0x82, 0x34, 0x0a},
    {0x0d, 0x08, (short)0xf000, 2, 0xbc, 0xa0, 0x38, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 3, 0xbc, 0xac, 0x38, 0x0a},
    PARTS_END,
};

THUMB void unkfunc_0217be3c()
{
    unkfunc_02178ff8(0, 0);
    drawMoneyAndPartyWindows();
}

THUMB void unkfunc_0217be4c(int type)
{
    unkfunc_0217927c(type);
    unkfunc_02179214();
    drawMoneyWindow(0x88, 0xa0, type);
    MaterielMenuPlayerControl* control = MaterielMenuPlayerControl::getSingleton();
    int itemID = MaterielMenu_SHOP_MANAGER::getSingleton()->getItem(control->activeItem_);
    unkfunc_021791c0(itemID);
    if (status::UseItem::getEquipItemType(itemID) <= ITEM_ACCESSORY) {
        unkfunc_02179054();
    } else {
        unkfunc_02179114();
    }
}

THUMB void unkfunc_0217be90(int type, int itemID)
{
    unkfunc_021794a0(itemID);
    drawPartyIcons(0, 1);
    drawActiveCharaHp(0);
    drawMoneyWindow(0x88, 0xa0, type);
    unkfunc_02179378();
}

THUMB void unkfunc_0217beb8()
{
    drawPartyIcons(0, 1);
    drawActiveCharaHp(0);
    drawMoneyWindow(0x88, 0xa0, 0);
    unkfunc_02179774();
}

THUMB void unkfunc_0217bed8(int fukuro)
{
    drawActiveCharaHp(0);
    drawMoneyWindow(0x88, 0xa0, 0);
    unkfunc_02179aac(0);
    unkfunc_02179878(0);
    if (fukuro == 1) {
        unkfunc_0217b9c4();
    } else {
        unkfunc_021799e4(0);
    }
    unkfunc_02179b3c(-1, fukuro);
}

THUMB void unkfunc_0217bf14()
{
    drawActiveCharaHp(0);
    drawMoneyWindow(0x88, 0xa0, 0);
    unkfunc_021799e4(1);
    unkfunc_02179aac(1);
    unkfunc_02179878(1);
    unkfunc_02179b3c(-1, 0);
}

THUMB void unkfunc_0217bf44(int value)
{
    unkfunc_02179ce4(value);
    unkfunc_02178ff8(0, 0);
    drawCommandCursor(0xa4, 0x28);
    unkfunc_02179b3c(-1, 0);
}

THUMB void unkfunc_0217bf68()
{
    int y = 0x10;
    switch (MaterielMenu_SHOP_MANAGER::getSingleton()->getShopAction()) {
        case 1:
            y = 0x28;
            break;
        case 2:
            y = 0x40;
            break;
    }
    drawCommandCursor(0xa4, y);
    unkfunc_0217be3c();
}

THUMB void drawChurchScreen(int index, int flag)
{
    if (index == -1 && gTownMenu_MESSAGE.isMessageWAITPROG() == true && flag == 0) {
        drawChurchCommands();
    }
    drawMoneyAndPartyWindows();
}

THUMB void unkfunc_0217bfbc()
{
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    drawPartyIcons(0x28, 0);
    drawActiveCharaHp(1);
    drawCharaStatusWindow(chara, 1);
    drawMoneyWindow(-1, -1, 0);
}

THUMB void unkfunc_0217bfe8()
{
    drawPartyStatusWindows();
}

THUMB void unkfunc_0217bff0()
{
    unkfunc_02178ff8(1, 0);
    drawMoneyAndPartyWindows();
}

THUMB void drawBankAmountScreen(int mode, int flag, int value)
{
    if (mode == 0) {
        if (flag != 0) {
            drawCommandCursor(0xa4, 0x10);
        } else {
            drawCommandCursor(0xa4, 0x28);
        }
        unkfunc_02178ff8(1, 1);
        drawBankDigits(value, 1);
    }
    drawMoneyAndPartyWindows();
}

THUMB void unkfunc_0217c034(int value, int flag)
{
    if (flag != 0) {
        drawBankDigits(value, 0);
    }
    drawMoneyAndPartyWindows();
}

THUMB void unkfunc_0217c048(int coin, int bet, int type)
{
    unkfunc_02179de8(coin, bet, 0, type);
    unkfunc_02179d24();
}

THUMB void unkfunc_0217c058(int mode, int coin, int bet, int* flags, int flag)
{
    if (mode == 1) {
        unkfunc_02179ea8(flags);
    }
    unkfunc_02179de8(coin, bet, flag, 0);
    unkfunc_02179d24();
}

THUMB void unkfunc_0217c07c(int mode, int coin, int bet, int flag)
{
    if (mode == 1) {
        unkfunc_02179e68(flag);
    }
    unkfunc_02179de8(coin, bet, flag, 0);
    unkfunc_02179d24();
}

THUMB void unkfunc_0217c0a0(int value, int flag)
{
    int param[2] = {(int)0xe0000352, 0};
    param[1] = value;
    if (value > 9999999) {
        value = 9999999;
    }
    param[1] = value;
    if (flag) {
        drawMenuPartsColored(s_parts_02181d5c, param, 1);
    } else {
        drawMenuPartsColored(s_parts_02181d86, param, 1);
    }
}

THUMB void unkfunc_0217c0e8(int value, int count)
{
    int param[4] = {(int)0xe0000071, 0, (int)0xe0000352, 0};
    param[1] = count;
    param[3] = value;
    if (value > 9999999) {
        value = 9999999;
    }
    param[3] = value;
    setMenuDrawOffset(0, 0);
    drawMenuPartsColored(s_parts_02181f9a, param, 1);
}

THUMB void unkfunc_0217c12c()
{
    int param[4];
    param[0] = (int)0xe000037f;
    param[1] = (int)0xe0000380;
    param[2] = (int)0xe0000381;
    param[3] = (int)0xe0000214;
    drawMenuPartsColored(s_parts_02181ef2, param, 1);
}

THUMB void unkfunc_0217c15c(int chara)
{
    MenuStatusInfo::setMode(MenuStatusInfo::PLAYER_MODE);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    UnkMenuParts* frames[4] = {s_parts_02181d08, s_parts_02181cec, s_parts_02181d40, s_parts_02181d24};
    drawMenuPartsColored(frames[count - 1], 0, 1);
    for (int i = 0; i < count; i++) {
        unkfunc_0217a578(MenuStatusInfo::getHaveStatusInfo(i).getIconIndex(), i * 0x28 + 0x10, 0x48);
        unkfunc_0217a598(i, i * 0x28 + 0x10, 0x48);
    }
    unkfunc_0217a4d0(chara, 0, 0x28);
    setMenuDrawOffset(0, 0);
    unkfunc_0217a67c(chara, 0, 0x58);
}

THUMB void unkfunc_0217c1e0(int mode, int flag)
{
    int param[3] = {(int)0xe0000385, (int)"\xff\xfe\xac\x24", 0xc9af5};
    int coin = MenuStatusInfo::getCoin();
    if (mode == 5) {
        if (flag != 0) {
            setMenuDrawOffset(0, 0);
            unkfunc_0217a8d8(mode, 0, 0, 0);
            unkfunc_0217a9c8(coin, 0xb0, 0x50);
        } else {
            unkfunc_0217a8d8(mode, 0, 0x70, 1);
            unkfunc_0217a9c8(coin, 0xb0, 0x20);
            drawMenuPartsColored(s_parts_02181e4a, param, 1);
        }
    } else {
        if (flag != 0) {
            setMenuDrawOffset(0, 0);
            unkfunc_0217a8d8(mode, 0, 0, 0);
            unkfunc_0217a9c8(coin, 0xb0, 0x60);
        } else {
            unkfunc_0217a8d8(mode, 0, 0x60, 1);
            unkfunc_0217a9c8(coin, 0xb0, 0x10);
            drawMenuParts(s_parts_02181e4a, param, 0, -0x10, 1);
        }
    }
}

THUMB void unkfunc_0217c2a4()
{
    int param[3] = {(int)0xe0000386, (int)"\xff\xfe\xac\x24", 0xc9a9c};
    drawMenuPartsColored(s_parts_02181f46, param, 1);
}

THUMB void unkfunc_0217c2cc()
{
    int param[4] = {(int)0xe0000389, (int)0xe000038a, (int)0xe000038b, (int)0xe0000214};
    drawMenuPartsColored(s_parts_02181df6, param, 1);
}

THUMB void unkfunc_0217c2f4()
{
    int title[2] = {(int)"\xff\xfe\xac\x24", (int)0xe0000392};
    drawMenuPartsColored(s_parts_02181dbe, title, 1);
    int text[3] = {(int)0xe000038e, (int)0xe000038f, (int)0xe0000390};
    setMenuDrawOffset(0, 0);
    drawMenuPartsColored(s_parts_02181e9e, text, 1);
    for (int i = 0; i < 10; i++) {
        int score = status::g_TouchData.ranking_[i].score;
        int stage = status::g_TouchData.ranking_[i].stage;
        if (stage == 0) {
            break;
        }
        unkfunc_0217a9f8(i + 1, score, stage, 0, i * 14 + 0x28);
    }
}

THUMB void unkfunc_0217c368()
{
    unkfunc_02179f28();
}

THUMB void unkfunc_0217c370(int index)
{
    unkfunc_0217a018(index);
}

THUMB void unkfunc_0217c378()
{
    unkfunc_0217ba00();
}

THUMB void unkfunc_0217c380(int mode, int page, int maxPage, int type)
{
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    unkfunc_0217a334(type, 0);
    unkfunc_0217ba68(page, maxPage, 0);
    switch (mode) {
        case 0:
            drawCharaDetailWindow(chara, 1, 0);
            drawCharaAbilityWindow(chara, 0);
            drawCharaEquipWindow(chara, 0);
            break;
        case 1:
            drawCharaSpellWindow(chara, 0);
            drawCharaSpellWindow(chara, 1);
            break;
    }
}

THUMB void unkfunc_0217c3dc(int page, int maxPage, int type, int monster)
{
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    unkfunc_0217a334(type, monster);
    unkfunc_0217ba68(page, maxPage, monster);
    drawCharaDetailWindow(chara, 1, monster);
    drawCharaAbilityWindow(chara, monster);
    drawCharaItemWindow(chara);
    drawCharaSpellListWindow(chara, monster);
}

THUMB void unkfunc_0217c424(int mode, int page, int maxPage, int type, short* list, int total)
{
    if (mode == 1) {
        unkfunc_0217a464(MaterielMenuPlayerControl::getSingleton()->activeChara_, 0x48);
        return;
    }
    unkfunc_0217a334(type, 0);
    unkfunc_0217bc54(page, maxPage, list, total);
    unkfunc_0217bd14();
}

THUMB void unkfunc_0217c458()
{
    unkfunc_0217aa1c();
}

THUMB void drawTagModeAmbassadorScreen(int mode, int icon, int type, int value)
{
    if (mode == 0) {
        drawTagModeIconGrid(type, value);
    } else {
        drawNameEditIcon(icon, 0x48);
    }
}

THUMB void unkfunc_0217c47c(int page, int value, int index, int icon, int flag)
{
    unkfunc_0217ab94(page, value, flag);
    if (index != -1) {
        drawNameEditIcon(icon, 0);
        unkfunc_0217ac98(index, 0);
    }
}

THUMB void unkfunc_0217c4a4(int mode, int icon, int page, int value)
{
    if (mode <= 1) {
        drawNameEditIcon(icon, 0);
    }
    switch (mode) {
        case 0:
            unkfunc_0217add4(page);
            break;
        case 1:
            unkfunc_0217ae9c(value);
            break;
        case 2:
            unkfunc_0217ad28(icon, 1, 0);
            break;
    }
}

THUMB void unkfunc_0217c4e4(int mode, int flag, int icon)
{
    if (flag == 0) {
        if (mode == 0) {
            drawNameEditIcon(icon, 0);
        }
    } else if (mode == 1) {
        unkfunc_0217af70();
    }
}

THUMB void drawMoneyAndPartyWindows()
{
    drawMoneyWindow(-1, -1, 0);
    drawPartyStatusWindows();
}

THUMB void unkfunc_0217c518()
{
    unkfunc_0217b924();
}

THUMB void unkfunc_0217c520(int mode)
{
    drawActiveCharaHp(0);
    drawCharaIconWithCondition(0, 0x10, 0x70);
    drawCharaIconWithCondition(-2, 0x38, 0x70);
    drawMenuFrame(0, 0x70, 0xb8, 0x30, -1);
    int chara = MaterielMenuPlayerControl::getSingleton()->activeChara_;
    if (chara == 0) {
        if (mode == 0) {
            drawCharaDetailWindow(chara, 1, 0);
            drawCharaAbilityWindow(chara, 0);
            drawCharaEquipWindow(chara, 0);
        } else {
            drawCharaSpellWindow(chara, 0);
            drawCharaSpellWindow(chara, 1);
        }
    } else if (mode == 2) {
        drawMoneyTimeWindow();
    } else if (mode == 3) {
        drawPartyHpMpWindows(1);
    } else {
        drawPartyAttackDefenceWindows(1);
    }
}

// not in the ROM (dead-stripped), its const local is still in .rodata
THUMB void unkfunc_unused_0217e340()
{
    const int unk = 0;
}
