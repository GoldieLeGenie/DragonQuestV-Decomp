#include "main/leveldata/PokerMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::PokerMessage::filename_ = "data/leveldata/dq5ds_poker_message.dat";
ExcelBinaryData dq5::level::PokerMessage::binary_;
void* dq5::level::PokerMessage::addr_;
dss::File::LoadSwitch dq5::level::PokerMessage::loadSwitch_;
char dq5::level::PokerMessage::dataRegion[128];

THUMB void dq5::level::PokerMessage::setup()
{
    if (levelData.getLoadType(132) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
