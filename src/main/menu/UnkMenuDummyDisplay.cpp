#include "main/menu/UnkMenuDummyDisplay.hpp"

THUMB UnkMenuDummyDisplay::UnkMenuDummyDisplay()
{
}

THUMB void UnkMenuDummyDisplay::setup(int id)
{
    id_ = id;
    unkfunc_020646c8();
    unkfunc_0206477c(1);
}

THUMB void UnkMenuDummyDisplay::update(UnkOamBuffer* main, UnkOamBuffer* sub)
{
}

THUMB void UnkMenuDummyDisplay::execute(UnkOamBuffer* main, UnkOamBuffer* sub)
{
}

THUMB void UnkMenuDummyDisplay::draw(UnkOamBuffer* main, UnkOamBuffer* sub)
{
}
