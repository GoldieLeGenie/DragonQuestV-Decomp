#include "main/leveldata/ActionParam.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::ActionParam* dq5::level::ActionParam::getRecord(int index) { return (ActionParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_); }

const char* dq5::level::ActionParam::filename_ = "data/leveldata/dq5ds_action.dat";
ExcelBinaryData dq5::level::ActionParam::binary_;
void* dq5::level::ActionParam::addr_;
dss::File::LoadSwitch dq5::level::ActionParam::loadSwitch_;
char dq5::level::ActionParam::dataRegion[32000];

THUMB void dq5::level::ActionParam::setup()
{
    if (levelData.getLoadType(2) == 0) {
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
