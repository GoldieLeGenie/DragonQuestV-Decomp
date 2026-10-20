#include "main/dss/Billboard.hpp"

ARM void TextureBillboard::unkfunc_0205071c(const UnkBillboardVertex* vertex, const UnkBillboardTexCoord* texCoord, void* texture)
{
    texture_ = texture;
    ((TextureObject*)texture)->unkfunc_02049e9c(1);
    unkfunc_02047a20(vertex);
    unkfunc_02047a94(texCoord);
    RenderObject::texture_ = texture_;
}

ARM void TextureBillboard::unkfunc_02050760()
{
    ((TextureObject*)texture_)->unkfunc_02049f90();
}

ARM void TextureBillboard::unkfunc_02050770(int a)
{
    ((TextureObject*)texture_)->unkfunc_0204a114((TextureObject*)(void*)a, 0);
}
