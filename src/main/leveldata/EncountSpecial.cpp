#include "main/leveldata/EncountSpecial.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::EncountSpecial::filename_ = "data/leveldata/dq5ds_encount_special.dat";
ExcelBinaryData dq5::level::EncountSpecial::binary_;
void* dq5::level::EncountSpecial::addr_;
dss::File::LoadSwitch dq5::level::EncountSpecial::loadSwitch_;
char dq5::level::EncountSpecial::dataRegion[80];

THUMB void dq5::level::EncountSpecial::setup()
{
    if (levelData.getLoadType(11) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
