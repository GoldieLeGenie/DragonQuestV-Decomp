#pragma ipa file
#include "ov001/town/player/TownActionKaidan.hpp"
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "main/cmn/CommonActionMoveToTarget.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/global/StageLink.hpp"
#include "main/sound/Sound.hpp"

#pragma thumb on

inline int FldCollision::getCollID()
{
    return id_;
}

inline void FldCollision::clearSurfaceByType(int type)
{
    surfaceType_[type] = -1;
}

inline int fld::FLDObject::CollGetPolyNoBySurface(int surface_id, int start)
{
    return coll_GetPolyNoBySurface(m_coll, surface_id, start);
}

inline void fld::FLDObject::CollEraseObjId(int obj_id)
{
    coll_EraseObjId(m_coll, obj_id);
}

inline void fld::FLDObject::CollResetObjId(int obj_id)
{
    coll_ResetObjId(m_coll, obj_id);
}

inline int FldStage::collGetObjId(int polygonNo)
{
    return coll_GetObjId(m_fld.m_coll, polygonNo);
}

inline void FldStage::eraseCollision(int objectID)
{
    m_fld.CollEraseObjId(objectID);
}

inline void FldStage::resetCollision(int objectID)
{
    m_fld.CollResetObjId(objectID);
}

inline int twn::TownStageManager::getWallCollId()
{
    return coll_.getCollID();
}

inline int twn::TownStageManager::getObjectID(int polygonNo)
{
    return stage_.collGetObjId(polygonNo);
}

inline int twn::TownStageManager::getCommonID(int objectID)
{
    if (objectID == -1) {
        return -1;
    }
    return stage_.m_fld.GetMapObjCommonId(objectID);
}

inline int twn::TownStageManager::collGetPolyIDbySurfaceID(int surfaceID)
{
    return stage_.m_fld.CollGetPolyNoBySurface(surfaceID, 0);
}

inline void twn::TownStageManager::eraseCollision(int objectID)
{
    stage_.eraseCollision(objectID);
}

inline void twn::TownStageManager::resetCollision(int objectID)
{
    stage_.resetCollision(objectID);
}

inline int twn::TownStageManager::getObjWallPolyNo(int objectId, int No)
{
    return stage_.getObjWallPolyNo(objectId, No);
}

inline short twn::TownStageManager::getObjectRotIdx(int objectId)
{
    return stage_.getObjectRotIdxY(objectId);
}

inline int twn::TownStageManager::getCollPolyByPolyNo(int polyNo, COLL_POLY* coll)
{
    return stage_.collGetPoly(polyNo, coll);
}

inline void twn::TownStageManager::computeCollFloor(dss::Fix32Vector3& pos, dss::Fix32 rad, dss::Fix32Vector3 fixPos)
{
    coll_.computeCollFloor(pos, rad, fixPos);
}

inline void twn::TownStageManager::clearHitSurfaceIdByType(int type)
{
    coll_.clearSurfaceByType(type);
}

inline void twn::TownPlayerManager::setExitSE(bool flag)
{
    mapChangeSE_ = flag;
}

inline int twn::TownPlayerAction::getPadInput()
{
    return padInput_;
}

inline int twn::TownPlayerManager::getPadInput()
{
    return player_.getPadInput();
}

namespace twn {
    const dss::Fix32 kaidanF((fx32)0x4cd);
    const dss::Fix32 kaidanUp((fx32)0x666);
    const dss::Fix32 kaidanSideFix((fx32)0x19a);
    const dss::Fix32 startSearchLen((fx32)0x1333);
}

int twn::TownActionKaidan::setup()
{
    dss::Fix32Vector3 pos;
    dss::Fix32Vector3 pos1;
    dss::Fix32Vector3 pos2;
    dss::Fix32 length;
    pos1 = position_;
    pos2 = position_;
    pos1.vz += startSearchLen;
    downKaidan_.objectId = upKaidan_.objectId = -1;
    kaidanBackWall_ = downChange_ = firstDown_ = false;
    side1Wall_ = false;
    side2Wall_ = false;
    downKaidanFixY_ = 0L;
    int polyNo;
    int surface[2] = {0x10000, 0x70000};
    TownStageManager::getSingleton()->getCrossPolygonOtherSurface(pos2, pos1, surface, 2, polyNo, NULL, false);
    int objectNo = TownStageManager::getSingleton()->getObjectID(polyNo);
    int commonId = TownStageManager::getSingleton()->getCommonID(objectNo);
    if (commonId == 0x1194 || commonId == 0x1195) {
        int id = util::StageLink::getTownExitIndex();
        if (id == -1) {
            return -1;
        }
        id = TownStageManager::getSingleton()->collGetPolyIDbySurfaceID(id);
        if (id == -1) {
            return -1;
        }
        TownStageManager::getSingleton()->eraseCollision(objectNo);
        setKaidanArea(id);
        TownStageManager::getSingleton()->getObjectPos(objectNo, polyNo, &pos);
        setKaidanByObject(downKaidan_, objectNo, pos);
        dss::Fix32Vector3 target = pos - downKaidan_.normal * startSearchLen;
        int num = TownStageManager::getSingleton()->checkCrossNum(pos, target, true);
        if (num >= 1) {
            kaidanBackWall_ = true;
        }
        side1Wall_ = setSideFix(downKaidan_.pos1, downKaidan_.pos2, pos, side1WallLine_, side1WallNormal_);
        side2Wall_ = setSideFix(downKaidan_.pos2, downKaidan_.pos1, pos, side2WallLine_, side2WallNormal_);
        short idx = TownStageManager::getSingleton()->getObjectRotIdx(objectNo);
        dirIdx_ = idx - 0x4003;
        downChange_ = firstDown_ = true;
    }
    return -1;
}

void twn::TownActionKaidan::execute()
{
    if (moveType_ != KAIDAN_MOVE_STOP) {
        cmn::gMoveToTarget.execute();
    }
}

int twn::TownActionKaidan::update()
{
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 centerPos;
    dss::Fix32Vector3 target;
    dss::Fix32Vector3 targetPos;
    dss::Fix32Vector3 mVec;
    dss::Fix32 length;
    dss::Fix32 dot;
    dss::Fix32 speedToTarget;
    int ret = -1;
    static const dss::Fix32 rad((fx32)0x99a);
    static const dss::Fix32 col((fx32)0x8cd);
    dss::Fix32 h;
    speedToTarget = TownPlayerAction::walkSpeed;
    int type = cmn::gMoveToTarget.update();
    if (type != -1) {
        moveType_ = (KAIDAN_MOVE_TYPE)type;
        vec = position_ - upKaidan_.center;
        vec.vy = 0L;
        vec.normalize();
        checkKaidanSide(mVec, target, length);
        dot = vec * upKaidan_.normal;
        switch (moveType_) {
        case KAIDAN_MOVE_BACK:
            moveType_ = KAIDAN_MOVE_SIDE;
            targetPos = target + mVec * kaidanF;
            break;
        case KAIDAN_MOVE_SIDE:
            moveType_ = KAIDAN_MOVE_FRONT;
            targetPos = target + mVec * kaidanF * -3 / 2;
            break;
        case KAIDAN_MOVE_FRONT:
            moveType_ = KAIDAN_MOVE_UP;
            targetPos = upKaidan_.center;
            targetPos.vy += kaidanUp;
            speedToTarget = TownPlayerAction::walkSpeed / 2;
            break;
        case KAIDAN_MOVE_UP:
            Sound::sePlayDirect(0x131);
            TownPlayerManager::getSingleton().setExitSE(false);
            TownPlayerManager::getSingleton().setRemote(false);
            TownPlayerManager::getSingleton().resetMapLink(RESET_EXIT_LOCK_KAIDAN);
            TownStageManager::getSingleton()->compute(position_, position_, col, col, rad, h);
            if (TownStageManager::getSingleton()->getHitSurfaceIdByType(1) != -1 || TownStageManager::getSingleton()->getHitSurfaceIdByType(7) != -1) {
                moveType_ = KAIDAN_MOVE_STOP;
            } else {
                dss::Fix32Vector3 dir;
                TownActionCalculate::getDirByIdx(dirIdx_, dir);
                targetPos = position_ + dir;
                moveType_ = KAIDAN_MOVE_NOT_EXIT;
            }
            break;
        case KAIDAN_MOVE_NOT_EXIT:
            TownPlayerManager::getSingleton().setRemote(false);
            return 0;
        }
        if (moveType_ != KAIDAN_MOVE_STOP) {
            cmn::gMoveToTarget.setAction(position_, targetPos, speedToTarget, 0, 0, moveType_);
        }
    }
    return ret;
}

int twn::TownActionKaidan::startCheck()
{
    int ret = -1;
    upKaidan_.objectId = -1;
    checkObject();
    checkSurface();
    if (upKaidan_.objectId != -1) {
        if (upKaidan_.objectId != downKaidan_.objectId) {
            dss::Fix32Vector3 vec;
            TownActionCalculate::getDirByIdx(dirIdx_, vec);
            int padInput = TownPlayerManager::getSingleton().getPadInput();
            if ((upKaidan_.center - position_) * vec > dss::Fix32(0L) && padInput) {
                TownPlayerManager::getSingleton().lockMapLink(EXIT_LOCK_KAIDAN);
                checkKaidanMoveStart();
                TownPlayerManager::getSingleton().setRemote(true);
                ret = 5;
            }
        } else {
            TownStageManager::getSingleton()->resetCollision(downKaidan_.objectId);
        }
    } else if (firstDown_ == true) {
        if (cmn::CommonCalculate::simpleAreaInCheck(kaidanArea_[0], kaidanArea_[1], position_) == false) {
            TownStageManager::getSingleton()->resetCollision(downKaidan_.objectId);
            downKaidan_.objectId = -1;
            dss::Fix32Vector3 pos(position_);
            pos.vy = kaidanMaxH_;
            pos.vy.value -= 500;
            TownStageManager::getSingleton()->computeCollFloor(pos, TownPlayerAction::collR, position_);
            TownStageManager::getSingleton()->clearHitSurfaceIdByType(9);
            firstDown_ = false;
        }
    }
    return ret;
}

void twn::TownActionKaidan::checkObject()
{
    int polyNo = TownStageManager::getSingleton()->getWallCollId();
    int objectNo = TownStageManager::getSingleton()->getObjectID(polyNo);
    if (objectNo != -1) {
        int commonId = TownStageManager::getSingleton()->getCommonID(objectNo);
        if (commonId == 0x1194 || commonId == 0x1195) {
            dss::Fix32Vector3 pos;
            TownStageManager::getSingleton()->getObjectPos(objectNo, polyNo, &pos);
            setKaidanByObject(upKaidan_, objectNo, pos);
            upKaidan_.normal.vy = 0L;
            upKaidan_.normal.normalize();
            upKaidan_.pos1.vy = position_.vy;
            upKaidan_.pos2.vy = position_.vy;
        }
    }
}

void twn::TownActionKaidan::checkSurface()
{
    exitBeforeUpKaidan_ = false;
    TownPlayerManager::getSingleton().resetMapLink(RESET_EXIT_LOCK_KAIDAN);
    dss::Fix32Vector3 dir;
    static const dss::Fix32Vector3 upN(0.0f, 1.0f, 0.0f);
    static const dss::Fix32 dotN1(0.85f);
    static const dss::Fix32 dotN2(0.25f);
    dss::Fix32 dot;
    int surfaceId = TownStageManager::getSingleton()->getHitSurfaceIdByType(1);
    int polyNo;
    if (surfaceId != -1) {
        polyNo = TownStageManager::getSingleton()->getHitSurfaceIdByType(1);
        dir = TownStageManager::getSingleton()->getHitSurfaceDirByType(1);
    } else {
        surfaceId = TownStageManager::getSingleton()->getHitSurfaceIdByType(7);
        if (surfaceId != -1) {
            polyNo = TownStageManager::getSingleton()->getHitSurfaceIdByType(7);
            dir = TownStageManager::getSingleton()->getHitSurfaceDirByType(7);
        }
    }
    if (surfaceId != -1) {
        dir.normalize();
        dot = dir * upN;
        if (dot > dotN2 && dot < dotN1) {
            exitBeforeUpKaidan_ = true;
            TownPlayerManager::getSingleton().lockMapLink(EXIT_LOCK_KAIDAN);
        }
    } else {
        downChange_ = false;
    }
}

void twn::TownActionKaidan::setKaidanByObject(TownKaidan& kaidan, int id, dss::Fix32Vector3& pos)
{
    int polyNo = TownStageManager::getSingleton()->getObjWallPolyNo(id, 2);
    kaidan.objectId = id;
    COLL_POLY coll;
    TownStageManager::getSingleton()->getCollPolyByPolyNo(polyNo, &coll);
    kaidan.center = pos;
    kaidan.pos1 = FldStage::getFx32Vector3(coll.vertex[0]);
    kaidan.pos2 = FldStage::getFx32Vector3(coll.vertex[2]);
    kaidan.normal = FldStage::getFx32Vector3(coll.normal);
    TownPlayerManager::getSingleton().lockMapLink(EXIT_LOCK_KAIDAN);
}

void twn::TownActionKaidan::checkKaidanMoveStart()
{
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 target;
    dss::Fix32Vector3 mVec;
    dss::Fix32Vector3 targetPos;
    dss::Fix32 length;
    dss::Fix32 speedToTarget;
    dss::Fix32 dot;
    speedToTarget = TownPlayerAction::walkSpeed;
    vec = position_ - upKaidan_.center;
    vec.vy = 0L;
    vec.normalize();
    dot = vec * upKaidan_.normal;
    if (dot.value <= -0xb50) {
        moveType_ = KAIDAN_MOVE_BACK;
        checkKaidanSide(mVec, target, length);
        targetPos = position_ + mVec * length;
    } else if (dot.value < 0x800) {
        moveType_ = KAIDAN_MOVE_SIDE;
        checkKaidanSide(mVec, target, length);
        targetPos = target + mVec * kaidanF;
    } else {
        moveType_ = KAIDAN_MOVE_UP;
        checkKaidanSide(mVec, target, length);
        targetPos = upKaidan_.center;
        targetPos.vy += kaidanUp;
        speedToTarget = TownPlayerAction::walkSpeed / 2;
    }
    cmn::gMoveToTarget.setAction(position_, targetPos, speedToTarget, 0, 0, moveType_);
}

void twn::TownActionKaidan::checkKaidanSide(dss::Fix32Vector3& mVec, dss::Fix32Vector3& target, dss::Fix32& length)
{
    dss::Fix32Vector3 vec0;
    dss::Fix32Vector3 vec1;
    dss::Fix32Vector3 vec2;
    dss::Fix32Vector3 checkPos;
    static const dss::Fix32 fixL((fx32)0x1333);
    vec1 = position_ - upKaidan_.pos1;
    vec1.vy = 0L;
    vec2 = position_ - upKaidan_.pos2;
    vec2.vy = 0L;
    vec0 = upKaidan_.pos1 - upKaidan_.pos2;
    vec0 *= fixL;
    checkPos = upKaidan_.center + vec0;
    int num1 = TownStageManager::getSingleton()->checkCrossNum(upKaidan_.center, checkPos, false);
    checkPos = upKaidan_.center - vec0;
    int num2 = TownStageManager::getSingleton()->checkCrossNum(upKaidan_.center, checkPos, false);
    if (moveType_ == KAIDAN_MOVE_BACK) {
        if (num1 > 1 || (vec1.lengthsq() > vec2.lengthsq() && num2 < 2)) {
            mVec = upKaidan_.pos2 - upKaidan_.pos1;
            mVec.vy = 0L;
            mVec.normalize();
            length = mVec * (position_ - upKaidan_.pos2);
            target = upKaidan_.pos2;
        } else {
            mVec = upKaidan_.pos1 - upKaidan_.pos2;
            mVec.vy = 0L;
            mVec.normalize();
            length = mVec * (position_ - upKaidan_.pos1);
            target = upKaidan_.pos1;
        }
    } else {
        if (vec1.lengthsq() > vec2.lengthsq()) {
            mVec = upKaidan_.pos2 - upKaidan_.pos1;
            mVec.vy = 0L;
            mVec.normalize();
            length = mVec * (position_ - upKaidan_.pos2);
            target = upKaidan_.pos2;
        } else {
            mVec = upKaidan_.pos1 - upKaidan_.pos2;
            mVec.vy = 0L;
            mVec.normalize();
            length = mVec * (position_ - upKaidan_.pos1);
            target = upKaidan_.pos1;
        }
    }
    length.value = dss::abs<long>(length.value) + kaidanF.value;
}

void twn::TownActionKaidan::setPlayerFixPosition(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos)
{
    if (firstDown_ != true) {
        return;
    }
    downKaidanFixY_ = newPos.vy - kaidanMaxH_;
    if (side1Wall_ == true) {
        if (TownActionCalculate::checkLineOver(newPos, side1WallLine_, side1WallNormal_) == true) {
            dss::Fix32Vector3 vec = newPos - oldPos;
            dss::Fix32 val = side1WallNormal_ * vec;
            newPos -= side1WallNormal_ * val;
        }
    }
    if (side2Wall_ == true) {
        if (TownActionCalculate::checkLineOver(newPos, side2WallLine_, side2WallNormal_) == true) {
            dss::Fix32Vector3 vec = newPos - oldPos;
            dss::Fix32 val = side2WallNormal_ * vec;
            newPos -= side2WallNormal_ * val;
        }
    }
    if (downKaidanFixY_ >= dss::Fix32(0L)) {
        if (kaidanBackWall_ == true) {
            newPos = oldPos;
        }
        newPos.vy = kaidanMaxH_;
    }
}

bool twn::TownActionKaidan::setSideFix(dss::Fix32Vector3& pos1, dss::Fix32Vector3& pos2, dss::Fix32Vector3& center, dss::Fix32Vector3& sideLine, dss::Fix32Vector3& sideNormal)
{
    bool sideWall = false;
    dss::Fix32Vector3 normal = pos1 - pos2;
    normal.vy = 0L;
    normal.normalize();
    dss::Fix32Vector3 target = center + normal * startSearchLen;
    int num = TownStageManager::getSingleton()->checkCrossNum(center, target, true);
    if (num >= 1) {
        sideWall = true;
        sideLine = center + normal * kaidanSideFix;
        sideNormal = normal;
    }
    return sideWall;
}

void twn::TownActionKaidan::setKaidanArea(int polyNo)
{
    COLL_POLY coll;
    TownStageManager::getSingleton()->getCollPolyByPolyNo(polyNo, &coll);
    kaidanArea_[0] = FldStage::getFx32Vector3(coll.bbox[0]);
    kaidanArea_[1] = FldStage::getFx32Vector3(coll.bbox[1]);
    kaidanMaxH_.value = kaidanArea_[1].vy.value - 1000;
}

bool twn::TownActionKaidan::isSaveOK()
{
    if (firstDown_ == false) {
        return true;
    }
    return false;
}
