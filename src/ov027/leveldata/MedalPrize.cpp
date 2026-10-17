#include "ov027/leveldata/MedalPrize.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::MedalPrize::filename_ = "data/leveldata/dq5ds_medal_prize.dat";
ExcelBinaryData dq5::level::MedalPrize::binary_;
void* dq5::level::MedalPrize::addr_;
dss::File::LoadSwitch dq5::level::MedalPrize::loadSwitch_;
char dq5::level::MedalPrize::dataRegion[28];

inline dq5::level::MedalPrize* dq5::level::MedalPrize::getRecord(int index)
{
    return (MedalPrize*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

THUMB void dq5::level::MedalPrize::setup()
{
    if (levelData.getLoadType(135) == 0) {
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

THUMB void dq5::level::MedalPrize::cleanup()
{
}
