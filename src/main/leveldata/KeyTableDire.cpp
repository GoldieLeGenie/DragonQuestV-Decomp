#include "main/leveldata/KeyTableDire.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::KeyTableDire* dq5::level::KeyTableDire::getRecord(int index)
{
    return (KeyTableDire*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::KeyTableDire::filename_ = "data/leveldata/dq5ds_keytable_dire.dat";
ExcelBinaryData dq5::level::KeyTableDire::binary_;
dss::File::LoadSwitch dq5::level::KeyTableDire::loadSwitch_;
void* dq5::level::KeyTableDire::addr_;

THUMB void dq5::level::KeyTableDire::setup()
{
    if (levelData.getLoadType(193) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::KeyTableDire::cleanup()
{
    binary_.cleanup(addr_);
}
