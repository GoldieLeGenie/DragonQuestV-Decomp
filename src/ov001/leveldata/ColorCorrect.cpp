#include "main/leveldata/ColorCorrect.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::ColorCorrect::filename_ = "data/leveldata/dq5ds_color_correct.dat";
ExcelBinaryData dq5::level::ColorCorrect::binary_;
void* dq5::level::ColorCorrect::addr_;
dss::File::LoadSwitch dq5::level::ColorCorrect::loadSwitch_;
char dq5::level::ColorCorrect::dataRegion[1024];

THUMB void dq5::level::ColorCorrect::setup()
{
    if (levelData.getLoadType(7) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::ColorCorrect::cleanup()
{
}
