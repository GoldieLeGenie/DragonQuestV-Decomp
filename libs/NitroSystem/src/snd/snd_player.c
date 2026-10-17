// Sequence player management (second half of the player module).
#include "snd_internal.h"

#pragma thumb on

typedef struct UnkSndFader {
    /* 0x00 */ s32 origin;
    /* 0x04 */ s32 target;
    /* 0x08 */ s32 counter;
    /* 0x0C */ s32 frames;
} UnkSndFader;

struct UnkSndHandle;
struct UnkSndPlayer;
struct UnkSndPlayerHeap;

typedef struct UnkSndSeqPlayer {
    /* 0x00 */ struct UnkSndHandle* handle;
    /* 0x04 */ struct UnkSndPlayer* player;
    /* 0x08 */ struct UnkSndPlayerHeap* heap;
    /* 0x0C */ UnkLink prioLink;
    /* 0x14 */ UnkLink playerLink;
    /* 0x1C */ UnkSndFader fader;
    /* 0x2C */ u8 status;
    /* 0x2D */ u8 unk_2d;
    /* 0x2E */ u8 unk_2e;
    /* 0x2F */ u8 unk_2f;
    /* 0x30 */ u32 commandTag;
    /* 0x34 */ u16 unk_34;
    /* 0x36 */ u8 unk_36[6];
    /* 0x3C */ u8 playerNo;
    /* 0x3D */ u8 prio;
    /* 0x3E */ u16 unk_3e;
    /* 0x40 */ u8 unk_40;
    /* 0x41 */ u8 unk_41;
} UnkSndSeqPlayer;

typedef struct UnkSndHandle {
    /* 0x00 */ UnkSndSeqPlayer* player;
} UnkSndHandle;

typedef struct UnkSndPlayer {
    /* 0x00 */ UnkList playerList;
    /* 0x0C */ UnkList heapList;
    /* 0x18 */ u32 playableSeqCount;
    /* 0x1C */ u32 allocChBitFlag;
    /* 0x20 */ u32 unk_20;
} UnkSndPlayer; // size 0x24

typedef struct UnkSndPlayerHeap {
    /* 0x00 */ UnkLink link;
    /* 0x08 */ void* heap;
    /* 0x0C */ UnkSndSeqPlayer* seqPlayer;
    /* 0x10 */ int playerNo;
} UnkSndPlayerHeap;

extern UnkList data_02122d0c;           // free seq player list
extern UnkList data_02122d18;           // priority ordered seq player list
extern UnkSndPlayer data_02123164[];    // players

void func_0207b524(UnkSndHandle* handle);
void func_0207c648(void* heap);
void func_0207c658(void* heap);
void func_0207e238(UnkSndFader* fader, s32 target, s32 frames);
void func_0207e22c(UnkSndFader* fader);

void func_0207b804(UnkSndSeqPlayer* seqPlayer, const void* seq, u32 offset, const void* bank);
void func_0207b844(UnkSndSeqPlayer* seqPlayer, int fadeFrame);
void func_0207b87c(UnkSndSeqPlayer* seqPlayer, BOOL flag);
void* func_0207b8a0(int playerNo, UnkSndSeqPlayer* seqPlayer);
void func_0207b8dc(UnkSndSeqPlayer* seqPlayer);
void func_0207b91c(UnkSndPlayer* player, UnkSndSeqPlayer* seqPlayer);
void func_0207b954(UnkSndSeqPlayer* seqPlayer);
void func_0207b990(UnkSndSeqPlayer* seqPlayer);
UnkSndSeqPlayer* func_0207b9c0(int prio);
void func_0207ba0c(UnkSndSeqPlayer* seqPlayer);
void func_0207ba60(UnkSndPlayerHeap* heap);
void func_0207ba94(UnkSndSeqPlayer* seqPlayer, int prio);

UnkSndSeqPlayer* func_0207b798(UnkSndHandle* handle, int playerNo, int prio) {
    UnkSndPlayer* player = &data_02123164[playerNo];
    UnkSndSeqPlayer* seqPlayer;

    if (handle->player != NULL) {
        func_0207b524(handle);
    }

    if (player->playerList.numObjects >= player->playableSeqCount) {
        seqPlayer = func_0207e384(&player->playerList, NULL);
        if (seqPlayer == NULL) {
            return NULL;
        }
        if (prio < seqPlayer->prio) {
            return NULL;
        }
        func_0207b990(seqPlayer);
    }

    seqPlayer = func_0207b9c0(prio);
    if (seqPlayer == NULL) {
        return NULL;
    }

    func_0207b91c(player, seqPlayer);
    seqPlayer->handle = handle;
    handle->player = seqPlayer;
    return seqPlayer;
}

void func_0207b7fc(UnkSndSeqPlayer* seqPlayer) {
    func_0207ba0c(seqPlayer);
}

void func_0207b804(UnkSndSeqPlayer* seqPlayer, const void* seq, u32 offset, const void* bank) {
    UnkSndPlayer* player = seqPlayer->player;

    func_02077a80(seqPlayer->playerNo, seq, offset, bank);
    if (player->allocChBitFlag != 0) {
        func_02077ae8(seqPlayer->playerNo, 0xFFFF, player->allocChBitFlag);
    }
    func_0207b8dc(seqPlayer);
    seqPlayer->commandTag = func_02078010();
    seqPlayer->unk_2f = 1;
    seqPlayer->status = 1;
}

void func_0207b844(UnkSndSeqPlayer* seqPlayer, int fadeFrame) {
    if (seqPlayer == NULL || seqPlayer->status == 0) {
        return;
    }

    if (fadeFrame == 0) {
        func_0207b990(seqPlayer);
        return;
    }

    func_0207e238(&seqPlayer->fader, 0, fadeFrame);
    func_0207ba94(seqPlayer, 0);
    seqPlayer->status = 2;
}

void func_0207b87c(UnkSndSeqPlayer* seqPlayer, BOOL flag) {
    if (seqPlayer == NULL) {
        return;
    }
    if (flag == seqPlayer->unk_2e) {
        return;
    }
    func_02077ab0(seqPlayer->playerNo, flag);
    seqPlayer->unk_2e = flag;
}

void* func_0207b8a0(int playerNo, UnkSndSeqPlayer* seqPlayer) {
    UnkSndPlayer* player = &data_02123164[playerNo];
    UnkSndPlayerHeap* heap;

    heap = func_0207e384(&player->heapList, NULL);
    if (heap == NULL) {
        return NULL;
    }
    func_0207e348(&player->heapList, heap);
    heap->seqPlayer = seqPlayer;
    seqPlayer->heap = heap;
    func_0207c658(heap->heap);
    return heap->heap;
}

void func_0207b8dc(UnkSndSeqPlayer* seqPlayer) {
    seqPlayer->unk_2e = 0;
    seqPlayer->unk_2d = 0;
    seqPlayer->unk_2f = 0;
    seqPlayer->unk_34 = 0;
    seqPlayer->unk_3e = 0;
    seqPlayer->unk_40 = 0x7F;
    seqPlayer->unk_41 = 0x7F;
    func_0207e22c(&seqPlayer->fader);
    func_0207e238(&seqPlayer->fader, 0x7F00, 1);
}

void func_0207b91c(UnkSndPlayer* player, UnkSndSeqPlayer* seqPlayer) {
    UnkSndSeqPlayer* next = func_0207e384(&player->playerList, NULL);

    while (next != NULL) {
        if (seqPlayer->prio < next->prio) {
            break;
        }
        next = func_0207e384(&player->playerList, next);
    }

    func_0207e310(&player->playerList, next, seqPlayer);
    seqPlayer->player = player;
}

void func_0207b954(UnkSndSeqPlayer* seqPlayer) {
    UnkSndSeqPlayer* next = func_0207e384(&data_02122d18, NULL);

    while (next != NULL) {
        if (seqPlayer->prio < next->prio) {
            break;
        }
        next = func_0207e384(&data_02122d18, next);
    }

    func_0207e310(&data_02122d18, next, seqPlayer);
}

void func_0207b990(UnkSndSeqPlayer* seqPlayer) {
    if (seqPlayer->status == 2) {
        func_02077ac8(seqPlayer->playerNo, -723);
    }
    func_02077a6c(seqPlayer->playerNo);
    func_0207ba0c(seqPlayer);
}

UnkSndSeqPlayer* func_0207b9c0(int prio) {
    UnkSndSeqPlayer* seqPlayer = func_0207e384(&data_02122d0c, NULL);

    if (seqPlayer == NULL) {
        seqPlayer = func_0207e384(&data_02122d18, NULL);
        if (prio < seqPlayer->prio) {
            return NULL;
        }
        func_0207b990(seqPlayer);
    }

    func_0207e348(&data_02122d0c, seqPlayer);
    seqPlayer->prio = prio;
    func_0207b954(seqPlayer);
    return seqPlayer;
}

void func_0207ba0c(UnkSndSeqPlayer* seqPlayer) {
    UnkSndPlayer* player;

    if (seqPlayer->handle != NULL) {
        seqPlayer->handle->player = NULL;
        seqPlayer->handle = NULL;
    }

    player = seqPlayer->player;
    func_0207e348(&player->playerList, seqPlayer);
    seqPlayer->player = NULL;

    if (seqPlayer->heap != NULL) {
        func_0207e2b8(&player->heapList, seqPlayer->heap);
        seqPlayer->heap->seqPlayer = NULL;
        seqPlayer->heap = NULL;
    }

    func_0207e348(&data_02122d18, seqPlayer);
    func_0207e2b8(&data_02122d0c, seqPlayer);
    seqPlayer->status = 0;
}

void func_0207ba60(UnkSndPlayerHeap* heap) {
    if (heap->heap == NULL) {
        return;
    }

    func_0207c648(heap->heap);

    if (heap->seqPlayer != NULL) {
        heap->seqPlayer->heap = NULL;
    } else {
        func_0207e348(&data_02123164[heap->playerNo].heapList, heap);
    }
}

void func_0207ba94(UnkSndSeqPlayer* seqPlayer, int prio) {
    UnkSndPlayer* player = seqPlayer->player;

    if (player != NULL) {
        func_0207e348(&player->playerList, seqPlayer);
        seqPlayer->player = NULL;
    }

    func_0207e348(&data_02122d18, seqPlayer);
    seqPlayer->prio = prio;

    if (player != NULL) {
        func_0207b91c(player, seqPlayer);
    }

    func_0207b954(seqPlayer);
}
