#include "ov019/leveldata/ChurchMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::ChurchMessage::filename_ = "data/leveldata/dq5ds_church_message.dat";
ExcelBinaryData dq5::level::ChurchMessage::binary_;
void* dq5::level::ChurchMessage::addr_;
dss::File::LoadSwitch dq5::level::ChurchMessage::loadSwitch_;
char dq5::level::ChurchMessage::dataRegion[528];

THUMB void dq5::level::ChurchMessage::setup()
{
    if (levelData.getLoadType(123) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::ChurchMessage::cleanup()
{
}
