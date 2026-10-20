#pragma ipa file
#include "main/menu/MenuIconDisplay.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/DssUtils.hpp"
#include "nitro/g2.hpp"

THUMB MenuIconDisplay::MenuIconDisplay()
{
}

THUMB void MenuIconDisplay::setup(int id)
{
    id_ = id;
    reset();
    setType(1);
    for (int i = 0; i < 4; i++) {
        posX_[i] = -1;
        posY_[i] = -1;
        value_[i] = -1;
    }
}

THUMB void MenuIconDisplay::update(UnkOamBuffer* main, UnkOamBuffer* sub)
{
}

THUMB void MenuIconDisplay::execute(UnkOamBuffer* main, UnkOamBuffer* sub)
{
}

THUMB void MenuIconDisplay::draw(UnkOamBuffer* main, UnkOamBuffer* sub)
{
    if (!unkfunc_02064730(main, sub)) {
        return;
    }
    if (y_ > 0xc0) {
        return;
    }
    if (flag_[0] == 1) {
        unkfunc_02064ddc(main, posX_[0], posY_[0], 0);
    }
    if (flag_[1] == 1) {
        unkfunc_02064ddc(main, posX_[1], posY_[1], 1);
    }
    if (flag_[2] == 1) {
        unkfunc_02064ddc(main, posX_[2], posY_[2], 2);
    }
    if (flag_[3] == 1) {
        unkfunc_02064ddc(main, posX_[3], posY_[3], 3);
    }
    flag_[0] = 0;
    flag_[1] = 0;
    flag_[2] = 0;
    flag_[3] = 0;
}

THUMB void MenuIconDisplay::unkfunc_02064ddc(UnkOamBuffer* oam, int x, int y, int index)
{
    index *= 8;
    G2_SetOBJAttr(oam->allocEntry(), x, y, 2, GX_OAM_MODE_NORMAL, FALSE, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x32, GX_OAM_COLORMODE_256, index + 0xe0, 0, 0);
    G2_SetOBJAttr(oam->allocEntry(), x, y + 0x20, 2, GX_OAM_MODE_NORMAL, FALSE, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_32x16, GX_OAM_COLORMODE_256, index + 0x160, 0, 0);
    G2_SetOBJAttr(oam->allocEntry(), x + 0x20, y, 2, GX_OAM_MODE_NORMAL, FALSE, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x16, GX_OAM_COLORMODE_256, index + 0x1a0, 0, 0);
    G2_SetOBJAttr(oam->allocEntry(), x + 0x20, y + 0x10, 2, GX_OAM_MODE_NORMAL, FALSE, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x16, GX_OAM_COLORMODE_256, index + 0x1a4, 0, 0);
    G2_SetOBJAttr(oam->allocEntry(), x + 0x20, y + 0x20, 2, GX_OAM_MODE_NORMAL, FALSE, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x8, GX_OAM_COLORMODE_256, index + 0x1e0, 0, 0);
    G2_SetOBJAttr(oam->allocEntry(), x + 0x20, y + 0x28, 2, GX_OAM_MODE_NORMAL, FALSE, GX_OAM_EFFECT_NONE, GX_OAM_SHAPE_16x8, GX_OAM_COLORMODE_256, index + 0x1e4, 0, 0);
}

THUMB void MenuIconDisplay::loadIcon(int index, int value)
{
    if (value == -1) {
        flag_[index] = 0;
        return;
    }
    if (value == 0x5f) {
        value = 8;
    }
    posX_[index] = index << 6;
    posY_[index] = 0x80;
    value_[index] = value;
    flag_[index] = 0;
    void* src = getMenuIconData(0xf5000000, value);
    transferIconTiles(index * 8, 7, src, 0, 0, 8);
    transferIconTiles(index * 8, 8, src, 0, 1, 8);
    transferIconTiles(index * 8, 9, src, 0, 2, 8);
    transferIconTiles(index * 8, 10, src, 0, 3, 8);
    transferIconTiles(index * 8, 11, src, 0, 4, 8);
    transferIconTiles(index * 8, 12, src, 0, 5, 8);
    transferIconTiles(index * 8, 13, src, 8, 0, 4);
    transferIconTiles(index * 8, 14, src, 8, 1, 4);
    transferIconTiles(index * 8 + 4, 13, src, 8, 2, 4);
    transferIconTiles(index * 8 + 4, 14, src, 8, 3, 4);
    transferIconTiles(index * 8, 15, src, 8, 4, 4);
    transferIconTiles(index * 8 + 4, 15, src, 8, 5, 4);
    getObjPaletteBuffer(1)->loadColors(0, 0, getMenuIconData(0xf5000000, 9999), 0xa0);
}

THUMB void MenuIconDisplay::setIconPosition(int index, int x, int y)
{
    posX_[index] = x;
    posY_[index] = y;
}

THUMB void MenuIconDisplay::setIconVisible(int index, int flag)
{
    flag_[index] = flag;
}

THUMB void MenuIconDisplay::transferIconTiles(int x, int y, void* src, int srcX, int srcY, int width)
{
    requestVramCopy(0x23, (x + y * 32) * 32, (char*)src + (srcX + srcY * 12) * 32, width * 32);
}
