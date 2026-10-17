#pragma ipa file
#include "ov004/ceremony/CeremonySystem.hpp"
#include "main/ceremony/UnkCeremonyEndingFin.hpp"
#include "main/cmn/CommonEffectLocation.hpp"
#include "main/dss/UnkLanguage.hpp"
#include "main/global/Global.hpp"
#include "main/script/ScriptSystem.hpp"
#include "main/status/StoryStatus.hpp"
#include "ov004/ceremony/CeremonyCamera.hpp"
#include "ov004/ceremony/CeremonyEndingFin.hpp"
#include "ov004/ceremony/CeremonyEndingSystem.hpp"
#include "ov004/ceremony/CeremonyOpeningSystem.hpp"
#include "ov004/ceremony/CeremonyStaffSystem.hpp"
#include "ov004/ceremony/CeremonyStage.hpp"

inline dq5::CHAPTER_NO status::StoryStatus::getChapter()
{
    return chapter_;
}

THUMB ceremony::CeremonySystem::CeremonySystem()
{
}

THUMB ceremony::CeremonySystem::~CeremonySystem()
{
}

THUMB ceremony::CeremonySystem* ceremony::CeremonySystem::getSingleton()
{
    static CeremonySystem m_singleton;
    return &m_singleton;
}

THUMB void ceremony::CeremonySystem::initialize()
{
    switch (g_Global.getCeremonyType()) {
    case 0:
        system_ = CeremonyStaffSystem::getSingleton();
        break;
    case 1:
        system_ = CeremonyOpeningSystem::getSingleton();
        break;
    case 2:
        system_ = CeremonyEndingSystem::getSingleton();
        break;
    case 3:
        if (unkfunc_020464e8() == 1) {
            system_ = CeremonyEndingFin::getSingleton();
        } else {
            system_ = UnkCeremonyEndingFin::getSingleton();
        }
        break;
    }
    cmn::CommonEffectLocation::getSingleton().initialize();
    CeremonyStage::getSingleton()->initialize();
    CeremonyCamera::getSingleton()->initialize();
    ScriptSystem::getSingleton()->initialize(status::g_Story.getChapter(), "ev17");
    system_->initialize();
}

THUMB void ceremony::CeremonySystem::terminate()
{
    ScriptSystem::getSingleton()->terminate();
    cmn::CommonEffectLocation::getSingleton().terminate();
    CeremonyCamera::getSingleton()->terminate();
    CeremonyStage::getSingleton()->terminate();
    system_->terminate();
}

THUMB void ceremony::CeremonySystem::execute()
{
    cmn::CommonEffectLocation::getSingleton().execute();
    ScriptSystem::getSingleton()->execute();
    system_->execute();
}

THUMB void ceremony::CeremonySystem::draw()
{
    CeremonyCamera::getSingleton()->draw();
    CeremonyStage::getSingleton()->draw();
    system_->draw();
}
