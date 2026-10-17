#include "../sdk_internal.h"

typedef struct UnkResetState {
    vu16 unk_00; // reset requested by ARM7
    u16 unk_02;  // initialized
} UnkResetState;

UnkResetState data_02127f4c;

void func_02088780(u32 tag, u32 data, BOOL err);

/* Installs the PXI reset-notification callback (tag 12). */
void func_0208872c(void) {
    if (data_02127f4c.unk_02) {
        return;
    }
    data_02127f4c.unk_02 = TRUE;

    func_0207734c();
    while (!func_0207744c(12, 1)) {
    }
    func_02077400(12, func_02088780);
}

void func_02088780(u32 tag, u32 data, BOOL err) {
    if ((u16)((data & 0x7f00) >> 8) == 0x10) {
        data_02127f4c.unk_00 = TRUE;
    } else {
        OS_Terminate();
    }
}
