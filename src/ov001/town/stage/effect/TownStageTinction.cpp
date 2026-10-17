#include "ov001/town/stage/effect/TownStageTinction.hpp"
#include "ov001/leveldata/FloorBackColor.hpp"
#include "ov001/leveldata/FloorFog.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/dss/UnkFog.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "main/dss/UnkRenderObject.hpp"
#include "main/leveldata/CLUTCode.hpp"
#include "main/leveldata/ColorCorrect.hpp"
#include "main/status/StageAttribute.hpp"
#include "main/status/StageInfo.hpp"

#pragma thumb on

inline dq5::level::ColorCorrect* dq5::level::ColorCorrect::getRecord(int index)
{
    return (ColorCorrect*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned char dq5::level::ColorCorrect::getBackcolor()
{
    return backcolor;
}

inline int dq5::level::ColorCorrect::getFog()
{
    return (byte_1 & 0x1c) << 22 >> 24;
}

inline char dq5::level::ColorCorrect::getClut()
{
    return byte_2 & 0xf;
}

inline dq5::level::FloorFog* dq5::level::FloorFog::getRecord(int index)
{
    return (FloorFog*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::FloorBackColor* dq5::level::FloorBackColor::getRecord(int index)
{
    return (FloorBackColor*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::CLUTCode* dq5::level::CLUTCode::getRecord(int index)
{
    return (CLUTCode*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline fx32 dq5::level::CLUTCode::getColorB()
{
    return colorB;
}

inline fx32 dq5::level::CLUTCode::getColorR()
{
    return colorR;
}

inline fx32 dq5::level::CLUTCode::getColorG()
{
    return colorG;
}

inline int status::StageAttribute::getMapCorrectIndex()
{
    return mapCorrectIndex_;
}

inline void FldStage::SetRGBRate(dss::Fix32Vector3& fldrate, int real_time)
{
    m_fld.SetRGBRate((VecFx32*)&fldrate, real_time);
}

inline void twn::TownStageManager::SetRGBRate(dss::Fix32Vector3& rate, int real_time)
{
    stage_.SetRGBRate(rate, real_time);
}

twn::TownStageTinction::TownStageTinction() : correctTime_(0)
{
}

twn::TownStageTinction::~TownStageTinction()
{
}

void twn::TownStageTinction::cleanup()
{
    unkfunc_02046bc4(false);
}

void twn::TownStageTinction::loadStage()
{
    int worldtime;
    switch (status::g_StageInfo.getTimeZone()) {
    case 1:
        worldtime = 3;
        break;
    case 2:
        worldtime = 0;
        break;
    case 3:
        worldtime = 2;
        break;
    case 4:
        worldtime = 1;
        break;
    default:
        worldtime = 0;
        break;
    }
    correctTime_ = status::g_StageAttribute.getMapCorrectIndex();
    if (correctTime_ >= 0) {
        correctTime_ += worldtime;
    } else if (status::g_StageAttribute.isTimeZoneEnable()) {
        correctTime_ = worldtime;
    } else {
        correctTime_ = 0;
    }
    setFloorfog(correctTime_);
    setTimezone(correctTime_);
    setBackcolor(correctTime_);
    if (data_020f3f58 == 0) {
        TownStageManager::getSingleton()->SetRGBRate(rate_, 0);
    }
}

void twn::TownStageTinction::setFloorfog(int index)
{
    if (dq5::level::ColorCorrect::getRecord(index)->getFog()) {
        unkfunc_02046bc4(true);
        dq5::level::FloorFog* fog = dq5::level::FloorFog::getRecord(dq5::level::ColorCorrect::getRecord(index)->getFog());
        unkfunc_02046ba8(fog->colorR00, fog->colorG00, fog->colorB00);
        unkfunc_02046ba8(fog->colorR01, fog->colorG01, fog->colorB01);
        unkfunc_02046b34(0, dss::Fix32(fog->rate00));
        unkfunc_02046b34(1, dss::Fix32(fog->rate01));
        unkfunc_02046b28(0, fog->offset00);
        unkfunc_02046b28(1, fog->offset01);
    } else {
        unkfunc_02046bc4(false);
    }
}

void twn::TownStageTinction::setTimezone(int index)
{
    dq5::level::CLUTCode* pCLUT = dq5::level::CLUTCode::getRecord(dq5::level::ColorCorrect::getRecord(index)->getClut());
    rate_.vx.value = pCLUT->getColorR();
    rate_.vy.value = pCLUT->getColorG();
    rate_.vz.value = pCLUT->getColorB();
}

dss::Fix32Vector3 twn::TownStageTinction::getDefaultPaletteRate()
{
    dss::Fix32Vector3 rate;
    dq5::level::CLUTCode* pCLUT = dq5::level::CLUTCode::getRecord(dq5::level::ColorCorrect::getRecord(correctTime_)->getClut());
    rate.vx.value = pCLUT->getColorR();
    rate.vy.value = pCLUT->getColorG();
    rate.vz.value = pCLUT->getColorB();
    return rate;
}

void twn::TownStageTinction::setBackcolor(int index)
{
    unsigned char color5[3];
    unsigned char color6[3];
    unsigned char color7[3];
    unsigned char color8[3];
    unsigned char color1[3];
    unsigned char color2[3];
    unsigned char color3[3];
    unsigned char color4[3];
    unsigned char* p = (unsigned char*)dq5::level::FloorBackColor::getRecord(dq5::level::ColorCorrect::getRecord(index)->getBackcolor());
    color1[0] = p[0];
    color1[1] = p[1];
    color1[2] = p[2];
    color2[0] = p[3];
    color2[1] = p[4];
    color2[2] = p[5];
    color3[0] = p[6];
    color3[1] = p[7];
    color3[2] = p[8];
    color4[0] = p[9];
    color4[1] = p[10];
    color4[2] = p[11];
    color5[0] = p[12];
    color5[1] = p[13];
    color5[2] = p[14];
    color6[0] = p[15];
    color6[1] = p[16];
    color6[2] = p[17];
    color7[0] = p[18];
    color7[1] = p[19];
    color7[2] = p[20];
    color8[0] = p[21];
    color8[1] = p[22];
    color8[2] = p[23];
    unkfunc_02048640(color5, color6, color7, color8, color1, color2, color3, color4);
}

void twn::TownStageTinction::setRGBRate(dss::Fix32Vector3& rate, int realTime)
{
    rate_ = rate;
    TownStageManager::getSingleton()->SetRGBRate(rate, realTime);
}

int twn::TownStageTinction::getCurrentBackColor()
{
    return dq5::level::ColorCorrect::getRecord(correctTime_)->getBackcolor();
}
