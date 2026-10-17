#include "main/leveldata/EffectColorParam.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::EffectColorParam* dq5::level::EffectColorParam::getRecord(int index)
{
    return (EffectColorParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::EffectColorParam::filename_ = "data/leveldata/dq5ds_effect_color.dat";
ExcelBinaryData dq5::level::EffectColorParam::binary_;
void* dq5::level::EffectColorParam::addr_;
dss::File::LoadSwitch dq5::level::EffectColorParam::loadSwitch_;
char dq5::level::EffectColorParam::dataRegion[3584];

THUMB void dq5::level::EffectColorParam::setup()
{
    if (levelData.getLoadType(114) == 0) {
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
