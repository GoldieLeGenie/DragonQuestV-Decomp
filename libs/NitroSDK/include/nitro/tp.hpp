#pragma once

// touch panel
struct TPData {
    unsigned short x;                           // 0x00
    unsigned short y;                           // 0x02
    unsigned short touch;                       // 0x04
    unsigned short validity;                    // 0x06
};

struct TPCalibrateParam {
    short x0;                                   // 0x00
    short y0;                                   // 0x02
    short xDotSize;                             // 0x04
    short yDotSize;                             // 0x06
};

extern "C" {
    int func_0207871c(TPCalibrateParam* calibrate);         // TP_GetUserInfo
    void func_02078794(const TPCalibrateParam* calibrate);  // TP_SetCalibrateParam
    void func_02078844(void);                               // TP_RequestSamplingAsync
    unsigned int func_020788d4(TPData* result);             // TP_WaitCalibratedResult
    unsigned short func_020788e8(void);                     // TP_GetLatestIndexInAuto
    void func_02078a70(TPData* disp, const TPData* raw);    // TP_GetCalibratedPoint
}
