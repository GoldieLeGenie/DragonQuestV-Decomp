#pragma ipa file
#include "ov001/town/TownSystem.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownSugorokuManager.hpp"
#include "main/cmn/GameManager.hpp"
#include "main/cmn/CommonSoundManager.hpp"
#include "main/cmn/TalkSoundManager.hpp"
#include "main/cmn/PartyTalk.hpp"
#include "main/cmn/CommonEffectLocation.hpp"
#include "main/cmn/CommonChapterTitle.hpp"
#include "main/object/BillboardCharacter.hpp"
#include "main/object/DSSAObject.hpp"
#include "main/global/Global.hpp"
#include "main/global/StageLink.hpp"
#include "main/leveldata/LevelData.hpp"
#include "main/leveldata/FloorParam.hpp"
#include "main/status/StageInfo.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StoryStatus.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/GameFlag.hpp"
#include "main/status/Status.hpp"
#include "main/sound/SoundManager.hpp"

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

inline void cmn::GameManager::setPlayerManager(PlayerManager* playerManager)
{
    playerManager_ = playerManager;
}

inline void BillboardCharacter::setAllAnimLock(bool flag)
{
    allAnimLock = flag;
}

inline void BillboardCharacter::setCamera(dss::UnkDualCameraBase* camera)
{
    camera_ = camera;
}

inline int status::StageInfo::getRuraFlag()
{
    return ruraFlag_;
}

inline bool status::StageInfo::isLoadFlag()
{
    return load_;
}

inline void status::StageInfo::setStageSepia(bool sep)
{
    DSSAObject::setHueChange(sep);
    sepiaFlag_ = sep;
}

inline void status::StageInfo::setEncountFlag(bool flag)
{
    encount_ = flag;
}

inline void status::StageInfo::setRiremitMapId(int id)
{
    riremitMap_ = id;
}

inline void status::StageInfo::setSymbolID(int sy)
{
    symbolID_ = sy;
}

inline void status::StageInfo::setReliveCheckFlag(bool flag)
{
    reliveCheckFlag_ = flag;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int Global::getPrevMapNameId()
{
    return prevMapNameId;
}

inline int Global::getNowAreaNo()
{
    return areaNo_;
}

inline void Global::setPartChangeFlag(bool flag)
{
    partChangeFlag_ = flag;
}

inline twn::UnkTownSystemRender::~UnkTownSystemRender()
{
}

THUMB void twn::UnkTownSystemRender::initialize()
{
    setup();
}

THUMB void twn::UnkTownSystemRender::terminate()
{
    cleanup();
}

THUMB void twn::UnkTownSystemRender::execute()
{
}

THUMB void twn::UnkTownSystemRender::draw()
{
    unkfunc_02048908();
}

THUMB twn::TownSystem::TownSystem()
{
}

THUMB twn::TownSystem& twn::TownSystem::getSingleton()
{
    static TownSystem townSystem;
    return townSystem;
}

THUMB void twn::TownSystem::initialize()
{
    cmn::GameManager::getSingleton().initialize();
    cmn::GameManager::getSingleton().setPlayerManager(&TownPlayerManager::getSingleton());
    BillboardCharacter::setAllAnimLock(false);
    g_Global.updateArea();
    dq5::level::levelData.setupTown();
    BillboardCharacter::unkfunc_0205647c();
    cmn::g_cmnSoundManager.initialize();
    args::GameSystemManager::getSingleton().clear();
    args::GameSystemManager::getSingleton().enRegister(townSystemRender_, 2, 7, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemScreenEffect_, 3, 1, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemCommand_, 1, 3, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemMenu_, 6, 6, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemMessage_, 4, 4, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemMaterielMenu_, 5, 5, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemDrawTownMap_, 21, 21, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemDrawShopList_, 7, 16, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemSugoroku_, 12, 11, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemCamera_, 17, 2, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemFurniture_, 10, 14, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemRiseup_, 11, 12, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemPlayer_, 14, 8, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemStage_, 8, 10, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemStageEffect_, 9, 13, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemCharacter_, 13, 9, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemScript_, 16, 17, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemEncount_, 15, 18, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemParticle_, 18, 15, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemGlobalMap_, 19, 19, true);
    args::GameSystemManager::getSingleton().enRegister(townSystemMuseum_, 20, 20, true);
    args::GameSystemManager::getSingleton().initialize();
    cmn::g_talkSound.setup();
    SoundManager::townPlay(getFloorBgmIndex());
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
    cmn::CommonEffectLocation::getSingleton().initialize();
    dq5::level::levelData.cleanupTown();
    dss::Fix32 scl;
    scl.value = 0x122b;
    DSSAObject::setDefaultScale2(scl);
    scl.value = 0x87;
    DSSAObject::setDefaultScale(scl);
    DSSAObject::setPriority(8);
    BillboardCharacter::setCamera(&TownCamera::getSingleton()->camera_);
    if (status::g_StageAttribute.isCoercionSort() == true && !status::g_StageInfo.isLoadFlag()) {
        if (status::g_Story.getChapter() == 1 && g_Global.getMapNameId() == 0x82) {
            status::PartyStatusUtility::forceReorderTown(false);
        }
        if (status::g_Story.getChapter() == 2 || status::g_Story.getChapter() == 3) {
            status::PartyStatusUtility::forceReorderTown(false);
        }
        status::g_StageAttribute.setCoercionSort(false);
    }
    if (g_Global.getNowAreaNo() == 0x33) {
        TownStageEffectManager::getSingleton()->resolveOverlapPosition();
    }
}

THUMB void twn::TownSystem::terminate()
{
    status::g_StageInfo.setStageSepia(false);
    dss::Fix32 scl;
    scl.value = 0x1000;
    DSSAObject::setDefaultScale2(scl);
    cmn::CommonEffectLocation::getSingleton().terminate();
    cmn::CommonChapterTitle::getSingleton().cleanup();
    if (dss::strcmp(g_Global.getMapName(), "field") == 0) {
        status::g_StageInfo.initDoorOpenFlag();
    }
    if (!g_Global.isNextPart(5)) {
        if (!g_Global.isNextPart(7) && !g_Global.isNextPart(8) && !g_Global.isNextPart(9) && !g_Global.isNextPart(10)) {
            g_GlobalFlag.clear();
        }
        if (g_Global.isAreaChange()) {
            if (!g_Global.isNextPart(7) && !g_Global.isNextPart(8) && !g_Global.isNextPart(9) && !g_Global.isNextPart(10)) {
                g_LocalFlag.clear();
            }
            status::g_StageInfo.initDoorOpenFlag();
            status::g_StageInfo.setRiremitMapId(g_Global.getPrevMapNameId());
            status::g_StageInfo.setSymbolID(util::StageLink::getTownExitIndex());
            status::g_StageAttribute.setShopListDisable(false);
            TownPlayerManager::getSingleton().player_.townActionTruck_.system_.wagonCrear();
            TownCamera::getSingleton()->resetAngle();
        }
        status::g_StageInfo.initFurnBreakFlag();
        status::StageAttribute::setToramana(false);
        status::PartyStatusUtility::clearWalkDamage();
    } else {
        status::g_StageInfo.setEncountFlag(true);
    }
    status::g_StageInfo.setReliveCheckFlag(true);
    args::GameSystemManager::getSingleton().terminate();
    BillboardCharacter::unkfunc_0205678c();
    status::Status::setFlagShopExec();
    dq5::level::levelData.cleanupTown();
    g_Global.setPartChangeFlag(false);
    cmn::GameManager::getSingleton().terminate();
}

THUMB void twn::TownSystem::execute()
{
    args::GameSystemManager::getSingleton().execute();
    cmn::GameManager::getSingleton().execute();
}

THUMB void twn::TownSystem::draw()
{
    args::GameSystemManager::getSingleton().draw();
}

THUMB void twn::TownSystem::debug()
{
}

THUMB int twn::TownSystem::getFloorBgmIndex()
{
    dq5::level::FloorParam* floorparam = status::StageAttribute::getFloorParam(g_Global.getMapNameId());
    if (TownSugorokuManager::getSingleton().isSugorokuMode()) {
        return 0x1c;
    }
    if (status::g_StageInfo.getTimeZone() == 1) {
        return floorparam->bgmDaytime;
    }
    if (status::g_StageInfo.getTimeZone() == 2) {
        return floorparam->bgmDaytime;
    }
    if (status::g_StageInfo.getTimeZone() == 3) {
        return floorparam->bgmDaytime;
    }
    if (status::g_StageInfo.getTimeZone() == 4) {
        return floorparam->bgmNight;
    }
    return 0;
}
