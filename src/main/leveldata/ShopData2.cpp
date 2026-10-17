#include "main/leveldata/ShopData2.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::ShopData2::filename_ = "data/leveldata/dq5ds_shop_data_2.dat";
ExcelBinaryData dq5::level::ShopData2::binary_;
void* dq5::level::ShopData2::addr_;
dss::File::LoadSwitch dq5::level::ShopData2::loadSwitch_;
char dq5::level::ShopData2::dataRegion[80];

THUMB void dq5::level::ShopData2::setup()
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
