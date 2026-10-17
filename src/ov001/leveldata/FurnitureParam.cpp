#include "ov001/leveldata/FurnitureParam.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FurnitureParam* dq5::level::FurnitureParam::getRecord(int index)
{
    return (FurnitureParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FurnitureParam::filename_ = "data/leveldata/dq5ds_furniture_param.dat";
ExcelBinaryData dq5::level::FurnitureParam::binary_;
void* dq5::level::FurnitureParam::addr_;
dss::File::LoadSwitch dq5::level::FurnitureParam::loadSwitch_;
char dq5::level::FurnitureParam::dataRegion[1800];

THUMB void dq5::level::FurnitureParam::setup()
{
    if (levelData.getLoadType(182) == 0) {
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

THUMB void dq5::level::FurnitureParam::cleanup()
{
}
