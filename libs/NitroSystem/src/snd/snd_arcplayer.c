// Sound archive player: player setup from the archive and sequence start helpers.
#include "snd_internal.h"

#pragma thumb on

typedef struct UnkSndPlayerInfo {
    /* 0x00 */ u8 seqMax;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u16 allocChBitFlag;
    /* 0x04 */ u32 heapSize;
} UnkSndPlayerInfo;

typedef struct UnkSndSeqParam {
    /* 0x00 */ u32 fileId; // offset inside the archive for a sequence archive entry
    /* 0x04 */ u16 bankNo;
    /* 0x06 */ u8 volume;
    /* 0x07 */ u8 channelPrio;
    /* 0x08 */ u8 playerPrio;
    /* 0x09 */ u8 playerNo;
} UnkSndSeqParam;

typedef struct UnkSndSeqData {
    /* 0x00 */ u8 unk_00[0x18];
    /* 0x18 */ u32 dataOffset;
} UnkSndSeqData;

void* func_0207c298(void);
void* func_0207c2a4(int index);
void* func_0207c2f0(int index);
void* func_0207c420(int index);
void* func_0207c5b0(u32 fileId);
int   func_0207c894(int seqNo, u32 flags, void* heap, BOOL addToArc, void** pData);
int   func_0207c920(int bankNo, u32 flags, void* heap, BOOL addToArc, void** pData);
UnkSndSeqParam* func_0207e200(void* seqArc, int index);
void* func_0207b798(void* handle, int playerNo, int prio);
void  func_0207b7fc(void* seqPlayer);
void  func_0207b804(void* seqPlayer, const void* seq, u32 offset, const void* bank);
void* func_0207b8a0(int playerNo, void* seqPlayer);
void  func_0207b480(int playerNo, int seqMax);
void  func_0207b494(int playerNo, u32 allocChBitFlag);
BOOL  func_0207b4a4(int playerNo, void* heap, u32 size);
void  func_0207b578(void* handle, int volume);
void  func_0207b588(void* handle, int prio);
void  func_0207b5b0(void* handle, int seqNo);
void  func_0207b5c4(void* handle, int seqArcNo, int index);

BOOL func_0207cf98(void* handle, int playerNo, int bankNo, int playerPrio, UnkSndSeqParam* param, int seqNo);
BOOL func_0207d02c(void* handle, int playerNo, int bankNo, int playerPrio, UnkSndSeqParam* param, UnkSndSeqData* seqArc, int seqArcNo, int index);

BOOL func_0207ce50(void* heap) {
    int i;

    func_0207c298();

    for (i = 0; i < 32; i++) {
        UnkSndPlayerInfo* info = func_0207c420(i);
        if (info == NULL) {
            continue;
        }

        func_0207b480(i, info->seqMax);
        func_0207b494(i, info->allocChBitFlag);

        if (info->heapSize != 0 && heap != NULL) {
            int j;
            for (j = 0; j < info->seqMax; j++) {
                if (!func_0207b4a4(i, heap, info->heapSize)) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

BOOL func_0207ceac(void* handle, int seqNo) {
    UnkSndSeqParam* info = func_0207c2a4(seqNo);

    if (info == NULL) {
        return FALSE;
    }
    return func_0207cf98(handle, info->playerNo, info->bankNo, info->playerPrio, info, seqNo);
}

BOOL func_0207ced8(void* handle, int seqArcNo, int index) {
    u32* info = func_0207c2f0(seqArcNo);
    UnkSndSeqData* seqArc;
    UnkSndSeqParam* param;

    if (info == NULL) {
        return FALSE;
    }

    seqArc = func_0207c5b0(*info);
    if (seqArc == NULL) {
        return FALSE;
    }

    param = func_0207e200(seqArc, index);
    if (param == NULL) {
        return FALSE;
    }

    return func_0207d02c(handle, param->playerNo, param->bankNo, param->playerPrio, param, seqArc, seqArcNo, index);
}

BOOL func_0207cf2c(void* handle, int playerNo, int bankNo, int playerPrio, int seqArcNo, int index) {
    u32* info = func_0207c2f0(seqArcNo);
    UnkSndSeqData* seqArc;
    UnkSndSeqParam* param;

    if (info == NULL) {
        return FALSE;
    }

    seqArc = func_0207c5b0(*info);
    if (seqArc == NULL) {
        return FALSE;
    }

    param = func_0207e200(seqArc, index);
    if (param == NULL) {
        return FALSE;
    }

    if (playerPrio < 0) {
        playerPrio = param->playerPrio;
    }
    if (bankNo < 0) {
        bankNo = param->bankNo;
    }
    if (playerNo < 0) {
        playerNo = param->playerNo;
    }
    return func_0207d02c(handle, playerNo, bankNo, playerPrio, param, seqArc, seqArcNo, index);
}

BOOL func_0207cf98(void* handle, int playerNo, int bankNo, int playerPrio, UnkSndSeqParam* param, int seqNo) {
    void* seqPlayer;
    void* heap;
    UnkSndSeqData* seq;
    void* bank;

    seqPlayer = func_0207b798(handle, playerNo, playerPrio);
    if (seqPlayer == NULL) {
        return FALSE;
    }

    heap = func_0207b8a0(playerNo, seqPlayer);

    if (func_0207c920(bankNo, 6, heap, FALSE, &bank) != 0) {
        func_0207b7fc(seqPlayer);
        return FALSE;
    }

    if (func_0207c894(seqNo, 1, heap, FALSE, (void**)&seq) != 0) {
        func_0207b7fc(seqPlayer);
        return FALSE;
    }

    func_0207b804(seqPlayer, (u8*)seq + seq->dataOffset, 0, bank);
    func_0207b578(handle, param->volume);
    func_0207b588(handle, param->channelPrio);
    func_0207b5b0(handle, seqNo);
    return TRUE;
}

BOOL func_0207d02c(void* handle, int playerNo, int bankNo, int playerPrio, UnkSndSeqParam* param, UnkSndSeqData* seqArc, int seqArcNo, int index) {
    void* seqPlayer;
    void* heap;
    void* bank;

    seqPlayer = func_0207b798(handle, playerNo, playerPrio);
    if (seqPlayer == NULL) {
        return FALSE;
    }

    heap = func_0207b8a0(playerNo, seqPlayer);

    if (func_0207c920(bankNo, 6, heap, FALSE, &bank) != 0) {
        func_0207b7fc(seqPlayer);
        return FALSE;
    }

    func_0207b804(seqPlayer, (u8*)seqArc + seqArc->dataOffset, param->fileId, bank);
    func_0207b578(handle, param->volume);
    func_0207b588(handle, param->channelPrio);
    func_0207b5c4(handle, seqArcNo, index);
    return TRUE;
}
