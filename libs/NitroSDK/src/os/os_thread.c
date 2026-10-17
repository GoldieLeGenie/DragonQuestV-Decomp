#include "os_internal.h"
#include <nitro/os/mutex.h>
#include <nitro/os/thread.h>

#pragma thumb on

#define STACK_BOTTOM_MAGIC 0xFDDB597D
#define STACK_TOP_MAGIC    0x7BF9DD5B

#define THREAD_STATE_WAITING    0
#define THREAD_STATE_READY      1
#define THREAD_STATE_TERMINATED 2

#define IDLE_THREAD_STACK_SIZE 200
#define IDLE_THREAD_PRIORITY   0x20
#define LAUNCHER_PRIORITY      0x10

#define REG_THREAD_INFO_PTR (*(OSThreadInfo**)0x027fffa0)

extern char unk_IrqStackSize[];   // linker constant (0x1000)
extern char unk_SysStackSize[];   // linker constant (0)
extern char unk_DtcmArenaStart[]; // linker constant (0x027e0080)

void      OSi_ExitThread_ArgSpecified(OSThread* thread, void* arg);
void      func_02087534(void);
OSThread* func_020878b8(void);
void      func_020878d0(void);
OSThreadSwitchCallback func_0208794c(OSThreadSwitchCallback callback);
void      func_02087968(void* arg);
u32       func_02087974(void);
u32       func_02087998(void);
void      func_020879bc(OSThread* thread, OSThreadDestructor destructor);
void      func_020879c4(OSContext* context, void (*func)(void*), void* sp);
void      func_02087688(OSThread* thread, void (*func)(void*), void* arg, void* stack, u32 stackSize, u32 prio);
void      func_02087760(void);
void      func_020877b4(void* arg);
void      func_020877dc(void);
s32       OS_SaveContext(OSContext* context);
void      OS_LoadContext(OSContext* context);

// Thread system globals (definition order chosen for the .bss layout: the compiler sorts the objects by size)
u32                    data_02127be0;  // used only by code that is not linked into the ROM
s32                    data_02127bf0;  // thread id counter
u32                    data_02127bd4;  // reschedule counter
OSThread**             data_02127bd8;  // current thread pointer
OSThreadSwitchCallback data_02127bd0;  // thread switch callback
BOOL                   data_02127bdc;  // initialized
u32                    data_02127be4;  // used only by code that is not linked into the ROM
u32                    data_02127be8;  // used only by code that is not linked into the ROM
void*                  data_02127bec;  // destructor stack
OSThreadInfo           ThreadInfo;
OSThread               data_02127cc4;  // launcher thread
OSThread               data_02127c04;  // idle thread
u32                    data_02127d84[IDLE_THREAD_STACK_SIZE / sizeof(u32)]; // idle thread stack

s32 OSi_GetUnusedThreadId(void) {
    return ++data_02127bf0;
}

void OSi_InsertLinkToQueue(OSThreadQueue* queue, OSThread* thread) {
    OSThread* next = queue->head;

    while (next != NULL && next->priority <= thread->priority) {
        if (next == thread) {
            return;
        }
        next = next->list.next;
    }

    if (next == NULL) {
        OSThread* prev = queue->tail;

        if (prev == NULL) {
            queue->head = thread;
        } else {
            prev->list.next = thread;
        }

        thread->list.prev = prev;
        thread->list.next = NULL;
        queue->tail       = thread;
    } else {
        OSThread* prev = next->list.prev;

        if (prev == NULL) {
            queue->head = thread;
        } else {
            prev->list.next = thread;
        }

        thread->list.prev = prev;
        thread->list.next = next;
        next->list.prev   = thread;
    }
}

OSThread* OSi_RemoveLinkFromQueue(OSThreadQueue* queue) {
    OSThread* thread = queue->head;

    if (thread != NULL) {
        OSThread* next = thread->list.next;

        queue->head = next;
        if (next != NULL) {
            next->list.prev = NULL;
        } else {
            queue->tail   = NULL;
            thread->queue = NULL;
        }
    }
    return thread;
}

OSThread* OSi_RemoveSpecifiedLinkFromQueue(OSThreadQueue* queue, OSThread* thread) {
    OSThread* t = queue->head;

    while (t != NULL) {
        OSThread* next = t->list.next;

        if (t == thread) {
            OSThread* prev = t->list.prev;

            if (queue->head == t) {
                queue->head = next;
            } else {
                prev->list.next = next;
            }

            if (queue->tail == t) {
                queue->tail = prev;
            } else {
                next->list.prev = prev;
            }
            break;
        }

        t = next;
    }

    return t;
}

OSMutex* OS_RemoveMutexFromQueue(OSMutexQueue* queue) {
    OSMutex* mutex = queue->head;

    if (mutex != NULL) {
        OSMutex* next = mutex->list.next;

        queue->head = next;
        if (next != NULL) {
            next->list.prev = NULL;
        } else {
            queue->tail = NULL;
        }
    }
    return mutex;
}

// Inserts a thread in the priority-sorted thread list
void func_020874d0(OSThread* thread) {
    OSThread* t   = ThreadInfo.list;
    OSThread* pre = NULL;

    while (t != NULL && t->priority < thread->priority) {
        pre = t;
        t   = t->next;
    }

    if (pre == NULL) {
        thread->next    = ThreadInfo.list;
        ThreadInfo.list = thread;
    } else {
        thread->next = pre->next;
        pre->next    = thread;
    }
}

// Removes a thread from the thread list
void func_02087508(OSThread* thread) {
    OSThread* t   = ThreadInfo.list;
    OSThread* pre = NULL;

    while (t != NULL && t != thread) {
        pre = t;
        t   = t->next;
    }

    if (pre == NULL) {
        ThreadInfo.list = thread->next;
    } else {
        pre->next = thread->next;
    }
}

// Switches to the highest priority ready thread
void func_02087534(void) {
    if (data_02127bd4 <= 0) {
        OSThreadInfo* info = &ThreadInfo;
        OSThread*     current;
        OSThread*     next;

        if (ThreadInfo.irqDepth > 0 || OS_GetCPUMode() == 0x12) {
            info->isSchedulerWaiting = TRUE;
            return;
        }

        current = *data_02127bd8;
        next    = func_020878b8();

        if (current == next || next == NULL) {
            return;
        }

        if (current->state != THREAD_STATE_TERMINATED && OS_SaveContext(&current->context)) {
            return;
        }

        if (data_02127bd0 != NULL) {
            data_02127bd0(current, next);
        }

        if (info->callback != NULL) {
            info->callback(current, next);
        }

        ThreadInfo.current = next;
        OS_LoadContext(&next->context);
    }
}

void OS_InitThread(void) {
    u32 stackLo;

    if (data_02127bdc) {
        return;
    }
    data_02127bdc = TRUE;
    data_02127bd8 = &ThreadInfo.current;

    data_02127cc4.priority = LAUNCHER_PRIORITY;
    data_02127cc4.id       = 0;
    data_02127cc4.state    = THREAD_STATE_READY;
    data_02127cc4.next     = NULL;
    data_02127cc4.profiler = NULL;

    ThreadInfo.list = &data_02127cc4;
    ThreadInfo.current = &data_02127cc4;

    if ((s32)unk_SysStackSize <= 0) {
        stackLo = (u32)unk_DtcmArenaStart - (u32)unk_SysStackSize;
    } else {
        stackLo = (u32)(u8*)data_027e0000 + 0x3f80 - (u32)unk_IrqStackSize - (u32)unk_SysStackSize;
    }

    data_02127cc4.stackBottom = (u32)(u8*)data_027e0000 + 0x3f80 - (u32)unk_IrqStackSize;
    data_02127cc4.stackTop    = stackLo;
    data_02127cc4.stackOffset = 0;

    *(u32*)(data_02127cc4.stackBottom - sizeof(u32)) = STACK_BOTTOM_MAGIC;
    *(u32*)data_02127cc4.stackTop                    = STACK_TOP_MAGIC;

    data_02127cc4.joinQueue.tail = NULL;
    data_02127cc4.joinQueue.head = NULL;

    ThreadInfo.isSchedulerWaiting = FALSE;
    ThreadInfo.irqDepth           = 0;

    REG_THREAD_INFO_PTR = &ThreadInfo;

    func_0208794c(NULL);

    func_02087688(&data_02127c04, func_02087968, NULL, data_02127d84 + IDLE_THREAD_STACK_SIZE / sizeof(u32),
                  IDLE_THREAD_STACK_SIZE, 0x1f);
    data_02127c04.priority = IDLE_THREAD_PRIORITY;
    data_02127c04.state    = THREAD_STATE_READY;
}

// Creates a thread
void func_02087688(OSThread* thread, void (*func)(void*), void* arg, void* stack, u32 stackSize, u32 prio) {
    u32 prev = OS_DisableIRQ();
    s32 id   = OSi_GetUnusedThreadId();

    thread->priority = prio;
    thread->id       = id;
    thread->state    = THREAD_STATE_WAITING;
    thread->profiler = NULL;

    func_020874d0(thread);

    thread->stackBottom = (u32)stack;
    thread->stackTop    = (u32)stack - stackSize;
    thread->stackOffset = 0;

    *(u32*)(thread->stackBottom - sizeof(u32)) = STACK_BOTTOM_MAGIC;
    *(u32*)thread->stackTop                    = STACK_TOP_MAGIC;

    thread->joinQueue.head = thread->joinQueue.tail = NULL;

    func_020879c4(&thread->context, func, (void*)((u32)stack - sizeof(u32)));

    thread->context.r[0] = (u32)arg;
    thread->context.lr   = (u32)func_02087760;

    func_02070224(0, (void*)((u32)stack - stackSize + sizeof(u32)), stackSize - sizeof(u32) * 2);

    thread->mutex           = NULL;
    thread->mutexQueue.head = NULL;
    thread->mutexQueue.tail = NULL;

    func_020879bc(thread, NULL);

    thread->queue     = NULL;
    thread->list.prev = thread->list.next = NULL;

    func_02070224(0, thread->unk_A4, sizeof(thread->unk_A4));

    thread->unk_B0 = NULL;

    OS_RestoreIRQ(prev);
}

// Exits the current thread
void func_02087760(void) {
    OS_DisableIRQ();
    OSi_ExitThread_ArgSpecified(ThreadInfo.current, NULL);
}

void OSi_ExitThread_ArgSpecified(OSThread* thread, void* arg) {
    if (data_02127bec != NULL) {
        func_020879c4(&thread->context, func_020877b4, data_02127bec);
        thread->context.r[0] = (u32)arg;
        thread->context.cpsr |= 0x80;
        thread->state = THREAD_STATE_READY;
        OS_LoadContext(&thread->context);
    } else {
        func_020877b4(arg);
    }
}

// Calls the destructor of the current thread, then destroys it
void func_020877b4(void* arg) {
    OSThread*          current    = *data_02127bd8;
    OSThreadDestructor destructor = current->destructor;

    if (destructor != NULL) {
        current->destructor = NULL;
        destructor(arg);
        OS_DisableIRQ();
    }

    func_020877dc();
}

// Destroys the current thread
void func_020877dc(void) {
    OSThread* current = *data_02127bd8;

    func_02087974();

    OS_UnlockAllQueuedThreadMutex(current);
    if (current->queue != NULL) {
        OSi_RemoveSpecifiedLinkFromQueue(current->queue, current);
    }
    func_02087508(current);
    current->state = THREAD_STATE_TERMINATED;
    OS_UnpauseThread(&current->joinQueue);
    func_02087998();
    func_020878d0();
    OS_Terminate();
}

void OS_PauseThread(OSThreadQueue* queue) {
    u32       prev    = OS_DisableIRQ();
    OSThread* current = *data_02127bd8;

    if (queue != NULL) {
        current->queue = queue;
        OSi_InsertLinkToQueue(queue, current);
    }

    current->state = THREAD_STATE_WAITING;
    func_02087534();

    OS_RestoreIRQ(prev);
}

void OS_UnpauseThread(OSThreadQueue* queue) {
    u32 prev = OS_DisableIRQ();

    if (queue->head != NULL) {
        while (queue->head != NULL) {
            OSThread* thread  = OSi_RemoveLinkFromQueue(queue);
            thread->state     = THREAD_STATE_READY;
            thread->queue     = NULL;
            thread->list.prev = thread->list.next = NULL;
        }

        queue->tail = NULL;
        queue->head = NULL;
        func_02087534();
    }

    OS_RestoreIRQ(prev);
}

void OS_WakeupThreadDirect(void* param1) {
    OSThread* thread = param1;
    u32       prev   = OS_DisableIRQ();

    thread->state = THREAD_STATE_READY;
    func_02087534();

    OS_RestoreIRQ(prev);
}

// Returns the highest priority ready thread
OSThread* func_020878b8(void) {
    OSThread* t = ThreadInfo.list;

    while (t != NULL && t->state != THREAD_STATE_READY) {
        t = t->next;
    }
    return t;
}

void func_020878d0(void) {
    u32 prev = OS_DisableIRQ();
    func_02087534();
    OS_RestoreIRQ(prev);
}

// Changes the priority of a thread
BOOL func_020878e4(OSThread* thread, u32 prio) {
    OSThread* t   = ThreadInfo.list;
    OSThread* pre = NULL;
    u32       prev = OS_DisableIRQ();

    while (t != NULL && t != thread) {
        pre = t;
        t   = t->next;
    }

    if (t == NULL || t == &data_02127c04) {
        OS_RestoreIRQ(prev);
        return FALSE;
    }

    if (t->priority != prio) {
        if (pre == NULL) {
            ThreadInfo.list = thread->next;
        } else {
            pre->next = thread->next;
        }
        thread->priority = prio;
        func_020874d0(thread);
        func_02087534();
    }

    OS_RestoreIRQ(prev);
    return TRUE;
}

OSThreadSwitchCallback func_0208794c(OSThreadSwitchCallback callback) {
    u32                    prev = OS_DisableIRQ();
    OSThreadSwitchCallback old  = ThreadInfo.callback;
    ThreadInfo.callback         = callback;
    OS_RestoreIRQ(prev);
    return old;
}

// Idle thread
void func_02087968(void* arg) {
    OS_EnableIRQ();
    while (TRUE) {
        func_0208894c();
    }
}

// Disables the scheduler
u32 func_02087974(void) {
    u32 prev = OS_DisableIRQ();
    u32 count;

    if (data_02127bd4 < (u32)-1) {
        count = data_02127bd4++;
    }

    OS_RestoreIRQ(prev);
    return count;
}

// Enables the scheduler
u32 func_02087998(void) {
    u32 prev  = OS_DisableIRQ();
    u32 count = 0;

    if (data_02127bd4 > 0) {
        count = data_02127bd4--;
    }

    OS_RestoreIRQ(prev);
    return count;
}

void func_020879bc(OSThread* thread, OSThreadDestructor destructor) {
    thread->destructor = destructor;
}

// Uses data_02127be0/b8/bc like the library code that is not linked into the ROM (keeps them in the pooled .bss).
static void unkfunc_unused_26(void) {
    data_02127be0 = 0;
    data_02127be4 = 0;
    data_02127be8 = 0;
}
