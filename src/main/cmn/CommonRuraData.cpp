#pragma ipa file
#include "main/cmn/CommonRuraData.hpp"
#include "main/status/GameFlag.hpp"
#include "main/leveldata/VehicleData.hpp"

inline dq5::level::VehicleData* dq5::level::VehicleData::getRecord(int index)
{
    return (VehicleData*)binary_.getRecord(index, addr_, filename_, loadSwitch_);
}

THUMB cmn::CommonRuraData& cmn::CommonRuraData::getSingleton()
{
    static CommonRuraData commonRuraData;
    return commonRuraData;
}

THUMB cmn::CommonRuraData::CommonRuraData()
{
}

THUMB cmn::CommonRuraData::~CommonRuraData()
{
}

THUMB void cmn::CommonRuraData::initialize()
{
}

THUMB void cmn::CommonRuraData::terminate()
{
}

THUMB bool cmn::CommonRuraData::isEnableRura(int index)
{
    if (g_AreaFlag.check(200)) {
        return g_AreaFlag.check(index);
    }
    return false;
}

THUMB int cmn::CommonRuraData::getRuraCount()
{
    int count = 0;
    for (int i = 1; i < maxRuraFlag; i++) {
        if (g_AreaFlag.check(i)) {
            count++;
        }
    }
    return count;
}

// getShipTownPos and getPlayerTownPos are not called: the linker drops them, but the guard of
// getPlayerTownPos's local static stays in this unit's .bss.
THUMB dss::Fix32Vector3 cmn::CommonRuraData::getShipTownPos(int index)
{
    dss::Fix32Vector3 pos;
    pos.vx.value = dq5::level::VehicleData::getRecord(index)->getShipX();
    pos.vy.value = dq5::level::VehicleData::getRecord(index)->getShipY();
    return pos;
}

THUMB dss::Fix32Vector3 cmn::CommonRuraData::getPlayerTownPos(int index)
{
    static const dss::Fix32 dy((fx32)0x6000);
    dss::Fix32Vector3 pos = getShipTownPos(index);
    pos.vy += dy;
    return pos;
}
