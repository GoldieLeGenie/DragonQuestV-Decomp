// DS Protect anti-piracy runtime (third-party middleware linked into main).
#include <nitro.h>

#define DSPROT_BEGIN(marker)          \
    asm {                             \
        stmdb   sp!, {r0};            \
        mov     r0, pc;               \
        add     r0, r0, #0x10;        \
        bl      func_020082dc;        \
        ldmia   sp!, {r0};            \
        b       dsprot_begin;         \
        dcd     marker;               \
    dsprot_begin:                     \
    }

#define DSPROT_END(marker)            \
    asm {                             \
        b       dsprot_end;           \
        dcd     marker;               \
    dsprot_end:                       \
        stmdb   sp!, {r0};            \
        mov     r0, pc;               \
        sub     r0, r0, #0x14;        \
        bl      func_0200834c;        \
        ldmia   sp!, {r0};            \
    }

#define REG_EXMEMCNT   (*(vu16*)0x04000204)
#define REG_CARD_MCNT  (*(vu8*)0x040001A1)
#define REG_CARD_CNT   (*(vu32*)0x040001A4)
#define REG_CARD_CMD   ((vu8*)0x040001A8)
#define REG_CARD_DATA  (*(vu32*)0x04100010)
#define HW_ROM_CTRL    (*(vu32*)0x027FFE60) /* card ROM control word copied from the ROM header */

typedef BOOL (*UnkDSProtCheck)(void);
typedef void (*UnkDSProtCallback)(void);

/* RC4 state */
typedef struct {
    u32 i;
    u32 j;
    u8  s[256];
} UnkDSProtRc4;

/* One RC4 key-schedule step: j += s[i] + key byte, swap s[i] and s[j]. */
static inline u32 ksaStep(UnkDSProtRc4* ctx, u8* p, u32 j, u32 kb) {
    u8 t = *p;
    u8 u;
    j = (t + (j + kb)) & 0xFF;
    u = ctx->s[j];
    ctx->s[j] = t;
    *p = u;
    return j;
}

BOOL func_0200819c(void);
void func_020082dc(u32* region);
void func_0200834c(u32* region);
BOOL func_02008568(const u8* key, const u8* src, u8* dst, u32 size);
BOOL func_020085c0(const u8* key, const u8* src, u8* dst, u32 size);

/* Runs the checks (only func_0200819c); calls the (0x190-xored) callback when one of them failed. */
BOOL func_02007e74(u32 callback) {
    UnkDSProtCheck checks[32];
    int bits;
    int i;
    BOOL result;

    result = FALSE;
    bits = 0;
    checks[0] = (UnkDSProtCheck)((u32)func_0200819c + 0x190);
    checks[1] = NULL;
    for (i = 0; checks[i] != NULL; i++) {
        checks[i] = (UnkDSProtCheck)((u32)checks[i] - 0x190);
        bits = (bits + (checks[i]() ? 1 : 0)) << 1;
    }
    DSPROT_BEGIN(0xEB00002A)
    callback ^= 0x190;
    if ((bits >> 1) != 0) result = TRUE;
    else if ((bits >> 1) == 0) result = FALSE;
    if (callback != 0 && result) ((UnkDSProtCallback)callback)();
    DSPROT_END(0xEB00002A)
    return result;
}

/* Reads ROM data straight through the card registers (0xB7 commands, 0x200-byte pages). */
void func_02007f50(void* buf, u32 offset, u32 size) {
    u16 lockId;
    u8 savedCmd[8];
    volatile u32 romCtrl = HW_ROM_CTRL;
    int i;
    int pos;
    u16 exmemcnt;
    u32 cnt;

    lockId = (u16)OS_GetLockID();
    CARD_LockRom(lockId);
    DSPROT_BEGIN(0xEB004AE2)
    exmemcnt = REG_EXMEMCNT;
    pos = -(offset & 0x1FF);
    REG_EXMEMCNT &= ~0x0800;
    cnt = (romCtrl & ~0x07000000) | 0xA1000000;
    while (REG_CARD_CNT & 0x80000000) {
    }
    REG_CARD_MCNT = 0x80;
    for (i = 0; i < 8; i++) savedCmd[i] = *(vu8*)(0x040001A8 + i);
    offset += pos;
    for (; pos < (int)size; offset += 0x200) {
        REG_CARD_CMD[0] = 0xB7;
        REG_CARD_CMD[1] = offset >> 24;
        REG_CARD_CMD[2] = offset >> 16;
        REG_CARD_CMD[3] = offset >> 8;
        REG_CARD_CMD[4] = offset;
        REG_CARD_CMD[5] = 0;
        REG_CARD_CMD[6] = 0;
        REG_CARD_CMD[7] = 0;
        REG_CARD_CNT = cnt;
        do {
            if (REG_CARD_CNT & 0x00800000) {
                u32 data = REG_CARD_DATA;
                if (pos >= 0 && pos < (int)size) *(u32*)((u8*)buf + pos) = data;
                pos += 4;
            }
        } while (REG_CARD_CNT & 0x80000000);
    }
    for (i = 0; i < 8; i++) *(vu8*)(0x040001A8 + i) = savedCmd[i];
    REG_EXMEMCNT = exmemcnt;
    DSPROT_END(0xEB004AE2)
    CARD_UnlockRom(lockId);
}

/* CRC-32 variant (reflected polynomial 0xEDB88320, xor applied on even bits). */
u32 func_02008100(const u8* data, u32 size) {
    int i;
    u32 crc = 0xFFFFFFFF;
    DSPROT_BEGIN(0xEB003D6D)
    while (size-- != 0) {
        crc ^= *data++;
        for (i = 0; i < 8; i++) {
            if (crc & 1) crc = crc >> 1;
            else crc = (crc >> 1) ^ 0xEDB88320;
        }
    }
    crc = ~crc;
    DSPROT_END(0xEB003D6D)
    return crc;
}

/* Reads six ROM pages and compares their CRCs (mirror detection); TRUE when the ROM looks dumped. */
BOOL func_0200819c(void) {
    u32 crcs[7];
    u8 buf[0x200];
    BOOL result = FALSE;
    int i;

    MI_CpuSet(buf, 0, sizeof(buf));
    for (i = 0; i < 7; i++) {
        if (i > 0) {
            func_02007f50(buf, ((i - 1) / 3) * 0x8000 + ((i - 1) % 3) * 0x200, sizeof(buf));
        }
        crcs[i] = func_02008100(buf, sizeof(buf));
    }
    DSPROT_BEGIN(0xEB002CD7)
    for (i = 1; i < 4; i++) {
        if (crcs[4] != crcs[i]) {
            result = TRUE;
            goto end;
        }
    }
    if (crcs[4] == crcs[5] && crcs[4] == crcs[6]) result = TRUE;
end:
    DSPROT_END(0xEB002CD7)
    return result;
}

/* Cache maintenance around the in-place code patching. */
void func_020082b8(BOOL decrypted) {
    if (decrypted) {
        DC_CleanAll();
        IC_Disable();
    } else {
        IC_Enable();
        DC_CleanAll();
    }
}

/* Decrypts a protected region in place: region[-1] is the marker, the region ends at the next marker. */
void func_020082dc(u32* region) {
    u32 key[4];
    u32 n;
    u32 marker = region[-1];
    n = 0;
    key[0] = marker ^ 0xFF;
    key[1] = marker;
    key[2] = marker;
    key[3] = marker ^ 0xFF000000;
    while (region[n] != marker) n++;
    if (n != 0) func_020085c0((u8*)key, (u8*)region, (u8*)region, n * 4);
    func_020082b8(TRUE);
}

/* Re-encrypts the protected region ending just before region[1] (the closing marker). */
void func_0200834c(u32* region) {
    u32 key[4];
    u32 marker = region[1];
    u32 n;
    key[0] = marker ^ 0xFF;
    key[1] = marker;
    key[2] = marker;
    key[3] = marker ^ 0xFF000000;
    while (*region != marker) region--;
    n = 0;
    while (region[n + 1] != marker) n++;
    if (n != 0) func_02008568((u8*)key, (u8*)(region + 1), (u8*)(region + 1), n * 4);
    func_020082b8(FALSE);
}

/* RC4 key schedule (state permuted from index 255 down). */
void func_020083dc(UnkDSProtRc4* ctx, const u8* key, u32 keySize) {
    u32 k;
    u32 j;
    int i2;
    int i;
    ctx->i = 0;
    ctx->j = 0;
    k = 0;
    j = 0;
    for (i = 0; i < 256; i++) ctx->s[i] = i;
    for (i2 = 255; i2 >= 0; i2--) {
        j = ksaStep(ctx, &ctx->s[i2], j, key[k]);
        k++;
        if (k >= keySize) k = 0;
    }
}

/* RC4 keystream byte. */
u8 func_02008450(UnkDSProtRc4* ctx) {
    u32 i = (ctx->i + 1) & 0xFF;
    u8 a = ctx->s[i];
    u32 j = (a + ctx->j) & 0xFF;
    u8 b = ctx->s[j];
    ctx->i = i;
    ctx->j = j;
    ctx->s[j] = a;
    ctx->s[i] = b;
    return ctx->s[(a + b) & 0xFF];
}

/* Substitution table for the third byte of each word (x ^ 1). */
int func_0200849c(u8* table) {
    int i;
    for (i = 0; i < 256; i++) table[i] = (u8)i ^ 1;
    return 0;
}

/* Word-wise crypt: bytes 0-1 xored with the keystream, byte 2 through the table, byte 3 (the ARM condition and
   opcode bits) kept. */
int func_020084c0(UnkDSProtRc4* ctx, const u8* src, u8* dst, u32 size) {
    u8 table[256];
    u32 i;
    if (size & 3) return -1;
    func_0200849c(table);
    for (i = 0; i < size; i += 4) {
        const u8* s = src + i;
        u8* d = dst + i;
        dst[i] = src[i] ^ func_02008450(ctx);
        d[1] = s[1] ^ func_02008450(ctx);
        d[2] = table[s[2]];
        d[3] = s[3];
    }
    return 0;
}

int func_0200855c(UnkDSProtRc4* ctx, const u8* src, u8* dst, u32 size) {
    return func_020084c0(ctx, src, dst, size);
}

BOOL func_02008568(const u8* key, const u8* src, u8* dst, u32 size) {
    UnkDSProtRc4 ctx;
    func_020083dc(&ctx, key, 16);
    return -(func_020084c0(&ctx, src, dst, size) == -1);
}

BOOL func_020085c0(const u8* key, const u8* src, u8* dst, u32 size) {
    UnkDSProtRc4 ctx;
    func_020083dc(&ctx, key, 16);
    return -(func_0200855c(&ctx, src, dst, size) == -1);
}
