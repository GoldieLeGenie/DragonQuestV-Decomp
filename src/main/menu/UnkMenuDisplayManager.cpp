#include "main/menu/UnkMenuDisplays.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/menu/UnkMenuSystem.hpp"

UnkMenuDisplays data_02114dd4;

THUMB void unkfunc_02063c00()
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

THUMB void unkfunc_02063cdc()
{
    data_02114dd4.message_.unkfunc_02064780(0);
    data_02114dd4.yesNo_.unkfunc_02064780(0);
    data_02114dd4.frames_.unkfunc_02064780(0);
    data_02114dd4.face_.unkfunc_02064780(0);
    data_02114dd4.icon_.unkfunc_02064780(0);
    data_02114dd4.sprite_.unkfunc_02064780(0);
    data_02114dd4.dummy_.unkfunc_02064780(0);
    data_02114dd4.texts_[0].unkfunc_02064780(0);
    data_02114dd4.texts_[1].unkfunc_02064780(0);
    data_02114dd4.texts_[2].unkfunc_02064780(0);
    data_02114dd4.texts_[3].unkfunc_02064780(0);
    data_02114dd4.windowFrame1_.unkfunc_02064780(0);
    data_02114dd4.windowFrame2_.unkfunc_02064780(0);
    data_02114dd4.arrow_.unkfunc_02064780(0);
    data_02114dd4.hopping_.unkfunc_02064780(0);
}

THUMB void unkfunc_02063d94()
{
    UnkOamBuffer* main = unkfunc_0204ce40(0);
    UnkOamBuffer* sub = unkfunc_0204ce40(192);
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
    UnkOamBuffer* main = unkfunc_0204ce40(0);
    UnkOamBuffer* sub = unkfunc_0204ce40(192);
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
    UnkOamBuffer* main = unkfunc_0204ce40(0);
    UnkOamBuffer* sub = unkfunc_0204ce40(192);
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
    unkfunc_020640b8();
    unkfunc_02063cdc();
}

THUMB void unkfunc_020640b8()
{
    data_02114dd4.face_.unkfunc_020646dc();
    data_02114dd4.icon_.unkfunc_020646dc();
    data_02114dd4.sprite_.unkfunc_020646dc();
    data_02114dd4.dummy_.unkfunc_020646dc();
    data_02114dd4.message_.unkfunc_020646dc();
    data_02114dd4.yesNo_.unkfunc_020646dc();
    data_02114dd4.windowFrame1_.unkfunc_020646dc();
    data_02114dd4.windowFrame2_.unkfunc_020646dc();
    data_02114dd4.texts_[0].unkfunc_020646dc();
    data_02114dd4.texts_[1].unkfunc_020646dc();
    data_02114dd4.texts_[2].unkfunc_020646dc();
    data_02114dd4.texts_[3].unkfunc_020646dc();
    data_02114dd4.frames_.unkfunc_020646dc();
    data_02114dd4.arrow_.unkfunc_020646dc();
    data_02114dd4.hopping_.unkfunc_020646dc();
}

THUMB void unkfunc_02064154()
{
    data_02114dd4.face_.unkfunc_020646c8();
    data_02114dd4.icon_.unkfunc_020646c8();
    data_02114dd4.sprite_.unkfunc_020646c8();
    data_02114dd4.dummy_.unkfunc_020646c8();
    data_02114dd4.frames_.unkfunc_020646c8();
    data_02114dd4.texts_[0].unkfunc_020646c8();
    data_02114dd4.texts_[1].unkfunc_020646c8();
    data_02114dd4.texts_[2].unkfunc_020646c8();
    data_02114dd4.texts_[3].unkfunc_020646c8();
    data_02114dd4.windowFrame1_.unkfunc_020646c8();
    data_02114dd4.windowFrame2_.unkfunc_020646c8();
    data_02114dd4.arrow_.unkfunc_020646c8();
    data_02114dd4.hopping_.unkfunc_020646c8();
}
