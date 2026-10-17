#include "main/leveldata/KeyTableArpha.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::KeyTableArpha* dq5::level::KeyTableArpha::getRecord(int index)
{
    return (KeyTableArpha*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::KeyTableArpha::filename_ = "data/leveldata/dq5ds_keytable_arpha.dat";
ExcelBinaryData dq5::level::KeyTableArpha::binary_;
dss::File::LoadSwitch dq5::level::KeyTableArpha::loadSwitch_;
void* dq5::level::KeyTableArpha::addr_;

THUMB void dq5::level::KeyTableArpha::setup()
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

THUMB void dq5::level::KeyTableArpha::cleanup()
{
    binary_.cleanup(addr_);
}
