#pragma once
#include <globaldefs.h>
#include "main/dss/UnkRenderObject.hpp"
#include "main/data/DataObject.hpp"
#include "main/dss/Render.hpp"

/* vtable 0x020c43e4 */
struct UnkSprite2D : UnkRenderObject {
    virtual void draw();                        // 0x02084590

    dss::Vector2<dss::Fix32> unk_14;            // 0x14 position
    short unk_1c;                               // 0x1C width
    short unk_1e;                               // 0x1E height
    short unk_20;                               // 0x20 texture u0
    short unk_22;                               // 0x22 texture v0
    short unk_24;                               // 0x24 texture u1
    short unk_26;                               // 0x26 texture v1
    int unk_28;                                 // 0x28 depth
    int unk_2c;                                 // 0x2C screens (bit 0: main, bit 1: sub)
    unsigned short unk_30;                      // 0x30 rotation
    unsigned short unk_32;                      // 0x32 texture mode
    unsigned short unk_34;                      // 0x34 color

    UnkSprite2D();
    void unkfunc_02047e88(int x, int y);
    void unkfunc_02047e9c(dss::Fix32 x, dss::Fix32 y);
    void unkfunc_02047ec0(int w, int h);
    void unkfunc_02047ecc(int u0, int v0, int u1, int v1);
    void setColor(int r, int g, int b);
    void setColor(int color);
};

struct UnkMenuSprite {
    Render* render_;                            // 0x00
    DataObject data_;                           // 0x04
    void* texture_;                             // 0x14
    UnkSprite2D sprite_;                        // 0x18

    UnkMenuSprite();
    ~UnkMenuSprite();
    int unkfunc_02057d50();
    void unkfunc_02057d88(void* addr);
    void unkfunc_02051b14(int x, int y);
    void unkfunc_02057ed4(int enable);
    void unkfunc_02057ef4();
    void unkfunc_02057f38(int a);
    void unkfunc_02051a20();
    void unkfunc_02051a2c();
    void unkfunc_02051a38();
    int unkfunc_02051a44();                     // texture data
    void unkfunc_02051a50(const char* filename, int a);
    void unkfunc_02051a68();
    void unkfunc_02051ac4();
    void unkfunc_02051adc(Render* render);
    void unkfunc_02051af0();                    // remove from the render
    int unkfunc_02051b04();
    void unkfunc_02051b20(int w, int h);
    void unkfunc_02051b2c(int u0, int v0, int u1, int v1);
    void unkfunc_02051b40(dss::Fix32 x, dss::Fix32 y);
    void unkfunc_02051b68();
    void unkfunc_02051b74(int enable);
    void unkfunc_02051b78();
    void unkfunc_02051b80();
    void unkfunc_02051b88();
    void unkfunc_02051b90(int a);
    void unkfunc_02051ba0(int polygonID);
    void unkfunc_02051bb0(int a);
    void unkfunc_02051bb4(int a);
    void unkfunc_02051bbc(unsigned char r, unsigned char g, unsigned char b);
    void unkfunc_02051bc8(int color);
};

