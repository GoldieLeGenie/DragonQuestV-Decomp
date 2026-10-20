#include "main/dss/Sprite2D.hpp"
#include "main/dss/RenderObject.hpp"
#include "main/dss/TextureObject.hpp"

THUMB UnkMenuSprite::UnkMenuSprite()
{
    texture_ = 0;
}

THUMB UnkMenuSprite::~UnkMenuSprite()
{
}

THUMB void UnkMenuSprite::freeVram()
{
    ((TextureObject*)texture_)->freeVram();
}

THUMB void UnkMenuSprite::transferToVram()
{
    ((TextureObject*)texture_)->transferToVram(0);
}

THUMB void UnkMenuSprite::allocVram()
{
    ((TextureObject*)texture_)->allocVram();
}

THUMB int UnkMenuSprite::getTextureData()
{
    return ((TextureObject*)texture_)->getTexData();
}

THUMB void UnkMenuSprite::loadFile(const char* filename, int a)
{
    data_.setup(filename, a, 0);
    setupTexture();
}

THUMB void UnkMenuSprite::setupTexture()
{
    texture_ = data_.getAddr();
    ((TextureObject*)texture_)->loadToVram(1);
    sprite_.texture_ = texture_;
    sprite_.unkfunc_02047e88(0, 0);
    sprite_.setSize(((TextureObject*)texture_)->getWidth(), ((TextureObject*)texture_)->getHeight());
    sprite_.unkfunc_02047ecc(0, 0, ((TextureObject*)texture_)->getWidth(), ((TextureObject*)texture_)->getHeight());
}

THUMB void UnkMenuSprite::unload()
{
    ((TextureObject*)texture_)->freeVram();
    data_.cleanup();
    texture_ = 0;
}

THUMB void UnkMenuSprite::attachRender(Render* render)
{
    render_ = render;
    render->addSprite(&sprite_);
}

THUMB void UnkMenuSprite::detachRender()
{
    render_->removeSprite(&sprite_);
    render_ = 0;
}

THUMB int UnkMenuSprite::isLoaded()
{
    if (texture_) {
        return 1;
    }
    return 0;
}

THUMB void UnkMenuSprite::setPosition(int x, int y)
{
    sprite_.unkfunc_02047e88(x, y);
}

THUMB void UnkMenuSprite::setSize(int w, int h)
{
    sprite_.setSize(w, h);
}

THUMB void UnkMenuSprite::setTexCoords(int u0, int v0, int u1, int v1)
{
    sprite_.unkfunc_02047ecc(u0, v0, u1, v1);
}

THUMB void UnkMenuSprite::setPositionFix32(dss::Fix32 x, dss::Fix32 y)
{
    sprite_.setPositionFix32(x, y);
}

THUMB void UnkMenuSprite::draw()
{
    sprite_.draw();
}

THUMB void UnkMenuSprite::setEnabled(int enable)
{
    sprite_.enable_ = enable;
}

THUMB void UnkMenuSprite::setMainScreen()
{
    sprite_.screens_ = 1;
}

THUMB void UnkMenuSprite::setSubScreen()
{
    sprite_.screens_ = 2;
}

THUMB void UnkMenuSprite::setBothScreens()
{
    sprite_.screens_ = 3;
}

THUMB void UnkMenuSprite::setAlpha(int a)
{
    sprite_.setAlpha((unsigned char)a);
}

THUMB void UnkMenuSprite::setPolygonID(int polygonID)
{
    sprite_.setPolygonID((unsigned char)polygonID);
}

THUMB void UnkMenuSprite::setDepth(int a)
{
    sprite_.depth_ = a;
}

THUMB void UnkMenuSprite::setRotation(int a)
{
    sprite_.rotation_ = a;
}

THUMB void UnkMenuSprite::setColor(unsigned char r, unsigned char g, unsigned char b)
{
    sprite_.setColor(r, g, b);
}

THUMB void UnkMenuSprite::setColor555(int color)
{
    sprite_.setColor(color);
}
