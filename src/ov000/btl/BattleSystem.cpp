#include "ov000/btl/BattleSystem.hpp"
#include "ov000/btl/BattleCamera.hpp"
#include "ov000/btl/BattleEffectManager.hpp"
#include "ov000/btl/BattleMonsterMask.hpp"
#include "ov000/btl/BattleRoot.hpp"
#include "ov000/btl/BattleStage.hpp"
#include "ov018/btl/BattleMonsterDraw2.hpp"
#include "main/cmn/CommonEffectLocation.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/LevelData.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/script/ScriptSystem.hpp"
#include "main/status/HaveAction.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StoryStatus.hpp"

inline dq5::CHAPTER_NO status::StoryStatus::getChapter() { return chapter_; }
inline void DSSAObjectWithCamera::setCamera(dss::Camera* camera) { camera_ = camera; }

THUMB btl::BattleSystem::BattleSystem()
{
}

THUMB btl::BattleSystem::~BattleSystem()
{
}

THUMB btl::BattleSystem* btl::BattleSystem::getSingleton()
{
    static BattleSystem m_singleton;
    return &m_singleton;
}

THUMB void btl::BattleSystem::initialize()
{
    dss::Fix32 scale;
    scale.value = 0x316;
    DSSAObject::setDefaultScale(scale);
    DSSAObject::setPriority(1);
    dq5::level::levelData.setupBattle();
    render_.setup();
    BattleStage::getSingleton()->initialize();
    BattleCamera::getSingleton()->initialize();
    BattleEffectManager::getSingleton()->initialize();
    BattleMonsterMask::getSingleton()->initialize();
    DSSAObjectWithCamera::setCamera(BattleCamera::getSingleton()->getCamera());
    BattleRoot::getSingleton()->initialize();
    status::HaveAction::setBattleMode();
    cmn::CommonEffectLocation::getSingleton().initialize();
    cmn::g_cmnSoundManager.initialize();
    ScriptSystem::getSingleton()->initialize(status::g_Story.getChapter(), "battle");
    status::PartyStatusUtility::resetForceReorderMember();
}

THUMB void btl::BattleSystem::terminate()
{
    ScriptSystem::getSingleton()->terminate();
    cmn::CommonEffectLocation::getSingleton().terminate();
    BattleRoot::getSingleton()->terminate();
    status::HaveAction::setTownMode();
    BattleMonsterDraw2::getSingleton().cleanup();
    BattleEffectManager::getSingleton()->terminate();
    BattleCamera::getSingleton()->terminate();
    BattleStage::getSingleton()->terminate();
    BattleMonsterMask::getSingleton()->terminate();
    render_.cleanup();
    dq5::level::levelData.cleanupBattle();
    g_Global.partChangeFlag_ = 0;
}

THUMB void btl::BattleSystem::execute()
{
    cmn::CommonEffectLocation::getSingleton().execute();
    BattleRoot::getSingleton()->execute();
    BattleStage::getSingleton()->execute();
    BattleEffectManager::getSingleton()->execute();
    ScriptSystem::getSingleton()->execute();
}

THUMB void btl::BattleSystem::draw()
{
    BattleCamera::getSingleton()->executeForMap();
    BattleCamera::getSingleton()->draw();
    DSSAObjectWithCamera::setCamera(BattleCamera::getSingleton()->getCamera());
    BattleEffectManager::getSingleton()->extraDraw();
    BattleMonsterMask::getSingleton()->draw();
    render_.unkfunc_02048908();
    BattleRoot::getSingleton()->draw();
    BattleMonsterDraw2::getSingleton().draw();
    BattleEffectManager::getSingleton()->draw();
    BattleMonsterMask::getSingleton()->setup();
}
