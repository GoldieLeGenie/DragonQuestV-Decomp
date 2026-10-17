#include "ov001/leveldata/FloorBackColor.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FloorBackColor* dq5::level::FloorBackColor::getRecord(int index)
{
    return (FloorBackColor*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FloorBackColor::filename_ = "data/leveldata/dq5ds_back_color.dat";
ExcelBinaryData dq5::level::FloorBackColor::binary_;
void* dq5::level::FloorBackColor::addr_;
dss::File::LoadSwitch dq5::level::FloorBackColor::loadSwitch_;
char dq5::level::FloorBackColor::dataRegion[720];

THUMB void dq5::level::FloorBackColor::setup()
{
    if (levelData.getLoadType(14) == 0) {
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

THUMB void dq5::level::FloorBackColor::cleanup()
{
}
