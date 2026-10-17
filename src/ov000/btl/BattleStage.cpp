#include "ov000/btl/BattleStage.hpp"
#include "ov000/btl/BattleSystem.hpp"
#include "main/menu/MenuAPI.hpp"
#include "main/status/StageAttribute.hpp"

static char* btlMapPath = "data/btlmap";

THUMB btl::BattleStage::BattleStage()
{
    dss::strcpy(mapName_, "btl_pl_d");
}

THUMB btl::BattleStage::~BattleStage()
{
}

THUMB btl::BattleStage* btl::BattleStage::getSingleton()
{
    static BattleStage m_singleton;
    return &m_singleton;
}

THUMB void btl::BattleStage::initialize()
{
    stage_.initialize(&BattleSystem::getSingleton()->render_);
    stage_.setPath(btlMapPath);
    if (stage_.isExist(status::g_StageAttribute.getBtlMapName())) {
        stage_.load(status::g_StageAttribute.getBtlMapName());
    }
    else {
        stage_.load("btl_pl_d");
    }
    stage_.setup();
    frame_ = 0;
    counter_ = 1;
    MenuAPI::setBattleBackDrop(status::g_StageAttribute.getBattleMapBackColor());
    status::g_StageAttribute.getBattleMapBackColor();
}

THUMB void btl::BattleStage::terminate()
{
    MenuAPI::setBattleBackDrop(0);
    stage_.cleanup();
    stage_.terminate();
}

THUMB void btl::BattleStage::execute()
{
    dss::Fix32 rate;
    rate.value = 0x6000;
    setRGBRate(rate, rate, rate);
    execFade();
}

THUMB void btl::BattleStage::execFade()
{
    dss::Fix32Vector3 rgb;
    dss::Fix32 one;
    dss::Fix32 t;
    if (isFade()) {
        one.value = 0x1000;
        t.value = (counter_ << 12) / frame_;
        rgb = prev_ * (one - t) + next_ * t;
        stage_.m_fld.SetRGBRate((VecFx32*)&rgb, 0);
        counter_++;
    }
}

THUMB bool btl::BattleStage::isFade()
{
    if (counter_ < frame_) {
        return true;
    }
    return false;
}

THUMB void btl::BattleStage::setRGBRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b)
{
    stage_.m_fld.unkfunc_0206175c(r.value, g.value, b.value);
}
