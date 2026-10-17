#include "ov027/leveldata/MedalMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::MedalMessage::filename_ = "data/leveldata/dq5ds_medal_message.dat";
ExcelBinaryData dq5::level::MedalMessage::binary_;
void* dq5::level::MedalMessage::addr_;
dss::File::LoadSwitch dq5::level::MedalMessage::loadSwitch_;
char dq5::level::MedalMessage::dataRegion[168];

THUMB void dq5::level::MedalMessage::setup()
{
    if (levelData.getLoadType(122) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::MedalMessage::cleanup()
{
}
