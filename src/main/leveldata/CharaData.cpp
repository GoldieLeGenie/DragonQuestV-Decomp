#include "main/leveldata/CharaData.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::CharaData::filename_ = "data/leveldata/dq5ds_chara_data.dat";
ExcelBinaryData dq5::level::CharaData::binary_;
void* dq5::level::CharaData::addr_;
dss::File::LoadSwitch dq5::level::CharaData::loadSwitch_;
char dq5::level::CharaData::dataRegion[2048];

THUMB void dq5::level::CharaData::setup()
{
    if (levelData.getLoadType(16) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
