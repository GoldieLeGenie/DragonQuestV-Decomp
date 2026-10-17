#pragma ipa file
#include "main/text/TextHook.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerData.hpp"

inline status::PlayerData& status::PlayerDataAll::getPlayerData(int index)
{
    return playerData_[index];
}

inline Sex status::PlayerData::getNameBasedSex()
{
    return nameBasedSex_;
}

UserExtractWordHook data_020ef2e0;

int UserExtractWordHook::extract(char* dst, int size, int type, int no)
{
    if (type == 0x50000000 && (unsigned int)no < 500) {
        int sex;
        switch (no) {
        case 1:
            sex = 1;
            break;
        case 2:
            sex = 1;
            break;
        case 3:
            sex = 2;
            break;
        case 4:
            sex = 2;
            break;
        case 5:
            sex = 2;
            break;
        case 6:
            sex = 1;
            break;
        case 7:
            sex = 1;
            break;
        case 8:
            sex = 2;
            break;
        case 9:
            sex = 2;
            break;
        case 10:
            sex = 2;
            break;
        case 11:
            sex = 1;
            break;
        case 12:
            sex = 1;
            break;
        case 13:
            sex = 1;
            break;
        case 14:
            sex = 2;
            break;
        case 15:
            sex = 1;
            break;
        default:
            sex = getOriginalWordSEX(no);
            break;
        }
        TextAPI::setMacroStat((MACRO_STAT)(sex | 0x10));
        dss::memcpy(dst, status::PlayerDataAll::playerData_[no].name_, size);
        return true;
    }
    if (type == 0x50000000 && no == 0x24e) {
        dss::memcpy(dst, status::g_Party.haveItemSack_.name_, size);
        return true;
    }
    if (type == 0x50000000) {
        int msg;
        switch (no) {
        case 16:
            msg = 101;
            break;
        case 17:
            msg = 111;
            break;
        case 18:
            msg = 121;
            break;
        case 19:
            msg = 125;
            break;
        case 20:
            msg = 129;
            break;
        case 21:
            msg = 133;
            break;
        case 22:
            msg = 137;
            break;
        case 23:
            msg = 141;
            break;
        case 24:
            msg = 145;
            break;
        case 25:
            msg = 149;
            break;
        case 26:
            msg = 153;
            break;
        case 27:
            msg = 157;
            break;
        case 28:
            msg = 161;
            break;
        case 29:
            msg = 165;
            break;
        case 30:
            msg = 169;
            break;
        case 31:
            msg = 173;
            break;
        case 32:
            msg = 177;
            break;
        case 33:
            msg = 181;
            break;
        case 34:
            msg = 185;
            break;
        case 35:
            msg = 189;
            break;
        case 36:
            msg = 193;
            break;
        case 37:
            msg = 197;
            break;
        case 38:
            msg = 201;
            break;
        case 39:
            msg = 205;
            break;
        case 40:
            msg = 209;
            break;
        case 41:
            msg = 213;
            break;
        case 42:
            msg = 217;
            break;
        case 43:
            msg = 221;
            break;
        case 44:
            msg = 225;
            break;
        case 45:
            msg = 229;
            break;
        case 46:
            msg = 233;
            break;
        case 47:
            msg = 237;
            break;
        case 48:
            msg = 241;
            break;
        case 49:
            msg = 245;
            break;
        case 50:
            msg = 249;
            break;
        case 51:
            msg = 253;
            break;
        case 52:
            msg = 257;
            break;
        case 53:
            msg = 261;
            break;
        case 54:
            msg = 265;
            break;
        case 55:
            msg = 269;
            break;
        case 56:
            msg = 273;
            break;
        case 57:
            msg = 277;
            break;
        case 60:
            msg = 281;
            break;
        case 61:
            msg = 285;
            break;
        case 62:
            msg = 289;
            break;
        case 63:
            msg = 293;
            break;
        case 64:
            msg = 297;
            break;
        case 65:
            msg = 301;
            break;
        case 66:
            msg = 305;
            break;
        case 67:
            msg = 309;
            break;
        case 68:
            msg = 313;
            break;
        case 69:
            msg = 317;
            break;
        case 70:
            msg = 321;
            break;
        case 71:
            msg = 325;
            break;
        case 72:
            msg = 329;
            break;
        case 73:
            msg = 333;
            break;
        case 74:
            msg = 337;
            break;
        case 75:
            msg = 341;
            break;
        case 76:
            msg = 345;
            break;
        case 77:
            msg = 349;
            break;
        case 78:
            msg = 353;
            break;
        case 79:
            msg = 357;
            break;
        case 80:
            msg = 361;
            break;
        case 81:
            msg = 365;
            break;
        case 83:
            msg = 369;
            break;
        case 84:
            msg = 373;
            break;
        case 85:
            msg = 377;
            break;
        case 86:
            msg = 381;
            break;
        case 87:
            msg = 385;
            break;
        default:
            msg = -1;
            break;
        }
        if (msg == -1) {
            return false;
        }
        return TextAPI::extractText(dst, size, type, msg);
    }
    return false;
}

int UserExtractWordHook::getOriginalWordSEX(int playerIndex)
{
    if (playerIndex > 231) {
        return 0;
    }
    if (playerIndex < 1) {
        return 0;
    }
    status::PlayerData& playerdata = status::PlayerDataAll::getPlayerData(playerIndex);
    if (playerdata.getNameBasedSex() == 0) {
        return 1;
    }
    if (playerdata.getNameBasedSex() == 1) {
        return 2;
    }
    return 0;
}
