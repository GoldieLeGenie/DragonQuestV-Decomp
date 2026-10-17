#pragma ipa file
#include "ov001/town/player/TownActionFall.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/TownSugorokuManager.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/cmn/ExtraMapLink.hpp"
#include "main/sound/SoundManager.hpp"
#include "main/status/StageInfo.hpp"
#include "main/town/TownSugorokuInfo.hpp"

#pragma thumb on

inline int FldCollision::getFloorPolygonNo()
{
    return floorPolygonNo_;
}

inline void FldCollision::clearSurfaceByType(int type)
{
    surfaceType_[type] = -1;
}

inline void FldCollision::setHitSurfaceByType(int type, int id)
{
    surfaceType_[type] = id;
}

inline int twn::TownStageManager::getFloorPolygonNo()
{
    return coll_.getFloorPolygonNo();
}

inline void twn::TownStageManager::clearHitSurfaceIdByType(int type)
{
    coll_.clearSurfaceByType(type);
}

inline void twn::TownStageManager::setHitSurfaceIdByType(int type, int id)
{
    coll_.setHitSurfaceByType(type, id);
}

inline void twn::TownStageManager::searchFloorSurface(dss::Fix32Vector3& oldPos, dss::Fix32 radius, dss::Fix32 judgeLen, dss::Fix32Vector3& retVec)
{
    coll_.searchFloorSurface(oldPos, radius, judgeLen, retVec);
}

inline void twn::TownPlayerManager::setShadowExec(bool flag)
{
    shadowSet_ = flag;
}

inline void twn::TownPlayerManager::setExitSE(bool flag)
{
    mapChangeSE_ = flag;
}

inline void twn::TownPlayerManager::setAnimation(int flag)
{
    partyDraw_.setAnimation(flag);
}

inline void cmn::CommonPartyInfo::setStartPos(dss::Fix32Vector3& pos)
{
    startPos_ = pos;
}

inline void twn::TownSugorokuInfo::decTimer()
{
    timeCount_--;
}

const dss::Fix32 twn::TownActionFall::fallStartFix((fx32)0x2000);
const dss::Fix32 twn::TownActionFall::fallSpeed((fx32)0x225);

int twn::TownActionFall::setup()
{
    int ret = -1;
    dss::Fix32 height;
    cmn::g_extraMapLink.checkExtraTownPos(position_, dirIdx_);
    dss::Fix32Vector3 startPos;
    startPos = position_;
    partyMove_ = 0;
    sePlay_ = 0;
    count_ = 0;
    if (status::g_StageInfo.getFallFlag() == true) {
        cameraPos_ = position_;
        cameraPos_ = TownStageManager::getSingleton()->compute(cameraPos_, cameraPos_, TownPlayerAction::collR, TownPlayerAction::collR, TownPlayerAction::townCharaPreR, height);
        cameraPos_.vy += height - TownPlayerAction::fixR;
        TownCamera::getSingleton()->camera_.unk_004.setTarget(cameraPos_);
        startPos.vy += fallStartFix;
        position_ = startPos;
        cmn::gMoveToTarget.setAction(startPos, cameraPos_, fallSpeed, 1, 0, 0);
        TownCamera::getSingleton()->setCameraLock(true);
        TownPlayerManager::getSingleton().setRemote(true);
        TownPlayerManager::getSingleton().setShadowExec(true);
        TownPlayerManager::getSingleton().setAnimation(0);
        sePlay_ = 1;
        fallType_ = 0;
        ret = 3;
    } else {
        startPos.vy += TownPlayerAction::collR;
        startPos = TownStageManager::getSingleton()->compute(startPos, startPos, TownPlayerAction::collR, TownPlayerAction::changePreR, TownPlayerAction::changePreR, height);
        if (height < TownPlayerAction::fallH * -3 && TownSugorokuManager::getSingleton().isSugorokuMode() == false && TownStageManager::getSingleton()->getFloorPolygonNo() != -1 && TownStageManager::getSingleton()->getHitSurfaceIdByType(6) == -1) {
            ret = -1;
        } else {
            startPos.vy += height - TownPlayerAction::collR;
            if (TownStageManager::getSingleton()->getHitSurfaceIdByType(6) == -1) {
                position_ = startPos;
            }
        }
    }
    cmn::g_cmnPartyInfo.setStartPos(startPos);
    status::g_StageInfo.setFallFlag(false);
    return ret;
}

void twn::TownActionFall::execute()
{
    moveMode_ = 1;
    dss::Fix32 height;
    dss::Fix32Vector3 temp;
    if (fallType_ == 0) {
        if (count_ > 8) {
            cmn::gMoveToTarget.execute();
        }
        count_++;
        temp = position_;
        temp.vy += TownPlayerAction::fixR;
        TownStageManager::getSingleton()->compute(temp, temp, TownPlayerAction::collR, TownPlayerAction::collR, TownPlayerAction::collR * 2, height);
        if (TownStageManager::getSingleton()->getHitSurfaceIdByType(11) != -1) {
            setCollFall();
            count_ = 5;
        }
    } else {
        count_++;
        if (count_ == 1) {
            setFixXZ();
        }
        if (count_ < 4) {
            position_ += vecXZ_;
            return;
        }
        if (count_ == 4) {
            if (sePlay_ == 1) {
                SoundManager::playSe(0x138, 0);
            }
            return;
        }
        temp = position_;
        temp.vy += TownPlayerAction::fixR;
        TownStageManager::getSingleton()->compute(temp, temp, TownPlayerAction::collR, TownPlayerAction::collR, TownPlayerAction::collR * 2, height);
        int surfaseId = TownStageManager::getSingleton()->getHitSurfaceIdByType(0);
        if (surfaseId == -1 || height < fallSpeed * -1) {
            position_.vy -= fallSpeed;
        } else {
            position_.vy += height;
            if (partyMove_ == 0) {
                TownPlayerManager::getSingleton().setMoveToFirstFlag();
                partyMove_ = 1;
            } else if (TownPlayerManager::getSingleton().getMoveToFirstFlag() == false) {
                moveMode_ = 0;
                if (surfaseId != -1) {
                    status::g_StageInfo.setFallFlag(false);
                }
            }
        }
    }
    if (TownSugorokuManager::getSingleton().isTreasuerRoom() == true) {
        g_SugorokuInfo.decTimer();
    }
}

int twn::TownActionFall::update()
{
    int ret = -1;
    if (fallType_ == 0) {
        if (cmn::gMoveToTarget.update() != -1) {
            dss::Fix32Vector3 temp;
            dss::Fix32 height;
            TownCamera::getSingleton()->setCameraLock(false);
            status::g_StageInfo.setFallFlag(false);
            ret = 0;
            TownPlayerManager::getSingleton().setRemote(false);
            TownPlayerManager::getSingleton().setShadowExec(false);
            TownPlayerManager::getSingleton().setExitSE(true);
            TownPlayerManager::getSingleton().setAnimation(1);
        }
    } else if (moveMode_ == 0) {
        TownCamera::getSingleton()->setCameraLock(false);
        TownPlayerManager::getSingleton().setRemote(false);
        TownPlayerManager::getSingleton().setShadowExec(false);
        TownPlayerManager::getSingleton().setExitSE(true);
        TownPlayerManager::getSingleton().setAnimation(1);
        ret = 0;
    }
    if (TownStageManager::getSingleton()->getExitIndex() != -1) {
        status::g_StageInfo.setFallFlag(true);
    }
    return ret;
}

int twn::TownActionFall::startCheck()
{
    int ret = -1;
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(11) != -1 && TownStageManager::getSingleton()->getHitSurfaceIdByType(0) == -1) {
        setCollFall();
        ret = 3;
    }
    return ret;
}

void twn::TownActionFall::setCollFall()
{
    partyMove_ = 0;
    moveMode_ = 1;
    fallType_ = 1;
    status::g_StageInfo.setFallFlag(true);
    TownPlayerManager::getSingleton().setMoveToFirstFlag();
    TownPlayerManager::getSingleton().setShadowExec(true);
    TownPlayerManager::getSingleton().setRemote(true);
    TownPlayerManager::getSingleton().setExitSE(false);
    TownPlayerManager::getSingleton().setAnimation(0);
    count_ = 0;
    sePlay_ = 1;
}

void twn::TownActionFall::setFixXZ()
{
    static const dss::Fix32 judgeLen((fx32)0xccd);
    static const dss::Fix32 fixXZ((fx32)0x59a);
    dss::Fix32Vector3 vec1;
    dss::Fix32Vector3 vec2;
    dss::Fix32Vector3 target;
    dss::Fix32Vector3 retVec;
    TownActionCalculate::getDirByIdx(dirIdx_, vec1);
    TownActionCalculate::getDirByIdx(dirIdx_ + 0x4000, vec2);
    position_ += vec1 * TownPlayerAction::walkSpeed;
    target = position_ + vec1 * TownPlayerAction::walkSpeed * 6;
    int poly;
    if (TownStageManager::getSingleton()->checkCrossNumEraseSurface(position_, target, 0x10000, true, poly)) {
        vecXZ_.set(0, 0, 0);
    } else {
        vecXZ_ = vec1 * TownPlayerAction::walkSpeed / 2;
    }
    target = position_ + vec2 * fixXZ;
    target.vy += TownPlayerAction::collR;
    int temp = TownStageManager::getSingleton()->getHitSurfaceIdByType(0);
    TownStageManager::getSingleton()->setHitSurfaceIdByType(0, -1);
    TownStageManager::getSingleton()->searchFloorSurface(target, TownPlayerAction::collR, judgeLen, retVec);
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0) == 0) {
        vecXZ_ -= vec2 * TownPlayerAction::walkSpeed;
    }
    TownStageManager::getSingleton()->clearHitSurfaceIdByType(0);
    TownStageManager::getSingleton()->setHitSurfaceIdByType(0, -1);
    target = position_ - vec2 * fixXZ;
    target.vy += TownPlayerAction::collR;
    TownStageManager::getSingleton()->searchFloorSurface(target, TownPlayerAction::collR, judgeLen, retVec);
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0) == 0) {
        vecXZ_ += vec2 * TownPlayerAction::walkSpeed;
    }
    TownStageManager::getSingleton()->setHitSurfaceIdByType(0, temp);
}

void twn::TownActionFall::exitFall()
{
    TownCamera::getSingleton()->setCameraLock(true);
    position_.vy -= fallSpeed;
}
