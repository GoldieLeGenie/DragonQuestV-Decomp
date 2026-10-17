#include "main/leveldata/CharacterInitData.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::CharacterInitData* dq5::level::CharacterInitData::getRecord(int index)
{
    return (CharacterInitData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::CharacterInitData::filename_ = "data/leveldata/dq5ds_character_init.dat";
ExcelBinaryData dq5::level::CharacterInitData::binary_;
void* dq5::level::CharacterInitData::addr_;
dss::File::LoadSwitch dq5::level::CharacterInitData::loadSwitch_;
char dq5::level::CharacterInitData::dataRegion[8008];

THUMB void dq5::level::CharacterInitData::setup()
{
    if (levelData.getLoadType(5) == 0) {
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
