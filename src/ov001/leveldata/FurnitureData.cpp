#include "ov001/leveldata/FurnitureData.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FurnitureData* dq5::level::FurnitureData::getRecord(int index)
{
    return (FurnitureData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FurnitureData::filename_ = "data/leveldata/dq5ds_furniture_data.dat";
ExcelBinaryData dq5::level::FurnitureData::binary_;
void* dq5::level::FurnitureData::addr_;
dss::File::LoadSwitch dq5::level::FurnitureData::loadSwitch_;
char dq5::level::FurnitureData::dataRegion[200];

THUMB void dq5::level::FurnitureData::setup()
{
    if (levelData.getLoadType(181) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::FurnitureData::cleanup()
{
}
