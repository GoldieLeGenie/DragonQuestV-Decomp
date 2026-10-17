#include "ov027/leveldata/GiftMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::GiftMessage::filename_ = "data/leveldata/dq5ds_gift_message.dat";
ExcelBinaryData dq5::level::GiftMessage::binary_;
void* dq5::level::GiftMessage::addr_;
dss::File::LoadSwitch dq5::level::GiftMessage::loadSwitch_;
char dq5::level::GiftMessage::dataRegion[184];

THUMB void dq5::level::GiftMessage::setup()
{
    if (levelData.getLoadType(129) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::GiftMessage::cleanup()
{
}
