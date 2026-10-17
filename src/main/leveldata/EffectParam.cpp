#include "main/leveldata/EffectParam.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::EffectParam* dq5::level::EffectParam::getRecord(int index)
{
    return (EffectParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::EffectParam::filename_ = "data/leveldata/dq5ds_effect_param.dat";
ExcelBinaryData dq5::level::EffectParam::binary_;
dss::File::LoadSwitch dq5::level::EffectParam::loadSwitch_;
void* dq5::level::EffectParam::addr_;

THUMB void dq5::level::EffectParam::setup()
{
    if (levelData.getLoadType(10) == 0) {
        loadSwitch_ = dss::File::None;
    }
    else {
        loadSwitch_ = dss::File::Switching;
    }
    binary_.setupHeader(filename_, loadSwitch_);
    addr_ = binary_.setup();
    getRecord(0);
}

THUMB void dq5::level::EffectParam::cleanup()
{
    binary_.cleanup(addr_);
}
