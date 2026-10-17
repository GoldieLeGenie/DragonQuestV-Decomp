#include "ov029/leveldata/CoinMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::CoinMessage::filename_ = "data/leveldata/dq5ds_coin_message.dat";
ExcelBinaryData dq5::level::CoinMessage::binary_;
void* dq5::level::CoinMessage::addr_;
dss::File::LoadSwitch dq5::level::CoinMessage::loadSwitch_;
char dq5::level::CoinMessage::dataRegion[104];

THUMB void dq5::level::CoinMessage::setup()
{
    if (levelData.getLoadType(128) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::CoinMessage::cleanup()
{
}
