#include "ov004/leveldata/PetalData.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::PetalData* dq5::level::PetalData::getRecord(int index)
{
    return (PetalData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::PetalData::filename_ = "data/leveldata/dq5ds_endhanabira.dat";
ExcelBinaryData dq5::level::PetalData::binary_;
void* dq5::level::PetalData::addr_;
dss::File::LoadSwitch dq5::level::PetalData::loadSwitch_;
char dq5::level::PetalData::dataRegion[248];

THUMB void dq5::level::PetalData::setup()
{
    if (levelData.getLoadType(0xf9) == 0) {
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
