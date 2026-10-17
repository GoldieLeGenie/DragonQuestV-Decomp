#include "main/leveldata/ShopData3.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::ShopData3::filename_ = "data/leveldata/dq5ds_shop_data_3.dat";
ExcelBinaryData dq5::level::ShopData3::binary_;
void* dq5::level::ShopData3::addr_;
dss::File::LoadSwitch dq5::level::ShopData3::loadSwitch_;
char dq5::level::ShopData3::dataRegion[80];

THUMB void dq5::level::ShopData3::setup()
{
    if (levelData.getLoadType(120) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
