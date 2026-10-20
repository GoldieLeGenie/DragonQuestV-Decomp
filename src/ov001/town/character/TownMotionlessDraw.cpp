#pragma ipa file
#include "ov001/town/character/TownMotionlessDraw.hpp"
#include "ov001/town/stage/TownExtraCollManager.hpp"
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

inline unsigned char twn::TownCharacterBase::getAlpha()
{
    return 0;
}

inline int twn::TownMotionlessDraw::getDir()
{
    return dirIdx_;
}

namespace twn {
    const dss::Fix32 bigRockSpeed((fx32)0x133);
    const dss::Fix32 collLine((fx32)0x1733);
}

twn::TownMotionlessDraw::TownMotionlessDraw()
{
}

twn::TownMotionlessDraw::~TownMotionlessDraw()
{
}

void twn::TownMotionlessDraw::setup(TOWN_CHARACTER& chara)
{
    TownCharacterBase::setup(chara);
    readData();
    motionless_.setModelPosition(data_.position);
    dirIdx_ = 0;
    display_ = true;
    modelIdx3d_.set(0, 0, 0);
    defaultIndex_ = data_.charaIndex;
    basePalletRate_.value = 0x7d0;
}

void twn::TownMotionlessDraw::cleanup()
{
    motionless_.vf04();
}

void twn::TownMotionlessDraw::readData()
{
    char path[0x80];
    OS_Wait();
    dss::sprintf_s(path, 0x80, "data/chr/h%03d.nsbmd", data_.charaIndex);
    motionless_.setup(path, dq5::level::CharaData::loadSwitch_);
}

void twn::TownMotionlessDraw::execute()
{
    TownCharacterBase::execute();
}

void twn::TownMotionlessDraw::draw()
{
    if (display_) {
        motionless_.draw();
    }
}

void twn::TownMotionlessDraw::setDisplay(int flag)
{
    display_ = flag;
}

int twn::TownMotionlessDraw::isDisplay()
{
    return display_;
}

void twn::TownMotionlessDraw::changePose(int set)
{
    motionless_.vf04();
    data_.charaIndex = set;
    readData();
    motionless_.setModelPosition(data_.position);
    dirIdx_ = 0;
    display_ = true;
    modelIdx3d_.set(0, 0, 0);
}

void twn::TownMotionlessDraw::restorePose()
{
    motionless_.vf04();
    data_.charaIndex = defaultIndex_;
    readData();
    motionless_.setModelPosition(data_.position);
}

void twn::TownMotionlessDraw::requestReload()
{
    motionless_.vf04();
    readData();
    motionless_.setModelPosition(data_.position);
}

void twn::TownMotionlessDraw::setScale(dss::Fix32 scale)
{
    dss::Fix32Vector3 scl(scale, scale, scale);
    motionless_.setModelScale(scl);
}

void twn::TownMotionlessDraw::setPosition(dss::Fix32Vector3& target)
{
    dss::Fix32Vector3 nowPos = getPosition();
    TownExtraCollManager::getSingleton().addMoveColl(data_.ctrlNo, type_, nowPos, target);
    data_.position = target;
    motionless_.setModelPosition(target);
}

void twn::TownMotionlessDraw::setRotation(dss::Vector3<short>& rot)
{
    motionless_.setModelRotation(rot);
}

dss::Fix32Vector3 twn::TownMotionlessDraw::getPosition()
{
    return data_.position;
}

void twn::TownMotionlessDraw::setAnimation(int flag)
{
}

void twn::TownMotionlessDraw::setPaletteRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b)
{
    setPaletteEffectTexture(motionless_.unk_1cc.unk_08);
    dss::Fix32Vector3 rate(r, g, b);
    applyModelPaletteRgbRate(motionless_.unk_1cc.unk_08, rate);
}

void twn::TownMotionlessDraw::setPaletteRate(unsigned char r, unsigned char g, unsigned char b, dss::Fix32 rate)
{
    int rr = dss::clamp<unsigned int>(0, r, 0x1f);
    int gg = dss::clamp<unsigned int>(0, g, 0x1f);
    int bb = dss::clamp<unsigned int>(0, b, 0x1f);
    rate.value = dss::clamp<int>(0, rate.value, basePalletRate_.value);
    blendModelPaletteToColor(motionless_.unk_1cc.unk_08, rr, gg, bb, rate);
}

void twn::TownMotionlessDraw::setDir(int dir)
{
    dirIdx_ = dir;
    dss::Vector3<short> rot;
    rot.set(0, dirIdx_, 0);
    setRotation(rot);
}

void twn::TownMotionlessDraw::setPalletRate(dss::Fix32 rate)
{
    basePalletRate_ = rate;
}
