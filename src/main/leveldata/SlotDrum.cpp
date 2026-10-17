#include "main/leveldata/SlotDrum.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::SlotDrum* dq5::level::SlotDrum::getRecord(int index)
{
    return (SlotDrum*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::SlotDrum::filename_ = "data/leveldata/dq5ds_slot_drum.dat";
ExcelBinaryData dq5::level::SlotDrum::binary_;
void* dq5::level::SlotDrum::addr_;
dss::File::LoadSwitch dq5::level::SlotDrum::loadSwitch_;
char dq5::level::SlotDrum::dataRegion[640];

THUMB void dq5::level::SlotDrum::setup()
{
    if (levelData.getLoadType(171) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
    getRecord(0);
}
