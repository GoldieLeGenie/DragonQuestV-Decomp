#include "main/leveldata/ShopIndex2.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::ShopIndex2::filename_ = "data/leveldata/dq5ds_shop_Index_2.dat";
ExcelBinaryData dq5::level::ShopIndex2::binary_;
void* dq5::level::ShopIndex2::addr_;
dss::File::LoadSwitch dq5::level::ShopIndex2::loadSwitch_;
char dq5::level::ShopIndex2::dataRegion[40];

THUMB void dq5::level::ShopIndex2::setup()
{
    if (levelData.getLoadType(119) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
