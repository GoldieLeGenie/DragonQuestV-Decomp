#pragma ipa file
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownDamageFloor.hpp"
#include "ov001/town/TownSystem.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/global/Global.hpp"
#include "main/status/PartyStatus.hpp"
#include "main/status/StageInfo.hpp"

// The original TU also emitted cmn::ActionBase's weak vtable (it is created last in the data layout).
// Our headers keep it external, so this dead-stripped stand-in recreates a vtable of the same size.
struct ActionBaseWeakVtable : cmn::ActionBase {
    virtual int setup();
    virtual void execute();
    virtual int update();
};

inline int ActionBaseWeakVtable::setup()
{
    return -1;
}

inline void ActionBaseWeakVtable::execute()
{
}

inline int ActionBaseWeakVtable::update()
{
    return -1;
}

inline int Global::getMapNameId()
{
    return nextMapNameId;
}

inline int status::PartyStatusUtility::isSeparate()
{
    return separateFlag_;
}

inline void twn::TownCommandInitWait::setWait(bool flag)
{
    flag_ = flag;
}

inline void twn::TownSystemCommand::setWait(bool flag)
{
    townCommandInitWait_.setWait(flag);
}

inline void twn::TownSystem::setWait(bool flag)
{
    townSystemCommand_.setWait(flag);
}

const dss::Fix32 twn::TownPlayerAction::collR(0x59a);
const dss::Fix32 twn::TownPlayerAction::collRR(collR * collR);
const dss::Fix32 twn::TownPlayerAction::coll2RR(collR * collR * 4);
const dss::Fix32 twn::TownPlayerAction::walkSpeed(0x19a);
const dss::Fix32 twn::TownPlayerAction::surfaceR(0x666);
const dss::Fix32 twn::TownPlayerAction::rageSurfaceR(0x1800);
const dss::Fix32 twn::TownPlayerAction::objectR(0x59a);
const dss::Fix32 twn::TownPlayerAction::fixR(0x571);
const dss::Fix32 twn::TownPlayerAction::ropeSpeed(0x19a);
const dss::Fix32 twn::TownPlayerAction::fallH(0x1000);
const dss::Fix32 twn::TownPlayerAction::bumpH(0x800);
const dss::Fix32 twn::TownPlayerAction::kaidanR(0x99a);
const dss::Fix32 twn::TownPlayerAction::shipR(0x159a);
const dss::Fix32 twn::TownPlayerAction::shipCollR(0x1400);
const dss::Fix32 twn::TownPlayerAction::getDownL(0x785);
const dss::Fix32 twn::TownPlayerAction::shipSpeed(0x171);
const dss::Fix32 twn::TownPlayerAction::ikadaR(0x948);
const dss::Fix32 twn::TownPlayerAction::getOnOffSpeed(0x11f);
const dss::Fix32 twn::TownPlayerAction::shipCtrLen(0x1ccd);
const dss::Fix32 twn::TownPlayerAction::walkCtrLen(0x199a);
const dss::Fix32 twn::TownPlayerAction::ruraSpeed(0x333);
const dss::Fix32 twn::TownPlayerAction::talkR(0x1000);
const dss::Fix32 twn::TownPlayerAction::talkRR(0x1000);
const dss::Fix32 twn::TownPlayerAction::townCharaR(0x666);
const dss::Fix32 twn::TownPlayerAction::townCharaPreR(0x800);
const dss::Fix32 twn::TownPlayerAction::changePreR(0x948);

THUMB twn::TownPlayerAction::TownPlayerAction()
{
}

THUMB twn::TownPlayerAction::~TownPlayerAction()
{
}

THUMB void twn::TownPlayerAction::setup()
{
    int ret;
    allShadowReset_ = 1;
    for (int i = 0; i < 21; i++) {
        action_[i] = 0;
    }
    action_[ACTION_TYPE_WALK] = &townActionWalk_;
    action_[ACTION_TYPE_KAIDAN] = &townActionKaidan_;
    action_[ACTION_TYPE_FALL] = &townActionFall_;
    action_[ACTION_TYPE_SUBE] = &townActionSube_;
    action_[ACTION_TYPE_ROPE] = &townActionRope_;
    action_[ACTION_TYPE_SHIP] = &townActionShip_;
    action_[ACTION_TYPE_IKADA] = &townActionIkada_;
    action_[ACTION_TYPE_DOOR] = &townActionDoor_;
    action_[ACTION_TYPE_RURA] = &townActionRura_;
    action_[ACTION_TYPE_RURA_FAILED] = &townActionRuraFailed_;
    action_[ACTION_TYPE_ICE] = &townActionIce_;
    action_[ACTION_TYPE_RIREMITO] = &townActionRiremito_;
    action_[ACTION_TYPE_RANARUTA] = &townActionRanaruta_;
    action_[ACTION_TYPE_TABI] = &townActionTabi_;
    action_[ACTION_TYPE_KAIFUKU] = &townActionKaifuku_;
    action_[ACTION_TYPE_TRUCK] = &townActionTruck_;
    action_[ACTION_TYPE_GIMMICK] = &townActionGimmick_;
    actionType_ = ACTION_TYPE_WALK;
    if (status::g_StageInfo.idoLinkOutFlag_ == 1 && status::g_StageInfo.idoLinkInFlag_ == 1) {
        cmn::g_cmnPartyInfo.position_ = status::g_StageInfo.idoLinkPos_;
        cmn::g_cmnPartyInfo.setDirIdx(status::g_StageInfo.idoLinkDirIdx_);
        status::g_StageInfo.idoLinkOutFlag_ = 0;
        status::g_StageInfo.idoLinkInFlag_ = 0;
    }
    ret = action_[ACTION_TYPE_FALL]->setup();
    if (ret != -1) {
        actionType_ = (TOWN_PLAYER_ACTION_TYPE)ret;
    }
    ret = action_[ACTION_TYPE_ROPE]->setup();
    if (ret != -1) {
        actionType_ = (TOWN_PLAYER_ACTION_TYPE)ret;
    }
    if (cmn::g_cmnPartyInfo.menuAction_ == cmn::MENU_SORATOBU_END) {
        dss::Fix32Vector3 pos;
        if (g_Global.getMapNameId() == 0x4b) {
            pos.vx.value = -0x3000;
            pos.vy.value = 0x2800;
            pos.vz.value = 0x7000;
        } else {
            pos.vx.value = 0;
            pos.vy.value = dss::Fix32Vector3(cmn::g_cmnPartyInfo.startPos_).vy.value;
            pos.vz.value = 0x7000;
        }
        TownCamera::getSingleton()->camera_.m_camera0.setTarget(pos);
        pos.vy.value = 0x5000;
        cmn::g_cmnPartyInfo.startPos_ = pos;
        cmn::g_cmnPartyInfo.setDirIdx(0);
        TownCamera::getSingleton()->setCameraLock(true);
        TownPlayerManager::getSingleton().setRemote(true);
        townActionFall_.setCollFall();
        townActionFall_.count_ = 3;
        townActionFall_.sePlay_ = false;
        cmn::g_cmnPartyInfo.setMenuAction(cmn::MENU_ACTION_NONE);
        actionType_ = ACTION_TYPE_FALL;
    }
    if (status::g_StageInfo.encount_ == 0) {
        cmn::g_cmnPartyInfo.setStartPosition();
        TownDamageFloor::getSingleton().setup();
    }
    for (int i = 0; i < 21; i++) {
        if (i != ACTION_TYPE_FALL && i != ACTION_TYPE_ROPE && action_[i]) {
            ret = action_[i]->setup();
            if (ret != -1) {
                actionType_ = (TOWN_PLAYER_ACTION_TYPE)ret;
            }
        }
    }
    switch (actionType_) {
    case ACTION_TYPE_SHIP:
        TownPlayerManager::getSingleton().setDrawPartyNone();
        TownSystem::getSingleton().setWait(false);
        break;
    case ACTION_TYPE_IKADA:
        TownPlayerManager::getSingleton().setPartyDrawOne();
        break;
    case ACTION_TYPE_TRUCK:
        TownSystem::getSingleton().setWait(false);
        TownPlayerManager::getSingleton().setPartyDrawOne();
        break;
    default:
        if (status::g_StageInfo.encount_ == 0 && cmn::g_cmnPartyInfo.prevLocation_ == 0 && status::PartyStatusUtility::isSeparate() == false) {
            TownPlayerManager::getSingleton().setStartEraseParty();
        }
        break;
    }
    if (status::g_StageInfo.ruraFlag_) {
        townActionFall_.sePlay_ = false;
    }
    status::g_StageInfo.setRuraFlag(0);
    prevType_ = actionType_;
}

THUMB void twn::TownPlayerAction::cleanup()
{
    for (int i = 0; i < 21; i++) {
        if (action_[i]) {
            action_[i]->terminate();
        }
    }
}

THUMB void twn::TownPlayerAction::execute()
{
    action_[actionType_]->execute();
}

THUMB void twn::TownPlayerAction::update()
{
    prevType_ = actionType_;
    int type = action_[actionType_]->update();
    if (type != -1) {
        actionType_ = (TOWN_PLAYER_ACTION_TYPE)type;
    }
}

THUMB void twn::TownPlayerAction::execCollision()
{
}

THUMB void twn::TownPlayerAction::execMove()
{
}

void TownPlayerAction_weakVtable()
{
    ActionBaseWeakVtable unused;
}
