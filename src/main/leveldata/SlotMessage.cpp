#include "main/leveldata/SlotMessage.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::SlotMessage::filename_ = "data/leveldata/dq5ds_slot_message.dat";
ExcelBinaryData dq5::level::SlotMessage::binary_;
void* dq5::level::SlotMessage::addr_;
dss::File::LoadSwitch dq5::level::SlotMessage::loadSwitch_;
char dq5::level::SlotMessage::dataRegion[80];

THUMB void dq5::level::SlotMessage::setup()
{
    if (levelData.getLoadType(133) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
