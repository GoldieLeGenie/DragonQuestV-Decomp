#include "main/leveldata/SugorokuData.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::SugorokuData* dq5::level::SugorokuData::getRecord(int index)
{
    return (SugorokuData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::SugorokuData::filename_ = "data/leveldata/dq5ds_sugoroku_data.dat";
ExcelBinaryData dq5::level::SugorokuData::binary_;
void* dq5::level::SugorokuData::addr_;
dss::File::LoadSwitch dq5::level::SugorokuData::loadSwitch_;
char dq5::level::SugorokuData::dataRegion[2688];

THUMB void dq5::level::SugorokuData::setup()
{
    if (levelData.getLoadType(150) == 0) {
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

THUMB void dq5::level::SugorokuData::cleanup()
{
}
