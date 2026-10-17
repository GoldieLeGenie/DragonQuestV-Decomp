#include "g3d_types.h"

#pragma thumb on

/* Texture / palette resources: VRAM loading and binding to model materials. */

typedef struct UnkResDict {
    u8 unk_00;                  // 0x00 revision
    u8 unk_01;                  // 0x01 number of entries
    u16 unk_02;                 // 0x02 dictionary size
    u16 unk_04;                 // 0x04
    u16 unk_06;                 // 0x06 offset of the entry table
} UnkResDict;

typedef struct UnkResDictEntryHeader {
    u16 unk_00;                 // 0x00 size of one data unit
    u16 unk_02;                 // 0x02 offset of the name table
    u8 unk_04[1];               // 0x04 data units
} UnkResDictEntryHeader;

typedef struct UnkResTexInfo {
    u32 unk_00;                 // 0x00 VRAM key
    u16 unk_04;                 // 0x04 data size / 8
    u16 unk_06;                 // 0x06 dictionary offset
    u16 unk_08;                 // 0x08 flags (bit 0: loaded)
    u16 unk_0a;                 // 0x0A
    u32 unk_0c;                 // 0x0C data offset
} UnkResTexInfo;

typedef struct UnkResTex4x4Info {
    u32 unk_00;                 // 0x00 VRAM key
    u16 unk_04;                 // 0x04 data size / 8
    u16 unk_06;                 // 0x06 dictionary offset
    u16 unk_08;                 // 0x08 flags (bit 0: loaded)
    u16 unk_0a;                 // 0x0A
    u32 unk_0c;                 // 0x0C data offset
    u32 unk_10;                 // 0x10 palette index data offset
} UnkResTex4x4Info;

typedef struct UnkResPlttInfo {
    u32 unk_00;                 // 0x00 VRAM key
    u16 unk_04;                 // 0x04 data size / 8
    u16 unk_06;                 // 0x06 flags (bit 0: loaded)
    u16 unk_08;                 // 0x08 dictionary offset
    u16 unk_0a;                 // 0x0A
    u32 unk_0c;                 // 0x0C data offset
} UnkResPlttInfo;

typedef struct UnkResTex {
    u32 unk_00;                 // 0x00 block kind
    u32 unk_04;                 // 0x04 block size
    UnkResTexInfo unk_08;       // 0x08 textures
    UnkResTex4x4Info unk_18;    // 0x18 4x4 compressed textures
    UnkResPlttInfo unk_2c;      // 0x2C palettes
    UnkResDict unk_3c;          // 0x3C texture dictionary
} UnkResTex;

typedef struct UnkResDictTexData {
    u32 unk_00;                 // 0x00 TEXIMAGE_PARAM value
    u32 unk_04;                 // 0x04 width (bits 0-10) / height (bits 11-21)
} UnkResDictTexData;

typedef struct UnkResDictPlttData {
    u16 unk_00;                 // 0x00 offset / 8
    u16 unk_02;                 // 0x02 flags (bit 0: 4-color palette)
} UnkResDictPlttData;

typedef struct UnkResDictToMatIdxData {
    u16 unk_00;                 // 0x00 offset of the material index list
    u8 unk_02;                  // 0x02 number of materials
    u8 unk_03;                  // 0x03 flags (bit 0: bound)
} UnkResDictToMatIdxData;

typedef struct UnkResMat {
    u16 unk_00;                 // 0x00 texture -> material dictionary offset
    u16 unk_02;                 // 0x02 palette -> material dictionary offset
    UnkResDict unk_04;          // 0x04 material dictionary
} UnkResMat;

typedef struct UnkResMatData {
    u8 unk_00[0x14];            // 0x00
    u32 unk_14;                 // 0x14 TEXIMAGE_PARAM
    u8 unk_18[4];               // 0x18
    u16 unk_1c;                 // 0x1C palette base
    u16 unk_1e;                 // 0x1E
    u16 unk_20;                 // 0x20 original width
    u16 unk_22;                 // 0x22 original height
    s32 unk_24;                 // 0x24 width scale
    s32 unk_28;                 // 0x28 height scale
} UnkResMatData;

typedef struct UnkResMdl {
    u32 unk_00;                 // 0x00
    u32 unk_04;                 // 0x04
    u32 unk_08;                 // 0x08 material block offset
} UnkResMdl;

typedef struct UnkResMdlSet {
    u32 unk_00;                 // 0x00 block kind
    u32 unk_04;                 // 0x04 block size
    UnkResDict unk_08;          // 0x08 model dictionary
} UnkResMdlSet;

typedef struct UnkResDictMdlSetData {
    u32 unk_00;                 // 0x00 model offset
} UnkResDictMdlSetData;

extern void func_02076e98(void);
extern void func_02076ef4(const void* src, u32 dest, u32 size);
extern void func_02077034(void);
extern void func_02077080(void);
extern void func_020770b4(const void* src, u32 dest, u32 size);
extern void func_02077120(void);
extern s32 FX_Divide(s32 numer, s32 denom);
extern void* func_02083064(const UnkResDict* dict, const void* name);

#define VRAM_KEY_ADDR(key) (((key) & 0xffff) << 3)

static inline u32 GetTexKeyAddr(u32 key) {
    return (u32)((key & 0xffff) << 3);
}

static inline void* GetResDataByIdx(const UnkResDict* dict, u32 idx) {
    if (dict != NULL && idx < dict->unk_01) {
        UnkResDictEntryHeader* hdr = (UnkResDictEntryHeader*)((u8*)dict + dict->unk_06);
        return (u8*)hdr->unk_04 + hdr->unk_00 * idx;
    }
    return NULL;
}

typedef struct UnkResName {
    char unk_00[16];            // 0x00
} UnkResName;

static inline UnkResName* GetResNameByIdx(const UnkResDict* dict, u32 idx) {
    if (dict != NULL && idx < dict->unk_01) {
        UnkResDictEntryHeader* hdr = (UnkResDictEntryHeader*)((u8*)dict + dict->unk_06);
        return &((UnkResName*)((u8*)hdr + hdr->unk_02))[idx];
    }
    return NULL;
}

static inline UnkResMatData* GetMatDataByIdx(UnkResMat* mat, u32 idx) {
    if (mat != NULL) {
        u32* data = (u32*)GetResDataByIdx(&mat->unk_04, idx);
        if (data != NULL) {
            return (UnkResMatData*)((u8*)mat + *data);
        }
    }
    return NULL;
}

static inline UnkResMat* GetMat(UnkResMdl* mdl) {
    if (mdl != NULL && mdl->unk_08 != 0) {
        return (UnkResMat*)((u8*)mdl + mdl->unk_08);
    }
    return NULL;
}

static inline UnkResDictTexData* GetTexDataByName(UnkResTex* tex, const UnkResName* name) {
    if (tex != NULL) {
        return func_02083064(&tex->unk_3c, name);
    }
    return NULL;
}

static inline UnkResDictPlttData* GetPlttDataByName(UnkResTex* tex, const UnkResName* name) {
    if (tex != NULL && tex->unk_2c.unk_08 != 0) {
        return func_02083064((UnkResDict*)((u8*)tex + tex->unk_2c.unk_08), name);
    }
    return NULL;
}

static inline UnkResMdl* GetMdlByIdx(UnkResMdlSet* mdlSet, u32 idx) {
    if (mdlSet != NULL) {
        UnkResDictMdlSetData* data = (UnkResDictMdlSetData*)GetResDataByIdx(&mdlSet->unk_08, idx);
        if (data != NULL) {
            return (UnkResMdl*)((u8*)mdlSet + data->unk_00);
        }
    }
    return NULL;
}

u32 func_0207fc2c(UnkResTex* tex) {
    if (tex != NULL) {
        return tex->unk_08.unk_04 << 3;
    }
    return 0;
}

u32 func_0207fc3c(UnkResTex* tex) {
    if (tex != NULL) {
        return tex->unk_18.unk_04 << 3;
    }
    return 0;
}

void func_0207fc4c(UnkResTex* tex, u32 texKey, u32 tex4x4Key) {
    if (texKey != 0) {
        tex->unk_08.unk_00 = texKey;
    }
    if (tex4x4Key != 0) {
        tex->unk_18.unk_00 = tex4x4Key;
    }
}

void func_0207fc5c(UnkResTex* tex, BOOL execBeginEnd) {
    u32 size;
    u32 size4;

    if (execBeginEnd) {
        func_02076e98();
    }

    size = tex->unk_08.unk_04 << 3;
    if (size != 0) {
        func_02076ef4((u8*)tex + tex->unk_08.unk_0c, VRAM_KEY_ADDR(tex->unk_08.unk_00), size);
        tex->unk_08.unk_08 |= 1;
    }

    size4 = tex->unk_18.unk_04 << 3;
    if (size4 != 0) {
        u8* data = (u8*)tex + tex->unk_18.unk_0c;
        u8* idx = (u8*)tex + tex->unk_18.unk_10;
        u32 addr = VRAM_KEY_ADDR(tex->unk_18.unk_00);

        func_02076ef4(data, addr, size4);
        func_02076ef4(idx, 0x20000 + ((addr & 0x1ffff) >> 1) + ((addr & 0x40000) >> 2), size4 >> 1);
        tex->unk_18.unk_08 |= 1;
    }

    if (execBeginEnd) {
        func_02077034();
    }
}

void func_0207fcd8(UnkResTex* tex, u32* texKey, u32* tex4x4Key) {
    if (texKey != NULL) {
        tex->unk_08.unk_08 &= ~1;
        *texKey = tex->unk_08.unk_00;
        tex->unk_08.unk_00 = 0;
    }
    if (tex4x4Key != NULL) {
        tex->unk_18.unk_08 &= ~1;
        *tex4x4Key = tex->unk_18.unk_00;
        tex->unk_18.unk_00 = 0;
    }
}

u32 func_0207fd08(UnkResTex* tex) {
    if (tex != NULL) {
        return tex->unk_2c.unk_04 << 3;
    }
    return 0;
}

void func_0207fd18(UnkResTex* tex, u32 plttKey) {
    tex->unk_2c.unk_00 = plttKey;
}

void func_0207fd1c(UnkResTex* tex, BOOL execBeginEnd) {
    if (execBeginEnd) {
        func_02077080();
    }
    func_020770b4((u8*)tex + tex->unk_2c.unk_0c, VRAM_KEY_ADDR(tex->unk_2c.unk_00), tex->unk_2c.unk_04 << 3);
    tex->unk_2c.unk_06 |= 1;
    if (execBeginEnd) {
        func_02077120();
    }
}

u32 func_0207fd4c(UnkResTex* tex) {
    u32 key;

    tex->unk_2c.unk_06 &= ~1;
    key = tex->unk_2c.unk_00;
    tex->unk_2c.unk_00 = 0;
    return key;
}

/* Binds one texture to every material that uses it. */
void func_0207fd60(UnkResMat* mat, UnkResDictToMatIdxData* data, UnkResTex* tex, UnkResDictTexData* texData) {
    u8* idx = (u8*)mat + data->unk_00;
    u32 offset;
    u32 i;

    if ((texData->unk_00 & 0x1c000000) != 0x14000000) {
        offset = GetTexKeyAddr(tex->unk_08.unk_00) >> 3;
    } else {
        offset = GetTexKeyAddr(tex->unk_18.unk_00) >> 3;
    }
    for (i = 0; i < data->unk_02; i++) {
        UnkResMatData* matData = GetMatDataByIdx(mat, idx[i]);
        u32 w;
        u32 h;

        matData->unk_14 |= texData->unk_00 + offset;
        w = texData->unk_04 & 0x7ff;
        h = (texData->unk_04 & 0x3ff800) >> 11;
        if (w != matData->unk_20) {
            matData->unk_24 = FX_Divide(w << 12, matData->unk_20 << 12);
        } else {
            matData->unk_24 = 0x1000;
        }
        if (h != matData->unk_22) {
            matData->unk_28 = FX_Divide(h << 12, matData->unk_22 << 12);
        } else {
            matData->unk_28 = 0x1000;
        }
    }
    data->unk_03 |= 1;
}

/* Unbinds one texture from its materials. */
void func_0207fe4c(UnkResMat* mat, UnkResDictToMatIdxData* data) {
    u8* idx = (u8*)mat + data->unk_00;
    u32 i;

    for (i = 0; i < data->unk_02; i++) {
        UnkResMatData* matData = GetMatDataByIdx(mat, idx[i]);

        matData->unk_14 &= 0xc00f0000;
        matData->unk_24 = 0x1000;
        matData->unk_28 = 0x1000;
    }
    data->unk_03 &= ~1;
}

BOOL func_0207feb4(UnkResMdl* mdl, UnkResTex* tex) {
    BOOL result = TRUE;
    UnkResMat* mat = GetMat(mdl);
    UnkResDict* dict = (UnkResDict*)((u8*)mat + mat->unk_00);
    u32 i;

    for (i = 0; i < dict->unk_01; i++) {
        UnkResDictTexData* texData = GetTexDataByName(tex, GetResNameByIdx(dict, i));

        if (texData != NULL) {
            UnkResDictToMatIdxData* data = GetResDataByIdx(dict, i);

            if (!(data->unk_03 & 1)) {
                func_0207fd60(mat, data, tex, texData);
            }
        } else {
            result = FALSE;
        }
    }
    return result;
}

void func_0207ff58(UnkResMdl* mdl) {
    UnkResMat* mat = GetMat(mdl);
    UnkResDict* dict = (UnkResDict*)((u8*)mat + mat->unk_00);
    u32 i;

    for (i = 0; i < dict->unk_01; i++) {
        UnkResDictToMatIdxData* data = GetResDataByIdx(dict, i);

        if (data->unk_03 & 1) {
            func_0207fe4c(mat, data);
        }
    }
}

/* Binds one palette to every material that uses it. */
void func_0207ffac(UnkResMat* mat, UnkResDictToMatIdxData* data, UnkResTex* tex, UnkResDictPlttData* plttData) {
    u8* idx = (u8*)mat + data->unk_00;
    u16 plttBase = plttData->unk_00;
    u16 vramOffset = GetTexKeyAddr(tex->unk_2c.unk_00) >> 3;
    u32 i;

    if (!(plttData->unk_02 & 1)) {
        plttBase >>= 1;
        vramOffset >>= 1;
    }
    for (i = 0; i < data->unk_02; i++) {
        UnkResMatData* matData = GetMatDataByIdx(mat, idx[i]);

        matData->unk_1c = (u16)(plttBase + vramOffset);
    }
    data->unk_03 |= 1;
}

BOOL func_02080030(UnkResMdl* mdl, UnkResTex* tex) {
    BOOL result = TRUE;
    UnkResMat* mat = GetMat(mdl);
    UnkResDict* dict = (UnkResDict*)((u8*)mat + mat->unk_02);
    u32 i;

    for (i = 0; i < dict->unk_01; i++) {
        UnkResDictPlttData* plttData = GetPlttDataByName(tex, GetResNameByIdx(dict, i));

        if (plttData != NULL) {
            UnkResDictToMatIdxData* data = GetResDataByIdx(dict, i);

            if (!(data->unk_03 & 1)) {
                func_0207ffac(mat, data, tex, plttData);
            }
        } else {
            result = FALSE;
        }
    }
    return result;
}

void func_020800d4(UnkResMdl* mdl) {
    UnkResMat* mat = GetMat(mdl);
    UnkResDict* dict = (UnkResDict*)((u8*)mat + mat->unk_02);
    u32 i;

    for (i = 0; i < dict->unk_01; i++) {
        UnkResDictToMatIdxData* data = GetResDataByIdx(dict, i);

        if (data->unk_03 & 1) {
            data->unk_03 &= ~1;
        }
    }
}

BOOL func_0208012c(UnkResMdlSet* mdlSet, UnkResTex* tex) {
    u32 i;
    BOOL result = TRUE;

    for (i = 0; i < mdlSet->unk_08.unk_01; i++) {
        UnkResMdl* mdl = GetMdlByIdx(mdlSet, i);

        result &= func_0207feb4(mdl, tex);
        result &= func_02080030(mdl, tex);
    }
    return result;
}

void func_02080194(UnkResMdlSet* mdlSet) {
    u32 i;

    for (i = 0; i < mdlSet->unk_08.unk_01; i++) {
        UnkResMdl* mdl = GetMdlByIdx(mdlSet, i);

        func_0207ff58(mdl);
        func_020800d4(mdl);
    }
}
