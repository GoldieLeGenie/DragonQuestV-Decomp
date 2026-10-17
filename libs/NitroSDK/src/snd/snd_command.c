#include "snd_internal.h"

#pragma thumb on

/* Command manager state: separate file statics (each one gets its own alias class, which lets the
   scheduler move the command-table load past the recvIndex store). The definition order gives the
   .bss layout under -ipa file. */
static u32            data_0211e1e4; /* finished tag */
static u32            data_0211e200; /* current tag */
static UnkSndCommand* data_0211e1f0; /* free list end */
static UnkSndCommand* data_0211e1e8; /* reserve list */
static UnkSndCommand* data_0211e1e0; /* free list */
static UnkSndCommand* data_0211e1ec; /* reserve list end */
static s32            data_0211e1f4; /* receive index */
static s32            data_0211e1f8; /* send index */
static s32            data_0211e1fc; /* send count */
static UnkSndCommand* data_0211e204[9];
static UnkSndSharedWork data_0211e240 __attribute__((aligned(32)));
static UnkSndCommand data_0211e4c0[256] __attribute__((aligned(32)));
extern UnkSndSharedWork* data_0211fd20;


void func_02077d04(void) {
    s32 i;

    func_020780e8();
    data_0211e1e0 = data_0211e4c0;
    for (i = 0; i < 255; i++) {
        data_0211e4c0[i].next = &data_0211e4c0[i + 1];
    }
    data_0211e4c0[255].next = NULL;
    data_0211e1f0 = &data_0211e4c0[255];
    data_0211e1e8 = NULL;
    data_0211e1ec = NULL;
    data_0211e1fc = 0;
    data_0211e1f4 = 0;
    data_0211e1f8 = 0;
    data_0211e200 = 1;
    data_0211e1e4 = 0;
    data_0211fd20 = &data_0211e240;
    func_02078270(&data_0211e240);

    {
        UnkSndCommand* cmd = func_02077e34(1);
        if (cmd == NULL) {
            return;
        }
        cmd->id = 29;
        cmd->arg[0] = (u32)data_0211fd20;
        func_02077e90(cmd);
        func_02077eb8(1);
    }
}

UnkSndCommand* func_02077d8c(u32 flags) {
    u32 enabled = OS_DisableIRQ();
    UnkSndCommand* head;
    UnkSndCommand* tail;

    if (flags & 1) {
        while (data_0211e1e4 == func_02078258()) {
            OS_RestoreIRQ(enabled);
            OS_Delay(100);
            enabled = OS_DisableIRQ();
        }
    } else if (data_0211e1e4 == func_02078258()) {
        OS_RestoreIRQ(enabled);
        return NULL;
    }

    head = data_0211e204[data_0211e1f4];
    data_0211e1f4++;
    if (data_0211e1f4 > 8) {
        data_0211e1f4 = 0;
    }

    tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    if (data_0211e1f0 != NULL) {
        data_0211e1f0->next = head;
    } else {
        data_0211e1e0 = head;
    }
    data_0211e1f0 = tail;
    data_0211e1fc--;
    data_0211e1e4++;

    OS_RestoreIRQ(enabled);
    return head;
}

UnkSndCommand* func_02077e34(u32 flags) {
    UnkSndCommand* cmd;

    if (!func_0207816c()) {
        return NULL;
    }
    cmd = func_0207813c();
    if (cmd != NULL) {
        return cmd;
    }
    if (!(flags & 1)) {
        return NULL;
    }

    if (func_020780b8() > 0) {
        while (func_02077d8c(0) != NULL) {
        }
        cmd = func_0207813c();
        if (cmd != NULL) {
            return cmd;
        }
    } else {
        func_02077eb8(1);
    }

    func_02078124();
    do {
        func_02077d8c(1);
        cmd = func_0207813c();
    } while (cmd == NULL);
    return cmd;
}

void func_02077e90(UnkSndCommand* cmd) {
    u32 enabled = OS_DisableIRQ();

    if (data_0211e1ec == NULL) {
        data_0211e1e8 = cmd;
        data_0211e1ec = cmd;
    } else {
        data_0211e1ec->next = cmd;
        data_0211e1ec = cmd;
    }
    cmd->next = NULL;

    OS_RestoreIRQ(enabled);
}

BOOL func_02077eb8(u32 flags) {
    u32 enabled = OS_DisableIRQ();

    if (data_0211e1e8 == NULL) {
        OS_RestoreIRQ(enabled);
        return TRUE;
    }

    if (data_0211e1fc >= 8) {
        if (!(flags & 1)) {
            OS_RestoreIRQ(enabled);
            return FALSE;
        }
        do {
            func_02077d8c(1);
        } while (data_0211e1fc >= 8);

        if (data_0211e1e8 == NULL) {
            OS_RestoreIRQ(enabled);
            return TRUE;
        }
    }

    DC_PurgeRange(data_0211e4c0, sizeof(data_0211e4c0));
    if (PXI_SendWordByFifo(7, (u32)data_0211e1e8, FALSE) < 0) {
        if (!(flags & 1)) {
            OS_RestoreIRQ(enabled);
            return FALSE;
        }
        while (data_0211e1fc >= 8 || PXI_SendWordByFifo(7, (u32)data_0211e1e8, FALSE) < 0) {
            OS_RestoreIRQ(enabled);
            func_02077d8c(0);
            enabled = OS_DisableIRQ();
            DC_PurgeRange(data_0211e4c0, sizeof(data_0211e4c0));
            if (data_0211e1e8 == NULL) {
                OS_RestoreIRQ(enabled);
                return TRUE;
            }
        }
    }

    data_0211e204[data_0211e1f8] = data_0211e1e8;
    data_0211e1f8++;
    if (data_0211e1f8 > 8) {
        data_0211e1f8 = 0;
    }
    data_0211e1e8 = NULL;
    data_0211e1ec = NULL;
    data_0211e1fc++;
    data_0211e200++;

    OS_RestoreIRQ(enabled);

    if (flags & 2) {
        func_02078124();
    }
    return TRUE;
}

void func_02077fcc(u32 tag) {
    if (func_02078030(tag)) {
        return;
    }
    while (func_02077d8c(0) != NULL) {
    }
    if (func_02078030(tag)) {
        return;
    }
    func_02078124();
    if (func_02078030(tag)) {
        return;
    }
    do {
        func_02077d8c(1);
    } while (!func_02078030(tag));
}

u32 func_02078010(void) {
    u32 tag;
    u32 enabled = OS_DisableIRQ();

    if (data_0211e1e8 == NULL) {
        tag = data_0211e1e4;
    } else {
        tag = data_0211e200;
    }
    OS_RestoreIRQ(enabled);
    return tag;
}

BOOL func_02078030(u32 tag) {
    BOOL result;
    u32 enabled = OS_DisableIRQ();

    if (tag > data_0211e1e4) {
        if (tag - data_0211e1e4 < 0x80000000) {
            result = FALSE;
        } else {
            result = TRUE;
        }
    } else {
        if (data_0211e1e4 - tag < 0x80000000) {
            result = TRUE;
        } else {
            result = FALSE;
        }
    }
    OS_RestoreIRQ(enabled);
    return result;
}

s32 func_02078070(void) {
    u32 enabled = OS_DisableIRQ();
    s32 count = 0;
    UnkSndCommand* cmd;

    for (cmd = data_0211e1e0; cmd != NULL; cmd = cmd->next) {
        count++;
    }
    OS_RestoreIRQ(enabled);
    return count;
}

s32 func_02078094(void) {
    u32 enabled = OS_DisableIRQ();
    s32 count = 0;
    UnkSndCommand* cmd;

    for (cmd = data_0211e1e8; cmd != NULL; cmd = cmd->next) {
        count++;
    }
    OS_RestoreIRQ(enabled);
    return count;
}

s32 func_020780b8(void) {
    s32 freeCount = func_02078070();
    s32 reserveCount = func_02078094();
    return 256 - freeCount - reserveCount;
}

void func_020780d0(u32 tag, u32 data, BOOL err) {
    u32 enabled = OS_DisableIRQ();
    func_020781ec(data);
    OS_RestoreIRQ(enabled);
}

void func_020780e8(void) {
    func_02077400(7, func_020780d0);
    if (!func_0207816c()) {
        return;
    }
    while (!func_0207744c(7, 1)) {
        OS_Delay(100);
    }
}

void func_02078124(void) {
    while (PXI_SendWordByFifo(7, 0, FALSE) < 0) {
    }
}

UnkSndCommand* func_0207813c(void) {
    UnkSndCommand* cmd;
    u32 enabled = OS_DisableIRQ();

    cmd = data_0211e1e0;
    if (cmd == NULL) {
        OS_RestoreIRQ(enabled);
        return NULL;
    }
    data_0211e1e0 = cmd->next;
    if (data_0211e1e0 == NULL) {
        data_0211e1f0 = NULL;
    }
    OS_RestoreIRQ(enabled);
    return cmd;
}

BOOL func_0207816c(void) {
    u32 enabled;
    u32 result;

    if (!func_02087ad8()) {
        return TRUE;
    }
    enabled = OS_DisableIRQ();
    *(vu32*)0x04fff200 = 0x10;
    result = *(vu32*)0x04fff200;
    OS_RestoreIRQ(enabled);
    return result ? TRUE : FALSE;
}
