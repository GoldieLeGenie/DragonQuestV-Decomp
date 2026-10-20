#include "main/cmn/CommonEffectLocation.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "main/leveldata/EffectColorParam.hpp"
#include "ov000/btl/BattleStage.hpp"
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov004/ceremony/CeremonyStage.hpp"

inline dq5::level::EffectColorParam* dq5::level::EffectColorParam::getRecord(int index)
{
    return (EffectColorParam*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned int dq5::level::EffectColorParam::getArraySize()
{
    return binary_.record_;
}

inline fx32 dq5::level::EffectColorParam::getRPoint()
{
    return rPoint;
}

inline fx32 dq5::level::EffectColorParam::getGPoint()
{
    return gPoint;
}

inline fx32 dq5::level::EffectColorParam::getBPoint()
{
    return bPoint;
}

inline unsigned short dq5::level::EffectColorParam::getFrame()
{
    return frame;
}

inline unsigned char dq5::level::EffectColorParam::getIndex()
{
    return index;
}

THUMB cmn::CommonEffectLocation::CommonEffectLocation()
{
}

THUMB cmn::CommonEffectLocation::~CommonEffectLocation()
{
}

THUMB cmn::CommonEffectLocation& cmn::CommonEffectLocation::getSingleton()
{
    static CommonEffectLocation m_singleton;
    return m_singleton;
}

THUMB void cmn::CommonEffectLocation::initialize()
{
    enable_ = 0;
}

THUMB void cmn::CommonEffectLocation::terminate()
{
}

THUMB void cmn::CommonEffectLocation::execute()
{
    if (enable_ != 0 && !calcPaletteRate()) {
        index_++;
        if (!setPaletteRate(index_)) {
            enable_ = 0;
        }
    }
}

THUMB void cmn::CommonEffectLocation::start(int index, int extend)
{
    for (unsigned int i = 0; i < dq5::level::EffectColorParam::getArraySize(); i++) {
        if (index == dq5::level::EffectColorParam::getRecord(i)->getIndex()) {
            index_ = i;
        }
    }
    enable_ = 1;
    extend_ = extend;
    setPaletteRate(index_);
}

THUMB bool cmn::CommonEffectLocation::setPaletteRate(int index)
{
    if (dq5::level::EffectColorParam::getRecord(index + 1)->getFrame() == 0) {
        return false;
    }
    prev_.vx.value = dq5::level::EffectColorParam::getRecord(index)->getRPoint();
    prev_.vy.value = dq5::level::EffectColorParam::getRecord(index)->getGPoint();
    prev_.vz.value = dq5::level::EffectColorParam::getRecord(index)->getBPoint();
    next_.vx.value = dq5::level::EffectColorParam::getRecord(index + 1)->getRPoint();
    next_.vy.value = dq5::level::EffectColorParam::getRecord(index + 1)->getGPoint();
    next_.vz.value = dq5::level::EffectColorParam::getRecord(index + 1)->getBPoint();
    frame_ = dq5::level::EffectColorParam::getRecord(index + 1)->getFrame();
    counter_ = 0;
    if (dq5::level::EffectColorParam::getRecord(index + 3)->getFrame() == 0) {
        frame_ = frame_ + extend_;
    }
    return true;
}

THUMB bool cmn::CommonEffectLocation::calcPaletteRate()
{
    dss::Fix32Vector3 rgb;
    dss::Fix32 one;
    dss::Fix32 rate;

    if (counter_ >= frame_) {
        return false;
    }
    if (prev_ == next_) {
        counter_++;
        return true;
    }
    one.value = 0x1000;
    rate.value = (counter_ << 12) / frame_;
    rgb = prev_ * (one - rate) + next_ * rate;
    if (data_02101c88.isCurrentPart(4)) {
        twn::TownStageEffectManager::getSingleton()->setRGBRate(rgb, 0);
    }
    if (data_02101c88.isCurrentPart(5)) {
        btl::BattleStage::getSingleton()->stage_.m_fld.SetRGBRate((VecFx32*)&rgb, 0);
    }
    if (data_02101c88.isCurrentPart(11)) {
        ceremony::CeremonyStage::getSingleton()->stage_.m_fld.SetRGBRate((VecFx32*)&rgb, 0);
    }
    counter_++;
    return true;
}
