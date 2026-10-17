#include "main/leveldata/SugorokuChanceCard.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::SugorokuChanceCard* dq5::level::SugorokuChanceCard::getRecord(int index)
{
    return (SugorokuChanceCard*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::SugorokuChanceCard::filename_ = "data/leveldata/dq5ds_sugoroku_chance.dat";
ExcelBinaryData dq5::level::SugorokuChanceCard::binary_;
void* dq5::level::SugorokuChanceCard::addr_;
dss::File::LoadSwitch dq5::level::SugorokuChanceCard::loadSwitch_;
char dq5::level::SugorokuChanceCard::dataRegion[468];

THUMB void dq5::level::SugorokuChanceCard::setup()
{
    if (levelData.getLoadType(151) == 0) {
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

THUMB void dq5::level::SugorokuChanceCard::cleanup()
{
}
