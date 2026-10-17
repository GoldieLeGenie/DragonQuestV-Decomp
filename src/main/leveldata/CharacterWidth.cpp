#include "main/leveldata/CharacterWidth.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::CharacterWidth::filename_ = "data/leveldata/dq5ds_character_width.dat";
ExcelBinaryData dq5::level::CharacterWidth::binary_;
dss::File::LoadSwitch dq5::level::CharacterWidth::loadSwitch_;
void* dq5::level::CharacterWidth::addr_;

THUMB void dq5::level::CharacterWidth::setup()
{
    if (levelData.getLoadType(212) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
}

THUMB void dq5::level::CharacterWidth::cleanup()
{
    binary_.cleanup(addr_);
}
