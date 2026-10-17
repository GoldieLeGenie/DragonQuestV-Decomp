#include "main/leveldata/PartytalkEndingIndex.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::PartytalkEndingIndex* dq5::level::PartytalkEndingIndex::getRecord(int index)
{
    return (PartytalkEndingIndex*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::PartytalkEndingIndex::filename_ = "data/leveldata/dq5ds_partytalk_ending_index.dat";
ExcelBinaryData dq5::level::PartytalkEndingIndex::binary_;
dss::File::LoadSwitch dq5::level::PartytalkEndingIndex::loadSwitch_;
void* dq5::level::PartytalkEndingIndex::addr_;

THUMB void dq5::level::PartytalkEndingIndex::setup()
{
    if (levelData.getLoadType(208) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::PartytalkEndingIndex::cleanup()
{
    binary_.cleanup(addr_);
}
