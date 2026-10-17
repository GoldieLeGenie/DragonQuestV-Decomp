#include "main/leveldata/HukubikiPrize.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::HukubikiPrize::filename_ = "data/leveldata/dq5ds_hukubiki_prize.dat";
ExcelBinaryData dq5::level::HukubikiPrize::binary_;
void* dq5::level::HukubikiPrize::addr_;
dss::File::LoadSwitch dq5::level::HukubikiPrize::loadSwitch_;
char dq5::level::HukubikiPrize::dataRegion[32];

THUMB void dq5::level::HukubikiPrize::setup()
{
    if (levelData.getLoadType(131) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::HukubikiPrize::cleanup()
{
}
