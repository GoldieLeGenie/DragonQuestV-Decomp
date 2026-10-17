#include "main/leveldata/FukuroWeapon.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::FukuroWeapon* dq5::level::FukuroWeapon::getRecord(int index)
{
    return (FukuroWeapon*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::FukuroWeapon::filename_ = "data/leveldata/dq5ds_fukuro_weapon.dat";
ExcelBinaryData dq5::level::FukuroWeapon::binary_;
dss::File::LoadSwitch dq5::level::FukuroWeapon::loadSwitch_;
void* dq5::level::FukuroWeapon::addr_;

THUMB void dq5::level::FukuroWeapon::setup()
{
    if (levelData.getLoadType(142) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::FukuroWeapon::cleanup()
{
    binary_.cleanup(addr_);
}
