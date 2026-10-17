#include "main/leveldata/EffectMessage.hpp"
#include "main/leveldata/LevelData.hpp"

inline dq5::level::EffectMessage* dq5::level::EffectMessage::getRecord(int index)
{
    return (EffectMessage*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

const char* dq5::level::EffectMessage::filename_ = "data/leveldata/dq5ds_effect_message.dat";
ExcelBinaryData dq5::level::EffectMessage::binary_;
void* dq5::level::EffectMessage::addr_;
dss::File::LoadSwitch dq5::level::EffectMessage::loadSwitch_;
char dq5::level::EffectMessage::dataRegion[1824];

THUMB void dq5::level::EffectMessage::setup()
{
    if (levelData.getLoadType(24) == 0) {
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
