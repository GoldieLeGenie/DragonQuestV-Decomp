#pragma ipa file
#include "ov005/fld/FieldActionCalculate.hpp"
#include "ov005/fld/FieldStage.hpp"

THUMB short fld::FieldActionCalculate::playerFixMove(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed)
{
    short ret;
    speed /= 2;
    switch (info->dirIdx) {
    case 0:
        ret = playerFixMoveUp(info, coll, speed, true);
        break;
    case 1:
        ret = playerFixMoveRightUp(info, coll, blkX, blkY, speed);
        break;
    case 2:
        ret = playerFixMoveRight(info, coll, speed, true);
        break;
    case 3:
        ret = playerFixMoveRightDown(info, coll, blkX, blkY, speed);
        break;
    case 4:
        ret = playerFixMoveDown(info, coll, speed, true);
        break;
    case 5:
        ret = playerFixMoveLeftDown(info, coll, blkX, blkY, speed);
        break;
    case 6:
        ret = playerFixMoveLeft(info, coll, speed, true);
        break;
    case 7:
        ret = playerFixMoveLeftUp(info, coll, blkX, blkY, speed);
        break;
    }
    return ret;
}

THUMB short fld::FieldActionCalculate::playerFixMoveUp(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed, bool flag)
{
    short ret = -1;
    dss::Fix32Vector3* positionN = &info->nextPos;
    if (coll->blockColl[0] == 0) {
        if (positionN->vy < coll->fixLine[0]) {
            if (info->dirIdx == 0) {
                frontHitFix(info, coll, speed);
            } else {
                info->dirIdx = info->dirIdx == 1 ? 2 : 6;
            }
        }
        if (positionN->vy < coll->collLine[0]) {
            ret = 0;
            positionN->vy = coll->collLine[0];
        }
    } else {
        switch (info->dirIdx) {
        case 0:
            if (positionN->vy < coll->collLine[0]) {
                frontBlankFix(info, coll, speed);
            }
            break;
        case 1:
            if ((coll->blockColl[1] == 0 && positionN->vy < coll->collLine[0] && flag == true) || (coll->blockColl[3] == 0 && info->nowPos.vy > coll->collLine[2]) || coll->blockColl[2] == 0) {
                if (positionN->vx > coll->collLine[1]) {
                    positionN->vx = coll->collLine[1];
                }
            }
            break;
        case 7:
            if ((coll->blockColl[7] == 0 && positionN->vy < coll->collLine[0] && flag == true) || (coll->blockColl[5] == 0 && info->nowPos.vy > coll->collLine[2]) || coll->blockColl[6] == 0) {
                if (positionN->vx < coll->collLine[3]) {
                    positionN->vx = coll->collLine[3];
                }
            }
            break;
        }
    }
    return ret;
}

THUMB short fld::FieldActionCalculate::playerFixMoveRight(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed, bool flag)
{
    short ret = -1;
    dss::Fix32Vector3* positionN = &info->nextPos;
    if (coll->blockColl[2] == 0) {
        if (positionN->vx > coll->fixLine[1]) {
            if (info->dirIdx == 2) {
                frontHitFix(info, coll, speed);
            } else {
                info->dirIdx = info->dirIdx == 1 ? 0 : 4;
            }
        }
        if (positionN->vx > coll->collLine[1]) {
            ret = 2;
            positionN->vx = coll->collLine[1];
        }
    } else {
        switch (info->dirIdx) {
        case 2:
            if (positionN->vx > coll->collLine[1]) {
                frontBlankFix(info, coll, speed);
            }
            break;
        case 1:
            if ((coll->blockColl[1] == 0 && positionN->vx > coll->collLine[1] && flag == true) || (coll->blockColl[7] == 0 && info->nowPos.vx < coll->collLine[3]) || coll->blockColl[0] == 0) {
                if (positionN->vy < coll->collLine[0]) {
                    positionN->vy = coll->collLine[0];
                }
            }
            break;
        case 3:
            if ((coll->blockColl[3] == 0 && positionN->vx > coll->collLine[1] && flag == true) || (coll->blockColl[5] == 0 && info->nowPos.vx < coll->collLine[3]) || coll->blockColl[4] == 0) {
                if (positionN->vy > coll->collLine[2]) {
                    positionN->vy = coll->collLine[2];
                }
            }
            break;
        }
    }
    return ret;
}

THUMB short fld::FieldActionCalculate::playerFixMoveDown(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed, bool flag)
{
    short ret = -1;
    dss::Fix32Vector3* positionN = &info->nextPos;
    if (coll->blockColl[4] == 0) {
        if (positionN->vy > coll->fixLine[2]) {
            if (info->dirIdx == 4) {
                frontHitFix(info, coll, speed);
            } else {
                info->dirIdx = info->dirIdx == 3 ? 2 : 6;
            }
        }
        if (positionN->vy > coll->collLine[2]) {
            positionN->vy = coll->collLine[2];
            ret = 4;
        }
    } else {
        switch (info->dirIdx) {
        case 4:
            if (positionN->vy > coll->collLine[2]) {
                frontBlankFix(info, coll, speed);
            }
            break;
        case 3:
            if ((coll->blockColl[3] == 0 && positionN->vy > coll->collLine[2] && flag == true) || (coll->blockColl[1] == 0 && info->nowPos.vy < coll->collLine[0]) || coll->blockColl[2] == 0) {
                if (positionN->vx > coll->collLine[1]) {
                    positionN->vx = coll->collLine[1];
                }
            }
            break;
        case 5:
            if ((coll->blockColl[5] == 0 && positionN->vy > coll->collLine[2] && flag == true) || (coll->blockColl[7] == 0 && info->nowPos.vy < coll->collLine[0]) || coll->blockColl[6] == 0) {
                if (positionN->vx < coll->collLine[3]) {
                    positionN->vx = coll->collLine[3];
                }
            }
            break;
        }
    }
    return ret;
}

THUMB short fld::FieldActionCalculate::playerFixMoveLeft(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed, bool flag)
{
    short ret = -1;
    dss::Fix32Vector3* positionN = &info->nextPos;
    if (coll->blockColl[6] == 0) {
        if (positionN->vx < coll->fixLine[3]) {
            if (info->dirIdx == 6) {
                frontHitFix(info, coll, speed);
            } else {
                info->dirIdx = info->dirIdx == 5 ? 4 : 0;
            }
        }
        if (positionN->vx < coll->collLine[3]) {
            positionN->vx = coll->collLine[3];
            ret = 6;
        }
    } else {
        switch (info->dirIdx) {
        case 6:
            if (positionN->vx < coll->collLine[3]) {
                frontBlankFix(info, coll, speed);
            }
            break;
        case 5:
            if ((coll->blockColl[5] == 0 && positionN->vx < coll->collLine[3] && flag == true) || (coll->blockColl[3] == 0 && info->nowPos.vx > coll->collLine[1]) || coll->blockColl[4] == 0) {
                if (positionN->vy > coll->collLine[2]) {
                    positionN->vy = coll->collLine[2];
                }
            }
            break;
        case 7:
            if ((coll->blockColl[7] == 0 && positionN->vx < coll->collLine[3] && flag == true) || (coll->blockColl[1] == 0 && info->nowPos.vx > coll->collLine[1]) || coll->blockColl[0] == 0) {
                if (positionN->vy < coll->collLine[0]) {
                    positionN->vy = coll->collLine[0];
                }
            }
            break;
        }
    }
    return ret;
}

THUMB short fld::FieldActionCalculate::playerFixMoveRightUp(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed)
{
    short ret;
    int side = checkDiagonalLine(info->nextPos, blkX + 1, blkY - 1, 2);
    if (side == 1) {
        ret = playerFixMoveUp(info, coll, speed, true);
        ret = playerFixMoveRight(info, coll, speed, true);
    } else {
        ret = playerFixMoveRight(info, coll, speed, true);
        ret = playerFixMoveUp(info, coll, speed, true);
    }
    return ret;
}

THUMB short fld::FieldActionCalculate::playerFixMoveRightDown(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed)
{
    short ret;
    int side = checkDiagonalLine(info->nextPos, blkX + 1, blkY + 1, 3);
    if (side == 1) {
        ret = playerFixMoveRight(info, coll, speed, true);
        ret = playerFixMoveDown(info, coll, speed, true);
    } else {
        ret = playerFixMoveDown(info, coll, speed, true);
        ret = playerFixMoveRight(info, coll, speed, true);
    }
    return ret;
}

THUMB short fld::FieldActionCalculate::playerFixMoveLeftDown(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed)
{
    short ret;
    int side = checkDiagonalLine(info->nextPos, blkX - 1, blkY + 1, 2);
    if (side == 1) {
        ret = playerFixMoveLeft(info, coll, speed, true);
        ret = playerFixMoveDown(info, coll, speed, true);
    } else {
        ret = playerFixMoveDown(info, coll, speed, true);
        ret = playerFixMoveLeft(info, coll, speed, true);
    }
    return ret;
}

THUMB short fld::FieldActionCalculate::playerFixMoveLeftUp(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed)
{
    short ret;
    int side = checkDiagonalLine(info->nextPos, blkX - 1, blkY - 1, 3);
    if (side == 1) {
        ret = playerFixMoveUp(info, coll, speed, true);
        ret = playerFixMoveLeft(info, coll, speed, true);
    } else {
        ret = playerFixMoveLeft(info, coll, speed, true);
        ret = playerFixMoveUp(info, coll, speed, true);
    }
    return ret;
}

THUMB void fld::FieldActionCalculate::frontHitFix(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed)
{
    switch (info->dirIdx) {
    case 0:
        if (info->nextPos.vx < coll->fixLine[3] && coll->blockColl[7] == 1) {
            info->nextPos.vx = info->nowPos.vx - speed;
            info->dirIdx = 6;
        } else if (info->nextPos.vx > coll->fixLine[1] && coll->blockColl[1] == 1) {
            info->nextPos.vx = info->nowPos.vx + speed;
            info->dirIdx = 2;
        }
        break;
    case 2:
        if (info->nextPos.vy < coll->fixLine[0] && coll->blockColl[1] == 1) {
            info->nextPos.vy = info->nowPos.vy - speed;
            info->dirIdx = 0;
        } else if (info->nextPos.vy > coll->fixLine[2] && coll->blockColl[3] == 1) {
            info->nextPos.vy = info->nowPos.vy + speed;
            info->dirIdx = 4;
        }
        break;
    case 4:
        if (info->nextPos.vx < coll->fixLine[3] && coll->blockColl[5] == 1) {
            info->nextPos.vx = info->nowPos.vx - speed;
            info->dirIdx = 6;
        } else if (info->nextPos.vx > coll->fixLine[1] && coll->blockColl[3] == 1) {
            info->nextPos.vx = info->nowPos.vx + speed;
            info->dirIdx = 2;
        }
        break;
    case 6:
        if (info->nextPos.vy < coll->fixLine[0] && coll->blockColl[7] == 1) {
            info->nextPos.vy = info->nowPos.vy - speed;
            info->dirIdx = 0;
        } else if (info->nextPos.vy > coll->fixLine[2] && coll->blockColl[5] == 1) {
            info->nextPos.vy = info->nowPos.vy + speed;
            info->dirIdx = 4;
        }
        break;
    }
}

THUMB void fld::FieldActionCalculate::frontBlankFix(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed)
{
    switch (info->dirIdx) {
    case 0:
        if (info->nextPos.vx > coll->fixLine[1] && coll->blockColl[1] == 0) {
            info->nextPos.vy = coll->collLine[0];
            info->nextPos.vx = info->nowPos.vx - speed;
            info->dirIdx = 6;
        } else if (info->nextPos.vx < coll->fixLine[3] && coll->blockColl[7] == 0) {
            info->nextPos.vy = coll->collLine[0];
            info->nextPos.vx = info->nowPos.vx + speed;
            info->dirIdx = 2;
        }
        break;
    case 2:
        if (info->nextPos.vy < coll->fixLine[0] && coll->blockColl[1] == 0) {
            info->nextPos.vx = coll->collLine[1];
            info->nextPos.vy = info->nowPos.vy + speed;
            info->dirIdx = 4;
        } else if (info->nextPos.vy > coll->fixLine[2] && coll->blockColl[3] == 0) {
            info->nextPos.vx = coll->collLine[1];
            info->nextPos.vy = info->nowPos.vy - speed;
            info->dirIdx = 0;
        }
        break;
    case 4:
        if (info->nextPos.vx > coll->fixLine[1] && coll->blockColl[3] == 0) {
            info->nextPos.vy = coll->collLine[2];
            info->nextPos.vx = info->nowPos.vx - speed;
            info->dirIdx = 6;
        } else if (info->nextPos.vx < coll->fixLine[3] && coll->blockColl[5] == 0) {
            info->nextPos.vy = coll->collLine[2];
            info->nextPos.vx = info->nowPos.vx + speed;
            info->dirIdx = 2;
        }
        break;
    case 6:
        if (info->nextPos.vy < coll->fixLine[0] && coll->blockColl[7] == 0) {
            info->nextPos.vx = coll->collLine[3];
            info->nextPos.vy = info->nowPos.vy + speed;
            info->dirIdx = 4;
        } else if (info->nextPos.vy > coll->fixLine[2] && coll->blockColl[5] == 0) {
            info->nextPos.vx = coll->collLine[3];
            info->nextPos.vy = info->nowPos.vy - speed;
            info->dirIdx = 0;
        }
        break;
    }
}

THUMB int fld::FieldActionCalculate::checkDiagonalLine(dss::Fix32Vector3& pos, int blkX, int blkY, int type)
{
    dss::Fix32Vector3 point[4];
    dss::Fix32Vector3 vec;
    dss::Fix32Vector3 normal;
    dss::Fix32 dot;
    point[0] = dss::Fix32Vector3(blkX << 4, blkY << 4, 0);
    point[1] = dss::Fix32Vector3((blkX << 4) + 0x10, blkY << 4, 0);
    point[2] = dss::Fix32Vector3((blkX << 4) + 0x10, (blkY << 4) + 0x10, 0);
    point[3] = dss::Fix32Vector3(blkX << 4, (blkY << 4) + 0x10, 0);
    if (type == 2) {
        normal = point[0] - point[2];
        vec = pos - point[3];
        dot = vec * normal;
        if (dot == dss::Fix32(0L)) {
            return 0;
        }
        if (dot > dss::Fix32(0L)) {
            return 1;
        }
        return -1;
    }
    if (type == 3) {
        normal = point[1] - point[3];
        vec = pos - point[0];
        dot = vec * normal;
        if (dot == dss::Fix32(0L)) {
            return 0;
        }
        if (dot > dss::Fix32(0L)) {
            return 1;
        }
        return -1;
    }
    return -2;
}

THUMB short fld::FieldActionCalculate::getDir8ByVector3(dss::Fix32Vector3& vec)
{
    static const dss::Fix32 cosPAI_1_8 = 0.9238f;
    static const dss::Fix32 cosPAI_3_8 = 0.3826f;
    dss::Fix32Vector3 tempVec = vec;
    int retIdx;
    tempVec.normalize();
    if (tempVec.vy <= dss::Fix32(0L)) {
        if (tempVec.vx >= cosPAI_1_8) {
            retIdx = 2;
        } else if (tempVec.vx >= cosPAI_3_8) {
            retIdx = 1;
        } else if (tempVec.vx >= cosPAI_3_8 * -1) {
            retIdx = 0;
        } else if (tempVec.vx >= cosPAI_1_8 * -1) {
            retIdx = 7;
        } else {
            retIdx = 6;
        }
        return retIdx;
    }
    {
        if (tempVec.vx >= cosPAI_1_8) {
            retIdx = 2;
        } else if (tempVec.vx >= cosPAI_3_8) {
            retIdx = 3;
        } else if (tempVec.vx >= cosPAI_3_8 * -1) {
            retIdx = 4;
        } else if (tempVec.vx >= cosPAI_1_8 * -1) {
            retIdx = 5;
        } else {
            retIdx = 6;
        }
    }
    return retIdx;
}

THUMB short fld::FieldActionCalculate::getDir8RotIdx(short idx, int rot)
{
    short ret = idx;
    int next = rot < 0 ? -1 : 1;
    while (rot != 0) {
        ret += next;
        if (ret < 0) {
            ret = 7;
        } else if (ret > 7) {
            ret = 0;
        }
        rot -= next;
    }
    return ret;
}

THUMB dss::Fix32Vector3 fld::FieldActionCalculate::getVector3ByDir8(short dir)
{
    static const dss::Fix32Vector3 retVec[8] = {
        dss::Fix32Vector3(0.0f, -1.0f, 0.0f),
        dss::Fix32Vector3(0.7f, -0.7f, 0.0f),
        dss::Fix32Vector3(1.0f, 0.0f, 0.0f),
        dss::Fix32Vector3(0.7f, 0.7f, 0.0f),
        dss::Fix32Vector3(0.0f, 1.0f, 0.0f),
        dss::Fix32Vector3(-0.7f, 0.7f, 0.0f),
        dss::Fix32Vector3(-1.0f, 0.0f, 0.0f),
        dss::Fix32Vector3(-0.7f, -0.7f, 0.0f),
    };
    return retVec[dir];
}

THUMB int fld::FieldActionCalculate::getIdxByParam4(int param)
{
    switch (param) {
    case 0:
        return 4;
    case 1:
        return 2;
    case 2:
        return 0;
    case 4:
        return 6;
    }
    return 4;
}

THUMB bool fld::FieldActionCalculate::isEnableGetOff(dss::Fix32Vector3& target)
{
    return FieldStage::getSingleton()->getBlockAttr(target.vx.value / 0x10000, target.vy.value / 0x10000);
}
