#include "main/leveldata/KeyTableJH.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::KeyTableJH* dq5::level::KeyTableJH::getRecord(int index)
{
    return (KeyTableJH*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::KeyTableJH::filename_ = "data/leveldata/dq5ds_keytable_jh.dat";
ExcelBinaryData dq5::level::KeyTableJH::binary_;
dss::File::LoadSwitch dq5::level::KeyTableJH::loadSwitch_;
void* dq5::level::KeyTableJH::addr_;

THUMB void dq5::level::KeyTableJH::setup()
{
    if (levelData.getLoadType(192) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::KeyTableJH::cleanup()
{
    binary_.cleanup(addr_);
}
