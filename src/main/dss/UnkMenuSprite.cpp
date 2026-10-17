#include "main/dss/UnkSprite2D.hpp"
#include "main/dss/UnkRenderObject.hpp"
#include "main/dss/UnkTextureObject.hpp"

THUMB UnkMenuSprite::UnkMenuSprite()
{
    texture_ = 0;
}

THUMB UnkMenuSprite::~UnkMenuSprite()
{
}

THUMB void UnkMenuSprite::unkfunc_02051a20()
{
    ((UnkTextureObject*)texture_)->unkfunc_02049f90();
}

THUMB void UnkMenuSprite::unkfunc_02051a2c()
{
    ((UnkTextureObject*)texture_)->unkfunc_0204a090(0);
}

THUMB void UnkMenuSprite::unkfunc_02051a38()
{
    ((UnkTextureObject*)texture_)->unkfunc_0204a004();
}

THUMB int UnkMenuSprite::unkfunc_02051a44()
{
    return ((UnkTextureObject*)texture_)->unkfunc_0204a1c4();
}

THUMB void UnkMenuSprite::unkfunc_02051a50(const char* filename, int a)
{
    data_.setup(filename, a, 0);
    unkfunc_02051a68();
}

THUMB void UnkMenuSprite::unkfunc_02051a68()
{
    texture_ = data_.getAddr();
    ((UnkTextureObject*)texture_)->unkfunc_02049e9c(1);
    sprite_.texture_ = texture_;
    sprite_.unkfunc_02047e88(0, 0);
    sprite_.unkfunc_02047ec0(((UnkTextureObject*)texture_)->unkfunc_0204a340(), ((UnkTextureObject*)texture_)->unkfunc_0204a38c());
    sprite_.unkfunc_02047ecc(0, 0, ((UnkTextureObject*)texture_)->unkfunc_0204a340(), ((UnkTextureObject*)texture_)->unkfunc_0204a38c());
}

THUMB void UnkMenuSprite::unkfunc_02051ac4()
{
    ((UnkTextureObject*)texture_)->unkfunc_02049f90();
    data_.cleanup();
    texture_ = 0;
}

THUMB void UnkMenuSprite::unkfunc_02051adc(Render* render)
{
    render_ = render;
    render->unkfunc_02048c2c(&sprite_);
}

THUMB void UnkMenuSprite::unkfunc_02051af0()
{
    render_->unkfunc_02048c54(&sprite_);
    render_ = 0;
}

THUMB int UnkMenuSprite::unkfunc_02051b04()
{
    if (texture_) {
        return 1;
    }
    return 0;
}

THUMB void UnkMenuSprite::unkfunc_02051b14(int x, int y)
{
    sprite_.unkfunc_02047e88(x, y);
}

THUMB void UnkMenuSprite::unkfunc_02051b20(int w, int h)
{
    sprite_.unkfunc_02047ec0(w, h);
}

THUMB void UnkMenuSprite::unkfunc_02051b2c(int u0, int v0, int u1, int v1)
{
    sprite_.unkfunc_02047ecc(u0, v0, u1, v1);
}

THUMB void UnkMenuSprite::unkfunc_02051b40(dss::Fix32 x, dss::Fix32 y)
{
    sprite_.unkfunc_02047e9c(x, y);
}

THUMB void UnkMenuSprite::unkfunc_02051b68()
{
    sprite_.draw();
}

THUMB void UnkMenuSprite::unkfunc_02051b74(int enable)
{
    sprite_.enable_ = enable;
}

THUMB void UnkMenuSprite::unkfunc_02051b78()
{
    sprite_.unk_2c = 1;
}

THUMB void UnkMenuSprite::unkfunc_02051b80()
{
    sprite_.unk_2c = 2;
}

THUMB void UnkMenuSprite::unkfunc_02051b88()
{
    sprite_.unk_2c = 3;
}

THUMB void UnkMenuSprite::unkfunc_02051b90(int a)
{
    sprite_.setAlpha((unsigned char)a);
}

THUMB void UnkMenuSprite::unkfunc_02051ba0(int polygonID)
{
    sprite_.setPolygonID((unsigned char)polygonID);
}

THUMB void UnkMenuSprite::unkfunc_02051bb0(int a)
{
    sprite_.unk_28 = a;
}

THUMB void UnkMenuSprite::unkfunc_02051bb4(int a)
{
    sprite_.unk_30 = a;
}

THUMB void UnkMenuSprite::unkfunc_02051bbc(unsigned char r, unsigned char g, unsigned char b)
{
    sprite_.setColor(r, g, b);
}

THUMB void UnkMenuSprite::unkfunc_02051bc8(int color)
{
    sprite_.setColor(color);
}
