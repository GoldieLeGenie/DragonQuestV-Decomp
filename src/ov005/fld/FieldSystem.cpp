#include "ov005/fld/FieldSystem.hpp"
#include "main/cmn/CommonChapterTitle.hpp"
#include "main/cmn/CommonParticleEmitter.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/NonBattleActionManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/leveldata/LevelData.hpp"
#include "main/object/SpriteCharacter.hpp"
#include "main/sound/Sound.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/Status.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/window/ScreenEffectManager.hpp"
#include "ov005/fld/FieldCamera.hpp"
#include "ov005/fld/FieldEffect.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldStage.hpp"

inline void Global::initFieldType()
{
    fieldType_ = nextFieldType_;
}

inline void Global::setPartChangeFlag(bool flag)
{
    partChangeFlag_ = flag;
}

inline void cmn::GameManager::setPlayerManager(PlayerManager* playerManager)
{
    playerManager_ = playerManager;
}

inline int status::StageInfo::getRuraFlag()
{
    return ruraFlag_;
}

inline void status::StageInfo::setEncountFlag(bool flag)
{
    encount_ = flag;
}

inline void status::StageInfo::setReliveCheckFlag(bool flag)
{
    reliveCheckFlag_ = flag;
}

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline cmn::MENU_ACTION cmn::CommonPartyInfo::getMenuAction()
{
    return menuAction_;
}

inline cmn::PARTY_RIDE_ON_TYPE cmn::CommonPartyInfo::getRideOn()
{
    return rideOnType_;
}

THUMB fld::FieldSystem::FieldSystem()
{
}

THUMB fld::FieldSystem* fld::FieldSystem::getSingleton()
{
    static FieldSystem fieldSystem;
    return &fieldSystem;
}

THUMB void fld::FieldSystem::initialize()
{
    g_Global.initFieldType();
    g_Global.updateArea();
    cmn::GameManager::getSingleton().initialize();
    cmn::GameManager::getSingleton().setPlayerManager(&FieldPlayerManager::getSingleton());
    render_.setup();
    SpriteCharacter::unkfunc_0205870c();
    cmn::g_cmnSoundManager.initialize();
    args::GameSystemManager::getSingleton().clear();
    args::GameSystemManager::getSingleton().enRegister(fieldSystemCommand_, CommandPriority, CommandPriority, true);
    args::GameSystemManager::getSingleton().enRegister(fieldSystemScreenEffect_, ScreenEffectPriority, ScreenEffectPriority, true);
    args::GameSystemManager::getSingleton().enRegister(fieldSystemMessage_, MessagePriority, MessagePriority, true);
    args::GameSystemManager::getSingleton().enRegister(fieldSystemMenu_, MenuPriority, MenuPriority, true);
    args::GameSystemManager::getSingleton().enRegister(fieldSystemMaterielMenu_, MaterielMenuPriority, MaterielMenuPriority, true);
    args::GameSystemManager::getSingleton().enRegister(fieldSystemStage_, StagePriority, StagePriority, true);
    args::GameSystemManager::getSingleton().enRegister(fieldSystemPlayer_, PlayerPriority, PlayerPriority, true);
    args::GameSystemManager::getSingleton().enRegister(fieldSystemScript_, ScriptPriority, ScriptPriority, true);
    args::GameSystemManager::getSingleton().enRegister(fieldSystemEncount_, EncountPriority, EncountPriority, true);
    args::GameSystemManager::getSingleton().enRegister(fieldSystemWorldMap_, MapDrawPriority, MapDrawPriority, true);
    args::GameSystemManager::getSingleton().initialize();
    args::GameSystemManager::getSingleton().setExclusion(EncountPriority, true);
    SoundManager::fieldPlay(getFloorBgmIndex());
    FieldEffectManager::getSingleton().initialize();
    FieldCamera::getSingleton().initialize();
    cmn::CommonParticleEmitter::getSingleton()->initialize();
    if (g_Global.getFieldType() == 1) {
        cmn::CommonParticleEmitter::getSingleton()->setup(0);
    }
    cmn::g_talkSound.setup();
    status::g_StageAttribute.setupField();
    encountStart_ = 0;
    int id;
    if (status::g_StageInfo.getRuraFlag() == 0) {
        id = util::StageLink::getTownExitIndex();
    } else {
        id = -1;
    }
    if (id != -1) {
        cmn::PartyTalk::getSingleton().resetPartyTalk();
        cmn::PartyTalk::getSingleton().setExitNo(id);
    }
    dq5::level::levelData.setupField();
    exitSound_ = 0;
    if (status::g_Story.getChapter() == 2 || status::g_Story.getChapter() == 3) {
        status::PartyStatusUtility::reorderFormerMember();
    }
}

THUMB void fld::FieldSystem::terminate()
{
    cmn::CommonChapterTitle::getSingleton().cleanup();
    cmn::CommonParticleEmitter::getSingleton()->terminate();
    FieldCamera::getSingleton().terminate();
    FieldEffectManager::getSingleton().terminate();
    if (!g_Global.isNextPart(5)) {
        if (!g_Global.isNextPart(7) && !g_Global.isNextPart(8) && !g_Global.isNextPart(9) && !g_Global.isNextPart(10)) {
            g_GlobalFlag.clear();
            g_LocalFlag.clear();
        }
        status::g_StageInfo.setEncountFlag(false);
        if (exitSound_ == 1) {
            Sound::sePlayDirect(0x131);
        }
        if (g_Global.isNextPart(4) == true) {
            int exitIndex = util::StageLink::getTownExitIndex();
            status::g_StageInfo.setRanaMap(exitIndex);
        }
        status::StageAttribute::setToramana(false);
        status::PartyStatusUtility::clearWalkDamage();
    } else {
        status::g_StageInfo.setEncountFlag(true);
        FieldPlayerManager::getSingleton().resetLockByEventEncount();
    }
    cmn::GameManager::getSingleton().terminate();
    args::GameSystemManager::getSingleton().terminate();
    SpriteCharacter::unkfunc_02058738();
    render_.cleanup();
    status::g_StageInfo.setReliveCheckFlag(true);
    status::Status::setFlagShopExec();
    dq5::level::levelData.cleanupField();
    g_Global.setPartChangeFlag(false);
}

THUMB void fld::FieldSystem::execute()
{
    args::GameSystemManager::getSingleton().execute();
    if (g_Global.getRanarutaFlag()) {
        cmn::NonBattleActionManager::getSingleton()->execute();
    }
    dss::Fix32Vector3 pos = FieldPlayerManager::getSingleton().getPosition();
    if (cameraLock_ == 0) {
        setLookAtPos(pos);
    }
    cmn::GameManager::getSingleton().execute();
    FieldEffectManager::getSingleton().execute();
    FieldCamera::getSingleton().execute();
    cmn::CommonParticleEmitter::getSingleton()->execute();
}

THUMB void fld::FieldSystem::draw()
{
    args::GameSystemManager::getSingleton().draw();
    cmn::CommonChapterTitle::getSingleton().draw();
    if (!window::gScreenEffect.isActivate()) {
        render_.unkfunc_02048908();
        FieldEffectManager::getSingleton().draw();
        FieldCamera::getSingleton().draw();
        cmn::CommonParticleEmitter::getSingleton()->draw();
    }
}

THUMB void fld::FieldSystem::setLookAtPos(dss::Fix32Vector3 pos)
{
    pos.vx -= dss::Fix32(0x80L);
    pos.vy -= dss::Fix32(0x60L);
    FieldStage::getSingleton()->setPosition(pos);
}

THUMB int fld::FieldSystem::getFloorBgmIndex()
{
    switch (cmn::g_cmnPartyInfo.getMenuAction()) {
    case cmn::MASTER_DRAGON_DIRECT:
        return 0x11;
    case cmn::TENKU_CASTLE:
        return 0x12;
    }
    if (cmn::g_cmnPartyInfo.getRideOn() == cmn::RIDE_ON_SHIP_IKADA) {
        return 9;
    }
    switch (g_Global.getFieldType()) {
    case 0:
        return 7;
    case 1:
    case 2:
        return 0x1b;
    case 3:
        return 0x18;
    }
    return 7;
}
