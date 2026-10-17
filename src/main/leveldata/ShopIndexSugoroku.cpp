#include "main/leveldata/ShopIndexSugoroku.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::ShopIndexSugoroku::filename_ = "data/leveldata/dq5ds_shop_index_sugoroku.dat";
ExcelBinaryData dq5::level::ShopIndexSugoroku::binary_;
void* dq5::level::ShopIndexSugoroku::addr_;
dss::File::LoadSwitch dq5::level::ShopIndexSugoroku::loadSwitch_;
char dq5::level::ShopIndexSugoroku::dataRegion[40];

THUMB void dq5::level::ShopIndexSugoroku::setup()
{
    if (levelData.getLoadType(157) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
