#pragma once
#include <globaldefs.h>
#include "main/dss/DssUtils.hpp"

extern const dss::Fix32 data_0209a368;                // pi / 2
extern const dss::Fix32 data_0209a364;                // 360
extern const dss::Fix32 data_0209a360;                // 180
extern const dss::Fix32 data_0209a35c;                // 90
extern const dss::Fix32 data_0209a358;                // 16
extern const dss::Fix32 data_0209a354;                // 8
extern const dss::Fix32 data_0209a36c;                // pi

int unkfunc_0204f3bc(int r, int g, int b, int a);  // RGBA8
int unkfunc_0204f3d0(dss::Fix32 degree);           // degree -> 16-bit angle
