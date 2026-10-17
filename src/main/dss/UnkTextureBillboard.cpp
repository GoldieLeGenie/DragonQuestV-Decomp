#include "main/dss/UnkBillboard.hpp"

ARM void UnkTextureBillboard::unkfunc_0205071c(const UnkBillboardVertex* vertex, const UnkBillboardTexCoord* texCoord, void* texture)
{
    texture_ = texture;
    ((UnkTextureObject*)texture)->unkfunc_02049e9c(1);
    unkfunc_02047a20(vertex);
    unkfunc_02047a94(texCoord);
    UnkRenderObject::texture_ = texture_;
}

ARM void UnkTextureBillboard::unkfunc_02050760()
{
    ((UnkTextureObject*)texture_)->unkfunc_02049f90();
}

ARM void UnkTextureBillboard::unkfunc_02050770(int a)
{
    ((UnkTextureObject*)texture_)->unkfunc_0204a114((UnkTextureObject*)(void*)a, 0);
}
