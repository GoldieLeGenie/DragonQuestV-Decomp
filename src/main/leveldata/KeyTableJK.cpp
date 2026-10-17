#include "main/leveldata/KeyTableJK.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::KeyTableJK* dq5::level::KeyTableJK::getRecord(int index)
{
    return (KeyTableJK*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::KeyTableJK::filename_ = "data/leveldata/dq5ds_keytable_jk.dat";
ExcelBinaryData dq5::level::KeyTableJK::binary_;
dss::File::LoadSwitch dq5::level::KeyTableJK::loadSwitch_;
void* dq5::level::KeyTableJK::addr_;

THUMB void dq5::level::KeyTableJK::setup()
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

THUMB void dq5::level::KeyTableJK::cleanup()
{
    binary_.cleanup(addr_);
}
