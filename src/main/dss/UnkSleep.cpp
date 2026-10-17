#include "main/dss/UnkSleep.hpp"
#include "nitro/gx.h"
#include "nitro/os.hpp"
#include "nitro/pad.h"
#include "nitro/pm.h"

int data_020fd15c;
int data_020fd164;
int data_020fd160;
UnkPmSleepCallback data_020fd168;
UnkPmSleepCallback data_020fd174;

ARM void unkfunc_0204bf48()
{
    data_020fd15c = 1;
    data_020fd168.func_ = unkfunc_02089578;
    data_020fd168.arg_ = &data_020fd160;
    data_020fd174.func_ = unkfunc_0208957c;
    data_020fd174.arg_ = NULL;
    func_0207927c(&data_020fd168);
    func_0207929c(&data_020fd174);
}

ARM void unkfunc_0204bfa4()
{
    if (data_020fd15c == 1 && PAD_DetectFold() == TRUE) {
        data_020fd164 = 0;
        data_020fd160 = 0;
        func_02078fb0(PM_TRIGGER_COVER_OPEN | PM_TRIGGER_CARD, 0, 0);
    }
    if (data_020fd164 == 0) {
        return;
    }
    if (data_020fd164 == 1) {
        OS_Wait();
        GX_DispOff();
        REG_DISPCNT_SUB &= ~0x10000;
        OS_Wait();
        if (func_020791e0(FALSE) != 0) {
            data_020fd164 = 0;
        }
    } else if (data_020fd164 == 2) {
        if (func_020791e0(TRUE) != 0) {
            OS_Wait();
            GX_DispOn();
            REG_DISPCNT_SUB |= 0x10000;
            OS_Wait();
            data_020fd164 = 0;
        }
    }
}

ARM void unkfunc_0204c08c(int enable)
{
    data_020fd15c = enable;
}

ARM int unkfunc_02089568()
{
    return data_020fd15c;
}

ARM void unkfunc_02089578(void* arg)
{
}

ARM void unkfunc_0208957c(void* arg)
{
}
