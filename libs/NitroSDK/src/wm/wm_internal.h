#ifndef WM_INTERNAL_H
#define WM_INTERNAL_H

#include "../sdk_internal.h"
#include <stdarg.h>

typedef void (*UnkWmCallbackFunc)(void* arg);

/* Status block shared with ARM7 (only the fields used here). */
typedef struct UnkWmStatus {
    u16 state;    // 0x000
    u8 unk_002[0xa];
    u32 unk_00c;  // 0x00c: MP active
    u8 unk_010[0x2c];
    u16 unk_03c;  // 0x03c
    u16 unk_03e;  // 0x03e
    u8 unk_040[0x32];
    u16 unk_072;  // 0x072
    u8 unk_074[0x8];
    u32 unk_07c;  // 0x07c
    u8 unk_080[0x6];
    u16 unk_086;  // 0x086: MP ready AIDs
    u8 unk_088[0x14];
    u16 unk_09c;  // 0x09c
    u8 unk_09e[0x1e];
    u16 unk_0bc;  // 0x0bc
    u8 unk_0be[0x8];
    u16 unk_0c6;  // 0x0c6
    u8 unk_0c8[0x30];
    u16 unk_0f8;  // 0x0f8
    u8 unk_0fa[0x88];
    u16 unk_182;  // 0x182: connected children
    u8 unk_184[0x4];
    u16 unk_188;  // 0x188: own AID
} UnkWmStatus;

typedef struct UnkWmArm9Buf {
    void* unk_000;                        // 0x000
    UnkWmStatus* status;                  // 0x004
    void* unk_008;                        // 0x008
    void* unk_00c;                        // 0x00c
    void* unk_010;                        // 0x010: ARM7 -> ARM9 fifo buffer
    u16 dmaNo;                            // 0x014
    u16 unk_016;                          // 0x016
    UnkWmCallbackFunc callbackTable[0x2c]; // 0x018
    UnkWmCallbackFunc indCallback;        // 0x0c8
    UnkWmCallbackFunc portCallbackTable[16]; // 0x0cc
    void* portCallbackArgument[16];       // 0x10c
    u32 connectedAidBitmap;               // 0x14c
    u16 myAid;                            // 0x150
} UnkWmArm9Buf;

typedef struct UnkWmCallback {
    u16 apiid;
    u16 errcode;
} UnkWmCallback;

typedef struct UnkWmPortRecvCallback {
    u16 apiid;              // 0x00
    u16 errcode;            // 0x02
    u16 state;              // 0x04
    u16 port;               // 0x06
    u16* recvBuf;           // 0x08
    u16* data;              // 0x0c
    u16 length;             // 0x10
    u16 aid;                // 0x12
    u8 macAddress[6];       // 0x14
    u16 seqNo;              // 0x1a
    void* arg;              // 0x1c
    u16 myAid;              // 0x20
    u16 connectedAidBitmap; // 0x22
    u8 ssid[24];            // 0x24
    u16 reason;             // 0x3c
    u16 rssi;               // 0x3e
    u16 maxSendDataSize;    // 0x40
    u16 maxRecvDataSize;    // 0x42
} UnkWmPortRecvCallback;

typedef struct UnkWmPortSendCallback {
    u16 apiid;   // 0x00
    u16 errcode; // 0x02
    u8 unk_04[6];
    u16 port;    // 0x0a
    u8 unk_0c[0xe];
    u16 seqNo;   // 0x1a
    void* callback; // 0x1c
    void* arg;   // 0x20
} UnkWmPortSendCallback;

typedef struct UnkWmStartMPCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 unk_06;
    u16* recvBuf;
} UnkWmStartMPCallback;

typedef struct UnkWmUnknownCallback {
    u16 apiid;
    u16 errcode;
    u8 unk_04[0x18];
    UnkWmCallbackFunc callback; // 0x1c
} UnkWmUnknownCallback;

typedef struct UnkWmStartParentCallback {
    u16 apiid;          // 0x00
    u16 errcode;        // 0x02
    u8 unk_04[4];
    u16 state;          // 0x08
    u8 macAddress[6];   // 0x0a
    u16 aid;            // 0x10
    u16 reason;         // 0x12
    u8 ssid[24];        // 0x14
    u16 parentSize;     // 0x2c
    u16 childSize;      // 0x2e
} UnkWmStartParentCallback;

typedef struct UnkWmStartConnectCallback {
    u16 apiid;          // 0x00
    u16 errcode;        // 0x02
    u8 unk_04[4];
    u16 state;          // 0x08
    u16 aid;            // 0x0a
    u16 reason;         // 0x0c
    u8 unk_0e[2];
    u8 macAddress[6];   // 0x10
    u16 parentSize;     // 0x16
    u16 childSize;      // 0x18
} UnkWmStartConnectCallback;

typedef struct UnkWmSystem {
    u16 initialized;                 // 0x00
    u16 unk_02;
    UnkWmArm9Buf* buf;               // 0x04
    UnkMessageQueue queue;           // 0x08
    void* queueArray[10];            // 0x28
    UnkWmPortRecvCallback portCb;    // 0x50
} UnkWmSystem;

typedef struct UnkWmDataSet {
    u16 aidBitmap;
    u16 receivedBitmap;
    u16 data[14];
    u16 childData[240]; // 0x20: child send area
} UnkWmDataSet;

typedef struct UnkWmDataSharingInfo {
    UnkWmDataSet ds[4];   // 0x000
    u16 seqNum[4];        // 0x800
    u16 writeIndex;       // 0x808
    u16 sendIndex;        // 0x80a
    u16 readIndex;        // 0x80c
    u16 aidBitmap;        // 0x80e
    u16 dataLength;       // 0x810
    u16 stationNumber;    // 0x812
    u16 dataSetLength;    // 0x814
    u16 port;             // 0x816
    u16 doubleMode;       // 0x818
    u16 currentSeqNum;    // 0x81a
    u16 state;            // 0x81c
    u16 reserved;         // 0x81e
} UnkWmDataSharingInfo;

u32 func_02079af8(void* buf, u16 dmaNo);
u32 func_02079b14(void* buf, u16 dmaNo, u32 size);
u32 func_02079c4c(void);
void func_02079c94(u32 id, UnkWmCallbackFunc callback);
u32* func_02079ca4(void);
u32 func_02079ce0(u16 id, u16 paramNum, ...);
u32 func_02079d5c(void* data, u32 length);
UnkWmArm9Buf* func_02079da8(void);
u32 func_02079db4(void);
u32 func_02079dc8(void);
u32 func_02079df8(s32 paramNum, ...);
void func_02079e48(u32 tag, u32 data, BOOL err);
void func_0207a0d4(void);
u16 func_0207a0ec(void);
u16 func_0207a110(void);
u32 func_0207a168(u16 port, UnkWmCallbackFunc callback, void* arg);
s32 func_0207a1fc(void);
s32 func_0207a240(void);

BOOL func_0207a540(void* param);
u32 func_0207a570(UnkWmCallbackFunc callback, BOOL powerSave);
u32 func_0207a79c(UnkWmCallbackFunc callback, u16* recvBuf, s32 recvBufSize, u16* sendBuf, u16 sendBufSize,
                  void* tmpParam);
u32 func_0207a8d8(UnkWmCallbackFunc callback, void* arg, const u16* sendData, u16 sendDataSize, u16 destBitmap,
                  u16 port, u16 prio);

u32 func_0207a9ec(UnkWmDataSharingInfo* dsInfo, u16 port, u16 aidBitmap, u16 dataLength, BOOL doubleMode);
u32 func_0207abb4(UnkWmDataSharingInfo* dsInfo);
void func_0207ae3c(void* arg);
void func_0207aecc(void* arg);
void func_0207af88(void* arg);
void func_0207b02c(UnkWmDataSharingInfo* dsInfo, u16 aid, u16* data);
void func_0207b0b8(UnkWmDataSharingInfo* dsInfo, BOOL delayed);
u16* func_0207b1ec(UnkWmDataSharingInfo* dsInfo, u32 aidBitmap, u16* data, u32 aid);

u32 func_0207a428(void* buf, UnkWmCallbackFunc callback, u16 dmaNo, u32 flags);

/* RTC (rtc library) */
typedef struct UnkRtcTime {
    u32 hour;   // 0x00
    u32 minute; // 0x04
    u32 second; // 0x08
} UnkRtcTime;

void func_020775a0(void);
s32 func_02077628(UnkRtcTime* time);

#endif
