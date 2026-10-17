#pragma once
#include <globaldefs.h>

// dss array index warnings
struct UnkArrayWarning {
    int index_;                                 // 0x00
    int size_;                                  // 0x04
    unsigned int caller_;                       // 0x08 return address
};

extern int data_0209a288;                       // array warnings enabled
extern int data_020fd180;                       // number of array warnings
extern UnkArrayWarning data_020fd184[16];

void unkfunc_0204c0b4(int enable);
void unkfunc_02089590(int index, int size, unsigned int caller);   // add a warning
UnkArrayWarning* unkfunc_0204c11c(int index);
int unkfunc_0204c130();                         // number of array warnings
void unkfunc_0204c140(int index, int size);     // "ARRAY ERROR %d/%d %08x !!!!"
