#include "main/leveldata/CharacterData.hpp"
#include "main/leveldata/LevelData.hpp"
#include "main/dss/DssUtils.hpp"

const char* dq5::level::CharacterData::filename_ = "data/leveldata/dq5ds_player_level%d.dat";
ExcelBinaryData dq5::level::CharacterData::binary_;
dss::File::LoadSwitch dq5::level::CharacterData::loadSwitch_;
char dq5::level::CharacterData::dataRegion[36];

ARM dq5::level::PlayerData1* dq5::level::CharacterData::getRecord(int index, int level)
{
    char path[128];
    if (levelData.getLoadType(28) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    dss::sprintf(path, filename_, index);
    binary_.setupHeader(path, loadSwitch_);
    binary_.setup(sizeof(dataRegion));
    return (PlayerData1*)binary_.getRecord(level, dataRegion, path, loadSwitch_);
}
