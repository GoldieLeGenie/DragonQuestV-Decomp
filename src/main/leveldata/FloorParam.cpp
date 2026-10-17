#include "main/leveldata/FloorParam.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::FloorParam::filename_ = "data/leveldata/dq5ds_floor_param.dat";
ExcelBinaryData dq5::level::FloorParam::binary_;
void* dq5::level::FloorParam::addr_;
dss::File::LoadSwitch dq5::level::FloorParam::loadSwitch_;
char dq5::level::FloorParam::dataRegion[120];

THUMB void dq5::level::FloorParam::setup()
{
    if (levelData.getLoadType(27) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
