#include "main/dss/Billboard.hpp"

ARM void TextureBillboard::unkfunc_0205071c(const UnkBillboardVertex* vertex, const UnkBillboardTexCoord* texCoord, void* texture)
{
    texture_ = texture;
    ((TextureObject*)texture)->loadToVram(1);
    unkfunc_02047a20(vertex);
    unkfunc_02047a94(texCoord);
    RenderObject::texture_ = texture_;
}

ARM void TextureBillboard::releaseTexture()
{
    ((TextureObject*)texture_)->freeVram();
}

ARM void TextureBillboard::changeTexture(int a)
{
    ((TextureObject*)texture_)->transferFrom((TextureObject*)(void*)a, 0);
}
