#include "main/leveldata/SplitMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::SplitMessage::filename_ = "data/leveldata/dq5ds_split_message.dat";
ExcelBinaryData dq5::level::SplitMessage::binary_;
void* dq5::level::SplitMessage::addr_;
dss::File::LoadSwitch dq5::level::SplitMessage::loadSwitch_;
char dq5::level::SplitMessage::dataRegion[2440];

THUMB void dq5::level::SplitMessage::setup()
{
    if (levelData.getLoadType(18) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
