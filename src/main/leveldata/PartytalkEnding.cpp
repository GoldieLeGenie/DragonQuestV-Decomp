#include "main/leveldata/PartytalkEnding.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::PartytalkEnding::filename_ = "data/leveldata/dq5ds_partytalk_ending.dat";
ExcelBinaryData dq5::level::PartytalkEnding::binary_;
dss::File::LoadSwitch dq5::level::PartytalkEnding::loadSwitch_;
void* dq5::level::PartytalkEnding::addr_;

THUMB void dq5::level::PartytalkEnding::setup()
{
    if (levelData.getLoadType(203) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
}

THUMB void dq5::level::PartytalkEnding::cleanup()
{
    binary_.cleanup(addr_);
}
