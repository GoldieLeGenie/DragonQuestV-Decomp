#include "main/leveldata/ShopIndex1.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::ShopIndex1* dq5::level::ShopIndex1::getRecord(int index)
{
    return (ShopIndex1*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::ShopIndex1::filename_ = "data/leveldata/dq5ds_shop_index_1.dat";
ExcelBinaryData dq5::level::ShopIndex1::binary_;
void* dq5::level::ShopIndex1::addr_;
dss::File::LoadSwitch dq5::level::ShopIndex1::loadSwitch_;
char dq5::level::ShopIndex1::dataRegion[16];

THUMB void dq5::level::ShopIndex1::setup()
{
    if (levelData.getLoadType(0) == 0) {
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
