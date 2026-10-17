#include "ov001/leveldata/MirrorMessage.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::MirrorMessage* dq5::level::MirrorMessage::getRecord(int index)
{
    return (MirrorMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::MirrorMessage::filename_ = "data/leveldata/dq5ds_mirror_message.dat";
ExcelBinaryData dq5::level::MirrorMessage::binary_;
void* dq5::level::MirrorMessage::addr_;
dss::File::LoadSwitch dq5::level::MirrorMessage::loadSwitch_;
char dq5::level::MirrorMessage::dataRegion[80];

THUMB void dq5::level::MirrorMessage::setup()
{
    if (levelData.getLoadType(20) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::MirrorMessage::cleanup()
{
}
