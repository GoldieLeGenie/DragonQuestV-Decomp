#include "main/leveldata/MeisanhinData.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::MeisanhinData* dq5::level::MeisanhinData::getRecord(int index)
{
    return (MeisanhinData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::MeisanhinData::filename_ = "data/leveldata/dq5ds_meisanhin_data.dat";
ExcelBinaryData dq5::level::MeisanhinData::binary_;
void* dq5::level::MeisanhinData::addr_;
dss::File::LoadSwitch dq5::level::MeisanhinData::loadSwitch_;
char dq5::level::MeisanhinData::dataRegion[1400];

THUMB void dq5::level::MeisanhinData::setup()
{
    if (levelData.getLoadType(230) == 0) {
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

THUMB void dq5::level::MeisanhinData::cleanup()
{
}
