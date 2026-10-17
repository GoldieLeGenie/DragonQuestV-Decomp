#include "ctrdg_internal.h"

#pragma thumb on

UnkCtrdgThread* data_0211dbe8;        /* task thread */
UnkCtrdgTask    data_0211dbec;
static u8       data_0211dc10[0x400]; /* task thread stack */

/* Starts the cartridge task thread. */
void func_02071fa8(UnkCtrdgThread* thread) {
    ENTER_CRITICAL_SECTION();
    if (data_0211dbe8 == NULL) {
        data_0211dbe8 = thread;
        func_0207200c(&thread->unk_c4);
        func_0207200c(&data_0211dbec);
        thread->unk_c0 = NULL;
        func_02087688(&thread->unk_00, func_02072018, thread, data_0211dc10 + sizeof(data_0211dc10), sizeof(data_0211dc10), 20);
        OS_WakeupThreadDirect(&thread->unk_00);
    }
    LEAVE_CRITICAL_SECTION();
}

void func_0207200c(UnkCtrdgTask* task) {
    MI_CpuSet(task, 0, sizeof(UnkCtrdgTask));
}

/* Cartridge task thread main loop. */
void func_02072018(void* arg) {
    UnkCtrdgThread* const thread = (UnkCtrdgThread*)arg;
    UnkCtrdgTask          task;

    for (;;) {
        u32 prevIRQState;

        MI_CpuSet(&task, 0, sizeof(task));

        prevIRQState = OS_DisableIRQ();
        while (thread->unk_c0 == NULL) {
            OS_PauseThread(NULL);
        }
        task = *thread->unk_c0;
        OS_RestoreIRQ(prevIRQState);

        if (task.unk_00 != NULL) {
            task.unk_08 = task.unk_00(&task);
        }

        prevIRQState = OS_DisableIRQ();
        {
            const UnkCtrdgTaskCallback callback = task.unk_04;
            data_0211dbec.unk_22         = 0;
            if (callback != NULL) {
                callback(&task);
            }
        }
        if (data_0211dbe8 == NULL) {
            break;
        }
        thread->unk_c0 = NULL;
        OS_RestoreIRQ(prevIRQState);
    }
    func_02087760();
}
