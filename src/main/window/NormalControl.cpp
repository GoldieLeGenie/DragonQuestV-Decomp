#pragma ipa file
#include "main/window/NormalControl.hpp"
#include "main/dss/Pad.hpp"
#include "main/global/Global.hpp"
#include "main/global/UnkGlobalSystem.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"

inline int window::NormalControl::getPhase()
{
    return PHASE_NORMAL;
}

inline window::NormalControl::~NormalControl()
{
}

THUMB inline bool TownCamera::isLimitRotate()
{
    int ret = limitL == dss::Fix32(-1L) && limitR == dss::Fix32(-1L);
    return ret;
}

window::NormalControl window::gNormalControl;

THUMB void window::NormalControl::setup()
{
    state_ = CONTROL_NORMAL;
}

THUMB void window::NormalControl::execute()
{
    if (g_Global.partChangeFlag_ == 0) {
        if (isPlayerLock()) {
            if (data_02101c88.isCurrentPart(6)) {
                fld::FieldPlayerManager::getSingleton().inputClear();
            } else {
                twn::TownPlayerManager::getSingleton().inputClear();
            }
        } else {
            checkCamera();
            executePlayer();
        }
    }
}

THUMB void window::NormalControl::executePlayer()
{
    if (data_02101c88.isCurrentPart(6)) {
        fld::FieldPlayerManager::getSingleton().inputClear();
        if (dss::g_Pad.pad() & 0xf0) {
            fld::FieldPlayerManager::getSingleton().inputPad(dss::g_Pad.padDir());
        }
    }
    if (data_02101c88.isCurrentPart(4)) {
        twn::TownPlayerManager::getSingleton().inputClear();
        if (dss::g_Pad.pad() & 0xf0) {
            twn::TownPlayerManager::getSingleton().inputPad(dss::g_Pad.padDir());
        }
    }
}

THUMB void window::NormalControl::checkCamera()
{
    if (data_02101c88.isCurrentPart(4)) {
        switch ((dss::g_Pad.pad() & 0x100) | (dss::g_Pad.pad() & 0x200)) {
            case 0x300:
                if (TownCamera::getSingleton()->isLimitRotate() != true) {
                    twn::TownPlayerManager::getSingleton().setCameraRotToNorth();
                }
                break;
            case 0x100:
                if (TownCamera::getSingleton()->isLimitRotate() != true) {
                    twn::TownPlayerManager::getSingleton().setCameraRotType(1);
                }
                break;
            case 0x200:
                if (TownCamera::getSingleton()->isLimitRotate() != true) {
                    twn::TownPlayerManager::getSingleton().setCameraRotType(2);
                }
                break;
            default:
                twn::TownPlayerManager::getSingleton().setCameraRotType(0);
                break;
        }
    }
}
