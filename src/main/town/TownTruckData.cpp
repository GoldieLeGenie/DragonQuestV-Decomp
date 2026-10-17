#include "main/town/TownTruckData.hpp"
#include "main/leveldata/TruckGoal.hpp"
#include "main/leveldata/TruckSwitch.hpp"
#include "main/status/StageInfo.hpp"

inline unsigned int ExcelBinaryData::getRecordCount()
{
    return record_;
}

inline dq5::level::TruckSwitch* dq5::level::TruckSwitch::getRecord(int index)
{
    return (TruckSwitch*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::TruckSwitch::getArraySize()
{
    return binary_.getRecordCount();
}

inline unsigned short dq5::level::TruckSwitch::getRailUid()
{
    return railUid;
}

inline unsigned short dq5::level::TruckSwitch::getSplit()
{
    return split;
}

inline unsigned short dq5::level::TruckSwitch::getSwitchUid()
{
    return switchUid;
}

inline char dq5::level::TruckSwitch::getSwitchAnim()
{
    return byte_1 & 7;
}

inline char dq5::level::TruckSwitch::getRailAnim()
{
    return (byte_1 & 0x38) >> 3;
}

inline dq5::level::TruckGoal* dq5::level::TruckGoal::getRecord(int index)
{
    return (TruckGoal*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::TruckGoal::getArraySize()
{
    return binary_.getRecordCount();
}

inline int dq5::level::TruckGoal::getX()
{
    return X;
}

inline int dq5::level::TruckGoal::getY()
{
    return Y;
}

inline int dq5::level::TruckGoal::getZ()
{
    return Z;
}

inline unsigned short dq5::level::TruckGoal::getFloor()
{
    return floor;
}

inline unsigned short dq5::level::TruckGoal::getUid()
{
    return uid;
}

inline short dq5::level::TruckGoal::getDir()
{
    return dir;
}

inline void twn::TownTruckWagon::setMap(short map)
{
    map_ = map;
}

inline void twn::TownTruckWagon::setUid(short uid)
{
    uid_ = uid;
}

inline void twn::TownTruckWagon::setPos(dss::Fix32Vector3& pos)
{
    pos_ = pos;
}

inline void twn::TownTruckWagon::setIdx(short idx)
{
    idx_ = idx;
}

twn::TownTruckWagon twn::wagon_[20];
int twn::wagonCount_;
twn::TownTruckSwitch twn::switch_[25];
int twn::switchCount_;
twn::TownTruckSeesaw twn::seesaw_;

THUMB void twn::loadAfterSetup()
{
    dq5::level::TruckSwitch::setup();
    unsigned int& switchInit = status::g_StageInfo.switchInitFlag_;
    unsigned int& switchData = status::g_StageInfo.switchDataFlag_;
    switchCount_ = 0;
    int max = dq5::level::TruckSwitch::getArraySize();
    for (int i = 0; i < max; i++) {
        if (switchInit & (1 << i)) {
            int switchAnim = dq5::level::TruckSwitch::getRecord(i)->getSwitchAnim();
            int railAnim = dq5::level::TruckSwitch::getRecord(i)->getRailAnim();
            if (switchData & (1 << i)) {
                switchAnim = getSetupData(switchAnim);
                railAnim = getSetupData(railAnim);
            }
            switch_[switchCount_].setupSwitch(dq5::level::TruckSwitch::getRecord(i)->getSplit(), dq5::level::TruckSwitch::getRecord(i)->getSwitchUid(), switchAnim,
                                              dq5::level::TruckSwitch::getRecord(i)->getRailUid(), railAnim);
            switchCount_++;
        }
    }
    seesaw_.setup();
    if (switchData & (1 << 30)) {
        seesaw_.seesawSwitch(false);
    }
    dq5::level::TruckSwitch::cleanup();
    dq5::level::TruckGoal::setup();
    wagonCount_ = 0;
    max = dq5::level::TruckGoal::getArraySize();
    for (int i = 0; i < max; i++) {
        unsigned int wagonData;
        int shift;
        if (i < 20) {
            wagonData = status::g_StageInfo.wagonData1Flag_;
            shift = i;
        } else {
            wagonData = status::g_StageInfo.wagonData2Flag_;
            shift = i - 20;
        }
        if (wagonData & (1 << shift)) {
            wagon_[wagonCount_].setMap(dq5::level::TruckGoal::getRecord(i)->getFloor());
            wagon_[wagonCount_].setIdx(dq5::level::TruckGoal::getRecord(i)->getDir());
            wagon_[wagonCount_].setUid(dq5::level::TruckGoal::getRecord(i)->getUid());
            dss::Fix32Vector3 pos;
            pos.vx.value = dq5::level::TruckGoal::getRecord(i)->getX();
            pos.vy.value = dq5::level::TruckGoal::getRecord(i)->getY();
            pos.vz.value = dq5::level::TruckGoal::getRecord(i)->getZ();
            wagon_[wagonCount_].setPos(pos);
            wagonCount_++;
        }
    }
    dq5::level::TruckGoal::cleanup();
}

THUMB int twn::getSetupData(int animNo)
{
    if (animNo == 3) {
        return 1;
    }
    return 3;
}

THUMB twn::TownTruckWagon::TownTruckWagon()
{
}
