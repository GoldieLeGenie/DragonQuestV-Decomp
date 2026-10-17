#include "main/leveldata/EncountData.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::EncountData::filename_ = "data/leveldata/dq5ds_encount_data.dat";
ExcelBinaryData dq5::level::EncountData::binary_;
void* dq5::level::EncountData::addr_;
dss::File::LoadSwitch dq5::level::EncountData::loadSwitch_;
char dq5::level::EncountData::dataRegion[280];

THUMB void dq5::level::EncountData::setup()
{
    if (levelData.getLoadType(9) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
