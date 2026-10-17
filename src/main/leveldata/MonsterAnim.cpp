#include "main/leveldata/MonsterAnim.hpp"
#include "main/leveldata/LevelData.hpp"

const char* dq5::level::MonsterAnim::filename_ = "data/leveldata/dq5ds_monster_anim.dat";
ExcelBinaryData dq5::level::MonsterAnim::binary_;
void* dq5::level::MonsterAnim::addr_;
dss::File::LoadSwitch dq5::level::MonsterAnim::loadSwitch_;
char dq5::level::MonsterAnim::dataRegion[240];

THUMB void dq5::level::MonsterAnim::setup()
{
    if (levelData.getLoadType(20) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = dataRegion;
    binary_.setup(sizeof(dataRegion));
}

THUMB void dq5::level::MonsterAnim::cleanup()
{
}
