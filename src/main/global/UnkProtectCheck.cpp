#include "main/global/UnkProtectCheck.hpp"

// Check value: 0x28cc + 0x1b once func_02007e74 has reported success
int data_0209c798 = 0x28cc;

int runProtectCheck() {
    if (func_02007e74(0x190) == 0) {
        return 1;
    }
    data_0209c798 += 0x1b;
    return 0;
}

int isProtectCheckTriggered() {
    return data_0209c798 == 0x28e7;
}
