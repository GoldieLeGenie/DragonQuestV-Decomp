#include "ov023/leveldata/InnMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::InnMessage::filename_ = "data/leveldata/dq5ds_inn_message.dat";
ExcelBinaryData dq5::level::InnMessage::binary_;
void* dq5::level::InnMessage::addr_;
dss::File::LoadSwitch dq5::level::InnMessage::loadSwitch_;
char dq5::level::InnMessage::dataRegion[128];

THUMB void dq5::level::InnMessage::setup()
{
    if (levelData.getLoadType(127) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::InnMessage::cleanup()
{
}
