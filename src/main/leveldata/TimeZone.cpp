#include "main/leveldata/TimeZone.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::TimeZone* dq5::level::TimeZone::getRecord(int index)
{
    return (TimeZone*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::TimeZone::filename_ = "data/leveldata/dq5ds_timezone.dat";
ExcelBinaryData dq5::level::TimeZone::binary_;
void* dq5::level::TimeZone::addr_;
dss::File::LoadSwitch dq5::level::TimeZone::loadSwitch_;
char dq5::level::TimeZone::dataRegion[32];

THUMB void dq5::level::TimeZone::setup()
{
    if (levelData.getLoadType(23) == 0) {
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
