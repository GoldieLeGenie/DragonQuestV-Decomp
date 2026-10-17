#include "main/leveldata/VehicleData.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::VehicleData* dq5::level::VehicleData::getRecord(int index)
{
    return (VehicleData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::VehicleData::filename_ = "data/leveldata/dq5ds_vehicles.dat";
ExcelBinaryData dq5::level::VehicleData::binary_;
void* dq5::level::VehicleData::addr_;
dss::File::LoadSwitch dq5::level::VehicleData::loadSwitch_;
char dq5::level::VehicleData::dataRegion[496];

THUMB void dq5::level::VehicleData::setup()
{
    if (levelData.getLoadType(26) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
    getRecord(0);
}

THUMB void dq5::level::VehicleData::cleanup()
{
}
