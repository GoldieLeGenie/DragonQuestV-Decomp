#include "main/leveldata/PlayerCarriage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::PlayerCarriage::filename_ = "data/leveldata/dq5ds_player_carriage.dat";
ExcelBinaryData dq5::level::PlayerCarriage::binary_;
dss::File::LoadSwitch dq5::level::PlayerCarriage::loadSwitch_;
void* dq5::level::PlayerCarriage::addr_;

THUMB void dq5::level::PlayerCarriage::setup()
{
    if (levelData.getLoadType(211) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
}

THUMB void dq5::level::PlayerCarriage::cleanup()
{
    binary_.cleanup(addr_);
}
