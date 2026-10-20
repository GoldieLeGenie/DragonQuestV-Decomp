#pragma ipa file
#include "ov018/menu/UnkBattleMenuDraw.hpp"
#include "ov018/menu/BattleMenu.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/UseAction.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextAPI.hpp"

using menu::MenuStatusInfo;

// parts lists (their definition order sets the .data layout)
static UnkMenuParts s_parts_02177324[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x18, 0x58, 0xe0, 0x48 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177378[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x10, 0x70, 0xe8, 0x30 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_0217735c[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x68, 0xe0, 0x58 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021772b4[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x40, 0xa0, 0x98, 0x20 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177394[] = {
    { 0x0e, 0x08, (short)0xf000, 0, 0x6, 0x0, 0x40, 0x18 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021772d0[] = {
    { 0x03, 0xd0, (short)0xf000, 0, 0x0, 0x8, 0x100, 0x40 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177308[] = {
    { 0x0d, 0x09, (short)0xf000, 0, 0x0, 0x4, 0x70, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021772ec[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x18, 0x78, 0xd0, 0x28 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177340[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x98, 0x68 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177458[] = {
    { 0x14, 0xc2, 0, 0, 0x4, 0xe, 0x20, 0x18 },
    { 0x0c, 0xf1, 0, 0, 0x0, 0x0, 0x20, 0x20 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021774ac[] = {
    { 0x14, 0xc2, 0, 0, 0x4, 0xe, 0x20, 0x18 },
    { 0x0c, 0xf1, 0, 0, 0x0, 0x0, 0x20, 0x20 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021774d6[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x100, 0xa0 },
    { 0x16, 0x00, (short)0xf000, 0, 0x0, 0x68, 0x100, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177500[] = {
    { 0x0f, 0x08, (short)0xf000, 0, 0x0, 0x0, 0xa, 0xa },
    { 0x0d, 0x0b, (short)0xf000, 1, 0x0, 0x0, 0xa, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_0217752a[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x10, 0x0, 0x30, 0xa },
    { 0x0d, 0x08, (short)0xf000, 1, 0x14, 0xc, 0x28, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177554[] = {
    { 0x14, 0xc2, 0, 0, 0x4, 0xe, 0x20, 0x18 },
    { 0x0c, 0xf1, 0, 0, 0x0, 0x0, 0x20, 0x20 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_0217757e[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x4c, 0xab, 0x3c, 0xa },
    { 0x0d, 0x08, (short)0xf000, 1, 0x94, 0xab, 0x3c, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021773b0[] = {
    { 0x0d, 0x08, (short)0xf000, 2, 0x20, 0xc, 0xa, 0xa },
    { 0x0f, 0x0b, (short)0xf000, 3, 0x0, 0x0, 0x14, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021773da[] = {
    { 0x0d, 0x08, (short)0xf000, 2, 0x20, 0xc, 0xa, 0xa },
    { 0x0d, 0x0b, (short)0xf000, 3, 0x0, 0x0, 0x14, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177404[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x48, 0x20 },
    { 0x0d, 0x09, (short)0xf000, 0, 0x8, 0xa, 0x38, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_0217742e[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x100, 0xa0 },
    { 0x16, 0x00, (short)0xf000, 0, 0x0, 0x68, 0x100, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177482[] = {
    { 0x0d, 0x08, (short)0xf000, 0, 0x14, 0xf, 0x4c, 0xa },
    { 0x0d, 0x08, (short)0xf000, 1, 0x74, 0xf, 0x4c, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021775a8[] = {
    { 0x14, 0xc2, 0, 0, 0x4, 0xe, 0x20, 0x18 },
    { 0x0c, 0xf1, 0, 0, 0x0, 0x0, 0x20, 0x20 },
    { 0x0f, 0x0a, (short)0xf000, 1, -4, 0x8, 0xc, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_021775e0[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x100, 0xa0 },
    { 0x16, 0x00, (short)0xf000, 2, 0x0, 0x8, 0x100, 0x0 },
    { 0x16, 0x00, (short)0xf000, 3, 0x0, 0x90, 0x100, 0x0 },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};
static UnkMenuParts s_parts_02177618[] = {
    { 0x01, 0x00, (short)0xf000, 0, 0x0, 0x0, 0x100, 0xc0 },
    { 0x16, 0x00, (short)0xf000, 1, 0x0, 0x18, 0x100, 0x0 },
    { 0x0d, 0x09, (short)0xf000, 0, 0x10, 0xc, 0xe0, 0xa },
    { 0xff, 0x00, 0, 0, 0x0, 0x0, 0x0, 0x0 },
};

static int s_param[2];

inline bool status::HaveStatus::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}
inline unsigned short status::HaveStatus::getStrength() const { return baseStatus_.strength_; }
inline unsigned short status::HaveStatus::getProtection() const { return baseStatus_.protection_; }
inline unsigned short status::PlayerData::getStrength() { return baseStatus_.strength_; }
inline unsigned char status::PlayerData::getAgility() { return baseStatus_.agility_; }
inline unsigned short status::PlayerData::getProtection() { return baseStatus_.protection_; }
inline unsigned char status::PlayerData::getWisdom() { return baseStatus_.wisdom_; }
inline unsigned char status::PlayerData::getLuck() { return baseStatus_.luck_; }
inline unsigned short status::PlayerData::getMp() { return baseStatus_.mp_; }
inline unsigned short status::PlayerData::getMpMax() { return baseStatus_.mpMax_; }
inline unsigned char status::PlayerData::getLevel() { return baseStatus_.level_; }
inline int BattleMenuPlayerControl::getPartyHP(int memberNum) { return statusData_[memberNum].hp; }
inline int BattleMenuPlayerControl::getHPColor(int memberNum)
{
    if (memberNum < 0) {
        return 0;
    }
    return statusData_[memberNum].color;
}
inline int BattleMenuPlayerControl::getSpecialFlag(int memberNum) { return historyData_[memberNum].special; }

THUMB void drawAttackCancelMenu()
{
    drawAttackCommandButton();
}

THUMB void drawItemMenu(int* items, int count, int page)
{
    drawItemCommandHeader();
    drawItemList(items, count, page);
}

THUMB void drawItemUseEquipMenu(int* items, int count, int page)
{
    drawMenuPartsPlain(s_parts_021772b4, 0);
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    drawBattleActiveMember(&info, BattleMenuPlayerControl::getSingleton()->getPartyHP(chara), 0);
    s_param[0] = 0xe00000a1;
    s_param[1] = 0xe00000a4;
    drawMenuPartsColored(s_parts_0217757e, s_param, 1);
    drawItemList(items, count, page);
}

THUMB void drawItemUseOnPartyMenu()
{
    drawItemCommandHeader();
    drawPartyTargetSelect();
}

THUMB void drawItemUseOnEnemyMenu()
{
    drawItemCommandHeader();
}

THUMB void drawAttackTargetMenu(int group)
{
    drawEnemyTargetSelect(group);
}

THUMB void drawMagicMenu(int* actions, int count, int page)
{
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(BattleMenuPlayerControl::getSingleton()->activeChara_);
    int pageMax;
    drawMagicCommandHeader();
    drawMenuPartsPlain(s_parts_0217742e, 0);
    pageMax = (count - 1) / 6;
    int num = (count - 1) % 6 + 1;
    if (pageMax > page) {
        num = 6;
    }
    int top = page * 6;
    for (int i = 0; i < num; i++) {
        int x = i % 2;
        int y = i / 2;
        x = x * 120 + 20;
        y = y * 32 + 12;
        drawBattleActionName(x, y, actions[top + i]);
    }
    drawBattleHelpMessage(8, 0x74, status::UseAction::getMenuMessage(info.haveAction_.getAction(BattleMenuPlayerControl::getSingleton()->activeMagic_)));
    drawBattlePageNumber(0xd8, 0x78, pageMax, page);
    drawBattleCancelButton();
}

THUMB void drawMagicOnEnemyMenu()
{
    drawMagicCommandHeader();
}

THUMB void drawMagicOnPartyMenu()
{
    drawMagicCommandHeader();
    drawPartyTargetSelect();
}

THUMB void drawTacticsMemberMenu()
{
    drawMenuPartsPlain(s_parts_02177378, 0);
    drawTacticsCommandButton();
    int list[4] = {0};
    for (int i = 0; i < 4; i++) list[i] = 0;
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    int n = 0;
    for (int i = 0; i < count; i++) {
        int index = MenuStatusInfo::getPlayerIndex(i);
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
        if (info.haveStatus_.isPlayer() && index != 1) {
            int x = n * 0x28 + 0x48;
            drawMemberIcon(x, 0x70, index);
            drawBattleMemberConditionMarks(&info, x, 0x70);
            n++;
        }
    }
    int param = 0x5c;
    drawMenuPartsAt(s_parts_02177458, &param, 0x20, 0x70);
    drawSelectedCharaHp(BattleMenuPlayerControl::getSingleton()->activeChara_);
    drawBattleCancelButton();
}

THUMB void drawTacticsSelectMenu()
{
    static const int tactics[6] = { (int)0x90000001, (int)0x90000002, (int)0x90000005, (int)0x90000003, (int)0x90000004, (int)0x90000006 };
    drawMenuPartsPlain(s_parts_02177324, 0);
    drawTacticsCommandButton();
    const int* p = tactics;
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 3; i++) {
            int param = *p;
            drawMenuParts(s_parts_02177394, &param, i * 0x40 + 0x24, j * 0x1e + 0x60, 1);
            p++;
        }
    }
    int partyCount = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    int count = 0;
    int list[4] = {0};
    for (int i = 0; i < 4; i++) list[i] = 0;
    for (int i = 0; i < partyCount && count < 4; i++) {
        int index = MenuStatusInfo::getPlayerIndex(i);
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
        if (info.haveStatus_.isPlayer() && index != 1) {
            list[count] = i;
            count++;
        }
    }
    int k;
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    if (chara == -1) {
        for (k = 0; k < count; k++) {
            status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(list[k]);
            int member = list[k];
            drawBattleMemberHpPercent(k * 0x40, 0x38, BattleMenuPlayerControl::getSingleton()->getPartyHP(member), &info);
        }
    }
    drawSelectedCharaHp(chara);
    drawBattleCancelButton();
}

THUMB void drawFormationMenu()
{
    drawMenuPartsPlain(s_parts_021772ec, 0);
    int param[2] = { (int)0xe0000009, (int)0xe000000a };
    drawMenuParts(s_parts_02177482, param, 0x18, 0x78, 1);
    drawFormationCommandButton();
    drawBattleCancelButton();
}

THUMB void drawFormationChangeMemberMenu()
{
    UnkMenuParts window[] = {
        { 0x01, 0x00, (short)0xf000, 0, 0x20, 0x70, 0xc0, 0x30 },
        { 0xff, 0x00, 0, 0, 0, 0, 0, 0 },
    };
    drawMenuPartsPlain(window, 0);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        int x = i * 0x28 + 0x30;
        int index = MenuStatusInfo::getPlayerIndex(i);
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
        drawMemberIcon(x, 0x70, index);
        drawBattleMemberConditionMarks(&info, x, 0x70);
    }
    drawFormationCommandButton();
    drawSelectedCharaHp(BattleMenuPlayerControl::getSingleton()->activeChara_);
    drawBattleCancelButton();
}

THUMB void drawFormationChangeTargetMenu(int* list, int count, int page)
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    drawBattleMemberSelectList(list, count, page);
    drawFormationCommandButton();
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    int hp = BattleMenuPlayerControl::getSingleton()->getPartyHP(chara);
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    drawBattleActiveMember(&info, hp, 0);
    int target = BattleMenuPlayerControl::getSingleton()->targetChara_;
    drawSelectedCharaHp(target);
    drawBattleCharaStatus(0x78, 8, &MenuStatusInfo::getHaveStatusInfo(target));
    drawBattleCancelButton();
}

THUMB void drawFormationAllMenu(int* list, int count, int* order, int orderCount)
{
    MenuStatusInfo::setMode(MenuStatusInfo::SHIFT_MEMBER_MODE);
    drawMenuPartsPlain(s_parts_02177340, 0);
    int n = 0;
    for (int i = 0; i < 4; i++) {
        int x = (i % 2) * 0x48 + 8;
        int y = (i / 2) * 0x30 + 8;
        int number[3];
        number[0] = i + 1;
        number[1] = (int)"\xff\xfe\xa8\x24";
        number[2] = (int)"\xff\xfe\xa6\x24";
        int color = 0;
        if (orderCount > n && *order != -1) {
            status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(*order);
            color = BattleDrawParts_getStatusColor(info);
            int param[4] = { 0, (int)0xe0000016, (int)"\xff\xfe\xa8\x24", 0 };
            param[0] = info.haveStatus_.playerIndex_ + 0x50000000;
            param[3] = info.haveStatus_.level_;
            drawMenuParts(s_parts_021773b0, param, x, y, data_02094dd4[color]);
            drawMenuParts(s_parts_0217752a, param, x, y, data_02094dd4[color]);
            n++;
        }
        drawMenuParts(s_parts_02177500, number, x, y, data_02094dd4[color]);
        order++;
    }
    int target = BattleMenuPlayerControl::getSingleton()->targetChara_;
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    if (target < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL)) {
        drawBattleCharaStatus(0x98, 0, &MenuStatusInfo::getHaveStatusInfo(target));
    }
    drawFormationMemberIcons(list, count);
    drawBattleCancelButton();
}

THUMB void drawPartyHpPercents()
{
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
        drawBattleMemberHpPercent(i * 0x40, 0xa0, BattleMenuPlayerControl::getSingleton()->getPartyHP(i), &info);
    }
}

THUMB void drawFriendSelectMenu(int page, int maxPage, int player)
{
    int list[5] = {-1};
    for (int i = 0; i < 5; i++) list[i] = -1;
    status::g_Party.setBattleModeAndCarriage();
    int count = status::g_Party.getCarriageOutCount() + status::g_Party.getCarriageCount();
    int n = 0;
    int skip = page * 5;
    int max = 5;
    int k;
    status::PlayerData* data = &status::PlayerDataAll::playerData_[player];
    int x = 0x10;
    if (skip == 0) {
        drawBattleMemberIcon(x, 0x70, data->getIconIndex());
        max--;
        x += 0x28;
    }
    k = 0;
    for (int i = 0; i < count; i++) {
        if (k >= max) {
            break;
        }
        status::HaveStatusInfo& info = status::g_Party.getPlayerStatus(i).haveStatusInfo_;
        if (info.haveStatus_.playerType_ == 5) {
            if (n >= skip - 1) {
                list[k] = i;
                drawBattleMemberIcon(x, 0x70, info.getIconIndex());
                drawBattleMemberConditionMarks(&info, x, 0x70);
                k++;
                x += 0x28;
            }
            n++;
        }
    }
    drawFriendSelectPageFrame(page, maxPage);
    int sel = BattleMenuPlayerControl::getSingleton()->activeChara_;
    if (page == 0) {
        sel = sel - 1;
    } else {
        sel = sel - skip;
    }
    if (sel >= 0) {
        status::HaveStatusInfo& info = status::g_Party.getPlayerStatus(list[sel]).haveStatusInfo_;
        status::HaveStatus& status = info.haveStatus_;
        short hp = info.getHp();
        unsigned short hpMax = info.getHpMax();
        unsigned short mp = info.getMp();
        unsigned short mpMax = info.getMpMax();
        drawFriendStatusProfile(hp, mp, hpMax, mpMax, status.getSex(), status.level_, info.haveStatus_.playerIndex_, status.monsterId_);
        drawFriendStatusAbilities(hp, hpMax, status.getStrength(), status.getAgility(), status.getProtection(), status.getWisdom(), status.getLuck(), info.getAttack(0), info.getDefence(0));
        drawFriendStatusItems(&info.haveItem_, hp, hpMax);
        drawFriendStatusSpells(&info.haveAction_, hp, hpMax);
    } else {
        unsigned short hpMax;
        short hp = data->baseStatus_.hp_;
        hpMax = data->baseStatus_.hpMax_;
        int sex;
        int sexId = data->getSexId();
        if (sexId == 1) {
            sex = 0;
        } else if (sexId == 2) {
            sex = 1;
        } else {
            sex = 2;
        }
        drawFriendStatusProfile(hp, data->getMp(), hpMax, data->getMpMax(), sex, data->getLevel(), player, data->getMonsterIndex());
        drawFriendStatusAbilities(hp, hpMax, data->getStrength(), data->getAgility(), data->getProtection(), data->getWisdom(), data->getLuck(), data->getStrength(), data->getProtection());
        drawFriendStatusItems(&data->haveItem_, hp, hpMax);
        drawFriendStatusSpells(&data->haveAction_, hp, hpMax);
    }
}

THUMB void drawEnemyTargetSelect(int group)
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    drawBattleActiveMember(&info, BattleMenuPlayerControl::getSingleton()->getPartyHP(chara), 0);
    drawMonsterNamePlates(group);
    drawBattleCancelButton();
}

THUMB void drawPartyTargetSelect()
{
    drawMenuPartsPlain(s_parts_021775e0, 0);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        drawBattleMemberStatusPanel(&MenuStatusInfo::getHaveStatusInfo(i), i);
    }
    drawBattleCancelButton();
}

THUMB void drawItemList(int* items, int count, int page)
{
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(BattleMenuPlayerControl::getSingleton()->activeChara_);
    int pageMax;
    int top;
    pageMax = (count - 1) / 6;
    int num = (count - 1) % 6 + 1;
    if (pageMax > page) {
        num = 6;
    }
    drawMenuPartsPlain(s_parts_021774d6, 0);
    top = page * 6;
    for (int i = 0; i < num; i++) {
        int x = i % 2;
        int y = i / 2;
        x = x * 120 + 20;
        y = y * 32;
        drawBattleItemEntry(x, y, items[top + i], info.haveItem_.isEquipment(i + top));
    }
    drawBattlePageNumber(0xd8, 0x78, pageMax, page);
    drawBattleHelpMessage(8, 0x74, status::UseItem::getMenuMessage(BattleMenuPlayerControl::getSingleton()->getPlayerItemId()));
    drawBattleCancelButton();
}

THUMB void drawAttackCommandButton()
{
    drawBattleCommandIcon(0x10, 0x40, 0xa0, 0);
}

THUMB void drawMagicCommandHeader()
{
    int useMp;
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    drawBattleActiveMember(&info, BattleMenuPlayerControl::getSingleton()->getPartyHP(chara), 0);
    if (BattleMenuPlayerControl::getSingleton()->getSpecialFlag(chara)) {
        drawBattleCommandIcon(0x100, 0x40, 0xa0, 0);
    } else {
        drawBattleCommandIcon(0x20, 0x40, 0xa0, 0);
    }
    useMp = status::UseAction::getUseMp(info.haveAction_.getAction(BattleMenuPlayerControl::getSingleton()->activeMagic_));
    if (useMp == 0xff) {
        useMp = info.getMp();
        if (useMp == 0) {
            useMp = 1;
        }
    } else if (useMp == 1000) {
        useMp = info.getMp();
    }
    drawBattleMpCost(info.getMp(), useMp);
}

THUMB void drawItemCommandHeader()
{
    int chara = BattleMenuPlayerControl::getSingleton()->activeChara_;
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    drawBattleActiveMember(&info, BattleMenuPlayerControl::getSingleton()->getPartyHP(chara), 0);
    drawBattleCommandIcon(0x40, 0x40, 0xa0, 0);
}

THUMB void drawTacticsCommandButton()
{
    drawBattleCommandIcon(4, 0x40, 0xa0, 0);
}

THUMB void drawFormationCommandButton()
{
    drawBattleCommandIcon(2, 0x40, 0xa0, 0);
}

THUMB void drawFormationMemberIcons(int* list, int count)
{
    drawMenuPartsPlain(s_parts_0217735c, 0);
    for (int i = 0; i < count; i++) {
        int x = (i % 5) * 0x28 + 0x10;
        int y = (i / 5) * 0x28 + 0x68;
        if (*list != -1) {
            status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(*list);
            drawMemberIcon(x, y, MenuStatusInfo::getPlayerIndex(*list));
            drawBattleMemberConditionMarks(&info, x, y);
        } else {
            drawMemberIcon(x, y, -1);
        }
        list++;
    }
}

THUMB void drawSelectedCharaHp(int chara)
{
    if (chara == -1) {
        int param = 0x5000024d;
        drawMenuParts(s_parts_02177404, &param, 0x88, 0xa0, 1);
        return;
    }
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    drawBattleMemberHpPercent(0x88, 0xa0, info.getHp(), &info);
}

THUMB void drawMemberIcon(int x, int y, int index)
{
    int inParty = 0;
    int found = 0;
    MenuStatusInfo::setMode(MenuStatusInfo::BATTLE_MODE);
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_ALL);
    for (int i = 0; i < count; i++) {
        if (index == MenuStatusInfo::getPlayerIndex(i)) {
            if (i < MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT)) {
                inParty = 1;
            }
            found = i;
        }
    }
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(found);
    int param[2];
    param[0] = info.getIconIndex();
    param[1] = found + 1;
    if (index == -1) {
        param[0] = 0x5e;
        drawMenuPartsAt(s_parts_02177554, param, x, y);
        return;
    }
    if (inParty) {
        drawMenuParts(s_parts_021775a8, param, x, y, data_02094dd4[BattleDrawParts_getStatusColor(info)]);
        return;
    }
    drawMenuPartsAt(s_parts_021774ac, param, x, y);
}

THUMB void drawBattleHistory(int chara)
{
    int count = MenuStatusInfo::getPartyCount(MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(i);
        int hp = info.getHp();
        drawBattleTopStatusWindow(&info, hp, info.getMp(), info.haveStatus_.level_, i);
        int first = BattleMenuPlayerControl::getSingleton()->historyData_[i].firstHistory;
        int second = BattleMenuPlayerControl::getSingleton()->historyData_[i].secondHistory;
        drawBattleActionHistory(i, first, second, BattleMenuPlayerControl::getSingleton()->getHPColor(i));
        if (i != chara) {
            drawBattleMemberIconInSlot(i * 0x40 + 8, 0x4a, info.getIconIndex(), i);
        }
    }
    drawMenuPartsPlain(s_parts_021772d0, 0);
}

THUMB void drawCharaBattleSpellList(int* actions, int count, int chara)
{
    status::HaveStatusInfo& info = MenuStatusInfo::getHaveStatusInfo(chara);
    setMenuDrawOffset(0, 0);
    TextAPI::setMACRO0(1, 0x50000000, info.haveStatus_.playerIndex_);
    int message = 0xe000001b;
    drawMenuPartsColored(s_parts_02177618, &message, data_02094dd4[0]);
    for (int i = 0; i < count; i++) {
        int param = actions[i] + 0x70000000;
        drawMenuParts(s_parts_02177308, &param, (i % 2) * 120 + 16, (i / 2) * 16 + 36, data_02094dd4[BattleDrawParts_getStatusColor(info)]);
    }
}

// not in the ROM (dead-stripped), keeps the unused parts list
THUMB void unkfunc_unused_021773da()
{
    drawMenuPartsPlain(s_parts_021773da, 0);
}
