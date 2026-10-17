#include "main/leveldata/PartytalkYounenIndex.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::PartytalkYounenIndex* dq5::level::PartytalkYounenIndex::getRecord(int index)
{
    return (PartytalkYounenIndex*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::PartytalkYounenIndex::filename_ = "data/leveldata/dq5ds_partytalk_younen_index.dat";
ExcelBinaryData dq5::level::PartytalkYounenIndex::binary_;
dss::File::LoadSwitch dq5::level::PartytalkYounenIndex::loadSwitch_;
void* dq5::level::PartytalkYounenIndex::addr_;

THUMB void dq5::level::PartytalkYounenIndex::setup()
{
    if (levelData.getLoadType(205) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::PartytalkYounenIndex::cleanup()
{
    binary_.cleanup(addr_);
}
