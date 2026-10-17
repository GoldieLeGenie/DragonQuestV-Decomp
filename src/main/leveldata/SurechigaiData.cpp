#include "main/leveldata/SurechigaiData.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::SurechigaiData::filename_ = "data/leveldata/dq5ds_surechigai_data.dat";
ExcelBinaryData dq5::level::SurechigaiData::binary_;
void* dq5::level::SurechigaiData::addr_;
dss::File::LoadSwitch dq5::level::SurechigaiData::loadSwitch_;
char dq5::level::SurechigaiData::dataRegion[512];

THUMB void dq5::level::SurechigaiData::setup()
{
    if (levelData.getLoadType(231) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::SurechigaiData::cleanup()
{
}
