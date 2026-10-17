#include "main/leveldata/KeyDataDire.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::KeyDataDire* dq5::level::KeyDataDire::getRecord(int index)
{
    return (KeyDataDire*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::KeyDataDire::filename_ = "data/leveldata/dq5ds_keydata_dire.dat";
ExcelBinaryData dq5::level::KeyDataDire::binary_;
dss::File::LoadSwitch dq5::level::KeyDataDire::loadSwitch_;
void* dq5::level::KeyDataDire::addr_;

THUMB void dq5::level::KeyDataDire::setup()
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

THUMB void dq5::level::KeyDataDire::cleanup()
{
    binary_.cleanup(addr_);
}
