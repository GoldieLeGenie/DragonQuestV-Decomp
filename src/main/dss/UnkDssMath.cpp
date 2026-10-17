#include "main/dss/UnkDssMath.hpp"

const dss::Fix32 data_0209a36c(0x3244);
const dss::Fix32 data_0209a368(0x1922);
const dss::Fix32 data_0209a364(0x168000);
const dss::Fix32 data_0209a360(0xb4000);
const dss::Fix32 data_0209a35c(0x5a000);
const dss::Fix32 data_0209a358(0x10000);
const dss::Fix32 data_0209a354(0x8000);
static const int s_unused[2] = {0};      // not original: unreferenced (stripped) item, fixes the .data order

ARM int unkfunc_0204f3bc(int r, int g, int b, int a)
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

ARM int unkfunc_0204f3d0(dss::Fix32 degree)
{
    return (unsigned short)(degree * data_0209a354 / data_0209a360).value;
}
