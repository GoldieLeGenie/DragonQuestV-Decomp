#pragma ipa file
#include "main/debug/DebugInfo.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/WorldLocation.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkArrayWarning.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/VramTransferManager.hpp"
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

DebugInfo data_020c2d10;

static char s_flagLine[] = "+--- - - - - - - - - - -";
static char s_flagHeader[] = "-flg 0 1 2 3 4 5 6 7 8 9";

THUMB DebugInfo::DebugInfo()
{
    clearLog();
}

THUMB void DebugInfo::initialize()
{
    posX_ = 0xfe02;
    posY_ = 0xfe02;
    posZ_ = 0xfe02;
    dir_ = 0xfe02;
    clearMessageIDs();
}

THUMB void DebugInfo::draw()
{
    if (showArrayWarning_ != 0) {
        drawArrayWarnings(1, 2);
        return;
    }
    if (showLog_ != 0) {
        drawLog(1, 2);
        return;
    }
    if (showPosition_ != 0) {
        drawPosition(1, 20);
    }
    if (showMessageID_ != 0) {
        unkfunc_02027d1c(25, 1);
    }
    if (showFlag_ != 0) {
        if (showFlag_ != 0) {
            drawFlags(0, 0);
        }
        return;
    }
    if (showWorldTime_ != 0) {
        drawWorldTime(1, 1);
    }
    if (showPlayTime_ != 0) {
        drawPlayTime(12, 1);
    }
    if (showHeap_ != 0) {
        drawHeap(1, 6);
    }
    if (showMuseum_ != 0) {
        drawMuseum(1, 12);
    }
    if (showFriend_ != 0) {
        drawFriendMonsters(8, 6);
    }
}

THUMB void DebugInfo::drawArrayWarnings(int x, int y)
{
    int count = getArrayErrorCount();
    debugPrint(x + 8, y, "ARRAY WARNING!");
    for (int i = 0; i < 16; i++) {
        if (i < count) {
            UnkArrayWarning* warning = getArrayError(i);
            debugConsolePrintf(x, y + i + 1, "ARRAY OVER %3d/%3d %08x", warning->index_, warning->size_, warning->caller_);
        } else {
            debugPrint(x, y + i + 1, "----");
        }
    }
    drawDebugWindow(x, y, 30, 17);
    s_arrayWarningDrawCount++;
}

THUMB void DebugInfo::drawPosition(int x, int y)
{
    dss::Fix32Vector3 position;
    short dirIdx;
    cmn::g_cmnPartyInfo.getPartyInfo(position, dirIdx);
    if (data_02101c88.getCurrentPart() == 4) {
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
    debugPrint(x, y, posXText_);
    debugPrint(x + 14, y, posYText_);
    debugPrint(x, y + 1, posZText_);
    debugPrint(x + 14, y + 1, dirText_);
    char* mapName = status::g_StageAttribute.getMapName();
    if (mapName != NULL) {
        if (data_02101c88.getCurrentPart() == 4) {
            debugConsolePrintf(x, y + 2, "%3d", g_Global.getMapNameIdByName(mapName));
            debugPrint(x + 4, y + 2, mapName);
        }
        if (data_02101c88.getCurrentPart() == 6) {
            debugConsolePrintf(x, y + 2, "---");
            debugPrint(x + 4, y + 2, mapName);
        }
    }
    debugConsolePrintf(x + 20, y + 2, "LK=%d", util::StageLink::getTownExitIndex());
    int walkCount = -1;
    if (data_02101c88.getCurrentPart() == 4) {
        walkCount = (int)twn::TownPlayerManager::getSingleton().walkCounter_ / 16;
    }
    if (data_02101c88.getCurrentPart() == 6) {
        walkCount = fld::FieldPlayerManager::getSingleton().walkCounter / 16;
    }
    debugConsolePrintf(x + 13, y + 2, "WK=%d", walkCount);
    drawDebugWindow(x, y, 29, 3);
}

THUMB void DebugInfo::clearMessageIDs()
{
    for (int i = 0; i < 16; i++) {
        messageID_[i] = -1;
    }
}

THUMB void DebugInfo::addMessageID(int messageID)
{
    for (int i = 0; i < 16; i++) {
        if (messageID_[i] == -1) {
            messageID_[i] = messageID;
            return;
        }
    }
}

THUMB void DebugInfo::unkfunc_02027d1c(int x, int y)
{
    debugPrint(x, y, "MessID");
    for (int i = 0; i < 16; i++) {
        if (messageID_[i] != -1) {
            debugConsolePrintf(x, y + i + 1, "%6d", messageID_[i]);
        } else {
            debugPrint(x, y + i + 1, "------");
        }
    }
    drawDebugWindow(x, y, 6, 17);
}

THUMB void DebugInfo::drawShortMessageIDs(int x, int y)
{
    debugPrint(x, y, "MessID");
    for (int i = 0; i < 6; i++) {
        if (messageID_[i] != -1) {
            debugConsolePrintf(x, y + i + 1, "%6d", messageID_[i]);
        } else {
            debugPrint(x, y + i + 1, "------");
        }
    }
    drawDebugWindow(x, y, 6, 7);
}

THUMB void DebugInfo::drawFlags(int x, int y)
{
    drawFlagTable(x, y, 'G', &g_AreaFlag, areaFlagTop_, 5, &areaFlag_);
    drawFlagTable(x, y + 7, 'A', &g_LocalFlag, localFlagTop_, 5, &localFlag_);
    drawFlagTable(x, y + 14, 'L', &g_GlobalFlag, globalFlagTop_, 5, &globalFlag_);
    drawDebugBox(0, 0, 24, 6);
    drawDebugBox(0, 7, 24, 6);
    drawDebugBox(0, 14, 24, 6);
}

THUMB void DebugInfo::drawFlagTable(int x, int y, char kind, status::GameFlag* flag, int top, int lines, status::GameFlag* prevFlag)
{
    int blink;
    if (getDisplayFrame() & 2) {
        blink = 1;
    } else {
        blink = 0;
    }
    s_flagHeader[0] = kind;
    debugPrint(x, y, s_flagHeader);
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
        debugPrint(x, y + 1 + i, s_flagLine);
    }
}

THUMB void DebugInfo::drawWorldTime(int x, int y)
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
    debugConsolePrintf(x, y, "WORLDTIME");
    debugConsolePrintf(x, y + 1, "%4d/%4d", status::g_StageInfo.getWorldTime(), cmn::WorldLocation::getMaxTime());
    debugConsolePrintf(x + 2, y + 2, timeZoneName);
    drawDebugWindow(x, y, 9, 3);
}

THUMB void DebugInfo::drawPlayTime(int x, int y)
{
    unsigned int playTime = status::g_Game.getPlayTime();
    unsigned int frameCount = data_02101c88.frameCount_;
    debugConsolePrintf(x, y, "PLAY TIME");
    unsigned int hourRest = playTime % 216000;
    unsigned int minuteRest = hourRest % 3600;
    debugConsolePrintf(x, y + 1, "%03d:%02d:%02d.%02d", playTime / 216000, hourRest / 3600, minuteRest / 60, minuteRest % 60 * 100 / 60);
    hourRest = frameCount % 216000;
    minuteRest = hourRest % 3600;
    debugConsolePrintf(x, y + 2, "%03d:%02d:%02d.%02d", frameCount / 216000, hourRest / 3600, minuteRest / 60, minuteRest % 60 * 100 / 60);
    drawDebugWindow(x, y, 11, 3);
}

THUMB void DebugInfo::drawMuseum(int x, int y)
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
    debugConsolePrintf(x, y, "MUSEUM");
    debugConsolePrintf(x, y + 1, "Lv.%d %3d", status::g_MuseumStatus.getMuseumLevel(), status::g_MuseumStatus.museumPoint_);
    debugConsolePrintf(x, y + 2, "Pe %d", status::g_MuseumStatus.penaltyPoint_);
    debugConsolePrintf(x, y + 3, "Be %d %c", status::g_MuseumStatus.beautifulPoint_, beautiful);
    debugConsolePrintf(x, y + 4, "Fu %d %c", status::g_MuseumStatus.funnyPoint_, funny);
    debugConsolePrintf(x, y + 5, "Fe %d %c", status::g_MuseumStatus.fearPoint_, fear);
    drawDebugWindow(x, y, 8, 6);
}

THUMB void DebugInfo::drawHeap(int x, int y)
{
    debugConsolePrintf(x, y, "HEAP");
    debugConsolePrintf(x, y + 1, "%3dK", getAppHeapFreeSize(&data_020fd24c) >> 10);
    debugConsolePrintf(x, y + 2, "VRAM");
    debugConsolePrintf(x, y + 3, "%3dk", data_020f4f74.unk_08 >> 10);
    drawDebugWindow(x, y, 5, 4);
}

THUMB void DebugInfo::drawFriendMonsters(int x, int y)
{
    debugConsolePrintf(x, y, "ALL FRIEND");
    debugConsolePrintf(x, y + 1, "count:%d", status::PlayerDataAll::getFriendMonsterCount());
    debugConsolePrintf(x, y + 2, "WITHOUT EVENT");
    debugConsolePrintf(x, y + 3, "count:%d", status::PlayerDataAll::getFriendMonsterCountWithoutEventMonster());
    drawDebugWindow(x, y, 13, 4);
}

THUMB void DebugInfo::setShowArrayWarning(int show)
{
    showArrayWarning_ = show;
}

THUMB void DebugInfo::clearLog()
{
    showLog_ = 0;
    unk_24 = 1;
    logIndex_ = 0;
    for (int i = 0; i < 24; i++) {
        log_[i][0] = 0;
    }
}

THUMB void DebugInfo::drawLog(int x, int y)
{
    drawDebugWindow(x, y, 30, 16);
    int index = logIndex_ - 16;
    if (index < 0) {
        index += 24;
    }
    for (int i = 0; i < 16; i++) {
        debugConsolePrintf(x, y + i, log_[index]);
        index++;
        if (index == 24) {
            index = 0;
        }
    }
}
