#pragma ipa file
#include "ov001/town/TownActionCalculate.hpp"
#include "ov001/town/TownCamera.hpp"
#include "ov001/town/TownCharacterManager.hpp"
#include "ov001/town/TownPlayerManager.hpp"
#include "ov001/town/TownStageManager.hpp"
#include "ov001/town/stage/TownExtraCollManager.hpp"
#include "main/cmn/CommonCalculate.hpp"
#include "main/dss/Camera.hpp"
#include "main/dss/UnkMatrix43.hpp"
#include <nitro/fx/fx_atan.h>

#pragma thumb on

inline int FldCollision::getCollID()
{
    return id_;
}

inline int FldStage::collGetObjId(int polygonNo)
{
    return coll_GetObjId(m_fld.m_coll, polygonNo);
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

inline int twn::TownStageManager::getMapObjUid(int obj_id)
{
    return stage_.m_fld.GetMapObjUid(obj_id);
}

inline int twn::TownStageManager::getSurfaceByPolygonNo(int polyNo)
{
    return coll_GetSurface(stage_.m_fld.m_coll, polyNo);
}

inline short twn::TownStageManager::getObjectRotIdx(int objectId)
{
    return stage_.getObjectRotIdxY(objectId);
}

inline int twn::TownStageManager::getFrontPoly(int polyNo, int objNo)
{
    return coll_.getFrontPoly(polyNo, objNo);
}

inline bool twn::TownStageManager::getPolyPos(dss::Fix32Vector3* pos, int polyNo)
{
    return stage_.collGetPolygonPos(polyNo, pos);
}

inline int TownCamera::isRotateL()
{
    return flagRotateL;
}

inline int TownCamera::isRotateR()
{
    return flagRotateR;
}

inline void twn::TownCharacterBase::setAreaCheck(bool flag)
{
    areaCheck_ = flag;
}

inline void TownCharacterManager::setAreaCheck(bool flag)
{
    twn::TownCharacterBase::setAreaCheck(flag);
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

const dss::Fix32 twn::TownActionCalculate::cos_PI_6((fx32)0xddb);

bool twn::TownActionCalculate::IntersectRaySphere(dss::Fix32Vector3& p, dss::Fix32Vector3& d, dss::Fix32Vector3& sc, dss::Fix32 r, dss::Fix32& t, dss::Fix32Vector3& q)
{
    dss::Fix32Vector3 m = p - sc;
    dss::Fix32 b = m * d;
    dss::Fix32 c = m * m - r * r;
    if (c > dss::Fix32(0L) && b > dss::Fix32(0L)) {
        return false;
    }
    dss::Fix32 discr = b * b - c;
    if (discr < dss::Fix32(0L)) {
        return false;
    }
    t = 0L;
    t -= b;
    t -= discr.sqrt();
    if (t < dss::Fix32(0L)) {
        t = 0L;
    }
    q = p + d * t;
    return true;
}

bool twn::TownActionCalculate::crossCheck(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32Vector3& target, dss::Fix32 radius)
{
    dss::Fix32Vector3 vec = target - nextPos;
    dss::Fix32 r2;
    r2.value = radius.value << 1;
    static const dss::Fix32 unk_02151748((fx32)0x7b);
    if (vec.lengthsq() < r2 * r2) {
        vec.normalize();
        dss::Fix32Vector3 ret;
        dss::Fix32Vector3 dir = nextPos - nowPos;
        dir.normalize();
        dss::Fix32 dot = dir * vec;
        dss::Fix32 t;
        if (dot.value > 0x92d) {
            if (IntersectRaySphere(nowPos, dir, target, r2, t, ret)) {
                if (nextPos.length(ret) <= radius) {
                    nextPos = ret;
                } else {
                    nextPos = nowPos;
                }
            }
        } else {
            nextPos = target - (vec * radius) * 2;
        }
        return true;
    }
    return false;
}

bool twn::TownActionCalculate::checkFarTalk(dss::Fix32Vector3& nowPos, int surfaceId, int objectId, int searchPoly, dss::Fix32 ctrLen)
{
    dss::Fix32Vector3 vecN;
    bool farTalk = false;
    int polyNo = -1;
    int commonId = TownStageManager::getSingleton()->getCommonID(objectId);
    if (surfaceId != -1) {
        vecN = TownStageManager::getSingleton()->getHitSurfaceDirByType(12);
        vecN = vecN * -1;
        ctrLen.value += 600;
        farTalk = true;
    } else if (commonId != -1) {
        switch (commonId) {
        case 0x2da:
        case 0x2dc: {
            dss::Fix32Vector3 objPos;
            dss::Fix32Vector3 objDir;
            TownStageManager::getSingleton()->getObjectPos(objectId, searchPoly, &objPos);
            int objIdx = TownStageManager::getSingleton()->getObjectRotIdx(objectId);
            getDirByIdx(objIdx, objDir);
            dss::Fix32Vector3 vec = TownPlayerManager::getSingleton().getPosition() - objPos;
            vec.vy = 0L;
            vec.normalize();
            if (vec * objDir <= dss::Fix32((fx32)0x800)) {
                return false;
            }
            break;
        }
        case 0x2c8:
        case 0x2c9:
        case 0x2cb: {
            dss::Fix32Vector3 objDir;
            int objIdx = TownStageManager::getSingleton()->getObjectRotIdx(objectId);
            getDirByIdx(objIdx, objDir);
            int playerIdx = TownPlayerManager::getSingleton().getDirection();
            if (dss::abs<int>(objIdx - playerIdx) < 0x4000) {
                return false;
            }
            dss::Fix32Vector3 objPos;
            TownStageManager::getSingleton()->getObjectPos(objectId, searchPoly, &objPos);
            dss::Fix32Vector3 vec = TownPlayerManager::getSingleton().getPosition() - objPos;
            if (vec * objDir <= dss::Fix32(0L)) {
                return false;
            }
            break;
        }
        }
        if (TownStageManager::getSingleton()->getSearchPolyDirection(vecN) == true) {
            vecN *= -1;
        } else {
            commonId = -1;
            vecN.set(0, 0, 0);
        }
        switch (commonId) {
        case 0x1069:
            farTalk = true;
            ctrLen.value += 1500;
            break;
        case 0x6a6:
        case 0x6a8:
            farTalk = true;
            ctrLen.value += 1000;
            break;
        case 0x1136:
            farTalk = true;
            break;
        case 0x320:
        case 0x6a4:
        case 0x6a5:
        case 0x6a7:
            TownCharacterManager::getSingleton()->checkObjectInTalk(objectId);
            polyNo = TownStageManager::getSingleton()->getFrontPoly(searchPoly, objectId);
            break;
        case 0x1f4:
        case 0x258:
        case 0x259:
        case 0x25a:
        case 0x25b:
        case 0x25c:
        case 0x2c8:
        case 0x2c9:
        case 0x2cb:
        case 0x2da:
        case 0x2dc:
        case 0x517:
        case 0x518:
        case 0x519:
        case 0x106a:
        case 0x14ba:
            TownCharacterManager::getSingleton()->checkObjectInTalk(objectId);
            break;
        }
    }
    return TownCharacterManager::getSingleton()->checkFarTalk(nowPos, vecN, ctrLen, polyNo, farTalk);
}

void twn::TownActionCalculate::townCharaColl(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 r)
{
    TownCharacterManager::getSingleton()->setAreaCheck(true);
    TownCharacterManager::getSingleton()->characterColl(nowPos, nextPos, r);
}

int twn::TownActionCalculate::townStageColl(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 radius, dss::Fix32 srufaceRad, dss::Fix32 preR)
{
    static const dss::Fix32 dv((fx32)0x8f);
    static const dss::Fix32 dvObj((fx32)0x17d);
    int ret = -1;
    dss::Fix32 height;
    dss::Fix32Vector3 temp;
    dss::Fix32Vector3 vec;
    temp = TownStageManager::getSingleton()->compute(nowPos, nextPos, radius, srufaceRad, preR, height);
    nextPos = temp;
    if (height < TownPlayerAction::fallH * -1) {
        ret = 3;
    } else {
        nextPos.vy += height;
    }
    vec = nextPos - nowPos;
    if (vec.lengthsq() < dv * dv) {
        nextPos = nowPos;
    } else {
        int collId = TownStageManager::getSingleton()->getWallCollId();
        if (collId != -1) {
            int objectId = TownStageManager::getSingleton()->getObjectID(collId);
            int commonId = TownStageManager::getSingleton()->getCommonID(objectId);
            if (commonId == 0x6a4) {
                return ret;
            }
            int surfaceId = TownStageManager::getSingleton()->getSurfaceByPolygonNo(collId);
            int mapUid = TownStageManager::getSingleton()->getMapObjUid(objectId);
            if (surfaceId != -1 || mapUid != 0) {
                if (TownStageManager::getSingleton()->getHitSurfaceIdByType(10) == -1) {
                    if (vec.lengthsq() < dvObj * dvObj) {
                        nextPos = nowPos;
                    }
                }
            }
        }
    }
    return ret;
}

void twn::TownActionCalculate::townShipStageColl(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 radius, dss::Fix32 surfaceRad, dss::Fix32 preR)
{
    dss::Fix32 height;
    dss::Fix32Vector3 temp;
    dss::Fix32Vector3 vec;
    static const dss::Fix32 unk_0215172c((fx32)0x1000);
    static const dss::Fix32 unk_0215173c((fx32)0x400);
    static const dss::Fix32 dv((fx32)0x8f);
    static const dss::Fix32 dvObj((fx32)0x17d);
    temp = TownStageManager::getSingleton()->compute(nowPos, nextPos, radius, surfaceRad, preR, height);
    nextPos = temp;
    nextPos.vy += height;
    vec = temp - nowPos;
}

bool twn::TownActionCalculate::directionCheckByPosition(dss::Fix32Vector3& pos, dss::Fix32Vector3& target, short idx, int value)
{
    dss::Fix32Vector3 dir;
    dss::Fix32Vector3 vec;
    getDirByIdx(idx, dir);
    vec = target - pos;
    vec.vy = 0L;
    vec.normalize();
    return (vec * dir).value >= value;
}

void twn::TownActionCalculate::getDirByIdx(short dirIdx, dss::Fix32Vector3& dir)
{
    cmn::CommonCalculate::getDirByIdx(dirIdx, dir);
}

void twn::TownActionCalculate::getVec4ByIdx(short dirIdx, dss::Fix32Vector3& retDir)
{
    retDir.set(0, 0, 0);
    if (dirIdx > -0x2000 && dirIdx <= 0x2000) {
        retDir.vz.value = 0x1000;
    } else if (dirIdx > 0x2000 && dirIdx <= 0x6000) {
        retDir.vx.value = 0x1000;
    } else if (dirIdx < -0x2000 && dirIdx >= -0x6000) {
        retDir.vx.value = -0x1000;
    } else {
        retDir.vz.value = -0x1000;
    }
}

void twn::TownActionCalculate::getIdxByVec(short& idx, dss::Fix32Vector3& dir)
{
    if (dir.vx == dss::Fix32(0L) && dir.vz == dss::Fix32(0L)) {
        return;
    }
    idx = FX_Atan2Idx(dir.vx.value, dir.vz.value);
}

int twn::TownActionCalculate::searchPairWdoor(int objectId, dss::Fix32Vector3* door1, dss::Fix32Vector3* door2)
{
    bool ret = false;
    static const dss::Fix32 wDoorlength((fx32)0x1b33);
    int retObjId = -1;
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 posDoor1;
    dss::Fix32Vector3 posDoor2;
    int commonId1 = TownStageManager::getSingleton()->getCommonID(objectId);
    int mapUid1 = TownStageManager::getSingleton()->getMapObjUid(objectId);
    TownStageManager::getSingleton()->getObjectPos(objectId, 0, &posDoor1);
    int objectId2 = TownStageManager::getSingleton()->getObjectIDfromMapUid(mapUid1 - 1);
    int commonId2 = TownStageManager::getSingleton()->getCommonID(objectId2);
    if (commonId1 == commonId2) {
        TownStageManager::getSingleton()->getObjectPos(objectId2, 0, &posDoor2);
        vec = posDoor2 - posDoor1;
        if (vec.lengthsq() < wDoorlength * wDoorlength) {
            retObjId = objectId2;
            ret = true;
        }
    }
    if (!ret) {
        objectId2 = TownStageManager::getSingleton()->getObjectIDfromMapUid(mapUid1 + 1);
        commonId2 = TownStageManager::getSingleton()->getCommonID(objectId2);
        if (commonId1 == commonId2) {
            TownStageManager::getSingleton()->getObjectPos(objectId2, 0, &posDoor2);
            vec = posDoor2 - posDoor1;
            if (vec.lengthsq() < wDoorlength * wDoorlength) {
                retObjId = objectId2;
            }
        }
    }
    if (door1) {
        *door1 = posDoor1;
    }
    if (door2) {
        *door2 = posDoor2;
    }
    return retObjId;
}

bool twn::TownActionCalculate::checkTalking(dss::Fix32Vector3& pos, short dirIdx, int objectId)
{
    if (TownCamera::getSingleton()->isRotateL()) {
        return false;
    }
    if (TownCamera::getSingleton()->isRotateR()) {
        return false;
    }
    if (objectId != -1) {
        int charaNo;
        if (TownExtraCollManager::getSingleton().isExtraCollChara(objectId, charaNo) == 2) {
            TownCharacterManager::getSingleton()->setTalked(charaNo, true);
            TownCharacterManager::getSingleton()->setTalkedArea(charaNo, true);
            return true;
        }
    }
    if (TownCharacterManager::getSingleton()->checkTalkingNearCharacter(pos, dirIdx, -1) == true) {
        return true;
    }
    return false;
}

bool twn::TownActionCalculate::checkIkadaTalk(dss::Fix32Vector3 pos, short dirIdx, int surfaceId, int polyId, bool menuSearch)
{
    static const dss::Fix32 len((fx32)0x14cd);
    if (TownCamera::getSingleton()->isRotateL()) {
        return false;
    }
    if (TownCamera::getSingleton()->isRotateR()) {
        return false;
    }
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 target;
    getDirByIdx(dirIdx, vec);
    target = pos + vec * len;
    if (surfaceId != -1) {
        dss::Fix32Vector3 dir;
        TownStageManager::getSingleton()->getPolyDirection(dir, polyId);
        if (((dir * vec) * -1).value < 0xb50) {
            return false;
        }
        if (TownCharacterManager::getSingleton()->checkIkadaTalk(target, dir) == true) {
            return true;
        }
    }
    return false;
}

void twn::TownActionCalculate::normalMove(dss::Fix32Vector3& position, short& dirIdx, dss::Fix32 speed)
{
    int padInput = TownPlayerManager::getSingleton().getPadInput();
    if (padInput) {
        int dirInput = (unsigned short)TownPlayerManager::getSingleton().getDirInput();
        if (TownStageManager::getSingleton()->getHitSurfaceIdByType(14) != -1) {
            dirInput = (short)((short)((dirInput + (dirInput < 0 ? -0x2000 : 0x2000)) / 0x4000) * 0x4000);
        }
        dss::Fix32Vector3 direction(TownCamera::getSingleton()->camera_.unk_004.getDirection());
        direction.vy = 0L;
        direction.normalize();
        dss::UnkMatrix43 mat;
        mat.setRotY(-dirInput);
        direction = mat * direction;
        direction.vy = 0L;
        position = position + direction * speed;
        dirIdx = 0x8000 - dirInput + TownCamera::getSingleton()->camera_.unk_004.getAngle().vy;
        dirIdx = (unsigned short&)dirIdx;
    }
}

bool twn::TownActionCalculate::checkGetOnShipAndIkada(const dss::Fix32Vector3& nextPos, const dss::Fix32Vector3& pos, short dirIdx, dss::Fix32 length)
{
    bool ret = false;
    static const dss::Fix32 dot((fx32)0xa66);
    dss::Fix32Vector3 vec = pos - nextPos;
    dss::Fix32Vector3 playerDir;
    getDirByIdx(dirIdx, playerDir);
    vec.vy.value = 0;
    if (vec.lengthsq() < length * length) {
        vec.normalize();
        playerDir.normalize();
        if (playerDir * vec > dot) {
            ret = true;
        }
    }
    return ret;
}

bool twn::TownActionCalculate::checkGetDownShipAndIkada(dss::Fix32Vector3& nextPos, short dirIdx, dss::Fix32Vector3& targetPos, dss::Fix32Vector3& surfaceDir, dss::Fix32Vector3& surfacePos, dss::Fix32 downL)
{
    bool ret = false;
    static const dss::Fix32 len((fx32)0x2333);
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 playerDir;
    dss::Fix32Vector3 checkPos;
    dss::Fix32 length;
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(10) != -1) {
        getDirByIdx(dirIdx, playerDir);
        int surfacePoly = TownStageManager::getSingleton()->getWallCollId();
        if (surfacePoly == -1) {
            return false;
        }
        int surfaceId = TownStageManager::getSingleton()->getSurfaceByPolygonNo(surfacePoly);
        if (surfaceId == -1 || (surfaceId & 0xffff0000) != 0xa0000) {
            return false;
        }
        TownStageManager::getSingleton()->getPolyDirection(surfaceDir, surfacePoly);
        TownStageManager::getSingleton()->getPolyPos(&surfacePos, surfacePoly);
        if (!TownStageManager::getSingleton()->isPolyFacePosition(surfacePoly, nextPos, len)) {
            return false;
        }
        surfaceDir.normalize();
        playerDir.normalize();
        if ((surfaceDir * playerDir).value > -0x800) {
            return false;
        }
        vec = nextPos - surfacePos;
        vec.vy = 0L;
        length = vec * surfaceDir;
        length.value = dss::abs<long>(length.value);
        length += downL;
        checkPos = nextPos + (surfaceDir * -1) * length;
        dss::Fix32 fy;
        dss::Fix32Vector3 tempPos;
        dss::Fix32Vector3 tnext;
        tnext = nextPos;
        tnext.vy += TownPlayerAction::collR;
        checkPos.vy += TownPlayerAction::collR;
        dss::Fix32 height(checkPos.vy);
        if (TownStageManager::getSingleton()->checkCrossPolygon(tnext, checkPos, surfacePoly) == 1) {
            targetPos = checkPos;
            tempPos = TownStageManager::getSingleton()->compute(targetPos, targetPos, TownPlayerAction::collR, TownPlayerAction::collR, TownPlayerAction::townCharaPreR, fy);
            tnext = nextPos;
            tnext.vy = tempPos.vy;
            if (tempPos.vx == targetPos.vx && tempPos.vz == targetPos.vz) {
                townCharaColl(tempPos, tempPos, TownPlayerAction::townCharaR);
                if (tempPos.vx == targetPos.vx && tempPos.vz == targetPos.vz) {
                    tnext.vy = targetPos.vy = height;
                    int polyNo;
                    if (TownStageManager::getSingleton()->checkCrossNumEraseSurface(tnext, targetPos, 0xc0000, true, polyNo) == 2) {
                        targetPos.vy += fy - TownPlayerAction::collR;
                        ret = true;
                    }
                }
            }
        }
    }
    return ret;
}

int twn::TownActionCalculate::getParamDir4ByIdx(short idx)
{
    if (idx <= 0x2000 && idx >= -0x2000) {
        return 0;
    }
    if (idx >= 0x2000 && idx <= 0x6000) {
        return 1;
    }
    if (idx >= -0x6000 && idx <= -0x2000) {
        return 3;
    }
    return 2;
}

dss::Fix32Vector3 twn::TownActionCalculate::getParamVec(unsigned char dir)
{
    dss::Fix32Vector3 retDir;
    retDir.set(0, 0, 0);
    switch (dir) {
    case 0:
        retDir.vz.value = 0x1000;
        break;
    case 1:
        retDir.vx.value = 0x1000;
        break;
    case 2:
        retDir.vz.value = -0x1000;
        break;
    case 3:
        retDir.vx.value = -0x1000;
        break;
    }
    return retDir;
}

short twn::TownActionCalculate::getIdxByParam(unsigned char dir)
{
    return cmn::CommonCalculate::getIdxByParam(dir);
}

bool twn::TownActionCalculate::checkLineOver(dss::Fix32Vector3& pos, dss::Fix32Vector3& linePos, dss::Fix32Vector3 normal)
{
    bool ret = false;
    dss::Fix32Vector3 vec = pos - linePos;
    dss::Fix32 dot = vec * normal;
    if (dot >= dss::Fix32(0L)) {
        ret = true;
    }
    return ret;
}

void twn::TownActionCalculate::setAngle(char axisNo, short idx, dss::Vector3<short>& angle)
{
    angle.set(0, 0, 0);
    switch (axisNo) {
    case 0:
        angle.vx = idx;
        break;
    case 1:
        angle.vy = idx;
        break;
    case 2:
        angle.vz = idx;
        break;
    }
}

bool twn::TownActionCalculate::checkGetDownIkada(dss::Fix32Vector3& nextPos, short dirIdx, dss::Fix32Vector3& targetPos)
{
    bool ret = false;
    static const dss::Fix32 downL((fx32)0x6b8);
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 playerDir;
    dss::Fix32Vector3 surfacePos;
    dss::Fix32Vector3 surfaceDir;
    dss::Fix32Vector3 checkPos;
    dss::Fix32 length;
    if (TownStageManager::getSingleton()->getHitSurfaceIdByType(10) != -1) {
        getDirByIdx(dirIdx, playerDir);
        surfaceDir = TownStageManager::getSingleton()->getHitSurfaceDirByType(10);
        surfacePos = TownStageManager::getSingleton()->getHitSurfacePosByType(10);
        int surfacePoly = TownStageManager::getSingleton()->getWallCollId();
        surfaceDir.normalize();
        playerDir.normalize();
        if ((surfaceDir * -1) * playerDir < cos_PI_6) {
            return false;
        }
        vec = nextPos - surfacePos;
        vec.vy = 0L;
        length = vec * surfaceDir;
        length.value = dss::abs<long>(length.value);
        length += downL;
        checkPos = nextPos + (surfaceDir * -1) * length;
        dss::Fix32 fy;
        dss::Fix32Vector3 tempPos;
        dss::Fix32Vector3 tnext;
        tnext = nextPos;
        tnext.vy += TownPlayerAction::collR;
        checkPos.vy += TownPlayerAction::collR;
        dss::Fix32 height(checkPos.vy);
        if (TownStageManager::getSingleton()->checkCrossPolygon(tnext, checkPos, surfacePoly) == 1) {
            targetPos = checkPos;
            tempPos = TownStageManager::getSingleton()->compute(targetPos, targetPos, TownPlayerAction::collR, TownPlayerAction::collR, TownPlayerAction::collR * 2, fy);
            tnext = nextPos;
            tnext.vy = tempPos.vy;
            if (tempPos == targetPos) {
                townCharaColl(tempPos, tempPos, TownPlayerAction::townCharaR);
                if (tempPos == targetPos) {
                    tnext.vy = targetPos.vy = height;
                    int polyNo;
                    if (TownStageManager::getSingleton()->checkCrossNumEraseSurface(tnext, targetPos, 0xc0000, true, polyNo) == 2) {
                        targetPos.vy += fy - TownPlayerAction::collR;
                        ret = true;
                    }
                }
            }
        }
    }
    return ret;
}
