#include "math_internal.h"

#pragma thumb on

static void func_020721e4(UnkMD5Context* context);

static u8 data_0209c210[4] = {0x80};

static u32 data_0209c214[48] = {
    1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
    5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
    0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9,
};

static u32 data_0209c2d4[64] = {
    0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501,
    0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE, 0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821,
    0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA, 0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8,
    0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED, 0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A,
    0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C, 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70,
    0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05, 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665,
    0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1,
    0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1, 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391,
};

void func_020720b0(UnkMD5Context* context) {
    context->unk_00[0] = 0x67452301;
    context->unk_00[1] = 0xEFCDAB89;
    context->unk_00[2] = 0x98BADCFE;
    context->unk_00[3] = 0x10325476;
    context->unk_10    = 0;
}

void func_020720d8(UnkMD5Context* context, const void* data, u32 len) {
    u32 used = (u32)context->unk_10 & 63;
    u32 rest;
    const u8* src;
    s32 blocks;

    context->unk_10 += len;
    rest = 64 - used;
    if (rest > len) {
        if (len != 0) {
            MI_CpuCopyU8(data, context->unk_18 + used, len);
        }
        return;
    }
    MI_CpuCopyU8(data, context->unk_18 + used, rest);
    func_020721e4(context);
    src = (const u8*)data + rest;
    len -= rest;
    for (blocks = (s32)(len >> 6); blocks > 0; blocks--) {
        MI_CpuCopyU8(src, context->unk_18, 64);
        src += 64;
        func_020721e4(context);
    }
    if (len & 63) {
        MI_CpuCopyU8(src, context->unk_18, len & 63);
    }
}

void func_0207216c(void* digest, UnkMD5Context* context) {
    u64 bits = context->unk_10 << 3;
    u32 used;
    u32 rest;

    func_020720d8(context, data_0209c210, 1);
    used = (u32)(context->unk_10 & 63);
    rest = 64 - used;
    if (rest < 8) {
        MI_CpuSet(context->unk_18 + used, 0, rest);
        func_020721e4(context);
        used = 0;
        rest = 64;
    }
    if (rest > 8) {
        MI_CpuSet(context->unk_18 + used, 0, rest - 8);
    }
    *(u64*)(context->unk_18 + 56) = bits;
    func_020721e4(context);
    MI_CpuCopyU8(context, digest, 16);
    MI_CpuSet(context, 0, sizeof(UnkMD5Context));
}

#define ROTL(x, s) (((x) << (s)) | ((x) >> (32 - (s))))

#define STEP(f, a, b, c, d, x, s, t)            \
    {                                           \
        u32 tt = (t);                           \
        u32 xx = (x);                           \
        a = b + ROTL(a + f(b, c, d) + xx + tt, s); \
    }

#define F(b, c, d) (((b) & (c)) | (~(b) & (d)))
#define G(b, c, d) (((b) & (d)) | ((c) & ~(d)))
#define H(b, c, d) ((b) ^ (c) ^ (d))
#define I(b, c, d) ((c) ^ ((b) | ~(d)))

static void func_020721e4(UnkMD5Context* context) {
    u32 a = context->unk_00[0];
    u32 b = context->unk_00[1];
    u32 c = context->unk_00[2];
    u32 d = context->unk_00[3];
    const u32* t = data_0209c2d4;
    const u32* idx;
    const u32* block = (const u32*)context->unk_18;
    const u32* x = block;
    s32 i;

    for (i = 0; i < 4; i++) {
        STEP(F, a, b, c, d, *x++, 7, *t++);
        STEP(F, d, a, b, c, *x++, 12, *t++);
        STEP(F, c, d, a, b, *x++, 17, *t++);
        STEP(F, b, c, d, a, *x++, 22, *t++);
    }
    idx = data_0209c214;
    for (i = 0; i < 4; i++) {
        STEP(G, a, b, c, d, block[*idx++], 5, *t++);
        STEP(G, d, a, b, c, block[*idx++], 9, *t++);
        STEP(G, c, d, a, b, block[*idx++], 14, *t++);
        STEP(G, b, c, d, a, block[*idx++], 20, *t++);
    }
    for (i = 0; i < 4; i++) {
        STEP(H, a, b, c, d, block[*idx++], 4, *t++);
        STEP(H, d, a, b, c, block[*idx++], 11, *t++);
        STEP(H, c, d, a, b, block[*idx++], 16, *t++);
        STEP(H, b, c, d, a, block[*idx++], 23, *t++);
    }
    for (i = 0; i < 4; i++) {
        STEP(I, a, b, c, d, block[*idx++], 6, *t++);
        STEP(I, d, a, b, c, block[*idx++], 10, *t++);
        STEP(I, c, d, a, b, block[*idx++], 15, *t++);
        STEP(I, b, c, d, a, block[*idx++], 21, *t++);
    }
    context->unk_00[0] += a;
    context->unk_00[1] += b;
    context->unk_00[2] += c;
    context->unk_00[3] += d;
}
