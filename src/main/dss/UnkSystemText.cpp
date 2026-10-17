#include "main/dss/UnkSystemText.hpp"
#include "main/dss/UnkDisplay.hpp"
#include "main/dss/UnkBgBuffer.hpp"
#include "main/dss/UnkVramRequest.hpp"

void* data_02101550[5];

THUMB void unkfunc_0204e654(void* res0, void* res1, void* res2, void* res3, void* res4)
{
    for (int i = 0; i < 5; i++) {
        data_02101550[i] = NULL;
    }
    data_02101550[0] = res0;
    data_02101550[1] = res1;
    data_02101550[2] = res2;
    data_02101550[3] = res3;
    data_02101550[4] = res4;
    unsigned char* tile = (unsigned char*)unkfunc_0204e698(1);
    for (int i = 0; i < 0xa0; i++) {
        unkfunc_0204ee28(tile, NULL);
        tile += 0x20;
    }
}

THUMB void* unkfunc_0204e698(int index)
{
    return data_02101550[index];
}

THUMB void* unkfunc_0204e6a4(int index)
{
    return data_02101550[index];
}

THUMB void unkfunc_0204e6b0(int type, int screen1, int screen2)
{
    if (type == 0) {
        return;
    }
    int sub = 0;
    int second = 1;
    if (type == 3) {
        sub = 1;
        second = 0;
    }
    unkfunc_0204dca8(unkfunc_0204de14(screen1), 0, unkfunc_0204e698(0), 0x1000);
    UnkCharBuffer buffer;
    void* chr = unkfunc_0204e698(3);
    unkfunc_0204e558(&buffer, chr, 0x20, 8);
    unkfunc_0204dca8(0x13, 0x2000, chr, 0x2000);
    if (sub) {
        unkfunc_0204dca8(unkfunc_0204de14(screen1), 0x8000, unkfunc_0204e698(0), 0x1000);
    }
    if (second) {
        unkfunc_0204dca8(unkfunc_0204de14(screen2), 0, unkfunc_0204e698(0), 0x1000);
    }
}

THUMB void unkfunc_0204e74c(int type, int screen1, int screen2)
{
    if (type == 0) {
        return;
    }
    int second = 1;
    if (type == 3) {
        second = 0;
    }
    unsigned short* palette1 = (unsigned short*)unkfunc_0204e6a4(2);
    unsigned short* palette2 = (unsigned short*)unkfunc_0204e6a4(4);
    unsigned short defaultPalette[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7fff};
    if (palette1 == NULL) {
        palette1 = defaultPalette;
    }
    if (palette2 == NULL) {
        palette2 = defaultPalette;
    }
    UnkPaletteBuffer* bg = unkfunc_0204cd8c(screen1);
    bg->unkfunc_0204dbf4(0xe, 0, palette1 + 0x10, 0x10);
    bg->unkfunc_0204dbf4(0xf, 0, palette1, 0x10);
    UnkPaletteBuffer* obj = unkfunc_0204cdf0(0);
    obj->unkfunc_0204dbf4(0xe, 0, palette2 + 0x10, 0x10);
    obj->unkfunc_0204dbf4(0xf, 0, palette2, 0x10);
    if (second == 0) {
        return;
    }
    bg = unkfunc_0204cd8c(screen2);
    bg->unkfunc_0204dbf4(0xe, 0, palette1 + 0x10, 0x10);
    bg->unkfunc_0204dbf4(0xf, 0, palette1, 0x10);
    obj = unkfunc_0204cdf0(1);
    obj->unkfunc_0204dbf4(0xe, 0, palette2 + 0x10, 0x10);
    obj->unkfunc_0204dbf4(0xf, 0, palette2, 0x10);
}
