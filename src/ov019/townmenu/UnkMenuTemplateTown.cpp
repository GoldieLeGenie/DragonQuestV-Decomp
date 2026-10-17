#pragma ipa file
#include "ov019/townmenu/UnkMenuTemplateTown.hpp"

// touch areas of the town menus

THUMB void unkfunc_02171338(menu::MenuItem* menuItem, int active, int max)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x20, 0x3c, 0x56, 0x10},
        {1, 2, 0x80, 0x3c, 0x56, 0x10},
        {1, 2, 0x20, 0x54, 0x56, 0x10},
        {1, 2, 0x80, 0x54, 0x56, 0x10},
        {1, 2, 0x20, 0x6c, 0x56, 0x10},
        {1, 2, 0x80, 0x6c, 0x56, 0x10},
        {1, 2, 0x20, 0x84, 0x56, 0x10},
        {1, 2, 0x80, 0x84, 0x56, 0x10},
        {1, 2, 0x20, 0x9c, 0x56, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 5, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_02171354(menu::MenuItem* menuItem, int active, int max)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x14, 0x74, 0x20, 0x18},
        {1, 2, 0x3c, 0x74, 0x20, 0x18},
        {1, 2, 0x64, 0x74, 0x20, 0x18},
        {1, 2, 0x8c, 0x74, 0x20, 0x18},
        {1, 2, 0xb4, 0x74, 0x20, 0x18},
        {1, 2, 0x14, 0x9c, 0x20, 0x18},
        {1, 2, 0x3c, 0x9c, 0x20, 0x18},
        {1, 2, 0x64, 0x9c, 0x20, 0x18},
        {1, 2, 0x8c, 0x9c, 0x20, 0x18},
        {1, 2, 0xb4, 0x9c, 0x20, 0x18},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 5, 2, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_02171370(menu::MenuItem* menuItem, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x58, 0x2a, 0x10, 0x10},
        {1, 2, 0x78, 0x2a, 0x10, 0x10},
        {1, 2, 0x98, 0x2a, 0x10, 0x10},
        {1, 2, 0xb8, 0x2a, 0x10, 0x10},
        {1, 2, 0xd8, 0x2a, 0x10, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 5, 1, 5);
    menuItem->active_ = active;
}

THUMB void unkfunc_0217138c(menu::MenuItem* menuItem, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x58, 0x42, 0x10, 0x10},
        {1, 2, 0x78, 0x42, 0x10, 0x10},
        {1, 2, 0x98, 0x42, 0x10, 0x10},
        {1, 2, 0xb8, 0x42, 0x10, 0x10},
        {1, 2, 0xd8, 0x42, 0x10, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 5, 1, 5);
    menuItem->active_ = active;
}

THUMB void unkfunc_021713a8(menu::MenuItem* menuItem, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x58, 0x8a, 0x10, 0x10},
        {1, 2, 0x78, 0x8a, 0x10, 0x10},
        {1, 2, 0x98, 0x8a, 0x10, 0x10},
        {1, 2, 0xb8, 0x8a, 0x10, 0x10},
        {1, 2, 0xd8, 0x8a, 0x10, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 5, 1, 5);
    menuItem->active_ = active;
}

THUMB void unkfunc_021713c4(menu::MenuItem* menuItem, int active)
{
    const int rootX = 64;
    const int rootY = 96;
    const int rootW = 72;
    const int rootH = 32;
    static MENUITEM_DATA menu[] = {
        {1, 2, rootX, rootY, rootW, rootH},
        {1, 2, rootX + rootW, rootY, rootW, rootH},
        {1, 2, rootX, rootY + rootH, rootW, rootH},
        {1, 2, rootX + rootW, rootY + rootH, rootW, rootH},
        {1, 2, rootX, rootY + rootH * 2, rootW, rootH},
        {1, 2, rootX + rootW, rootY + rootH * 2, rootW, rootH},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 3, 6);
    menuItem->active_ = active;
}

THUMB void unkfunc_021713e0(menu::MenuItem* menuItem, int commandFlag, int active)
{
    static MENUITEM_DATA menuAll[] = {
        {1, 2, 0x10, 0x70, 0x40, 0x10},
        {1, 2, 0x60, 0x70, 0x40, 0x10},
        {1, 2, 0xb0, 0x70, 0x40, 0x10},
        {1, 2, 0x10, 0x88, 0x40, 0x10},
        {1, 2, 0x60, 0x88, 0x40, 0x10},
        {1, 2, 0xb0, 0x88, 0x40, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    static MENUITEM_DATA menuNone[] = {
        {1, 2, 0x10, 0x70, 0x40, 0x10},
        {1, 2, 0x60, 0x70, 0x40, 0x10},
        {1, 2, 0xb0, 0x70, 0x40, 0x10},
        {1, 2, 0x10, 0x88, 0x40, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    static MENUITEM_DATA menuOnlyEquip[] = {
        {1, 2, 0x10, 0x70, 0x40, 0x10},
        {1, 2, 0x60, 0x70, 0x40, 0x10},
        {1, 2, 0xb0, 0x70, 0x40, 0x10},
        {1, 2, 0x10, 0x88, 0x40, 0x10},
        {1, 2, 0x60, 0x88, 0x40, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    static MENUITEM_DATA menuOnlyShow[] = {
        {1, 2, 0x10, 0x70, 0x40, 0x10},
        {1, 2, 0x60, 0x70, 0x40, 0x10},
        {1, 2, 0xb0, 0x70, 0x40, 0x10},
        {1, 2, 0x10, 0x88, 0x40, 0x10},
        {1, 2, 0x60, 0x88, 0x40, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    switch (commandFlag) {
        case 0:
            menuItem->setMenuItem(menuNone, 3, 2, 4);
            menuItem->active_ = active;
            break;
        case 1:
            menuItem->setMenuItem(menuOnlyEquip, 3, 2, 5);
            menuItem->active_ = active;
            break;
        case 2:
            menuItem->setMenuItem(menuOnlyShow, 3, 2, 5);
            menuItem->active_ = active;
            break;
        case 3:
            menuItem->setMenuItem(menuAll, 3, 2, 6);
            menuItem->active_ = active;
            break;
    }
}

THUMB void unkfunc_02171458(menu::MenuItem* menuItem, int max, int active, int x, int y)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x14, 0x58, 0x20, 0x18},
        {1, 2, 0x3c, 0x58, 0x20, 0x18},
        {1, 2, 0x64, 0x58, 0x20, 0x18},
        {1, 2, 0x8c, 0x58, 0x20, 0x18},
        {1, 2, 0xb4, 0x58, 0x20, 0x18},
        {1, 2, 0x14, 0x80, 0x20, 0x18},
        {1, 2, 0x3c, 0x80, 0x20, 0x18},
        {1, 2, 0x64, 0x80, 0x20, 0x18},
        {1, 2, 0x8c, 0x80, 0x20, 0x18},
        {1, 2, 0xb4, 0x80, 0x20, 0x18},
        {-1, -1, 0, 0, 0, 0},
    };
    if (x != -1 && y != -1) {
        for (int i = 0; i < 10; i++) {
            unkfunc_02067ca4(&menu[i], x, y);
        }
    }
    menuItem->setMenuItem(menu, 5, 2, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_021714a8(menu::MenuItem* menuItem, int max, int active, int x, int y)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x14, 0x80, 0x20, 0x18},
        {1, 2, 0x3c, 0x80, 0x20, 0x18},
        {1, 2, 0x64, 0x80, 0x20, 0x18},
        {1, 2, 0x8c, 0x80, 0x20, 0x18},
        {1, 2, 0xb4, 0x80, 0x20, 0x18},
        {-1, -1, 0, 0, 0, 0},
    };
    if (x != -1 && y != -1) {
        for (int i = 0; i < 10; i++) {
            unkfunc_02067ca4(&menu[i], x, y);
        }
    }
    menuItem->setMenuItem(menu, 5, 1, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_021714f8(menu::MenuItem* menuItem, int max, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x14, 0x58, 0x20, 0x18},
        {1, 2, 0x3c, 0x58, 0x20, 0x18},
        {1, 2, 0x64, 0x58, 0x20, 0x18},
        {1, 2, 0x8c, 0x58, 0x20, 0x18},
        {1, 2, 0xb4, 0x58, 0x20, 0x18},
        {1, 2, 0x14, 0x80, 0x20, 0x18},
        {1, 2, 0x3c, 0x80, 0x20, 0x18},
        {1, 2, 0x64, 0x80, 0x20, 0x18},
        {1, 2, 0x8c, 0x80, 0x20, 0x18},
        {1, 2, 0xb4, 0x80, 0x20, 0x18},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 5, 2, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_02171514(menu::MenuItem* menuItem, int max, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x14, 0x80, 0x20, 0x18},
        {1, 2, 0x3c, 0x80, 0x20, 0x18},
        {1, 2, 0x64, 0x80, 0x20, 0x18},
        {1, 2, 0x8c, 0x80, 0x20, 0x18},
        {1, 2, 0xb4, 0x80, 0x20, 0x18},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 5, 1, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_02171530(menu::MenuItem* menuItem, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x1c, 0x08, 0x38, 0x18},
        {1, 2, 0x5c, 0x08, 0x38, 0x18},
        {1, 2, 0x9c, 0x08, 0x38, 0x18},
        {1, 2, 0x1c, 0x28, 0x38, 0x18},
        {1, 2, 0x5c, 0x28, 0x38, 0x18},
        {1, 2, 0x9c, 0x28, 0x38, 0x18},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 3, 2, 6);
    menuItem->active_ = active;
}

// unused 2x3 list (its table stays in the data)
THUMB void unkfunc_unused_0217f30c(menu::MenuItem* menuItem, int active)
{
    const int offsetY = 32;
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x14, 0x0c, 0x68, 0x18},
        {1, 2, 0x8c, 0x0c, 0x68, 0x18},
        {1, 2, 0x14, 0x0c + offsetY, 0x68, 0x18},
        {1, 2, 0x8c, 0x0c + offsetY, 0x68, 0x18},
        {1, 2, 0x14, 0x0c + offsetY * 2, 0x68, 0x18},
        {1, 2, 0x8c, 0x0c + offsetY * 2, 0x68, 0x18},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 3, 6);
    menuItem->active_ = active;
}

THUMB void unkfunc_0217154c(menu::MenuItem* menuItem, int max, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x0c, 0x0c, 0x70, 0x38},
        {1, 2, 0x84, 0x0c, 0x70, 0x38},
        {1, 2, 0x0c, 0x4c, 0x70, 0x38},
        {1, 2, 0x84, 0x4c, 0x70, 0x38},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 2, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_02171568(menu::MenuItem* menuItem, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x10, 0x88, 0x56, 0x10},
        {1, 2, 0x70, 0x88, 0x56, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 1, 2);
    menuItem->active_ = active;
}

THUMB void unkfunc_02171584(menu::MenuItem* menuItem)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x14, 0x6c, 0x68, 0x18},
        {1, 2, 0x8c, 0x6c, 0x68, 0x18},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 1, 2);
}

THUMB void unkfunc_02171598(menu::MenuItem* menuItem, int max, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x14, 0x0c, 0x60, 0x10},
        {1, 2, 0x8c, 0x0c, 0x60, 0x10},
        {1, 2, 0x14, 0x24, 0x60, 0x10},
        {1, 2, 0x8c, 0x24, 0x60, 0x10},
        {1, 2, 0x14, 0x3c, 0x60, 0x10},
        {1, 2, 0x8c, 0x3c, 0x60, 0x10},
        {1, 2, 0x14, 0x54, 0x60, 0x10},
        {1, 2, 0x8c, 0x54, 0x60, 0x10},
        {-1, -1, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 4, max);
    menuItem->active_ = active;
}
