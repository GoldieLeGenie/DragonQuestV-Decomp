#include "main/leveldata/SugorokuDrop.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::SugorokuDrop* dq5::level::SugorokuDrop::getRecord(int index)
{
    return (SugorokuDrop*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::SugorokuDrop::filename_ = "data/leveldata/dq5ds_sugoroku_drop.dat";
ExcelBinaryData dq5::level::SugorokuDrop::binary_;
void* dq5::level::SugorokuDrop::addr_;
dss::File::LoadSwitch dq5::level::SugorokuDrop::loadSwitch_;
char dq5::level::SugorokuDrop::dataRegion[176];

THUMB void dq5::level::SugorokuDrop::setup()
{
    if (levelData.getLoadType(158) == 0) {
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

THUMB void dq5::level::SugorokuDrop::cleanup()
{
}
