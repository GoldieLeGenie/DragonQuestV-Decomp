#include "ov001/town/TownStageEffectManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkModelMember.hpp"
#include "main/dss/UnkVramTransfer.hpp"
#include "main/sound/SoundManager.hpp"

#pragma thumb on

namespace twn {
    namespace {
        int flashFrame[3] = {0x33, 0x5c, 0x63};
        int lightFrame[3] = {0x28, 6, 0x28};
    }
}

twn::TownStageLightning::TownStageLightning() : counter_(0), phase_(false), enable_(false)
{
}

twn::TownStageLightning::~TownStageLightning()
{
}

void twn::TownStageLightning::setup()
{
    light_ = 0x1000;
    dark_ = 0;
    enable_ = true;
    counter_ = 0;
    TownStageManager::getSingleton()->setObjectDraw(0x204, 1, 1);
    char path[128];
    dss::sprintf_s(path, sizeof(path), "data/light/light.dat");
    unk_1c.setup(path, 0, 0);
    dss::sprintf_s(path, sizeof(path), "data/light/light2.dat");
    unk_2c.setup(path, 0, 0);
}

void twn::TownStageLightning::start(int first)
{
    lightCounter_ = 0;
    frame_ = first;
    phase_ = true;
}

void twn::TownStageLightning::cleanup()
{
    unk_1c.cleanup();
    unk_2c.cleanup();
    enable_ = false;
    phase_ = false;
}

void twn::TownStageLightning::execute()
{
    if (enable_ == false || (unkfunc_0204ccd0() & 1)) {
        return;
    }
    counter_++;
    NNSG3dResTex* tex;
    unsigned int size;
    unsigned int address;
    char* data;
    if (phase_ == false) {
        tex = unkfunc_02046f40();
        size = tex->plttInfo.sizePltt << 3;
        address = (tex->plttInfo.vramKey & 0xffff) << 3;
        data = (char*)unk_1c.getAddr();
        data += size * 39;
        data_020f4f74.unkfunc_0204a6f0(1, data, address, size, 0);
        TownCharacterManager::getSingleton()->setSpecCharaAlpha(0x4d, 0);
    } else {
        tex = unkfunc_02046f40();
        size = tex->plttInfo.sizePltt << 3;
        address = (tex->plttInfo.vramKey & 0xffff) << 3;
        if (frame_ == 0x28) {
            data = (char*)unk_1c.getAddr();
        } else {
            data = (char*)unk_2c.getAddr();
        }
        data += size * lightCounter_;
        data_020f4f74.unkfunc_0204a6f0(1, data, address, size, 0);
        int color = (lightCounter_ * dark_ + light_ * (frame_ - lightCounter_)) / frame_;
        TownCharacterManager::getSingleton()->setSpecCharaAlpha(0x4d, color * 31 / 4096);
        if (lightCounter_ == 0) {
            SoundManager::playSe2(0x68, 0);
        }
        lightCounter_++;
        if (lightCounter_ == frame_) {
            phase_ = false;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (counter_ == flashFrame[i]) {
            start(lightFrame[i]);
        }
    }
    if (counter_ == 179) {
        counter_ = 0;
    }
}

void twn::TownStageLightning::setEnable(bool en)
{
    enable_ = en;
    if (en) {
        TownStageManager::getSingleton()->setObjectDraw(0x204, 1, 1);
    } else {
        TownStageManager::getSingleton()->setObjectDraw(0x204, 0, 1);
    }
}
