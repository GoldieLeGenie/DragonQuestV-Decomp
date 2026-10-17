#include "ov001/leveldata/BoobyTrap.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::BoobyTrap* dq5::level::BoobyTrap::getRecord(int index)
{
    return (BoobyTrap*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::BoobyTrap::filename_ = "data/leveldata/dq5ds_booby_trap.dat";
ExcelBinaryData dq5::level::BoobyTrap::binary_;
void* dq5::level::BoobyTrap::addr_;
dss::File::LoadSwitch dq5::level::BoobyTrap::loadSwitch_;
char dq5::level::BoobyTrap::dataRegion[240];

THUMB void dq5::level::BoobyTrap::setup()
{
    if (levelData.getLoadType(220) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
    getRecord(0);
}

THUMB void dq5::level::BoobyTrap::cleanup()
{
}
