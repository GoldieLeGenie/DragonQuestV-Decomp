#include "main/leveldata/SugorokuChangeMsg.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::SugorokuChangeMsg* dq5::level::SugorokuChangeMsg::getRecord(int index)
{
    return (SugorokuChangeMsg*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::SugorokuChangeMsg::filename_ = "data/leveldata/dq5ds_sugoroku_change.dat";
ExcelBinaryData dq5::level::SugorokuChangeMsg::binary_;
void* dq5::level::SugorokuChangeMsg::addr_;
dss::File::LoadSwitch dq5::level::SugorokuChangeMsg::loadSwitch_;
char dq5::level::SugorokuChangeMsg::dataRegion[48];

THUMB void dq5::level::SugorokuChangeMsg::setup()
{
    if (levelData.getLoadType(152) == 0) {
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

THUMB void dq5::level::SugorokuChangeMsg::cleanup()
{
}
