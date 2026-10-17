#include "main/leveldata/PartytalkMonster.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::PartytalkMonster::filename_ = "data/leveldata/dq5ds_partytalk_monster.dat";
ExcelBinaryData dq5::level::PartytalkMonster::binary_;
dss::File::LoadSwitch dq5::level::PartytalkMonster::loadSwitch_;
void* dq5::level::PartytalkMonster::addr_;

THUMB void dq5::level::PartytalkMonster::setup()
{
    if (levelData.getLoadType(204) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
}

THUMB void dq5::level::PartytalkMonster::cleanup()
{
    binary_.cleanup(addr_);
}
