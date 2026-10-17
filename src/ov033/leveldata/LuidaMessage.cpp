#include "ov033/leveldata/LuidaMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::LuidaMessage::filename_ = "data/leveldata/dq5ds_luida_message.dat";
ExcelBinaryData dq5::level::LuidaMessage::binary_;
void* dq5::level::LuidaMessage::addr_;
dss::File::LoadSwitch dq5::level::LuidaMessage::loadSwitch_;
char dq5::level::LuidaMessage::dataRegion[240];

THUMB void dq5::level::LuidaMessage::setup()
{
    if (levelData.getLoadType(0) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::LuidaMessage::cleanup()
{
}
