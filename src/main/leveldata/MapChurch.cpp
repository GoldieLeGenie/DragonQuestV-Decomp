#include "main/leveldata/MapChurch.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::MapChurch* dq5::level::MapChurch::getRecord(int index)
{
    return (MapChurch*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::MapChurch::filename_ = "data/leveldata/dq5ds_map_church.dat";
ExcelBinaryData dq5::level::MapChurch::binary_;
void* dq5::level::MapChurch::addr_;
dss::File::LoadSwitch dq5::level::MapChurch::loadSwitch_;
char dq5::level::MapChurch::dataRegion[980];

THUMB void dq5::level::MapChurch::setup()
{
    if (levelData.getLoadType(19) == 0) {
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

THUMB void dq5::level::MapChurch::cleanup()
{
}
