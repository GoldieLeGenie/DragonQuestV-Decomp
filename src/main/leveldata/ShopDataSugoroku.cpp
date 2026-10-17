#include "main/leveldata/ShopDataSugoroku.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::ShopDataSugoroku::filename_ = "data/leveldata/dq5ds_shop_data_sugoroku.dat";
ExcelBinaryData dq5::level::ShopDataSugoroku::binary_;
void* dq5::level::ShopDataSugoroku::addr_;
dss::File::LoadSwitch dq5::level::ShopDataSugoroku::loadSwitch_;
char dq5::level::ShopDataSugoroku::dataRegion[80];

THUMB void dq5::level::ShopDataSugoroku::setup()
{
    if (levelData.getLoadType(156) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
