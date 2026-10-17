#include "main/leveldata/FloorList.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FloorList* dq5::level::FloorList::getRecord(int index)
{
    return (FloorList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FloorList::filename_ = "data/leveldata/dq5ds_floor_list.dat";
ExcelBinaryData dq5::level::FloorList::binary_;
void* dq5::level::FloorList::addr_;
dss::File::LoadSwitch dq5::level::FloorList::loadSwitch_;
char dq5::level::FloorList::dataRegion[10064];

THUMB void dq5::level::FloorList::setup()
{
    if (levelData.getLoadType(1) == 0) {
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
