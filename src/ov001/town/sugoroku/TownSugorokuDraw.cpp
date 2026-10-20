#pragma ipa file
#include "main/dss/DssVectorDefault.hpp"
#include "ov001/town/TownSugorokuDraw.hpp"
#include "main/dss/UnkArchive.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/TextureObject.hpp"

template <>
inline dss::Vector3<dss::Fix16>::Vector3() : vx(0L), vy(0L), vz(0L)
{
}

inline DSSAObject2D::DSSAObject2D()
{
}

#pragma thumb on

inline void UnkBillboardTexCoord::set(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
                                      const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

twn::TownSugorokuDraw::TownSugorokuDraw()
{
}

twn::TownSugorokuDraw::~TownSugorokuDraw()
{
}

void twn::TownSugorokuDraw::unkfunc_0214d3ac(const UnkPolygonVertex* xy)
{
    data_.setup("data/sugoroku/sgpall.tex", 0, 0);
    texture_ = data_.getAddr();
    ((TextureObject*)texture_)->loadToVram(1);
    int width = ((TextureObject*)texture_)->getWidth() / 32;
    dss::Vector2<dss::Fix32> leftTop;
    dss::Vector2<dss::Fix32> rightTop;
    dss::Vector2<dss::Fix32> rightBottom;
    dss::Vector2<dss::Fix32> leftBottom;
    for (int i = 0; i < PANEL_TYPE_MAX; i++) {
        int x = i % width;
        int y = i / width;
        leftTop.vx.value = x << 17;
        leftTop.vy.value = y << 17;
        rightTop.vx.value = (x + 1) << 17;
        rightTop.vy.value = y << 17;
        rightBottom.vx.value = (x + 1) << 17;
        rightBottom.vy.value = (y + 1) << 17;
        leftBottom.vx.value = x << 17;
        leftBottom.vy.value = (y + 1) << 17;
        uv_[i].set(leftBottom, rightBottom, rightTop, leftTop);
    }
    xy_ = *xy;
    polygon_.RenderObject::texture_ = texture_;
    polygon_.setVertex(&xy_);
}

void twn::TownSugorokuDraw::unkfunc_0214d568(int type, dss::Fix32Vector3& pos)
{
    polygon_.setTexCoord(&uv_[type]);
    polygon_.setPosition(pos);
    polygon_.draw();
}

void twn::TownSugorokuDraw::cleanup()
{
    ((TextureObject*)texture_)->freeVram();
    data_.cleanup();
}

twn::TownSugorokuDice::TownSugorokuDice()
{
}

twn::TownSugorokuDice::~TownSugorokuDice()
{
}

void twn::TownSugorokuDice::setup()
{
    char path[128];
    dss::sprintf_s(path, sizeof(path), "data/sugoroku/dice.pack");
    diceData_.setup(path, 0, 0);
    texture_ = getArchiveFile(diceData_.getAddr(), 0);
    ((TextureObject*)texture_)->loadToVram(1);
    for (int i = 0; i < DICE_ANIM_MAX; i++) {
        diceAnim_[i].setup(getArchiveFile(diceData_.getAddr(), i + 1));
        diceAnim_[i].setTexture(texture_);
    }
    enable_ = false;
}

void twn::TownSugorokuDice::throwIn(int number)
{
    enable_ = true;
    number_ = number;
    diceAnim_[number - 1].start(0);
}

void twn::TownSugorokuDice::draw()
{
    if (enable_ == false) {
        return;
    }
    if (diceAnim_[number_ - 1].isEnd() == false) {
        if (getDisplayFrame() & 1) {
            diceAnim_[number_ - 1].draw();
        }
        diceAnim_[number_ - 1].execute();
    } else {
        enable_ = false;
    }
}

void twn::TownSugorokuDice::drawNumber(int number)
{
    if (getDisplayFrame() & 1) {
        diceAnim_[number + 5].draw();
    }
}

void twn::TownSugorokuDice::cleanup()
{
    for (int i = 0; i < DICE_ANIM_MAX; i++) {
        diceAnim_[i].cleanup();
    }
    ((TextureObject*)texture_)->freeVram();
    diceData_.cleanup();
}

twn::TownSugorokuArrow::TownSugorokuArrow()
{
}

twn::TownSugorokuArrow::~TownSugorokuArrow()
{
}

void twn::TownSugorokuArrow::setup(const UnkPolygonVertex* xy)
{
    arrowData_.setup("data/sugoroku/arrow.tex", 0, 0);
    texture_ = arrowData_.getAddr();
    ((TextureObject*)texture_)->loadToVram(1);
    dss::Vector2<dss::Fix32> leftTop;
    dss::Vector2<dss::Fix32> rightTop;
    dss::Vector2<dss::Fix32> rightBottom;
    dss::Vector2<dss::Fix32> leftBottom;
    for (int i = 0; i < ARROW_ANIM_MAX; i++) {
        leftTop.vx.value = i << 16;
        leftTop.vy.value = 0;
        rightTop.vx.value = (i + 1) << 16;
        rightTop.vy.value = 0;
        rightBottom.vx.value = (i + 1) << 16;
        rightBottom.vy.value = 1 << 16;
        leftBottom.vx.value = i << 16;
        leftBottom.vy.value = 1 << 16;
        uv_[i].set(leftBottom, rightBottom, rightTop, leftTop);
    }
    xy_ = *xy;
    polygon_.RenderObject::texture_ = texture_;
    polygon_.setVertex(&xy_);
    counter_ = 0;
    animFrame_ = 8;
}

void twn::TownSugorokuArrow::draw(dss::Fix32Vector3& pos)
{
    polygon_.setRotationIdx(rot_);
    polygon_.setTexCoord(&uv_[counter_ / animFrame_ % ARROW_ANIM_MAX]);
    polygon_.setPosition(pos);
    polygon_.draw();
    counter_++;
}

void twn::TownSugorokuArrow::cleanup()
{
    ((TextureObject*)texture_)->freeVram();
    arrowData_.cleanup();
}

void twn::TownSugorokuArrow::setRotate(unsigned short rot)
{
    rot_.vy = rot;
}
