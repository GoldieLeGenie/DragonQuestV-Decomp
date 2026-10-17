#include "main/cmn/WorldLocation.hpp"
#include "main/global/Global.hpp"
#include "main/leveldata/CLUTCode.hpp"
#include "main/leveldata/TimeZone.hpp"
#include "main/status/StageInfo.hpp"
#include "ov005/fld/FieldStage.hpp"

inline dq5::level::CLUTCode* dq5::level::CLUTCode::getRecord(int index)
{
    return (CLUTCode*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline dq5::level::TimeZone* dq5::level::TimeZone::getRecord(int index)
{
    return (TimeZone*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

inline unsigned short CWorldMap::getWorldEdgeX()
{
    return m_syn->mapx * m_syn->wldx;
}

inline unsigned short CWorldMap::getWorldEdgeY()
{
    return m_syn->mapy * m_syn->wldy;
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

inline unsigned int dq5::level::TimeZone::getArraySize()
{
    return binary_.record_;
}

inline unsigned short dq5::level::TimeZone::getFrame()
{
    return frame;
}

inline char dq5::level::TimeZone::getScript()
{
    return byte_1 & 3;
}

inline char dq5::level::TimeZone::getZone()
{
    return (byte_1 & 0x1c) >> 2;
}

inline char dq5::level::TimeZone::getPrevPalette()
{
    return byte_2 & 0xf;
}

inline char dq5::level::TimeZone::getNextPalette()
{
    return (byte_2 & 0xf0) >> 4;
}

inline void status::StageInfo::setCurrentTimeZone(TIME_ZONE time)
{
    timeZone_ = time;
}

THUMB void cmn::WorldLocation::calcWorldPos(fx32& x, fx32& y)
{
    int xMax = fld::FieldStage::getSingleton()->getFieldData().worldData_.getWorldEdgeX() << 16;
    int yMax = fld::FieldStage::getSingleton()->getFieldData().worldData_.getWorldEdgeY() << 16;
    if (x < 0) {
        x = x + xMax;
    } else if (x >= xMax) {
        x = x - xMax;
    }
    if (y < 0) {
        y = y + yMax;
    } else if (y >= yMax) {
        y = y - yMax;
    }
}

THUMB dss::Fix32Vector3 cmn::WorldLocation::calcPaletteRate(int prev, int next, dss::Fix32 ratio)
{
    dss::Fix32Vector3 prevRate;
    dss::Fix32Vector3 nextRate;
    dss::Fix32Vector3 rate;
    dss::Fix32 one;
    one.value = 0x1000;

    dq5::level::CLUTCode* pCLUT = dq5::level::CLUTCode::getRecord(prev);
    prevRate.vx.value = pCLUT->getColorR();
    prevRate.vy.value = pCLUT->getColorG();
    prevRate.vz.value = pCLUT->getColorB();

    pCLUT = dq5::level::CLUTCode::getRecord(next);
    nextRate.vx.value = pCLUT->getColorR();
    nextRate.vy.value = pCLUT->getColorG();
    nextRate.vz.value = pCLUT->getColorB();

    rate = prevRate * (one - ratio) + nextRate * ratio;
    return rate;
}

THUMB dss::Fix32Vector3 cmn::WorldLocation::calcPaletteRate(int wtime)
{
    dss::Fix32 ratio;
    int nextID;
    int prevID;

    for (unsigned int i = 0; i < dq5::level::TimeZone::getArraySize(); i++) {
        if (wtime <= dq5::level::TimeZone::getRecord(i)->getFrame()) {
            int rateTime = 0;
            if (i != 0) {
                rateTime = dq5::level::TimeZone::getRecord(i - 1)->getFrame();
            }
            ratio.value = ((wtime - rateTime) << 12) / 60;
            prevID = dq5::level::TimeZone::getRecord(i)->getPrevPalette();
            nextID = dq5::level::TimeZone::getRecord(i)->getNextPalette();
            break;
        }
    }
    return calcPaletteRate(prevID, nextID, ratio);
}

THUMB dss::Fix32Vector3 cmn::WorldLocation::calcDarkPaletteRate()
{
    return calcPaletteRate(1, 0xf, dss::Fix32((fx32)0x1000));
}

THUMB void cmn::WorldLocation::setCurrentTimeZone()
{
    int wt = status::g_StageInfo.getWorldTime();
    for (unsigned int i = 0; i < dq5::level::TimeZone::getArraySize(); i++) {
        if (wt <= dq5::level::TimeZone::getRecord(i)->getFrame()) {
            status::g_StageInfo.setCurrentTimeZone((TIME_ZONE)dq5::level::TimeZone::getRecord(i)->getZone());
            break;
        }
    }
    status::g_StageInfo.setWorldTime(wt);
}

THUMB TIME_ZONE cmn::WorldLocation::getCurrentTimeZone()
{
    int wt = status::g_StageInfo.getWorldTime();
    for (unsigned int i = 0; i < dq5::level::TimeZone::getArraySize(); i++) {
        if (wt <= dq5::level::TimeZone::getRecord(i)->getFrame()) {
            return (TIME_ZONE)dq5::level::TimeZone::getRecord(i)->getZone();
        }
    }
    return TIME_ZONE_MORNING;
}

THUMB dq5::DAY_NIGHT cmn::WorldLocation::getCurrentDayNight()
{
    int wt = status::g_StageInfo.getWorldTime();
    for (unsigned int i = 0; i < dq5::level::TimeZone::getArraySize(); i++) {
        if (wt <= dq5::level::TimeZone::getRecord(i)->getFrame()) {
            return (dq5::DAY_NIGHT)dq5::level::TimeZone::getRecord(i)->getScript();
        }
    }
    return dq5::DAY_NIGHT_NONE;
}

THUMB int cmn::WorldLocation::getMorning()
{
    return 0;
}

THUMB int cmn::WorldLocation::getDaytime()
{
    return dq5::level::TimeZone::getRecord(1)->getFrame() + 1;
}

THUMB int cmn::WorldLocation::getEvening()
{
    return dq5::level::TimeZone::getRecord(3)->getFrame() + 1;
}

THUMB int cmn::WorldLocation::getNight()
{
    return dq5::level::TimeZone::getRecord(5)->getFrame() + 1;
}

THUMB int cmn::WorldLocation::getMaxTime()
{
    return dq5::level::TimeZone::getRecord(7)->getFrame() + 1;
}

THUMB bool cmn::WorldLocation::isVehicleExist(int vehicle)
{
    return g_Global.getFieldType() == 0;
}
