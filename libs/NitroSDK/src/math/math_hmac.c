#include "math_internal.h"

#pragma thumb on

/* Not linked in the ROM (no caller); its parameter template stays in this unit's .rodata (0x0208de94). */
void unkfunc_unused_15(u8* digest, const void* data, u32 dataLen, const void* key, u32 keyLen) {
    UnkSha1Context context;
    u8             hash[20];
    UnkHmacParam   param = {20, 64};

    param.unk_08 = &context;
    param.unk_0c = hash;
    param.unk_10 = (void (*)(void*))func_0207251c;
    param.unk_14 = (void (*)(void*, const void*, u32))func_02072550;
    param.unk_18 = (void (*)(void*, void*))func_02072624;
    func_020727b0(digest, data, dataLen, key, keyLen, &param);
}

/* HMAC-SHA1. The parameter block is initialized from a constant template (the ROM copy is data_0208de78). */
void func_0207275c(u8* digest, const void* data, u32 dataLen, const void* key, u32 keyLen) {
    UnkSha1Context context;
    u8             hash[20];
    UnkHmacParam   param = {20, 64};

    param.unk_08 = &context;
    param.unk_0c = hash;
    param.unk_10 = (void (*)(void*))func_0207251c;
    param.unk_14 = (void (*)(void*, const void*, u32))func_02072550;
    param.unk_18 = (void (*)(void*, void*))func_02072624;
    func_020727b0(digest, data, dataLen, key, keyLen, &param);
}

/* Not linked in the ROM (no caller); its parameter template stays in this unit's .rodata (0x0208deb0). */
void unkfunc_unused_16(u8* digest, const void* data, u32 dataLen, const void* key, u32 keyLen) {
    UnkSha1Context context;
    u8             hash[20];
    UnkHmacParam   param = {20, 64};

    param.unk_08 = &context;
    param.unk_0c = hash;
    param.unk_10 = (void (*)(void*))func_0207251c;
    param.unk_14 = (void (*)(void*, const void*, u32))func_02072550;
    param.unk_18 = (void (*)(void*, void*))func_02072624;
    func_020727b0(digest, data, dataLen, key, keyLen, &param);
}

void func_020727b0(u8* digest, const void* data, u32 dataLen, const u8* key, s32 keyLen, UnkHmacParam* param) {
    u8  keyHash[64];
    u8  ipad[64];
    u8  opad[64];
    s32 i;

    if (digest == NULL || data == NULL || dataLen == 0 || key == NULL || keyLen == 0 || param == NULL) {
        return;
    }

    if (keyLen > param->unk_04) {
        param->unk_10(param->unk_08);
        param->unk_14(param->unk_08, key, keyLen);
        param->unk_18(param->unk_08, keyHash);
        keyLen = param->unk_00;
        key    = keyHash;
    }

    for (i = 0; i < keyLen; i++) {
        ipad[i] = key[i] ^ 0x36;
    }
    for (; i < param->unk_04; i++) {
        ipad[i] = 0x36;
    }
    param->unk_10(param->unk_08);
    param->unk_14(param->unk_08, ipad, param->unk_04);
    param->unk_14(param->unk_08, data, dataLen);
    param->unk_18(param->unk_08, param->unk_0c);

    for (i = 0; i < keyLen; i++) {
        opad[i] = key[i] ^ 0x5C;
    }
    for (; i < param->unk_04; i++) {
        opad[i] = 0x5C;
    }
    param->unk_10(param->unk_08);
    param->unk_14(param->unk_08, opad, param->unk_04);
    param->unk_14(param->unk_08, param->unk_0c, param->unk_00);
    param->unk_18(param->unk_08, digest);
}
