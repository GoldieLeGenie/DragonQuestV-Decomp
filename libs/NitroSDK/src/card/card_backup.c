#include "card_internal.h"

#pragma thumb on

/* Sets up the backup device parameters for a backup type. */
void func_02070d24(u32 type) {
    UnkCardCmd* const cmd = data_0211d1a0.unk_000;

    MI_CpuSet(&cmd->unk_18, 0, 0x48);
    cmd->unk_04 = type;
    cmd->unk_58 = 0x203F;

    if (type != 0) {
        const u32 size   = (u32)(1 << (((s32)type >> 8) & 0xFF));
        const u32 kind   = type & 0xFF;
        const u32 vendor = ((s32)type >> 16) & 0xFF;

        cmd->unk_18 = size;
        cmd->unk_54 = 0xFF;

        if (kind == 1) {
            switch (size) {
                case 0x200:
                    cmd->unk_24 = 0x10;
                    cmd->unk_28 = 1;
                    cmd->unk_2c = 5;
                    cmd->unk_54 = 0xF0;
                    break;
                case 0x2000:
                    cmd->unk_24 = 0x20;
                    cmd->unk_28 = 2;
                    cmd->unk_2c = 5;
                    cmd->unk_54 = 0;
                    break;
                case 0x10000:
                    cmd->unk_24 = 0x80;
                    cmd->unk_28 = 2;
                    cmd->unk_2c = 10;
                    cmd->unk_54 = 0;
                    break;
                default:
                    goto invalid;
            }
            cmd->unk_1c = cmd->unk_24;
            cmd->unk_58 |= 0x40;
            cmd->unk_58 |= 0x100;
            cmd->unk_58 |= 0x200;
            cmd->unk_58 |= 0x4000;
        } else if (kind == 2) {
            switch (size) {
                case 0x40000:
                case 0x80000:
                case 0x100000:
                    cmd->unk_30 = 25;
                    cmd->unk_34 = 300;
                    cmd->unk_50 = 300;
                    cmd->unk_40 = 5000;
                    cmd->unk_58 |= 0x80;
                    cmd->unk_58 |= 0x400;
                    break;
                case 0x200000:
                    cmd->unk_30 = 23;
                    cmd->unk_34 = 300;
                    cmd->unk_40 = 500;
                    cmd->unk_44 = 5000;
                    cmd->unk_38 = 10000;
                    cmd->unk_3c = 60000;
                    cmd->unk_54 = 0;
                    cmd->unk_58 |= 0x80;
                    cmd->unk_58 |= 0x400;
                    cmd->unk_58 |= 0x1000;
                    cmd->unk_58 |= 0x4000;
                    break;
                case 0x400000:
                    cmd->unk_40 = 600;
                    cmd->unk_44 = 3000;
                    cmd->unk_48 = 70;
                    cmd->unk_4c = 150;
                    cmd->unk_38 = 23000;
                    cmd->unk_3c = 800000;
                    cmd->unk_54 = 0;
                    cmd->unk_20 = 0x1000;
                    cmd->unk_58 |= 0x8000;
                    cmd->unk_58 |= 0x1000;
                    cmd->unk_58 |= 0x4000;
                    break;
                case 0x800000:
                    if (vendor == 0) {
                        cmd->unk_40 = 1000;
                        cmd->unk_44 = 3000;
                        cmd->unk_38 = 68000;
                        cmd->unk_3c = 160000;
                        cmd->unk_54 = 0;
                        cmd->unk_58 |= 0x1000;
                        cmd->unk_58 |= 0x4000;
                    } else if (vendor == 1) {
                        cmd->unk_40 = 1000;
                        cmd->unk_44 = 3000;
                        cmd->unk_38 = 68000;
                        cmd->unk_3c = 160000;
                        cmd->unk_54 = 0x84;
                        cmd->unk_58 |= 0x1000;
                        cmd->unk_58 |= 0x4000;
                    }
                    break;
                default:
                    goto invalid;
            }
            cmd->unk_1c = 0x10000;
            cmd->unk_24 = 0x100;
            cmd->unk_28 = 3;
            cmd->unk_2c = 5;
            cmd->unk_58 |= 0x40;
            cmd->unk_58 |= 0x100;
            cmd->unk_58 |= 0x200;
            cmd->unk_58 |= 0x800;
        } else if (kind == 3) {
            if (size != 0x2000 && size != 0x8000) {
                goto invalid;
            }
            cmd->unk_24 = size;
            cmd->unk_1c = size;
            cmd->unk_28 = 2;
            cmd->unk_54 = 0;
            cmd->unk_58 |= 0x40;
            cmd->unk_58 |= 0x100;
            cmd->unk_58 |= 0x200;
            cmd->unk_58 |= 0x4000;
        } else {
            goto invalid;
        }
    }
    return;

invalid:
    cmd->unk_18 = cmd->unk_04 = 0;
    data_0211d1a0.unk_000->unk_00 = 3;
}

/* Card thread task: transfers a backup request page by page. */
void func_02070f98(UnkCardCommon* p) {
    const u32 req   = p->unk_02c;
    const u32 mode  = p->unk_034;
    const u32 retry = p->unk_030;
    u32       page  = 0x100;

    func_02000be8(CARD_BACKUP_MARKER);
    if (req == 11) {
        page = func_020711cc();
    } else if (req == 15) {
        page = data_0211d1a0.unk_000->unk_20;
    }

    {
        for (;;) {
            const u32 len = (page < p->unk_024) ? page : p->unk_024;
            p->unk_000->unk_14 = len;

            if (p->unk_114 & 0x40) {
                p->unk_114 &= ~0x40;
                p->unk_000->unk_00 = 7;
                break;
            }

            switch (mode) {
                case 0:
                    DC_InvalidateRange(p->unk_120, len);
                    p->unk_000->unk_0c = p->unk_01c;
                    p->unk_000->unk_10 = (u32)p->unk_120;
                    break;
                case 1:
                case 2:
                    MI_CpuCopyU8((void*)p->unk_01c, p->unk_120, len);
                    DC_PurgeRange(p->unk_120, len);
                    DC_DrainWriteBuffer();
                    p->unk_000->unk_0c = (u32)p->unk_120;
                    p->unk_000->unk_10 = p->unk_020;
                    break;
                case 3:
                    p->unk_000->unk_0c = p->unk_01c;
                    p->unk_000->unk_10 = p->unk_020;
                    break;
            }

            if (!func_0207186c(p, req, retry)) {
                break;
            }
            if (mode == 2) {
                if (!func_0207186c(p, 9, 1)) {
                    break;
                }
            } else if (mode == 0) {
                MI_CpuCopyU8(p->unk_120, (void*)p->unk_020, len);
            }
            p->unk_01c += len;
            p->unk_020 += len;
            p->unk_024 -= len;
            if (p->unk_024 == 0) {
                break;
            }
        }
    }
    CARDi_EndTask(p);
}

BOOL CARD_ReadWriteBackupAsync(u32 src, u32 dst, u32 len, UnkCardCallback callback, void* arg, BOOL async, u32 req, u32 retry,
                   u32 mode) {
    UnkCardCommon* const p = &data_0211d1a0;

    func_02000be8(CARD_BACKUP_MARKER);
    CARDi_WaitAndLock(p, callback, arg);
    p->unk_01c = src;
    p->unk_020 = dst;
    p->unk_024 = len;
    p->unk_02c = req;
    p->unk_030 = retry;
    p->unk_034 = mode;
    if (async) {
        func_02070a90(func_02070f98);
        return TRUE;
    } else {
        data_0211d1a0.unk_104 = OS_GetCurrentThread();
        func_02070f98(p);
        return p->unk_000->unk_00 == 0;
    }
}

u32 func_020711cc(void) {
    return data_0211d1a0.unk_000->unk_1c;
}

BOOL CARD_IdentifyBackup(u32 type) {
    UnkCardCommon* const p = &data_0211d1a0;

    func_02000be8(CARD_BACKUP_MARKER);
    if (type == 0) {
        OS_Terminate();
    }
    func_02070c54();
    CARDi_WaitAndLock(p, NULL, NULL);
    func_02070d24(type);
    data_0211d1a0.unk_104 = OS_GetCurrentThread();
    func_0207186c(p, 2, 1);
    p->unk_000->unk_0c = 0;
    p->unk_000->unk_10 = (u32)p->unk_120;
    p->unk_000->unk_14 = 1;
    func_0207186c(p, 6, 1);
    CARDi_EndTask(p);
    return p->unk_000->unk_00 == 0;
}

BOOL func_020712d0(void) {
    return func_02070c70();
}

BOOL CARD_TryWaitBackupAsync(void) {
    return func_02070cac();
}
