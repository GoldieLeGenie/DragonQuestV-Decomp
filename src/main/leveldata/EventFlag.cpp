#include "main/leveldata/EventFlag.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::EventFlag::filename_ = "data/leveldata/dq5ds_event_flag.dat";
ExcelBinaryData dq5::level::EventFlag::binary_;
dss::File::LoadSwitch dq5::level::EventFlag::loadSwitch_;
void* dq5::level::EventFlag::addr_;

THUMB void dq5::level::EventFlag::setup()
{
    if (levelData.getLoadType(3) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
}

THUMB void dq5::level::EventFlag::cleanup()
{
    binary_.cleanup(addr_);
}
