#include "main/leveldata/PartytalkSeinen.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::PartytalkSeinen::filename_ = "data/leveldata/dq5ds_partytalk_seinen.dat";
ExcelBinaryData dq5::level::PartytalkSeinen::binary_;
dss::File::LoadSwitch dq5::level::PartytalkSeinen::loadSwitch_;
void* dq5::level::PartytalkSeinen::addr_;

THUMB void dq5::level::PartytalkSeinen::setup()
{
    if (levelData.getLoadType(201) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
}

THUMB void dq5::level::PartytalkSeinen::cleanup()
{
    binary_.cleanup(addr_);
}
