#ifndef RTC_INTERNAL_H
#define RTC_INTERNAL_H

#include <nitro/types.h>
#include <nitro/rtc.h>

BOOL func_020779d4(void); /* read the raw time (PXI command 0x12) */
BOOL func_020779e0(void); /* write the raw status 2 (PXI command 0x27) */
u32  func_02077a0c(const RTCDate* date); /* day of the week */

#endif
