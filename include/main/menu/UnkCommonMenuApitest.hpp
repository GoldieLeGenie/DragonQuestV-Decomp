#pragma once
#include <globaldefs.h>
#include "main/menu/MenuBase.hpp"

struct UnkCommonMenuApitest : menu::MenuBase {
    virtual void menuSetup();
    virtual void menuExecute();
    virtual void menuDraw();
    virtual void menuUpdate();
};

extern UnkCommonMenuApitest data_020a2ae8;
