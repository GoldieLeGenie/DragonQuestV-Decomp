#include "main/leveldata/PartytalkSounen.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::PartytalkSounen::filename_ = "data/leveldata/dq5ds_partytalk_sounen.dat";
ExcelBinaryData dq5::level::PartytalkSounen::binary_;
dss::File::LoadSwitch dq5::level::PartytalkSounen::loadSwitch_;
void* dq5::level::PartytalkSounen::addr_;

THUMB void dq5::level::PartytalkSounen::setup()
{
    if (levelData.getLoadType(202) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
}

THUMB void dq5::level::PartytalkSounen::cleanup()
{
    binary_.cleanup(addr_);
}
