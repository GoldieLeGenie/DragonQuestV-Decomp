#include "main/leveldata/SugorokuSpecialMsg.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::SugorokuSpecialMsg* dq5::level::SugorokuSpecialMsg::getRecord(int index)
{
    return (SugorokuSpecialMsg*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::SugorokuSpecialMsg::filename_ = "data/leveldata/dq5ds_sugoroku_special.dat";
ExcelBinaryData dq5::level::SugorokuSpecialMsg::binary_;
void* dq5::level::SugorokuSpecialMsg::addr_;
dss::File::LoadSwitch dq5::level::SugorokuSpecialMsg::loadSwitch_;
char dq5::level::SugorokuSpecialMsg::dataRegion[256];

THUMB void dq5::level::SugorokuSpecialMsg::setup()
{
    if (levelData.getLoadType(153) == 0) {
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

THUMB void dq5::level::SugorokuSpecialMsg::cleanup()
{
}
