#include "main/menu/UnkMenuDisplays.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/UnkMenuSystem.hpp"

UnkMenuDisplays data_02114dd4;

THUMB void setupMenuDisplays()
{
    data_02114dd4.message_.setup(-1);
    data_02114dd4.yesNo_.setup(0x1d4);
    data_02114dd4.frames_.setup(0);
    data_02114dd4.face_.setup(0);
    data_02114dd4.icon_.setup(0);
    data_02114dd4.sprite_.setup(0);
    data_02114dd4.dummy_.setup(0);
    data_02114dd4.texts_[0].setup(0);
    data_02114dd4.texts_[1].setup(0x40);
    data_02114dd4.texts_[2].setup(0x80);
    data_02114dd4.texts_[3].setup(0xc0);
    data_02114dd4.windowFrame1_.setup(0);
    data_02114dd4.windowFrame2_.setup(0);
    data_02114dd4.arrow_.setup(0);
    data_02114dd4.hopping_.setup(0);
}

THUMB void disableMenuDisplays()
{
    data_02114dd4.message_.setEnable(0);
    data_02114dd4.yesNo_.setEnable(0);
    data_02114dd4.frames_.setEnable(0);
    data_02114dd4.face_.setEnable(0);
    data_02114dd4.icon_.setEnable(0);
    data_02114dd4.sprite_.setEnable(0);
    data_02114dd4.dummy_.setEnable(0);
    data_02114dd4.texts_[0].setEnable(0);
    data_02114dd4.texts_[1].setEnable(0);
    data_02114dd4.texts_[2].setEnable(0);
    data_02114dd4.texts_[3].setEnable(0);
    data_02114dd4.windowFrame1_.setEnable(0);
    data_02114dd4.windowFrame2_.setEnable(0);
    data_02114dd4.arrow_.setEnable(0);
    data_02114dd4.hopping_.setEnable(0);
}

THUMB void unkfunc_02063d94()
{
    UnkOamBuffer* main = getOamBufferAtY(0);
    UnkOamBuffer* sub = getOamBufferAtY(192);
    data_02114dd4.message_.update(main, sub);
    data_02114dd4.yesNo_.update(main, sub);
    data_02114dd4.face_.update(main, sub);
    data_02114dd4.icon_.update(main, sub);
    data_02114dd4.sprite_.update(main, sub);
    data_02114dd4.windowFrame1_.update(main, sub);
    data_02114dd4.windowFrame2_.update(main, sub);
    data_02114dd4.arrow_.update(main, sub);
    data_02114dd4.dummy_.update(main, sub);
    data_02114dd4.texts_[0].update(main, sub);
    data_02114dd4.texts_[1].update(main, sub);
    data_02114dd4.texts_[2].update(main, sub);
    data_02114dd4.texts_[3].update(main, sub);
    data_02114dd4.frames_.update(main, sub);
    data_02114dd4.hopping_.update(main, sub);
}

THUMB void unkfunc_02063e98()
{
    UnkOamBuffer* main = getOamBufferAtY(0);
    UnkOamBuffer* sub = getOamBufferAtY(192);
    data_02114dd4.message_.execute(main, sub);
    data_02114dd4.yesNo_.execute(main, sub);
    data_02114dd4.face_.execute(main, sub);
    data_02114dd4.icon_.execute(main, sub);
    data_02114dd4.sprite_.execute(main, sub);
    data_02114dd4.windowFrame1_.execute(main, sub);
    data_02114dd4.windowFrame2_.execute(main, sub);
    data_02114dd4.arrow_.execute(main, sub);
    data_02114dd4.dummy_.execute(main, sub);
    data_02114dd4.texts_[0].execute(main, sub);
    data_02114dd4.texts_[1].execute(main, sub);
    data_02114dd4.texts_[2].execute(main, sub);
    data_02114dd4.texts_[3].execute(main, sub);
    data_02114dd4.frames_.execute(main, sub);
    data_02114dd4.hopping_.execute(main, sub);
}

THUMB void unkfunc_02063f9c()
{
    UnkOamBuffer* main = getOamBufferAtY(0);
    UnkOamBuffer* sub = getOamBufferAtY(192);
    data_02114dd4.face_.draw(main, sub);
    data_02114dd4.icon_.draw(main, sub);
    data_02114dd4.sprite_.draw(main, sub);
    data_02114dd4.dummy_.draw(main, sub);
    data_02114dd4.message_.draw(main, sub);
    data_02114dd4.yesNo_.draw(main, sub);
    data_02114dd4.windowFrame1_.draw(main, sub);
    data_02114dd4.windowFrame2_.draw(main, sub);
    data_02114dd4.texts_[0].draw(main, sub);
    data_02114dd4.texts_[1].draw(main, sub);
    data_02114dd4.texts_[2].draw(main, sub);
    data_02114dd4.texts_[3].draw(main, sub);
    data_02114dd4.yesNo_.unkfunc_0206756c(main, sub);
    data_02114dd4.frames_.draw(main, sub);
    data_02114dd4.arrow_.draw(main, sub);
    data_02114dd4.hopping_.draw(main, sub);
    moveMenuDisplays();
    disableMenuDisplays();
}

THUMB void moveMenuDisplays()
{
    data_02114dd4.face_.updateMove();
    data_02114dd4.icon_.updateMove();
    data_02114dd4.sprite_.updateMove();
    data_02114dd4.dummy_.updateMove();
    data_02114dd4.message_.updateMove();
    data_02114dd4.yesNo_.updateMove();
    data_02114dd4.windowFrame1_.updateMove();
    data_02114dd4.windowFrame2_.updateMove();
    data_02114dd4.texts_[0].updateMove();
    data_02114dd4.texts_[1].updateMove();
    data_02114dd4.texts_[2].updateMove();
    data_02114dd4.texts_[3].updateMove();
    data_02114dd4.frames_.updateMove();
    data_02114dd4.arrow_.updateMove();
    data_02114dd4.hopping_.updateMove();
}

THUMB void unkfunc_02064154()
{
    data_02114dd4.face_.reset();
    data_02114dd4.icon_.reset();
    data_02114dd4.sprite_.reset();
    data_02114dd4.dummy_.reset();
    data_02114dd4.frames_.reset();
    data_02114dd4.texts_[0].reset();
    data_02114dd4.texts_[1].reset();
    data_02114dd4.texts_[2].reset();
    data_02114dd4.texts_[3].reset();
    data_02114dd4.windowFrame1_.reset();
    data_02114dd4.windowFrame2_.reset();
    data_02114dd4.arrow_.reset();
    data_02114dd4.hopping_.reset();
}
