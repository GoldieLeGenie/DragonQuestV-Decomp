#pragma ipa file
#include "ov018/menu/UnkMenuTemplateBattle.hpp"
#include "ov018/menu/BattleMenu.hpp"

// touch areas of the battle menus

THUMB void unkfunc_02175a5c(menu::MenuItem* menuItem)
{
    static MENUITEM_DATA menu[] = {
        {2, 0xff, 0xde, 0x9e, 0x1c, 0x1c},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 1, 1, 1);
}

THUMB void unkfunc_02175a70(menu::MenuItem* menuItem)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0xde, 0x86, 0x1c, 0x1c},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 1, 1, 1);
}

THUMB void unkfunc_02175a84(menu::MenuItem* menuItem, int max, int active)
{
    static MENUITEM_DATA menuA[] = {
        {1, 2, 0x40, 0x80, 0x48, 0x20},
        {1, 2, 0x88, 0x80, 0x48, 0x20},
        {1, 2, 0x40, 0xa0, 0x48, 0x20},
        {1, 2, 0x88, 0xa0, 0x48, 0x20},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    static MENUITEM_DATA menuB[] = {
        {1, 2, 0x40, 0x80, 0x48, 0x20},
        {1, 2, 0x88, 0x80, 0x48, 0x20},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    if (max < 4) {
        menuItem->setMenuItem(menuB, 2, 2, max);
    } else {
        menuItem->setMenuItem(menuA, 2, 2, 4);
    }
    menuItem->active_ = active;
}

THUMB void unkfunc_02175ab8(menu::MenuItem* menuItem, int max)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x14, 0x0c, 0x68, 0x18},
        {1, 2, 0x8c, 0x0c, 0x68, 0x18},
        {1, 2, 0x14, 0x2c, 0x68, 0x18},
        {1, 2, 0x8c, 0x2c, 0x68, 0x18},
        {1, 2, 0x14, 0x4c, 0x68, 0x18},
        {1, 2, 0x8c, 0x4c, 0x68, 0x18},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 3, max);
}

THUMB void unkfunc_02175acc(menu::MenuItem* menuItem, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x24, 0x60, 0x36, 0x18},
        {1, 2, 0x64, 0x60, 0x36, 0x18},
        {1, 2, 0xa4, 0x60, 0x36, 0x18},
        {1, 2, 0x24, 0x80, 0x36, 0x18},
        {1, 2, 0x64, 0x80, 0x36, 0x18},
        {1, 2, 0xa4, 0x80, 0x36, 0x18},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 3, 2, 6);
    menuItem->active_ = active;
}

THUMB void unkfunc_02175ae8(menu::MenuItem* menuItem, int max)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x0c, 0x14, 0x70, 0x38},
        {1, 2, 0x84, 0x14, 0x70, 0x38},
        {1, 2, 0x0c, 0x54, 0x70, 0x38},
        {1, 2, 0x84, 0x54, 0x70, 0x38},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 2, max);
}

THUMB void unkfunc_02175afc(menu::MenuItem* menuItem, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x26, 0x86, 0x4e, 0x0e},
        {1, 2, 0x86, 0x86, 0x4e, 0x0e},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 1, 2);
    menuItem->active_ = active;
}

THUMB void unkfunc_02175b18(menu::MenuItem* menuItem, int active, int max)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x26, 0x76, 0x1c, 0x1c},
        {1, 2, 0x4e, 0x76, 0x1c, 0x1c},
        {1, 2, 0x76, 0x76, 0x1c, 0x1c},
        {1, 2, 0x9e, 0x76, 0x1c, 0x1c},
        {1, 2, 0xc6, 0x76, 0x1c, 0x1c},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 5, 1, max);
    menuItem->active_ = active;
}

// unused, keeps a constant table that is dead-stripped with it (fixes the data order)
THUMB int unkfunc_unused_02175b34(int index)
{
    static const int table[1] = {0};
    return table[index];
}

THUMB void unkfunc_02175b34(menu::MenuItem* menuItem, int active, int max)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x36, 0x76, 0x1c, 0x1c},
        {1, 2, 0x5e, 0x76, 0x1c, 0x1c},
        {1, 2, 0x86, 0x76, 0x1c, 0x1c},
        {1, 2, 0xae, 0x76, 0x1c, 0x1c},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 4, 1, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_02175b50(menu::MenuItem* menuItem, int active, int max)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x16, 0x76, 0x1c, 0x1c},
        {1, 2, 0x3e, 0x76, 0x1c, 0x1c},
        {1, 2, 0x66, 0x76, 0x1c, 0x1c},
        {1, 2, 0x8e, 0x76, 0x1c, 0x1c},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 4, 1, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_02175b6c(menu::MenuItem* menuItem, int active, int max)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x16, 0x6e, 0x1c, 0x1c},
        {1, 2, 0x3e, 0x6e, 0x1c, 0x1c},
        {1, 2, 0x66, 0x6e, 0x1c, 0x1c},
        {1, 2, 0x8e, 0x6e, 0x1c, 0x1c},
        {1, 2, 0xb6, 0x6e, 0x1c, 0x1c},
        {1, 2, 0x16, 0x96, 0x1c, 0x1c},
        {1, 2, 0x3e, 0x96, 0x1c, 0x1c},
        {1, 2, 0x66, 0x96, 0x1c, 0x1c},
        {1, 2, 0x8e, 0x96, 0x1c, 0x1c},
        {1, 2, 0xb6, 0x96, 0x1c, 0x1c},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 5, 2, max);
    menuItem->active_ = active;
}

THUMB void unkfunc_02175b88(menu::MenuItem* menuItem, int active, menu::TOUCHRECT* rect, int count)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {1, 2, 0, 0, 0, 0},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    for (int i = 0; i < count; i++) {
        if (i < count) {
            menu[i].x = rect[i].x;
            menu[i].y = rect[i].y;
            menu[i].w = rect[i].width;
            menu[i].h = rect[i].height;
        }
    }
    menuItem->setMenuItem(menu, 12, 1, count);
    menuItem->active_ = active;
}

THUMB void unkfunc_02175be0(menu::MenuItem* menuItem)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0, 0, 0, 0},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menu[0].x = 0;
    menu[0].y = 0x20;
    menu[0].w = 0x100;
    menu[0].h = 0x60;
    menuItem->setMenuItem(menu, 1, 1, 1);
}

THUMB void unkfunc_02175c0c(menu::MenuItem* menuItem, int active, int max, int x, int y)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 6, 6, 0x1c, 0x1c},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 1, 1, 1);
    if (max == 0) {
        menuItem->setMenuItem(menu, 1, 1, 0);
        return;
    }
    menuItem->active_ = active;
    menuItem->setBaseXY(x, y);
}

// unused 2x3 list (its table stays in the data)
THUMB void unkfunc_unused_02177bdc(menu::MenuItem* menuItem, int max, int active)
{
    static MENUITEM_DATA menu[] = {
        {1, 2, 0x1c, 0x0c, 0x60, 0x18},
        {1, 2, 0x94, 0x0c, 0x60, 0x18},
        {1, 2, 0x1c, 0x2c, 0x60, 0x18},
        {1, 2, 0x94, 0x2c, 0x60, 0x18},
        {1, 2, 0x1c, 0x4c, 0x60, 0x18},
        {1, 2, 0x94, 0x4c, 0x60, 0x18},
        {0xff, 0xff, 0, 0, 0, 0},
    };
    menuItem->setMenuItem(menu, 2, 3, max);
    menuItem->active_ = active;
}
