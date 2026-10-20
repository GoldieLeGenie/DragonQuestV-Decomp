#pragma ipa file
#include "main/menu/UnkMenuStatusDraw.hpp"
#include "main/menu/MenuDataCommon.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/menu/UnkMenuPartsDraw.hpp"
#include "main/menu/UnkMenuTemplate.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/PlayerData.hpp"

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

inline unsigned short status::PlayerData::getStrength()
{
    return baseStatus_.strength_;
}

inline unsigned char status::PlayerData::getAgility()
{
    return baseStatus_.agility_;
}

inline unsigned short status::PlayerData::getProtection()
{
    return baseStatus_.protection_;
}

inline unsigned char status::PlayerData::getWisdom()
{
    return baseStatus_.wisdom_;
}

inline unsigned char status::PlayerData::getLuck()
{
    return baseStatus_.luck_;
}

inline unsigned short status::PlayerData::getHp()
{
    return baseStatus_.hp_;
}

inline unsigned short status::PlayerData::getHpMax()
{
    return baseStatus_.hpMax_;
}

inline unsigned short status::PlayerData::getMp()
{
    return baseStatus_.mp_;
}

inline unsigned short status::PlayerData::getMpMax()
{
    return baseStatus_.mpMax_;
}

inline unsigned char status::PlayerData::getLevel()
{
    return baseStatus_.level_;
}

#define PARTS_END {0xff, 0x00, 0x0000, 0, 0x00, 0x00, 0x00, 0x00}

static UnkMenuParts s_actionTitleParts[] = {
    {0x0d, 0x09, (short)0xf000, 0, 0x08, 0x10, 0xf0, 0x18},
    PARTS_END,
};

static UnkMenuParts s_statusParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0xd0, 0x08, 0x10, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0xdc, 0x08, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0xdc, 0x08, 0x18, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_faceParts[] = {
    {0x0a, 0x00, 0x0000, 0, 0x00, 0x00, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_equipParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x6a, 0x10, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x60, 0x10},
    PARTS_END,
};

static UnkMenuParts s_timeParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x5b, 0x78, 0x10},
    {0x0f, 0x0a, (short)0xf000, 1, 0xb8, 0x5b, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 2, 0xc0, 0x5b, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 3, 0xc8, 0x5b, 0x08, 0x10},
    {0x0d, 0x0a, (short)0xf000, 4, 0xd0, 0x5b, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 5, 0xd8, 0x5b, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 6, 0xe0, 0x5b, 0x08, 0x10},
    PARTS_END,
};

static UnkMenuParts s_attackParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0xa0, 0xaa, 0x10, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_coinParts[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x00, 0xaa, 0x40, 0x0c},
    PARTS_END,
};

static UnkMenuParts s_goldParts2[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0xb6, 0x8a, 0x38, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_attackDefenceParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x08, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x18, 0x30, 0x10},
    {0x0f, 0x0a, (short)0xf000, 2, 0x18, 0x24, 0x20, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x30, 0x28, 0x10},
    {0x0f, 0x0a, (short)0xf000, 4, 0x18, 0x3c, 0x20, 0x10},
    PARTS_END,
};

static UnkMenuParts s_conditionParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x20, 0x00, 0x0e, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_hpMpParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x08, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x1c, 0x18, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x08, 0x3c, 0x18, 0x10},
    {0x0f, 0x0a, (short)0xf000, 3, 0x18, 0x16, 0x20, 0x10},
    {0x0d, 0x0a, (short)0xf000, 4, 0x20, 0x20, 0x08, 0x08},
    {0x0d, 0x0a, (short)0xf000, 5, 0x28, 0x20, 0x08, 0x08},
    {0x0d, 0x0a, (short)0xf000, 6, 0x30, 0x20, 0x08, 0x08},
    {0x0f, 0x0a, (short)0xf000, 7, 0x18, 0x28, 0x20, 0x10},
    {0x0f, 0x0a, (short)0xf000, 8, 0x18, 0x36, 0x20, 0x10},
    {0x0d, 0x0a, (short)0xf000, 9, 0x20, 0x40, 0x08, 0x08},
    {0x0d, 0x0a, (short)0xf000, 10, 0x28, 0x40, 0x08, 0x08},
    {0x0d, 0x0a, (short)0xf000, 11, 0x30, 0x40, 0x08, 0x08},
    {0x0f, 0x0a, (short)0xf000, 12, 0x18, 0x48, 0x20, 0x10},
    PARTS_END,
};

static UnkMenuParts s_statusDetailParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0x58, 0x0a, 0x10, 0x10},
    {0x0d, 0x08, (short)0xf000, 2, 0x68, 0x0a, 0x28, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x38, 0x24, 0x58, 0x10},
    {0x0d, 0x08, (short)0xf000, 4, 0x38, 0x34, 0x28, 0x10},
    {0x0d, 0x0b, (short)0xf000, 5, 0x00, 0x00, 0x08, 0x10},
    {0x0d, 0x0b, (short)0xf000, 6, 0x00, 0x00, 0x28, 0x10},
    {0x0d, 0x08, (short)0xf000, 7, 0x38, 0x42, 0x28, 0x10},
    {0x0d, 0x0b, (short)0xf000, 8, 0x00, 0x00, 0x08, 0x10},
    {0x0f, 0x0b, (short)0xf000, 17, 0x00, 0x00, 0x28, 0x10},
    {0x0d, 0x08, (short)0xf000, 9, 0x38, 0x4f, 0x18, 0x10},
    {0x0f, 0x0a, (short)0xf000, 10, 0x48, 0x4f, 0x20, 0x10},
    {0x0d, 0x0b, (short)0xf000, 11, 0x00, 0x00, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 12, 0x68, 0x4f, 0x20, 0x10},
    {0x0d, 0x08, (short)0xf000, 13, 0x38, 0x5c, 0x18, 0x10},
    {0x0f, 0x0a, (short)0xf000, 14, 0x48, 0x5c, 0x20, 0x10},
    {0x0d, 0x0b, (short)0xf000, 15, 0x00, 0x00, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 16, 0x68, 0x5c, 0x20, 0x10},
    PARTS_END,
};

static UnkMenuParts s_iconParts[] = {
    {0x14, 0xc0, 0x0000, -1, 0x04, 0x10, 0x20, 0x18},
    {0x0c, 0xf1, 0x0000, 0, 0x00, 0x00, 0x20, 0x20},
    PARTS_END,
};

static UnkMenuParts s_moneyParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x10, 0x08, 0x90, 0x10},
    {0x0d, 0x08, (short)0xf000, 1, 0xa0, 0x08, 0x10, 0x10},
    {0x0f, 0x0a, (short)0xf000, 2, 0xa8, 0x08, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 3, 0x10, 0x18, 0x90, 0x10},
    {0x0d, 0x08, (short)0xf000, 4, 0xa0, 0x18, 0x10, 0x10},
    {0x0f, 0x0a, (short)0xf000, 5, 0xa8, 0x18, 0x40, 0x10},
    {0x0d, 0x08, (short)0xf000, 6, 0x10, 0x30, 0x90, 0x10},
    {0x0f, 0x0a, (short)0xf000, 7, 0xa0, 0x30, 0x48, 0x10},
    {0x0d, 0x0a, (short)0xf000, 8, 0xe8, 0x30, 0x10, 0x10},
    {0x0d, 0x08, (short)0xf000, 9, 0x10, 0x40, 0x90, 0x10},
    {0x0f, 0x0a, (short)0xf000, 10, 0x90, 0x40, 0x58, 0x10},
    {0x0d, 0x0a, (short)0xf000, 11, 0xe8, 0x40, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_actionListParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x0c, 0x68, 0x48, 0x10},
    PARTS_END,
};

static UnkMenuParts s_unusedParts[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x60, 0x42, 0x18, 0x10},
    PARTS_END,
};

static UnkMenuParts s_abilityParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0xa0, 0x08, 0x30, 0x10},
    {0x0d, 0x0a, (short)0xf000, 1, 0xd8, 0x08, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 2, 0xe0, 0x08, 0x18, 0x10},
    PARTS_END,
};

static UnkMenuParts s_memberParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x30, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x20, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0x10, 0x20, 0x28, 0x0a},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x2e, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 4, 0x10, 0x2e, 0x28, 0x0a},
    {0x0d, 0x08, (short)0xf000, 5, 0x08, 0x3c, 0x10, 0x0a},
    {0x0d, 0x0b, (short)0xf000, 6, 0x00, 0x00, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 7, 0x10, 0x3c, 0x28, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_numberParts[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x08, 0x08, 0x10, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_memberAltParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x0a, 0x30, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x08, 0x20, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0x10, 0x20, 0x28, 0x0a},
    {0x0d, 0x08, (short)0xf000, 3, 0x08, 0x2e, 0x10, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 4, 0x10, 0x2e, 0x28, 0x0a},
    {0x0d, 0x08, (short)0xf000, 5, 0x08, 0x3c, 0x30, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_statusAltParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0xd0, 0x08, 0x38, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_levelParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x03, 0x10, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x08, 0x00, 0x08, 0x10},
    {0x0f, 0x0a, (short)0xf000, 2, 0x18, 0x03, 0x20, 0x10},
    PARTS_END,
};

static UnkMenuParts s_equipMarkParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x0c, 0x08, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_frameParts[] = {
    {0x01, 0x00, (short)0xf000, 0, 0x00, 0x00, 0x00, 0x00},
    PARTS_END,
};

static UnkMenuParts s_statusBigParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x9c, 0x08, 0x30, 0x0a},
    {0x0d, 0x08, (short)0xf000, 1, 0x9c, 0x20, 0x18, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 2, 0xb4, 0x20, 0x20, 0x0a},
    {0x0d, 0x08, (short)0xf000, 3, 0xd4, 0x20, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 4, 0xd4, 0x20, 0x20, 0x0a},
    {0x0d, 0x08, (short)0xf000, 5, 0x9c, 0x2e, 0x18, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 6, 0xb4, 0x2e, 0x20, 0x0a},
    {0x0d, 0x08, (short)0xf000, 7, 0xd4, 0x2e, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 8, 0xd4, 0x2e, 0x20, 0x0a},
    {0x0d, 0x08, (short)0xf000, 9, 0x9c, 0x42, 0x38, 0x0a},
    {0x0d, 0x08, (short)0xf000, 10, 0xd4, 0x42, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 11, 0xd4, 0x42, 0x20, 0x0a},
    {0x0d, 0x08, (short)0xf000, 12, 0x9c, 0x50, 0x38, 0x0a},
    {0x0d, 0x08, (short)0xf000, 13, 0xd4, 0x50, 0x08, 0x0a},
    {0x0f, 0x0a, (short)0xf000, 14, 0xd4, 0x50, 0x20, 0x0a},
    PARTS_END,
};

static UnkMenuParts s_expParts[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0xc0, 0xaa, 0x38, 0x10},
    PARTS_END,
};

static UnkMenuParts s_numberParts2[] = {
    {0x0f, 0x08, (short)0xf000, 0, 0x08, 0x08, 0x10, 0x10},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x10, 0x10},
    PARTS_END,
};

static UnkMenuParts s_levelAltParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x08, 0x04, 0x30, 0x10},
    PARTS_END,
};

static UnkMenuParts s_itemParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x14, 0x08, 0x60, 0x10},
    PARTS_END,
};

static UnkMenuParts s_actionNameParts[] = {
    {0x0d, 0x08, (short)0xf000, 0, 0x20, 0x00, 0x80, 0x10},
    PARTS_END,
};

static UnkMenuParts s_goldParts[] = {
    {0x0f, 0x0a, (short)0xf000, 0, 0x00, 0xaa, 0x40, 0x0c},
    {0x0d, 0x0b, (short)0xf000, 1, 0x00, 0x00, 0x10, 0x0c},
    PARTS_END,
};

THUMB void drawMenuFrame(int x, int y, int w, int h, int lineY)
{
    s_frameParts[0].x_ = x;
    s_frameParts[0].y_ = y;
    s_frameParts[0].w_ = w;
    s_frameParts[0].h_ = h;
    unkfunc_0206297c(s_frameParts, NULL);
    if (lineY > 0) {
        drawMenuFrameLine(x, lineY, w);
    }
}

THUMB void drawMenuFrameLine(int x, int y, int w)
{
    UnkMenuParts parts[] = {
        {0x16, 0x00, (short)0xf000, 0, 0x00, 0x00, 0x00, 0x00},
        PARTS_END,
    };
    parts[0].x_ = x;
    parts[0].y_ = y;
    parts[0].w_ = w;
    unkfunc_0206297c(parts, NULL);
}

THUMB void drawPartyStatusWindows()
{
    unsigned int mode = menu::MenuStatusInfo::getMode();
    menu::MenuStatusInfo::setMode(menu::MenuStatusInfo::BATTLE_MODE);
    int count = menu::MenuStatusInfo::getPartyCount(menu::MenuStatusInfo::COUNT_CARRIAGE_OUT);
    for (int i = 0; i < count; i++) {
        unkfunc_0201c188(i, i);
        drawMenuFrame(i * 0x40, 0, 0x40, 0x50, 0x18);
    }
    menu::MenuStatusInfo::setMode(mode);
}

THUMB int getActorConditionColor(int actor)
{
    int color = 0;
    if (menu::MenuStatusInfo::isPlayerCondition(actor, menu::MenuStatusInfo::CONDITION_DEATH) == true) {
        color = 2;
    } else if (menu::MenuStatusInfo::isPlayerCondition(actor, menu::MenuStatusInfo::CONDITION_NEARDEATH) == true) {
        color = 1;
    }
    return color;
}

THUMB void drawMoneyWindow(int x, int y, int type)
{
    UnkMenuParts* parts = s_goldParts;
    int param[2] = {0, 0xe0000071};
    param[0] = menu::MenuStatusInfo::getGold();
    if (type == 1) {
        param[0] = menu::MenuStatusInfo::getCoin();
        param[1] = 0;
        parts = s_coinParts;
    }
    if (type == 2) {
        param[0] = menu::MenuStatusInfo::getMedal();
        param[1] = 0;
        parts = s_coinParts;
    }
    if (g_AreaFlag.check(0x82) && !g_AreaFlag.check(0x84)) {
        param[0] = 0;
    }
    if (x == -1 && y == -1) {
        parts[0].x_ = 0xb6;
        if (type != 1) {
            parts[0].w_ = 0x38;
        }
        unkfunc_02061c5c(0, 0);
        unkfunc_020629a4(parts, param, data_02094dd4[0]);
        drawMenuFrame(0xb0, 0xa0, 0x50, 0x20, -1);
    } else {
        parts[0].x_ = x + 6;
        if (type != 1) {
            parts[0].w_ = 0x38;
        }
        unkfunc_020629a4(parts, param, data_02094dd4[0]);
        drawMenuFrame(x, y, 0x50, 0x20, -1);
    }
}

THUMB void drawCharaStatusWindow(int activeChara, int mode)
{
    UnkMenuParts* parts = s_statusParts;
    int x = 0;
    int y = 0;
    int frameX = 0x90;
    int frameY = 0;
    int lineY = 0x18;
    if (mode == 1) {
        unkfunc_02061c5c(0, 0);
        x -= 0x90;
        y += 0x58;
        frameX = 0;
        frameY = 0x58;
        lineY = 0x70;
    }
    status::HaveStatusInfo& info = menu::MenuStatusInfo::getHaveStatusInfo(activeChara);
    int param[15] = {
        0, 0xe0000014, 0, (int)"\xff\xfe\xa7\x24", 0, 0xe0000015, 0, (int)"\xff\xfe\xa7\x24", 0, 0xe0000019, (int)"\xff\xfe\xa8\x24", 0, 0xe000001a, (int)"\xff\xfe\xa8\x24", 0,
    };
    param[0] = menu::MenuStatusInfo::getPlayerIndex(activeChara) + 0x50000000;
    param[2] = info.haveStatus_.getHp();
    param[4] = info.haveStatus_.getHpMax();
    param[6] = info.haveStatus_.getMp();
    param[8] = info.haveStatus_.getMpMax();
    param[11] = info.getAttack(0);
    param[14] = info.getDefence(0);
    int level[3] = {0xe0000016, (int)"\xff\xfe\xa8\x24", 0};
    level[2] = info.haveStatus_.level_;
    int condition = menu::MenuDataCommon::getPlayerCondition(activeChara);
    if (condition != 0) {
        level[0] = condition;
        parts = s_statusAltParts;
    }
    unkfunc_020629b4(s_statusBigParts, param, x, y, data_02094dd4[getActorConditionColor(activeChara)]);
    unkfunc_020629b4(parts, level, x, y, data_02094dd4[getActorConditionColor(activeChara)]);
    drawMenuFrame(frameX, frameY, 0x70, 0x68, lineY);
}

THUMB void unkfunc_0201b3c8(int icon, int x, int y)
{
    int param = icon;
    unkfunc_02062990(s_iconParts, &param, x, y);
}

THUMB void unkfunc_0201b3e4(int activeChara, int x, int y)
{
    int color = 0;
    int param = 0;
    switch (activeChara) {
        case -1:
            param = 0x5d;
            break;
        case -2:
            param = 0x5c;
            break;
        case -3:
            param = 0x5e;
            break;
        default:
            param = menu::MenuStatusInfo::getPlayerIconIndex(activeChara);
            color = getActorConditionColor(activeChara);
            break;
    }
    unkfunc_0201b3c8(param, x, y);
    if (activeChara > -1) {
        if (menu::MenuStatusInfo::isPlayerCondition(activeChara, menu::MenuStatusInfo::CONDITION_SPELL) == true ||
            menu::MenuStatusInfo::isPlayerCondition(activeChara, menu::MenuStatusInfo::CONDITION_ITEM_SPELL) == true) {
            param = 0xe0000039;
            unkfunc_020629b4(s_conditionParts, &param, x - 6, y + 0x14, data_02094dd4[color]);
        }
        if (color == 2) {
            param = 0xe0000037;
            y += 8;
            unkfunc_020629b4(s_conditionParts, &param, x - 6, y, data_02094dd4[color]);
            return;
        }
        if (menu::MenuStatusInfo::isPlayerCondition(activeChara, menu::MenuStatusInfo::CONDITION_POISON) == true ||
            menu::MenuStatusInfo::isPlayerCondition(activeChara, menu::MenuStatusInfo::CONDITION_VENOM) == true) {
            param = 0xe0000038;
            y += 8;
            unkfunc_020629b4(s_conditionParts, &param, x - 6, y, data_02094dd4[color]);
        }
    }
}

THUMB void unkfunc_0201b4d4(int activeChara, int flag, int ctrl)
{
    int param[18] = {-1};
    for (int i = 0; i < 18; i++) {
        param[i] = -1;
    }
    int icon;
    int level;
    int color;
    param[1] = (int)"\xff\xfe\xac\x24";
    param[2] = 0xe0000123;
    param[4] = 0xe0000113;
    param[5] = (int)"\xff\xfe\xa8\x24";
    param[6] = (int)"???";
    param[7] = 0xe0000118;
    param[8] = (int)"\xff\xfe\xa8\x24";
    param[9] = 0xe0000014;
    param[11] = (int)"\xff\xfe\xa7\x24";
    param[13] = 0xe0000015;
    param[15] = (int)"\xff\xfe\xa7\x24";
    color = 0;
    icon = 0;
    if (activeChara == 999) {
        int index = status::PlayerDataAll::getCtrlFromFriendMonsterIndex(ctrl);
        status::PlayerData& playerData = status::PlayerDataAll::playerData_[index];
        int job = playerData.getJob();
        icon = playerData.getIconIndex();
        int jobName;
        switch (playerData.getKindIndex()) {
            case 0x3a:
            case 0x3b:
                jobName = 0xe000010b;
                break;
            case 0x52:
                jobName = 0xe000010c;
                break;
            default:
                jobName = job + 0x60000000;
                break;
        }
        param[0] = index + 0x50000000;
        param[3] = jobName;
        param[10] = playerData.getHp();
        param[12] = playerData.getHpMax();
        param[14] = playerData.getMp();
        param[16] = playerData.getMpMax();
        switch (playerData.getSexId()) {
            case 0x114:
                param[6] = 0xe0000114;
                break;
            case 0x115:
                param[6] = 0xe0000115;
                break;
        }
        level = playerData.getLevel();
    } else {
        menu::MenuStatusInfo::getHaveStatusInfo(activeChara);
        icon = menu::MenuStatusInfo::getPlayerIconIndex(activeChara);
        param[0] = menu::MenuStatusInfo::getPlayerIndex(activeChara) + 0x50000000;
        param[3] = menu::MenuDataCommon::getPlayerJob(activeChara);
        param[10] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::NOWHP, color);
        param[12] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::MAXHP, color);
        param[14] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::NOWMP, color);
        param[16] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::MAXMP, color);
        if (flag == 0) {
            param[2] = 0xe0000066;
        }
        switch (menu::MenuStatusInfo::getPlayerSex(activeChara)) {
            case 0x114:
                param[6] = 0xe0000114;
                break;
            case 0x115:
                param[6] = 0xe0000115;
                break;
        }
        level = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::LEVEL, false);
        color = getActorConditionColor(activeChara);
    }
    param[17] = level;
    unkfunc_020629a4(s_statusDetailParts, param, data_02094dd4[color]);
    unkfunc_02062990(s_faceParts, &icon, 6, 0x28);
    drawMenuFrame(0, 0, 0x98, 0x70, 0x18);
}

THUMB void unkfunc_0201b6b4(int activeChara, int ctrl)
{
    int order[7] = {2, 3, 4, 5, 6, 0, 1};
    int param[3] = {-1};
    for (int i = 0; i < 3; i++) {
        param[i] = -1;
    }
    if (activeChara == 999) {
        status::PlayerData& playerData = status::PlayerDataAll::playerData_[status::PlayerDataAll::getCtrlFromFriendMonsterIndex(ctrl)];
        int value[7];
        value[0] = playerData.getStrength();
        value[1] = playerData.getAgility();
        value[2] = playerData.getProtection();
        value[3] = playerData.getWisdom();
        value[4] = playerData.getLuck();
        value[5] = playerData.getAttack();
        value[6] = playerData.getDefence();
        for (int i = 0; i < 7; i++) {
            param[0] = menu::MenuDataCommon::getAbilityKind((menu::MenuDataCommon::STATUS_INDEX)order[i]);
            param[1] = (int)"\xff\xfe\xa8\x24";
            param[2] = value[i];
            unkfunc_020629b4(s_abilityParts, param, 0, i * 0xe, data_02094dd4[0]);
        }
    } else {
        for (int i = 0; i < 7; i++) {
            param[0] = menu::MenuDataCommon::getAbilityKind((menu::MenuDataCommon::STATUS_INDEX)order[i]);
            param[1] = (int)"\xff\xfe\xa8\x24";
            param[2] = menu::MenuDataCommon::getStatus(activeChara, (menu::MenuDataCommon::STATUS_INDEX)order[i], false);
            unkfunc_020629b4(s_abilityParts, param, 0, i * 0xe, data_02094dd4[getActorConditionColor(activeChara)]);
        }
    }
    drawMenuFrame(0x98, 0, 0x68, 0x70, -1);
}

THUMB void unkfunc_0201b7dc(int activeChara, int mode)
{
    unkfunc_02061c5c(0, 0);
    int equip[5] = {-1};
    for (int i = 0; i < 5; i++) {
        equip[i] = -1;
    }
    for (int i = 0; i < 5; i++) {
        int id = menu::MenuStatusInfo::getPlayerEquipItemID(activeChara, (ItemType)i, 0);
        if (id != 0) {
            equip[i] = id;
        }
    }
    int count = 0;
    int accessory[7] = {0};
    for (int i = 0; i < 7; i++) {
        accessory[i] = 0;
    }
    for (int i = 0; i < 7; i++) {
        accessory[i] = menu::MenuStatusInfo::getPlayerEquipItemID(activeChara, (ItemType)4, i);
        if (accessory[i] != 0) {
            count++;
        }
    }
    int param[2] = {0};
    for (int i = 0; i < 2; i++) {
        param[i] = 0;
    }
    int* e = equip;
    for (int i = 0, y = 0; i < 5; e++, i++, y += 0x10) {
        if (*e != -1) {
            int x = 0;
            int py = y;
            if (count > 1) {
                py = y - ((count - 1) << 4);
            }
            param[0] = 0xe000003c;
            param[1] = *e + 0x40000000;
            if (mode == 1) {
                x = 0x68;
            }
            unkfunc_020629b4(s_equipParts, param, x, py, data_02094dd4[getActorConditionColor(activeChara)]);
        }
    }
    int frameY = 0x60;
    int frameH = 0x60;
    if (count > 1) {
        int i = 1;
        int* a = &accessory[1];
        for (int y = 0x50; i < 7; a++, i++, y += 0x10) {
            if (*a != 0) {
                int py = y - ((count - 1) << 4);
                int x = 0;
                if (mode == 1) {
                    x = 0x68;
                }
                param[1] = *a + 0x40000000;
                unkfunc_020629b4(s_equipParts, param, x, py, data_02094dd4[getActorConditionColor(activeChara)]);
            }
        }
        frameY = frameY - ((count - 1) << 4);
        frameH = frameH + ((count - 1) << 4);
    }
    if (mode == 1) {
        drawMenuFrame(0x68, frameY, 0x98, frameH, -1);
        return;
    }
    drawMenuFrame(0, frameY, 0x98, frameH, -1);
    param[0] = 0xe0000124;
    param[1] = (int)"\xff\xfe\xa8\x24";
    unkfunc_020629a4(s_attackParts, param, data_02094dd4[getActorConditionColor(activeChara)]);
    int exp = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::EXP, false);
    unkfunc_020629a4(s_expParts, &exp, data_02094dd4[getActorConditionColor(activeChara)]);
    param[0] = menu::MenuStatusInfo::getGold();
    param[1] = 0xe0000071;
    if (g_AreaFlag.check(0x82) && !g_AreaFlag.check(0x84)) {
        param[0] = 0;
    }
    unkfunc_020629a4(s_goldParts2, param, data_02094dd4[getActorConditionColor(activeChara)]);
    drawMenuFrame(0x98, 0xa0, 0x68, 0x20, -1);
    drawMenuFrame(0x98, 0x80, 0x68, 0x20, -1);
}

THUMB void unkfunc_0201ba48(int activeChara, int mode)
{
    int title = 0;
    status::HaveAction::ActionMode actionMode = status::HaveAction::getActionMode();
    if (mode == 1) {
        unkfunc_02061c5c(0, 0);
        title = 0xe000001b;
        if (menu::MenuStatusInfo::isPlayerType(activeChara, menu::MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
            title = 0xe000001c;
        }
        unkfunc_020629a4(s_actionTitleParts, &title, data_02094dd4[0]);
        status::HaveAction::setBattleMode();
        int count = menu::MenuStatusInfo::getPlayerActionCount(activeChara, menu::MenuStatusInfo::USE_BATTLE);
        for (int i = 0; i < count; i++) {
            int param = menu::MenuStatusInfo::getWordDBIndex(menu::MenuStatusInfo::getPlayerActionID(activeChara, i)) + 0x70000000;
            unkfunc_020629b4(s_actionNameParts, &param, (i % 2) << 7, (i / 2) * 0xc + 0x34, data_02094dd4[getActorConditionColor(activeChara)]);
        }
    } else {
        title = 0xe000012c;
        if (menu::MenuStatusInfo::isPlayerType(activeChara, menu::MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
            title = 0xe000012e;
        }
        unkfunc_020629a4(s_actionTitleParts, &title, data_02094dd4[0]);
        status::HaveAction::setTownMode();
        int count = menu::MenuStatusInfo::getPlayerActionCount(activeChara, menu::MenuStatusInfo::USE_TOWN);
        for (int i = 0; i < count; i++) {
            int param = menu::MenuStatusInfo::getWordDBIndex(menu::MenuStatusInfo::getPlayerActionID(activeChara, i)) + 0x70000000;
            unkfunc_020629b4(s_actionNameParts, &param, (i % 2) << 7, (i / 2) * 0xc + 0x34, data_02094dd4[getActorConditionColor(activeChara)]);
        }
    }
    status::HaveAction::setActionMode(actionMode);
    if (mode == 1) {
        drawMenuFrame(0, 0, 0x100, 0xc0, 0x28);
    } else {
        drawMenuFrame(0, 0, 0x100, 0x70, 0x28);
    }
}

THUMB void unkfunc_0201bbb4()
{
    int money[12] = {
        0xe0000140, (int)"\xff\xfe\xa9\x24", 0, 0xe0000141, (int)"\xff\xfe\xa9\x24", 0, 0xe0000142, 0, 0xe0000071, 0xe0000143, 0, 0xe0000071,
    };
    money[2] = menu::MenuStatusInfo::getCoin();
    money[5] = menu::MenuStatusInfo::getMedal();
    money[7] = menu::MenuStatusInfo::getGold();
    money[10] = menu::MenuStatusInfo::getBank();
    if (g_AreaFlag.check(0x82) && !g_AreaFlag.check(0x84)) {
        money[2] = 0;
        money[5] = 0;
        money[7] = 0;
    }
    int time = status::g_Game.getPlayTime();
    int hour = time / 216000;
    int minute = (time % 216000) / 3600;
    int param[7] = {0xe0000144, 0, 0, 0, (int)"\xff\xfe\xa8\x24", 0, 0};
    param[1] = hour / 100;
    param[2] = (hour / 10) % 10;
    param[3] = hour % 10;
    param[5] = minute / 10;
    param[6] = minute % 10;
    unkfunc_020629a4(s_moneyParts, money, data_02094dd4[0]);
    unkfunc_020629a4(s_timeParts, param, data_02094dd4[0]);
    drawMenuFrame(0, 0, 0x100, 0x70, 0x28);
    drawMenuFrameLine(0, 0x50, 0x100);
}

THUMB void unkfunc_0201bcc8(int mode)
{
    int count = menu::MenuStatusInfo::getPartyCount(menu::MenuStatusInfo::COUNT_ALL);
    int param[2] = {0, (int)"\xff\xfe\xa8\x24"};
    int top;
    if (count > 4) {
        top = 4;
    } else {
        top = count;
    }
    if (mode == 1) {
        top = 1;
    }
    for (int i = 0; i < top; i++) {
        param[0] = i + 1;
        unkfunc_020629b4(s_numberParts, param, i << 6, 0, data_02094dd4[getActorConditionColor(i)]);
        unkfunc_0201c218(i, i << 6, 0x10);
    }
    if (count < 5) {
        if (mode == 1) {
            drawMenuFrame(0, 0, 0x40, 0x70, -1);
            return;
        }
        drawMenuFrame(0, 0, count << 6, 0x70, -1);
        return;
    }
    drawMenuFrame(0, 0, 0x100, 0x70, -1);
    unkfunc_02061c5c(0, 0);
    int rest = count - 4;
    if (rest > 4) {
        for (int i = 0; i < 4; i++) {
            unkfunc_0201c218(i + 4, i << 6, 0x60);
        }
        drawMenuFrame(0, 0x60, 0x100, 0x60, -1);
        int rest2 = count - 8;
        for (int i = 0; i < rest2; i++) {
            unkfunc_0201c218(i + 8, i << 6, 0);
        }
        drawMenuFrame(0, 0, (rest2 - 4) << 6, 0x60, -1);
        return;
    }
    for (int i = 0; i < rest; i++) {
        unkfunc_0201c218(i + 4, i << 6, 0x60);
    }
    drawMenuFrame(0, 0x60, rest << 6, 0x60, -1);
}

THUMB void unkfunc_0201be24(int mode)
{
    int count = menu::MenuStatusInfo::getPartyCount(menu::MenuStatusInfo::COUNT_ALL);
    int param[2] = {0, (int)"\xff\xfe\xa8\x24"};
    int top;
    if (count > 4) {
        top = 4;
    } else {
        top = count;
    }
    if (mode == 1) {
        top = 1;
    }
    for (int i = 0; i < top; i++) {
        param[0] = i + 1;
        unkfunc_020629b4(s_numberParts2, param, i << 6, 0, data_02094dd4[getActorConditionColor(i)]);
        unkfunc_0201c300(i, i, 0x40, 0x58);
        unkfunc_0201c29c(i, i << 6, 0x10);
    }
    if (count < 5) {
        if (mode == 1) {
            drawMenuFrame(0, 0, 0x40, 0x70, -1);
            return;
        }
        drawMenuFrame(0, 0, count << 6, 0x70, -1);
        return;
    }
    drawMenuFrame(0, 0, 0x100, 0x70, -1);
    unkfunc_02061c5c(0, 0);
    int rest = count - 4;
    if (rest > 4) {
        for (int i = 0; i < 4; i++) {
            unkfunc_0201c29c(i + 4, i << 6, 0x60);
            unkfunc_0201c300(i + 4, i, 0x40, 0xa8);
        }
        drawMenuFrame(0, 0x60, 0x100, 0x60, -1);
        count = menu::MenuStatusInfo::getPartyCount(menu::MenuStatusInfo::COUNT_ALL) - 8;
        for (int i = 0; i < count; i++) {
            int index = i + 8;
            unkfunc_0201c29c(index, i << 6, 0);
            unkfunc_0201c300(index, i, 0x40, 0x48);
        }
        drawMenuFrame(0, 0, (count - 4) << 6, 0x60, -1);
        return;
    }
    for (int i = 0; i < rest; i++) {
        unkfunc_0201c29c(i + 4, i << 6, 0x60);
        unkfunc_0201c300(i + 4, i, 0x40, 0xa8);
    }
    drawMenuFrame(0, 0x60, rest << 6, 0x60, -1);
}

THUMB void unkfunc_0201bfbc(int activeChara)
{
    unkfunc_02061c5c(0, 0);
    if (activeChara != 999) {
        int count = menu::MenuStatusInfo::getPlayerItemCount(activeChara);
        int param = 0;
        for (int i = 0; i < count; i++) {
            param = menu::MenuStatusInfo::getPlayerItemID(activeChara, i) + 0x40000000;
            int x = (i % 2) * 0x78;
            int y = (i / 2) * 8 + (i / 2) * 5;
            if (menu::MenuStatusInfo::isPlayerEquipItemIndex(activeChara, i) == true) {
                int mark = 0xe000003c;
                unkfunc_020629b4(s_equipMarkParts, &mark, x, y, data_02094dd4[getActorConditionColor(activeChara)]);
            }
            unkfunc_020629b4(s_itemParts, &param, x, y, data_02094dd4[getActorConditionColor(activeChara)]);
        }
    }
    drawMenuFrame(0, 0, 0xf0, 0x60, -1);
}

THUMB void unkfunc_0201c084(int activeChara, int ctrl)
{
    unkfunc_02061c5c(0, 0);
    int param = 0;
    if (activeChara == 999) {
        int count;
        status::HaveAction* action = &status::PlayerDataAll::playerData_[status::PlayerDataAll::getCtrlFromFriendMonsterIndex(ctrl)].haveAction_;
        count = action->getCountAll();
        for (int i = 0; i < count; i++) {
            param = action->getActionAll(i) + 0x70000000;
            unkfunc_020629b4(s_actionListParts, &param, (i % 3) * 0x50, (i / 3) * 0xc, data_02094dd4[0]);
        }
    } else {
        int count = menu::MenuStatusInfo::getPlayerActionCount(activeChara, menu::MenuStatusInfo::USE_ALL);
        for (int i = 0; i < count; i++) {
            param = menu::MenuStatusInfo::getPlayerActionID(activeChara, i, menu::MenuStatusInfo::USE_ALL) + 0x70000000;
            int color = getActorConditionColor(activeChara);
            unkfunc_020629b4(s_actionListParts, &param, (i % 3) * 0x50, (i / 3) * 0xc, data_02094dd4[color]);
        }
    }
    drawMenuFrame(0, 0x60, 0x100, 0x60, -1);
}

THUMB void unkfunc_0201c188(int activeChara, int pos)
{
    unkfunc_02061c5c(0, 0);
    UnkMenuParts* parts = s_memberParts;
    status::HaveStatusInfo& info = menu::MenuStatusInfo::getHaveStatusInfo(activeChara);
    int param[8] = {0, 0xe0000014, 0, 0xe0000015, 0, 0xe0000016, (int)"\xff\xfe\xa8\x24", 0};
    param[0] = menu::MenuStatusInfo::getPlayerIndex(activeChara) + 0x50000000;
    param[2] = info.getHp();
    param[4] = info.getMp();
    param[7] = info.haveStatus_.level_;
    int condition = menu::MenuDataCommon::getPlayerCondition(activeChara);
    if (condition != 0) {
        parts = s_memberAltParts;
        param[5] = condition;
    }
    unkfunc_020629b4(parts, param, pos << 6, 0, data_02094dd4[getActorConditionColor(activeChara)]);
}

THUMB void unkfunc_0201c218(int activeChara, int x, int y)
{
    int param[13] = {
        0, 0xe0000014, 0xe0000015, 0, (int)"@\x81\x5c", (int)"@\x81\x5c", (int)"@\x81\x5c", 0, 0, (int)"@\x81\x5c", (int)"@\x81\x5c", (int)"@\x81\x5c", 0,
    };
    param[0] = menu::MenuStatusInfo::getPlayerIndex(activeChara) + 0x50000000;
    param[3] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::NOWHP, false);
    param[7] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::MAXHP, false);
    param[8] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::NOWMP, false);
    param[12] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::MAXMP, false);
    unkfunc_020629b4(s_hpMpParts, param, x, y, data_02094dd4[getActorConditionColor(activeChara)]);
}

THUMB void unkfunc_0201c29c(int activeChara, int x, int y)
{
    int param[5];
    param[0] = menu::MenuStatusInfo::getPlayerIndex(activeChara) + 0x50000000;
    param[1] = menu::MenuDataCommon::getAbilityKind(menu::MenuDataCommon::ATTACK);
    param[2] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::ATTACK, false);
    param[3] = menu::MenuDataCommon::getAbilityKind(menu::MenuDataCommon::DEFENCE);
    param[4] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::DEFENCE, false);
    unkfunc_020629b4(s_attackDefenceParts, param, x, y, data_02094dd4[getActorConditionColor(activeChara)]);
}

THUMB void unkfunc_0201c300(int activeChara, int pos, int w, int y)
{
    int param[3] = {0xe0000016, (int)"\xff\xfe\xa8\x24", 0};
    param[2] = menu::MenuDataCommon::getStatus(activeChara, menu::MenuDataCommon::LEVEL, false);
    UnkMenuParts* parts = s_levelParts;
    int condition = menu::MenuDataCommon::getPlayerCondition(activeChara);
    if (condition != 0) {
        parts = s_levelAltParts;
        param[0] = condition;
    }
    unkfunc_020629b4(parts, param, w * pos, y, data_02094dd4[getActorConditionColor(activeChara)]);
}

// not in the ROM (dead-stripped), its parts list is still in .data
THUMB void unkfunc_unused_0201c364()
{
    unkfunc_0206297c(s_unusedParts, NULL);
}
