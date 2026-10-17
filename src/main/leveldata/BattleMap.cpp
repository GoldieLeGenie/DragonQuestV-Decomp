#include "main/leveldata/BattleMap.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::BattleMap* dq5::level::BattleMap::getRecord(int index)
{
    return (BattleMap*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::BattleMap::filename_ = "data/leveldata/dq5ds_battle_map.dat";
ExcelBinaryData dq5::level::BattleMap::binary_;
void* dq5::level::BattleMap::addr_;
dss::File::LoadSwitch dq5::level::BattleMap::loadSwitch_;
char dq5::level::BattleMap::dataRegion[1800];

THUMB void dq5::level::BattleMap::setup()
{
    if (levelData.getLoadType(113) == 0) {
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
