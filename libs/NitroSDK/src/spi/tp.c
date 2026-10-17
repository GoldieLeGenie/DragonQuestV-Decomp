#include "../sdk_internal.h"
#include <nitro/reg.h>

#pragma thumb on

typedef void (*UnkTpCallback)(u32 command, u8 result, u16 index);

typedef struct UnkTpData {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} UnkTpData;

typedef union UnkTpRawData {
    struct {
        u32 x : 12;
        u32 y : 12;
        u32 touch : 1;
        u32 validity : 2;
        u32 dummy : 5;
    } e;
    u16 half[2];
    u32 raw;
} UnkTpRawData;

// calibration parameters given by the user (or the owner settings)
typedef struct UnkTpCalibrateParam {
    s16 x0;       // 0x00
    s16 y0;       // 0x02
    s16 xDotSize; // 0x04
    s16 yDotSize; // 0x06
} UnkTpCalibrateParam;

// calibration parameters used for the conversion
typedef struct UnkTpCalibrate {
    s32 x0;          // 0x00
    s32 xDotSize;    // 0x04
    s32 xDotSizeInv; // 0x08
    s32 y0;          // 0x0C
    s32 yDotSize;    // 0x10
    s32 yDotSizeInv; // 0x14
} UnkTpCalibrate;

typedef struct UnkTpWork {
    u16 initialized;         // 0x00
    u16 unk_02;
    UnkTpCallback callback;  // 0x04
    UnkTpData sample;        // 0x08
    u16 index;               // 0x10
    u16 unk_12;
    UnkTpData* samplingBufs; // 0x14
    u16 bufSize;             // 0x18
    u8 unk_1a[0x1c - 0x1a];
    UnkTpCalibrate calibrate; // 0x1C
    u16 unk_34;     // 0x34 calibration set
    u16 state;      // 0x36
    u16 errorFlags; // 0x38
    vu16 busyFlags; // 0x3a
} UnkTpWork;

UnkTpWork data_0211fd24;

#define TP_RAW_DATA ((vu16*)0x027fffaa)

void func_02078564(u32 tag, u32 data, BOOL err) {
    u16 result = (u16)data;
    u32 tpResult;
    u16 command = (u16)((result & 0x7f00) >> 8);

    if (err) {
        data_0211fd24.errorFlags |= 1 << command;
        if (data_0211fd24.callback) {
            data_0211fd24.callback(command, 4, 0);
        }
        return;
    }

    if (command == 0x10) {
        UnkTpRawData raw;
        UnkTpData* buf;

        data_0211fd24.index++;
        if (data_0211fd24.index >= data_0211fd24.bufSize) {
            data_0211fd24.index = 0;
        }
        buf = &data_0211fd24.samplingBufs[data_0211fd24.index];
        raw.half[0] = TP_RAW_DATA[0];
        raw.half[1] = TP_RAW_DATA[1];
        buf->x = raw.e.x;
        buf->y = raw.e.y;
        buf->touch = (u8)raw.e.touch;
        buf->validity = (u8)raw.e.validity;
        if (data_0211fd24.callback) {
            data_0211fd24.callback(command, 0, (u8)data_0211fd24.index);
        }
        return;
    }

    if (!(data & 0x1000000)) {
        return;
    }

    switch ((u8)result) {
    case 0:
        switch (command) {
        case 0: {
            UnkTpRawData raw;
            raw.half[0] = TP_RAW_DATA[0];
            raw.half[1] = TP_RAW_DATA[1];
            data_0211fd24.sample.x = raw.e.x;
            data_0211fd24.sample.y = raw.e.y;
            data_0211fd24.sample.touch = (u8)raw.e.touch;
            data_0211fd24.sample.validity = (u8)raw.e.validity;
            data_0211fd24.state = 0;
            break;
        }
        case 1:
            data_0211fd24.state = 2;
            break;
        case 2:
            data_0211fd24.state = 0;
            break;
        }
        data_0211fd24.busyFlags &= ~(1 << command);
        if (data_0211fd24.callback) {
            data_0211fd24.callback(command, 0, 0);
        }
        return;
    case 4:
        tpResult = 3;
        break;
    case 2:
        tpResult = 1;
        break;
    case 3:
        tpResult = 2;
        break;
    default:
        goto terminate;
    }

    data_0211fd24.errorFlags |= 1 << command;
    data_0211fd24.busyFlags &= ~(1 << command);
    if (data_0211fd24.callback) {
        data_0211fd24.callback(command, (u8)tpResult, 0);
    }
    return;

terminate:
    OS_Terminate();
}

void func_020786d4(void) {
    if (data_0211fd24.initialized) {
        return;
    }
    data_0211fd24.initialized = TRUE;
    func_0207734c();

    data_0211fd24.index = 0;
    data_0211fd24.callback = NULL;
    data_0211fd24.samplingBufs = NULL;
    data_0211fd24.state = 0;
    data_0211fd24.unk_34 = 0;
    data_0211fd24.busyFlags = 0;
    data_0211fd24.errorFlags = 0;

    while (!func_0207744c(6, 1)) {
    }
    func_02077400(6, func_02078564);
}

typedef struct UnkTpUserInfo {
    u8 unk_00[0x58];
    u16 raw_x1; // 0x58
    u16 raw_y1; // 0x5A
    u8 dx1;     // 0x5C
    u8 dy1;     // 0x5D
    u16 raw_x2; // 0x5E
    u16 raw_y2; // 0x60
    u8 dx2;     // 0x62
    u8 dy2;     // 0x63
} UnkTpUserInfo;

#define TP_USER_INFO ((const UnkTpUserInfo*)0x027ffc80)

static inline void SetDiv32_32_(u32 numer, u32 denom) {
    REG_DIV_CNT = 0;
    *(vu32*)&REG_DIV_NUMER = numer;
    REG_DIV_DENOM = denom;
}

static inline void WaitDiv_(void) {
    while (REG_DIV_CNT & 0x8000) {
    }
}

static inline s32 GetDivResult32_(void) {
    WaitDiv_();
    return *(vs32*)&REG_DIV_RESULT;
}

u32 func_020788f4(UnkTpCalibrateParam* calibrate, u16 raw_x1, u16 raw_y1, u16 dx1, u16 dy1, u16 raw_x2, u16 raw_y2,
                  u16 dx2, u16 dy2);
void func_02078a70(UnkTpData* disp, const UnkTpData* raw);
void func_02078b20(u32 flags);

// Gets the calibration parameters of the owner settings
BOOL func_0207871c(UnkTpCalibrateParam* calibrate) {
    const UnkTpUserInfo* info = TP_USER_INFO;
    u16 x1 = info->raw_x1;
    u16 y1 = info->raw_y1;
    u8 dx1 = info->dx1;
    u8 dy1 = info->dy1;
    u16 x2 = info->raw_x2;
    u16 y2 = info->raw_y2;
    u8 dx2 = info->dx2;
    u8 dy2 = info->dy2;

    if ((x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0) ||
        func_020788f4(calibrate, x1, y1, dx1, dy1, x2, y2, dx2, dy2) != 0) {
        calibrate->x0 = 0;
        calibrate->y0 = 0;
        calibrate->xDotSize = 0;
        calibrate->yDotSize = 0;
        return TRUE;
    }
    return TRUE;
}

// Sets the calibration parameters (NULL: no calibration)
void func_02078794(const UnkTpCalibrateParam* param) {
    u32 enabled;

    if (param == NULL) {
        data_0211fd24.unk_34 = 0;
        return;
    }

    enabled = OS_DisableIRQ();

    if (param->xDotSize != 0) {
        SetDiv32_32_(0x10000000, param->xDotSize);
        data_0211fd24.calibrate.x0 = param->x0;
        data_0211fd24.calibrate.xDotSize = param->xDotSize;
        data_0211fd24.calibrate.xDotSizeInv = GetDivResult32_();
    } else {
        data_0211fd24.calibrate.x0 = 0;
        data_0211fd24.calibrate.xDotSize = 0;
        data_0211fd24.calibrate.xDotSizeInv = 0;
    }

    if (param->yDotSize != 0) {
        SetDiv32_32_(0x10000000, param->yDotSize);
        data_0211fd24.calibrate.y0 = param->y0;
        data_0211fd24.calibrate.yDotSize = param->yDotSize;
        data_0211fd24.calibrate.yDotSizeInv = GetDivResult32_();
    } else {
        data_0211fd24.calibrate.y0 = 0;
        data_0211fd24.calibrate.yDotSize = 0;
        data_0211fd24.calibrate.yDotSizeInv = 0;
    }

    OS_RestoreIRQ(enabled);
    data_0211fd24.unk_34 = TRUE;
}

static inline BOOL SendCommand_(u32 data) {
    return (PXI_SendWordByFifo(6, data, 0) >= 0) ? TRUE : FALSE;
}

// Requests one sampling
void func_02078844(void) {
    u32 enabled = OS_DisableIRQ();

    if (!SendCommand_(0x03000000)) {
        OS_RestoreIRQ(enabled);
        data_0211fd24.errorFlags |= 1;
        if (data_0211fd24.callback) {
            data_0211fd24.callback(0, 4, 0);
        }
        return;
    }
    data_0211fd24.busyFlags |= 1;
    data_0211fd24.errorFlags &= ~1;
    OS_RestoreIRQ(enabled);
}

// Gets the calibrated result of the last sampling
u32 func_020788a4(UnkTpData* result) {
    if (data_0211fd24.errorFlags & 1) {
        return 1;
    }
    *result = data_0211fd24.sample;
    func_02078a70(result, result);
    return 0;
}

// Waits for the sampling and gets its calibrated result
u32 func_020788d4(UnkTpData* result) {
    func_02078b20(1);
    return func_020788a4(result);
}

// Index of the latest auto sampling
u32 func_020788e8(void) {
    return data_0211fd24.index;
}

// Computes the calibration parameters from two points
u32 func_020788f4(UnkTpCalibrateParam* calibrate, u16 raw_x1, u16 raw_y1, u16 dx1, u16 dy1, u16 raw_x2, u16 raw_y2,
                  u16 dx2, u16 dy2) {
    s32 ry_width;
    s32 dy_width;
    s32 tmp32;
    u32 enabled;

    if (raw_x1 >= 0x1000 || raw_y1 >= 0x1000 || raw_x2 >= 0x1000 || raw_y2 >= 0x1000) {
        return 1;
    }
    if (dx1 >= 0x100 || dx2 >= 0x100 || dy1 >= 0xc0 || dy2 >= 0xc0) {
        return 1;
    }
    if (dx1 == dx2 || dy1 == dy2 || raw_x1 == raw_x2 || raw_y1 == raw_y2) {
        return 1;
    }

    enabled = OS_DisableIRQ();

    SetDiv32_32_((raw_x1 - raw_x2) << 8, dx1 - dx2);
    ry_width = raw_y1 - raw_y2;
    dy_width = dy1 - dy2;
    tmp32 = GetDivResult32_();
    SetDiv32_32_(ry_width << 8, dy_width);

    if (tmp32 >= 0x8000 || tmp32 < -0x8000) {
        OS_RestoreIRQ(enabled);
        return 1;
    }
    calibrate->xDotSize = (s16)tmp32;
    tmp32 = (s16)((((raw_x1 + raw_x2) << 8) - (dx1 + dx2) * calibrate->xDotSize) >> 7);
    if (tmp32 >= 0x8000 || tmp32 < -0x8000) {
        OS_RestoreIRQ(enabled);
        return 1;
    }
    calibrate->x0 = (s16)tmp32;

    tmp32 = GetDivResult32_();
    OS_RestoreIRQ(enabled);

    if (tmp32 >= 0x8000 || tmp32 < -0x8000) {
        return 1;
    }
    calibrate->yDotSize = (s16)tmp32;
    tmp32 = (s16)((((raw_y1 + raw_y2) << 8) - (dy1 + dy2) * calibrate->yDotSize) >> 7);
    if (tmp32 >= 0x8000 || tmp32 < -0x8000) {
        return 1;
    }
    calibrate->y0 = (s16)tmp32;
    return 0;
}

// Converts raw touch panel coordinates to screen coordinates
static inline UnkTpCalibrate* GetCalibrate_(void) {
    return &data_0211fd24.calibrate;
}

void func_02078a70(UnkTpData* disp, const UnkTpData* raw) {
    UnkTpCalibrate* cal;

    if (!data_0211fd24.unk_34) {
        *disp = *raw;
        return;
    }

    cal = &data_0211fd24.calibrate;
    disp->touch = raw->touch;
    disp->validity = raw->validity;
    if (raw->touch == 0) {
        disp->x = 0;
        disp->y = 0;
        return;
    }

    disp->x = (s16)((((s64)(raw->x << 2) - cal->x0) * cal->xDotSizeInv) >> 22);
    if ((s16)disp->x < 0) {
        disp->x = 0;
    } else if ((s16)disp->x > 0xff) {
        disp->x = 0xff;
    }

    disp->y = (s16)((((s64)(raw->y << 2) - cal->y0) * cal->yDotSizeInv) >> 22);
    if ((s16)disp->y < 0) {
        disp->y = 0;
    } else if ((s16)disp->y > 0xbf) {
        disp->y = 0xbf;
    }
}

// Waits until the given requests are done
void func_02078b20(u32 flags) {
    while (data_0211fd24.busyFlags & flags) {
    }
}
