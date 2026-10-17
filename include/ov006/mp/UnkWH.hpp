#pragma once
#include "globaldefs.h"
#include "nitro/wm.h"
#include "nitro/os/os_owner.h"

extern "C" {
    int func_0208a8dc(u32 value);                                  // bit count
    void func_020887c8(OSOwnerInfo* info);                         // owner info
    char* STD_CopyLString(char* dst, const char* src, int size);
    BOOL func_02071a78(WMBssDesc* desc);

    // WM library
    WMErrCode func_0207a138(void (*callback)(void* arg));         // set the indication callback
    u16 func_0207a2c8(void);                                       // allowed channels
    u16 func_0207a3d4(void);                                       // next tgid
    int func_0207a2e4(void);                                       // link level
    u16 func_0207a344(void);                                       // beacon period
    u16 func_0207a38c(void);                                       // scan period
    WMErrCode func_0207a41c(void* buf, void (*callback)(void* arg), u16 dmaNo);    // initialize
    WMErrCode func_0207a464(void (*callback)(void* arg));         // reset
    WMErrCode func_0207a488(void (*callback)(void* arg));         // end
    WMErrCode func_0207a4b0(void (*callback)(void* arg), WMParentParam* param);    // parent parameter
    WMErrCode func_0207a5ac(void (*callback)(void* arg));         // start parent
    WMErrCode func_0207a5b8(void (*callback)(void* arg));         // end parent
    WMErrCode func_0207a5e0(void (*callback)(void* arg), WMScanParam* param);      // start scan
    WMErrCode func_0207a664(void (*callback)(void* arg));         // end scan
    WMErrCode func_0207a68c(void (*callback)(void* arg), WMBssDesc* desc, u8* ssid, BOOL powerSave, u16 authMode);  // start connect
    WMErrCode func_0207a710(void (*callback)(void* arg), u16 aid);                  // disconnect
    WMErrCode func_0207a89c(void (*callback)(void* arg), u16* recvBuf, u16 recvBufSize, u16* sendBuf, u16 sendBufSize, u16 mpFreq);  // start MP
    WMErrCode func_0207a9a4(void (*callback)(void* arg));         // end MP
    WMErrCode func_0207a9ec(WMDataSharingInfo* info, u16 port, u16 aidBitmap, u16 dataLength, BOOL doubleMode);  // start data sharing
    WMErrCode func_0207abb4(WMDataSharingInfo* info);             // end data sharing
    WMErrCode func_0207abe8(WMDataSharingInfo* info, const u16* sendData, WMDataSet* receiveData);  // step data sharing
    u16* func_0207b1b0(WMDataSharingInfo* info, WMDataSet* receiveData, u16 aid);  // shared data address
    WMErrCode func_0207b20c(WMKeySetBuf* buf, u16 port);          // start key sharing
    WMErrCode func_0207b220(WMKeySetBuf* buf);                    // end key sharing
    WMErrCode func_0207b228(void (*callback)(void* arg), u16 wepMode, const u16* wepKey);  // WEP key
    int func_0207b270(void (*callback)(void* arg), void* info, u16 size, u32 ggid, u16 tgid, u8 attr);   // game info
    WMErrCode func_0207b2e0(void (*callback)(void* arg), u16 ccaMode, u16 edThreshold, u16 channel, u16 measureTime);  // measure channel
}

// wireless layer 
enum {
    WH_SYSSTATE_STOP = 0,
    WH_SYSSTATE_IDLE = 1,
    WH_SYSSTATE_SCANNING = 2,
    WH_SYSSTATE_BUSY = 3,
    WH_SYSSTATE_CONNECTED = 4,
    WH_SYSSTATE_DATASHARING = 5,
    WH_SYSSTATE_KEYSHARING = 6,
    WH_SYSSTATE_MEASURECHANNEL = 7,
    WH_SYSSTATE_CONNECT_FAIL = 8,
    WH_SYSSTATE_ERROR = 9,
    WH_SYSSTATE_FATAL = 10
};

// Connection modes
enum {
    WH_CONNECTMODE_MP_PARENT = 0,
    WH_CONNECTMODE_MP_CHILD = 1,
    WH_CONNECTMODE_KS_PARENT = 2,
    WH_CONNECTMODE_KS_CHILD = 3,
    WH_CONNECTMODE_DS_PARENT = 4,
    WH_CONNECTMODE_DS_CHILD = 5
};

void unkfunc_021210e4(const char* fmt, ...);                    // debug print (empty)
void unkfunc_021210f0(int state);                               // set the system state
void unkfunc_02121100(int code);                                // set the error code
BOOL unkfunc_0212111c();                                        // set the parent parameter
void unkfunc_0212115c(void* arg);
BOOL unkfunc_021211c0();                                        // set the parent WEP key
void unkfunc_02121220(void* arg);
BOOL unkfunc_02121258();                                        // start the parent
void unkfunc_021212b0(void* arg);
BOOL unkfunc_021213cc();                                        // start MP (parent)
void unkfunc_02121460(void* arg);
BOOL unkfunc_02121544();                                        // start key sharing (parent)
BOOL unkfunc_02121578();                                        // end key sharing (parent)
BOOL unkfunc_021215b8();                                        // end MP (parent)
void unkfunc_021215e8(void* arg);
BOOL unkfunc_02121618();                                        // end the parent
void unkfunc_02121640(void* arg);
BOOL unkfunc_02121664(void (*callback)(WMBssDesc*), const u8* bssid, u16 channel);  // start the scan
BOOL unkfunc_021216d0();                                        // scan the next channel
void unkfunc_02121798(void* arg);
BOOL unkfunc_021218f4();                                        // end the scan
BOOL unkfunc_02121928();                                        // end the scan (WM)
void unkfunc_02121950(void* arg);
BOOL unkfunc_021219c0();                                        // set the child WEP key
void unkfunc_02121a20(void* arg);
BOOL unkfunc_02121a58();                                        // start the connection
void unkfunc_02121adc(void* arg);
BOOL unkfunc_02121bc0();                                        // start MP (child)
void unkfunc_02121c2c(void* arg);
BOOL unkfunc_02121d14();                                        // start key sharing (child)
BOOL unkfunc_02121d6c();                                        // end key sharing (child)
BOOL unkfunc_02121dc4();                                        // end MP (child)
void unkfunc_02121df4(void* arg);
BOOL unkfunc_02121e28();                                        // disconnect (child)
void unkfunc_02121e60(void* arg);
BOOL unkfunc_02121e84();                                        // reset
void unkfunc_02121eb4(void* arg);
void unkfunc_02121ee8(void* arg);
void unkfunc_02121f10(u32 ggid);
void unkfunc_02121f20(BOOL (*judge)(void* arg));
u16 unkfunc_02121f40();                                         // connected bitmap
int unkfunc_02121f50();                                         // system state
const char* unkfunc_02121f60();                                 // system state name
void unkfunc_02122030(WMBssDesc* desc);                         // print a parent description
BOOL unkfunc_021221fc();                                        // measure the channels
u16 unkfunc_021222bc(u16 channel);                              // measure a channel
void unkfunc_02122358(void* arg);
int unkfunc_02122400(void (*callback)(void* arg), u16 channel);
u16 unkfunc_02122420();                                         // best channel
s16 unkfunc_0212244c(u16 bitmap);                               // pick a channel
BOOL unkfunc_02122528();                                        // initialize
void unkfunc_021225bc(void* arg);
BOOL unkfunc_021225d8();
void unkfunc_0212261c(void* arg);
BOOL unkfunc_02122684(int mode, u16 tgid, u16 channel, u16 beaconPeriod);   // parent connect
BOOL unkfunc_02122740(int mode, WMBssDesc* desc);               // child connect
u16* unkfunc_021227cc(u16 aid);                                 // shared data of a child
BOOL unkfunc_021227ec(const void* data);                        // data sharing step
void unkfunc_02122840();                                        // reset
void unkfunc_02122888();                                        // finalize
BOOL unkfunc_02122998();                                        // end
void unkfunc_021229e0(void (*callback)(void* arg));             // indication callback
int unkfunc_021229f0();                                         // beacon count
void unkfunc_02122a00(int value);
