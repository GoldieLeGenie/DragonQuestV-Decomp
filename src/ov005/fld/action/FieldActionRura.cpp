#include "ov005/fld/FieldAction.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/global/StageLink.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/StageAttribute.hpp"
#include "ov005/fld/FieldEffect.hpp"
#include "ov005/fld/FieldPlayerManager.hpp"
#include "ov005/fld/FieldSystem.hpp"

inline int cmn::CommonActionMoveToTarget::getNextAction()
{
    return nextAction_;
}

inline void fld::FieldPartyDraw::setShadowFlag(int index, int flag)
{
    partyCharacter_[index].setShadowFlag(flag);
}

inline cmn::PARTY_RIDE_ON_TYPE cmn::CommonPartyInfo::getRideOn()
{
    return rideOnType_;
}

inline void cmn::CommonPartyInfo::setRideOn(PARTY_RIDE_ON_TYPE type)
{
    rideOnType_ = type;
}

inline void fld::FieldPlayerManager::setLink(bool flag)
{
    flagMapLink_ = flag;
}

inline void fld::FieldPlayerManager::setDummyPos(dss::Fix32Vector3& pos)
{
    dummyPos_ = pos;
}

inline void fld::FieldPlayerManager::setDummyPosFlag(bool flag)
{
    dummyPosFlag_ = flag;
}

inline void fld::FieldPlayerManager::setMoveType(int type)
{
    player_.setMoveType(type);
}

inline void fld::FieldSystem::setLockCameraFlag(bool flag)
{
    cameraLock_ = flag;
}

THUMB int fld::FieldActionRura::setup()
{
    effectIndex_ = -1;
    effectPos_.set(0, 0, 0);
    count_ = 0;
    return -1;
}

THUMB void fld::FieldActionRura::execute()
{
    cmn::gMoveToTarget.execute();
    switch (cmn::gMoveToTarget.getNextAction()) {
    case 1:
    case 2:
        if (position_ == cmn::gMoveToTarget.target_) {
            FieldPlayerManager::getSingleton().partyDraw_.setShadowFlag(0, true);
        }
        break;
    case 0:
        for (int i = 0; i < FieldPlayerManager::getSingleton().partyDraw_.countReal_; i++) {
            FieldParty& party = FieldPlayerManager::getSingleton().party_;
            if ((cmn::gMoveToTarget.moveVec_ * 2).lengthsq() > (cmn::gMoveToTarget.startPos_ - party.getMemberPos(i)).lengthsq()) {
                FieldPlayerManager::getSingleton().partyDraw_.setShadowFlag(i, false);
            }
        }
        break;
    }
    if (cmn::gMoveToTarget.getNextAction() == 0) {
        if (effectPos_.vy.value == 0) {
            if (data_020f4f74.texVramFree_ >= 0x1000) {
                sprite_ = true;
            } else {
                sprite_ = false;
            }
        }
        if (cmn::g_cmnPartyInfo.getRideOn() != cmn::RIDE_ON_SHIP_IKADA && sprite_) {
            if (effectPos_.vy.value % 0x18000 == 0) {
                FieldEffectManager::getSingleton().setup(RULA_EFFECT, effectPos_);
            }
            effectPos_.vy.value -= 0x2000;
        }
    }
}

THUMB int fld::FieldActionRura::update()
{
    int state = cmn::gMoveToTarget.update();
    FieldPlayerManager::getSingleton().setLink(true);
    switch (state) {
    case 1:
        if (count_ == 10) {
            FieldPlayerManager::getSingleton().party_.setBashaArray(status::g_StageAttribute.isCarriageEnable());
            FieldPlayerManager::getSingleton().party_.setAllMemberPos(cmn::g_cmnPartyInfo.position_, cmn::g_cmnPartyInfo.dirIdx_);
            FieldPlayerManager::getSingleton().setAllShadow(true);
            FieldPlayerManager::getSingleton().setRemote(false);
            FieldSystem::getSingleton()->setLockCameraFlag(false);
            FieldPlayerManager::getSingleton().setLink(true);
            FieldPlayerManager::getSingleton().setDummyPosFlag(false);
            return 0;
        }
        count_++;
        break;
    case 0:
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_RURA_AFTER);
        cmn::g_extraMapLink.setRuraLink();
        cmn::g_cmnPartyInfo.setRideOn(cmn::RIDE_ON_NONE);
        FieldPlayerManager::getSingleton().setRemote(false);
        break;
    case 2:
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_SORATOBU_END);
        FieldPlayerManager::getSingleton().setRemote(false);
        FieldPlayerManager::getSingleton().setLink(false);
        break;
    }
    return -1;
}

THUMB int fld::FieldActionRura::start(int type)
{
    const dss::Fix32 ruraFixY = 0x64000;
    const dss::Fix32 ruraUpFixY = 0xc8000;
    const dss::Fix32 ruraPosFixY = 0x7000;
    const dss::Fix32 fallSpeed = 0x3000;
    const dss::Fix32 fieldRuraSpeed = 0x4000;
    static const dss::Fix32 unk_ruraSpeed = 0x3c000;
    dss::Fix32Vector3 target;
    switch (type) {
    case RURA_UP:
        target = position_;
        target.vy -= ruraUpFixY;
        cmn::gMoveToTarget.setAction(position_, target, fieldRuraSpeed, 1, 0, 0);
        FieldSystem::getSingleton()->setLookAtPos(position_);
        FieldPlayerManager::getSingleton().party_.LRreset_ = true;
        FieldPlayerManager::getSingleton().setDummyPos(position_);
        SoundManager::playSe(0x23b, 0);
        break;
    case RURA_DOWN:
        if ((util::StageLink::getFieldSymbolIndex() & 0xfff) != 0x5c) {
            position_.vy += ruraPosFixY;
        }
        target = position_;
        position_.vy -= ruraFixY;
        FieldPlayerManager::getSingleton().party_.setAllPlayerAtFirst();
        cmn::gMoveToTarget.setAction(position_, target, fallSpeed, 1, 0, 1);
        FieldSystem::getSingleton()->setLookAtPos(target);
        FieldPlayerManager::getSingleton().party_.setBashaArray(false);
        FieldPlayerManager::getSingleton().setDummyPos(target);
        FieldPlayerManager::getSingleton().setAllShadow(false);
        break;
    case SORATOBU:
        target = position_;
        position_.vy -= ruraFixY;
        FieldPlayerManager::getSingleton().party_.setAllPlayerAtFirst();
        cmn::gMoveToTarget.setAction(position_, target, fallSpeed, 0, 0, 2);
        FieldSystem::getSingleton()->setLookAtPos(target);
        FieldPlayerManager::getSingleton().party_.setBashaArray(false);
        FieldPlayerManager::getSingleton().setDummyPos(target);
        FieldPlayerManager::getSingleton().setAllShadow(false);
        SoundManager::playSe(0x23b, 0);
        break;
    }
    FieldPlayerManager::getSingleton().setDummyPosFlag(true);
    FieldSystem::getSingleton()->setLockCameraFlag(true);
    FieldPlayerManager::getSingleton().setRemote(true);
    FieldPlayerManager::getSingleton().setLink(true);
    FieldPlayerManager::getSingleton().setMoveType(FieldPlayer::MOVE_RURA);
    return -1;
}

THUMB bool fld::FieldActionRura::search()
{
    return false;
}
