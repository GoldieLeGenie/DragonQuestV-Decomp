#include "ov001/leveldata/TruckRail.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::TruckRail* dq5::level::TruckRail::getRecord(int index)
{
    return (TruckRail*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::TruckRail::filename_ = "data/leveldata/dq5ds_truck_rail.dat";
ExcelBinaryData dq5::level::TruckRail::binary_;
dss::File::LoadSwitch dq5::level::TruckRail::loadSwitch_;
void* dq5::level::TruckRail::addr_;

THUMB void dq5::level::TruckRail::setup()
{
    if (levelData.getLoadType(221) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::TruckRail::cleanup()
{
    binary_.cleanup(addr_);
}
