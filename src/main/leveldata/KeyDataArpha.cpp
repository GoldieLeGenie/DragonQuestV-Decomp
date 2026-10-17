#include "main/leveldata/KeyDataArpha.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::KeyDataArpha* dq5::level::KeyDataArpha::getRecord(int index)
{
    return (KeyDataArpha*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::KeyDataArpha::filename_ = "data/leveldata/dq5ds_keydata_arpha.dat";
ExcelBinaryData dq5::level::KeyDataArpha::binary_;
dss::File::LoadSwitch dq5::level::KeyDataArpha::loadSwitch_;
void* dq5::level::KeyDataArpha::addr_;

THUMB void dq5::level::KeyDataArpha::setup()
{
    if (levelData.getLoadType(191) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::KeyDataArpha::cleanup()
{
    binary_.cleanup(addr_);
}
