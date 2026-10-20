#pragma ipa file
#include "ov001/town/character/TownModelDraw.hpp"
#include "ov001/town/stage/TownExtraCollManager.hpp"
#include "main/data/FileLoader.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/leveldata/CharaData.hpp"
#include "nitro/os.hpp"

#pragma thumb on

inline dss::Fix32Vector3::Fix32Vector3(const Fix32& x, const Fix32& y, const Fix32& z)
{
    vx = x;
    vy = y;
    vz = z;
}

inline int ModelObject::getAnimation()
{
    return m_animation_index;
}

namespace twn {
    const dss::Fix32 bigRockSpeed((fx32)0x133);
    const dss::Fix32 collLine((fx32)0x1733);
    const dss::Vector3<dss::Fix16> buon(0.363281f, -0.726563f, -0.578125f);
    const dss::Vector3<dss::Fix16> estrk(0.30313f, 0.30313f, -0.903451f);
    const dss::Vector3<dss::Fix16> master(0.363281f, -0.726563f, -0.578125f);
}

twn::TownModelDraw::TownModelDraw()
{
}

twn::TownModelDraw::~TownModelDraw()
{
}

void twn::TownModelDraw::setup(TOWN_CHARACTER& chara)
{
    TownCharacterBase::setup(chara);
    readData();
    switch (data_.charaIndex) {
    case 0x201:
        model_.setLightColor(1, 0x739f);
        model_.setLightVector(1, buon);
        break;
    case 0x206:
        model_.setLightColor(2, 0x7fff);
        model_.setLightVector(2, estrk);
        break;
    case 0x5f:
        model_.setLightColor(1, 0x739f);
        model_.setLightVector(1, master);
        break;
    }
    model_.start(1);
    model_.setPosition(data_.position);
    dirIdx_ = 0;
    display_ = true;
    modelIdx3d_.set(0, 0, 0);
    defaultIndex_ = data_.charaIndex;
    basePalletRate_.value = 0x7d0;
}

void twn::TownModelDraw::cleanup()
{
    model_.cleanup(true);
}

void twn::TownModelDraw::readData()
{
    char path[0x80];
    int index = 0;
    OS_Wait();
    dss::sprintf_s(path, 0x80, "data/chr/h%03d.nsbmd", data_.charaIndex);
    model_.setup(path, NULL, dq5::level::CharaData::loadSwitch_);
    int i = 0;
    int found;
    do {
        found = false;
        dss::sprintf_s(path, 0x80, "data/chr/h%03d_%02d.nsbma", data_.charaIndex, i);
        if (dss::g_File.isExist(path, dq5::level::CharaData::loadSwitch_)) {
            found = true;
            model_.loadAnimation(path, index, dq5::level::CharaData::loadSwitch_);
            index++;
        }
        dss::sprintf_s(path, 0x80, "data/chr/h%03d_%02d.nsbta", data_.charaIndex, i);
        if (dss::g_File.isExist(path, dq5::level::CharaData::loadSwitch_)) {
            found = true;
            model_.loadAnimation(path, index, dq5::level::CharaData::loadSwitch_);
            index++;
        }
        dss::sprintf_s(path, 0x80, "data/chr/h%03d_%02d.nsbca", data_.charaIndex, i);
        if (dss::g_File.isExist(path, dq5::level::CharaData::loadSwitch_)) {
            found = true;
            model_.loadAnimation(path, index, dq5::level::CharaData::loadSwitch_);
            index++;
        }
        i++;
    } while (found);
}

void twn::TownModelDraw::execute()
{
    TownCharacterBase::execute();
}

void twn::TownModelDraw::draw()
{
    if (display_) {
        model_.draw();
    }
}

void twn::TownModelDraw::setDisplay(int flag)
{
    display_ = flag;
}

int twn::TownModelDraw::isDisplay()
{
    return display_;
}

void twn::TownModelDraw::changePose(int set)
{
    model_.cleanup(true);
    data_.charaIndex = set;
    readData();
    model_.start(1);
    model_.setPosition(data_.position);
    dirIdx_ = 0;
    display_ = true;
    modelIdx3d_.set(0, 0, 0);
}

void twn::TownModelDraw::restorePose()
{
    model_.cleanup(true);
    data_.charaIndex = defaultIndex_;
    readData();
    model_.start(1);
    model_.setPosition(data_.position);
}

void twn::TownModelDraw::requestReload()
{
    int anim = model_.getAnimation();
    model_.cleanup(true);
    readData();
    model_.start(1);
    model_.setPosition(data_.position);
    model_.startAnimation(anim, 1);
}

void twn::TownModelDraw::setScale(dss::Fix32 scale)
{
    dss::Fix32Vector3 scl(scale, scale, scale);
    model_.setScale(scl);
}

void twn::TownModelDraw::setAnimation(int flag)
{
    if (flag == 2) {
        flag = 0;
    }
    model_.pause(flag == 0);
}

void twn::TownModelDraw::setPosition(dss::Fix32Vector3& target)
{
    dss::Fix32Vector3 nowPos = getPosition();
    TownExtraCollManager::getSingleton().addMoveColl(data_.ctrlNo, type_, nowPos, target);
    data_.position = target;
    model_.setPosition(target);
}

void twn::TownModelDraw::setRotation(dss::Vector3<short>& rot)
{
    model_.setRotationIdx(rot);
}

dss::Fix32Vector3 twn::TownModelDraw::getPosition()
{
    return data_.position;
}

void twn::TownModelDraw::setPaletteRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b)
{
    setPaletteEffectTexture(model_.unk_1cc.unk_08);
    dss::Fix32Vector3 rate(r, g, b);
    applyModelPaletteRgbRate(model_.unk_1cc.unk_08, rate);
}

void twn::TownModelDraw::setPaletteRate(unsigned char r, unsigned char g, unsigned char b, dss::Fix32 rate)
{
    int rr = dss::clamp<unsigned int>(0, r, 0x1f);
    int gg = dss::clamp<unsigned int>(0, g, 0x1f);
    int bb = dss::clamp<unsigned int>(0, b, 0x1f);
    rate.value = dss::clamp<int>(0, rate.value, basePalletRate_.value);
    blendModelPaletteToColor(model_.unk_1cc.unk_08, rr, gg, bb, rate);
}

void twn::TownModelDraw::setMotion(int motion, bool flag)
{
    setAnimation(1);
    model_.startAnimation(motion, flag);
}

bool twn::TownModelDraw::isMotion()
{
    return model_.m_play_flag == 0;
}

void twn::TownModelDraw::setDir(int dir)
{
    dirIdx_ = dir;
    dss::Vector3<short> rot;
    rot.set(0, dirIdx_, 0);
    setRotation(rot);
}

void twn::TownModelDraw::setPalletRate(dss::Fix32 rate)
{
    basePalletRate_ = rate;
}

int twn::TownModelDraw::getDir()
{
    return dirIdx_;
}
