#include "ov027/leveldata/ShopMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::ShopMessage::filename_ = "data/leveldata/dq5ds_shop_message.dat";
ExcelBinaryData dq5::level::ShopMessage::binary_;
void* dq5::level::ShopMessage::addr_;
dss::File::LoadSwitch dq5::level::ShopMessage::loadSwitch_;
char dq5::level::ShopMessage::dataRegion[780];

THUMB void dq5::level::ShopMessage::setup()
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

THUMB void dq5::level::ShopMessage::cleanup()
{
}
