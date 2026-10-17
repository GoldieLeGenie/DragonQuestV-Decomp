#include "main/leveldata/SugorokuStage.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::SugorokuStage* dq5::level::SugorokuStage::getRecord(int index)
{
    return (SugorokuStage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::SugorokuStage::filename_ = "data/leveldata/dq5ds_sugoroku_stage.dat";
ExcelBinaryData dq5::level::SugorokuStage::binary_;
dss::File::LoadSwitch dq5::level::SugorokuStage::loadSwitch_;
void* dq5::level::SugorokuStage::addr_;

THUMB void dq5::level::SugorokuStage::setup()
{
    if (levelData.getLoadType(154) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::SugorokuStage::cleanup()
{
    binary_.cleanup(addr_);
}
