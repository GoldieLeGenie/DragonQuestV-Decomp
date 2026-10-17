#include "g3d_internal.h"

#pragma thumb on

typedef struct UnkResAnmSet {
    u32 kind;           // 0x00
    u32 size;           // 0x04
    NNSG3dResDict dict; // 0x08
} UnkResAnmSet;

typedef struct UnkResNameTable {
    u8 unk_00[6];
    u8 numTex;       // 0x06
    u8 numPltt;      // 0x07
    u16 ofsTexName;  // 0x08
    u16 ofsPlttName; // 0x0A
} UnkResNameTable;

typedef struct UnkTexPatFV {
    u16 idxFrame; // 0x00
    u8 idxTex;    // 0x02
    u8 idxPltt;   // 0x03
} UnkTexPatFV;

typedef struct UnkTexPatDictData {
    u16 numFV;          // 0x00
    u16 flag;           // 0x02
    fx16 ratioDataFrame; // 0x04
    u16 offset;         // 0x06
} UnkTexPatDictData;

typedef struct UnkTexPatAnm {
    u8 unk_00[0xc];
    NNSG3dResDict dict; // 0x0C
} UnkTexPatAnm;

static inline const NNSG3dResName* GetResNameByIdx(const NNSG3dResDict* dict, u32 idx) {
    if (dict != NULL && idx < dict->numEntry) {
        UnkResDictEntryHeader* p = (UnkResDictEntryHeader*)((u8*)dict + dict->ofsEntry);
        return (const NNSG3dResName*)((u8*)p + p->ofsName) + idx;
    }
    return NULL;
}

// Looks a resource up by name, returns its dictionary data
void* func_02083064(const NNSG3dResDict* dict, const NNSG3dResName* name) {
    if (name == NULL) {
        return NULL;
    }
    if (dict->numEntry < 16) {
        u32 i;
        u32 n0 = name->val[0];
        u32 n1 = name->val[1];
        u32 n2 = name->val[2];
        u32 n3 = name->val[3];
        for (i = 0; i < dict->numEntry; i++) {
            const NNSG3dResName* n = GetResNameByIdx(dict, i);
            if (n->val[0] == n0 && n->val[1] == n1 && n->val[2] == n2 && n->val[3] == n3) {
                return GetResDataByIdx(dict, i);
            }
        }
    } else {
        const UnkResDictTreeNode* tree = (const UnkResDictTreeNode*)((u8*)dict + 8);
        u32 idx = tree[0].idx[0];
        if (idx) {
            const UnkResDictTreeNode* prev = &tree[0];
            const UnkResDictTreeNode* p = &tree[idx];
            while (prev->refBit > p->refBit) {
                prev = p;
                p = &tree[p->idx[(name->val[p->refBit >> 5] >> (p->refBit & 0x1f)) & 1]];
            }
            {
                const NNSG3dResName* n = GetResNameByIdx(dict, p->idxEntry);
                if (n->val[0] == name->val[0] && n->val[1] == name->val[1] && n->val[2] == name->val[2] &&
                    n->val[3] == name->val[3]) {
                    return GetResDataByIdx(dict, p->idxEntry);
                }
            }
        }
    }
    return NULL;
}

// Looks a resource up by name, returns its index or -1
int func_02083180(const NNSG3dResDict* dict, const NNSG3dResName* name) {
    if (name == NULL) {
        return -1;
    }
    if (dict->numEntry < 16) {
        u32 i;
        u32 n0 = name->val[0];
        u32 n1 = name->val[1];
        u32 n2 = name->val[2];
        u32 n3 = name->val[3];
        for (i = 0; i < dict->numEntry; i++) {
            const NNSG3dResName* n = GetResNameByIdx(dict, i);
            if (n->val[0] == n0 && n->val[1] == n1 && n->val[2] == n2 && n->val[3] == n3) {
                return i;
            }
        }
    } else {
        const UnkResDictTreeNode* tree = (const UnkResDictTreeNode*)((u8*)dict + 8);
        u32 idx = tree[0].idx[0];
        if (idx) {
            const UnkResDictTreeNode* prev = &tree[0];
            const UnkResDictTreeNode* p = &tree[idx];
            while (prev->refBit > p->refBit) {
                prev = p;
                p = &tree[p->idx[(name->val[p->refBit >> 5] >> (p->refBit & 0x1f)) & 1]];
            }
            {
                const NNSG3dResName* n = GetResNameByIdx(dict, p->idxEntry);
                if (n->val[0] == name->val[0] && n->val[1] == name->val[1] && n->val[2] == name->val[2] &&
                    n->val[3] == name->val[3]) {
                    return p->idxEntry;
                }
            }
        }
    }
    return -1;
}

// Returns the model set block of a model file
void* func_02083268(const UnkBinFileHeader* file) {
    return (u8*)file + *(const u32*)((u8*)file + file->headerSize);
}

// Returns the texture block of a model/texture file
NNSG3dResTex* func_02083270(const UnkBinFileHeader* file) {
    const u32* blocks = (const u32*)((u8*)file + file->headerSize);
    if (file->dataBlocks == 1) {
        if (file->signature == 0x30585442) {
            return (NNSG3dResTex*)((u8*)file + blocks[0]);
        }
        return NULL;
    }
    return (NNSG3dResTex*)((u8*)file + blocks[1]);
}

// Returns an animation of an animation file
void* func_02083298(const UnkBinFileHeader* file, u32 idx) {
    if (file != NULL) {
        UnkResAnmSet* set = (UnkResAnmSet*)((u8*)file + *(const u32*)((u8*)file + file->headerSize));
        const u32* data = (const u32*)GetResDataByIdx(&set->dict, idx);
        if (data) {
            return (u8*)set + *data;
        }
    }
    return NULL;
}

const NNSG3dResName* func_020832d4(const UnkResNameTable* res, u32 idx) {
    if (res != NULL && idx < res->numTex) {
        return (const NNSG3dResName*)((u8*)res + res->ofsTexName) + idx;
    }
    return NULL;
}

const NNSG3dResName* func_020832ec(const UnkResNameTable* res, u32 idx) {
    if (res != NULL && idx < res->numPltt) {
        return (const NNSG3dResName*)((u8*)res + res->ofsPlttName) + idx;
    }
    return NULL;
}

const UnkTexPatDictData* func_02083350(const UnkTexPatAnm* pat, u32 idx);

// Finds the pattern entry of a frame
const UnkTexPatFV* func_02083304(const UnkTexPatAnm* pat, u32 idx, u32 frame) {
    const UnkTexPatDictData* d = func_02083350(pat, idx);
    const UnkTexPatFV* fv = (const UnkTexPatFV*)((u8*)pat + d->offset);
    u32 i = (u32)(d->ratioDataFrame * frame) >> 12;

    while (i > 0 && fv[i].idxFrame >= frame) {
        i--;
    }
    while (i + 1 < d->numFV && fv[i + 1].idxFrame <= frame) {
        i++;
    }
    return &fv[i];
}

const UnkTexPatDictData* func_02083350(const UnkTexPatAnm* pat, u32 idx) {
    return (const UnkTexPatDictData*)GetResDataByIdx(&pat->dict, idx);
}
