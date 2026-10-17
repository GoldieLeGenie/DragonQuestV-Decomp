#pragma ipa file
#include "main/cmn/CommonCalculate.hpp"
#include "main/dss/UnkMatrix43.hpp"
#include <nitro/fx/fx_atan.h>

// dead-stripped unkfunc_unused_0208d690
static const short unk_0208d690 = 0x1000;

static const short checkDir[8] = {0x0000, 0x2000, 0x4000, 0x6000, (short)0x8000, (short)0xa000, (short)0xc000, (short)0xe000};

THUMB void cmn::CommonCalculate::getDirByIdx(short dir, dss::Fix32Vector3& vec)
{
    vec.set(0, 0, 0x1000);
    dss::UnkMatrix43 mtx;
    mtx.unkfunc_0204f4ec(dir);
    vec = mtx * vec;
}

THUMB bool cmn::CommonCalculate::simpleAreaInCheck(dss::Fix32Vector3& min, dss::Fix32Vector3& max, dss::Fix32Vector3 pos)
{
    if (min.vx <= pos.vx && max.vx >= pos.vx && min.vy <= pos.vy && max.vy >= pos.vy && min.vz <= pos.vz && max.vz >= pos.vz) {
        return true;
    }
    return false;
}

THUMB bool cmn::CommonCalculate::areaCheck(dss::Fix32Vector3& pos, short dir, dss::Fix32Vector3& min, dss::Fix32Vector3& max, int check, int type)
{
    if (min.vx < pos.vx && max.vx > pos.vx && min.vy < pos.vy && max.vy > pos.vy && min.vz < pos.vz && max.vz > pos.vz) {
        if (type == 7) {
            return false;
        }
        if (check == 0) {
            return true;
        }
    } else {
        if (type == 6) {
            return false;
        }
        if (check == 0) {
            return true;
        }
    }
    dss::Fix32Vector3 diff = (min + max) / 2 - pos;
    dss::Fix32Vector3 dirVec;
    switch (check) {
        case 1:
            getDirByIdx(dir, dirVec);
            break;
        case 2:
            dirVec.set(0, 0, 0x1000);
            break;
        case 3:
            dirVec.set(0x1000, 0, 0);
            break;
        case 4:
            dirVec.set(0, 0, -0x1000);
            break;
        case 5:
            dirVec.set(-0x1000, 0, 0);
            break;
    }
    dss::Fix32 dot = dirVec * diff;
    if (check == 1) {
        if ((dot > dss::Fix32(0L) && type == 6) || (dot < dss::Fix32(0L) && type == 7)) {
            return true;
        }
    } else if (dot > dss::Fix32(0L)) {
        return true;
    }
    return false;
}

THUMB bool cmn::CommonCalculate::directionCheckByScriptParam(int param, short dir)
{
    if (param != 4) {
        int ret = 0;
        short check = checkDir[param];
        if (check - 0x1000 <= dir && dir < check + 0x1000) {
            ret = 1;
        }
        if (ret) {
            return true;
        }
        return false;
    }
    if (dir >= 0x7000 || dir < -0x7000) {
        return true;
    }
    return false;
}

THUMB int cmn::CommonCalculate::getFrameByVector(dss::Fix32Vector3& start, dss::Fix32Vector3& target, dss::Fix32 speed)
{
    if (speed == dss::Fix32(0L)) {
        return 0;
    }
    return dss::max<int>(((target - start) / speed).length().value / 0x1000, 1);
}

THUMB dss::Fix32Vector3 cmn::CommonCalculate::setVecByParam(int x, int y, int z)
{
    dss::Fix32Vector3 vec;
    vec.vx.value = x;
    vec.vy.value = y;
    vec.vz.value = z;
    return vec;
}

THUMB short cmn::CommonCalculate::getIdxByParam(unsigned char param)
{
    switch (param) {
        case 0:
            return 0;
        case 1:
            return 0x4000;
        case 2:
            return (short)0x8000;
        case 3:
            return (short)0xc000;
    }
    return 0;
}

THUMB dss::Fix32Vector3 cmn::CommonCalculate::getAxisMoveTargetByParam(unsigned int axis, unsigned int type, int value, dss::Fix32Vector3& base)
{
    dss::Fix32Vector3 target(base);
    dss::Fix32 add;
    add.value = value;
    if (type == 1) {
        switch (axis) {
            case 0:
                target.vx += add;
                break;
            case 1:
                target.vy += add;
                break;
            case 2:
                target.vz += add;
                break;
        }
    } else if (type == 0) {
        switch (axis) {
            case 0:
                target.vx = add;
                break;
            case 1:
                target.vy = add;
                break;
            case 2:
                target.vz = add;
                break;
        }
    }
    return target;
}

THUMB void cmn::CommonCalculate::getIdxByVec(short& idx, dss::Fix32Vector3& vec)
{
    bool zero = false;
    if (vec.vx == dss::Fix32(0L)) {
        if (vec.vz == dss::Fix32(0L)) {
            zero = true;
        }
    }
    if (!zero) {
        idx = FX_Atan2Idx(vec.vx.value, vec.vz.value);
    }
}

THUMB const short* unkfunc_unused_0208d690()
{
    return &unk_0208d690;
}
