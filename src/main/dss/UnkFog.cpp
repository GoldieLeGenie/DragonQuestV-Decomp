#include "main/dss/UnkFog.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkDssMath.hpp"
#include "nitro/g3.hpp"

int data_020f3e30;
dss::Fix32 data_020f3e34[2];
int data_020f3e3c[2];
unsigned int data_020f3e44[2][8];

THUMB void unkfunc_02046ab0()
{
    data_020f3e30 = 0;
    func_02075e00(0, 0, 10, 1000);
    for (signed char i = 0; i < 8; i++) {
        data_020f3e44[0][i] = unkfunc_0204f3bc((unsigned char)(i * 16 + 12), (unsigned char)(i * 16 + 8), (unsigned char)(i * 16 + 4), (unsigned char)(i * 16));
    }
    func_02075eb8(data_020f3e44[0]);
    *(volatile unsigned int*)0x04000358 = 0x1f7fff;
}

THUMB void unkfunc_02046b28(int side, int offset)
{
    data_020f3e3c[side] = offset;
}

THUMB void unkfunc_02046b34(int side, dss::Fix32 rate)
{
    for (int i = 0; i < 8; i++) {
        int a = rate.value * (i * 16) >> 12;
        a = dss::clamp<int>(a, 0, 0x7f);
        int b = dss::clamp<int>(a, 0, 0x7f);
        int g = dss::clamp<int>(a, 0, 0x7f);
        int r = dss::clamp<int>(a, 0, 0x7f);
        if (i == 7) {
            r = 0x7f;
        }
        data_020f3e44[side][i] = unkfunc_0204f3bc((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a);
    }
}

THUMB void unkfunc_02046ba8(int r, int g, int b)
{
    *(volatile unsigned int*)0x04000358 = (unsigned short)(r | (g << 5) | (b << 10)) | 0x1f0000;
}

THUMB void unkfunc_02046bc4(int enable)
{
    data_020f3e30 = enable;
    func_02075e00(0, 0, 10, 1000);
}

THUMB void unkfunc_02046be0()
{
    if (data_020f3e30 == 0) {
        return;
    }
    if (getDisplayFrame() & 1) {
        func_02075e00(1, 0, 10, data_020f3e3c[0]);
        func_02075eb8(data_020f3e44[0]);
    } else {
        func_02075e00(1, 0, 10, data_020f3e3c[1]);
        func_02075eb8(data_020f3e44[1]);
    }
}
