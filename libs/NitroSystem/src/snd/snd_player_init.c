#include "../nns_internal.h"

#pragma thumb on

typedef struct {
    void* prevObject;                       /* 0x00 */
    void* nextObject;                       /* 0x04 */
} UnkFndLink;

typedef struct {
    void* headObject;                       /* 0x00 */
    void* tailObject;                       /* 0x04 */
    u16 numObjects;                         /* 0x08 */
    u16 offset;                             /* 0x0A */
} UnkFndList;

typedef struct {
    u8 unk_00[0x10];                        /* 0x00 */
} UnkSndFader;

typedef struct {
    u8 unk_00[0x20];
    u8 volume;                              /* 0x20 */
} UnkSndPlayerGroup;

struct UnkSndHandle;

typedef struct UnkSndSeqPlayer {
    struct UnkSndHandle* handle;            /* 0x00 */
    UnkSndPlayerGroup* player;              /* 0x04 */
    u8 unk_08[0x14 - 0x08];                 /* 0x08 */
    UnkFndLink prioLink;                    /* 0x14 */
    UnkSndFader fader;                      /* 0x1C */
    u8 status;                              /* 0x2C */
    u8 startedFlag;                         /* 0x2D */
    u8 unk_2e;                              /* 0x2E */
    u8 updateFlag;                          /* 0x2F */
    u32 commandTag;                         /* 0x30 */
    u16 seqType;                            /* 0x34 */
    u16 unk_36;                             /* 0x36 */
    u16 seqNo;                              /* 0x38 */
    u16 seqArcIndex;                        /* 0x3A */
    u8 playerNo;                            /* 0x3C */
    u8 unk_3d;                              /* 0x3D */
    s16 extVolume;                          /* 0x3E */
    u8 initVolume;                          /* 0x40 */
    u8 volume;                              /* 0x41 */
    u8 unk_42[2];                           /* 0x42 */
} UnkSndSeqPlayer;

typedef struct UnkSndHandle {
    UnkSndSeqPlayer* volatile player;       /* 0x00 */
} UnkSndHandle;

typedef struct {
    UnkFndList playerList;                  /* 0x00 */
    UnkFndList heapList;                    /* 0x0C */
    u32 playableSeqCount;                   /* 0x18 */
    u32 allocSize;                          /* 0x1C */
    u8 volume;                              /* 0x20 */
    u8 unk_21[3];                           /* 0x21 */
} UnkSndPlayerGroupState;

typedef struct {
    UnkFndLink link;                        /* 0x00 */
    void* heap;                             /* 0x08 */
    u32 unk_0c;                             /* 0x0C */
    int playerNo;                           /* 0x10 */
} UnkSndPlayerHeap;

UnkFndList data_02122d0c;               /* free player list */
UnkFndList data_02122d18;               /* priority player list */
UnkSndSeqPlayer data_02122d24[16];
UnkSndPlayerGroupState data_02123164[32];
extern const s16 data_0208e0a0[];

void func_0207e290(UnkFndList* list, u16 offset);
void func_0207e2b8(UnkFndList* list, void* object);
void* func_0207e384(UnkFndList* list, void* object);
void* func_0207c6c8(void* heap, u32 size, void (*callback)(void*, u32, u32, u32), u32 data1, u32 data2);
void* func_0207c5fc(void* buffer, u32 size);
void func_0207ba60(void* mem, u32 size, u32 data1, u32 data2);
void func_0207b844(UnkSndSeqPlayer* player);
void func_0207b87c(UnkSndSeqPlayer* player, BOOL flag);
void func_02077ad8(u32 playerNo, int fadeFrame);
BOOL func_02078234(u32 playerNo);
u32 func_02078218(void);
BOOL func_02078030(u32 tag);
void func_0207ba0c(UnkSndSeqPlayer* player);
void func_0207e270(UnkSndFader* fader);
int func_0207e250(UnkSndFader* fader);
BOOL func_0207e280(UnkSndFader* fader);
void func_02077ac8(u32 playerNo, int volume);
void func_0207b990(UnkSndSeqPlayer* player);
void func_02077a9c(u32 playerNo);

void func_0207b480(int playerNo, int seqCount)
{
    data_02123164[playerNo].playableSeqCount = (u16)seqCount;
}

void func_0207b494(int playerNo, u32 size)
{
    data_02123164[playerNo].allocSize = size;
}

BOOL func_0207b4a4(int playerNo, void* heap, u32 size)
{
    UnkSndPlayerHeap* playerHeap;
    void* buffer;

    playerHeap = func_0207c6c8(heap, size + sizeof(UnkSndPlayerHeap), func_0207ba60, 0, 0);
    if (playerHeap == NULL) {
        return FALSE;
    }
    playerHeap->unk_0c = 0;
    playerHeap->playerNo = playerNo;
    playerHeap->heap = NULL;

    buffer = func_0207c5fc(playerHeap + 1, size);
    if (buffer == NULL) {
        return FALSE;
    }
    playerHeap->heap = buffer;
    func_0207e2b8(&data_02123164[playerNo].heapList, playerHeap);
    return TRUE;
}

void func_0207b504(UnkSndHandle* handle)
{
    func_0207b844(handle->player);
}

void func_0207b510(UnkSndHandle* handle, BOOL flag)
{
    func_0207b87c(handle->player, flag);
}

void func_0207b51c(UnkSndHandle* handle)
{
    handle->player = NULL;
}

void func_0207b524(UnkSndHandle* handle)
{
    if (handle->player == NULL) {
        return;
    }
    handle->player->handle = NULL;
    handle->player = NULL;
}

int func_0207b534(u16 seqNo)
{
    int count = 0;
    UnkSndSeqPlayer* player = func_0207e384(&data_02122d18, NULL);

    while (player != NULL) {
        if (player->seqType == 1 && player->seqNo == seqNo) {
            count++;
        }
        player = func_0207e384(&data_02122d18, player);
    }
    return count;
}

void func_0207b568(UnkSndHandle* handle, u8 volume)
{
    if (handle->player != NULL) {
        handle->player->volume = volume;
    }
}

void func_0207b578(UnkSndHandle* handle, u8 volume)
{
    if (handle->player != NULL) {
        handle->player->initVolume = volume;
    }
}

void func_0207b588(UnkSndHandle* handle, int fadeFrame)
{
    if (handle->player == NULL) {
        return;
    }
    func_02077ad8(handle->player->playerNo, fadeFrame);
}

void func_0207b59c(UnkSndHandle* handle, u32 trackBitMask, u32 chBitMask)
{
    if (handle->player == NULL) {
        return;
    }
    func_02077ae8(handle->player->playerNo, trackBitMask, chBitMask);
}

void func_0207b5b0(UnkSndHandle* handle, u16 seqNo)
{
    if (handle->player == NULL) {
        return;
    }
    handle->player->seqType = 1;
    handle->player->seqNo = seqNo;
}

void func_0207b5c4(UnkSndHandle* handle, u16 seqArcNo, u16 index)
{
    if (handle->player == NULL) {
        return;
    }
    handle->player->seqType = 2;
    handle->player->seqNo = seqArcNo;
    handle->player->seqArcIndex = index;
}

BOOL func_0207b5e0(UnkSndHandle* handle)
{
    UnkSndSeqPlayer* player;

    if (handle->player == NULL) {
        return FALSE;
    }
    player = handle->player;
    if (!player->startedFlag) {
        return FALSE;
    }
    return func_02078234(player->playerNo);
}

void func_0207b608(void)
{
    int i;
    UnkSndSeqPlayer* player;
    UnkSndPlayerGroupState* group;

    func_0207e290(&data_02122d18, 0x14);
    func_0207e290(&data_02122d0c, 0x14);

    player = data_02122d24;
    for (i = 0; i < 16; i++, player++) {
        player->status = 0;
        player->playerNo = i;
        func_0207e2b8(&data_02122d0c, player);
    }

    group = data_02123164;
    for (i = 0; i < 32; i++, group++) {
        func_0207e290(&group->playerList, 0xc);
        func_0207e290(&group->heapList, 0);
        group->volume = 0x7f;
        group->playableSeqCount = 1;
        group->allocSize = 0;
    }
}

void func_0207b680(void)
{
    UnkSndSeqPlayer* player;
    UnkSndSeqPlayer* next;
    int volume;
    u32 status;
    int seqVol, initVol, groupVol;

    status = func_02078218();
    player = func_0207e384(&data_02122d18, NULL);

    while (player != NULL) {
        next = func_0207e384(&data_02122d18, player);

        if (!player->startedFlag) {
            if (func_02078030(player->commandTag)) {
                player->startedFlag = TRUE;
            }
        }

        if (player->startedFlag && !(status & (1 << player->playerNo))) {
            func_0207ba0c(player);
        } else {
            func_0207e270(&player->fader);
            seqVol = data_0208e0a0[player->volume];
            initVol = data_0208e0a0[player->initVolume];
            groupVol = data_0208e0a0[player->player->volume];
            volume = data_0208e0a0[func_0207e250(&player->fader) >> 8];
            volume += initVol + seqVol + groupVol;
            if (volume < -0x8000) {
                volume = -0x8000;
            } else if (volume > 0x7fff) {
                volume = 0x7fff;
            }
            if (volume != player->extVolume) {
                func_02077ac8(player->playerNo, volume);
                player->extVolume = volume;
            }
            if (player->status == 2 && func_0207e280(&player->fader)) {
                func_0207b990(player);
            }
            if (player->updateFlag) {
                func_02077a9c(player->playerNo);
                player->updateFlag = FALSE;
            }
        }
        player = next;
    }
}
