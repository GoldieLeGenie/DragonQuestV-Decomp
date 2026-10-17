#include "main/leveldata/FukuroItem.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FukuroItem* dq5::level::FukuroItem::getRecord(int index)
{
    return (FukuroItem*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FukuroItem::filename_ = "data/leveldata/dq5ds_fukuro_item.dat";
ExcelBinaryData dq5::level::FukuroItem::binary_;
dss::File::LoadSwitch dq5::level::FukuroItem::loadSwitch_;
void* dq5::level::FukuroItem::addr_;

THUMB void dq5::level::FukuroItem::setup()
{
    if (levelData.getLoadType(140) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::FukuroItem::cleanup()
{
    binary_.cleanup(addr_);
}
