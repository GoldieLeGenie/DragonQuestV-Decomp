#include "main/leveldata/MonsterData.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::MonsterData* dq5::level::MonsterData::getRecord(int index)
{
    return (MonsterData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::MonsterData::filename_ = "data/leveldata/dq5ds_monster.dat";
ExcelBinaryData dq5::level::MonsterData::binary_;
void* dq5::level::MonsterData::addr_;
dss::File::LoadSwitch dq5::level::MonsterData::loadSwitch_;
char dq5::level::MonsterData::dataRegion[12792];

THUMB void dq5::level::MonsterData::setup()
{
    if (levelData.getLoadType(21) == 0) {
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
