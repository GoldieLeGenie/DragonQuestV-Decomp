#include "main/leveldata/StadiumMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::StadiumMessage::filename_ = "data/leveldata/dq5ds_stadium_message.dat";
ExcelBinaryData dq5::level::StadiumMessage::binary_;
void* dq5::level::StadiumMessage::addr_;
dss::File::LoadSwitch dq5::level::StadiumMessage::loadSwitch_;
char dq5::level::StadiumMessage::dataRegion[80];

THUMB void dq5::level::StadiumMessage::setup()
{
    if (levelData.getLoadType(134) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
