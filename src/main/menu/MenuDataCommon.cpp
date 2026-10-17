#include "main/menu/MenuDataCommon.hpp"
#include "main/menu/MenuStatusInfo.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/UseItem.hpp"
#include "main/text/TextHook.hpp"

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
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

inline int status::PlayerData::getExp()
{
    return baseStatus_.exp_;
}

inline int status::PlayerData::getKindIndex()
{
    return kindIndex_;
}

THUMB int menu::MenuDataCommon::getEquipKind(int index)
{
    const int equipKind[5] = {0xe00000c8, 0xe00000c9, 0xe00000ca, 0xe00000cb, 0xe00000cc};
    return equipKind[index];
}

THUMB int menu::MenuDataCommon::getAbilityKind(STATUS_INDEX index)
{
    if (index == ATTACK) {
        return 0xe0000019;
    }
    if (index == DEFENCE) {
        return 0xe000001a;
    }
    if (index == STRENGTH) {
        return 0xe000011c;
    }
    if (index == AGILITY) {
        return 0xe00000d9;
    }
    if (index == PROTECTION) {
        return 0xe000011e;
    }
    if (index == WISDOM) {
        return 0xe00000da;
    }
    if (index == LUCK) {
        return 0xe00000db;
    }
    if (index == MAXHP) {
        return 0xe00003dd;
    }
    if (index == MAXMP) {
        return 0xe00003de;
    }
    return 0;
}

THUMB int menu::MenuDataCommon::getStatus(int activeChara, STATUS_INDEX index, int noEquip)
{
    status::HaveStatusInfo* statusInfo = 0;
    status::PlayerData* playerData = 0;
    int status = 0;
    int flag = status::g_Menu.drawFlag_;

    if (flag == 0) {
        statusInfo = &MenuStatusInfo::getHaveStatusInfo(activeChara);
    } else {
        playerData = &MenuStatusInfo::getPlayerData(activeChara);
    }
    if (index == ATTACK) {
        if (noEquip == true) {
            return statusInfo->getAttack(1);
        }
        if (flag == 0) {
            status = statusInfo->getAttack(0);
        } else {
            status = playerData->getAttack();
        }
    }
    if (index == DEFENCE) {
        if (noEquip == true) {
            return statusInfo->getDefence(1);
        }
        if (flag == 0) {
            status = statusInfo->getDefence(0);
        } else {
            status = playerData->getDefence();
        }
    }
    if (index == STRENGTH) {
        if (noEquip == true) {
            return statusInfo->getStrength(1);
        }
        if (flag == 0) {
            status = statusInfo->getStrength(0);
        } else {
            status = playerData->getEquipStrength();
        }
    }
    if (index == AGILITY) {
        if (noEquip == true) {
            return statusInfo->getAgility(1);
        }
        if (flag == 0) {
            status = statusInfo->getAgility(0);
        } else {
            status = playerData->getEquipAgility();
        }
    }
    if (index == PROTECTION) {
        if (noEquip == true) {
            return statusInfo->getProtection(1);
        }
        if (flag == 0) {
            status = statusInfo->getProtection(0);
        } else {
            status = playerData->getEquipProtection();
        }
    }
    if (index == WISDOM) {
        if (noEquip == true) {
            return statusInfo->getWisdom(1);
        }
        if (flag == 0) {
            status = statusInfo->getWisdom(0);
        } else {
            status = playerData->getEquipWisdom();
        }
    }
    if (index == LUCK) {
        if (noEquip == true) {
            return statusInfo->getLuck(1);
        }
        if (flag == 0) {
            status = statusInfo->getLuck(0);
        } else {
            status = playerData->getEquipLuck();
        }
    }
    if (index == NOWHP) {
        if (flag == 0) {
            status = statusInfo->getHp();
        } else {
            status = playerData->getHp();
        }
    }
    if (index == MAXHP) {
        if (flag == 0) {
            status = statusInfo->getHpMax();
        } else {
            status = playerData->getHpMax();
        }
    }
    if (index == NOWMP) {
        if (flag == 0) {
            status = statusInfo->getMp();
        } else {
            status = playerData->getMp();
        }
    }
    if (index == MAXMP) {
        if (flag == 0) {
            status = statusInfo->getMpMax();
        } else {
            status = playerData->getMpMax();
        }
    }
    if (index == LEVEL) {
        if (flag == 0) {
            status = statusInfo->haveStatus_.level_;
        } else {
            status = playerData->getLevel();
        }
    }
    if (index == EXP) {
        if (flag == 0) {
            status = statusInfo->getExp();
        } else {
            status = playerData->getExp();
        }
    }
    return status;
}

THUMB int menu::MenuDataCommon::getRuraName(int index)
{
    const int moveName[20] = {
        0xc00002bd, 0xc00002be, 0xc00002bf, 0xc00002c0, 0xc00002c1, 0xc00002c2, 0xc00002c3, 0xc00002c4, 0xc00002c5, 0xc00002c6,
        0xc00002c7, 0xc00002c8, 0xc00002c9, 0xc00002ca, 0xc00002cb, 0xc00002cc, 0xc00002cd, 0xc00002ce, 0xc00002cf, 0xc00002d0,
    };
    return moveName[index];
}

THUMB int menu::MenuDataCommon::getItemTypeMessageNo(int itemID)
{
    int messageNo = 0;
    int itemType = status::UseItem::getItemType(itemID);
    switch (itemType) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            messageNo = itemType + 0xe00000c8;
            break;
        case 5:
        case 6:
        case 8:
            messageNo = 0xe00000cd;
            break;
        case 12:
            messageNo = 0xe00000d2;
            break;
        case 7:
            messageNo = 0xe00000cf;
            break;
        case 9:
        case 10:
            messageNo = 0xe00000ce;
            break;
        case 11:
            messageNo = 0xe00000d0;
            break;
    }
    return messageNo;
}

THUMB int menu::MenuDataCommon::getItemMessageNo(int itemID)
{
    int messageNo = status::UseItem::getCommentMessage(itemID);
    if (messageNo == 0) {
        switch (status::UseItem::getCommentKindIndex(itemID)) {
            case 0x19:
                messageNo = 0xe0000019;
                break;
            case 0x1a:
                messageNo = 0xe000001a;
                break;
            case 0xd9:
                messageNo = 0xe00000d9;
                break;
            case 0xda:
                messageNo = 0xe00000da;
                break;
            case 0xdb:
                messageNo = 0xe00000db;
                break;
        }
    }
    return messageNo;
}

THUMB int menu::MenuDataCommon::getPlayerJob(int activeChara)
{
    int job = MenuStatusInfo::getPlayerJob(activeChara);
    int index = MenuStatusInfo::getPlayerIndex(activeChara);
    if (MenuStatusInfo::isPlayerType(activeChara, MenuStatusInfo::TYPE_FRIEND_MONSTER) == true) {
        switch (MenuStatusInfo::getPlayerData(activeChara).getKindIndex()) {
            case 0x3a:
            case 0x3b:
                job = 0xe000010b;
                break;
            case 0x52:
                job = 0xe000010c;
                break;
            default:
                job += 0x60000000;
                break;
        }
    } else {
        job -= 0x20000000;
        if (index == 1) {
            if (g_AreaFlag.check(0x82) == true) {
                job = 0xe00000fb;
            }
            if (g_AreaFlag.check(0x84) == true) {
                job = 0xe00000fc;
            }
            if (g_AreaFlag.check(0xae) == true) {
                job = 0xe00000fd;
            }
            if (g_AreaFlag.check(0xc0) == true) {
                job = 0xe00000fe;
            }
            if ((g_AreaFlag.check(0x11b) == true && g_LocalFlag.check(0xa) == true) || g_AreaFlag.check(0x11c) == true) {
                job = 0xe00000ff;
            }
            if (g_AreaFlag.check(0x167) == true) {
                job = 0xe0000100;
            }
        }
        if (index == 0xd && g_AreaFlag.check(0x167) == true) {
            job = 0xe0000109;
        }
        if (index == 9 || index == 10 || (index == 4 && g_AreaFlag.check(0xeb) == true)) {
            job = 0xe0000103;
        }
    }
    return job;
}

THUMB int menu::MenuDataCommon::getPlayerCondition(int activeChara)
{
    int param = 0;
    if (MenuStatusInfo::isPlayerCondition(activeChara, MenuStatusInfo::CONDITION_DEATH) == true) {
        if (status::g_Story.getChapter() == 1) {
            param = 0xe000002c;
        } else {
            param = 0xe0000023;
        }
    } else if (MenuStatusInfo::isPlayerCondition(activeChara, MenuStatusInfo::CONDITION_VENOM) == true) {
        param = 0xe000002a;
    } else if (MenuStatusInfo::isPlayerCondition(activeChara, MenuStatusInfo::CONDITION_POISON) == true) {
        param = 0xe0000027;
    } else if (MenuStatusInfo::isPlayerCondition(activeChara, MenuStatusInfo::CONDITION_SPELL) == true ||
               MenuStatusInfo::isPlayerCondition(activeChara, MenuStatusInfo::CONDITION_ITEM_SPELL) == true) {
        param = 0xe000002b;
    }
    bool female = false;
    int type = MenuStatusInfo::getPlayerSex(activeChara);
    if (type == 0x115) {
        female = true;
    }
    if (type != 0x114 && type != 0x115 && UserExtractWordHook::getOriginalWordSEX(MenuStatusInfo::getPlayerIndex(activeChara)) == 2) {
        female = true;
    }
    if (female) {
        if (param == 0xe000002c) {
            param = 0xe000002c + 0xa;
        }
        if (param == 0xe0000023) {
            param = 0xe0000023 + 0xa;
        }
        if (param == 0xe000002a) {
            param = 0xe000002a + 0xa;
        }
        if (param == 0xe0000027) {
            param = 0xe0000027 + 0xa;
        }
        if (param == 0xe000002b) {
            param = 0xe000002b + 0xa;
        }
    }
    return param;
}
