#include "main/leveldata/AppriseItem.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::AppriseItem::filename_ = "data/leveldata/dq5ds_apprise_item.dat";
ExcelBinaryData dq5::level::AppriseItem::binary_;
void* dq5::level::AppriseItem::addr_;
dss::File::LoadSwitch dq5::level::AppriseItem::loadSwitch_;
char dq5::level::AppriseItem::dataRegion[400];

THUMB void dq5::level::AppriseItem::setup()
{
    if (levelData.getLoadType(4) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}
