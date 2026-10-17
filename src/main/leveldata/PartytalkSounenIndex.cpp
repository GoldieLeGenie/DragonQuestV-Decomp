#include "main/leveldata/PartytalkSounenIndex.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::PartytalkSounenIndex* dq5::level::PartytalkSounenIndex::getRecord(int index)
{
    return (PartytalkSounenIndex*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::PartytalkSounenIndex::filename_ = "data/leveldata/dq5ds_partytalk_sounen_index.dat";
ExcelBinaryData dq5::level::PartytalkSounenIndex::binary_;
dss::File::LoadSwitch dq5::level::PartytalkSounenIndex::loadSwitch_;
void* dq5::level::PartytalkSounenIndex::addr_;

THUMB void dq5::level::PartytalkSounenIndex::setup()
{
    if (levelData.getLoadType(207) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::PartytalkSounenIndex::cleanup()
{
    binary_.cleanup(addr_);
}
