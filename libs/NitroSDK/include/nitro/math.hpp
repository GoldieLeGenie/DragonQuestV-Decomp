#pragma once

struct MATHRandContext32 {
    unsigned long long x;                       // 0x00
    unsigned long long mul;                     // 0x08
    unsigned long long add;                     // 0x10
};

struct MATHRandContext16 {
    unsigned int x;                             // 0x00
    unsigned int mul;                           // 0x04
    unsigned int add;                           // 0x08
};

extern "C" {
    void func_0208a920(void* digest, const void* data, unsigned int len);   // MATH_CalcMD5
}
