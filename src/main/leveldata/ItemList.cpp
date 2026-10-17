#include "main/leveldata/ItemData.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::ItemData* dq5::level::ItemData::getRecord(int index) { return (ItemData*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }

const char* dq5::level::ItemData::filename_ = "data/leveldata/dq5ds_item_list.dat";
ExcelBinaryData dq5::level::ItemData::binary_;
void* dq5::level::ItemData::addr_;
dss::File::LoadSwitch dq5::level::ItemData::loadSwitch_;
char dq5::level::ItemData::dataRegion[11616];

THUMB void dq5::level::ItemData::setup()
{
    if (levelData.getLoadType(17) == 0) {
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
