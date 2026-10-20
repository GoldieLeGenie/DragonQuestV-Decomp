#pragma ipa file
#include "main/fld/FldCollision.hpp"
#include "main/fld/FldStage.hpp"
#include "main/dss/DssCore.hpp"
#include "main/dss/UnkMatrix43.hpp"

inline int fld::FLDObject::CollCrossCheck(VecFx32* pos0, VecFx32* pos1, int start, fx32* len)
{
    if (start == 0) {
        m_cross_pos = *pos0;
        func_0208a1dc(pos1, pos0, &m_cross_dir);
        func_0208a330(&m_cross_dir, &m_cross_dir);
        m_cross_len = func_0208a5d0(pos0, pos1);
    }
    return coll_CrossCheck(m_coll, &m_cross_pos, &m_cross_dir, m_cross_len, start, len);
}

static int g_floor_ret;

ARM FldCollision::FldCollision()
{
    polyIndex_ = -1;
    animObjectCheck_ = NULL;
}

ARM FldCollision::~FldCollision()
{
}

ARM int FldCollision::getCollisionTick()
{
    return g_floor_ret;
}

ARM bool FldCollision::setExitPosition(dss::Fix32Vector3* pos, int index)
{
    int polyNo = coll_GetPolyNoBySurface(g_fld->m_coll, index, 0);
    if (polyNo == -1) {
        pos->set(0, 0, 0);
        return false;
    }
    COLL_POLY polyInfo;
    coll_GetPoly(g_fld->m_coll, polyNo, &polyInfo);
    dss::Fix32Vector3* normal = (dss::Fix32Vector3*)&polyInfo.normal;
    dss::Fix32Vector3 axisY(0, 1, 0);
    dss::Fix32 dot = *normal * axisY;
    static const dss::Fix32 fix(0x8cd);
    if (dot.value < 0x165) {
        exitType_ = 0;
        dss::Fix32Vector3 sum;
        sum = *(dss::Fix32Vector3*)&polyInfo.vertex[0];
        sum += *(dss::Fix32Vector3*)&polyInfo.vertex[1];
        sum += *(dss::Fix32Vector3*)&polyInfo.vertex[2];
        sum += *(dss::Fix32Vector3*)&polyInfo.vertex[3];
        sum /= 4;
        sum += *normal * fix;
        *pos = sum;
    } else {
        exitType_ = 1;
        dss::Fix32Vector3 sum;
        sum = *(dss::Fix32Vector3*)&polyInfo.vertex[0];
        sum += *(dss::Fix32Vector3*)&polyInfo.vertex[1];
        sum += *(dss::Fix32Vector3*)&polyInfo.vertex[2];
        sum += *(dss::Fix32Vector3*)&polyInfo.vertex[3];
        sum /= 4;
        sum.vy += 0x28;
        *pos = sum;
    }
    return true;
}

ARM dss::Fix32Vector3 FldCollision::compute(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 radius, dss::Fix32 surfaceR, dss::Fix32 preR, dss::Fix32& height)
{
    static const dss::Fix32 judgeLen(0xccd);
    if (*collisionFlag_ == 0) {
        return newPos;
    }
    g_floor_ret = getTick();
    floorPolygonNo_ = -1;
    polyIndex_ = -1;
    playerDirFlag_ = 0;
    eraseCheckCount_ = 0;
    dot_ = 0L;
    searchClear();
    dss::Fix32Vector3 retVec;
    searchFloorSurface(newPos, radius, judgeLen, retVec);
    dss::Fix32Vector3 correctedPosition;
    computeCollWall(oldPos, newPos, radius, surfaceR, preR, correctedPosition);
    correctedPosition.vy = oldPos.vy;
    dss::Fix32Vector3 fixYPos;
    computeCollFloor(correctedPosition, radius, fixYPos);
    correctedPosition.vy = oldPos.vy;
    height = fixYPos.vy - oldPos.vy;
    g_floor_ret = getTick() - g_floor_ret;
    return correctedPosition;
}

ARM void FldCollision::computeCollFloor(dss::Fix32Vector3& pos, dss::Fix32 radius, dss::Fix32Vector3& fixYPos)
{
    int ret = coll_SearchFloorPoly(g_fld->m_coll, (VecFx32*)&pos, radius.value, (VecFx32*)&fixYPos);
    if (ret < 0) {
        return;
    }
    floorPolygonNo_ = ret;
    if (coll_GetSurface(g_fld->m_coll, floorPolygonNo_) == -1 && surfaceType_[0] == -1) {
        surfaceType_[0] = 0;
        surfacePolyNo_[0] = floorPolygonNo_;
    }
}

ARM void FldCollision::searchClear()
{
    for (int i = 0; i < 22; i++) {
        surfaceType_[i] = -1;
    }
    searchObjectId_ = -1;
    floorMapUid_ = 0;
}

ARM void FldCollision::computeCollWall(const dss::Fix32Vector3& oldPos, const dss::Fix32Vector3& newPos, dss::Fix32 collRad, dss::Fix32 searchRad, dss::Fix32 preRad, dss::Fix32Vector3& retPos)
{
    unsigned short count;
    COLL_HEADER* coll = g_fld->m_coll;
    id_ = -1;
    retPos = oldPos;
    searchLen2.value = 0x7fffffff;
    unsigned short start = coll->floor_poly_size;
    count = start + (coll->wall_poly_size + coll->common_poly_size);
    newX = newPos.vx.value;
    newY = newPos.vy.value + collRad.value;
    newZ = newPos.vz.value;
    preR = preRad.value;
    radB = searchRad.value;
    radS = collRad.value;
    dss::Fix32Vector3 dirVec = newPos - oldPos;
    dirVec32.x = -dirVec.vx.value;
    dirVec32.y = -dirVec.vy.value;
    dirVec32.z = -dirVec.vz.value;
    collCount = 0;
    crossCount = 0;
    {
        COLL_HEADER* header = g_fld->m_coll;
        fx32 x = newPos.vx.value;
        fx32 z = newPos.vz.value;
        fx32 r = FX32_ONE;
        VecFx32 p0;
        VecFx32 p1;
        p0.x = x - r;
        p1.x = x + r;
        p0.z = z - r;
        p1.z = z + r;
        if (header->check_point[0].x > p0.x || header->check_point[0].z > p0.z || header->check_point[1].x < p1.x || header->check_point[1].z < p1.z) {
            p0.x -= r;
            p1.x += r;
            p0.z -= r;
            p1.z += r;
            p0.y = 0;
            p1.y = 0;
            header->check_point[0] = p0;
            header->check_point[1] = p1;
            coll_PreSearchWallPoly(header, &p0, &p1);
        }
    }
    wallPolyCheck(newPos, coll->poly, start, count);
    wallPolyCheck(newPos, coll->ext_data->ext_coll, 0, coll->ext_data->ext_num);
    if (crossCount == 0) {
        retPos = newPos;
        id_ = -1;
        return;
    }
    int min_poly_no = -1;
    fx32 rr = FX_Mul(collRad.value, collRad.value);
    fx32 min;
    fx32 len;
    VecFx32 min_cross;
    VecFx32 cross;
    VecFx32 min_crossN;
    VecFx32 ret = FldStage::getVecFx32(newPos);
    int counter = 0;
    long i;
    int signPolyNo = -1;
    while (true) {
        if (counter > 2) {
            retPos = oldPos;
            if (signPolyNo == -1) {
                signPolyNo = min_poly_no;
            }
            id_ = signPolyNo;
            return;
        }
        crossCount = 0;
        min = rr;
        for (i = 0; i < collCount; i++) {
            COLL_POLY* poly = nextList[i];
            if (poly->flag & 1) {
                continue;
            }
            if (newY < poly->bbox[0].y - radS || newY > radS + poly->bbox[1].y) {
                continue;
            }
            if (coll_CheckLinePoint(&ret, radS, &poly->bbox[0], &poly->bbox[1], &poly->normal, &cross) != 1) {
                continue;
            }
            len = FX_Mul(cross.x - ret.x, cross.x - ret.x) + FX_Mul(cross.z - ret.z, cross.z - ret.z);
            if (min > len + 2) {
                min = len;
                min_poly_no = collPolyNo[i];
                min_cross = cross;
                min_cross.y = oldPos.vy.value;
                crossCount++;
                if (nextList[i]->id != -1 || nextList[i]->obj_id != -1) {
                    signPolyNo = collPolyNo[i];
                }
            }
            if (signPolyNo == -1) {
                if (nextList[i]->id != -1 || nextList[i]->obj_id != -1) {
                    signPolyNo = collPolyNo[i];
                }
            }
        }
        if (crossCount == 0) {
            retPos = FldStage::getFx32Vector3(ret);
            if (signPolyNo == -1) {
                signPolyNo = min_poly_no;
            }
            id_ = signPolyNo;
            return;
        }
        func_0208a1dc(&ret, &min_cross, &min_crossN);
        min_crossN.y = 0;
        if (min_crossN.x == 0 && min_crossN.z == 0) {
            ret = min_cross;
        } else {
            func_0208a330(&min_crossN, &min_crossN);
            func_0208a574(radS, &min_crossN, &min_cross, &ret);
        }
        counter++;
    }
}

ARM bool FldCollision::checkSignPoly(const dss::Fix32Vector3& newPos, dss::Fix32Vector3& cross, int polyNo, COLL_POLY* poly)
{
    dss::Fix32 len2;
    if (poly->obj_id != -1) {
        if (isAnimObject(searchObjectId_) == true) {
            return true;
        }
        if (isAnimObject(poly->obj_id) == true) {
            searchObjectId_ = poly->obj_id;
            searchPolyNo_ = polyNo;
            searchLen2 = len2;
            return true;
        }
        len2 = (cross - newPos).lengthsq();
        if (len2 < searchLen2) {
            dss::Fix32Vector3 vec = cross - newPos;
            vec.vy = 0L;
            vec.normalize();
            if (playerDirFlag_ == 0) {
                playerDir_.vx.value = 0;
                playerDir_.vy.value = 0;
                playerDir_.vz.value = FX32_ONE;
                dss::UnkMatrix43 mat;
                mat.setRotY(playerIdx_);
                playerDir_ = mat * playerDir_;
                playerDirFlag_ = 1;
            }
            dss::Fix32 dot = playerDir_ * vec;
            if (dot > dss::Fix32(0x800) && dot >= dot_) {
                searchObjectId_ = poly->obj_id;
                searchPolyNo_ = polyNo;
                searchLen2 = len2;
                dot_ = dot;
            }
        }
    }
    if (poly->id != -1) {
        if (poly->id & 0xa0000) {
            len2.value = FX_Mul(cross.vx.value - newPos.vx.value, cross.vx.value - newPos.vx.value) + FX_Mul(cross.vz.value - newPos.vz.value, cross.vz.value - newPos.vz.value);
            if (surfaceType_[10] != -1 && surfaceLen < len2) {
                return true;
            }
            surfaceLen = len2;
        }
        if (isEraseSurfaceId(poly->id) == true) {
            eraseCheckSurface_[eraseCheckCount_] = poly->id;
            eraseCheckCount_++;
            return true;
        }
        int tempSurfaceID = poly->id;
        unsigned int type = (unsigned int)tempSurfaceID >> 16;
        if (surfaceType_[type] == -1) {
            surfaceType_[type] = tempSurfaceID;
            surfacePolyNo_[type] = polyNo;
        } else {
            dss::Fix32Vector3 p1 = FldStage::getFx32Vector3(poly->bbox[0]);
            dss::Fix32Vector3 p2 = FldStage::getFx32Vector3(poly->bbox[1]);
            p1.vy = p2.vy = 0L;
            dss::Fix32Vector3 tpos(newPos);
            tpos.vy = 0L;
            if ((tpos - p1) * (p1 - p2) > dss::Fix32(0L)) {
                return true;
            }
            if ((tpos - p2) * (p2 - p1) > dss::Fix32(0L)) {
                return true;
            }
            surfaceType_[type] = tempSurfaceID;
            surfacePolyNo_[type] = polyNo;
        }
    }
    return true;
}

ARM int FldCollision::characterColl(dss::Fix32Vector3& oldPos, dss::Fix32Vector3& newPos, dss::Fix32 radius, dss::Fix32Vector3* retPos, int type)
{
    int ret = -1;
    if (type & 1) {
        ret = coll_GetNextMove(g_fld->m_coll, (VecFx32*)&oldPos, (VecFx32*)&newPos, radius.value, (VecFx32*)retPos);
    } else {
        COLL_HEADER* header = g_fld->m_coll;
        fx32 x = newPos.vx.value;
        fx32 z = newPos.vz.value;
        fx32 r = radius.value;
        VecFx32 p0;
        VecFx32 p1;
        p0.x = x - r;
        p1.x = x + r;
        p0.z = z - r;
        p1.z = z + r;
        if (header->check_point[0].x > p0.x || header->check_point[0].z > p0.z || header->check_point[1].x < p1.x || header->check_point[1].z < p1.z) {
            p0.x -= r;
            p1.x += r;
            p0.z -= r;
            p1.z += r;
            p0.y = 0;
            p1.y = 0;
            header->check_point[0] = p0;
            header->check_point[1] = p1;
            coll_PreSearchWallPoly(header, &p0, &p1);
        }
    }
    if (type & 2) {
        retPos->vy += radius * 2;
        coll_SearchFloorPoly(g_fld->m_coll, (VecFx32*)retPos, radius.value, (VecFx32*)retPos);
        retPos->vy -= radius;
    }
    return ret;
}

ARM int FldCollision::getSearchObjectId()
{
    return searchObjectId_;
}

ARM int FldCollision::getSearchPolyNo()
{
    return searchPolyNo_;
}

ARM int FldCollision::boxCompute(dss::Fix32Vector3& nowPos, dss::Fix32Vector3& nextPos, dss::Fix32 rad, dss::Fix32Vector3* retVec)
{
    fx32 r;
    int polyNo;
    int surfaceId;
    unsigned int type;
    int ret;
    VecFx32 tpos, center, old_center, fixYPos;
    for (int i = 0; i < 22; i++) {
        surfaceType_[i] = -1;
        surfacePolyNo_[i] = -1;
    }
    searchObjectId_ = -1;
    searchPolyNo_ = -1;
    tpos = FldStage::getVecFx32(nowPos);
    center = FldStage::getVecFx32(nextPos);
    r = rad.value;
    polyNo = coll_GetNextMoveBox(g_fld->m_coll, &tpos, &center, r, &old_center);
    id_ = polyNo;
    int objNo = coll_GetObjId(g_fld->m_coll, polyNo);
    if (objNo != -1) {
        searchObjectId_ = objNo;
        searchPolyNo_ = polyNo;
    }
    surfaceId = coll_GetSurface(g_fld->m_coll, polyNo);
    if (surfaceId != -1) {
        type = (unsigned int)surfaceId >> 16;
        surfaceType_[type] = surfaceId;
        surfacePolyNo_[type] = polyNo;
    }
    fixYPos = old_center;
    ret = coll_SearchFloorPoly(g_fld->m_coll, &old_center, r, &fixYPos);
    if (ret >= 0) {
        floorPolygonNo_ = ret;
        if (coll_GetSurface(g_fld->m_coll, floorPolygonNo_) == -1 && surfaceType_[0] == -1) {
            surfaceType_[0] = 0;
            surfacePolyNo_[0] = floorPolygonNo_;
        }
    }
    *retVec = FldStage::getFx32Vector3(old_center);
    return polyNo;
}

ARM bool FldCollision::checkCrossPolygon(VecFx32& pos, VecFx32& pos1, int polyNo)
{
    bool ret = false;
    COLL_HEADER* header = g_fld->m_coll;
    if (header->poly[polyNo].flag & 1) {
        return ret;
    }
    VecFx32 dir;
    func_0208a1dc(&pos1, &pos, &dir);
    func_0208a330(&dir, &dir);
    fx32 len = func_0208a5d0(&pos, &pos1);
    fx32 tmp_len;
    if (coll_TriangleIntersect(&pos, &dir, &header->poly[polyNo], 0, &tmp_len, NULL, NULL)) {
        if (tmp_len <= len) {
            ret = true;
        }
    } else if ((header->poly[polyNo].type & 1) == 1) {
        if (coll_TriangleIntersect(&pos, &dir, &header->poly[polyNo], 1, &tmp_len, NULL, NULL)) {
            if (tmp_len <= len) {
                ret = true;
            }
        }
    }
    return ret;
}

ARM int FldCollision::getSurfaceByType(int type)
{
    return surfaceType_[type];
}

ARM int FldCollision::checkCrossNum(VecFx32& pos0, VecFx32& pos1, int notFloor)
{
    int no = 0;
    int count = 0;
    int floorCount = g_fld->m_coll->floor_poly_size;
    fx32 len;
    while ((no = g_fld->CollCrossCheck(&pos0, &pos1, no, &len)) != -1) {
        if (notFloor == true && no < floorCount) {
            no++;
            continue;
        }
        count++;
        no++;
    }
    return count;
}

ARM int FldCollision::checkCrossNumCheckUnder(VecFx32& pos0, VecFx32& pos1, int notFloor)
{
    int no = 0;
    int count = 0;
    int floorCount = g_fld->m_coll->floor_poly_size;
    fx32 len;
    while ((no = g_fld->CollCrossCheck(&pos0, &pos1, no, &len)) != -1) {
        if (notFloor == true && no < floorCount) {
            no++;
            continue;
        }
        if (len < 0) {
            no++;
        } else {
            count++;
            no++;
        }
    }
    return count;
}

ARM int FldCollision::checkCrossNumEraseSurface(VecFx32 pos0, VecFx32 pos1, int surface, int notFloor, int& polyNo)
{
    int no = 0;
    int count = 0;
    int floorCount = g_fld->m_coll->floor_poly_size;
    fx32 len;
    while ((no = g_fld->CollCrossCheck(&pos0, &pos1, no, &len)) != -1) {
        if (notFloor == true && no < floorCount) {
            no++;
            continue;
        }
        int polySurface = coll_GetSurface(g_fld->m_coll, no);
        if ((polySurface & 0xffff0000) == surface & 0xffff0000) {
            no++;
            continue;
        }
        if (len < 0) {
            no++;
        } else {
            polyNo = no;
            count++;
            no++;
        }
    }
    return count;
}

ARM bool FldCollision::getObjectPos(int objectID, int polyNo, dss::Fix32Vector3* pos)
{
    pos->vx = 0L;
    pos->vy = 0L;
    pos->vz = 0L;
    dss::Fix32Vector3 tpos[6];
    dss::Fix32Vector3 center;
    COLL_POLY* collPoly;
    int move = 1;
    int next = 0;
    int no = polyNo;
    int count = 0;
    dss::Fix32Vector3* tp;
    COLL_HEADER* header = g_fld->m_coll;
    int size = header->poly_size;
    if (polyNo == 0) {
        no = coll_GetPolyNoByMapObj(header, objectID, polyNo);
        if (no == -1) {
            return false;
        }
    }
    if (header->poly[no].obj_id != objectID || no >= size) {
        return false;
    }
    if (objectID == -1) {
        return false;
    }
    tp = tpos;
    while (true) {
        collPoly = &header->poly[no];
        if (objectID != collPoly->obj_id || no < 0 || no >= size || next == 2 || count == 4) {
            break;
        }
        center.set(0, 0, 0);
        if (collPoly->type & 1) {
            for (int i = 0; i < 4; i++) {
                center.vx.value += collPoly->vertex[i].x;
                center.vy.value += collPoly->vertex[i].y;
                center.vz.value += collPoly->vertex[i].z;
            }
            center /= 4;
        } else {
            for (int i = 0; i < 3; i++) {
                center.vx.value += collPoly->vertex[i].x;
                center.vy.value += collPoly->vertex[i].y;
                center.vz.value += collPoly->vertex[i].z;
            }
            center /= 3;
        }
        *tp = center;
        tp++;
        no += move;
        count++;
        if (no < size) {
            if (header->poly[no].obj_id != objectID) {
                next++;
                no = polyNo - 1;
                move = -1;
            }
        } else {
            next++;
            no = polyNo - 1;
            move = -1;
        }
    }
    if (count != 0) {
        for (int i = 0; i < count; i++) {
            tpos[i].vx /= count;
            tpos[i].vy /= count;
            tpos[i].vz /= count;
            *pos += tpos[i];
        }
    } else {
        return false;
    }
    return true;
}

ARM void FldCollision::searchFloorSurface(dss::Fix32Vector3& pos, dss::Fix32 radius, dss::Fix32 judgeLen, dss::Fix32Vector3& retVec)
{
    int no;
    unsigned int type;
    int tempSurfaceID;
    floorSurfaceId_ = -1;
    no = coll_SearchFloorPoly2(g_fld->m_coll, (VecFx32*)&pos, radius.value, 0, judgeLen.value, (VecFx32*)&retVec);
    while (no != -1) {
        tempSurfaceID = coll_GetSurface(g_fld->m_coll, no);
        if (tempSurfaceID != -1) {
            if (isEraseSurfaceId(tempSurfaceID) == false) {
                type = (unsigned int)tempSurfaceID >> 16;
                surfaceType_[type] = tempSurfaceID;
                surfacePolyNo_[type] = no;
                floorSurfaceId_ = tempSurfaceID;
            }
        } else if (surfaceType_[0] != 0) {
            surfaceType_[0] = 0;
            surfacePolyNo_[0] = floorPolygonNo_;
        }
        if (g_fld->m_coll->poly[no].uid != 0) {
            floorMapUid_ = g_fld->m_coll->poly[no].uid;
        }
        no = coll_SearchFloorPoly2(g_fld->m_coll, (VecFx32*)&pos, radius.value, no + 1, judgeLen.value, (VecFx32*)&retVec);
    }
}

ARM bool FldCollision::isAnimObject(int objectId)
{
    if (animObjectCheck_ == NULL) {
        return false;
    }
    return animObjectCheck_->isAnimObject(g_fld, objectId);
}

ARM void FldCollision::setEraseSurface(int surfaceId, bool flag)
{
    for (int i = 0; i < eraseSurfaceCount_; i++) {
        if (surfaceId == eraseSurfaceId_[i]) {
            if (flag == false) {
                eraseSurfaceId_[i] = -1;
                return;
            }
        } else if (eraseSurfaceId_[i] == -1 && flag == true) {
            eraseSurfaceId_[i] = surfaceId;
            return;
        }
    }
    if (flag == true) {
        eraseSurfaceId_[eraseSurfaceCount_] = surfaceId;
        eraseSurfaceCount_++;
    }
}

ARM void FldCollision::resetEraseSurface()
{
    eraseSurfaceCount_ = 0;
}

ARM bool FldCollision::isEraseSurfaceId(int surfaceId)
{
    for (int i = 0; i < eraseSurfaceCount_; i++) {
        if (surfaceId == eraseSurfaceId_[i]) {
            return true;
        }
    }
    return false;
}

ARM void FldCollision::wallPolyCheck(const dss::Fix32Vector3& newPos, COLL_POLY* poly, int start, int count)
{
    dss::Fix32Vector3 temp;
    VecFx32* bboxA;
    VecFx32* bboxB;
    VecFx32* normal;
    for (int i = start; i < count; i++) {
        COLL_POLY* p = &poly[i];
        bboxA = &p->bbox[0];
        bboxB = &p->bbox[1];
        normal = &p->normal;
        if (p->flag & 1) {
            continue;
        }
        if (newX < MATH_MIN(bboxA->x, bboxB->x) - preR || newX > preR + MATH_MAX(bboxA->x, bboxB->x)) {
            continue;
        }
        if (newZ < MATH_MIN(bboxA->z, bboxB->z) - preR || newZ > preR + MATH_MAX(bboxA->z, bboxB->z)) {
            continue;
        }
        if (newY < MATH_MIN(bboxA->y, bboxB->y) - radS || newY > radS + MATH_MAX(bboxA->y, bboxB->y)) {
            continue;
        }
        if (collCount < 30) {
            nextList[collCount] = p;
            collPolyNo[collCount] = i;
        }
        collCount++;
        if (func_0208a210(&dirVec32, normal) < 0) {
            continue;
        }
        if (coll_CheckLinePoint((VecFx32*)&newPos, radB, bboxA, bboxB, normal, (VecFx32*)&temp) == 0) {
            continue;
        }
        if (checkSignPoly(newPos, temp, i, p)) {
            crossCount++;
        }
    }
}

ARM int FldCollision::getFrontPoly(int polyNo, int objNo)
{
    COLL_POLY coll0;
    coll_GetPoly(g_fld->m_coll, polyNo, &coll0);
    dss::Fix32Vector3 normal0 = FldStage::getFx32Vector3(coll0.normal);
    int no = coll_GetPolyNoByMapObj(g_fld->m_coll, objNo, 0);
    while (no != -1) {
        COLL_POLY coll1;
        coll_GetPoly(g_fld->m_coll, no, &coll1);
        dss::Fix32Vector3 normal1 = FldStage::getFx32Vector3(coll1.normal);
        if ((normal0 * normal1).value < -0xf74) {
            return no;
        }
        no = coll_GetPolyNoByMapObj(g_fld->m_coll, objNo, no + 1);
    }
    return -1;
}

ARM bool FldCollision::isEraseHitSurface(int surfaceId)
{
    for (int i = 0; i < eraseCheckCount_; i++) {
        if (surfaceId == eraseCheckSurface_[i]) {
            return true;
        }
    }
    return false;
}
