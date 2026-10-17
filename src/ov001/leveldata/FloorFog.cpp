#include "ov001/leveldata/FloorFog.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FloorFog* dq5::level::FloorFog::getRecord(int index)
{
    return (FloorFog*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FloorFog::filename_ = "data/leveldata/dq5ds_fog_data.dat";
ExcelBinaryData dq5::level::FloorFog::binary_;
void* dq5::level::FloorFog::addr_;
dss::File::LoadSwitch dq5::level::FloorFog::loadSwitch_;
char dq5::level::FloorFog::dataRegion[60];

THUMB void dq5::level::FloorFog::setup()
{
    if (levelData.getLoadType(15) == 0) {
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

THUMB void dq5::level::FloorFog::cleanup()
{
}
