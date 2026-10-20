#pragma ipa file
#include "main/debug/DebugBattleInfo.hpp"
#include "main/debug/DebugInfo.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/menu/UnkMenuDisplays.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/PlayerStatus.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/status/MonsterParty.hpp"

DebugBattleInfo data_020c2ce4;

THUMB DebugBattleInfo::DebugBattleInfo()
{
    type_ = 0;
    index_ = 0;
    showStatusChange_ = 1;
    showHeap_ = 0;
    showLog_ = 0;
}

THUMB void DebugBattleInfo::initialize()
{
    type_ = 0;
    index_ = 0;
    for (int i = 0; i < status::g_Monster.getCount(); i++) {
        status::HaveStatusInfo& info = status::g_Monster.getMonsterStatus(i).haveStatusInfo_;
        info.getHp();
        info.getHpMax();
        info.getMp();
        info.getMpMax();
        info.getStrength(0);
        info.getAgility(0);
        info.getProtection(0);
        info.getWisdom(0);
        info.getLuck(0);
        info.getAttack(0);
        info.getDefence(0);
        btl::BattleMonsterMask::getSingleton()->getMonsterTouchRect(i);
    }
}

THUMB void DebugBattleInfo::draw()
{
    if (showHeap_ != 0) {
        unkfunc_020273fc(1, 1);
    }
    if (showLog_ != 0) {
        drawMessageIDs(1, 7);
    }
    if (type_ == 0 || (type_ == 1 && index_ >= status::g_Party.getCount()) ||
        (type_ == 2 && index_ >= status::g_Monster.getCount())) {
        return;
    }
    int index = index_;
    if (type_ == 1) {
        int command = status::g_Party.getPlayerStatus(index).haveBattleStatus_.actionIndex_;
        debugConsolePrintf(13, 1, "PLAYER NO      %3d", index);
        debugConsolePrintf(13, 2, "                  ");
        debugConsolePrintf(13, 3, "COMMAND        %3d", command);
        drawStatusInfo(13, 5, &status::g_Party.getPlayerStatus(index).haveStatusInfo_);
    }
    if (type_ == 2) {
        int command = status::g_Monster.getMonsterStatus(index).haveBattleStatus_.actionIndex_;
        debugConsolePrintf(13, 1, "MONSTER NO     %3d", index);
        debugConsolePrintf(13, 2, "GROUP NO       %3d", status::g_Monster.getMonsterGroup(index));
        debugConsolePrintf(13, 3, "COMMAND        %3d", command);
        drawStatusInfo(13, 5, &status::g_Monster.getMonsterStatus(index).haveStatusInfo_);
    }
    if (type_ == 2) {
        int* rect = btl::BattleMonsterMask::getSingleton()->getMonsterTouchRect(index);
        if (blink_ > 0) {
            if (blink_ & 1) {
                data_02114dd4.arrow_.addArrow(rect[1] + (rect[3] - rect[1]) / 2, rect[2], 2, 0);
            }
            blink_--;
        }
    }
    drawDebugWindow(13, 1, 18, 19);
    if (showStatusChange_ == 1) {
        drawDebugWindow(13, 25, 18, 19);
    }
}

THUMB void DebugBattleInfo::unkfunc_020273fc(int x, int y)
{
    debugConsolePrintf(x, y, "HEAP");
    debugConsolePrintf(x, y + 1, "%3dK", getAppHeapFreeSize(&data_020fd24c) >> 10);
    debugConsolePrintf(x, y + 2, "VRAM");
    debugConsolePrintf(x, y + 3, "%3dk", data_020f4f74.texVramFree_ >> 10);
    drawDebugWindow(x, y, 4, 4);
}

THUMB void DebugBattleInfo::drawStatusInfo(int x, int y, status::HaveStatusInfo* info)
{
    int hp = info->getHp();
    int hpMax = info->getHpMax();
    int mp = info->getMp();
    int mpMax = info->getMpMax();
    int strength = info->getStrength(0);
    int agility = info->getAgility(0);
    int protection = info->getProtection(0);
    int wisdom = info->getWisdom(0);
    int luck = info->getLuck(0);
    int attack = info->getAttack(0);
    int defence = info->getDefence(0);
    int specialTargetCount = info->getSpecialTargetCount();
    int damageMin = info->effectValueMin_;
    int damageMax = info->effectValueMax_;
    debugConsolePrintf(x, y, "HP/HPMAX %4d/%4d", hp, hpMax);
    debugConsolePrintf(x, y + 1, "MP/MPMAX %4d/%4d", mp, mpMax);
    debugConsolePrintf(x, y + 2, "                  ");
    debugConsolePrintf(x, y + 3, "STRENGTH       %3d", strength);
    debugConsolePrintf(x, y + 4, "AGILITY        %3d", agility);
    debugConsolePrintf(x, y + 5, "PROTECTION     %3d", protection);
    debugConsolePrintf(x, y + 6, "WISDOM         %3d", wisdom);
    debugConsolePrintf(x, y + 7, "LUCK           %3d", luck);
    debugConsolePrintf(x, y + 8, "                  ");
    debugConsolePrintf(x, y + 9, "ATTACK         %3d", attack);
    debugConsolePrintf(x, y + 10, "DEFENCE        %3d", defence);
    debugConsolePrintf(x, y + 11, "                  ");
    debugConsolePrintf(x, y + 12, "SPTARGET CNT   %3d", specialTargetCount);
    debugConsolePrintf(x, y + 13, "DAMAGE MIN     %3d", damageMin);
    debugConsolePrintf(x, y + 14, "DAMAGE MAX     %3d", damageMax);
    if (showStatusChange_ == 1) {
        char mark[] = {'X', 'O'};
        status::StatusChange& statusChange = info->statusChange_;
        debugConsolePrintf(x, 25, "ASTORON          %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_ASTORON) ? 1 : 0]);
        debugConsolePrintf(x, 26, "SPAZZ            %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHI) ? 1 : 0]);
        debugConsolePrintf(x, 27, "SLEEP            %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_NEMURI) ? 1 : 0]);
        debugConsolePrintf(x, 28, "MANUSA           %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MANUSA) ? 1 : 0]);
        debugConsolePrintf(x, 29, "BAIKIRUTO        %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_BAIKIRUTO) ? 1 : 0]);
        debugConsolePrintf(x, 30, "FUBAHA           %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_FUBAHA) ? 1 : 0]);
        debugConsolePrintf(x, 31, "MAHOKANTA        %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOKANTA) ? 1 : 0]);
        debugConsolePrintf(x, 32, "MOSYASU          %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MOSYASU) ? 1 : 0]);
        debugConsolePrintf(x, 33, "POWER SAVE       %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_TAMEKEI) ? 1 : 0]);
        debugConsolePrintf(x, 34, "MAHOTON          %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_MAHOTON) ? 1 : 0]);
        debugConsolePrintf(x, 35, "DRAGORAM         %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_DORAGORAM) ? 1 : 0]);
        debugConsolePrintf(x, 36, "CONFUSION        %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_KONRAN) ? 1 : 0]);
        debugConsolePrintf(x, 37, "PATH 1           %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_PATH_1) ? 1 : 0]);
        debugConsolePrintf(x, 38, "POISON           %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_DOKU) ? 1 : 0]);
        debugConsolePrintf(x, 39, "DEFENCE CHANGE   %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_DF_HENKA) ? 1 : 0]);
        debugConsolePrintf(x, 40, "AGILITY CHANGE   %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_SPD_PLUS) ? 1 : 0]);
        debugConsolePrintf(x, 41, "DEFENCE          %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_DEFENCE) ? 1 : 0]);
        debugConsolePrintf(x, 42, "TIME STOP        %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_TIMESTOP) ? 1 : 0]);
        debugConsolePrintf(x, 43, "FIZZLE ZONE      %c", mark[statusChange.isEnable(dq5::level::ActionParam::ACTIONTYPE_FIZZLEZONE) ? 1 : 0]);
    }
}

THUMB void DebugBattleInfo::drawMessageIDs(int x, int y)
{
    data_020c2d10.drawShortMessageIDs(x, y);
}
