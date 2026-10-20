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

void printWhDebug(const char* fmt, ...);                    // debug print (empty)
void changeWhSysState(int state);                               // set the system state
void setWhError(int code);                                // set the error code
BOOL setWhParentParam();                                        // set the parent parameter
void onSetParentParamCallback(void* arg);
BOOL setWhParentWepKey();                                        // set the parent WEP key
void unkfunc_02121220(void* arg);
BOOL startWhParent();                                        // start the parent
void unkfunc_021212b0(void* arg);
BOOL unkfunc_021213cc();                                        // start MP (parent)
void unkfunc_02121460(void* arg);
BOOL unkfunc_02121544();                                        // start key sharing (parent)
BOOL endWhParentKeySharing();                                        // end key sharing (parent)
BOOL endWhParentMP();                                        // end MP (parent)
void onEndParentMPCallback(void* arg);
BOOL endWhParent();                                        // end the parent
void unkfunc_02121640(void* arg);
BOOL startWhScan(void (*callback)(WMBssDesc*), const u8* bssid, u16 channel);  // start the scan
BOOL scanWhNextChannel();                                        // scan the next channel
void unkfunc_02121798(void* arg);
BOOL endWhScan();                                        // end the scan
BOOL unkfunc_02121928();                                        // end the scan (WM)
void onEndScanCallback(void* arg);
BOOL setWhChildWepKey();                                        // set the child WEP key
void unkfunc_02121a20(void* arg);
BOOL startWhChildConnect();                                        // start the connection
void onStartConnectCallback(void* arg);
BOOL startWhChildMP();                                        // start MP (child)
void unkfunc_02121c2c(void* arg);
BOOL unkfunc_02121d14();                                        // start key sharing (child)
BOOL endWhChildKeySharing();                                        // end key sharing (child)
BOOL endWhChildMP();                                        // end MP (child)
void onEndChildMPCallback(void* arg);
BOOL disconnectWhChild();                                        // disconnect (child)
void unkfunc_02121e60(void* arg);
BOOL requestWhReset();                                        // reset
void onResetCallback(void* arg);
void onWhEndCallback(void* arg);
void unkfunc_02121f10(u32 ggid);
void setWhJudgeAcceptFunc(BOOL (*judge)(void* arg));
u16 getWhConnectBitmap();                                         // connected bitmap
int getWhSysState();                                         // system state
const char* getWhSysStateName();                                 // system state name
void printWhBssDesc(WMBssDesc* desc);                         // print a parent description
BOOL startWhMeasureChannel();                                        // measure the channels
u16 measureWhNextChannel(u16 channel);                              // measure a channel
void onMeasureChannelCallback(void* arg);
int measureWhChannel(void (*callback)(void* arg), u16 channel);
u16 getWhBestChannel();                                         // best channel
s16 selectWhRandomChannel(u16 bitmap);                               // pick a channel
BOOL initWh();                                        // initialize
void onWhIndicateCallback(void* arg);
BOOL initWhWM();
void unkfunc_0212261c(void* arg);
BOOL connectWhParent(int mode, u16 tgid, u16 channel, u16 beaconPeriod);   // parent connect
BOOL connectWhChild(int mode, WMBssDesc* desc);               // child connect
u16* getWhSharedData(u16 aid);                                 // shared data of a child
BOOL unkfunc_021227ec(const void* data);                        // data sharing step
void resetWh();                                        // reset
void finalizeWh();                                        // finalize
BOOL endWh();                                        // end
void unkfunc_021229e0(void (*callback)(void* arg));             // indication callback
int unkfunc_021229f0();                                         // beacon count
void unkfunc_02122a00(int value);
