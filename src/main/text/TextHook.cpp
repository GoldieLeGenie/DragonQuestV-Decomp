#pragma ipa file
#include "main/text/TextHook.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkRandom.hpp"
#include "main/dss/UnkTextConvert.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/BattleResult.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "main/status/UseItem.hpp"

inline bool status::HaveStatusInfo::isPlayer() const
{
    bool flag = false;
    unsigned char type = (unsigned char)haveStatus_.playerType_ + 0xff;
    if (type <= 4 && ((1 << type) & 0x13)) {
        flag = true;
    }
    return flag;
}

inline status::HaveStatusInfo& status::CharacterStatus::getHaveStatusInfo()
{
    return haveStatusInfo_;
}

TextHook gTextHook;

THUMB int TextHook::extractDefaultText(char* text, int size, int id, int param)
{
    int result = 0;
    unsigned int accessMode = status::g_Party.getAccessMode();
    status::g_Party.setNormalMode();
    checkPlayer();
    if (extractDefaultTextTest(text, size, id, param)) {
        result = 1;
    } else if (extractDefaultTextString(text, size, id, param)) {
        result = 1;
    } else if (extractDefaultTextNumber(text, size, id, param)) {
        result = 1;
    }
    status::g_Party.setAccessMode(accessMode);
    return result;
}

THUMB int TextHook::extractDefaultTextTest(char* text, int size, int id, int param)
{
    switch (id) {
        case 0x1a:
            return 1;
        case 0x1c:
        case 0x8f: {
            const char* str = "----";
            if (status::g_MuseumStatus.playerTaishi_.isTaishi_ == 1) {
                unsigned char* name = (unsigned char*)status::g_MuseumStatus.playerTaishi_.taishiName_;
                if (name[0] != 0 && name[0] != 0xff) {
                    str = (const char*)name;
                }
            }
            dss::strcpy_s(text, size, str);
            return 1;
        }
    }
    return 0;
}

THUMB int TextHook::extractDefaultTextString(char* text, int size, int id, int param)
{
    char buffer[0x200];
    char number[0x100];
    switch (id) {
        case 9:
            extractParty(text, size, 1);
            return 1;
        case 0x7b: {
            int value = 4;
            if (g_AreaFlag.check(0xeb)) {
                value = 4;
            }
            if (g_AreaFlag.check(0xec)) {
                value = 9;
            }
            if (g_AreaFlag.check(0x259)) {
                value = 10;
            }
            extractParty(text, size, value);
            return 1;
        }
        case 0x16:
            for (int i = 0; i < equipable_pc_count_; i++) {
                const char* delimiter = "";
                if (i > 0) {
                    delimiter = equipable_pc_delimiter1_;
                }
                if (i + 1 == equipable_pc_count_) {
                    delimiter = equipable_pc_delimiter2_;
                }
                if (i == 0) {
                    delimiter = "";
                }
                dss::strcat(text, delimiter);
                if (TextAPI::m_lang == 0 && i == 4) {
                    dss::strcat(text, "\n\t");
                }
                extractParty(buffer, sizeof(buffer), equipable_pc_list_[i]);
                dss::strcat(text, buffer);
            }
            return 1;
        case 0xb:
            extractParty(text, size, leaderpc_);
            return 1;
        case 0xc:
            extractParty(text, size, leader_);
            return 1;
        case 0xe:
            extractParty(text, size, mostheroic_);
            return 1;
        case 0x7c:
            extractParty(text, size, 0xd);
            return 1;
        case 0x7d:
            extractParty(text, size, 0xe);
            return 1;
        case 0x79:
            extractParty(text, size, 0x10);
            return 1;
        case 0x8c:
            extractParty(text, size, 0x24e);
            return 1;
        case 0x6c: {
            int low = raceResultA_ + 1;
            int high = raceResultB_ + 1;
            int max = high;
            if (low > high) {
                max = low;
                low = high;
            }
            dss::sprintf_s(number, sizeof(number), "%d-%d", low, max);
            translateText(data_0209a0b8[0], data_0209a0b8[1], text, size, number);
            return 1;
        }
        case 0x7a:
            *text = 0;
            switch (UnkDssRand::rand(3)) {
                case 0:
                    g_text_extractor.extractText(text, size, 0xe0000000, 0x3d4);
                    break;
                case 1:
                    g_text_extractor.extractText(text, size, 0xe0000000, 0x3d5);
                    break;
                case 2:
                    g_text_extractor.extractText(text, size, 0xe0000000, 0x3d6);
                    break;
            }
            return 1;
    }
    return 0;
}

THUMB int TextHook::extractDefaultTextNumber(char* text, int size, int id, int param)
{
    switch (id) {
        case 0x29:
            extractNumber(text, size, status::g_Party.gold_);
            return 1;
        case 0x4a:
            extractNumber(text, size, status::g_BattleResult.battleTurnCount_);
            return 1;
    }
    return 0;
}

THUMB void TextHook::resetEQUIPABLE_PC()
{
    const char* delimiter1 = "";
    const char* delimiter2 = delimiter1;
    switch (TextAPI::m_lang) {
        case 0:
            delimiter1 = "\xe3\x80\x81";
            delimiter2 = delimiter1;
            break;
        case 1:
            delimiter1 = ", ";
            delimiter2 = " and ";
            break;
        case 2:
            delimiter1 = ", ";
            delimiter2 = " et ";
            break;
        case 3:
            delimiter1 = ", ";
            delimiter2 = " und ";
            break;
        case 4:
            delimiter1 = ", ";
            delimiter2 = " e ";
            break;
        case 5:
            delimiter1 = ", ";
            delimiter2 = " y ";
            break;
    }
    equipable_pc_count_ = 0;
    for (int i = 0; i < EQUIPABLE_PC_MAXCOUNT; i++) {
        equipable_pc_list_[i] = -1;
    }
    equipable_pc_delimiter1_ = delimiter1;
    equipable_pc_delimiter2_ = delimiter2;
}

THUMB void TextHook::setEQUIPABLE_PC(int playerIndex)
{
    equipable_pc_list_[equipable_pc_count_++] = playerIndex;
}

THUMB void TextHook::checkPlayer()
{
    humanPC_ = -1;
    humanNPC_ = -1;
    monsterPC_ = -1;
    topchar_ = -1;
    deadleadpc_ = -1;
    deadleader_ = -1;
    leader_ = -1;
    leaderpc_ = -1;
    mostheroic_ = -1;
    sister_ = 0;
    male_ = 0;
    female_ = 0;
    monster_ = 0;
    corpse_ = 0;
    for (int i = 0; i < status::g_Party.getCount(); i++) {
        int pc;
        int npc;
        int hero;
        int mon;
        int playerIndex = status::g_Party.getPlayerStatus(i).index_;
        int death = status::g_Party.getPlayerStatus(i).haveStatusInfo_.isDeath();
        int isHuman = status::g_Party.getPlayerStatus(i).getHaveStatusInfo().isPlayer() != false ? 1 : 0;
        int inCarriage = status::PartyStatus::isInsideCarriageForPlayerIndex(playerIndex);
        if (!death) {
            if (!inCarriage) {
                int sex = status::g_Party.getPlayerStatus(i).haveStatusInfo_.haveStatus_.getSex();
                if (leader_ == -1) {
                    leader_ = playerIndex;
                    leaderSex_ = (Sex)sex;
                }
                if (leaderpc_ == -1 && isHuman) {
                    leaderpc_ = playerIndex;
                    leadPcSex_ = (Sex)sex;
                }
                pc = -1;
                npc = -1;
                hero = -1;
                mon = -1;
                switch (playerIndex) {
                    case 1:
                        pc = playerIndex;
                        hero = playerIndex;
                        break;
                    case 2:
                        pc = playerIndex;
                        break;
                    case 3:
                        pc = playerIndex;
                        break;
                    case 4:
                        pc = playerIndex;
                        break;
                    case 5:
                        pc = playerIndex;
                        break;
                    case 6:
                        pc = playerIndex;
                        break;
                    case 7:
                        pc = playerIndex;
                        break;
                    case 8:
                        npc = playerIndex;
                        break;
                    case 9:
                        pc = playerIndex;
                        break;
                    case 10:
                        pc = playerIndex;
                        break;
                    case 11:
                        pc = playerIndex;
                        break;
                    case 12:
                        pc = playerIndex;
                        break;
                    case 13:
                        pc = playerIndex;
                        break;
                    case 14:
                        pc = playerIndex;
                        break;
                    case 15:
                        npc = playerIndex;
                        break;
                    default:
                        mon = playerIndex;
                        break;
                }
                if (humanPC_ == -1) {
                    humanPC_ = pc;
                }
                if (humanNPC_ == -1) {
                    humanNPC_ = npc;
                }
                if (mostheroic_ == -1) {
                    mostheroic_ = hero;
                }
                if (monsterPC_ == -1) {
                    monsterPC_ = mon;
                }
                if (sex == SEX_MALE) {
                    male_++;
                }
                if (sex == SEX_FEMALE) {
                    female_++;
                }
                if (sex == SEX_NONE) {
                    monster_++;
                }
            }
        } else if (isHuman) {
            corpse_++;
        }
        if (deadleader_ == -1) {
            deadleader_ = playerIndex;
        }
        if (isHuman && deadleadpc_ == -1) {
            deadleadpc_ = playerIndex;
        }
    }
    if (topchar_ == -1) {
        topchar_ = humanPC_;
    }
    if (topchar_ == -1) {
        topchar_ = humanNPC_;
    }
    if (topchar_ == -1) {
        topchar_ = monsterPC_;
    }
    if (topchar_ == -1) {
        topchar_ = deadleadpc_;
    }
    if (topchar_ == -1) {
        topchar_ = deadleader_;
    }
    if (topchar_ == -1) {
        topchar_ = 1;
    }
    if (leader_ == -1) {
        leader_ = topchar_;
    }
    if (leaderpc_ == -1) {
        leaderpc_ = leader_;
    }
    if (mostheroic_ == -1) {
        mostheroic_ = humanPC_;
    }
    if (mostheroic_ == -1) {
        mostheroic_ = monsterPC_;
    }
}

THUMB void TextHook::extractParty(char* text, int size, int value)
{
    g_text_extractor.extractText(text, size, 0x50000000, value);
}

THUMB void TextHook::extractNumber(char* text, int size, int value)
{
    g_text_extractor.extractText(text, size, 0xf0000000, value);
}

THUMB int TextHook::getMacroStat(int id, int param)
{
    unsigned int accessMode = status::g_Party.getAccessMode();
    MACRO_STAT result = MST_NULL;
    checkPlayer();
    switch (id) {
        case 0xb:
            if (leadPcSex_ == SEX_MALE) {
                result = (MACRO_STAT)(result | MST_MALE);
            }
            if (leadPcSex_ == SEX_FEMALE) {
                result = (MACRO_STAT)(result | MST_FEMALE);
            }
            if (leadPcSex_ == SEX_NONE) {
                result = (MACRO_STAT)(result | UserExtractWordHook::getOriginalWordSEX(leaderpc_));
            }
            break;
        case 0xc:
            if (leaderSex_ == SEX_MALE) {
                result = (MACRO_STAT)(result | MST_MALE);
            }
            if (leaderSex_ == SEX_FEMALE) {
                result = (MACRO_STAT)(result | MST_FEMALE);
            }
            if (leadPcSex_ == SEX_NONE) {
                result = (MACRO_STAT)(result | UserExtractWordHook::getOriginalWordSEX(leaderpc_));
            }
            break;
        case 0xe:
            break;
        case 0x56: {
            status::g_Party.setBattleMode();
            int count = status::g_Party.getCarriageOutAliveCount();
            if (count == 1) {
                result = (MACRO_STAT)(result | MST_SINGLE);
                result = (MACRO_STAT)(result | MST_SINGLE_FR);
            }
            if (count == 0) {
                result = (MACRO_STAT)(result | MST_SINGLE_FR);
            }
            break;
        }
        case 0x96:
            break;
        case 0x97: {
            MsgVar* var = g_text_env.search_msg_var(10, 0);
            if (var != 0) {
                ItemType type = status::UseItem::getItemType(var->m_no);
                if (type == 0) {
                    result = (MACRO_STAT)(result | MST_BOOL);
                }
                if (type == 2) {
                    result = (MACRO_STAT)(result | MST_BOOL);
                }
            }
            break;
        }
    }

    int number = -1;
    if (id == 0x29) {
        number = status::g_Party.gold_;
    }
    if (id == 0x4a) {
        number = status::g_BattleResult.battleTurnCount_;
    }
    if (number >= 0) {
        result = (MACRO_STAT)(result | MST_PLUS);
    }
    if (number == 1) {
        result = (MACRO_STAT)(result | MST_SINGLE);
        result = (MACRO_STAT)(result | MST_SINGLE_FR);
    }
    if (number == 0) {
        result = (MACRO_STAT)(result | MST_SINGLE_FR);
    }

    if (id == 0x60) {
        int leader = 0;
        switch (param) {
            case 0:
                if (leader_ == 1) {
                    leader = 1;
                }
                if (leader_ == 2) {
                    leader = 1;
                }
                break;
            case 1:
                if (leader_ == 3) {
                    leader = 1;
                }
                break;
            case 2:
                if (leader_ == 4) {
                    leader = 1;
                }
                break;
            case 3:
                if (leader_ == 5) {
                    leader = 1;
                }
                break;
            case 4:
                if (leader_ == 6) {
                    leader = 1;
                }
                break;
            case 5:
                if (leader_ == 7) {
                    leader = 1;
                }
                break;
            case 6:
                if (leader_ == 9) {
                    leader = 1;
                }
                break;
            case 7:
                if (leader_ == 8) {
                    leader = 1;
                }
                break;
            case 8:
                if (leader_ == 0x19) {
                    leader = 1;
                }
                break;
            case 9:
                if (leader_ == 0x13) {
                    leader = 1;
                }
                break;
        }
        if (leader) {
            result = (MACRO_STAT)(result | MST_LEADER);
        }
    }
    if (sister_ == 2) {
        result = (MACRO_STAT)(result | MST_SISTER);
    }
    if (male_ == 0 && monster_ == 0) {
        result = (MACRO_STAT)(result | MST_ALLMEMBER);
    }
    if (id == 0x12) {
        result = (MACRO_STAT)(result | MST_SOLO);
    }
    if (id == 0xc) {
        result = (MACRO_STAT)(result | MST_SOLO);
    }
    if (id == 0xb) {
        result = (MACRO_STAT)(result | MST_SOLO);
    }
    if (id == 0x16 && equipable_pc_count_ == 1) {
        result = (MACRO_STAT)(result | MST_SOLO);
    }
    status::g_Party.setAccessMode(accessMode);
    return result;
}
