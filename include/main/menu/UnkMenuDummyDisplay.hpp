#pragma once
#include <globaldefs.h>
#include "main/menu/MenuDisplay.hpp"

// Display object drawing nothing (data_02114dd4.dummy_)
struct UnkMenuDummyDisplay : MenuDisplay {
    UnkMenuDummyDisplay();
    virtual void setup(int id);
    virtual void update(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void execute(UnkOamBuffer* main, UnkOamBuffer* sub);
    virtual void draw(UnkOamBuffer* main, UnkOamBuffer* sub);
};
