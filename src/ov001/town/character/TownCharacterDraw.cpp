#pragma ipa file
#include "ov001/town/TownCharacterManager.hpp"
#include "main/leveldata/CharaData.hpp"
#include "nitro/os.hpp"

inline dq5::level::CharaData* dq5::level::CharaData::getRecord(int index)
{
    return (CharaData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned char dq5::level::CharaData::getHeight()
{
    return height;
}

inline unsigned char dq5::level::CharaData::getWidth()
{
    return width;
}

inline void dq5::level::CharaData::setWidth(unsigned char data)
{
    width = data;
}

inline unsigned char DisplayCharacter::getAlpha()
{
    return alpha_;
}

THUMB twn::TownCharacterDraw::TownCharacterDraw()
{
}

THUMB twn::TownCharacterDraw::~TownCharacterDraw()
{
}

THUMB void twn::TownCharacterDraw::setup(TOWN_CHARACTER& chara)
{
    TownCharacterBase::setup(chara);
    if (data_.charaIndex != 999) {
        if (dq5::level::CharaData::getRecord(charaParamIndex_)->getWidth() < 0x20) {
            dq5::level::CharaData::getRecord(charaParamIndex_)->setWidth(0x20);
        }
        character_.setCharacterSize(dq5::level::CharaData::getRecord(charaParamIndex_)->getWidth(), dq5::level::CharaData::getRecord(charaParamIndex_)->getHeight());
        char name[128];
        dss::sprintf_s(name, sizeof(name), "data/chr/h%03d.pack", data_.charaIndex);
        character_.setup(name, dq5::level::CharaData::loadSwitch_);
        character_.setPosition(data_.position);
        character_.setRotate(data_.dir);
        character_.setRender(render_);
        BillboardCharacter::setCamera(cmr_);
    }
}

THUMB void twn::TownCharacterDraw::execute()
{
    TownCharacterBase::execute();
}

THUMB void twn::TownCharacterDraw::cleanup()
{
    if (data_.charaIndex != 999) {
        data_.enable = 0;
        if (dataObject_.getAddr()) {
            restorePose();
        }
        character_.cleanup();
    }
}

THUMB void twn::TownCharacterDraw::setDir(int dir)
{
    data_.dir = dir;
    character_.setRotate(dir);
}

THUMB int twn::TownCharacterDraw::getDir()
{
    return data_.dir;
}

THUMB void twn::TownCharacterDraw::draw()
{
}

THUMB void twn::TownCharacterDraw::setDisplay(int flag)
{
    character_.setDisplayEnable(flag);
}

THUMB int twn::TownCharacterDraw::isDisplay()
{
    return character_.isDisplayEnable();
}

THUMB void twn::TownCharacterDraw::setShadow(int flag)
{
    character_.setShadowFlag(flag);
}

THUMB void twn::TownCharacterDraw::setAnimation(int flag)
{
    if (data_.flag.check(0x8000) != true || flag == 0) {
        character_.setAnimFlag(flag);
    }
}

THUMB void twn::TownCharacterDraw::setNearCharacter(int flag)
{
    character_.setNearFlag(flag);
}

THUMB void twn::TownCharacterDraw::setWriggleCharacter(int flag)
{
    character_.setWriggleFlag(flag);
}

THUMB void twn::TownCharacterDraw::setPosition(dss::Fix32Vector3& pos)
{
    data_.position = pos;
    character_.setPosition(pos);
}

THUMB void twn::TownCharacterDraw::setSleepCharacter(int flag)
{
    type_ = flag == 1 ? 1 : 0;
    character_.setSleepFlag(flag);
}

THUMB void twn::TownCharacterDraw::changePose(int set)
{
    if (data_.charaIndex != 999) {
        character_.unkfunc_02055a60();
        if (dataObject_.getAddr()) {
            dataObject_.cleanup();
        }
        char name[128];
        dss::sprintf_s(name, sizeof(name), "data/chr/h%03d.pack", set);
        OS_Wait();
        dataObject_.setup(name, dq5::level::CharaData::loadSwitch_, 0);
        character_.setTextureWithHead(dataObject_.getAddr());
        data_.charaIndex = set;
    }
}

THUMB void twn::TownCharacterDraw::restorePose()
{
    if (data_.charaIndex != 999) {
        character_.unkfunc_02055a60();
        if (dataObject_.getAddr()) {
            dataObject_.cleanup();
        }
        character_.resetTextureWithHead();
    }
}

THUMB void twn::TownCharacterDraw::setPaletteRate(dss::Fix32 r, dss::Fix32 g, dss::Fix32 b)
{
    setRGB.set(r, g, b);
    character_.setAnimPalletFlag(1);
    character_.setPaletteRgbRate(&setRGB);
}

THUMB bool twn::TownCharacterDraw::isEndPalletRate()
{
    if (rgbFrame_ == 0) {
        dss::Fix32Vector3 rate;
        rate.vx.value = rate.vy.value = rate.vz.value = 0x1000;
        character_.setPaletteRgbRate(&rate);
    } else if (rgbFrame_ == -1) {
        character_.setAnimPalletFlag(0);
        return true;
    }
    return false;
}

THUMB void twn::TownCharacterDraw::setShadowOnly(int flag)
{
    character_.setShadowOnlyFlag(flag);
}

THUMB void twn::TownCharacterDraw::setHueChange(int type, int frame)
{
    character_.setHueChange(type, frame);
}

THUMB bool twn::TownCharacterDraw::isHueChange()
{
    return character_.isHueChange();
}

THUMB void twn::TownCharacterDraw::setColor(unsigned char r, unsigned char g, unsigned char b)
{
    character_.setColor((unsigned short)(r | (g << 5) | (b << 10)));
}

THUMB void twn::TownCharacterDraw::setRotation(unsigned short rot)
{
    character_.setRotate(rot);
}

THUMB void twn::TownCharacterDraw::requestReload()
{
    character_.requestReload();
}

THUMB unsigned char twn::TownCharacterDraw::getAlpha()
{
    return character_.getAlpha();
}

THUMB void twn::TownCharacterDraw::setAlpha(unsigned char alpha)
{
    character_.setAlpha(alpha);
}
