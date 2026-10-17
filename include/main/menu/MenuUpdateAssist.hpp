#pragma once
#include "main/menu/UnkCursorMoveGridLoop.hpp"

namespace menu {
    struct MenuItem;
}

namespace MenuUpdate_Assist {
    int isPageFlip(menu::MenuItem& item, UnkCursorMoveBase& cursor, int& active);
    int isPageFlipOne(menu::MenuItem& item, UnkCursorMoveBase& cursor, int& active);
    int isCancel(menu::MenuItem& item);
    int menuSelect(menu::MenuItem& item, UnkCursorMoveBase& cursor);
}
