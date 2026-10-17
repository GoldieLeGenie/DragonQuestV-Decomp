#include "g3d_f.h"

/* sends joint SRT (Softimage 3D classic scale) */
void func_02085320(const UnkJntAnmResult* result)
{
    BOOL trFlag = FALSE;
    u32 exFlag = result->flag & 0x18;

    if (exFlag == 0) {
        func_020826d0(0x1b, &result->scaleEx1, 3);
    }

    if (!(result->flag & 4)) {
        if (exFlag != 0) {
            trFlag = TRUE;
        } else {
            UnkVecFx32 tmp;
            tmp.x = UNK_MUL64(result->trans.x, result->scaleEx0.x);
            tmp.y = UNK_MUL64(result->trans.y, result->scaleEx0.y);
            tmp.z = UNK_MUL64(result->trans.z, result->scaleEx0.z);
            func_020826d0(0x1c, &tmp, 3);
        }
    }

    if (!(result->flag & 2)) {
        if (trFlag) {
            func_020826d0(0x19, &result->rot, 12);
        } else {
            func_020826d0(0x1a, &result->rot, 9);
        }
    } else {
        if (trFlag) {
            func_020826d0(0x1c, &result->trans, 3);
        }
    }

    if (exFlag == 0) {
        func_020826d0(0x1b, &result->scaleEx0, 3);
    }

    if (!(result->flag & 1)) {
        func_020826d0(0x1b, &result->scale, 3);
    }
}

/* joint scale (Softimage 3D classic scale) */
void func_0208544c(UnkJntAnmResult* result, const UnkVecFx32* p, const u8* data, u32 srtflag)
{
    u32 nodeID = data[1];
    u32 parentID = data[2];

    if (srtflag & 4) {
        result->flag |= 1;
        if (data_02124e18->isScaleCacheOne[parentID >> 5] & (1 << (parentID & 31))) {
            data_02124e18->isScaleCacheOne[nodeID >> 5] |= 1 << (nodeID & 31);
            result->flag |= 0x18;
        } else {
            MI_CpuCopyU32(&data_02124e1c.scaleCache[parentID], &data_02124e1c.scaleCache[nodeID], sizeof(UnkScaleCache));
            MI_CpuCopyU32(&data_02124e1c.scaleCache[parentID], &result->scaleEx0, sizeof(UnkScaleCache));
        }
    } else {
        result->scale.x = p->x;
        result->scale.y = p->y;
        result->scale.z = p->z;
        if (data_02124e18->isScaleCacheOne[parentID >> 5] & (1 << (parentID & 31))) {
            MI_CpuCopyU32(p, &data_02124e1c.scaleCache[nodeID], sizeof(UnkScaleCache));
            data_02124e18->isScaleCacheOne[nodeID >> 5] &= ~(1 << (nodeID & 31));
            result->flag |= 0x18;
        } else {
            data_02124e18->isScaleCacheOne[nodeID >> 5] &= ~(1 << (nodeID & 31));
            data_02124e1c.scaleCache[nodeID].s.x = UNK_MUL64(p[0].x, data_02124e1c.scaleCache[parentID].s.x);
            data_02124e1c.scaleCache[nodeID].s.y = UNK_MUL64(p[0].y, data_02124e1c.scaleCache[parentID].s.y);
            data_02124e1c.scaleCache[nodeID].s.z = UNK_MUL64(p[0].z, data_02124e1c.scaleCache[parentID].s.z);
            data_02124e1c.scaleCache[nodeID].inv.x = UNK_MUL64(p[1].x, data_02124e1c.scaleCache[parentID].inv.x);
            data_02124e1c.scaleCache[nodeID].inv.y = UNK_MUL64(p[1].y, data_02124e1c.scaleCache[parentID].inv.y);
            data_02124e1c.scaleCache[nodeID].inv.z = UNK_MUL64(p[1].z, data_02124e1c.scaleCache[parentID].inv.z);
            MI_CpuCopyU32(&data_02124e1c.scaleCache[parentID], &result->scaleEx0, sizeof(UnkScaleCache));
        }
    }
}

/* sends the texture matrix (Softimage 3D) */
void func_02085668(const UnkMatAnmResult* anm)
{
    UnkTexMtxCmd43 buf;

    if (anm->flag & 8) {
        buf.cmd = 0x101710;
    } else {
        buf.cmd = 0x101910;
    }
    buf.mtxMode = 3;
    buf.m.m[3][2] = 0;
    buf.m.m[2][2] = 0;
    buf.m.m[2][1] = 0;
    buf.m.m[2][0] = 0;
    buf.m.m[1][2] = 0;
    buf.m.m[1][0] = 0;
    buf.m.m[0][2] = 0;
    buf.m.m[0][1] = 0;
    buf.mtxMode2 = 2;

    if (anm->flag & 4) {
        buf.m.m[3][0] = 0;
        buf.m.m[3][1] = 0;
        if (anm->flag & 1) {
            buf.m.m[0][0] = 0x1000;
            buf.m.m[1][1] = 0x1000;
        } else {
            buf.m.m[0][0] = anm->scaleS;
            buf.m.m[1][1] = anm->scaleT;
        }
    } else if (anm->flag & 1) {
        buf.m.m[3][0] = -(anm->transS << 4) * anm->origW;
        buf.m.m[3][1] = -(anm->transT << 4) * anm->origH;
        buf.m.m[0][0] = 0x1000;
        buf.m.m[1][1] = 0x1000;
    } else {
        buf.m.m[3][0] = anm->origW * -UNK_MUL64_8(anm->scaleS, anm->transS);
        buf.m.m[3][1] = anm->origH * -UNK_MUL64_8(anm->scaleT, anm->transT);
        buf.m.m[0][0] = anm->scaleS;
        buf.m.m[1][1] = anm->scaleT;
    }

    if (anm->magW != 0x1000) {
        buf.m.m[0][0] = UNK_MUL64(anm->magW, buf.m.m[0][0]);
        buf.m.m[3][0] = UNK_MUL64(anm->magW, buf.m.m[3][0]);
    }
    if (anm->magH != 0x1000) {
        buf.m.m[1][1] = UNK_MUL64(anm->magH, buf.m.m[1][1]);
        buf.m.m[3][1] = UNK_MUL64(anm->magH, buf.m.m[3][1]);
    }

    func_020826d0(buf.cmd, (u32*)&buf + 1, 0xe);
}
