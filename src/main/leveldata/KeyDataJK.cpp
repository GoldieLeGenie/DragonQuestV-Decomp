#include "main/leveldata/KeyDataJK.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::KeyDataJK* dq5::level::KeyDataJK::getRecord(int index)
{
    return (KeyDataJK*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::KeyDataJK::filename_ = "data/leveldata/dq5ds_keydata_jk.dat";
ExcelBinaryData dq5::level::KeyDataJK::binary_;
dss::File::LoadSwitch dq5::level::KeyDataJK::loadSwitch_;
void* dq5::level::KeyDataJK::addr_;

THUMB void dq5::level::KeyDataJK::setup()
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

THUMB void dq5::level::KeyDataJK::cleanup()
{
    binary_.cleanup(addr_);
}
