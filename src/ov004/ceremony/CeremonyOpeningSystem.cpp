#pragma ipa file
#include "ov004/ceremony/CeremonyOpeningSystem.hpp"
#include "main/ceremony/CeremonySetting.hpp"
#include "main/cmn/CommonEffectLocation.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "nitro/pad.h"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkLanguage.hpp"
#include "main/global/Global.hpp"
#include "main/sound/Sound.hpp"
#include "main/status/GameStatus.hpp"
#include "main/status/StoryStatus.hpp"
#include "ov004/ceremony/CeremonyStage.hpp"

inline UnkLZDataObject::UnkLZDataObject()
{
}

inline DSSAObject2D::DSSAObject2D()
{
}

inline DSSAObject2D::~DSSAObject2D()
{
}

inline int ceremony::CeremonySetting::getNextActMap()
{
    return nextActMap_;
}

inline dss::Fix32Vector3& ceremony::CeremonySetting::getNextActPos()
{
    return nextActPosition_;
}

THUMB ceremony::CeremonyOpeningSystem::CeremonyOpeningSystem()
{
}

THUMB ceremony::CeremonyOpeningSystem::~CeremonyOpeningSystem()
{
}

THUMB ceremony::CeremonyOpeningSystem* ceremony::CeremonyOpeningSystem::getSingleton()
{
    static CeremonyOpeningSystem m_singleton;
    return &m_singleton;
}

THUMB void ceremony::CeremonyOpeningSystem::initialize()
{
    dss::Fix32 scl;
    scl.value = 0x320;
    DSSAObject::setDefaultScale(scl);
    DSSAObject::setPriority(1);
    if (getGameRegion() == 1) {
        char path[128];
        dss::sprintf_s(path, sizeof(path), "data/opening/jp/logo.tex.lz");
        textureData_.setup(path, 0, 1);
        texture_ = (TextureObject*)textureData_.getAddr();
        texture_->loadToVram(1);
        dss::sprintf_s(path, sizeof(path), "data/opening/jp/logo1.dssa");
        logo1Data_.setup(path, 0, 0);
        logo1Dssa_.setup(logo1Data_.getAddr());
        logo1Dssa_.setTexture(texture_);
        logo1Dssa_.pause(true);
        dss::sprintf_s(path, sizeof(path), "data/opening/jp/logo3.dssa");
        logo3Data_.setup(path, 0, 0);
        logo3Dssa_.setup(logo3Data_.getAddr());
        logo3Dssa_.setTexture(texture_);
        logo3Dssa_.pause(true);
        dss::sprintf_s(path, sizeof(path), "data/opening/jp/logo4.dssa");
        logo4Data_.setup(path, 0, 0);
        logo4Dssa_.setup(logo4Data_.getAddr());
        logo4Dssa_.setTexture(texture_);
        logo4Dssa_.pause(true);
    } else {
        char area[3];
        char lang[3];
        char path[128];
        if (getGameRegion() == 2) {
            dss::sprintf_s(area, sizeof(area), "na");
        }
        if (getGameRegion() == 3) {
            dss::sprintf_s(area, sizeof(area), "eu");
        }
        if (status::g_Game.language_ == English) {
            dss::sprintf_s(lang, sizeof(lang), "en");
        }
        if (status::g_Game.language_ == French) {
            dss::sprintf_s(lang, sizeof(lang), "fr");
        }
        if (status::g_Game.language_ == German) {
            dss::sprintf_s(lang, sizeof(lang), "de");
        }
        if (status::g_Game.language_ == Italian) {
            dss::sprintf_s(lang, sizeof(lang), "it");
        }
        if (status::g_Game.language_ == Spanish) {
            dss::sprintf_s(lang, sizeof(lang), "es");
        }
        if (getGameRegion() == 2 && status::g_Game.language_ == German) {
            dss::sprintf_s(lang, sizeof(lang), "en");
        }
        if (getGameRegion() == 2 && status::g_Game.language_ == Italian) {
            dss::sprintf_s(lang, sizeof(lang), "en");
        }
        dss::sprintf_s(path, sizeof(path), "data/opening/%s/%s/logo_%s_%s.tex.lz", area, lang, area, lang);
        textureData_.setup(path, 0, 1);
        texture_ = (TextureObject*)textureData_.getAddr();
        texture_->loadToVram(1);
        dss::sprintf_s(path, sizeof(path), "data/opening/%s/%s/logo_%s_%s1.dssa", area, lang, area, lang);
        logo1Data_.setup(path, 0, 0);
        logo1Dssa_.setup(logo1Data_.getAddr());
        logo1Dssa_.setTexture(texture_);
        logo1Dssa_.pause(true);
        dss::sprintf_s(path, sizeof(path), "data/opening/%s/%s/logo_%s_%s3.dssa", area, lang, area, lang);
        logo3Data_.setup(path, 0, 0);
        logo3Dssa_.setup(logo3Data_.getAddr());
        logo3Dssa_.setTexture(texture_);
        logo3Dssa_.pause(true);
        dss::sprintf_s(path, sizeof(path), "data/opening/%s/%s/logo_%s_%s4.dssa", area, lang, area, lang);
        logo4Data_.setup(path, 0, 0);
        logo4Dssa_.setup(logo4Data_.getAddr());
        logo4Dssa_.setTexture(texture_);
        logo4Dssa_.pause(true);
    }
    Sound::bgmStop(0xf);
    CeremonyStage::getSingleton()->stage_.m_fld.SetCameraNo(1, 0);
    CeremonyStage::getSingleton()->stage_.m_fld.SetCameraNo(2, 1);
}

THUMB void ceremony::CeremonyOpeningSystem::terminate()
{
    Sound::strmStop(0xf);
    texture_->freeVram();
    textureData_.cleanup();
    logo1Dssa_.cleanup();
    logo1Data_.cleanup();
    logo3Dssa_.cleanup();
    logo3Data_.cleanup();
    logo4Dssa_.cleanup();
    logo4Data_.cleanup();
    Sound::strmStop(0);
}

THUMB void ceremony::CeremonyOpeningSystem::execute()
{
    switch (phase_) {
    case OPENING_PHASE_FADEIN:
        if (counter_ == 30) {
            setNextPhase(OPENING_PHASE_KEYWAIT);
            Sound::strmPlay(0);
            logo1Dssa_.start(0);
            cmn::CommonEffectLocation::getSingleton().start(0x26, 0);
        }
        break;
    case OPENING_PHASE_KEYWAIT:
        if (dss::g_Pad.edge() != 0 && !(dss::g_Pad.edge() & PAD_BUTTON_SELECT)) {
            if (CeremonySetting::getSingleton()->opening_ == 0) {
                setNextPhase(OPENING_PHASE_TO_GAMELOAD);
            } else {
                setNextPhase(OPENING_PHASE_TO_GAMESTART);
            }
            Sound::strmStop(0xf);
        } else if (!Sound::isStrmPlaying()) {
            if (CeremonySetting::getSingleton()->opening_ == 0) {
                setNextPhase(OPENING_PHASE_TO_LOGO);
            } else {
                setNextPhase(OPENING_PHASE_TO_GAMESTART);
            }
            Sound::strmStop(0xf);
        }
        break;
    case OPENING_PHASE_TO_LOGO:
        g_Global.startLogo();
        setNextPhase(OPENING_PHASE_STOP);
        break;
    case OPENING_PHASE_TO_GAMELOAD:
        g_Global.startGame();
        setNextPhase(OPENING_PHASE_STOP);
        break;
    case OPENING_PHASE_TO_GAMESTART:
        status::g_Story.setChapter(dq5::CHAPTER_YOUNENKI);
        cmn::g_extraMapLink.setExtraLinkTown(CeremonySetting::getSingleton()->getNextActMap(), CeremonySetting::getSingleton()->getNextActPos(), 0);
        setNextPhase(OPENING_PHASE_STOP);
        break;
    }
    if (logo1Dssa_.isEnd() && !logo1Dssa_.isPause()) {
        logo1Dssa_.pause(true);
        logo1Dssa_.setCurrentFrame(logo1Dssa_.dssaData_.frame_ - 1);
        CeremonyStage::getSingleton()->stage_.eventAnim(1, 0);
    }
    counter_++;
}

THUMB void ceremony::CeremonyOpeningSystem::draw()
{
    if (getDisplayFrame() & 1) {
        dss::Fix32Vector3 posD(0, 0, 0x400);
        logo1Dssa_.setPosition(posD);
        logo1Dssa_.draw();
        logo1Dssa_.execute();
    } else {
        dss::Fix32Vector3 posU(0, 0x100, 0x400);
        logo1Dssa_.setPosition(posU);
        logo1Dssa_.draw();
    }
}

THUMB void ceremony::CeremonyOpeningSystem::setNextPhase(int phase)
{
    phase_ = phase;
    counter_ = 0;
}
