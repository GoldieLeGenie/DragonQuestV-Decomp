#include "rtc_internal.h"

#pragma thumb on

u32 func_02077a0c(const RTCDate* date) {
    s32 month;
    s32 year;
    s32 day;
    s32 century;
    s32 yy;

    year  = (s32)date->year + 2000;
    month = (s32)date->month - 2;
    day   = (s32)date->day;

    if (month < 1) {
        month += 12;
        year--;
    }
    century = year / 100;
    yy      = year % 100;
    return (u32)((day + (26 * month - 2) / 10 + yy + yy / 4 + century / 4 + 5 * century) % 7);
}
