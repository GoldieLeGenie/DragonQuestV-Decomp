#pragma ipa file
#include "main/debug/UnkDebugInfo.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/WorldLocation.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkArrayWarning.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/UnkVramTransfer.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/MuseumStatus.hpp"
#include "main/status/PlayerData.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

static int s_arrayWarningDrawCount;

UnkDebugInfo data_020c2d10;

static char s_flagLine[] = "+--- - - - - - - - - - -";
static char s_flagHeader[] = "-flg 0 1 2 3 4 5 6 7 8 9";

THUMB UnkDebugInfo::UnkDebugInfo()
{
    unkfunc_0202825c();
}

THUMB void UnkDebugInfo::initialize()
{
    posX_ = 0xfe02;
    posY_ = 0xfe02;
    posZ_ = 0xfe02;
    dir_ = 0xfe02;
    unkfunc_02027cdc();
}

THUMB void UnkDebugInfo::draw()
{
    if (showArrayWarning_ != 0) {
        unkfunc_020279bc(1, 2);
        return;
    }
    if (showLog_ != 0) {
        unkfunc_0202827c(1, 2);
        return;
    }
    if (showPosition_ != 0) {
        unkfunc_02027a38(1, 20);
    }
    if (showMessageID_ != 0) {
        unkfunc_02027d1c(25, 1);
    }
    if (showFlag_ != 0) {
        if (showFlag_ != 0) {
            unkfunc_02027ddc(0, 0);
        }
        return;
    }
    if (showWorldTime_ != 0) {
        unkfunc_02027f58(1, 1);
    }
    if (showPlayTime_ != 0) {
        unkfunc_02027fe8(12, 1);
    }
    if (showHeap_ != 0) {
        unkfunc_020281a0(1, 6);
    }
    if (showMuseum_ != 0) {
        unkfunc_020280e0(1, 12);
    }
    if (showFriend_ != 0) {
        unkfunc_02028204(8, 6);
    }
}

THUMB void UnkDebugInfo::unkfunc_020279bc(int x, int y)
{
    int count = unkfunc_0204c130();
    unkfunc_02027034(x + 8, y, "ARRAY WARNING!");
    for (int i = 0; i < 16; i++) {
        if (i < count) {
            UnkArrayWarning* warning = unkfunc_0204c11c(i);
            unkfunc_02026ffc(x, y + i + 1, "ARRAY OVER %3d/%3d %08x", warning->index_, warning->size_, warning->caller_);
        } else {
            unkfunc_02027034(x, y + i + 1, "----");
        }
    }
    unkfunc_0202708c(x, y, 30, 17);
    s_arrayWarningDrawCount++;
}

THUMB void UnkDebugInfo::unkfunc_02027a38(int x, int y)
{
    dss::Fix32Vector3 position;
    short dirIdx;
    cmn::g_cmnPartyInfo.getPartyInfo(position, dirIdx);
    if (data_02101c88.unkfunc_02051810() == 4) {
        if (posX_ != position.vx.value) {
            posX_ = position.vx.value;
            dss::sprintf_s(posXText_, 0x20, "X:%10f", position.vx.getfloat());
        }
        if (posY_ != position.vy.value) {
            posY_ = position.vy.value;
            dss::sprintf_s(posYText_, 0x20, "Y:%10f", position.vy.getfloat());
        }
        if (posZ_ != position.vz.value) {
            posZ_ = position.vz.value;
            dss::sprintf_s(posZText_, 0x20, "Z:%10f", position.vz.getfloat());
        }
        if (dir_ != dirIdx) {
            dir_ = dirIdx;
            dss::sprintf_s(dirText_, 0x20, "D:%6d %04x", dirIdx, (unsigned short)dirIdx);
        }
    } else {
        if (posX_ != position.vx.value) {
            posX_ = position.vx.value;
            dss::sprintf_s(posXText_, 0x20, "X:%-7.2f", position.vx.getfloat());
        }
        if (posY_ != position.vy.value) {
            posY_ = position.vy.value;
            dss::sprintf_s(posYText_, 0x20, "Y:%-7.2f", position.vy.getfloat());
        }
        if (posZ_ != position.vz.value) {
            posZ_ = position.vz.value;
            dss::sprintf_s(posZText_, 0x20, "Z:%-7.2f", position.vz.getfloat());
        }
        if (dir_ != dirIdx) {
            dir_ = dirIdx;
            dss::sprintf_s(dirText_, 0x20, "D:%6d %04x", dirIdx, (unsigned short)dirIdx);
        }
    }
    unkfunc_02027034(x, y, posXText_);
    unkfunc_02027034(x + 14, y, posYText_);
    unkfunc_02027034(x, y + 1, posZText_);
    unkfunc_02027034(x + 14, y + 1, dirText_);
    char* mapName = status::g_StageAttribute.getMapName();
    if (mapName != NULL) {
        if (data_02101c88.unkfunc_02051810() == 4) {
            unkfunc_02026ffc(x, y + 2, "%3d", g_Global.getMapNameIdByName(mapName));
            unkfunc_02027034(x + 4, y + 2, mapName);
        }
        if (data_02101c88.unkfunc_02051810() == 6) {
            unkfunc_02026ffc(x, y + 2, "---");
            unkfunc_02027034(x + 4, y + 2, mapName);
        }
    }
    unkfunc_02026ffc(x + 20, y + 2, "LK=%d", util::StageLink::getTownExitIndex());
    int walkCount = -1;
    if (data_02101c88.unkfunc_02051810() == 4) {
        walkCount = (int)twn::TownPlayerManager::getSingleton().walkCounter_ / 16;
    }
    if (data_02101c88.unkfunc_02051810() == 6) {
        walkCount = fld::FieldPlayerManager::getSingleton().walkCounter / 16;
    }
    unkfunc_02026ffc(x + 13, y + 2, "WK=%d", walkCount);
    unkfunc_0202708c(x, y, 29, 3);
}

THUMB void UnkDebugInfo::unkfunc_02027cdc()
{
    for (int i = 0; i < 16; i++) {
        messageID_[i] = -1;
    }
}

THUMB void UnkDebugInfo::unkfunc_02027cf0(int messageID)
{
    for (int i = 0; i < 16; i++) {
        if (messageID_[i] == -1) {
            messageID_[i] = messageID;
            return;
        }
    }
}

THUMB void UnkDebugInfo::unkfunc_02027d1c(int x, int y)
{
    unkfunc_02027034(x, y, "MessID");
    for (int i = 0; i < 16; i++) {
        if (messageID_[i] != -1) {
            unkfunc_02026ffc(x, y + i + 1, "%6d", messageID_[i]);
        } else {
            unkfunc_02027034(x, y + i + 1, "------");
        }
    }
    unkfunc_0202708c(x, y, 6, 17);
}

THUMB void UnkDebugInfo::unkfunc_02027d7c(int x, int y)
{
    unkfunc_02027034(x, y, "MessID");
    for (int i = 0; i < 6; i++) {
        if (messageID_[i] != -1) {
            unkfunc_02026ffc(x, y + i + 1, "%6d", messageID_[i]);
        } else {
            unkfunc_02027034(x, y + i + 1, "------");
        }
    }
    unkfunc_0202708c(x, y, 6, 7);
}

THUMB void UnkDebugInfo::unkfunc_02027ddc(int x, int y)
{
    unkfunc_02027e74(x, y, 'G', &g_AreaFlag, areaFlagTop_, 5, &areaFlag_);
    unkfunc_02027e74(x, y + 7, 'A', &g_LocalFlag, localFlagTop_, 5, &localFlag_);
    unkfunc_02027e74(x, y + 14, 'L', &g_GlobalFlag, globalFlagTop_, 5, &globalFlag_);
    unkfunc_02027058(0, 0, 24, 6);
    unkfunc_02027058(0, 7, 24, 6);
    unkfunc_02027058(0, 14, 24, 6);
}

THUMB void UnkDebugInfo::unkfunc_02027e74(int x, int y, char kind, status::GameFlag* flag, int top, int lines, status::GameFlag* prevFlag)
{
    int blink;
    if (unkfunc_0204ccd0() & 2) {
        blink = 1;
    } else {
        blink = 0;
    }
    s_flagHeader[0] = kind;
    unkfunc_02027034(x, y, s_flagHeader);
    for (int i = 0; i < lines; i++) {
        int index = top + i * 10;
        char* p;
        s_flagLine[1] = index / 100 + '0';
        int rest = index % 100;
        s_flagLine[2] = rest / 10 + '0';
        rest = rest % 10;
        s_flagLine[3] = rest + '0';
        int flagIndex = index;
        p = &s_flagLine[5];
        for (int j = 0; j < 10; j++) {
            int check = flag->check(flagIndex);
            int prevCheck = prevFlag->check(flagIndex);
            *p = check + '0';
            if (check != prevCheck && blink) {
                *p = ' ';
            }
            p += 2;
            flagIndex++;
        }
        unkfunc_02027034(x, y + 1 + i, s_flagLine);
    }
}

THUMB void UnkDebugInfo::unkfunc_02027f58(int x, int y)
{
    const char* timeZoneName = "";
    switch (cmn::WorldLocation::getCurrentTimeZone()) {
    case TIME_ZONE_MORNING:
        timeZoneName = "MORNING";
        break;
    case TIME_ZONE_DAYTIME:
        timeZoneName = "DAYTIME";
        break;
    case TIME_ZONE_EVENING:
        timeZoneName = "EVENING";
        break;
    case TIME_ZONE_NIGHT:
        timeZoneName = "  NIGHT";
        break;
    }
    unkfunc_02026ffc(x, y, "WORLDTIME");
    unkfunc_02026ffc(x, y + 1, "%4d/%4d", status::g_StageInfo.getWorldTime(), cmn::WorldLocation::getMaxTime());
    unkfunc_02026ffc(x + 2, y + 2, timeZoneName);
    unkfunc_0202708c(x, y, 9, 3);
}

THUMB void UnkDebugInfo::unkfunc_02027fe8(int x, int y)
{
    unsigned int playTime = status::g_Game.getPlayTime();
    unsigned int frameCount = data_02101c88.frameCount_;
    unkfunc_02026ffc(x, y, "PLAY TIME");
    unsigned int hourRest = playTime % 216000;
    unsigned int minuteRest = hourRest % 3600;
    unkfunc_02026ffc(x, y + 1, "%03d:%02d:%02d.%02d", playTime / 216000, hourRest / 3600, minuteRest / 60, minuteRest % 60 * 100 / 60);
    hourRest = frameCount % 216000;
    minuteRest = hourRest % 3600;
    unkfunc_02026ffc(x, y + 2, "%03d:%02d:%02d.%02d", frameCount / 216000, hourRest / 3600, minuteRest / 60, minuteRest % 60 * 100 / 60);
    unkfunc_0202708c(x, y, 11, 3);
}

THUMB void UnkDebugInfo::unkfunc_020280e0(int x, int y)
{
    char fear = '-';
    char funny = '-';
    char beautiful = '-';
    switch (status::g_MuseumStatus.getMuseumTrend()) {
    case status::MUSEUMTREND_BEAUTIFUL:
        beautiful = '*';
        break;
    case status::MUSEUMTREND_FUNNY:
        funny = '*';
        break;
    case status::MUSEUMTREND_FEAR:
        fear = '*';
        break;
    }
    unkfunc_02026ffc(x, y, "MUSEUM");
    unkfunc_02026ffc(x, y + 1, "Lv.%d %3d", status::g_MuseumStatus.getMuseumLevel(), status::g_MuseumStatus.museumPoint_);
    unkfunc_02026ffc(x, y + 2, "Pe %d", status::g_MuseumStatus.penaltyPoint_);
    unkfunc_02026ffc(x, y + 3, "Be %d %c", status::g_MuseumStatus.beautifulPoint_, beautiful);
    unkfunc_02026ffc(x, y + 4, "Fu %d %c", status::g_MuseumStatus.funnyPoint_, funny);
    unkfunc_02026ffc(x, y + 5, "Fe %d %c", status::g_MuseumStatus.fearPoint_, fear);
    unkfunc_0202708c(x, y, 8, 6);
}

THUMB void UnkDebugInfo::unkfunc_020281a0(int x, int y)
{
    unkfunc_02026ffc(x, y, "HEAP");
    unkfunc_02026ffc(x, y + 1, "%3dK", unkfunc_0204c5f4(&data_020fd24c) >> 10);
    unkfunc_02026ffc(x, y + 2, "VRAM");
    unkfunc_02026ffc(x, y + 3, "%3dk", data_020f4f74.unk_08 >> 10);
    unkfunc_0202708c(x, y, 5, 4);
}

THUMB void UnkDebugInfo::unkfunc_02028204(int x, int y)
{
    unkfunc_02026ffc(x, y, "ALL FRIEND");
    unkfunc_02026ffc(x, y + 1, "count:%d", status::PlayerDataAll::getFriendMonsterCount());
    unkfunc_02026ffc(x, y + 2, "WITHOUT EVENT");
    unkfunc_02026ffc(x, y + 3, "count:%d", status::PlayerDataAll::getFriendMonsterCountWithoutEventMonster());
    unkfunc_0202708c(x, y, 13, 4);
}

THUMB void UnkDebugInfo::unkfunc_02028258(int show)
{
    showArrayWarning_ = show;
}

THUMB void UnkDebugInfo::unkfunc_0202825c()
{
    showLog_ = 0;
    unk_24 = 1;
    logIndex_ = 0;
    for (int i = 0; i < 24; i++) {
        log_[i][0] = 0;
    }
}

THUMB void UnkDebugInfo::unkfunc_0202827c(int x, int y)
{
    unkfunc_0202708c(x, y, 30, 16);
    int index = logIndex_ - 16;
    if (index < 0) {
        index += 24;
    }
    for (int i = 0; i < 16; i++) {
        unkfunc_02026ffc(x, y + i, log_[index]);
        index++;
        if (index == 24) {
            index = 0;
        }
    }
}
