#pragma ipa file
#include "main/part/UnkBattleMenuPart.hpp"
#include "main/btl/Encount.hpp"
#include "main/btl/UnkBattleMapList.hpp"
#include "main/data/FileLoader.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/status/StageAttribute.hpp"
#include "nitro/g3.hpp"

inline void btl::Encount::setTileId(int id)
{
    tileId_ = id;
    encountData_.setTileId(id);
}

inline void btl::Encount::setMonsterIndex(int group, int index)
{
    monsterIndex_[group] = index;
}

inline void btl::Encount::setMonsterCount(int group, int count)
{
    monsterCount_[group] = count;
}

// the dss header templates: their instances are emitted in this file (loop<long>: HaveBattleStatus.cpp emits
// its own loop<int> copy)
namespace dss {
    template <typename T> T max(T a, T b)
    {
        return (a > b) ? a : b;
    }

    template <typename T> T min(T a, T b)
    {
        return (a < b) ? a : b;
    }

    template <typename T> T clamp(T a, T b, T c)
    {
        return min(max(a, b), c);
    }

    template <typename T> T loop(T x, T a, T b)
    {
        if (x > b) {
            return a;
        }
        if (x < a) {
            return b;
        }
        return x;
    }
}

UnkBattleMenuPart data_0209cf54;

THUMB UnkBattleMenuPart::UnkBattleMenuPart()
{
    tileId_ = 1;
    timeZone_ = 0;
    group_ = 0;
    monster_[0] = 0;
    count_[0] = 1;
    monster_[1] = 0;
    count_[1] = 0;
    monster_[2] = 0;
    count_[2] = 0;
    monster_[3] = 0;
    count_[3] = 0;
}

THUMB void UnkBattleMenuPart::initialize()
{
    x_ = 0;
    y_ = 2;
    cursor_ = 0;
    mode_ = 0;
    isStart_ = 0;
    if (data_0209ce6c.unkfunc_0206da30() == 0) {
        data_0209ce6c.unkfunc_0206da18("data/btlmap/_list.txt");
    }
    g_Global.fadeIn(30);
}

THUMB void UnkBattleMenuPart::terminate()
{
}

THUMB void UnkBattleMenuPart::onExecutePart()
{
    char path[128];

    if (dss::g_Pad.edge() & 0x40) {
        cursor_--;
    }
    if (dss::g_Pad.edge() & 0x80) {
        cursor_++;
    }
    data_020f6f9c.unkfunc_0204affc();
    if (cursor_ == 0) {
        if (dss::g_Pad.edge() & 0x10) {
            mode_ = 1;
        }
        if (dss::g_Pad.edge() & 0x20) {
            mode_ = 0;
        }
    }
    if (mode_ == 0) {
        unkfunc_0200928c();
        cursor_ = dss::loop<long>(cursor_, 0, 4);
    }
    if (mode_ == 1) {
        unkfunc_02009378();
        cursor_ = dss::loop<long>(cursor_, 0, 5);
    }
    if (isStart_ != 0) {
        return;
    }
    if (!(dss::g_Pad.edge() & 1)) {
        return;
    }
    isStart_ = 1;
    dss::sprintf_s(path, sizeof(path), "data/btlmap/%s.lz", data_0209ce6c.unkfunc_0206db60());
    if (!dss::g_File.isExist(path, dss::File::None)) {
        return;
    }
    if (mode_ == 0) {
        btl::Encount::getSingleton()->setTileId(tileId_);
        btl::Encount::getSingleton()->brew();
    } else if (mode_ == 1) {
        for (int i = 0; i < 4; i++) {
            btl::Encount::getSingleton()->setMonsterIndex(i, monster_[i]);
            btl::Encount::getSingleton()->setMonsterCount(i, count_[i]);
        }
    }
    status::g_StageAttribute.setBtlMapName(data_0209ce6c.unkfunc_0206db60());
    g_Global.directStartBattle();
}

THUMB void UnkBattleMenuPart::onDrawPart()
{
    data_020f6f9c.unkfunc_0204b04c(x_, y_ + cursor_, ">");
    if (mode_ == 0) {
        data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_, "1.Mode : Encount");
        unkfunc_02009504();
    }
    if (mode_ == 1) {
        data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_, "1.Mode : Select");
        unkfunc_0200959c();
    }
}

THUMB void UnkBattleMenuPart::onWindowPart()
{
}

THUMB void UnkBattleMenuPart::onDebugPart()
{
    data_020f6f9c.unkfunc_0204b04c(0, 0, "Battle Menu Part", REG_GFX_RAM_COUNT);
}

THUMB void UnkBattleMenuPart::unkfunc_0200928c()
{
    switch (cursor_) {
    case 0:
        break;
    case 1:
        if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
            tileId_++;
        }
        if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
            tileId_--;
        }
        break;
    case 2:
        if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
            timeZone_++;
        }
        if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
            timeZone_--;
        }
        timeZone_ = dss::clamp<int>(timeZone_, 0, 2);
        break;
    case 3:
        if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
            data_0209ce6c.unkfunc_0206da44();
        }
        if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
            data_0209ce6c.unkfunc_0206dac4();
        }
        break;
    case 4:
        if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
            data_0209ce6c.unkfunc_0206db74();
        }
        if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
            data_0209ce6c.unkfunc_0206dbdc();
        }
        break;
    }
}

THUMB void UnkBattleMenuPart::unkfunc_02009378()
{
    switch (cursor_) {
    case 0:
        break;
    case 1:
        if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
            group_++;
        }
        if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
            group_--;
        }
        group_ = dss::clamp<int>(group_, 0, 3);
        break;
    case 2:
        if (dss::g_Pad.pad() & 0x100) {
            if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
                monster_[group_] += 10;
            }
            if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
                monster_[group_] -= 10;
            }
        } else {
            if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
                monster_[group_]++;
            }
            if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
                monster_[group_]--;
            }
        }
        monster_[group_] = dss::clamp<int>(monster_[group_], 0, 0x140);
        break;
    case 3:
        if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
            count_[group_]++;
        }
        if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
            count_[group_]--;
        }
        count_[group_] = dss::clamp<int>(count_[group_], 0, 8);
        break;
    case 4:
        if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
            data_0209ce6c.unkfunc_0206da44();
        }
        if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
            data_0209ce6c.unkfunc_0206dac4();
        }
        break;
    case 5:
        if (dss::g_Pad.unkfunc_0204bc00() & 0x10) {
            data_0209ce6c.unkfunc_0206db74();
        }
        if (dss::g_Pad.unkfunc_0204bc00() & 0x20) {
            data_0209ce6c.unkfunc_0206dbdc();
        }
        break;
    }
}

THUMB void UnkBattleMenuPart::unkfunc_02009504()
{
    data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_ + 1, "2.Encount Tile : %3d", tileId_);
    char timeZone[3][8] = { "None", "Day", "Night" };
    data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_ + 2, "3.Time Zone    : %s", timeZone[timeZone_]);
    data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_ + 3, "4.Group        : %s", data_0209ce6c.unkfunc_0206da34());
    data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_ + 4, "5.Map          : %s", data_0209ce6c.unkfunc_0206db60());
}

THUMB void UnkBattleMenuPart::unkfunc_0200959c()
{
    data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_ + 1, "2.GROUP   : %d", group_ + 1);
    data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_ + 2, "3.MONSTER : m%03d", monster_[group_]);
    data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_ + 3, "4.COUNT   : %d", count_[group_]);
    data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_ + 4, "5.Group   : %s", data_0209ce6c.unkfunc_0206da34());
    data_020f6f9c.unkfunc_0204b04c(x_ + 1, y_ + 5, "6.Map     : %s", data_0209ce6c.unkfunc_0206db60());
    data_020f6f9c.unkfunc_0204b04c(x_ + 0x18, y_ + 1, "m%03d(%d)", monster_[0], count_[0]);
    data_020f6f9c.unkfunc_0204b04c(x_ + 0x18, y_ + 2, "m%03d(%d)", monster_[1], count_[1]);
    data_020f6f9c.unkfunc_0204b04c(x_ + 0x18, y_ + 3, "m%03d(%d)", monster_[2], count_[2]);
    data_020f6f9c.unkfunc_0204b04c(x_ + 0x18, y_ + 4, "m%03d(%d)", monster_[3], count_[3]);
}
