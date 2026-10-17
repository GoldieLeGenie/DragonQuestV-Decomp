#include "card_internal.h"

#pragma thumb on

typedef BOOL (*UnkCardPulledOutCallback)(void);

/* Card pull-out state (data_0211da00, 8 bytes). */
typedef struct UnkCardPullOut {
    /* 0x00 */ volatile BOOL            unk_00; /* card pulled out */
    /* 0x04 */ volatile UnkCardPulledOutCallback unk_04; /* user callback, return TRUE to terminate */
} UnkCardPullOut;

UnkCardPullOut data_0211da00;

void func_02071948(void) {
    func_0207734c();
    func_02077400(14, func_02071968);
    data_0211da00.unk_04 = NULL;
}

/* PXI callback of the pull-out FIFO tag. */
void func_02071968(u32 tag, u32 data, BOOL err) {
    if ((data & 0x3F) == 17) {
        UnkCardPullOut* const s = &data_0211da00;
        if (!s->unk_00) {
            BOOL                     terminate = TRUE;
            UnkCardPulledOutCallback callback;
            s->unk_00 = terminate;
            callback  = s->unk_04;
            if (callback != NULL) {
                terminate = callback();
            }
            if (terminate) {
                func_020719a8();
            }
        }
    } else {
        OS_Terminate();
    }
}

BOOL CARD_IsPulledOut(void) {
    return data_0211da00.unk_00;
}

/* Stops all DMA, waits for the power LED state and asks the ARM7 to shut down. */
void func_020719a8(void) {
    BOOL shutdown = TRUE;

    func_0206feb0(0);
    func_0206feb0(1);
    func_0206feb0(2);
    func_0206feb0(3);

    if ((*(u16*)0x027FFFA8 & 0x8000) >> 15) {
        u32 state = func_02078f20();
        while (state == 4) {
            OS_Delay(0xA3A47);
            state = func_02078f20();
        }
        if (state == 0) {
            shutdown = FALSE;
        }
    }
    if (shutdown) {
        func_02071a48(1, 1);
    }
    OS_Terminate();
}

/* Compares the current card ID with the one read at boot. */
void func_02071a08(u32 id) {
    vu32 boot_id = *(u32*)((*(u16*)0x027FFC10 == 0) ? 0x027FF800 : 0x027FFC00);
    if (id != boot_id) {
        ENTER_CRITICAL_SECTION();
        func_02071968(14, 17, FALSE);
        LEAVE_CRITICAL_SECTION();
    }
}

void func_02071a48(u32 data, s32 wait) {
    while (PXI_SendWordByFifo(14, data, FALSE) != 0) {
        WaitByLoop(wait);
    }
}
