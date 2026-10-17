#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

namespace fld
{
    struct FieldPlayerInfo {
        dss::Fix32Vector3 nowPos;               // 0x00
        dss::Fix32Vector3 nextPos;              // 0x0C
        short dirIdx;                           // 0x18
    };

    struct FieldCollInfo {
        dss::Fix32 collLine[4];                 // 0x00
        dss::Fix32 fixLine[4];                  // 0x10
        int blockColl[9];                       // 0x20
    };

    struct FieldActionCalculate {
        static short playerFixMove(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed);
        static short playerFixMoveUp(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed, bool flag);
        static short playerFixMoveRightUp(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed);
        static short playerFixMoveRight(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed, bool flag);
        static short playerFixMoveRightDown(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed);
        static short playerFixMoveDown(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed, bool flag);
        static short playerFixMoveLeftDown(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed);
        static short playerFixMoveLeft(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed, bool flag);
        static short playerFixMoveLeftUp(FieldPlayerInfo* info, FieldCollInfo* coll, int blkX, int blkY, dss::Fix32 speed);
        static void frontHitFix(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed);
        static void frontBlankFix(FieldPlayerInfo* info, FieldCollInfo* coll, dss::Fix32 speed);
        static int checkDiagonalLine(dss::Fix32Vector3& pos, int blkX, int blkY, int type);
        static short getDir8ByVector3(dss::Fix32Vector3& vec);
        static short getDir8RotIdx(short idx, int rot);
        static dss::Fix32Vector3 getVector3ByDir8(short dir);
        static int getIdxByParam4(int param);
        static bool isEnableGetOff(dss::Fix32Vector3& target);
    };
} // namespace fld
