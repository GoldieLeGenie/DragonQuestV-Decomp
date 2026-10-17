#include "main/leveldata/TruckSwitch.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::TruckSwitch* dq5::level::TruckSwitch::getRecord(int index)
{
    return (TruckSwitch*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::TruckSwitch::filename_ = "data/leveldata/dq5ds_town_truck_switch.dat";
ExcelBinaryData dq5::level::TruckSwitch::binary_;
dss::File::LoadSwitch dq5::level::TruckSwitch::loadSwitch_;
void* dq5::level::TruckSwitch::addr_;

THUMB void dq5::level::TruckSwitch::setup()
{
    if (levelData.getLoadType(223) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::TruckSwitch::cleanup()
{
    binary_.cleanup(addr_);
}
