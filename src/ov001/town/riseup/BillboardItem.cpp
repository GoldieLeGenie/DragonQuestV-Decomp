#include "main/dss/DssVectorDefault.hpp"
#include "ov001/town/riseup/BillboardItem.hpp"
#include "ov001/town/riseup/TownRiseupExhibit.hpp"
#include "main/dss/UnkMemory.hpp"
#include "main/menu/UnkMenuIconData.hpp"
#include "nitro/os.hpp"

#pragma thumb on

inline twn::UnkBillboardCorners::UnkBillboardCorners(const dss::Vector2<dss::Fix16>& v0, const dss::Vector2<dss::Fix16>& v1,
                                                   const dss::Vector2<dss::Fix16>& v2, const dss::Vector2<dss::Fix16>& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

inline void UnkBillboardTexCoord::set(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
                                      const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

inline twn::UnkBillboardTexCorners::UnkBillboardTexCorners(const dss::Vector2<dss::Fix32>& v0, const dss::Vector2<dss::Fix32>& v1,
                                                         const dss::Vector2<dss::Fix32>& v2, const dss::Vector2<dss::Fix32>& v3)
{
    set(v0, v1, v2, v3);
}

static dss::Vector2<dss::Fix16> xyLeftBottom(-0.48f, -0.0f);
static dss::Vector2<dss::Fix16> xyRightBottom(0.48f, -0.0f);
static dss::Vector2<dss::Fix16> xyRightTop(0.48f, 0.96f);
static dss::Vector2<dss::Fix16> xyLeftTop(-0.48f, 0.96f);
static dss::Vector2<dss::Fix32> uvLeftTop(0L, 0L);
static dss::Vector2<dss::Fix32> uvRightTop(32L, 0L);
static dss::Vector2<dss::Fix32> uvRightBottom(32L, 32L);
static dss::Vector2<dss::Fix32> uvLeftBottom(0L, 32L);
// layout stand-in: the original had three unreferenced 4-byte .rodata objects here (dead-stripped at
// link); they only take part in the .data/.bss heapsort order
static const int s_unusedRodata0[1] = { 0 };
static const int s_unusedRodata1[1] = { 0 };
static const int s_unusedRodata2[1] = { 0 };
static twn::UnkBillboardCorners xy(xyLeftBottom, xyRightBottom, xyRightTop, xyLeftTop);
static twn::UnkBillboardTexCorners uv(uvLeftBottom, uvRightBottom, uvRightTop, uvLeftTop);
static const dss::Fix32 scale(1.0f);

BillboardItem::BillboardItem()
{
}

BillboardItem::~BillboardItem()
{
}

void BillboardItem::unkfunc_0214e840(const char* filename)
{
    unk_b8.setup(filename, 0, 0);
    OS_Wait();
    unkfunc_0205071c(&xy, &uv, unk_b8.getAddr());
    setScale(scale);
    setPolygonID(0x1f);
    setAlpha(0x1f);
}

void BillboardItem::unkfunc_0214e8a0(const UnkBillboardVertex* vertex)
{
    unkfunc_02047a20(vertex);
}

void BillboardItem::unkfunc_0214e8a8(const UnkBillboardTexCoord* texCoord)
{
    unkfunc_02047a94(texCoord);
}

void BillboardItem::unkfunc_0214e8b0(const char* filename, int index)
{
    unsigned char buf[0x400];
    unk_b8.setup(filename, 0, 0);
    OS_Wait();
    unkfunc_0205071c(&xy, &uv, unk_b8.getAddr());
    texture_ = unk_b8.getAddr();
    ((TextureObject*)texture_)->unkfunc_02049e9c(0);
    ((TextureObject*)texture_)->unkfunc_0204a004();
    unkfunc_02047a20(&xy);
    unkfunc_02047a94(&uv);
    setAlpha(0x1f);
    RenderObject::texture_ = texture_;
    setScale(scale);
    unsigned char* dst = (unsigned char*)((TextureObject*)texture_)->unkfunc_0204a1c4();
    void* src = getMenuIconData(0xf0000000, index);
    switch (*(unsigned int*)src & 0xf0) {
    case 0x10:
        func_02070620(src, buf);
        break;
    case 0x20:
        func_02070720(src, buf);
        break;
    case 0x30:
        func_02070818(src, buf);
        break;
    }
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 8; x++) {
            for (int ty = 0; ty < 4; ty++) {
                for (int tx = 0; tx < 8; tx++) {
                    *dst++ = buf[y * 0x100 + ty * 0x40 + x * 8 + tx];
                }
            }
        }
    }
    void* palette = getMenuIconData(0xf0000000, 9999);
    dss::memcpy((void*)((TextureObject*)texture_)->unkfunc_0204a1d4(), palette, 0x200);
    ((TextureObject*)texture_)->unkfunc_0204a090(1);
}

void BillboardItem::draw()
{
    Billboard::draw();
}

void BillboardItem::cleanup()
{
    removeRender();
    unkfunc_02050760();
    unk_b8.cleanup();
}
