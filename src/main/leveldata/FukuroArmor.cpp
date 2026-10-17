#include "main/leveldata/FukuroArmor.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FukuroArmor* dq5::level::FukuroArmor::getRecord(int index)
{
    return (FukuroArmor*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FukuroArmor::filename_ = "data/leveldata/dq5ds_fukuro_armor.dat";
ExcelBinaryData dq5::level::FukuroArmor::binary_;
dss::File::LoadSwitch dq5::level::FukuroArmor::loadSwitch_;
void* dq5::level::FukuroArmor::addr_;

THUMB void dq5::level::FukuroArmor::setup()
{
    if (levelData.getLoadType(141) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::FukuroArmor::cleanup()
{
    binary_.cleanup(addr_);
}
