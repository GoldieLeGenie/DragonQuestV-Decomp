#include "ov030/leveldata/GoldMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::GoldMessage::filename_ = "data/leveldata/dq5ds_bank_message.dat";
ExcelBinaryData dq5::level::GoldMessage::binary_;
void* dq5::level::GoldMessage::addr_;
dss::File::LoadSwitch dq5::level::GoldMessage::loadSwitch_;
char dq5::level::GoldMessage::dataRegion[184];

THUMB void dq5::level::GoldMessage::setup()
{
    if (levelData.getLoadType(130) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::GoldMessage::cleanup()
{
}
