#include "main/leveldata/PartytalkYounen.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::PartytalkYounen::filename_ = "data/leveldata/dq5ds_partytalk_younen.dat";
ExcelBinaryData dq5::level::PartytalkYounen::binary_;
dss::File::LoadSwitch dq5::level::PartytalkYounen::loadSwitch_;
void* dq5::level::PartytalkYounen::addr_;

THUMB void dq5::level::PartytalkYounen::setup()
{
    if (levelData.getLoadType(200) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
}

THUMB void dq5::level::PartytalkYounen::cleanup()
{
    binary_.cleanup(addr_);
}
