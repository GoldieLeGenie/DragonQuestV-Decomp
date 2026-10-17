#include "main/leveldata/PartytalkSeinenIndex.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::PartytalkSeinenIndex* dq5::level::PartytalkSeinenIndex::getRecord(int index)
{
    return (PartytalkSeinenIndex*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::PartytalkSeinenIndex::filename_ = "data/leveldata/dq5ds_partytalk_seinen_index.dat";
ExcelBinaryData dq5::level::PartytalkSeinenIndex::binary_;
dss::File::LoadSwitch dq5::level::PartytalkSeinenIndex::loadSwitch_;
void* dq5::level::PartytalkSeinenIndex::addr_;

THUMB void dq5::level::PartytalkSeinenIndex::setup()
{
    if (levelData.getLoadType(206) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::PartytalkSeinenIndex::cleanup()
{
    binary_.cleanup(addr_);
}
