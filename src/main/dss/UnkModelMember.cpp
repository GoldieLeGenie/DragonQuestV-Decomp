#include "main/dss/UnkModelMember.hpp"
#include "main/dss/VramTransferManager.hpp"
#include "main/dss/UnkPaletteEffect.hpp"
#include "nitro/os.hpp"

NNSG3dResTex* data_020f3e84;
int data_020f3e88;

ARM UnkModelMember::UnkModelMember()
{
    modelFile_ = NULL;
    model_ = NULL;
}

ARM void UnkModelMember::setModelFile(void* data)
{
    bindModelFile(data);
}

ARM void UnkModelMember::release()
{
    releaseModelFile();
}

ARM void UnkModelMember::reloadTextures()
{
    releaseTextures();
    loadTextures();
}

ARM void UnkModelMember::bindModelFile(void* data)
{
    modelFile_ = data;
    if (data_020f3e88 != 0) {
        data_020f3e88 = 0;
    } else {
        loadTextures();
    }
    model_ = NNS_G3dGetMdlByIdx(func_02083268(modelFile_), 0);
    NNSG3dResMdlSet* mdlSet = func_02083268(modelFile_);
    for (int i = 0; i < mdlSet->dict.numEntry; i++) {
        model_ = NNS_G3dGetMdlByIdx(func_02083268(modelFile_), i);
        func_020803d0(0, 0, 2, 0, 0x1f, 0x8000);
        func_02082e1c(model_, 0, 0x8000);
    }
}

ARM void UnkModelMember::releaseModelFile()
{
    releaseTextures();
}

ARM void UnkModelMember::loadTextures()
{
    NNSG3dResMdlSet* mdlSet = func_02083268(modelFile_);
    NNSG3dResTex* tex = func_02083270(modelFile_);
    if (tex == NULL) {
        return;
    }
    data_020f3e84 = tex;
    texture_ = tex;
    int texSize = func_0207fc2c(tex);
    func_0207fc3c(tex);
    int plttSize = func_0207fd08(tex);
    int texKey = data_020f4f74.allocTexVram(texSize);
    int plttKey = data_020f4f74.allocPlttVram(plttSize);
    setPaletteEffectTexture(tex);
    if (!(tex->texInfo.flag & 1)) {
        func_0207fc4c(tex, texKey, 0);
        func_0207fd18(tex, plttKey);
        OS_Wait();
        func_0207fc5c(tex, 1);
        func_0207fd1c(tex, 1);
    }
    func_0208012c(mdlSet, tex);
}

ARM void UnkModelMember::releaseTextures()
{
    NNSG3dResMdlSet* mdlSet = func_02083268(modelFile_);
    NNSG3dResTex* tex = func_02083270(modelFile_);
    if (tex == NULL) {
        return;
    }
    func_02080194(mdlSet);
    int plttKey = func_0207fd4c(tex);
    int texKey;
    int tex4x4Key;
    func_0207fcd8(tex, &texKey, &tex4x4Key);
    if (plttKey != 0) {
        data_020f4f74.freePlttVram(plttKey);
    }
    if (texKey != 0) {
        data_020f4f74.freeTexVram(texKey);
    }
    data_020f3e84 = NULL;
    texture_ = NULL;
}

ARM void* UnkModelMember::getModelFile()
{
    return modelFile_;
}

ARM NNSG3dResMdl* UnkModelMember::getModel()
{
    return model_;
}

ARM NNSG3dResTex* getLastModelTexture()
{
    return data_020f3e84;
}
