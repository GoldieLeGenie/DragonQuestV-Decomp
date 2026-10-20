#include "ov001/town/player/TownActionRura.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/riseup/TownRiseupManager.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/StageInfo.hpp"

#pragma thumb on

inline void twn::TownStageManager::computeCollFloor(dss::Fix32Vector3& pos, dss::Fix32 rad, dss::Fix32Vector3 fixPos)
{
    coll_.computeCollFloor(pos, rad, fixPos);
}

inline void twn::TownPlayerManager::setShadowExec(bool flag)
{
    shadowSet_ = flag;
}

inline void twn::TownPlayerManager::setExitSE(bool flag)
{
    mapChangeSE_ = flag;
}

inline void twn::TownPlayerManager::setEffectPosFlag(bool flag)
{
    effectPosFlag_ = flag;
}

inline void twn::TownPlayerManager::setEffectPos(dss::Fix32Vector3& pos)
{
    effectPos_ = pos;
}

inline cmn::PARTY_RIDE_ON_TYPE cmn::CommonPartyInfo::getRideOn()
{
    return rideOnType_;
}

inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type)
{
    rideOnType_ = type;
}

inline void status::StageInfo::setIdoLinkInFlag(bool flag)
{
    idoLinkInFlag_ = flag;
    idoLinkOutFlag_ = false;
}

inline void TownCamera::setEndCameraReset(bool flag)
{
    endCameraReset_ = flag;
}

int twn::TownActionRura::setup()
{
    counter_ = 0;
    return -1;
}

void twn::TownActionRura::execute()
{
    position_ = tempPos_;
    short prev_dirIdx_ = dirIdx_;
    cmn::gMoveToTarget.execute();
    dss::Fix32Vector3 temp = position_;
    dirIdx_ = prev_dirIdx_;
    TownStageManager::getSingleton()->computeCollFloor(temp, TownPlayerAction::collR, temp);
    TownPlayerManager::getSingleton().setEffectPos(position_);
    tempPos_ = position_;
    position_ = startPos_;
    if (counter_ == 0) {
        if (data_020f4f74.texVramFree_ >= 0x1000) {
            sprite_ = true;
        } else {
            sprite_ = false;
        }
    }
    if (counter_ % 12 == 0 && sprite_) {
        TownRiseupManager::getSingleton().setupSprite(RULA_EFFECT, tempPos_, false, 0);
    }
    counter_++;
}

int twn::TownActionRura::update()
{
    if (cmn::gMoveToTarget.update() != -1) {
        int townId = status::g_StageInfo.getRuraTownID();
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RURA_AFTER);
        cmn::g_extraMapLink.setRuraLink();
        TownPlayerManager::getSingleton().setLock(true);
        status::g_StageInfo.setIdoLinkInFlag(false);
        cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_NONE);
        TownCamera::getSingleton()->setEndCameraReset(true);
    }
    return -1;
}

int twn::TownActionRura::startCheck()
{
    static const dss::Fix32 dy((fx32)0x14000);
    short prev_dirIdx = dirIdx_;
    dss::Fix32Vector3 target = position_;
    startPos_ = position_;
    tempPos_ = position_;
    target.vy += dy;
    cmn::gMoveToTarget.setAction(position_, target, TownPlayerAction::ruraSpeed, 0, 0, 0xb);
    status::g_StageInfo.setRuraFlag(2);
    TownCamera::getSingleton()->setCameraLock(true);
    TownPlayerManager::getSingleton().setRemote(true);
    TownPlayerManager::getSingleton().resetDrawPartyCount();
    TownPlayerManager::getSingleton().setShadowExec(true);
    if (cmn::g_cmnPartyInfo.getRideOn() == cmn::RIDE_ON_SHIP_IKADA) {
        TownPlayerManager::getSingleton().setPartyToFirst(position_);
    }
    dirIdx_ = prev_dirIdx;
    TownPlayerManager::getSingleton().setExitSE(false);
    SoundManager::playSe(0x23b, 0);
    TownPlayerManager::getSingleton().setEffectPos(position_);
    TownPlayerManager::getSingleton().setEffectPosFlag(true);
    return 0xb;
}
