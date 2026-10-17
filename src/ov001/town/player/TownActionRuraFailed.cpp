#include "ov001/town/player/TownActionRuraFailed.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownWindowSystem.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/MenuStatus.hpp"
#include "main/text/TextAPI.hpp"

#pragma thumb on

inline short status::MenuStatus::getActorIndex()
{
    return actorIndex_;
}

inline void status::MenuStatus::setActorIndex(short actor)
{
    actorIndex_ = actor;
}

inline void twn::TownPlayerManager::setShadowExec(bool flag)
{
    shadowSet_ = flag;
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

int twn::TownActionRuraFailed::setup()
{
    return -1;
}

void twn::TownActionRuraFailed::execute()
{
    position_ = tempPos_;
    switch (mode_) {
    case FAILED_RURA_UP1:
    case FAILED_RURA_UP2:
    case FAILED_RURA_DOWN1:
    case FAILED_RURA_DOWN2:
        cmn::gMoveToTarget.execute();
        break;
    case FAILED_RURA_TOP:
        counter_++;
        break;
    }
}

int twn::TownActionRuraFailed::update()
{
    static const dss::Fix32 dy((fx32)0x3000);
    dss::Fix32Vector3 pos;
    if (cmn::gMoveToTarget.update() != -1) {
        switch (mode_) {
        case FAILED_RURA_UP1:
            mode_ = FAILED_RURA_UP2;
            pos = tempPos_;
            pos.vy += dy;
            cmn::gMoveToTarget.setAction(tempPos_, pos, TownPlayerAction::ruraSpeed, 0, 0, 0xb);
            break;
        case FAILED_RURA_UP2:
            TownCamera::getSingleton()->setShake(2, 6);
            TownPlayerManager::getSingleton().setMoveToFirstFlag();
            counter_ = 0;
            mode_ = FAILED_RURA_TOP;
            SoundManager::stopSeWithIndex(0x23b, 0);
            SoundManager::playSe(0x14c, 0);
            break;
        case FAILED_RURA_TOP:
            if (counter_ > 0x3c) {
                mode_ = FAILED_RURA_DOWN1;
                pos = startPos_;
                pos.vy.value += 0x1000;
                cmn::gMoveToTarget.setAction(tempPos_, pos, TownPlayerAction::walkSpeed, 0, 0, 0xb);
            }
            break;
        case FAILED_RURA_DOWN1:
            switch (prevAction_) {
            case 8:
                cmn::gMoveToTarget.setAction(tempPos_, startPos_, TownPlayerAction::walkSpeed, 1, 2, 0xb);
                break;
            case 9:
                cmn::gMoveToTarget.setAction(tempPos_, startPos_, TownPlayerAction::walkSpeed, 1, 1, 0xb);
                break;
            default:
                cmn::gMoveToTarget.setAction(tempPos_, startPos_, TownPlayerAction::walkSpeed, 1, 0, 0xb);
                break;
            }
            mode_ = FAILED_RURA_DOWN2;
            break;
        case FAILED_RURA_DOWN2:
            TextAPI::setMACRO0(1, 0x50000000, status::g_Menu.getActorIndex());
            status::g_Menu.setActorIndex(0);
            TownWindowSystem::getSingleton().openSystemMessage();
            TownWindowSystem::getSingleton().addCommonMessage(0xc40f2);
            TownPlayerManager::getSingleton().setRemote(false);
            TownPlayerManager::getSingleton().setShadowExec(false);
            TownCamera::getSingleton()->setCameraLock(false);
            TownPlayerManager::getSingleton().setEffectPosFlag(false);
            return prevAction_;
        }
    }
    dirIdx_ = prev_dirIdx_;
    TownPlayerManager::getSingleton().setEffectPos(position_);
    tempPos_ = position_;
    position_ = startPos_;
    return -1;
}

int twn::TownActionRuraFailed::startCheck()
{
    prev_dirIdx_ = dirIdx_;
    dss::Fix32Vector3 target = position_;
    startPos_ = position_;
    tempPos_ = position_;
    target.vy.value += 0x1000;
    cmn::gMoveToTarget.setAction(position_, target, TownPlayerAction::ruraSpeed, 0, 0, 0xb);
    TownCamera::getSingleton()->setCameraLock(true);
    TownPlayerManager::getSingleton().setShadowExec(true);
    if (cmn::g_cmnPartyInfo.getRideOn() == cmn::RIDE_ON_SHIP_IKADA) {
        TownPlayerManager::getSingleton().setPartyToFirst(position_);
    }
    dirIdx_ = prev_dirIdx_;
    mode_ = FAILED_RURA_UP1;
    prevAction_ = TownPlayerManager::getSingleton().player_.actionType_;
    SoundManager::playSe(0x23b, 0);
    TownPlayerManager::getSingleton().setEffectPos(position_);
    TownPlayerManager::getSingleton().setEffectPosFlag(true);
    return 0xc;
}
