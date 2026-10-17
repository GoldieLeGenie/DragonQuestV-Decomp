#pragma ipa file
#include "main/object/SpriteCharacter.hpp"
#include "main/dss/UnkArchive.hpp"
#include "main/dss/UnkTextureObject.hpp"

#pragma thumb on

dss::BitFlag<unsigned char> SpriteCharacter::allFlag_(SpriteCharacter::FLAG_ANIM);
static UnkTextureObject* s_shadowTexture;
static DataObject s_commonTex;
static int s_shadowDraw = 1;

SpriteCharacter::SpriteCharacter()
{
}

SpriteCharacter::~SpriteCharacter()
{
}

void SpriteCharacter::setup(const char* name, int width, int height, int flag)
{
    data_.setup(name, flag, 0);
    unkfunc_0205833c(width, height);
}

void SpriteCharacter::unkfunc_0205833c(int width, int height)
{
    textureNum_ = unkfunc_0204c860(data_.getAddr());
    for (int i = 0; i < textureNum_; i++) {
        unk_78[i] = (UnkTextureObject*)unkfunc_0204c878(data_.getAddr(), i);
    }
    unk_58 = unk_78[0];
    unk_58->unkfunc_02049e9c(1);
    texture_ = unk_58;
    unkfunc_02047e88(0, 0);
    anmIndex_ = 0;
    direction_ = -1;
    dispDirection_ = 0;
    unk_9c = width;
    unk_a0 = height;
    unkfunc_020583ec();
    shadow_.unkfunc_0205876c();
    flag_.flag_ |= FLAG_DEFAULT;
}

void SpriteCharacter::cleanup()
{
    unk_58->unkfunc_02049f90();
    data_.cleanup();
    shadow_.unkfunc_020587b4();
}

void SpriteCharacter::unkfunc_020583ec()
{
    unkfunc_02047ec0(unk_9c, unk_a0);
    unkfunc_02047ecc(0, 0, unk_9c, unk_a0);
    unk_2c = 1;
}

void SpriteCharacter::setAlpha(int alpha)
{
    UnkRenderObject::setAlpha(alpha);
    shadow_.setAlpha((unsigned char)((unsigned int)alpha >> 1));
}

void SpriteCharacter::draw()
{
    if (flag_.check(FLAG_DISPLAY) == false) {
        return;
    }
    execute();
    UnkSprite2D::draw();
    if (flag_.check(FLAG_SHADOW)) {
        shadow_.draw();
    }
}

void SpriteCharacter::execute()
{
    if (flag_.check(FLAG_ANIM_NEUTRAL)) {
        if (!(allFlag_.flag_ & FLAG_ANIM)) {
            return;
        }
    } else if (!flag_.check(FLAG_ANIM)) {
        return;
    }
    switch (anmIndex_ / 12) {
    case 0:
        unkfunc_02047ecc(0, 0, unk_9c, unk_a0);
        break;
    case 1:
        unkfunc_02047ecc(unk_9c, 0, unk_9c * 2, unk_a0);
        break;
    case 2:
        unkfunc_02047ecc(unk_9c * 2, 0, unk_9c * 3, unk_a0);
        break;
    case 3:
        unkfunc_02047ecc(unk_9c, 0, unk_9c * 2, unk_a0);
        break;
    }
    anmIndex_++;
    anmIndex_ = dss::loop<long>(anmIndex_, 0, 0x30);
}

void SpriteCharacter::unkfunc_0205853c(int dir)
{
    if (dispDirection_ == dir && !flag_.check(FLAG_RELOAD)) {
        return;
    }
    unk_58->unkfunc_0204a114(unk_78[dir], 0);
    dispDirection_ = dir;
}

void SpriteCharacter::reload()
{
    flag_.flag_ |= FLAG_RELOAD;
}

void SpriteCharacter::setPosition(int x, int y)
{
    unkfunc_02047e88(x - unk_9c / 2, y - unk_a0);
    if (flag_.check(FLAG_STAY)) {
        shadow_.setPosition(x, y);
    }
}

void SpriteCharacter::setPosition(dss::Vector2<int> pos)
{
    unkfunc_02047e88(pos.vx - unk_9c / 2, pos.vy - unk_a0);
    if (flag_.check(FLAG_STAY)) {
        shadow_.setPosition(pos.vx, pos.vy);
    }
}

void SpriteCharacter::setDirection(unsigned short dir)
{
    if (textureNum_ == 4) {
        direction_ = dir / 2;
        unkfunc_0205853c(direction_);
    } else {
        direction_ = dir;
        unkfunc_0205853c(direction_);
    }
}

void SpriteCharacter::setDisplayEnable(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_DISPLAY;
    } else {
        flag_.flag_ &= ~FLAG_DISPLAY;
    }
}

int SpriteCharacter::isDisplayEnable()
{
    return flag_.check(FLAG_DISPLAY);
}

void SpriteCharacter::setShadowStay(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_STAY;
    } else {
        flag_.flag_ &= ~FLAG_STAY;
    }
}

void SpriteCharacter::setAnimFlag(int flag)
{
    if (flag == 1) {
        flag_.flag_ |= FLAG_ANIM;
        flag_.flag_ &= ~FLAG_ANIM_NEUTRAL;
    } else if (flag == 2) {
        flag_.flag_ |= FLAG_ANIM_NEUTRAL;
    } else {
        flag_.flag_ &= ~FLAG_ANIM;
        flag_.flag_ &= ~FLAG_ANIM_NEUTRAL;
    }
}

void SpriteCharacter::setShadowFlag(int flag)
{
    if (flag) {
        flag_.flag_ |= FLAG_SHADOW;
    } else {
        flag_.flag_ &= ~FLAG_SHADOW;
    }
}

void SpriteCharacter::setAllCharaAnim(int flag)
{
    if (flag) {
        allFlag_.flag_ |= FLAG_ANIM;
    } else {
        allFlag_.flag_ &= ~FLAG_ANIM;
    }
}

int SpriteCharacter::getAllCharaAnim()
{
    return (allFlag_.flag_ & FLAG_ANIM) ? true : false;
}

int SpriteCharacter::unkfunc_020586dc()
{
    if (!allFlag_.check(FLAG_ANIM)) {
        return false;
    }
    return true;
}

SpriteShadow::SpriteShadow()
{
}

SpriteShadow::~SpriteShadow()
{
}

void SpriteCharacter::unkfunc_0205870c()
{
    s_commonTex.setup("data/common.tex", 0, 0);
    s_shadowTexture = (UnkTextureObject*)s_commonTex.getAddr();
    s_shadowTexture->unkfunc_02049e9c(1);
}

void SpriteCharacter::unkfunc_02058738()
{
    s_shadowTexture->unkfunc_02049f90();
    s_commonTex.cleanup();
}

void SpriteCharacter::unkfunc_02058754()
{
    if (s_shadowTexture) {
        s_shadowTexture->unkfunc_0204a090(0);
    }
}

void SpriteShadow::unkfunc_0205876c()
{
    texture_ = s_shadowTexture;
    unkfunc_02047e88(0, 0);
    unkfunc_02047ec0(0x12, 0xc);
    unkfunc_02047ecc(0, 0, 0x20, 0x20);
    unk_2c = 1;
    unk_28 = 4;
    setAlpha(15);
}

void SpriteShadow::unkfunc_020587b4()
{
}

void SpriteShadow::draw()
{
    if (s_shadowDraw) {
        UnkSprite2D::draw();
    }
}

void SpriteShadow::setPosition(int x, int y)
{
    unkfunc_02047e88(x - 9, y - 8);
}
