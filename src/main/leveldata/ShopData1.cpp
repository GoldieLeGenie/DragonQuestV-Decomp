#include "main/leveldata/ShopData1.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::ShopData1::filename_ = "data/leveldata/dq5ds_shop_data_1.dat";
ExcelBinaryData dq5::level::ShopData1::binary_;
void* dq5::level::ShopData1::addr_;
dss::File::LoadSwitch dq5::level::ShopData1::loadSwitch_;
char dq5::level::ShopData1::dataRegion[80];

THUMB void dq5::level::ShopData1::setup()
{
    if (levelData.getLoadType(118) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
