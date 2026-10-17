#include "ov031/leveldata/HukubikiMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::HukubikiMessage::filename_ = "data/leveldata/dq5ds_hukubiki_message.dat";
ExcelBinaryData dq5::level::HukubikiMessage::binary_;
void* dq5::level::HukubikiMessage::addr_;
dss::File::LoadSwitch dq5::level::HukubikiMessage::loadSwitch_;
char dq5::level::HukubikiMessage::dataRegion[240];

THUMB void dq5::level::HukubikiMessage::setup()
{
    if (levelData.getLoadType(124) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::HukubikiMessage::cleanup()
{
}
