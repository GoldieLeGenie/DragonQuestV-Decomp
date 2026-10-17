#pragma ipa file
#include "ov001/town/player/TownActionRope.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonPartyInfo.hpp"
#include "main/fld/Coll.hpp"
#include "main/status/StageInfo.hpp"

#pragma thumb on

inline int status::StageInfo::getEncountFlag()
{
    return encount_;
}

inline int status::StageInfo::getIdoLinkInFlag()
{
    return idoLinkInFlag_;
}

inline void status::StageInfo::setIdoLinkOutFlag(bool flag)
{
    idoLinkOutFlag_ = flag;
}

inline void status::StageInfo::setRopeLink(int flag)
{
    ropeLink_ = flag;
}

inline void cmn::CommonPartyInfo::setStartPos(dss::Fix32Vector3& pos)
{
    startPos_ = pos;
}

inline void cmn::CommonPartyInfo::setPrevPosition()
{
    prev_position_ = position_;
}

inline int FldCollision::getSurfacePolyNoByType(int type)
{
    return surfacePolyNo_[type];
}

inline int twn::TownStageManager::getHitPolyNoByType(int type)
{
    return coll_.getSurfacePolyNoByType(type);
}

inline int twn::TownStageManager::getCollPolyByPolyNo(int polyNo, COLL_POLY* coll)
{
    return stage_.collGetPoly(polyNo, coll);
}

inline void twn::TownPlayerManager::setShadowExec(bool flag)
{
    shadowSet_ = flag;
}

inline int twn::TownPlayerAction::getPadInput()
{
    return padInput_;
}

inline int twn::TownPlayerAction::getDirInput()
{
    return dirInput_;
}

inline int twn::TownPlayerManager::getPadInput()
{
    return player_.getPadInput();
}

inline int twn::TownPlayerManager::getDirInput()
{
    return player_.getDirInput();
}

namespace twn {
    const dss::Fix32 ropeDownDY((fx32)0x4cd);
    const dss::Fix32 ropeUpDY(0.35f);
    const dss::Fix32 lengthGetDown(0.9f);
    const dss::Fix32 ropeSearchR(0.35f);
    const dss::Fix32 ropeUpFixY(0.4f);
}

const dss::Fix32 twn::TownActionRope::ropeFix((fx32)0xccd);

int twn::TownActionRope::setup()
{
    if (status::g_StageInfo.getEncountFlag() == true) {
        return -1;
    }
    int ret = -1;
    dss::Fix32Vector3 surfacePos;
    dss::Fix32Vector3 startPos;
    dss::Fix32Vector3 tempDir;
    int surfaceId = TownStageManager::getSingleton()->getHitSurfaceIdByType(6);
    if (surfaceId != -1) {
        surfacePos = TownStageManager::getSingleton()->getHitSurfacePosByType(6);
        surfaceDir_ = TownStageManager::getSingleton()->getHitSurfaceDirByType(6);
        getRopeSide(surfaceId);
        int ropeLink;
        if (position_.vy < (maxY_ + minY_) / 2) {
            ropeLink = true;
        }
        if (ropeLink == true) {
            surfacePos.vy = position_.vy + TownPlayerAction::rageSurfaceR;
            startPos = surfacePos + surfaceDir_ * ropeDownDY;
        } else {
            surfacePos.vy = position_.vy - TownPlayerAction::rageSurfaceR;
            startPos = surfacePos + surfaceDir_ * ropeDownDY;
        }
        tempDir = surfaceDir_ * -1;
        TownActionCalculate::getIdxByVec(dirIdx_, tempDir);
        TownPlayerManager::getSingleton().setShadowExec(true);
        cmn::g_cmnPartyInfo.setStartPos(startPos);
        ret = 1;
        moveMode_ = ROPE_MOVE;
    }
    return ret;
}

void twn::TownActionRope::execute()
{
    switch (moveMode_) {
    case ROPE_MOVE:
        ropeMove();
        break;
    case DOWN_SIDE_GET_ON:
    case DOWN_SIDE_GET_OFF:
    case UP_SIDE_GET_ON:
    case UP_SIDE_GET_OFF:
        cmn::gMoveToTarget.execute();
        break;
    }
}

int twn::TownActionRope::update()
{
    dss::Fix32Vector3 nowPos;
    dss::Fix32Vector3 nextPos;
    dss::Fix32 height;
    int ret = -1;
    switch (moveMode_) {
    case ROPE_MOVE:
        nowPos = position_;
        ropeMoveUpdate();
        nextPos = position_;
        TownStageManager::getSingleton()->compute(nowPos, nextPos, TownPlayerAction::collR, TownPlayerAction::surfaceR, TownPlayerAction::collR * 2, height);
        if (TownStageManager::getSingleton()->getHitSurfaceIdByType(5) != -1 && status::g_StageInfo.getIdoLinkInFlag() == true) {
            status::g_StageInfo.setIdoLinkOutFlag(true);
        } else if (TownStageManager::getSingleton()->getHitSurfaceIdByType(1) != 0) {
            if (position_.vy > (minY_ + maxY_) / 2) {
                status::g_StageInfo.setRopeLink(1);
            } else {
                status::g_StageInfo.setRopeLink(2);
            }
        }
        break;
    case DOWN_SIDE_GET_ON:
    case UP_SIDE_GET_ON:
        if (cmn::gMoveToTarget.update() != -1) {
            moveMode_ = ROPE_MOVE;
            TownPlayerManager::getSingleton().setRemote(false);
        }
        break;
    case DOWN_SIDE_GET_OFF:
    case UP_SIDE_GET_OFF:
        if (cmn::gMoveToTarget.update() != -1) {
            TownPlayerManager::getSingleton().setRemote(false);
            cmn::g_cmnPartyInfo.setPrevPosition();
            ret = 0;
        }
        break;
    }
    return ret;
}

int twn::TownActionRope::startCheck()
{
    int ret = -1;
    static const dss::Fix32 cosRope(0.75f);
    dss::Fix32Vector3 playerDir;
    dss::Fix32Vector3 surfacePos;
    dss::Fix32Vector3 surfaceDir;
    dss::Fix32Vector3 targetPos;
    dss::Fix32Vector3 vec;
    dss::Fix32 minY;
    dss::Fix32 maxY;
    int surfaceId = TownStageManager::getSingleton()->getHitSurfaceIdByType(6);
    if (surfaceId != -1) {
        TownActionCalculate::getDirByIdx(dirIdx_, playerDir);
        playerDir.normalize();
        surfacePos = TownStageManager::getSingleton()->getHitSurfacePosByType(6);
        surfaceDir = TownStageManager::getSingleton()->getHitSurfaceDirByType(6);
        vec = surfacePos - position_;
        vec.vy = 0L;
        vec.normalize();
        getRopeSide(surfaceId);
        dss::Fix32 center = (minY_ + maxY_) / 2;
        dss::Fix32Vector3 dir = surfaceDir * -1;
        if (playerDir * (surfaceDir * -1) > cosRope && playerDir * vec > cosRope) {
            if (center > position_.vy) {
                surfacePos.vy = position_.vy;
                targetPos = surfacePos + surfaceDir * ropeDownDY;
                cmn::gMoveToTarget.setAction(position_, targetPos, TownPlayerAction::walkSpeed, 0, 0, 1);
                TownActionCalculate::getIdxByVec(dirIdx_, dir);
                moveMode_ = UP_SIDE_GET_ON;
            } else {
                surfacePos.vy = position_.vy;
                targetPos = surfacePos + surfaceDir * ropeDownDY * -1;
                targetPos.vy -= TownPlayerAction::walkSpeed * 8;
                cmn::gMoveToTarget.setAction(position_, targetPos, TownPlayerAction::walkSpeed, 0, 0, 1);
                TownActionCalculate::getIdxByVec(dirIdx_, surfaceDir);
                moveMode_ = DOWN_SIDE_GET_ON;
            }
            TownPlayerManager::getSingleton().setRemote(true);
            ret = 1;
            TownPlayerManager::getSingleton().setShadowExec(true);
        }
    }
    return ret;
}

void twn::TownActionRope::getRopeSide(int surfaceID)
{
    COLL_POLY coll;
    int polyNo = TownStageManager::getSingleton()->getHitPolyNoByType(6);
    if (TownStageManager::getSingleton()->getCollPolyByPolyNo(polyNo, &coll)) {
        minY_.value = coll.vertex[0].y;
        maxY_.value = coll.vertex[0].y;
        for (int i = 1; i < 4; i++) {
            if (coll.vertex[i].y < minY_.value) {
                minY_.value = coll.vertex[i].y;
            }
            if (coll.vertex[i].y > maxY_.value) {
                maxY_.value = coll.vertex[i].y;
            }
        }
    }
}

void twn::TownActionRope::ropeMove()
{
    int padInput = TownPlayerManager::getSingleton().getPadInput();
    int dirInput = TownPlayerManager::getSingleton().getDirInput();
    if (padInput) {
        switch (dirInput) {
        case 0:
            position_.vy += TownPlayerAction::ropeSpeed;
            break;
        case 0x8000:
            position_.vy -= TownPlayerAction::ropeSpeed;
            break;
        }
    }
}

void twn::TownActionRope::ropeMoveUpdate()
{
    dss::Fix32Vector3 playerDir;
    dss::Fix32Vector3 target;
    dss::Fix32Vector3 pos;
    dss::Fix32 height;
    TownActionCalculate::getDirByIdx(dirIdx_, playerDir);
    int padInput = TownPlayerManager::getSingleton().getPadInput();
    int dirInput = TownPlayerManager::getSingleton().getDirInput();
    if (padInput == 0) {
        return;
    }
    if (position_.vy <= minY_ + ropeUpDY && dirInput == 0x8000) {
        target = position_ + playerDir * ropeDownDY * -1;
        cmn::gMoveToTarget.setAction(position_, target, TownPlayerAction::walkSpeed, 0, 0, 0);
        moveMode_ = DOWN_SIDE_GET_OFF;
        TownPlayerManager::getSingleton().setShadowExec(false);
        TownPlayerManager::getSingleton().setRemote(true);
        return;
    }
    if (position_.vy >= (maxY_ + minY_) / 2 && dirInput == 0) {
        target = position_ + playerDir;
        target.vy += TownPlayerAction::collR;
        TownStageManager::getSingleton()->compute(target, target, ropeUpFixY, ropeUpFixY, ropeUpFixY * 2, height);
        target.vy += height - TownPlayerAction::collR;
        if (TownStageManager::getSingleton()->getHitSurfaceIdByType(0) != -1) {
            pos = TownStageManager::getSingleton()->getHitSurfacePosByType(0);
            if (position_.vy > pos.vy && pos.vy > (maxY_ + minY_) / 2) {
                cmn::gMoveToTarget.setAction(position_, target, TownPlayerAction::walkSpeed, 0, 0, 0);
                moveMode_ = UP_SIDE_GET_OFF;
                TownPlayerManager::getSingleton().setShadowExec(false);
                TownPlayerManager::getSingleton().setRemote(true);
            }
        }
    }
}
