#include "ov001/town/stage/effect/TownStageWrap.hpp"
#include "main/data/FileLoader.hpp"
#include "main/dss/DssUtils.hpp"

#pragma thumb on

void twn::TownStageWrap::setup(EFFECT_TYPE type)
{
    char filename[0x80];
    effectType_ = type;
    checkData();
    isDisplay_ = false;
    if (isSetup_) {
        sprite_.unload();
    }
    isSetup_ = true;
    if (isData_) {
        switch (effectType_) {
        case EFFECT_TYPE_DREAM1:
            dss::sprintf_s(filename, sizeof(filename), "data/mask/siro1a1.tex");
            sprite_.loadFile(filename, 0);
            sprite_.setMainScreen();
            sprite_.setAlpha(0x1e);
            sprite_.setPolygonID(0x3c);
            unk_50.setSubScreen();
            unk_50.setPolygonID(0x3d);
            break;
        case EFFECT_TYPE_DREAM2:
            dss::sprintf_s(filename, sizeof(filename), "data/mask/siro1a2.tex");
            sprite_.loadFile(filename, 0);
            sprite_.setMainScreen();
            sprite_.setAlpha(0x1e);
            sprite_.setPolygonID(0x3c);
            unk_50.setupTexture();
            unk_50.setSubScreen();
            unk_50.setPolygonID(0x3d);
            break;
        case EFFECT_TYPE_DEATHPISARO:
            dss::sprintf_s(filename, sizeof(filename), "data/mask/pisaro.tex");
            sprite_.loadFile(filename, 0);
            sprite_.setMainScreen();
            sprite_.setAlpha(0x1e);
            sprite_.setPolygonID(0x3c);
            centerX_ = 0x80;
            centerY_ = 0x60;
            sizeX_ = 0x100;
            sizeY_ = 0xc0;
            break;
        }
    }
    colorR_ = 0x1f;
    colorG_ = 0x1f;
    colorB_ = 0x1f;
    counter_ = -1;
}

void twn::TownStageWrap::cleanup()
{
    if (isSetup_) {
        sprite_.unload();
        isData_ = false;
        isDisplay_ = false;
    }
    isSetup_ = false;
}

void twn::TownStageWrap::checkData()
{
    char filename[0x80];
    isData_ = false;
    switch (effectType_) {
    case EFFECT_TYPE_DREAM1:
        dss::sprintf_s(filename, sizeof(filename), "data/mask/siro1a1.tex");
        isData_ = dss::g_File.isExist(filename, dss::File::None);
        break;
    case EFFECT_TYPE_DREAM2:
        dss::sprintf_s(filename, sizeof(filename), "data/mask/siro1a2.tex");
        isData_ = dss::g_File.isExist(filename, dss::File::None);
        break;
    case EFFECT_TYPE_DEATHPISARO:
        dss::sprintf_s(filename, sizeof(filename), "data/mask/pisaro.tex");
        isData_ = dss::g_File.isExist(filename, dss::File::None);
        break;
    }
}

void twn::TownStageWrap::setScalingX(fx32 scale)
{
}

void twn::TownStageWrap::setScalingY(fx32 scale)
{
}
