#pragma ipa file
#include "ov001/town/character/TownMonsterDraw.hpp"
#include "ov001/town/TownCamera.hpp"
#include "main/dss/DssUtils.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/leveldata/CharaData.hpp"

inline void DSSACharacter::setCamera(dss::Camera* camera)
{
    DSSAObjectWithCamera::camera_ = camera;
}

#pragma thumb on

inline UnkFileDataObject::UnkFileDataObject()
{
}

inline UnkFileDataObject::~UnkFileDataObject()
{
}

inline dss::Fix32Vector3::Fix32Vector3(const Fix32& x, const Fix32& y, const Fix32& z)
{
    vx = x;
    vy = y;
    vz = z;
}

inline int DSSACharacter::getAnimation()
{
    return currentAnimationIndex_;
}

twn::TownMonsterDraw::TownMonsterDraw()
{
}

twn::TownMonsterDraw::~TownMonsterDraw()
{
}

void twn::TownMonsterDraw::setup(TOWN_CHARACTER& chara)
{
    char path[0x80];
    TownCharacterBase::setup(chara);
    dss::sprintf_s(path, 0x80, "data/chr/h%03d.tex.lz", data_.charaIndex);
    textureData_.setup(path, dq5::level::CharaData::loadSwitch_, 1);
    TextureObject* texture = (TextureObject*)textureData_.getAddr();
    texture->loadToVram(1);
    dss::memcpy(&texture_, texture, 0x70);
    if (data_.charaIndex == 0x204 || data_.charaIndex == 0x205 || data_.charaIndex == 0x219) {
        textureData_.cleanup();
    }
    if (data_.charaIndex != 0x219) {
        dss::sprintf_s(path, 0x80, "data/chr/h%03d.anm.lz", data_.charaIndex);
        animData_.setup(path, dq5::level::CharaData::loadSwitch_, 1);
        monster_.unkfunc_020524c8(&texture_, &animData_);
    } else {
        monster_.setupStream(&texture_, "data/chr/mild_c_%02d.dssa", 0x10);
    }
    monster_.setPosition(data_.position);
    monster_.setCameraType(DSSAObjectWithCamera::Standard);
    display_ = true;
    monster_.pause(false);
    defaultIndex_ = data_.charaIndex;
}

void twn::TownMonsterDraw::cleanup()
{
    if (data_.enable) {
        data_.enable = false;
        monster_.cleanup();
        animData_.cleanup();
        if (data_.charaIndex != 0x204 && data_.charaIndex != 0x205 && data_.charaIndex != 0x219) {
            textureData_.cleanup();
        }
    }
}

void twn::TownMonsterDraw::execute()
{
    TownCharacterBase::execute();
}

void twn::TownMonsterDraw::draw()
{
    if (display_) {
        DSSAObject::calcType_ = false;
        int no = (getDisplayFrame() & 1) ? 0 : 1;
        TownCamera* camera = TownCamera::getSingleton();
        monster_.setCamera(no == 0 ? &camera->camera_.m_camera0 : &camera->camera_.m_camera1);
        monster_.draw();
        dss::Fix32Vector3 pos = *monster_.getPosition();
        DSSAObject::calcType_ = true;
    }
}

void twn::TownMonsterDraw::setDisplay(int flag)
{
    display_ = flag;
}

int twn::TownMonsterDraw::isDisplay()
{
    return display_;
}

void twn::TownMonsterDraw::setNearCharacter(int flag)
{
    if (flag == 1) {
        monster_.setCameraType(DSSAObjectWithCamera::Normal2);
    } else {
        monster_.setCameraType(DSSAObjectWithCamera::Standard);
        monster_.setScale(DSSAObject::getDefaultScale2());
    }
}

void twn::TownMonsterDraw::setAnimation(int flag)
{
    if (flag == 2) {
        flag = 0;
    }
    monster_.pause(flag == 0);
}

void twn::TownMonsterDraw::setPosition(dss::Fix32Vector3& pos)
{
    data_.position = pos;
    monster_.setPosition(pos);
}

void twn::TownMonsterDraw::setPaletteRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b)
{
    TextureObject* texture = monster_.texture_;
    dss::Fix32Vector3 rate(r, g, b);
    applyTexturePaletteRgbRate(texture, rate);
}

void twn::TownMonsterDraw::setMotion(int motion, bool flag)
{
    monster_.start(motion, flag);
}

bool twn::TownMonsterDraw::isMotion()
{
    return monster_.getAnimation() == 0;
}

void twn::TownMonsterDraw::setDir(int dir)
{
}

int twn::TownMonsterDraw::getDir()
{
    return 0;
}

void twn::TownMonsterDraw::changePose(int pose)
{
    monster_.cleanup();
    data_.charaIndex = pose;
    monster_.setupFromData(&textureData_, &animData_);
    monster_.setPosition(data_.position);
    monster_.setCameraType(DSSAObjectWithCamera::Standard);
    display_ = true;
    monster_.pause(false);
}

void twn::TownMonsterDraw::restorePose()
{
    monster_.cleanup();
    data_.charaIndex = defaultIndex_;
    monster_.setupFromData(&textureData_, &animData_);
    monster_.setPosition(data_.position);
    monster_.setCameraType(DSSAObjectWithCamera::Standard);
    monster_.pause(false);
}

void twn::TownMonsterDraw::requestReload()
{
    int animation = monster_.getAnimation();
    monster_.cleanup();
    monster_.setupFromData(&textureData_, &animData_);
    monster_.setPosition(data_.position);
    monster_.setCameraType(DSSAObjectWithCamera::Standard);
    monster_.pause(false);
    monster_.start(animation, true);
}

void twn::TownMonsterDraw::setScale(dss::Fix32 scale)
{
    monster_.setScale(scale);
}

void twn::TownMonsterDraw::setAlpha(unsigned char alpha)
{
    monster_.setAlpha(alpha);
}
