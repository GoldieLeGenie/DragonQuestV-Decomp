#include "g3d_f.h"

#pragma thumb on

/* sends joint SRT (basic scaling) */
void func_02084b4c(const UnkJntAnmResult* result)
{
    if (!(result->flag & 4)) {
        if (!(result->flag & 2)) {
            func_020826d0(0x19, &result->rot, 12);
        } else {
            func_020826d0(0x1c, &result->trans, 3);
        }
    } else {
        if (!(result->flag & 2)) {
            func_020826d0(0x1a, &result->rot, 9);
        }
    }

    if (!(result->flag & 1)) {
        func_020826d0(0x1b, &result->scale, 3);
    }
}

/* joint scale (basic scaling) */
void func_02084ba0(UnkJntAnmResult* result, const UnkVecFx32* p, const u8* data, u32 srtflag)
{
    if (srtflag & 4) {
        result->flag |= 1;
    } else {
        result->scale.x = p->x;
        result->scale.y = p->y;
        result->scale.z = p->z;
    }
    result->flag |= 0x18;
}
