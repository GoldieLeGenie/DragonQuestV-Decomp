#include "ov032/leveldata/JisanMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::JisanMessage::filename_ = "data/leveldata/dq5ds_jisan_message.dat";
ExcelBinaryData dq5::level::JisanMessage::binary_;
void* dq5::level::JisanMessage::addr_;
dss::File::LoadSwitch dq5::level::JisanMessage::loadSwitch_;
char dq5::level::JisanMessage::dataRegion[600];

THUMB void dq5::level::JisanMessage::setup()
{
    if (levelData.getLoadType(125) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::JisanMessage::cleanup()
{
}
