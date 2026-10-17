// Keep the complete SDK sound state, including its reserved work buffer.
#pragma define_section sdk_state ".data" ".bss.keep" ".rodata" RW
#include "../nns_internal.h"

#pragma thumb on

typedef void (*UnkSleepCallbackFunc)(void* arg);

typedef struct UnkSleepCallbackInfo {
    UnkSleepCallbackFunc func;              /* 0x00 */
    void* arg;                              /* 0x04 */
    struct UnkSleepCallbackInfo* next;      /* 0x08 */
} UnkSleepCallbackInfo;

typedef struct UnkSndMainUnk {
    u8 unk_00[0x23d8];
} UnkSndMainUnk;

/* definition order chosen for the .bss layout (the compiler sorts the objects by size) */
__declspec(sdk_state) s8 data_02120900;
__declspec(sdk_state) u32 data_02120904;
__declspec(sdk_state) UnkSleepCallbackInfo data_0212091c;         /* post-sleep callback */
__declspec(sdk_state) u32 data_02120908;
__declspec(sdk_state) BOOL data_0212090c;                         /* initialized */
__declspec(sdk_state) UnkSleepCallbackInfo data_02120910;         /* pre-sleep callback */
__declspec(sdk_state) UnkSndMainUnk data_02120928;                /* not referenced by the code in the ROM */

void SND_Init(void);
void func_0207928c(UnkSleepCallbackInfo* info);
void func_0207929c(UnkSleepCallbackInfo* info);
void func_0207b470(void);
void func_0207bee4(void);
void func_0207b608(void);
BOOL func_02077d8c(u32 flag);
void func_0207b680(void);
void func_0207bef4(void);
void func_0207d2c8(void);
BOOL func_02077eb8(u32 flag);
void func_0207bfe8(void);
void func_02077b1c(u32 a, u32 b, u32 c, u32 d);
u32 func_02078010(void);
void func_02077fcc(u32 tag);
void func_0207c02c(void);

void func_0207b3a8(void* arg);
void func_0207b3d0(void* arg);

void func_0207b328(void)
{
    if (data_0212090c) {
        return;
    }
    data_0212090c = TRUE;

    SND_Init();

    data_02120910.func = func_0207b3a8;
    data_02120910.arg = NULL;
    data_0212091c.func = func_0207b3d0;
    data_0212091c.arg = NULL;
    func_0207928c(&data_02120910);
    func_0207929c(&data_0212091c);

    func_0207b470();
    func_0207bee4();
    func_0207b608();

    data_02120900 = -1;
    data_02120904 = 1;
}

void func_0207b384(void)
{
    while (func_02077d8c(0)) {
    }

    func_0207b680();
    func_0207bef4();
    func_0207d2c8();

    func_02077eb8(0);
}

/* pre-sleep callback */
void func_0207b3a8(void* arg)
{
    u32 tag;

    func_0207bfe8();
    func_02077b1c(0, 0, 0, 0);
    tag = func_02078010();
    func_02077eb8(1);
    func_02077fcc(tag);
}

/* post-sleep callback */
void func_0207b3d0(void* arg)
{
    func_0207c02c();
}

/* Uses data_02120908 like the library code that is not linked into the ROM (keeps it in the pooled .bss). */
static void unkfunc_unused_24(void)
{
    data_02120908 = 0;
}
