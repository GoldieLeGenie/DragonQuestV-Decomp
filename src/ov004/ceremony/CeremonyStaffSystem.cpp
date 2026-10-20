#pragma ipa file
#include "ov004/ceremony/CeremonyStaffSystem.hpp"
#include "main/ceremony/CeremonySetting.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/Pad.hpp"
#include "nitro/pad.h"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkLanguage.hpp"
#include "main/global/Global.hpp"
#include "main/sound/Sound.hpp"
#include "main/status/GameStatus.hpp"

inline UnkLZDataObject::UnkLZDataObject()
{
}

inline DSSAObject2D::DSSAObject2D()
{
}

inline DSSAObject2D::~DSSAObject2D()
{
}

THUMB ceremony::CeremonyStaffSystem::CeremonyStaffSystem()
{
}

THUMB ceremony::CeremonyStaffSystem::~CeremonyStaffSystem()
{
}

THUMB ceremony::CeremonyStaffSystem* ceremony::CeremonyStaffSystem::getSingleton()
{
    static CeremonyStaffSystem m_singleton;
    return &m_singleton;
}

THUMB void ceremony::CeremonyStaffSystem::initialize()
{
    dss::Fix32 scl;
    scl.value = 0x320;
    DSSAObject::setDefaultScale(scl);
    DSSAObject::setPriority(1);
    if (getGameRegion() == 1) {
        char path[128];
        dss::sprintf_s(path, sizeof(path), "data/opening/jp/staff.tex.lz");
        textureData_.setup(path, 0, 1);
        texture_ = (TextureObject*)textureData_.getAddr();
        texture_->loadToVram(1);
        dss::sprintf_s(path, sizeof(path), "data/opening/jp/staff_u.dssa");
        staffUpData_.setup(path, 0, 0);
        staffUpDssa_.setup(staffUpData_.getAddr());
        staffUpDssa_.setTexture(texture_);
        dss::sprintf_s(path, sizeof(path), "data/opening/jp/staff_d.dssa");
        staffDownData_.setup(path, 0, 0);
        staffDownDssa_.setup(staffDownData_.getAddr());
        staffDownDssa_.setTexture(texture_);
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
        dss::sprintf_s(path, sizeof(path), "data/opening/%s/%s/staff_%s_%s.tex.lz", area, lang, area, lang);
        textureData_.setup(path, 0, 1);
        texture_ = (TextureObject*)textureData_.getAddr();
        texture_->loadToVram(1);
        dss::sprintf_s(path, sizeof(path), "data/opening/%s/%s/staff_%s_%s_u.dssa", area, lang, area, lang);
        staffUpData_.setup(path, 0, 0);
        staffUpDssa_.setup(staffUpData_.getAddr());
        staffUpDssa_.setTexture(texture_);
        dss::sprintf_s(path, sizeof(path), "data/opening/%s/%s/staff_%s_%s_d.dssa", area, lang, area, lang);
        staffDownData_.setup(path, 0, 0);
        staffDownDssa_.setup(staffDownData_.getAddr());
        staffDownDssa_.setTexture(texture_);
    }
    Sound::unkfunc_0206889c(0xf);
}

THUMB void ceremony::CeremonyStaffSystem::terminate()
{
    Sound::unkfunc_02068908(0xf);
    texture_->freeVram();
    textureData_.cleanup();
    staffUpDssa_.cleanup();
    staffUpData_.cleanup();
    staffDownDssa_.cleanup();
    staffDownData_.cleanup();
    Sound::unkfunc_02068908(0);
}

THUMB void ceremony::CeremonyStaffSystem::execute()
{
    switch (phase_) {
    case STAFF_PHASE_FADEIN:
        if (counter_ == 30) {
            setNextPhase(STAFF_PHASE_KEYWAIT);
        }
        break;
    case STAFF_PHASE_KEYWAIT:
        if (dss::g_Pad.edge() != 0 && !(dss::g_Pad.edge() & PAD_BUTTON_SELECT)) {
            setNextPhase(STAFF_PHASE_FADEOUT);
        } else if (staffUpDssa_.isPause()) {
            setNextPhase(STAFF_PHASE_FADEOUT);
        }
        break;
    case STAFF_PHASE_FADEOUT:
        g_Global.startTitle();
        CeremonySetting::getSingleton()->opening_ = 0;
        setNextPhase(STAFF_PHASE_STOP);
        break;
    }
    if (staffUpDssa_.isEnd() && !staffUpDssa_.isPause()) {
        staffUpDssa_.pause(true);
        staffUpDssa_.setCurrentFrame(staffUpDssa_.dssaData_.frame_ - 1);
        staffDownDssa_.pause(true);
        staffDownDssa_.setCurrentFrame(staffDownDssa_.dssaData_.frame_ - 1);
    }
    counter_++;
}

THUMB void ceremony::CeremonyStaffSystem::draw()
{
    if (getDisplayFrame() & 1) {
        dss::Fix32Vector3 posD(0, 0x18, 0);
        staffDownDssa_.setPosition(posD);
        staffDownDssa_.draw();
        staffDownDssa_.execute();
        staffUpDssa_.execute();
    } else {
        dss::Fix32Vector3 posU(0, 0x18, 0);
        staffUpDssa_.setPosition(posU);
        staffUpDssa_.draw();
    }
}

THUMB void ceremony::CeremonyStaffSystem::setNextPhase(int phase)
{
    phase_ = phase;
    counter_ = 0;
}
