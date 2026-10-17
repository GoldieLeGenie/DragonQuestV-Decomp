#include "main/leveldata/FurnitureList.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FurnitureList* dq5::level::FurnitureList::getRecord(int index)
{
    return (FurnitureList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FurnitureList::filename_ = "data/leveldata/dq5ds_furniture_list.dat";
ExcelBinaryData dq5::level::FurnitureList::binary_;
dss::File::LoadSwitch dq5::level::FurnitureList::loadSwitch_;
void* dq5::level::FurnitureList::addr_;

THUMB void dq5::level::FurnitureList::setup()
{
    if (levelData.getLoadType(180) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::FurnitureList::cleanup()
{
    binary_.cleanup(addr_);
}
