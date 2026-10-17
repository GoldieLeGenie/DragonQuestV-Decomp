#include "main/dss/UnkModelMember.hpp"
#include "main/dss/UnkVramTransfer.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "nitro/os.hpp"

NNSG3dResTex* data_020f3e84;
int data_020f3e88;

ARM UnkModelMember::UnkModelMember()
{
    unk_00 = NULL;
    unk_04 = NULL;
}

ARM void UnkModelMember::unkfunc_02046c3c(void* data)
{
    unkfunc_02046c6c(data);
}

ARM void UnkModelMember::unkfunc_02046c48()
{
    unkfunc_02046dbc();
}

ARM void UnkModelMember::unkfunc_02046c54()
{
    unkfunc_02046e98();
    unkfunc_02046dc8();
}

ARM void UnkModelMember::unkfunc_02046c6c(void* data)
{
    unk_00 = data;
    if (data_020f3e88 != 0) {
        data_020f3e88 = 0;
    } else {
        unkfunc_02046dc8();
    }
    unk_04 = NNS_G3dGetMdlByIdx(func_02083268(unk_00), 0);
    NNSG3dResMdlSet* mdlSet = func_02083268(unk_00);
    for (int i = 0; i < mdlSet->dict.numEntry; i++) {
        unk_04 = NNS_G3dGetMdlByIdx(func_02083268(unk_00), i);
        func_020803d0(0, 0, 2, 0, 0x1f, 0x8000);
        func_02082e1c(unk_04, 0, 0x8000);
    }
}

ARM void UnkModelMember::unkfunc_02046dbc()
{
    unkfunc_02046e98();
}

ARM void UnkModelMember::unkfunc_02046dc8()
{
    NNSG3dResMdlSet* mdlSet = func_02083268(unk_00);
    NNSG3dResTex* tex = func_02083270(unk_00);
    if (tex == NULL) {
        return;
    }
    data_020f3e84 = tex;
    unk_08 = tex;
    int texSize = func_0207fc2c(tex);
    func_0207fc3c(tex);
    int plttSize = func_0207fd08(tex);
    int texKey = data_020f4f74.unkfunc_0204a5f4(texSize);
    int plttKey = data_020f4f74.unkfunc_0204a658(plttSize);
    unkfunc_020491f8(tex);
    if (!(tex->texInfo.flag & 1)) {
        func_0207fc4c(tex, texKey, 0);
        func_0207fd18(tex, plttKey);
        OS_Wait();
        func_0207fc5c(tex, 1);
        func_0207fd1c(tex, 1);
    }
    func_0208012c(mdlSet, tex);
}

ARM void UnkModelMember::unkfunc_02046e98()
{
    NNSG3dResMdlSet* mdlSet = func_02083268(unk_00);
    NNSG3dResTex* tex = func_02083270(unk_00);
    if (tex == NULL) {
        return;
    }
    func_02080194(mdlSet);
    int plttKey = func_0207fd4c(tex);
    int texKey;
    int tex4x4Key;
    func_0207fcd8(tex, &texKey, &tex4x4Key);
    if (plttKey != 0) {
        data_020f4f74.unkfunc_0204a690(plttKey);
    }
    if (texKey != 0) {
        data_020f4f74.unkfunc_0204a618(texKey);
    }
    data_020f3e84 = NULL;
    unk_08 = NULL;
}

ARM void* UnkModelMember::unkfunc_02046f30()
{
    return unk_00;
}

ARM NNSG3dResMdl* UnkModelMember::unkfunc_02046f38()
{
    return unk_04;
}

ARM NNSG3dResTex* unkfunc_02046f40()
{
    return data_020f3e84;
}
