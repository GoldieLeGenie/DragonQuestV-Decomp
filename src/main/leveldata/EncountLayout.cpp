#include "main/leveldata/EncountLayout.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::EncountLayout* dq5::level::EncountLayout::getRecord(int index)
{
    return (EncountLayout*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::EncountLayout::filename_ = "data/leveldata/dq5ds_encount_layout.dat";
ExcelBinaryData dq5::level::EncountLayout::binary_;
void* dq5::level::EncountLayout::addr_;
dss::File::LoadSwitch dq5::level::EncountLayout::loadSwitch_;
char dq5::level::EncountLayout::dataRegion[1120];

THUMB void dq5::level::EncountLayout::setup()
{
    if (levelData.getLoadType(22) == 0) {
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
