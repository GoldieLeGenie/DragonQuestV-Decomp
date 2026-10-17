#include "main/leveldata/KeyDataJH.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::KeyDataJH* dq5::level::KeyDataJH::getRecord(int index)
{
    return (KeyDataJH*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::KeyDataJH::filename_ = "data/leveldata/dq5ds_keydata_jh.dat";
ExcelBinaryData dq5::level::KeyDataJH::binary_;
dss::File::LoadSwitch dq5::level::KeyDataJH::loadSwitch_;
void* dq5::level::KeyDataJH::addr_;

THUMB void dq5::level::KeyDataJH::setup()
{
    if (levelData.getLoadType(190) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::KeyDataJH::cleanup()
{
    binary_.cleanup(addr_);
}
