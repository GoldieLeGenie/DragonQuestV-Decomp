#include "main/leveldata/ActionTypeList.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::ActionTypeList* dq5::level::ActionTypeList::getRecord(int index)
{
    return (ActionTypeList*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::ActionTypeList::filename_ = "data/leveldata/dq5ds_action_type.dat";
ExcelBinaryData dq5::level::ActionTypeList::binary_;
void* dq5::level::ActionTypeList::addr_;
dss::File::LoadSwitch dq5::level::ActionTypeList::loadSwitch_;
char dq5::level::ActionTypeList::dataRegion[408];

THUMB void dq5::level::ActionTypeList::setup()
{
    if (levelData.getLoadType(8) == 0) {
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
