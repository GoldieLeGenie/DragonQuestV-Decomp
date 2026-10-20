#pragma ipa file
#include "ov004/ceremony/CeremonyEndingSystem.hpp"
#include "main/ceremony/CeremonySetting.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkLanguage.hpp"
#include "main/dss/RenderObject.hpp"
#include "ov004/leveldata/PetalData.hpp"

inline UnkLZDataObject::UnkLZDataObject()
{
}

inline DSSAObject2D::DSSAObject2D()
{
}

inline DSSAObject2D::~DSSAObject2D()
{
}

inline dq5::level::PetalData* dq5::level::PetalData::getRecord(int index)
{
    return (PetalData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline int ceremony::CeremonySetting::getNextActMap()
{
    return nextActMap_;
}

inline dss::Fix32Vector3& ceremony::CeremonySetting::getNextActPos()
{
    return nextActPosition_;
}

THUMB ceremony::CeremonyEndingSystem::CeremonyEndingSystem()
{
}

THUMB ceremony::CeremonyEndingSystem::~CeremonyEndingSystem()
{
}

THUMB ceremony::CeremonyEndingSystem* ceremony::CeremonyEndingSystem::getSingleton()
{
    static CeremonyEndingSystem m_singleton;
    return &m_singleton;
}

THUMB void ceremony::CeremonyEndingSystem::initialize()
{
    char path[128];
    dq5::level::PetalData::setup();
    if (unkfunc_020464e8() == 1) {
        rollStart_[0] = 0;
        rollEnd_[0] = 3;
        rollStart_[1] = 4;
        rollEnd_[1] = 8;
        rollStart_[2] = 9;
        rollEnd_[2] = 12;
        rollStart_[3] = 13;
        rollEnd_[3] = 17;
        rollStart_[4] = 18;
        rollEnd_[4] = 23;
        rollStart_[5] = 24;
        rollEnd_[5] = 61;
    } else if (unkfunc_020464e8() == 2) {
        rollStart_[0] = 0;
        rollEnd_[0] = 3;
        rollStart_[1] = 4;
        rollEnd_[1] = 7;
        rollStart_[2] = 8;
        rollEnd_[2] = 14;
        rollStart_[3] = 15;
        rollEnd_[3] = 19;
        rollStart_[4] = 20;
        rollEnd_[4] = 25;
        rollStart_[5] = 26;
        rollEnd_[5] = 61;
    } else {
        rollStart_[0] = 0;
        rollEnd_[0] = 3;
        rollStart_[1] = 4;
        rollEnd_[1] = 7;
        rollStart_[2] = 8;
        rollEnd_[2] = 13;
        rollStart_[3] = 14;
        rollEnd_[3] = 17;
        rollStart_[4] = 18;
        rollEnd_[4] = 23;
        rollStart_[5] = 24;
        rollEnd_[5] = 61;
    }
    index_ = CeremonySetting::getSingleton()->staffrollIndex_;
    if (index_ != 5) {
        lineCount_ = rollEnd_[index_] - rollStart_[index_] + 3;
    } else {
        lineCount_ = rollEnd_[index_] - rollStart_[index_] + 1;
    }
    for (int i = 0; i < lineCount_; i++) {
        lineY_[i] = 0x180 + i * 0xc0;
    }
    for (int i = 0; i < DIVISION; i++) {
        pageY_[i] = i * 0xc0;
        rollSprite_[i].enable_ = 0;
    }
    phase_ = ENDING_PHASE_FADEIN;
    counter_ = 0;
    endStaff_ = 0;
    dss::sprintf_s(path, sizeof(path), "data/ending/animation/hanabira.tex");
    petalTextureData_.setup(path, 0, 0);
    petalTexture_ = (TextureObject*)petalTextureData_.getAddr();
    petalTexture_->unkfunc_02049e9c(0);
    for (int i = 0; i < MAX_PETAL; i++) {
        dss::sprintf_s(path, sizeof(path), "data/ending/animation/hanabira_%d.dssa", i + 1);
        petalData_[i].setup(path, 0, 0);
        petalDssa_[i].setup(petalData_[i].getAddr());
        petalDssa_[i].setTexture(petalTexture_);
        petalDssa_[i].pause(true);
    }
}

THUMB void ceremony::CeremonyEndingSystem::terminate()
{
    for (int i = 0; i < DIVISION; i++) {
        if (rollData_[i].getAddr() != NULL) {
            rollTexture_[i]->unkfunc_02049f90();
            rollData_[i].cleanup();
        }
    }
    petalTexture_->unkfunc_02049f90();
    petalTextureData_.cleanup();
    for (int i = 0; i < MAX_PETAL; i++) {
        petalData_[i].cleanup();
    }
}

THUMB void ceremony::CeremonyEndingSystem::execute()
{
    char path[128];
    switch (phase_) {
    case ENDING_PHASE_FADEIN:
        if (counter_ == 30) {
            setNextPhase(ENDING_PHASE_KEYWAIT);
            counter_ = 0;
        }
        counter_++;
        break;
    case ENDING_PHASE_KEYWAIT:
        for (int i = 0; i < lineCount_; i++) {
            if (lineY_[i] == 0x180) {
                int page = i % DIVISION;
                if (rollStart_[index_] + i <= rollEnd_[index_]) {
                    if (unkfunc_020464e8() == 1) {
                        dss::sprintf_s(path, sizeof(path), "data/ending/jp/endroll%02d.tex.lz", rollStart_[index_] + i);
                    } else if (unkfunc_020464e8() == 2) {
                        dss::sprintf_s(path, sizeof(path), "data/ending/na/endroll%02d.tex.lz", rollStart_[index_] + i);
                    } else {
                        dss::sprintf_s(path, sizeof(path), "data/ending/eu/endroll%02d.tex.lz", rollStart_[index_] + i);
                    }
                } else {
                    if (unkfunc_020464e8() == 1) {
                        dss::sprintf_s(path, sizeof(path), "data/ending/jp/dummy.tex.lz");
                    } else if (unkfunc_020464e8() == 2) {
                        dss::sprintf_s(path, sizeof(path), "data/ending/na/dummy.tex.lz");
                    } else {
                        dss::sprintf_s(path, sizeof(path), "data/ending/eu/dummy.tex.lz");
                    }
                }
                if (rollSprite_[page].enable_) {
                    UnkLZDataObject data;
                    data.setup(path, 0, 1);
                    TextureObject* texture = (TextureObject*)data.getAddr();
                    dss::memcpy((void*)rollTexture_[page]->unkfunc_0204a1c4(), (char*)texture + texture->unkfunc_0204a1c4(), 0x6000);
                    dss::memcpy((void*)rollTexture_[page]->unkfunc_0204a1d4(), (char*)texture + texture->unkfunc_0204a1d4(), 0x20);
                    rollTexture_[page]->unkfunc_0204a090(0);
                    data.cleanup();
                } else {
                    rollData_[page].setup(path, 0, 1);
                    rollTexture_[page] = (TextureObject*)rollData_[page].getAddr();
                    rollSprite_[page].texture_ = rollTexture_[page];
                    rollSprite_[page].enable_ = 1;
                    rollTexture_[page]->unkfunc_02049e9c(0);
                }
                rollSprite_[page].unk_2c = 3;
                rollSprite_[page].unkfunc_02047ecc(0, 0, 0x100, 0xc0);
                rollSprite_[page].unkfunc_02047ec0(0x100, 0xc0);
            }
            lineY_[i]--;
        }
        for (int i = 0; i < lineCount_; i++) {
            if (rollStart_[index_] + i <= rollEnd_[index_]) {
                if (dq5::level::PetalData::getRecord(rollStart_[index_] + i)->position + 0xc0 == lineY_[i]) {
                    petalDssa_[(char)(dq5::level::PetalData::getRecord(rollStart_[index_] + i)->byte_1 & 0xf) - 1].start(0);
                }
            }
        }
        if (lineY_[lineCount_ - 1] <= 0xc0 && index_ == 5) {
            rollSprite_[(lineCount_ - 3) % DIVISION].setAlpha(0);
            if (unkfunc_020464e8() == 1) {
                setNextPhase(ENDING_PHASE_LASTROLL);
                endStaff_ = 0;
            } else {
                setNextPhase(ENDING_PHASE_STOP);
                endStaff_ = 1;
            }
            counter_ = 0;
            return;
        }
        if (lineY_[lineCount_ - 1] <= 0x120 && endStaff_ == 0 && index_ != 5) {
            cmn::g_extraMapLink.setExtraLinkTown(CeremonySetting::getSingleton()->getNextActMap(), CeremonySetting::getSingleton()->getNextActPos(), 0);
            endStaff_ = 1;
        }
        counter_++;
        break;
    case ENDING_PHASE_LASTROLL:
        if (counter_ > 0xc0) {
            setNextPhase(ENDING_PHASE_STOP);
            endStaff_ = 1;
            return;
        }
        counter_++;
        break;
    case ENDING_PHASE_FADEOUT:
        cmn::g_extraMapLink.setExtraLinkTown(CeremonySetting::getSingleton()->getNextActMap(), CeremonySetting::getSingleton()->getNextActPos(), 0);
        endStaff_ = 1;
        break;
    }
}

THUMB void ceremony::CeremonyEndingSystem::draw()
{
    setupOrtho2DBackground();
    if (phase_ != ENDING_PHASE_LASTROLL && phase_ != ENDING_PHASE_STOP) {
        for (int i = 0; i < DIVISION; i++) {
            if (getDisplayFrame() & 1) {
                rollSprite_[i].unkfunc_02047e88(0, 0xbf - (counter_ - i * 0xc0) % 0x240);
                if (rollSprite_[i].enable_) {
                    rollSprite_[i].draw();
                }
            } else {
                rollSprite_[i].unkfunc_02047e88(0, 0x17f - (counter_ - i * 0xc0) % 0x240);
                if (rollSprite_[i].enable_) {
                    rollSprite_[i].draw();
                }
            }
        }
    } else {
        if (getDisplayFrame() & 1) {
            rollSprite_[(lineCount_ - 1) % DIVISION].draw();
        } else {
            rollSprite_[(lineCount_ - 2) % DIVISION].unkfunc_02047e88(0, -counter_);
            rollSprite_[(lineCount_ - 2) % DIVISION].draw();
        }
    }
    for (int i = 0; i < MAX_PETAL; i++) {
        if (getDisplayFrame() & 1) {
            petalDssa_[i].draw();
            petalDssa_[i].execute();
        }
        if (petalDssa_[i].isEnd()) {
            petalDssa_[i].pause(true);
        }
    }
}

THUMB void ceremony::CeremonyEndingSystem::setNextPhase(int phase)
{
    phase_ = phase;
}

THUMB bool ceremony::CeremonyEndingSystem::isEnd()
{
    if (endStaff_ == 1) {
        return true;
    }
    return false;
}
