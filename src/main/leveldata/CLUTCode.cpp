#include "main/leveldata/CLUTCode.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::CLUTCode* dq5::level::CLUTCode::getRecord(int index)
{
    return (CLUTCode*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::CLUTCode::filename_ = "data/leveldata/dq5ds_clut_code.dat";
ExcelBinaryData dq5::level::CLUTCode::binary_;
void* dq5::level::CLUTCode::addr_;
dss::File::LoadSwitch dq5::level::CLUTCode::loadSwitch_;
char dq5::level::CLUTCode::dataRegion[192];

THUMB void dq5::level::CLUTCode::setup()
{
    if (levelData.getLoadType(6) == 0) {
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
